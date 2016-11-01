// ScreenVw.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h"
//#include "IAccess.h"
//#include "Thread.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for CSMView
#include "ui.h"
#include "readmsg.h"
//#include "UMapi.h"
//#include "MMSYSTEM.H"
#include "SMView.h"
#include "Valuation.h"
#include "ScreenVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenVw

#define SCREEN_VW_SUBHEADING _T("Settings\\Screening View")

IMPLEMENT_DYNCREATE(CScreenVw, CListViewEx)

CScreenVw::CScreenVw()
{
  m_pOwner=NULL;
}

CScreenVw::CScreenVw(CSMView *pOwner)
{
  ASSERT(pOwner);
  m_pOwner = pOwner;
}


CScreenVw::~CScreenVw()
{
  EmptyDataArray();
}

void CScreenVw::EmptyDataArray()
{
  CScreenVwData *p=NULL;
  
	for ( int i=0; i<m_DataArray.GetSize(); i++) {
		p = (CScreenVwData *)m_DataArray[i];
		delete p;
	}
	m_DataArray.RemoveAll();
}

BEGIN_MESSAGE_MAP(CScreenVw, CListViewEx)
	//{{AFX_MSG_MAP(CScreenVw)
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewViewquotes)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_PORTFOLIO_ADDTICKER, OnPortfolioAddticker)
	ON_COMMAND(ID_VIEW_REFRESHVALUATION, OnViewRefreshvaluation)
	//}}AFX_MSG_MAP
	ON_MESSAGE (SHOW_SCREEN_STKS, OnShowScreenedStks)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenVw drawing

void CScreenVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CScreenVw diagnostics

#ifdef _DEBUG
void CScreenVw::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CScreenVw::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScreenVw message handlers

void CScreenVw::OnViewViewquotes() 
{
	THEAPP()->SwitchView(m_pOwner);	
}


afx_msg LRESULT  CScreenVw::OnShowScreenedStks(WPARAM wParam, LPARAM lParam)
{
	CString strWebPageContent((LPCTSTR)lParam);

  if ( -1 != strWebPageContent.Find((LPCTSTR)"Displaying the first") ) {
    AfxMessageBox((LPCTSTR)"More than 100 companies qualify. Please refine your search.");
  }


	CFile f;
	int bOpen = f.Open((LPCTSTR)"c:\\x.htm", CFile::modeCreate | CFile::modeWrite);

	if ( bOpen ) {
		f.Write(strWebPageContent, strWebPageContent.GetLength());
	}

  ShowScreenedStocks(strWebPageContent);
  return 0;
}

void CScreenVw::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	
	m_strColWidths = THEAPP()->GetProfileString(SCREEN_VW_SUBHEADING, FRM_LHV_COLWIDTH );
	DisplayColumnHeadings(IDS_SCRNVIEW);
	
}

void CScreenVw::OnDestroy() 
{
	// Save the column widths
	CListCtrl& ListCtrl=GetListCtrl();
	int i=0;
	WCHAR szT[80];
	CString strValue;
	CString strTemp;
	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT;
	lvc.pszText = szT;
	lvc.cchTextMax = sizeof(szT) - sizeof(char);
	while ( ListCtrl.GetColumn(i++, &lvc) ) {
		strTemp.Format(_T("%d "), lvc.cx);
		strValue += strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( SCREEN_VW_SUBHEADING, FRM_LHV_COLWIDTH, strValue );
	}
	CListViewEx::OnDestroy();
	
}

