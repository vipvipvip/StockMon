// MktSumVw.cpp : implementation file
//

#include "stdafx.h"
#include "StockMon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "IAccess.h"
#include "Thread.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for CSMView
#include "ui.h"
#include "readmsg.h"
#include "UMapi.h"
#include "MMSYSTEM.H"
#include "SMView.h"
#include "MktSumVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// data for the list view control

#define NUM_COLUMNS	5

static WCHAR *_gszColumnLabel[NUM_COLUMNS]=
{
	_T("Ticker"), _T("Last"), _T("Change"), _T("Pct Change"), _T("Volume")
};

static int _gnColumnFmt[NUM_COLUMNS]=
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT
};

static int _gnColumnWidth[NUM_COLUMNS]=
{
	100, 100, 150, 100, 100
};

/////////////////////////////////////////////////////////////////////////////
// CMktSumVw

IMPLEMENT_DYNCREATE(CMktSumVw, CListViewEx)

CMktSumVw::CMktSumVw()
{
}

CMktSumVw::CMktSumVw(CSMView *pOwner)
{
	ASSERT(pOwner);
	m_pOwner = pOwner;
	// create the large icon image list.
	m_LargeImageList.Create(32,32,
		FALSE,			// list does not include masks
		4,
		0 );			// list won't grow

	// Create the small icon image list.
	m_SmallImageList.Create(16,16,
		FALSE,			// list does not include masks
		4,
		0 );			// list won't grow

	
	m_bmLarge.LoadBitmap(IDB_LARGE_ARROWS);
	m_bmSmall.LoadBitmap(IDB_SMALL_ARROWS);
	m_nLargeIdx = m_LargeImageList.Add(&m_bmLarge, (CBitmap*)NULL);
	m_nSmallIdx = m_SmallImageList.Add(&m_bmSmall, (CBitmap*)NULL);

}

CMktSumVw::~CMktSumVw()
{
	EmptyTickers();
}

void CMktSumVw::EmptyTickers()
{
	CStkTicker *p=NULL;

	for ( int i=0; i<m_VolumeArray.GetSize(); i++) {
		p = (CStkTicker *)m_VolumeArray[i];
		delete p;
	}
	m_VolumeArray.RemoveAll();

	for (int  i=0; i<m_PctGainersArray.GetSize(); i++) {
		p = (CStkTicker *)m_PctGainersArray[i];
		delete p;
	}
	m_PctGainersArray.RemoveAll();

	for ( int i=0; i<m_PctLosersArray.GetSize(); i++) {
		p = (CStkTicker *)m_PctLosersArray[i];
		delete p;
	}
	m_PctLosersArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CMktSumVw, CListViewEx)
	//{{AFX_MSG_MAP(CMktSumVw)
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewViewquotes)
	ON_COMMAND(ID_HELP_HOWTOREGISTER, OnHelpHowtoregister)
	ON_COMMAND(ID_PORTFOLIO_ADDTICKER, OnPortfolioAddticker)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_ADDTICKER, OnUpdatePortfolioAddticker)
	ON_COMMAND(ID_SUMMARY_NYSE, OnSummaryNyse)
	ON_COMMAND(ID_SUMMARY_NASDAQ, OnSummaryNasdaq)
	ON_COMMAND(ID_SUMMARY_AMEX, OnSummaryAmex)
	//}}AFX_MSG_MAP
	ON_MESSAGE (SHOW_MKT_SUMMARY, OnShowMktSummary)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMktSumVw drawing

void CMktSumVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMktSumVw diagnostics

#ifdef _DEBUG
void CMktSumVw::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CMktSumVw::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMktSumVw message handlers

void CMktSumVw::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	

	CListCtrl& ListCtrl=GetListCtrl();
// set image lists

	// Associate the image lists with the list view control.
	ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);
	ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);

// insert columns

	int i;
	LV_COLUMN lvc;

	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i=0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem=i;
		lvc.pszText=_gszColumnLabel[i];
		lvc.cx=_gnColumnWidth[i];
		lvc.fmt=_gnColumnFmt[i];
		ListCtrl.DeleteColumn(i);
		ListCtrl.InsertColumn(i,&lvc);
	}
}

