// BrowserVw.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "IAccess.h"
#include "Thread.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for CBrowserVw
#include "SMView.h"
#include "BrowserVw.h"
#include "MainFrm.h"
#include "WWW.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserVw

IMPLEMENT_DYNCREATE(CBrowserVw, CHtmlView)

CBrowserVw::CBrowserVw()
{
  m_pOwner=NULL;
	m_iRange = CSMView::YAHOO_6_MONTH;
	m_cChartType = "c";
}

CBrowserVw::CBrowserVw(CSMView *pOwner)
{
	//{{AFX_DATA_INIT(CBrowserVw)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  ASSERT(pOwner);
  m_pOwner = pOwner;
  m_iRange  = pOwner->m_iRange;
//	m_cChartType = m_pOwner->m_cChartType.IsEmpty() ? "c" : m_pOwner->m_cChartType;
	m_cChartType = "c";
}

CBrowserVw::~CBrowserVw()
{
}

void CBrowserVw::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrowserVw)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrowserVw, CHtmlView)
	//{{AFX_MSG_MAP(CBrowserVw)
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewViewquotes)
	ON_COMMAND(ID_VIEW_VIEWRBG, OnViewRGB)
	ON_COMMAND(ID_VIEW_VIEWVALUATIONS, OnViewViewvaluations)
	ON_COMMAND(ID_BROWSER_STOP, OnBrowserStop)
	ON_COMMAND(ID_BROWSER_BACK, OnBrowserBack)
	ON_COMMAND(ID_BROWSER_FORWARD, OnBrowserForward)
	ON_COMMAND(ID_BROWSER_REFRESH, OnBrowserRefresh)
	ON_COMMAND(ID_PORTFOLIO_GETNEWS, OnPortfolioGetnews)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_COMMAND(ID_CHART_YAHOO_ONE_DAY, OnChartYahooOneDay)
	ON_COMMAND(ID_CHART_YAHOO_5_DAY, OnChartYahoo5Day)
	ON_COMMAND(ID_CHART_YAHOO_10_DAY, OnChartYahoo10Day)
	ON_COMMAND(ID_CHART_YAHOO_3_MONTH, OnChartYahoo3Month)
	ON_COMMAND(ID_CHART_YAHOO_6_MONTH, OnChartYahoo6Month)
	ON_COMMAND(ID_CHART_YAHOO_1_YEAR, OnChartYahoo1Year)
	ON_COMMAND(ID_CHART_YAHOO_2_YEAR, OnChartYahoo2Year)
	ON_COMMAND(ID_CHART_YAHOO_5_YEAR, OnChartYahoo5Year)
	ON_COMMAND(ID_CHART_YAHOO_MAX, OnChartYahooMax)
	ON_COMMAND(ID_CHART_TYPE_LINE, OnChartTypeLine)
	ON_COMMAND(ID_CHART_TYPE_BAR, OnChartTypeBar)
	ON_COMMAND(ID_CHART_TYPE_CANDLE, OnChartTypeCandle)
	ON_COMMAND(ID_VIEW_REFRESHVALUATION, OnViewRefreshvaluation)
	ON_COMMAND(ID_PORTFOLIO_DELETETICKER, OnPortfolioDeleteticker)
	ON_COMMAND(ID_PORTFOLIO_ADDTICKER, OnPortfolioAddticker)
	ON_COMMAND(ID_SITE_YAHOO, OnSiteYahoo)
	ON_COMMAND(ID_SITE_TD, OnSiteTd)
	ON_COMMAND(ID_COMPAREWITH_SP500, &CSMView::OnComparewithSp500)
	ON_COMMAND(ID_COMPAREWITH_NASDAQ, &CSMView::OnComparewithNasdaq)
	ON_COMMAND(ID_COMPAREWITH_DOW, &CSMView::OnComparewithDow)
	ON_COMMAND(ID_COMPAREWITH_CLEAR, &CSMView::OnComparewithClear)

	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(0xe00, 0xfff, OnFavorite)
 	ON_MESSAGE (SHOW_CHART, OnShoWCHARt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserVw diagnostics

#ifdef _DEBUG
void CBrowserVw::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBrowserVw::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

void CBrowserVw::OnViewViewquotes() 
{
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(0);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(1);

	THEAPP()->SwitchView((CView *)m_pOwner);	
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserVw message handlers
afx_msg LRESULT  CBrowserVw::OnShoWCHARt(WPARAM wParam, LPARAM lParam)
{
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
	((CMainFrame *)THEAPP()->m_pMainWnd)->Invalidate();

  CString strURL = (LPCTSTR)wParam;
  if (!strURL.IsEmpty() ) {
    Navigate2(strURL, 0, NULL);
  }
  return 0;
}


void CBrowserVw::OnViewRefreshvaluation()
{
  if (m_pOwner)
    m_pOwner->OnViewRefreshvaluation();	

}
void CBrowserVw::OnChartYahooOneDay() 
{
  m_iRange = CSMView::YAHOO_1_DAY;
	m_pOwner->m_iRange = CSMView::YAHOO_1_DAY;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_1_DAY);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahooOneDay();  	
}
void CBrowserVw::OnChartYahoo5Day() 
{
  m_iRange = CSMView::YAHOO_5_DAY;
	m_pOwner->m_iRange = CSMView::YAHOO_5_DAY;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_5_DAY);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo5Day();  	

}