void CScreenVw::ShowScreenedStocks(CString& rWebPage)
{
  EmptyDataArray();
  EraseList(TRUE);
  ParseScreenedStocksHTML(rWebPage);

  CScreenVwData *p=NULL;
  int iRow=0;
  int iCol=0;
  for ( int i=0; i<m_DataArray.GetSize(); i++) {
		p = (CScreenVwData *)m_DataArray[i];
    AddItem(iRow, iCol++, p->m_strTicker,p);
    AddItem(iRow, iCol++, p->m_strCompany);
    AddItem(iRow, iCol++, p->m_strLast);
    AddItem(iRow, iCol++, p->m_strPE);
    AddItem(iRow, iCol++, p->m_strYield);
    AddItem(iRow, iCol++, p->m_strROE);
    AddItem(iRow, iCol++, p->m_strDE);
    AddItem(iRow, iCol++, p->m_strEPSChg);	  
    AddItem(iRow, iCol++, p->m_strEarnGr);
    AddItem(iRow, iCol++, p->m_strMktCap);
    iRow++;
    iCol=0;
  }
}

void CScreenVw::ParseScreenedStocksHTML(CString& rWebPage)
{
  CString strToken((LPCTSTR)"?s=");
  CString strSymbolToken((LPCTSTR)"?s=");

  int iPos;
  
  iPos = rWebPage.Find((LPCTSTR)"New Courier");
  if (iPos == -1) return;
  rWebPage = rWebPage.Mid(iPos);

  iPos = rWebPage.Find(strToken);

/*
  while ( iPos != -1 ) {
    iPos += strToken.GetLength();
    if ( rWebPage.Mid(iPos,strSymbolToken.GetLength()) == strSymbolToken) {
      rWebPage = rWebPage.Mid(iPos+strSymbolToken.GetLength());
      iPos = 0;
      break;
    }
    else {
      rWebPage = rWebPage.Mid(iPos);
      iPos = rWebPage.Find(strToken);
    }
  }
*/

  if ( iPos == - 1) {
    return;
  }
  else {
    rWebPage = rWebPage.Mid(iPos+strToken.GetLength()+1);
    iPos=0;
  }
  CString strTicker;
  CString strCompany;
  CString strLast;
  CString strPE;
  CString strYield;
  CString strROE;
  CString strDE;
  CString strEPSChg;
  CString strEarnGr;
  CString strMktCap;

  int iLen = 0;
  while ( iPos != -1 ) {
    iLen = rWebPage.GetLength();

    CScreenVwData *pData = new CScreenVwData;
    if (!pData) return;

    // get ticker symbol
    strTicker.Empty();
    while (iPos < iLen && rWebPage[iPos] != '&' ) {
      strTicker += rWebPage[iPos++];
    }
    pData->m_strTicker = strTicker;


    // get the company name
    strCompany.Empty();
    while (iPos < iLen && rWebPage[iPos] != '>' ) iPos++;
    iPos++;
    while (iPos < iLen && rWebPage[iPos] != '<' ) {
      strCompany += rWebPage[iPos++];
    }
    pData->m_strCompany = strCompany;

    for ( int i=0; i<8;i++) {
      strLast.Empty();
      strPE.Empty();
      strYield.Empty();
      strROE.Empty();
      strDE.Empty();
      strEPSChg.Empty();
      strEarnGr.Empty();
      strMktCap.Empty();

      while (iPos < iLen && rWebPage.Mid(iPos,11) != "New Courier")  iPos++;
      iPos += 11+2;

      while (iPos < iLen && rWebPage[iPos] != '<' ) {
        if(rWebPage[iPos] != ' ') {
          switch(i) {
            case 0:
              strLast += rWebPage[iPos++];
              pData->m_strLast = strLast;
              break;

            case 1:
              strPE += rWebPage[iPos++];
              pData->m_strPE = strPE;
              break;

            case 2:
              strYield += rWebPage[iPos++];
              pData->m_strYield = strYield;
              break;

            case 3:
              strROE += rWebPage[iPos++];
              pData->m_strROE = strROE;
              break;

            case 4:
              strDE += rWebPage[iPos++];
              pData->m_strDE = strDE;
              break;

            case 5:
              strEPSChg += rWebPage[iPos++];
              pData->m_strEPSChg = strEPSChg;
              break;

            case 6:
              strEarnGr += rWebPage[iPos++];
              pData->m_strEarnGr = strEarnGr;
              break;

            case 7:
              strMktCap += rWebPage[iPos++];
              pData->m_strMktCap = strMktCap;
              break;
          }
        }
        else {
          iPos++;
        }
      }
    }
    m_DataArray.Add(pData);
    rWebPage = rWebPage.Mid(iPos);
    iPos = rWebPage.Find(strSymbolToken);
    if(iPos != -1 )
      iPos += strSymbolToken.GetLength();
  }

}