void CMktSumVw::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
}

BOOL CMktSumVw::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style|= LVS_SHOWSELALWAYS | LVS_REPORT | LVS_EDITLABELS;
	return CListViewEx::PreCreateWindow(cs);
}


afx_msg LRESULT  CMktSumVw::OnShowMktSummary(WPARAM wParam, LPARAM lParam)
{
	CString strWebPageContent((LPCTSTR)lParam);
	DisplayQuote(strWebPageContent);

	return 0;
}

void CMktSumVw::DisplayQuote(CString& rWebPage)
{
  try {
	  EmptyTickers();
	  CListCtrl& ListCtrl=GetListCtrl();
	  int iLen = rWebPage.GetLength();
	  int iPos = 0;

	  if( !GetExchange(m_strExchg, rWebPage) )
		  return;
	  
	  CString strSrch;
	  strSrch = "Top 10 ";
	  strSrch += m_strExchg;
	  strSrch += " Volume Leaders";

	  iPos = rWebPage.Find(strSrch);
	  if(iPos != -1 ) {
		  CString str = rWebPage.Mid(iPos);
		  GetData(str, m_VolumeArray);
	  }

	  strSrch = "Top 10 ";
	  strSrch += m_strExchg;
	  strSrch += " Percentage Gainers";

	  iPos = rWebPage.Find(strSrch);
	  if(iPos != -1 ) {
		  CString str = rWebPage.Mid(iPos);
		  GetData(str, m_PctGainersArray);
	  }

	  strSrch = "Top 10 ";
	  strSrch += m_strExchg;
	  strSrch += " Percentage Losers";

	  iPos = rWebPage.Find(strSrch);
	  if(iPos != -1 ) {
		  CString str = rWebPage.Mid(iPos);
		  GetData(str, m_PctLosersArray);
	  }

	  OnPopulateList();
  }
  catch (...) {}
}


int CMktSumVw::GetExchange( CString& rExchg, const CString& rWebPage)
{
	rExchg.Empty();

	if ( -1 != rWebPage.Find((LPCTSTR)"NASDAQ Market Summary") ) {
		rExchg = "NASDAQ";
	}
	else if (-1 != rWebPage.Find((LPCTSTR)"AMEX Market Summary") ){
		rExchg = "AMEX";
	}
	else if (-1 != rWebPage.Find((LPCTSTR)"NYSE Market Summary") ){
		rExchg = "NYSE";
	}
	return rExchg.GetLength();
}