void CBrowserVw::OnChartYahoo10Day() 
{
  m_iRange = CSMView::YAHOO_10_DAY;
	m_pOwner->m_iRange = CSMView::YAHOO_10_DAY;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_10_DAY);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo5Day();  	

}

void CBrowserVw::OnChartYahoo3Month() 
{
  m_iRange = CSMView::YAHOO_3_MONTH;
	m_pOwner->m_iRange = CSMView::YAHOO_3_MONTH;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_3_MONTH);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo3Month();  	
	
}

void CBrowserVw::OnChartYahoo6Month() 
{
  m_iRange = CSMView::YAHOO_6_MONTH;
	m_pOwner->m_iRange = CSMView::YAHOO_6_MONTH;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_6_MONTH);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo6Month();  	
	
}

void CBrowserVw::OnChartYahoo1Year() 
{
  m_iRange = CSMView::YAHOO_1_YEAR;
	m_pOwner->m_iRange = CSMView::YAHOO_1_YEAR;
	//m_pOwner->m_cChartType = "c";
	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_1_YEAR);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo1Year();  	
	
}

void CBrowserVw::OnChartYahoo2Year() 
{
  m_iRange = CSMView::YAHOO_2_YEAR;
	m_pOwner->m_iRange = CSMView::YAHOO_2_YEAR;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_2_YEAR);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo2Year();  	
	
}

void CBrowserVw::OnChartYahoo5Year() 
{
  m_iRange = CSMView::YAHOO_5_YEAR;
	m_pOwner->m_iRange = CSMView::YAHOO_5_YEAR;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_5_YEAR);
        return;
      }
	  }
  }

	//m_pOwner->OnChartYahoo5Year();  	
	
}

void CBrowserVw::OnChartYahooMax() 
{
  m_iRange = CSMView::YAHOO_MAX;
	m_pOwner->m_iRange = CSMView::YAHOO_MAX;
	//m_pOwner->m_cChartType = "c";

	CString URL;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL) {
        ((CSMView *)(THEAPP()->m_pOldView))->SubmitChartReq_Yahoo(p, CSMView::YAHOO_MAX);
        return;
      }
	  }
  }

//	m_pOwner->OnChartYahooMax();  	

}


void CBrowserVw::OnViewViewvaluations() 
{
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(0);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(1);

	THEAPP()->SwitchView((CView *)(m_pOwner->m_pValVw));	  
}

void CBrowserVw::OnViewRGB() 
{
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(0);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(1);

	THEAPP()->SwitchView((CView *)(m_pOwner->m_pRGBVw));	  
}
void CBrowserVw::OnBrowserStop() 
{
  Stop();	
}

void CBrowserVw::OnBrowserBack() 
{
  GoBack();
	
}

void CBrowserVw::OnBrowserForward() 
{
  GoForward();
}

void CBrowserVw::OnBrowserRefresh() 
{
  Refresh();
}

void CBrowserVw::OnFavorite(UINT nID)
{
  Navigate2(((CMainFrame *)THEAPP()->m_pMainWnd)->m_astrFavoriteURLs[nID-0xe00], 0, NULL);
}

/*

void CBrowserVw::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CHtmlView::OnShowWindow(bShow, nStatus);
  if(bShow) {
    ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
    ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
  }
	
}
*/
void CBrowserVw::OnPortfolioGetnews() 
{
  THEAPP()->CheckSerNo(TRUE);

	CString strTicker;

	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), strTicker);
  CSMDoc *pDoc = (CSMDoc *)GetDocument();

  CWWWYahoo *pWWW = new CWWWYahoo(m_pOwner);
  if ( !pWWW )
    return;
  else {
    if (!strTicker.IsEmpty() ) {
        pWWW->GetNews(strTicker);
    }
    else {
      pWWW->GetNews();
    }
  }
}