static int iColOrder[] = {0,0,0,0,0,0,0,0,0,0};
static CSMDoc *pDoc = NULL;

void CScreenVw::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl& ListCtrl=GetListCtrl();
	iColOrder[pNMListView->iSubItem]==0 ? iColOrder[pNMListView->iSubItem]=1 : iColOrder[pNMListView->iSubItem]=0;

	pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	ListCtrl.SortItems(CompareFunc, (LPARAM)(pNMListView->iSubItem));
	*pResult = 0;
}

int CALLBACK CScreenVw::CompareFunc(LPARAM lParam1, LPARAM lParam2, 
	LPARAM lParamSort)
{
	CScreenVwData *p1 = (CScreenVwData *)lParam1;
	CScreenVwData *p2 = (CScreenVwData *)lParam2;
	double dRes;
	int iRes=0;
	CString str1, str2;
	int i=0;
	if ( !p1 || !p2 )
		return iRes;

	switch( lParamSort)
	{
		case 0: // Ticker
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strTicker, p2->m_strTicker);
			}
			else {
				iRes = lstrcmpi(p2->m_strTicker, p1->m_strTicker);
			}
			break;
		case 1: // Company
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strCompany, p2->m_strCompany);
			}
			else {
				iRes = lstrcmpi(p2->m_strCompany, p1->m_strCompany);
			}
			break;

		case 2: // Last Price
			str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			str2 = pDoc->ConvertToDecimal(p2->m_strLast);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 3: // P/E
			str1 = pDoc->ConvertToDecimal(p1->m_strPE);
			str2 = pDoc->ConvertToDecimal(p2->m_strPE);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 4: // Yield
			str1 = pDoc->ConvertToDecimal(p1->m_strYield);
			str2 = pDoc->ConvertToDecimal(p2->m_strYield);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

    case 5: // ROE
			str1 = pDoc->ConvertToDecimal(p1->m_strROE);
			str2 = pDoc->ConvertToDecimal(p2->m_strROE);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 6: // D/E
			str1 = pDoc->ConvertToDecimal(p1->m_strDE);
			str2 = pDoc->ConvertToDecimal(p2->m_strDE);
			if(iColOrder[lParamSort]) {
				dRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				dRes = _wtoi(str2) - _wtoi(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 7: // EPS Change
			str1 = pDoc->ConvertToDecimal(p1->m_strEPSChg);
			str2 = pDoc->ConvertToDecimal(p2->m_strEPSChg);
			if(iColOrder[lParamSort]) {
				dRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				dRes = _wtoi(str2) - _wtoi(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 8: // Earn Growth
			str1 = pDoc->ConvertToDecimal(p1->m_strEarnGr);
			str2 = pDoc->ConvertToDecimal(p2->m_strEarnGr);
			if(iColOrder[lParamSort]) {
				dRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				dRes = _wtoi(str2) - _wtoi(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 9: // Mkt Cap
			str1 = pDoc->ConvertToDecimal(p1->m_strMktCap);
			str2 = pDoc->ConvertToDecimal(p2->m_strMktCap);
			if(iColOrder[lParamSort]) {
				dRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				dRes = _wtoi(str2) - _wtoi(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

	}
	return iRes;
}


void CScreenVw::OnPortfolioAddticker() 
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


void CScreenVw::OnViewRefreshvaluation() 
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
        m_pOwner->SubmitReqForValuation(p);
        sLock.Unlock();
      }
    }
    nItem	=	ListCtrl.GetNextItem(nItem,LVNI_SELECTED);
	}

  
  if (m_pOwner) {
    m_pOwner->SendMessage(POPULATE_LIST,0,0);
  }
	
}
