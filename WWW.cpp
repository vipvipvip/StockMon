// WWW.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "StkTickr.h"
#include "request.h"
#include "SMDoc.h"
#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"
#include "WWW.h"
#include "BrowserVw.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Trim(CString& rStr)
{
  rStr.TrimLeft();
  rStr.TrimRight();
}

/////////////////////////////////////////////////////////////////////////////
// CWWW

IMPLEMENT_DYNCREATE(CWWW, CCmdTarget)

CWWW::CWWW()
{
  m_nRef=0;
}

CWWW::~CWWW()
{
}


BEGIN_MESSAGE_MAP(CWWW, CCmdTarget)
	//{{AFX_MSG_MAP(CWWW)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWWW message handlers
void CWWW::GetALLQuotes()
{
  THEAPP()->CheckSerNo(TRUE);

  if ( !m_pDoc ) return;
  if ( !m_pView ) return;

	CSingleLock sLock(&m_pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;
	int i=0;
	int nNewReq=0;
	int iNumTickers = m_pDoc->m_TickerArray.GetSize();

  m_pView->m_time = CTime::GetCurrentTime();
	sLock.Lock();

  while ( i < iNumTickers ) {

    strAddr = m_strAddr;    
	  strIden.Empty();

	  pReq = new CRequest;
	  for ( int j=0; j<m_pDoc->m_nMaxStksInReq && i<iNumTickers; j++ ) {
		  CStkTicker *p = (CStkTicker *)m_pDoc->m_TickerArray[i];
		  if(p) {
			  if (pReq) {
				  if ( j!=0) {
					  strAddr += ',';
					  strIden += '+';
				  }
				  strAddr += p->m_strSymbol;
				  strIden += p->m_strSymbol;
			  }
		  }
		  i++;
	  }
		if (iNumTickers==1) strAddr += ",IBM";
	  pReq->Init(strAddr, strIden, this);
	  m_pDoc->m_ReqArray.Add(pReq);
	  m_pView->m_QuotesReq++;
	  nNewReq++;
    AddRef();
	}
	sLock.Unlock();
	long l;
  if ( 0 == m_pView->m_TotThreads ) {
    m_pView->StartWorkerThread();
  }

  if( nNewReq > 0 ) AddRef(nNewReq);

	ReleaseSemaphore(m_pView->m_hWorkEvent, nNewReq<m_pView->m_TotThreads ? nNewReq:m_pView->m_TotThreads, &l);
}

void CWWW::GetQuote(CString& rStr)
{
  THEAPP()->CheckSerNo(TRUE);

  if ( !m_pDoc ) return;
  if ( !m_pView ) return;

	CSingleLock sLock(&m_pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;

	strAddr = m_strAddr;
  strAddr += rStr;
	strAddr += _T(",IBM");

	strIden = rStr;

  pReq = new CRequest;
	pReq->Init(strAddr, strIden, this);
  sLock.Lock();
	m_pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_pView->m_QuotesReq++;
  AddRef();
  long l;
  if ( 0 == m_pView->m_TotThreads ) {
    m_pView->StartWorkerThread();
  }
	ReleaseSemaphore(m_pView->m_hWorkEvent, 1, &l);
}

void CWWW::UpdateSelected()
{
  THEAPP()->CheckSerNo(TRUE);

  if (!m_pDoc ) return;
  if (!m_pView) return;

	CSingleLock sLock(&m_pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;
	int i=0;
	int nNewReq=0;
	CListCtrl& ListCtrl=m_pView->GetListCtrl();
	int iNumTickers = ListCtrl.GetItemCount();
	int nItem=-1;
	CStkTicker *p=NULL;

	nItem = m_pView->GetSelectedRows(&p, nItem);
	while ( i < iNumTickers ) {
		if (nItem == -1 || !p ) {
			break;
		}

	  strAddr = m_strAddr;

		strIden.Empty();

		pReq = new CRequest;
		for ( int j=0; p && j<m_pDoc->m_nMaxStksInReq && i<iNumTickers; j++ ) {

			if (pReq) {
				if ( j!=0) {
					strAddr += ',';
					strIden += '+';
				}
				strAddr += p->m_strSymbol;
				strAddr += _T(",IBM");
				strIden += p->m_strSymbol;
			}

			nItem = m_pView->GetSelectedRows(&p, nItem);
			if (nItem == -1 || !p ) {
				break;
			}

			i++;
		}
		pReq->Init(strAddr, strIden, this);
		sLock.Lock();
		m_pDoc->m_ReqArray.Add(pReq);
		sLock.Unlock();
		m_pView->m_QuotesReq++;
		nNewReq++;
		if (nItem == -1 || !p ) {
			break;
		}
	}
	
	if( nNewReq ) {
    AddRef(nNewReq);
		THEAPP()->CheckSerNo(TRUE);
		long l;
    if ( 0 == m_pView->m_TotThreads ) {
      m_pView->StartWorkerThread();
    }
  	ReleaseSemaphore(m_pView->m_hWorkEvent, nNewReq<m_pView->m_TotThreads ? nNewReq:m_pView->m_TotThreads, &l);
	}

/*
  if ( !m_pDoc ) return;
  if ( !m_pView ) return;
	int nItem=-1;
	CStkTicker *p=NULL;

	while ( TRUE ) {
		nItem = m_pView->GetSelectedRows(&p, nItem);
		if (nItem == -1 || !p ) {
			break;
		}
    if (p) {
      GetQuote(p->m_strSymbol);
    }
  }
*/

}

void CWWW::GetNews()
{
	THEAPP()->CheckSerNo(TRUE);

	if (!m_pDoc) return;
	//  if (!m_pView) return;
	//  m_pView->CreateBrowserWindow();
	CString strBrowser = THEAPP()->GetBrowser();
	BOOL bNewWindow = 1;
	int iPos, iPos2;
	iPos = strBrowser.ReverseFind('\\');
	iPos2 = strBrowser.Find((LPCTSTR)".exe");
	CString sExe;
	sExe = strBrowser.Mid(iPos + 1, iPos2 - iPos);
	sExe += "exe";


	//  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
	//  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);

	CSingleLock sLock(&m_pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq = NULL;
	int i = 0;
	int nNewReq = 0;
	CListCtrl& ListCtrl = m_pView->GetListCtrl();
	int iNumTickers = ListCtrl.GetItemCount();
	int nItem = -1;
	CStkTicker *p = NULL;

	nItem = m_pView->GetSelectedRows(&p, nItem);
	while (i < iNumTickers) {
		if (nItem == -1 || !p) {
			break;
		}

		strAddr = m_strAddr;

		for (int j = 0; p && j < m_pDoc->m_nMaxStksInReq && i < iNumTickers; j++) {

			if (j != 0) {
				strAddr += ',';
			}
			strAddr += p->m_strSymbol;


			nItem = m_pView->GetSelectedRows(&p, nItem);
			if (nItem == -1 || !p) {
				break;
			}
			i++;
		}
		//    m_pView->m_pBrowserVw->Navigate2(strAddr);
		if (bNewWindow) {
			::ShellExecute(NULL, L"open", L"chrome.exe", strAddr, NULL, SW_SHOWNORMAL);
		}

		if (nItem == -1 || !p) {
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CWWWYahoo

IMPLEMENT_DYNCREATE(CWWWYahoo, CCmdTarget)

CWWWYahoo::CWWWYahoo()
{
  m_pDoc = NULL;
  m_pView = NULL;

	m_strAddr = _T("http://");
	m_strAddr += _T("quote.yahoo.com");
	m_strAddr += _T("/q?d=t&s=");

}

CWWWYahoo::CWWWYahoo(CSMView *pView)
{
  if ( pView ) {
    m_pView = pView;
    m_pDoc = m_pView->GetDocument();
  }
}

CWWWYahoo::~CWWWYahoo()
{
}


BEGIN_MESSAGE_MAP(CWWWYahoo, CCmdTarget)
	//{{AFX_MSG_MAP(CWWWYahoo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWWWYahoo message handlers

void CWWWYahoo::GetALLQuotes()
{
	m_strAddr = _T("http://");
	m_strAddr += _T("finance.yahoo.com");
	m_strAddr += _T("/quotes/");
	m_strAddr = _T("http://download.finance.yahoo.com/d/quotes.csv?f=nsl1c1p2vomo");
	m_strAddr += _T("&s=");
  CWWW::GetALLQuotes();
  return;
}

void CWWWYahoo::GetQuote(CString &rStr)
{
	m_strAddr = _T("http://");
	m_strAddr += _T("finance.yahoo.com");
	m_strAddr += _T("/quotes/");
	m_strAddr = _T("http://download.finance.yahoo.com/d/quotes.csv?f=nsl1c1p2vomo");
	m_strAddr += _T("&s=");
  CWWW::GetQuote(rStr);
  return;
}

void CWWWYahoo::HandleQuote(CString &rTicker, CString &rWebPage)
{
  THEAPP()->StripTags(rWebPage.GetBuffer());

  int iPos;
  CString strTicker;
  strTicker = rTicker;

/*
  CString sFind;

  sFind = "Download Data";
  iPos = rWebPage.Find(sFind);
  if ( iPos != -1 ) {
    rWebPage=rWebPage.Mid(1, iPos);
  }

  sFind = "View Comparison Chart";
  iPos = rWebPage.Find(sFind);
  if ( iPos != -1 ) {
    rWebPage=rWebPage.Mid(1, iPos);
  }

  sFind = "Cash Flow";
  iPos = rWebPage.Find(sFind);
  if ( iPos == -1 ) {
    sFind = "Summary";
    iPos = rWebPage.Find(sFind);
    if ( iPos == -1 ) {
      return;
    }
    else {
      // The word Summary appears twice when asking for more than 1 stock
      //rWebPage=rWebPage.Mid(iPos+sFind.GetLength()+1);
      //iPos = rWebPage.Find(sFind);
      //if ( iPos == -1 ) return;
    }
  }
  rWebPage=rWebPage.Mid(iPos+sFind.GetLength()+1);
  Trim(rWebPage);
*/


	if ( -1 != (iPos = strTicker.Find(',')) ) {
		CString str = strTicker.Left(iPos);
		iPos =rWebPage.Find(str[0] == '$' ? str.Mid(1) : str);
		if(iPos != -1) {
			DisplayMultiQuote(strTicker, rWebPage);
		}
    return;
	}
	else {
		iPos =rWebPage.Find(strTicker[0] == '$' ? strTicker.Mid(1) : strTicker);
		if(iPos != -1) {
			DisplaySingleQuote(strTicker, rWebPage);
		}
    return;
	}
}

void CWWWYahoo::UpdateSelected()
{
	m_strAddr = _T("http://");
	m_strAddr += _T("finance.yahoo.com");
	m_strAddr += _T("/q?d=s&s=");

	m_strAddr = _T("http://download.finance.yahoo.com/d/quotes.csv?f=nsl1c1p2vomo");
	m_strAddr += _T("&s=");
  CWWW::UpdateSelected();
  return;
}

void CWWWYahoo::DisplayMultiQuote(CString& rSymbol, CString& rWebPage)
{

	int iPos = 0;
	int nSymbols=0;
	CStringArray TickArray;
	int iSlash = rSymbol.ReverseFind('/');
	rSymbol = rSymbol.Mid(iSlash+1);
	while ( -1 != (iPos = rSymbol.Find(','))) {
		CString str = rSymbol.Left(iPos);
		TickArray.Add(str);
		rSymbol = rSymbol.Mid(iPos+1);
	}
	TickArray.Add(rSymbol);

	for (int i=0; i<TickArray.GetSize(); i++) {
    DisplaySingleQuote(TickArray[i], rWebPage);
	}
}

/*
 * Use this is HTML tags are not stripped off
*/ 
/*
void CWWWYahoo::DisplaySingleQuote(CString& rSymbol, CString& rWebPage)
{
  CString strPrevCls;
  CString strName;
  CString strHigh;
	CString strLow;
	CString strLast;
	CString strChange;
	CString strVolume;
  CString strLastTraded;
	int iPos = 0;
	CListCtrl& ListCtrl=m_pView->GetListCtrl();
	int iLen = rWebPage.GetLength();

	iPos = rWebPage.Find((LPCTSTR)"<b>");
  if ( iPos == -1 ) return;
  iPos += 3;

  // Name
  while ( iPos < iLen && rWebPage[iPos] != '<') {
    strName += rWebPage[iPos++];
  }
  iPos++;
  Trim(strName);

  rWebPage=rWebPage.Mid(iPos);
	iLen = rWebPage.GetLength();

  // Last Traded  
  iPos = rWebPage.Find((LPCTSTR)"Last Trade");
  if ( iPos == -1 ) return;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage[iPos] != ' ') {
    strLastTraded += rWebPage[iPos++];
  }
  iPos++;
  Trim(strLastTraded);

  //Close
  while ( iPos < iLen && rWebPage.Mid(iPos,2) != "<b" ) iPos++;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage.Mid(iPos,5) != "</td>") {
    if ( (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || (rWebPage[iPos] == '/' && rWebPage[iPos+1] == '<') ) 
      strLast += rWebPage[iPos++];
    else
      iPos++;
  }
  iPos++;
  Trim(strLast);


  rWebPage=rWebPage.Mid(iPos);
	iLen = rWebPage.GetLength();

  // Change
  iPos = rWebPage.Find((LPCTSTR)"Change");
  if ( iPos == -1 ) return;

  while ( iPos < iLen && (rWebPage[iPos] != '+' && rWebPage[iPos] != '-') ) iPos++;
  while ( iPos < iLen && rWebPage[iPos] != '(' ) {
    if ( (rWebPage[iPos]) == '.' || (rWebPage[iPos]) == '-' || (rWebPage[iPos]) == '+' || (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || (rWebPage[iPos] == '/' && rWebPage[iPos+1] == '<') ) 
      strChange += rWebPage[iPos++];
    else
      iPos++;
  }
  iPos++;

  Trim(strChange);

  rWebPage=rWebPage.Mid(iPos);
	iLen = rWebPage.GetLength();

  // Prev Cls
  iPos = rWebPage.Find((LPCTSTR)"Prev Cls");
  if ( iPos == -1 ) return;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage[iPos] != '<') {
    if ( (rWebPage[iPos]) == '.' ||  (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || (rWebPage[iPos] == '/' && rWebPage[iPos+1] == '<') ) 
      strPrevCls += rWebPage[iPos++];
    else
      iPos++;
  }
  iPos++;
  Trim(strPrevCls);

  rWebPage=rWebPage.Mid(iPos);
	iLen = rWebPage.GetLength();

  // Volume
  iPos = rWebPage.Find((LPCTSTR)"Volume");
  if ( iPos == -1 ) return;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage[iPos] != '<') {
    strVolume += rWebPage[iPos++];
  }
  iPos++;
  Trim(strVolume);

  rWebPage=rWebPage.Mid(iPos);
	iLen = rWebPage.GetLength();

  // Day's Range
  iPos = rWebPage.Find((LPCTSTR)"Range");
  if ( iPos == -1 ) return;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage[iPos] != '-') {
    if ( (rWebPage[iPos]) == '.' || (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || (rWebPage[iPos] == '/' && rWebPage[iPos+1] == '<') ) 
      strLow += rWebPage[iPos++];
    else
      iPos++;
  }
  iPos++;
  while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
  while ( iPos < iLen && rWebPage.Mid(iPos,5) != "</td>") {
    if ( (rWebPage[iPos]) == '.' || (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || (rWebPage[iPos] == '/' && rWebPage[iPos+1] == '<') ) 
      strHigh += rWebPage[iPos++];
    else
      iPos++;
  }
  Trim(strLow);
  Trim(strHigh);


  CString strMsg;
  strMsg.Format((LPCTSTR)"Name=%s, High=%s. Low=%s, Last=%s, Change=%s, Volume=%s",
                 strName, strHigh, strLow, strLast, strChange, strVolume);

//  AfxMessageBox(strMsg);

  iPos = rWebPage.Find((LPCTSTR)"<table border=1");
  if ( iPos >= 0 ) {
    rWebPage=rWebPage.Mid(iPos);  
  }
	CStkTicker *p = m_pView->InsertTicker(rSymbol, strLast, strChange, strHigh, strLow, strVolume, strName, strLastTraded);
	m_pView->UpdateRow(p);
}
*/
void CWWWYahoo::HandleIndex(CString& rSymbol, CString& rWebPage)
{
//		rWebPage = rWebPage.Replace((WCHAR)"&amp;", "&");

	CString strPctChg;
  CString strPrevCls;
  CString strName;
  CString strHigh;
	CString strLow;
	CString strLast;
	CString strChange;
	CString strVolume;
  CString strLastTraded;
	int iPos = 0;
	int iPos1=0;
	int iPos2=0;

  CString sSearch;
  sSearch = ":";
  sSearch += rSymbol;

	int iLen = rWebPage.GetLength();

  iPos = rWebPage.Find(sSearch);
  if ( iPos == -1 ) {
		sSearch = ": ";
		sSearch += rSymbol;
		iPos = rWebPage.Find(sSearch);
		if ( iPos == -1 ) return;
	}

  
  int iTemp;
  while ( iPos != 0 && rWebPage[iPos] != '(' ) iPos--;
  --iPos;
  iTemp = iPos;

  iPos = rWebPage.Find(_T("New View"));
	if (iPos == -1) iPos = rWebPage.Find(_T("Site"));
	if (iPos == -1 ) return;
	strName  = rWebPage.Mid(iPos,iTemp-iPos);
	strName.Replace(_T("New View"), _T(""));
	strName.Replace(_T("Site"), _T(""));
	strName.Replace(_T("&nbsp;"), _T(""));
  strName.Replace(_T("&amp;"), _T("&"));
  Trim(strName);

	// Index Value:
  iPos = rWebPage.Find(_T("Index Value:"));
	rWebPage = rWebPage.Mid(iPos+12);
	iPos=0;
	
	while (rWebPage.Mid(iPos, 5) != _T("Trade")) {
		strLast = strLast + rWebPage.Mid(iPos,1);
		iPos++;
	}

	// Trade Time:
	sSearch = _T("Trade Time:");
  iPos = rWebPage.Find(sSearch);
  if ( iPos == -1 ) return;
  rWebPage = rWebPage.Mid(iPos+sSearch.GetLength());
  iLen = rWebPage.GetLength();
  iPos=0;
	while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
	
	while ( rWebPage.Mid(iPos,6) !=  _T("Change") ) {
		strLastTraded = strLastTraded + rWebPage.Mid(iPos,1);
		iPos++;
	}
  Trim(strLastTraded);

	// Change:
	iPos = rWebPage.Find(_T("Change:"));
	rWebPage = rWebPage.Mid(iPos+11);
	iLen = rWebPage.GetLength();
	iPos=0;
	while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;

	while (rWebPage.Mid(iPos, 1) != _T("(")) {
		strChange = strChange + rWebPage.Mid(iPos,1);
		iPos++;
	}
	Trim(strChange);

	// Pct change
	iPos++;
	while (rWebPage.Mid(iPos, 1) != _T(")")) {
		strPctChg = strPctChg + rWebPage.Mid(iPos,1);
		iPos++;
	}

	// Prev Close:
	iPos = rWebPage.Find(_T("Prev Close:"));
	rWebPage = rWebPage.Mid(iPos+11);
	iPos=0;
	
	while (rWebPage.Mid(iPos, 4) != _T("Open")) {
		strPrevCls = strPrevCls + rWebPage.Mid(iPos,1);
		iPos++;
	}

	// Day's Range:
	iPos = rWebPage.Find(_T("Day's Range:"));
	rWebPage = rWebPage.Mid(iPos+12);
	iPos=0;
	iLen = rWebPage.GetLength();	

	while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
	while (iPos < iLen && rWebPage[iPos] != '-' && rWebPage.Mid(iPos, 3) != _T("N/A")) {
		if ( (rWebPage[iPos]) == '.' || (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || rWebPage[iPos] == '/' ) 
			strLow += rWebPage[iPos++];
		else
			iPos++;
	}
	iPos++;
	while ( iPos < iLen && !isdigit(rWebPage[iPos]) ) iPos++;
	while (iPos < iLen && !isalpha(rWebPage[iPos]) && rWebPage.Mid(iPos, 2) != "52" && rWebPage.Mid(iPos, 3) != _T("N/A")) {
		if ( (rWebPage[iPos]) == '.' || (rWebPage[iPos]) == ' ' || isdigit(rWebPage[iPos]) || rWebPage[iPos] == '/') 
			strHigh += rWebPage[iPos++];
		else
			iPos++;
	}
	Trim(strLastTraded);
	Trim(strLow);
	Trim(strHigh);
	Trim(strLast);
	Trim(strPrevCls);
	Trim(strChange);

	strLow.Replace(_T("),"), _T(""));
	strHigh.Replace(_T("),"), _T(""));
	strLast.Replace(_T("),"), _T(""));
	strPrevCls.Replace(_T("),"), _T(""));
	strChange.Replace(_T("nbsp;"), _T(""));

  if ( _wtof(strLast) - _wtof(strPrevCls)  > 0 ) {
    strChange = CString(_T("+")) + strChange;
		strPctChg = CString(_T("+")) + strPctChg;
  } else if ( _wtof(strLast) - _wtof(strPrevCls)  < 0 ) {
     strChange = CString(_T("-")) + strChange;
		 strPctChg = CString(_T("-")) + strPctChg;
  }


	CStkTicker *p = m_pView->InsertTicker(rSymbol, strLast, strChange, strPctChg, strHigh, strLow, strVolume, strName, strLastTraded);
	m_pView->UpdateRow(p);

	return;
}

void CWWWYahoo::DisplaySingleQuote(CString& rSymbol, CString& rWebPage)
{
	if ( rSymbol.Find(_T("^")) != -1 ) {
		HandleIndex(rSymbol, rWebPage);
		return;
	}

  CString strPrevCls;
  CString strName;
  CString strHigh;
	CString strLow;
	CString strLast;
	CString strChange;
	CString strVolume;
  CString strLastTraded;
  CString strPctChg;

  int iPos = 0;
  CString sSearch;
  sSearch = _T("\"") + rSymbol + _T("\"");
  int iLen = rWebPage.GetLength();

  iPos = rWebPage.Find(sSearch);
  if ( iPos == -1 ) {
		sSearch = _T(": ");
		sSearch += rSymbol;
		iPos = rWebPage.Find(sSearch);
		if ( iPos == -1 ) {
			iPos = rWebPage.Find(rSymbol);
			if (iPos == -1) return;
		}
	}
  int iTemp, iTemp2;
  iTemp=iPos;
  iTemp2=0;
  while (iTemp2<3 && iTemp >= 0) {
	  if (rWebPage[iTemp] == _T('\"')) iTemp2++;
	  iTemp--;
  }
  iPos = rWebPage.Find(_T("\""), iTemp+1);
  iTemp = rWebPage.Find(_T("\""),iPos+1);
  strName  = rWebPage.Mid(iPos+1, iTemp-iPos-1);

  iPos = rWebPage.Find(sSearch);
  iPos = rWebPage.Find(_T(","), iPos+1);
  iTemp = rWebPage.Find(_T(","),iPos+1);
  strLast = rWebPage.Mid(iPos+1, iTemp-iPos);
  Trim(strLast);
  strLast.Replace(_T(","), _T(""));

  // Change
  iPos = rWebPage.Find(_T(","), iPos+1);
  iTemp = rWebPage.Find(_T(","),iPos+1);
  strChange = rWebPage.Mid(iPos+1, iTemp-iPos);
  Trim(strChange);
  strChange.Replace(_T("&nbsp;"), _T(""));
  strChange.Replace(_T(""), _T(""));
  strChange.Replace(_T(","), _T(""));

	//Pct Change
  iPos = rWebPage.Find(_T(","), iPos+1);
  iTemp = rWebPage.Find(_T("%"),iPos+1);
  strPctChg = rWebPage.Mid(iPos+1, iTemp-iPos);
  Trim(strPctChg);
  strPctChg.Replace(_T("\""), _T(""));

  //Prev Close
  strPrevCls.Format(_T("%9.2f"), _wtof(strLast) + _wtof(strChange));
  Trim(strPrevCls);
  strPrevCls.Replace(_T("&nbsp;"), _T(""));
  strPrevCls.Replace(_T(","), _T(""));

  // Volume
  iPos = rWebPage.Find(_T(","), iPos+1);
  iTemp = rWebPage.Find(_T(","),iPos+1);
  strVolume = rWebPage.Mid(iPos+1, iTemp-iPos);
  Trim(strVolume);
  strVolume.Replace(_T(","), _T(""));

  // Day's Range
  iPos = rWebPage.Find(_T("\""), iPos+1);
  iTemp = rWebPage.Find(_T("\""),iPos+1);
  iTemp2 = rWebPage.Find(_T("-"),iPos+1);
  strLow = rWebPage.Mid(iPos+1, iTemp2-iPos-1);
  strHigh = rWebPage.Mid(iTemp2+1, iTemp-iTemp2);
  Trim(strLow);
  Trim(strHigh);
  strLow.Replace(_T(","), _T(""));
  strHigh.Replace(_T(","), _T(""));
  strHigh.Replace(_T("\""), _T(""));
  strLow.Replace(_T("\""), _T(""));

  // Trade Time
  //Trim(strLastTraded);

//  CString strMsg;
//  strMsg.Format((LPCTSTR)"Prev Cls = %s, Last Traded = %s, Name=%s, High=%s. Low=%s, Last=%s, Change=%s, Volume=%s",
//                 strPrevCls, strLastTraded, strName, strHigh, strLow, strLast, strChange, strVolume);

//  AfxMessageBox(strMsg);

	CStkTicker *p = m_pView->InsertTicker(rSymbol, strLast, strChange, strPctChg, strHigh, strLow, strVolume, strName, strLastTraded);
	m_pView->UpdateRow(p);

}

void CWWWYahoo::GetNews()
{
	m_strAddr = "http://";
	m_strAddr += "finance.yahoo.com";
	m_strAddr += "/q?d=t&s=";

  CWWW::GetNews();
  return;
}

void CWWWYahoo::GetNews(CString strTicker)
{
CString strBrowser = THEAPP()->GetBrowser();
m_strAddr = "\"http://";
m_strAddr += "finance.yahoo.com";
m_strAddr += "/q?d=t&s=";
m_strAddr += strTicker;
m_strAddr += "\"";
BOOL bNewWindow=1;
int iPos, iPos2;
iPos = strBrowser.ReverseFind('\\');
iPos2 = strBrowser.Find(_T(".exe"));
CString sExe;
sExe = strBrowser.Mid(iPos+1, iPos2-iPos);
sExe += "exe";

if (bNewWindow)
   ::ShellExecute(NULL, NULL, sExe, m_strAddr, NULL, SW_SHOWNORMAL);
  else
  {
	  if(!m_pView) return;
	  m_pView->CreateBrowserWindow();
	  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
	  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
		m_pView->m_pBrowserVw->Navigate2(m_strAddr,BrowserNavConstants::navNoReadFromCache | BrowserNavConstants::navOpenInNewTab  );
	}
}