void CMktSumVw::GetData(CString rWebPage, CPtrArray& rArray)
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iLen = rWebPage.GetLength();
	int iPos = 0;

	int iTickers=10;

	CString strTicker;
	CString strLast;
	CString strChange;
	CString strPctChange;
	CString strVolume;

	CStkTicker *p = NULL;
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT;
	for ( int i=0; i<iTickers; i++) {

		strTicker.Empty();
		iPos = rWebPage.Find((LPCTSTR)"TICKER=");
		if ( iPos != -1) {
			iPos += wcslen((LPCTSTR)"TICKER=");
//			while ( iPos < iLen && rWebPage[iPos] != '>') iPos++;
//			iPos++;
			while ( iPos < iLen && isalpha(rWebPage[iPos]) && rWebPage[iPos] != '&') {
				strTicker += rWebPage[iPos];
				iPos++;
			}
			if ( !strTicker.IsEmpty() ) {
				strTicker.TrimLeft();
				strTicker.TrimRight();
				p = new CStkTicker(strTicker);

				rArray.Add(p);
			}
			rWebPage = rWebPage.Mid(iPos);
			iLen = rWebPage.GetLength();
		} // end ticker

		// Get the last price
		strLast.Empty();
		iPos = rWebPage.Find((LPCTSTR)"face=");
		if ( iPos != -1 ) {
			iPos += wcslen((LPCTSTR)"face=");
			while ( iPos < iLen && rWebPage[iPos] != '>') iPos++;
			iPos++;

			while ( iPos < iLen && rWebPage[iPos] != '<') {
				strLast += rWebPage[iPos];
				iPos++;
			}
			strLast.TrimLeft();
			strLast.TrimRight();
			p->m_strLast = strLast;
			rWebPage = rWebPage.Mid(iPos);
			iLen = rWebPage.GetLength();
		} // end last

		// Get the Change
		strChange.Empty();
		iPos = rWebPage.Find((LPCTSTR)"font color=");
		if ( iPos != -1 ) {
			iPos += wcslen((LPCTSTR)"font color=");
			while ( iPos < iLen && rWebPage[iPos] != '>') iPos++;
			iPos++;

			while ( iPos < iLen && rWebPage[iPos] != '<') {
				strChange += rWebPage[iPos];
				iPos++;
			}
			strChange.TrimLeft();
			strChange.TrimRight();
			p->m_strChange = strChange;
			rWebPage = rWebPage.Mid(iPos);
			iLen = rWebPage.GetLength();
		} // end Change

		// Get the Pct Change
		strPctChange.Empty();
		iPos = rWebPage.Find((LPCTSTR)"font color=");
		if ( iPos != -1 ) {
			iPos += wcslen((LPCTSTR)"font color=");
			while ( iPos < iLen && rWebPage[iPos] != '>') iPos++;
			iPos++;

			while ( iPos < iLen && rWebPage[iPos] != '<') {
				strPctChange += rWebPage[iPos];
				iPos++;
			}
			strPctChange.TrimLeft();
			strPctChange.TrimRight();
			p->m_strPctChange = strPctChange;
			rWebPage = rWebPage.Mid(iPos);
			iLen = rWebPage.GetLength();
		} // end Pct Change

		// Get the volume
		strVolume.Empty();
		iPos = rWebPage.Find((LPCTSTR)"face=");
		if ( iPos != -1 ) {
			iPos += wcslen((LPCTSTR)"face=");
			while ( iPos < iLen && rWebPage[iPos] != '>') iPos++;
			iPos++;

			while ( iPos < iLen && rWebPage[iPos] != '<') {
				strVolume += rWebPage[iPos];
				iPos++;
			}
			strVolume.TrimLeft();
			strVolume.TrimRight();
			p->m_strVolume = strVolume;
			rWebPage = rWebPage.Mid(iPos);
			iLen = rWebPage.GetLength();
		} // end Volume

	} // end for loop
}