void CBrowserVw::OnViewOptions() 
{
  if (m_pOwner)
    m_pOwner->OnViewOptions();	
}

void CBrowserVw::OnPortfolioDeleteticker() 
{
	CSMView *pView = (CSMView *)(THEAPP()->m_pOldView);
	CListCtrl& ListCtrl=pView->GetListCtrl();
	CString URL;
	int iCurSel;
	iCurSel = ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel();
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.DeleteItem(iCurSel);
((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.SetCurSel(iCurSel-1);
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.Invalidate();

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetDocument();
  if (pDoc) {
		CSingleLock sLock(&pDoc->m_mutex);

		// get item data
		WCHAR szBuff[MAX_PATH];
		LV_ITEM lvi;
		lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
		lvi.iSubItem=0;
		lvi.pszText=szBuff;
		lvi.cchTextMax=sizeof(szBuff);
		lvi.lParam=NULL;
		lvi.stateMask=0xFFFF;		// get all state flags

		int iCount= ListCtrl.GetItemCount();

		for(	int i=0; i<iCount; i++ ) {
			lvi.iItem = i;
			if(ListCtrl.GetItem(&lvi)) {
				CStkTicker *p = (CStkTicker *) lvi.lParam;
				if ( p && p->m_strSymbol == URL) {
					ListCtrl.DeleteItem(i);

					sLock.Lock();
					for ( int k=0; i<pDoc->m_TickerArray.GetSize(); k++) {
						CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[k];
						if ( pTick && pTick->m_strSymbol == URL) {
							pDoc->SetModifiedFlag(TRUE);
							pDoc->m_TickerArray.RemoveAt(k);
							delete p;
							pDoc->SetModifiedFlag(TRUE);
							break;
						}
					}
					sLock.Unlock();

					continue;
				}
			}
		}

		pView->Invalidate();
	}
}

void CBrowserVw::OnPortfolioAddticker() 
{
	CString URL;
	CString strEmpty;
	int iCurSel;
	iCurSel = ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel();
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetLBText(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.GetCurSel(), URL);
	URL.TrimLeft();
	URL.TrimRight();
	URL.MakeUpper();

	if (!m_pOwner->FindInArray(URL) ) {
		CStkTicker *p = new CStkTicker;
		p->m_strSymbol = URL;

		CSMDoc *pDoc = (CSMDoc *)GetDocument();
		if (pDoc) {
			CSingleLock sLock(&pDoc->m_mutex);
			sLock.Lock();
			pDoc->m_TickerArray.Add(p);
			sLock.Unlock();
			m_pOwner->OnPopulateList(NULL,NULL);
			m_pOwner->OnViewRefresh();
		}
	}

}

void CBrowserVw::GenReq()
{
  switch(m_iRange) {
    case CSMView::YAHOO_1_DAY:
			OnChartYahooOneDay();
      break;

    case CSMView::YAHOO_5_DAY:
			OnChartYahoo5Day();
      break;

    case CSMView::YAHOO_3_MONTH:
			OnChartYahoo3Month();
      break;

    case CSMView::YAHOO_6_MONTH:
			OnChartYahoo6Month();
      break;
    case CSMView::YAHOO_1_YEAR:
			OnChartYahoo1Year();
      break;

    case CSMView::YAHOO_2_YEAR:
			OnChartYahoo2Year();
      break;

    case CSMView::YAHOO_5_YEAR:
			OnChartYahoo5Year();
      break;

    case CSMView::YAHOO_MAX:
			OnChartYahooMax();
      break;

    default:
      return;
  }
}

void CBrowserVw::OnChartTypeLine() 
{
	m_cChartType = "l";
	m_pOwner->m_cChartType  = "l";
	GenReq();
}


void CBrowserVw::OnChartTypeBar() 
{
	m_cChartType = "b";
	m_pOwner->m_cChartType = "b";
	GenReq();
}


void CBrowserVw::OnChartTypeCandle() 
{
	m_cChartType = "c";
	m_pOwner->m_cChartType = "c";
	GenReq();
}

void CBrowserVw::OnSiteYahoo()
{
	CSMDoc *pDoc = (CSMDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bWebSite = CSMDoc::YAHOO;
}

void CBrowserVw::OnSiteTd()
{
	CSMDoc *pDoc = (CSMDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bWebSite = CSMDoc::TD;
}