void CMktSumVw::OnPopulateList()
{

	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.DeleteAllItems();

	int iRowNum=0;
	LV_ITEM lvi;

	// Title for Volume
	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	CString strTitle;
	char tmpbuf[128];
	_strtime( tmpbuf );
	strTitle = m_strExchg;
	strTitle += " ( As of ";
	strTitle += tmpbuf;
	strTitle += " )";	

	ListCtrl.SetItemText(iRowNum,2, strTitle);
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"Top 10 Volume");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"   Leaders   ");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	iRowNum++;

	// insert items
	int nCount = m_VolumeArray.GetSize();


	for(int i=0; i<nCount; i++)
	{
		CStkTicker *p = (CStkTicker *)m_VolumeArray[i];
		lvi = p->m_lvi;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.pszText = (LPTSTR)(LPCTSTR)p->m_strSymbol;
		lvi.iImage = GetImageIndex(p->m_strChange);
		lvi.iItem=iRowNum;
		lvi.iSubItem=0;
		ListCtrl.InsertItem(&lvi);

		ListCtrl.SetItemText(iRowNum,1, p->m_strLast);
		ListCtrl.SetItemText(iRowNum,2, p->m_strChange);
		ListCtrl.SetItemText(iRowNum,3, p->m_strPctChange);
		ListCtrl.SetItemText(iRowNum,4, p->m_strVolume);
		iRowNum++;
	}

	// Title for Gainers
	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"Top 10 Pct");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"   Gainers   ");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	iRowNum++;


	nCount = m_PctGainersArray.GetSize();

	for(int i=0; i<nCount; i++)
	{
		CStkTicker *p = (CStkTicker *)m_PctGainersArray[i];
		lvi = p->m_lvi;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.pszText = (LPTSTR)(LPCTSTR)p->m_strSymbol;
		lvi.iImage = GetImageIndex(p->m_strChange);
		lvi.iItem=iRowNum;
		lvi.iSubItem=0;
		ListCtrl.InsertItem(&lvi);

		ListCtrl.SetItemText(iRowNum,1, p->m_strLast);
		ListCtrl.SetItemText(iRowNum,2, p->m_strChange);
		ListCtrl.SetItemText(iRowNum,3, p->m_strPctChange);
		ListCtrl.SetItemText(iRowNum,4, p->m_strVolume);
		iRowNum++;
	}

	// Title for Losers
	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"Top 10 Pct");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	ListCtrl.SetItemText(iRowNum,2,(LPCTSTR)"   Losers   ");
	iRowNum++;

	lvi.mask = LVIF_IMAGE;
	lvi.iImage = 0;
	lvi.iItem=iRowNum;
	lvi.iSubItem=0;
	ListCtrl.InsertItem(&lvi);
	iRowNum++;

	nCount = m_PctLosersArray.GetSize();

	for(int i=0; i<nCount; i++)
	{
		CStkTicker *p = (CStkTicker *)m_PctLosersArray[i];
		lvi = p->m_lvi;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.pszText = (LPTSTR)(LPCTSTR)p->m_strSymbol;
		lvi.iImage = GetImageIndex(p->m_strChange);
		lvi.iItem=iRowNum;
		lvi.iSubItem=0;
		ListCtrl.InsertItem(&lvi);

		ListCtrl.SetItemText(iRowNum,1, p->m_strLast);
		ListCtrl.SetItemText(iRowNum,2, p->m_strChange);
		ListCtrl.SetItemText(iRowNum,3, p->m_strPctChange);
		ListCtrl.SetItemText(iRowNum,4, p->m_strVolume);
		iRowNum++;
	}

	Invalidate();
	UpdateWindow();
}

int CMktSumVw::GetImageIndex( CString& rString )
{
	if( rString.Find('+') != -1 ) {
		return m_nSmallIdx+2;
	}
	else if(rString.Find('-') != -1 ) {
		return m_nSmallIdx+1;
	}
	else {
		return m_nSmallIdx;
	}
}

void CMktSumVw::OnViewViewquotes() 
{
	m_pOwner->m_bSummaryInProgress=FALSE;
	THEAPP()->SwitchView(m_pOwner);	
}

void CMktSumVw::OnHelpHowtoregister() 
{
}

void CMktSumVw::OnPortfolioAddticker() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int nItem=0;
	CString strTicker;
  CStkTicker *p = NULL;
	CSMDoc *pDoc = (CSMDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	nItem	=	ListCtrl.GetNextItem(-1,LVNI_SELECTED);
	while ( nItem != -1) {
		strTicker= ListCtrl.GetItemText(nItem, 0);
    if (!strTicker.IsEmpty() && !m_pOwner->InListCtrl(strTicker)) {
      p = new CStkTicker(strTicker);
      if(p) {
        sLock.Lock();
        pDoc->m_TickerArray.InsertAt( pDoc->m_TickerArray.GetSize(),p);
        sLock.Unlock();
      }
    }
    nItem	=	ListCtrl.GetNextItem(nItem,LVNI_SELECTED);
	}

  if (m_pOwner) {
    m_pOwner->SendMessage(POPULATE_LIST,0,0);
  }
}


void CMktSumVw::OnUpdatePortfolioAddticker(CCmdUI* pCmdUI) 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int nItem	=	ListCtrl.GetNextItem(-1,LVNI_SELECTED);
  pCmdUI->Enable(nItem != -1);
}



void CMktSumVw::OnSummaryNyse() 
{
  if (m_pOwner)  {
    m_pOwner->OnSummaryNyse();
  }
	
}

void CMktSumVw::OnSummaryNasdaq() 
{
  if (m_pOwner)  {
    m_pOwner->OnSummaryNasdaq();
  }

}

void CMktSumVw::OnSummaryAmex() 
{
  if (m_pOwner)  {
    m_pOwner->OnSummaryAmex();
  }
}
