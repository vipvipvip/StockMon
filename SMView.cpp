// SMView.cpp : implementation of the CSMView class

#include "stdafx.h"
#include <afxole.h>
#include "MainFrm.h"
#include "StockMon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "IAccess.h"
#include "Thread.h"
#include "request.h"
#include "SMDoc.h"


#include "ListVwEx.h"	// base class for CSMView
#include "ui.h"
#include "readmsg.h"
#include "UMapi.h"
#include "MMSYSTEM.H"
#include "MktSumVw.h"
#include "ScreenVw.h"
#include "FundaVw.h"
#include "BrowserVw.h"
#include "Valuation.h"
#include "RGBView.h"
#include <AFXPRIV.H>
#include "WWW.h"
#include "Datafile.h"
#include "SMView.h"

#include <Shlwapi.h>

#ifdef _DORAS_
#include <ras.h>
#include <rassapi.h>
#include <rasdlg.h>
#include <raserror.h>
#include ".\smview.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSMView

IMPLEMENT_DYNCREATE(CSMView, CListViewEx)

BEGIN_MESSAGE_MAP(CSMView, CListViewEx)
	//{{AFX_MSG_MAP(CSMView)
	ON_COMMAND(ID_VIEW_SMALLICONS, OnViewSmallIcons)
	ON_COMMAND(ID_VIEW_LARGEICONS, OnViewLargeIcons)
	ON_COMMAND(ID_VIEW_LIST, OnViewList)
	ON_COMMAND(ID_VIEW_ROWDETAILS, OnViewFullRowDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLICONS, OnUpdateViewSmallIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGEICONS, OnUpdateViewLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ROWDETAILS, OnUpdateViewFullRowDetails)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_VIEW_CLIENTWIDTHSEL, OnViewClientwidthsel)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLIENTWIDTHSEL, OnUpdateViewClientwidthsel)
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PORTFOLIO_DELETETICKER, OnPortfolioDeleteticker)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_DELETETICKER, OnUpdatePortfolioDeleteticker)
	ON_COMMAND(ID_PORTFOLIO_ADDTICKER, OnPortfolioAddticker)
	ON_COMMAND(ID_PORTFOLIO_UPDATESELECTED, OnPortfolioUpdateselected)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_UPDATESELECTED, OnUpdatePortfolioUpdateselected)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_SUMMARY_NASDAQ, OnSummaryNasdaq)
	ON_COMMAND(ID_SUMMARY_NYSE, OnSummaryNyse)
	ON_COMMAND(ID_SUMMARY_AMEX, OnSummaryAmex)
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_AMEX, OnUpdateSummaryAmex)
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_NASDAQ, OnUpdateSummaryNasdaq)
	ON_UPDATE_COMMAND_UI(ID_SUMMARY_NYSE, OnUpdateSummaryNyse)
	ON_COMMAND(ID_VIEW_MKT_SUMMARY, OnViewMktSummary)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MKT_SUMMARY, OnUpdateViewMktSummary)
	ON_COMMAND(ID_PORTFOLIO_ADDFUND, OnPortfolioAddfund)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESH, OnUpdateViewRefresh)
	ON_COMMAND(ID_HELP_HOWTOREGISTER, OnHelpHowtoregister)
	ON_COMMAND(ID_PORTFOLIO_TRADE, OnPortfolioTrade)
	ON_COMMAND(ID_PORTFOLIO_SCREEN, OnPortfolioScreen)
	ON_COMMAND(ID_VIEW_VIEWSCREENING, OnViewscreening)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWSCREENING, OnUpdateViewscreening)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_PORTFOLIO_GETCOMPANYFUNDAMENTALS, OnPortfolioGetcompanyfundamentals)
	ON_COMMAND(ID_VIEW_VIEWFUNDAMENTALS, OnViewfundamentals)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWFUNDAMENTALS, OnUpdateViewfundamentals)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_GETCOMPANYFUNDAMENTALS, OnUpdatePortfolioGetcompanyfundamentals)
	ON_COMMAND(ID_PORTFOLIO_VALUATION, OnPortfolioValuation)
	ON_COMMAND(ID_VIEW_VIEWVALUATIONS, OnViewViewvaluations)
	ON_COMMAND(ID__VALUATION, OnValuation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWVALUATIONS, OnUpdateViewViewvaluations)
	ON_COMMAND(ID_VIEW_VIEWBROWSER, OnViewViewbrowser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWBROWSER, OnUpdateViewViewbrowser)
	ON_COMMAND(ID_PORTFOLIO_GETNEWS, OnPortfolioGetnews)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_GETNEWS, OnUpdatePortfolioGetnews)
	ON_COMMAND(ID_PORTFOLIO_SORT_ALERT_CLOSESTTOLOWPRICE, OnPortfolioSortAlertClosesttolowprice)
	ON_COMMAND(ID_PORTFOLIO_SORT_ALERT_CLOSESTTOHIGHPRICE, OnPortfolioSortAlertClosesttohighprice)
	ON_COMMAND(ID_VIEW_REFRESHVALUATION, OnViewRefreshvaluation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESHVALUATION, OnUpdateViewRefreshvaluation)
	ON_COMMAND(ID_PORTFOLIO_DELOVERVALUED, OnPortfolioDelovervalued)
	ON_UPDATE_COMMAND_UI(ID_PORTFOLIO_DELOVERVALUED, OnUpdatePortfolioDelovervalued)
	ON_COMMAND(ID_CHART_YAHOO_ONE_DAY, OnChartYahooOneDay)
	ON_COMMAND(ID_CHART_YAHOO_5_DAY, OnChartYahoo5Day)
	ON_COMMAND(ID_CHART_YAHOO_10_DAY, OnChartYahoo10Day)
	ON_COMMAND(ID_CHART_YAHOO_3_MONTH, OnChartYahoo3Month)
	ON_COMMAND(ID_CHART_YAHOO_6_MONTH, OnChartYahoo6Month)
	ON_COMMAND(ID_CHART_YAHOO_1_YEAR, OnChartYahoo1Year)
	ON_COMMAND(ID_CHART_YAHOO_2_YEAR, OnChartYahoo2Year)
	ON_COMMAND(ID_CHART_YAHOO_5_YEAR, OnChartYahoo5Year)
	ON_COMMAND(ID_CHART_YAHOO_MAX, OnChartYahooMax)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_SUMMARY_YAHOONYSE_PRICEGAINERS, OnSummaryYahoonysePricegainers)
	ON_COMMAND(ID_SUMMARY_YAHOONYSE_VOLUMELEADERS, OnSummaryYahoonyseVolumeleaders)
	ON_COMMAND(ID_SUMMARY_YAHOONASDAQ_VOLUMELEADERS, OnSummaryYahoonasdaqVolumeleaders)
	ON_COMMAND(ID_SUMMARY_YAHOONASDAQ_PRICEGAINERS, OnSummaryYahoonasdaqPricegainers)
	ON_COMMAND(ID_SUMMARY_YAHOOAMEX_PRICEGAINERS, OnSummaryYahooamexPricegainers)
	ON_COMMAND(ID_SUMMARY_YAHOOAMEX_VOLUMELEADERS, OnSummaryYahooamexVolumeleaders)
	ON_COMMAND(ID_SUMMARY_YAHOOALLVOLUMEGAINERS, OnSummaryYahooallvolumegainers)
	ON_COMMAND(ID_SUMMARY_YAHOOALLPRICEGAINERS, OnSummaryYahooallpricegainers)
	ON_COMMAND(ID_SUMMARY_YAHOOALL, OnSummaryYahooall)
	ON_COMMAND(ID_SUMMARY_INDIAALLVOLUMEGAINERS, OnSummaryIndiaallvolumegainers)
	ON_COMMAND(ID_SUMMARY_INDIAALLPRICEGAINERS, OnSummaryIndiaallpricegainers)
	ON_COMMAND(ID_SUMMARY_WSJALL, OnSummaryWsjall)
	ON_COMMAND(ID_SUMMARY_WSJSUMMARY, OnSummaryWsjsummary)
	ON_COMMAND(ID_CHART_TYPE_LINE, OnChartTypeLine)
	ON_UPDATE_COMMAND_UI(ID_CHART_TYPE_LINE, OnUpdateChartTypeLine)
	ON_COMMAND(ID_CHART_TYPE_BAR, OnChartTypeBar)
	ON_UPDATE_COMMAND_UI(ID_CHART_TYPE_BAR, OnUpdateChartTypeBar)
	ON_COMMAND(ID_CHART_TYPE_CANDLE, OnChartTypeCandle)
	ON_UPDATE_COMMAND_UI(ID_CHART_TYPE_CANDLE, OnUpdateChartTypeCandle)
	//}}AFX_MSG_MAP
	ON_MESSAGE (POPULATE_LIST, OnPopulateList)
	ON_MESSAGE (READ_COMPLETED, OnReadCompleted)
	ON_COMMAND_RANGE(ID_PORTFOLIO_ADDINDEXTICKERS_NASDAQCOMPOSITE, ID_PORTFOLIO_ADDINDEXTICKERS_REMOVEALLOFTHEABOVE, AddStdTickers)
	ON_COMMAND(ID_PORTFOLIO_INITTRADES, OnPortfolioInittrades)
	ON_COMMAND(ID_PORTFOLIO_DELETEALLTRADES, OnPortfolioDeletealltrades)
	ON_COMMAND(ID_PORTFOLIO_EXPORT, OnPortfolioExport)
	ON_COMMAND(ID_FILE_IMPORT_ISM, OnFileImportISM)
	ON_COMMAND(ID_VIEW_VIEWRBG, OnViewRGB)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWRBG, OnUpdateViewViewrbg)
	ON_COMMAND(ID_PORTFOLIO_RGB, OnPortfolioRgb)
	ON_COMMAND(ID_PORTFOLIO_NOTES, OnPortfolioNotes)
	ON_COMMAND(ID_VIEW_REFRESHRGB, OnViewRefreshrgb)
	ON_COMMAND(ID_SITE_YAHOO, CSMView::OnSiteYahoo)
	ON_COMMAND(ID_SITE_TD, CSMView::OnSiteTd)
	ON_COMMAND(ID_PORTFOLIO_GETTOPHOLDINGS, &CSMView::OnPortfolioGettopholdings)
	ON_COMMAND(ID_COMPAREWITH_SP500, &CSMView::OnComparewithSp500)
	ON_COMMAND(ID_COMPAREWITH_NASDAQ, &CSMView::OnComparewithNasdaq)
	ON_COMMAND(ID_COMPAREWITH_DOW, &CSMView::OnComparewithDow)
	ON_COMMAND(ID_COMPAREWITH_CLEAR, &CSMView::OnComparewithClear)
	ON_COMMAND(ID_FILE_IMPORT_TICKERS, &CSMView::OnFileImportTickers)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMView construction/destruction

CSMView::CSMView()
{
	m_bStateIcons		=	TRUE;
	m_nCheckedItem	=	-1;
	m_QuotesReq     = NULL;
	m_pPS = NULL;
	m_hWorkEvent		= NULL;
	m_TotThreads		= 0;
	m_pMktSum				= NULL;
  m_pScreenVw     = NULL;
  m_pFundaVw      = NULL;
  m_pBrowserVw    = NULL;
  m_pValVw        = NULL;
	m_pRGBVw				= NULL;

	m_bSummaryInProgress = FALSE;
	m_bAddingFund		= 0;
	m_nTimerID			= 0;
  m_nNextUpdateTimerID = 0;

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

  m_WrkThreadArray.SetSize(0);

	m_iRange = YAHOO_6_MONTH;
	m_cChartType = "c";
}

CSMView::~CSMView()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_bmLarge.DeleteObject();
	m_bmSmall.DeleteObject();
  if(pDoc->m_bHangup ) {
		DoHangup();
	}
  Sleep(30);
}

BOOL CSMView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|= LVS_SHOWSELALWAYS | LVS_REPORT | LVS_EDITLABELS;

	return CListViewEx::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSMView initialization

int ReadFile(CString& rFileName,CString& rString)
{
	rString.Empty();

	CFile f;
	int bOpen = f.Open(rFileName, CFile::modeRead);
	WCHAR szT[MAX_PATH];
	memset(szT, 0, sizeof(szT));
  int nBytes=0;
	if ( bOpen ) {
		while ( (nBytes = f.Read(szT, MAX_PATH-1)) != 0) {
      szT[nBytes] = 0;
			rString += szT;
		}
    f.Close();
	}
  rString += '\0';
	return rString.GetLength();
}

void CSMView::OnInitialUpdate()
{
	CListViewEx::OnInitialUpdate();
	CListCtrl& ListCtrl=GetListCtrl();

// set image lists

	// Associate the image lists with the list view control.
	ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);
	ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);

	m_strColWidths = THEAPP()->GetProfileString(FRM_SUBKEY_HEADING, FRM_LHV_COLWIDTH );
	DisplayColumnHeadings(IDS_SMVIEW);

	OnPopulateList(0, 0L);

	// initialize the threads and let them start running!
	StartWorkerThread();

	StartTimers();
  if (m_pMktSum) {
    m_pMktSum->EraseList(TRUE,FALSE);
  }

  if (m_pScreenVw) {
    m_pScreenVw->EraseList(TRUE,FALSE);
  }

	CString cmd;
	cmd = THEAPP()->m_lpCmdLine;
	CString resToken;
	int curPos=0;
	if ( !cmd.IsEmpty() ) {
		resToken = cmd.Tokenize(_T("/"), curPos);
		while (resToken != _T("")) {
		if (resToken == 'Q') 
			GetAllQuotes();
		if (resToken == 'V') 
			OnViewRefreshvaluation();
		if (resToken == 'R') 
			OnViewRefreshrgb();

		resToken = cmd.Tokenize(_T("/"), curPos);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// CSMView diagnostics

#ifdef _DEBUG
void CSMView::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CSMView::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}

CSMDoc* CSMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSMDoc)));
	return (CSMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSMView helpers

BOOL CSMView::SetViewType(DWORD dwViewType)
{
	return(ModifyStyle(LVS_TYPEMASK,dwViewType & LVS_TYPEMASK));
}

DWORD CSMView::GetViewType()
{
	return(GetStyle() & LVS_TYPEMASK);
}


/////////////////////////////////////////////////////////////////////////////
// CSMView message handlers

void CSMView::OnViewSmallIcons() 
{
	if(GetViewType()!=LVS_SMALLICON)
		SetViewType(LVS_SMALLICON);
}

void CSMView::OnViewLargeIcons() 
{
	if(GetViewType()!=LVS_ICON)
		SetViewType(LVS_ICON);
}

void CSMView::OnViewList() 
{
	if(GetViewType()!=LVS_LIST)
		SetViewType(LVS_LIST);
}


void CSMView::OnViewFullRowDetails() 
{
	if((GetViewType()!=LVS_REPORT) || !GetFullRowSel())
	{
		SetFullRowSel(TRUE);
		if(GetViewType()!=LVS_REPORT)
			SetViewType(LVS_REPORT);
	}
}

void CSMView::OnViewClientwidthsel() 
{
	m_bClientWidthSel=!m_bClientWidthSel;
	Invalidate();
	UpdateWindow();
}

void CSMView::OnUpdateViewSmallIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetViewType()==LVS_SMALLICON);
}

void CSMView::OnUpdateViewLargeIcons(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetViewType()==LVS_ICON);
}

void CSMView::OnUpdateViewList(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetViewType()==LVS_LIST);
}

void CSMView::OnUpdateViewFullRowDetails(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((GetViewType()==LVS_REPORT) && GetFullRowSel());
}

void CSMView::OnUpdateViewClientwidthsel(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bClientWidthSel);
	pCmdUI->Enable((GetViewType()==LVS_REPORT) && GetFullRowSel());
}

void CSMView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags=0;
	int nHitItem=GetListCtrl().HitTest(point,&uFlags);
	if ( -1 == nHitItem ) 
		return;

	// we need additional checking in owner-draw mode
	// because we only get LVHT_ONITEM
	BOOL bHit=FALSE;
	if(uFlags==LVHT_ONITEM && (GetStyle() & LVS_OWNERDRAWFIXED))
	{
		CRect rect;
		GetListCtrl().GetItemRect(nHitItem,rect,LVIR_ICON);

		// check if hit was on a state icon
		if(m_bStateIcons && point.x<rect.left)
			bHit=TRUE;
	}
	else if(uFlags & LVHT_ONITEMSTATEICON)
		bHit=TRUE;

	CListViewEx::OnLButtonDown(nFlags, point);
}

void CSMView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl& ListCtrl=GetListCtrl();	
	int nItems = ListCtrl.GetItemCount();

	if ( nChar == 45  ) {
		// Insert Key pressed
		int iIndex = ListCtrl.InsertItem(nItems+1,_T("New")); 
		ListCtrl.EditLabel(iIndex);
	}

	if(ListCtrl.GetSelectedCount())
	{
		if ( nChar == 46  ) {
			// Delete Key pressed
			OnPortfolioDeleteticker();
		}
	}

	CListViewEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSMView::FillAddressBar()
{
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.ResetContent();

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
			if ( p ) {
	      COMBOBOXEXITEM item;
	      item.mask = CBEIF_TEXT;
	      item.iItem = -1;
	      item.pszText = (LPTSTR)(LPCTSTR)p->m_strSymbol;
    	  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.InsertItem(&item);
			}
		}
	}
	((CMainFrame *)THEAPP()->m_pMainWnd)->Invalidate();
}


afx_msg LRESULT  CSMView::OnPopulateList(WPARAM wParam, LPARAM lParam)
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSingleLock sLock(&pDoc->m_mutex);

	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.DeleteAllItems();
	((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.ResetContent();
	// insert items

	sLock.Lock();

	int nCount = pDoc->m_TickerArray.GetUpperBound();
	for(int i=0; i<=nCount; i++)
	{
		CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
		UpdateRow(p, i);
	}
	sLock.Unlock();
	return 0;
}

afx_msg LRESULT  CSMView::OnReadCompleted(WPARAM wParam, LPARAM lParam)
{
  THEAPP()->CheckSerNo(TRUE);

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->SetModifiedFlag(TRUE);

	if(m_QuotesReq) 
		--m_QuotesReq;

	if ( m_QuotesReq == 0)  {
		m_bSummaryInProgress=FALSE;
		Invalidate();
		UpdateWindow();
		OnTimer(m_nNextUpdateTimerID);

		// Hangup the phone if we are done for now
		if ( pDoc->m_bHangup)
			DoHangup();
	}

	int iPos;

	CReadMsg *pMsg = (CReadMsg *)lParam;
	if ( !pMsg ) {
		return -1;
	}

	CString strTicker((LPCTSTR)wParam);

	CString strWebPageContent(pMsg->m_strWebPageContent);
	CString strTopHoldings(pMsg->m_strWebPageContent);
	//THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
	CInternetThread *pThread = (CInternetThread *)pMsg->m_pThread;
	if(pThread)
		pThread->FreeWebPageContent();

	if( strTicker.IsEmpty() || strWebPageContent.IsEmpty() ){
		return -1;
	}

	if ( -1 != strTicker.Find(_T("SCREEN"))) {
    if(CreateScreenWindow()) {
      m_pScreenVw->SendMessage(SHOW_SCREEN_STKS, (WPARAM)0, (LPARAM)(LPCTSTR)strWebPageContent);
    }
		return 0;
	}

	// Volume Percentage Leaders from WSJ
	iPos = strWebPageContent.Find(_T("Volume Percentage Leaders"));
	if ( -1 != iPos ) {
		THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
		iPos = strWebPageContent.Find(_T("Volume Percentage Leaders"));
		CString st(strWebPageContent.Mid(iPos));
		InsertWSJSummaryValues(st);
		return 0;
	}

	// Mkt Summary from Yahoo
	iPos = strWebPageContent.Find(_T("All headlines for"));
	if ( -1 != iPos && ( strTicker == _T("o") || strTicker == _T("nq") || strTicker == _T("aq")) ) {
		THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
		iPos = strWebPageContent.Find(_T("All headlines for"));
		int iPos2 = strWebPageContent.Find(_T("Copyright"));
		CString st(strWebPageContent.Mid(iPos+18, iPos2-iPos-18));
		InsertSummaryValues(st);
		return 0;
	}

	// Mkt Summary from Yahoo India
	iPos = strWebPageContent.Find(_T("All headlines for:"));
	if ( -1 != iPos && ( strTicker == _T("bo")) ) {
		THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
		iPos = strWebPageContent.Find(_T("All headlines for:"));
		int iPos2 = strWebPageContent.Find(_T("Copyright"));
		CString st(strWebPageContent.Mid(iPos+18, iPos2-iPos-18));
		InsertSummaryValues(st);
		return 0;
	}

/*
if ( -1 != strWebPageContent.Find((LPCTSTR)"Market Summary") ) {
		if(CreateSummaryWindow()) {
			THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
			m_pMktSum->SendMessage(SHOW_MKT_SUMMARY, (WPARAM)0, (LPARAM)(LPCTSTR)strWebPageContent);
			m_bSummaryInProgress=FALSE;
		}
		return 0;
	}
*/
	if ( -1 != (iPos = strTicker.Find(_T("1A")))) {
		iPos = strTicker.ReverseFind(':');
    if ( iPos != -1 && CreateFundaWindow() ) {
		  strTicker = strTicker.Mid(iPos+1);
      THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
      m_pFundaVw->SendMessage(SHOW_FUNDA, (WPARAM)(LPCTSTR)strTicker, (LPARAM)(LPCTSTR)strWebPageContent);
    }
    return 0;
  }

	if ( -1 != (iPos = strTicker.Find(_T("VALUE")))) {
		iPos = strTicker.ReverseFind(':');
    if ( iPos != -1 ) {
      strTicker = strTicker.Mid(iPos+1);
      CStkTicker *p = InListCtrl(strTicker);
      if (p && CreateValuationWindow() ) {
        THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
        m_pValVw->SendMessage(SHOW_VALUATION, (WPARAM)(LPCTSTR)p->m_strSymbol, (LPARAM)(LPCTSTR)strWebPageContent);
      }
    }
    return 0;
  }

	iPos = strTopHoldings.Find(_T("Top 10 Holdings"));
	if ( -1 != iPos) {
		CString st(strTopHoldings.Mid(iPos,strTopHoldings.GetLength()));
		InsertTopHoldings(st);
    return 0;
  }


	if ( -1 != (iPos = strTicker.Find(_T("RGB")))) {
		iPos = strTicker.ReverseFind(':');
    if ( iPos != -1 ) {
      strTicker = strTicker.Mid(iPos+1);
      CStkTicker *p = InListCtrl(strTicker);
      if (p && CreateRGBWindow() ) {
        THEAPP()->StripTags((LPTSTR)(LPCTSTR)strWebPageContent);
        m_pRGBVw->SendMessage(SHOW_RGBVIEW, (WPARAM)(LPCTSTR)p->m_strSymbol, (LPARAM)(LPCTSTR)strWebPageContent);
      }
    }
    return 0;
  }
	

  // Handle Quote
  CWWW *pWWW = (CWWW *)pMsg->m_pWWW;
  if(pWWW && pWWW->IsKindOf( RUNTIME_CLASS( CWWWYahoo))) {
		THEAPP()->StripTags(strWebPageContent.GetBuffer());
    ((CWWWYahoo *)pWWW)->HandleQuote(strTicker, strWebPageContent);
    if(m_pValVw) {
      m_pValVw->SendMessage(REFRESH_VALUATION, 0, 0);
    }
    pWWW->Release();
    return 0;
  }  
  
  // must be some error
  iPos = strWebPageContent.Find(_T("Error"));
  if ( iPos != -1 ) {
    AfxMessageBox(strWebPageContent.Mid(iPos));
  }

	return 0;
}

CStkTicker *CSMView::FindInArray(CString& s) 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSingleLock sLock(&pDoc->m_mutex);
	int iNumTickers = pDoc->m_TickerArray.GetSize();
	if (iNumTickers <=0 ) return NULL;
  int i=0;
	CStkTicker *p=NULL;
	sLock.Lock();
	while ( i < iNumTickers ) {
    p = (CStkTicker *)pDoc->m_TickerArray[i];
    if ( p->m_strSymbol == s ) {
			sLock.Unlock();
      return p;
    }
    i++;
  }
	sLock.Unlock();
	return NULL;
}

void CSMView::InsertSummaryValues(CString& st)
{
	st.Replace((WCHAR)" ", (WCHAR)"");
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	int iStart,iPos;
	iStart=0;
	iPos = st.Find((LPCTSTR)",",iStart);

	
	while ( iPos != -1 ) {
		CString s;
		s = st.Mid(iStart,iPos-iStart);
		s.TrimLeft();
		s.TrimRight();
		if ( !FindInArray(s) ) {
			CStkTicker *p = new CStkTicker();
			p->m_strSymbol = s;
			sLock.Lock();
			pDoc->m_TickerArray.Add(p);
			sLock.Unlock();
		}
		iStart=iPos+1;
		iPos = st.Find((LPCTSTR)",",iStart);
	}
	OnPopulateList(0,0);
}

void CSMView::InsertWSJSummaryValues(CString& st)
{
	st.Replace(_T(" "), _T(""));
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	int iStart,iPos;
	iStart=0;
	iPos = st.Find(_T("("),iStart);
	
	while ( iPos != -1 ) {
		CString s;
		iPos++;
		while ( st.Mid(iPos,1) != ')' ) {
			s += st.Mid(iPos,1);
			iPos++;
		}
		s.TrimLeft();
		s.TrimRight();
		if ( !FindInArray(s) ) {
			CStkTicker *p = new CStkTicker();
			p->m_strSymbol = s;
			sLock.Lock();

			pDoc->m_TickerArray.Add(p);
			sLock.Unlock();
		}
		iStart=iPos+1;
		iPos = st.Find(_T("("),iStart);
	}
	OnPopulateList(0,0);

}

void CSMView::OnDestroy() 
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
	lvc.cchTextMax = sizeof(szT) - sizeof(WCHAR);
	while ( ListCtrl.GetColumn(i++, &lvc) ) {
		strTemp.Format(_T("%d "), lvc.cx);
		strValue += strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( FRM_SUBKEY_HEADING, FRM_LHV_COLWIDTH, strValue );
	}
	StopTimer(m_nTimerID);
	StopTimer(m_nNextUpdateTimerID);

	StopWorkerThread();
	CListViewEx::OnDestroy();
}

void CSMView::StopTimer(UINT& nID)
{
	if(nID) {
		KillTimer(nID);
		nID = 0;
	}
}

void CSMView::StartTimers()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if ( pDoc->m_bAutoUpdates && !pDoc->m_strOpenTime.IsEmpty()) {
		m_nTimerID = SetTimer(1, pDoc->m_nInterval, NULL);
		m_nNextUpdateTimerID  = SetTimer(2, 1000, NULL);
		m_time = CTime::GetCurrentTime();
	}
}


void CSMView::OnTimer(UINT nIDEvent) 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	int iNumTickers = pDoc->m_TickerArray.GetSize();
	int iWrkQue = pDoc->m_ReqArray.GetSize();

	// Wake up the thread only if there is work to be done
	if ( nIDEvent == m_nTimerID && iNumTickers && IsUpdateWindow() )		
	{
    // Update chart
    if (m_pBrowserVw) {
      CString sURL = m_pBrowserVw->GetLocationURL();
      //if ( -1 != sURL.Find((LPCTSTR)"time=5m") ) {
        m_pBrowserVw->Refresh();
      //}
    }

		GetAllQuotes();

	}
  else if( nIDEvent == m_nNextUpdateTimerID && !m_QuotesReq) {
		long  secsLeft;

		if( !IsUpdateWindow() ) {
			CString str;
			if ( pDoc->m_bAutoUpdates ) {
				if ( !pDoc->m_strOpenTime.IsEmpty() )
					str.Format(_T("Updates will resume at %s"), pDoc->m_strOpenTime);
				else 
					str = _T("Not in Update Time Window. Updates will resume later.");
			}
			else {
				str = _T("Updates are off.");
			}

			THEAPP()->ShowMsgText(str);
		}
		else {
			WCHAR tmpbuf[9];
			_wstrtime( tmpbuf );
			if ( iNumTickers ) {
				secsLeft = GetSecsToNextUpdate();
				int iHrs = secsLeft/(60*60);
				int iMinutes = (secsLeft-(iHrs*3600))/60;
				int isecs = secsLeft - (iHrs*3600+iMinutes*60);

				CString str;
				str.Format(_T("Next Update in %dh::%dm::%ds\t\t[%s] "), iHrs, iMinutes, isecs, tmpbuf);
				THEAPP()->ShowMsgText(str);
			}
			else {
				CString str;
				str.Format(_T("                            \t\t[%s] "), tmpbuf);
				THEAPP()->ShowMsgText(str);
			}
		}

		if ( pDoc->m_AlertType != 0 )
			DoAlert();
  }
}

long CSMView::GetSecsToNextUpdate() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int Hr=0, Min=0;
	CTime t = CTime::GetCurrentTime();
	if ( m_time < t ) {
		CTimeSpan ts = t - m_time;
		return (pDoc->m_nInterval)/1000 - ts.GetTotalSeconds();
	}
	else {
		int iMin = pDoc->m_strOpenTime.Find(':');
		if ( iMin != -1 ) {
			Hr = _wtoi((LPCTSTR)pDoc->m_strOpenTime.Mid(0,iMin));
			Min = _wtoi((LPCTSTR)pDoc->m_strOpenTime.Mid(iMin+1));
		}
		CTime open(t.GetYear(), t.GetMonth(), t.GetDay(), Hr, Min, 0);
		CTimeSpan ts = t - open;
		return (pDoc->m_nInterval) - ts.GetTotalSeconds();
	}
}

void CSMView::SubmitReqForCoFunda(CStkTicker *pTicker)
{
  if ( pTicker->m_bMutualFund) {
	AfxMessageBox(_T("Cannot get fundamental data for Mutual Funds"));
	return;
  }


  CString strTicker;
  strTicker = _T("FUNDA:");
  strTicker += pTicker->m_strSymbol;

/*
  CString rWebPage;
  CString strFile;
  strFile = "c:\\funda.htm";
  ReadFile(strFile, rWebPage);
	CReadMsg msg;
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;
*/


  if (!pTicker)  return;
  if(pTicker->m_bStdTicker) return;


	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;

  strAddr = _T("http://");
/*
  strAddr += "ad.morningstar.net";
  if ( pTicker->m_bMutualFund) {
	strAddr += "/nd/ndNSAPI.nd/Research/ViewQTFunds.asp?ticker=";
  }
  else {
	strAddr += "/nd/ndNSAPI.nd/Research/ViewStCoPerf?ticker=";
  }
*/
//  strAddr += "www.wsrn.com";
//	strAddr += "/home/dataset/quicksource.html?symbol=";

  strAddr += _T("www.wsrn.com/apps/companyinfo/fund.xpl?s=");
  strAddr += pTicker->m_strSymbol;
  strAddr += _T("&f=FUND");

  strIden = _T("FUNDA:");
  strIden += pTicker->m_strSymbol;

  pReq = new CRequest;
	pReq->Init(strAddr, strIden);
  sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_QuotesReq++;

  long l;
  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
}

void CSMView::SubmitReqForValuation(CStkTicker *pTicker)
{
  if ( !pTicker ) return;

  if ( pTicker->m_bMutualFund) {
	AfxMessageBox((LPCTSTR)"Cannot get valuation data for Mutual Funds");
	return;
  }

  if(pTicker->m_bStdTicker) return;

  if ( pTicker->m_strLast.IsEmpty() ) {
    GetQuote(pTicker->m_strSymbol);
  }


/*

  CString strTicker;
  strTicker = "VALUE:";
  strTicker += pTicker->m_strSymbol;


  CString rWebPage;
  CString strFile;
  strFile = "c:\\x.htm";
  ReadFile(strFile, rWebPage);
	CReadMsg msg;
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;

  strFile = "c:\\EE.htm";
  ReadFile(strFile, rWebPage);
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;

*/

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr, strAddr2;
	CString strIden;
	CRequest *pReq=NULL;

  // http://quicktake.morningstar.com/Stocks/EarnEst/_CSCO.html#anearneanchor
  /*
	strAddr = "http://";
  strAddr += "quicktake.morningstar.com/";
	strAddr += "Stocknet/EarningsEstimates.aspx?CustId=&CLogin=&CType=&CName=&Symbol=";
  strAddr += pTicker->m_strSymbol;
*/
	strAddr = _T("http://");
	strAddr += _T("finance.yahoo.com/q/ae?s=");
	strAddr += pTicker->m_strSymbol;

  strIden = _T("VALUE_EE:");
  strIden += pTicker->m_strSymbol;

  pReq = new CRequest;
	pReq->Init(strAddr, strIden);
  sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_QuotesReq++;

  long l;
  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
}


void CSMView::SubmitReqForRGB(CStkTicker *pTicker)
{
  if ( !pTicker ) return;

  if ( pTicker->m_bMutualFund) {
	AfxMessageBox((LPCTSTR)"Cannot get RGB data for Mutual Funds");
	return;
  }

  if(pTicker->m_bStdTicker) return;

  if ( pTicker->m_strLast.IsEmpty() ) {
    GetQuote(pTicker->m_strSymbol);
  }


/*

  CString strTicker;
  strTicker = "VALUE:";
  strTicker += pTicker->m_strSymbol;


  CString rWebPage;
  CString strFile;
  strFile = "c:\\x.htm";
  ReadFile(strFile, rWebPage);
	CReadMsg msg;
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;

  strFile = "c:\\EE.htm";
  ReadFile(strFile, rWebPage);
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;

*/

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr, strAddr2;
	CString strIden;
	CRequest *pReq=NULL;

  strAddr = _T("http://");
  strAddr += _T("finance.yahoo.com/q/ks?s=");

  strAddr += pTicker->m_strSymbol;

  strIden = _T("RGB_EE:");
  strIden += pTicker->m_strSymbol;

  pReq = new CRequest;
	pReq->Init(strAddr, strIden);
  sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_QuotesReq++;

  long l;
  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);

	// Get CashFlow Stuff
	//http://finance.yahoo.com/q/cf?s=BNI
	strAddr = _T("http://");
  strAddr += _T("finance.yahoo.com/q/cf?s=");
  strAddr += pTicker->m_strSymbol;
	strAddr += _T("&annual"); 

//	strAddr = "http://moneycentral.msn.com/investor/invsub/results/pstatemnt.aspx?lstStatement=CashFlow&stmtView=Ann&symbol=";
//	strAddr += pTicker->m_strSymbol;

  strIden = _T("RGB_CF:");
  strIden += pTicker->m_strSymbol;
  pReq = new CRequest;
	pReq->Init(strAddr, strIden);
  sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_QuotesReq++;

  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
}

CString GetCode(CString& str)
{
  CString ret;
  int iPos = str.Find(_T("("));
  int iLen = str.GetLength();
  if ( iPos != -1 ) {
    iPos++;
    while ( iPos < iLen && str[iPos] != ')') {
      ret += str[iPos];
      iPos++;
    }
  }
  ret.TrimRight();
  ret.TrimLeft();
  return ret;
}

void CSMView::SubmitScreeningReq()
{
/*
  CString strTicker;
  strTicker = "SCREEN";
  CString rWebPage;
  CString strFile;
  strFile = "c:\\x.html";
  ReadFile(strFile, rWebPage);
	CReadMsg msg;
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;
*/

  CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;

  /*
    http://www2.wsrn.com/dataset/search.html?pe_l=&pe_h=30&yield_l=&yield_h=
    &salesratio_l=&salesratio_h=&bookratio_h=&bookratio_l=&
    close_l=10&close_h=&beta_l=&beta_h=&epsqtr_l=50&epsqtr_h=
    &fyear_l=&fyear_h=&payout_l=&payout_h=&dte_l=&dte_h=&roe_l=&roe_h=
    &sales_l=&sales_h=&mc_l=100&mc_h=&dj=&sp=&igroup=&exchange=
  */

	strAddr = "http://";
	strAddr += "www.wsrn.com";
	strAddr += "/apps/quicksearch/search.xpl?";

  // PE
	strAddr += "pe_l=";
  strAddr += pDoc->m_strPE_Min;
	strAddr += "&pe_h=";
  strAddr += pDoc->m_strPE_Max;

  // Yield
	strAddr += "&yield_l=";
  strAddr += pDoc->m_strYield_Min;
	strAddr += "&yield_h=";
  strAddr += pDoc->m_strYield_Max;

  // Price to Sales Ratio
	strAddr += "&salesratio_l=";
  strAddr += pDoc->m_strPSRatio_Min;
	strAddr += "&salesratio_h=";
  strAddr += pDoc->m_strPSRatio_Max;

  // Price to Book Ratio
	strAddr += "&bookratio_l=";
  strAddr += pDoc->m_strPBRatio_Min;
	strAddr += "&bookratio_h=";
  strAddr += pDoc->m_strPBRatio_Max;

  // Stock Price
	strAddr += "&close_l=";
  strAddr += pDoc->m_strPrice_Min;
	strAddr += "&close_h=";
  strAddr += pDoc->m_strPrice_Max;

  // Beta
	strAddr += "&beta_l=";
  strAddr += pDoc->m_strBeta_Min;
	strAddr += "&beta_h=";
  strAddr += pDoc->m_strBeta_Max;

  // Last Qtr Eps Change
	strAddr += "&epsqtr_l=";
  strAddr += pDoc->m_strEPSChg_Min;
	strAddr += "&epsqtr_h=";
  strAddr += pDoc->m_strEPSChg_Max;

  // 5 Year Growth Rate
	strAddr += "&fyear_l=";
  strAddr += pDoc->m_strGr_Min;
	strAddr += "&fyear_h=";
  strAddr += pDoc->m_strGr_Max;

  // Div Payout Ratio
	strAddr += "&payout_l=";
  strAddr += pDoc->m_strDPRatio_Min;
	strAddr += "&payout_h=";
  strAddr += pDoc->m_strDPRatio_Max;

  // Debt to Equity Ratio
	strAddr += "&dte_l=";
  strAddr += pDoc->m_strDERatio_Min;
	strAddr += "&dte_h=";
  strAddr += pDoc->m_strDERatio_Max;

  // ROE
	strAddr += "&roe_l=";
  strAddr += pDoc->m_strROE_Min;
	strAddr += "&roe_h=";
  strAddr += pDoc->m_strROE_Max;

  // Sales
	strAddr += "&sales_l=";
  strAddr += pDoc->m_strSales_Min;
	strAddr += "&sales_h=";
  strAddr += pDoc->m_strSales_Max;

  // Mkt Cap
	strAddr += "&mc_l=";
  strAddr += pDoc->m_strMktCap_Min;
	strAddr += "&mc_h=";
  strAddr += pDoc->m_strMktCap_Max;

  CString strCode;

  // Industry Group
  strCode = GetCode(pDoc->m_strIndustryGrp);
//  AfxMessageBox(strCode);
//  if ( !strCode.IsEmpty() ) {
	  strAddr += "&igroup=";
    strAddr += strCode;
  //}

  // Dow Jones
  strCode = GetCode(pDoc->m_strDowJones);
  //AfxMessageBox(strCode);
  //if ( !strCode.IsEmpty() ) {
  	strAddr += "&dj=";
    strAddr += strCode;
  //}

  // S&P 500
  strCode = GetCode(pDoc->m_strSP500);
  //AfxMessageBox(strCode);
  //if ( !strCode.IsEmpty() ) {
  	strAddr += "&sp=";
    strAddr += strCode;
  //}


  // Exhanges
  strCode = GetCode(pDoc->m_strExchg);
  //AfxMessageBox(strCode);
  //if ( !strCode.IsEmpty() ) {
	  strAddr += "&exchange=";
    strAddr += strCode;
  //}


	strIden.Empty();
	strIden += "SCREEN:";

	pReq = new CRequest;
	pReq->Init(strAddr, strIden);
	sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
	sLock.Unlock();

	m_QuotesReq++;

	long l;
  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
}

void CSMView::GetAllQuotes()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  switch (pDoc->m_bWebSite)
  {
    case CSMDoc::YAHOO:
//      CWWWMoney *pWWW = new CWWWMoney(this);
      CWWWYahoo *pWWW = new CWWWYahoo(this);
      if ( !pWWW )
        return;
      else 
        pWWW->GetALLQuotes();

  }

/*
  CString strTicker;
  strTicker = "MRK";
  CString rWebPage;
  CString strFile;
  strFile = "c:\\x.htm";
  ReadFile(strFile, rWebPage);
	CReadMsg msg;
	msg.m_strWebPageContent = rWebPage;
	msg.m_pThread = NULL;
  CWWWYahoo *pWWW = new CWWWYahoo(this);
  msg.m_pWWW = pWWW;
  OnReadCompleted((WPARAM)(LPCTSTR)strTicker, (LPARAM)&msg);
  return;
*/
}

void CSMView::GetQuote(CString& rStr)
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  switch (pDoc->m_bWebSite)
  {
    case CSMDoc::YAHOO:
      CWWWYahoo *pWWW = new CWWWYahoo(this);
      if ( !pWWW )
        return;
      else 
        pWWW->GetQuote(rStr);
  }
}

CStkTicker *CSMView::InsertTicker(	CString& rSymbol, CString& rStrLast, 
														CString& rStrChange, CString& rStrPctChange, CString& rStrHigh, 
														CString& rStrLow, CString& rStrVolume,
                            CString& rCoName, CString& strLastTraded)
{
	// Last Updated
	time_t ltime;
	time( &ltime );
	CString strTime = ctime(&ltime);
	int i = strTime.Find('\n');
	strTime = strTime.Mid(0, i);

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CStkTicker *p = NULL;
	// Set the values for the CStkTicker Object
	sLock.Lock();
	for ( i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		p = (CStkTicker *) pDoc->m_TickerArray[i];
		if ( p->m_strSymbol == rSymbol) {
      if (!rCoName.IsEmpty() && rCoName != p->m_strCoName) p->m_strCoName =  rCoName;
			if ( p->m_strCoName.IsEmpty() ) p->m_strCoName = rCoName;
      p->m_strLastUpdated = strLastTraded;

      if (p->m_bMutualFund) {
				p->m_strLast		= pDoc->ConvertToDecimal(rStrLast);
				p->m_strChange	= pDoc->ConvertToDecimal(rStrChange);
				p->m_strHigh		= pDoc->ConvertToDecimal(rStrHigh);
				p->m_strPctChange = rStrPctChange;
				p->m_strLow			= pDoc->ConvertToDecimal(rStrLow);
      }
			else if (pDoc->m_DisplayOptions == 1) {
				p->m_strLast		= pDoc->ConvertToDecimal(rStrLast);
				p->m_strChange	= pDoc->ConvertToDecimal(rStrChange);
				p->m_strPctChange = rStrPctChange;
				p->m_strHigh		= pDoc->ConvertToDecimal(rStrHigh);
				p->m_strLow			= pDoc->ConvertToDecimal(rStrLow);
			}
			else {
				p->m_strLast		= rStrLast;
				p->m_strChange	= rStrChange;
				p->m_strPctChange = rStrPctChange;
				p->m_strHigh		= rStrHigh;
				p->m_strLow			= rStrLow;
			}
			p->m_strVolume	= rStrVolume;
//			p->m_strLastUpdated = strTime;

			if( rStrChange.Find('+') != -1 ) {
				p->m_lvi.iImage = m_nSmallIdx+2;
			}
			else if(rStrChange.Find('-') != -1 ) {
				p->m_lvi.iImage = m_nSmallIdx+1;
			}
			else {
				p->m_lvi.iImage = m_nSmallIdx;
			}
			if (!p->m_strAlertHi.IsEmpty() || !p->m_strAlertLow.IsEmpty())  {
				// Do this because if alert freq was set to once, then this flag
				// was set to zero to prevent further alerts. By enabling it here
				// we are producing only one alert per update.
				p->m_bAlert = 1;
			}
			break;
		}
	}
	sLock.Unlock();

	if ( pDoc->m_AlertType != 0 && p->m_bAlert ) {
		DoAlert(p);
	}

	return p;
}

void CSMView::DeleteSelectedItem()
{
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
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
	int nItem;

	for(nItem=ListCtrl.GetNextItem(-1,LVNI_SELECTED);
			nItem!=-1;
			nItem=ListCtrl.GetNextItem(-1,LVNI_SELECTED))
	{
		lvi.iItem=nItem;
		ListCtrl.GetItem(&lvi);

		CStkTicker *p = (CStkTicker *)lvi.lParam;
		if(!p) {
			ListCtrl.DeleteItem(nItem);
			continue;
		}

		sLock.Lock();
		for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
			CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[i];
			if ( pTick && pTick->m_strSymbol == p->m_strSymbol) {
        if ( m_pValVw) m_pValVw->SendMessage(DELVALUATIONTICKER, (WPARAM)(LPCTSTR)p->m_strSymbol, NULL);
				pDoc->SetModifiedFlag(TRUE);
				pDoc->m_TickerArray.RemoveAt(i);
				delete p;
				ListCtrl.DeleteItem(nItem);
				pDoc->SetModifiedFlag(TRUE);
				break;
			}
		}
		sLock.Unlock();
	}
	Invalidate();
}

void CSMView::OnViewRefresh() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int iNumTickers = pDoc->m_TickerArray.GetSize();

	if ( iNumTickers ) {
		GetAllQuotes();
	}
}

CStkTicker *CSMView::InListCtrl( LPCTSTR pTicker )
{
	if ( !pTicker ) {
		return NULL;
	}

	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CString str;
	str = pTicker;
	if(pDoc->m_bMakeSymbolsUpperCase) str.MakeUpper();
	
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
			if ( p && p->m_strSymbol == str) {
				return p;
			}
		}
	}

	return NULL;
}

void CSMView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM lvi = pDispInfo->item;
	CString str;
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	if (lvi.pszText != NULL && !InListCtrl(lvi.pszText)) {
		str = lvi.pszText;
		if(pDoc->m_bMakeSymbolsUpperCase) str.MakeUpper();
		CStkTicker *p = new CStkTicker(str);
		if ( !p )
			return;
		if ( pDoc->IsStdTicker(str) ) {
			p->m_bStdTicker=TRUE;
		}

		if (m_bAddingFund) {
			p->m_bMutualFund=TRUE;
			if (p->m_strSymbol.Left(1) != "^" ) p->m_strSymbol = p->m_strSymbol + ".NS";
		}

		sLock.Lock();
		pDoc->m_TickerArray.InsertAt(lvi.iItem,p);
		sLock.Unlock();
		ListCtrl.DeleteItem(pDispInfo->item.iItem);
		OnPopulateList(0,0);
		pDoc->SetModifiedFlag(TRUE);

    // Get the latest quote
//    GetQuote(str);
	}
	else {
		ListCtrl.DeleteItem(pDispInfo->item.iItem);
		Invalidate();	
	}

	m_bAddingFund	= FALSE;
	*pResult = 0;
}

void CSMView::OnViewOptions() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CGeneralOptions Page1;
	// Options from General PropertyPage
	Page1.m_bConfirmDel=pDoc->m_bConfirmDel;
	Page1.m_bAutoSaveDoc=pDoc->m_bAutoSaveDoc;
	Page1.m_bMakeSymbolsUpperCase=pDoc->m_bMakeSymbolsUpperCase;
	Page1.m_DisplayOptions=pDoc->m_DisplayOptions;

	CUPdates Page2;
	Page2.m_nInterval = pDoc->m_nInterval/1000;
	Page2.m_bDisableUpdateonWkends = pDoc->m_bDisableUpdateonWkends;
	Page2.m_bAutoUpdates = pDoc->m_bAutoUpdates ;
	Page2.m_strOpenTime = pDoc->m_strOpenTime ;
	Page2.m_strCloseTime = pDoc->m_strCloseTime;
	Page2.m_nMaxStksInReq = pDoc->m_nMaxStksInReq;

	CProxyDlg Page3;
	Page3.m_bUseProxy = pDoc->m_bUseProxy ;
	Page3.m_strProxy  = pDoc->m_strProxy ;
	Page3.m_strPort   = pDoc->m_strPort ;
	Page3.m_DUP		  = pDoc->m_DUP;
	Page3.m_bHangup   = pDoc->m_bHangup;

	CConfigAlertDlg Page4;
	Page4.m_Freq = pDoc->m_Freq ;
	Page4.m_AlertType = pDoc->m_AlertType;
	Page4.m_dwSeconds	= pDoc->m_dwSeconds;
	Page4.m_strWAVFile = pDoc->m_strWavFile;

	CChartPrefDlg Page5;
	Page5.m_strPts						= pDoc->m_strPts;
	Page5.m_strType						= pDoc->m_strType;
	Page5.m_strImageLocation	= pDoc->m_strImageLocation;
  Page5.m_strChartString = pDoc->m_strChartString;



  CStkTicker *p=NULL;
  CString str;
	int nHitItem = GetSelectedRows(&p, -1);
	if ( -1 != nHitItem && p ) {
    str = p->m_strSymbol;
  }

  CSetAlertDlg Page6(pDoc->m_TickerArray, pDoc, str, this);

	CPref_RGB Page7;
	Page7.m_strROE = pDoc->m_strROE;

	if(m_pPS) {
		delete m_pPS;
		m_pPS = NULL;
	}

	m_pPS = new CPropertySheet;
	if(!m_pPS) {
		return;
	}

	m_pPS->AddPage(&Page1);
	m_pPS->AddPage(&Page2);
	m_pPS->AddPage(&Page3);
	m_pPS->AddPage(&Page4);
	m_pPS->AddPage(&Page5);
	m_pPS->AddPage(&Page6);
	m_pPS->AddPage(&Page7);

	if(IDOK == m_pPS->DoModal() ) {

		// Get Options from GeneralOptions PropertyPage
		pDoc->m_bConfirmDel		= Page1.m_bConfirmDel;
		pDoc->m_bAutoSaveDoc	= Page1.m_bAutoSaveDoc;
		pDoc->m_bMakeSymbolsUpperCase = Page1.m_bMakeSymbolsUpperCase;
		pDoc->m_DisplayOptions = Page1.m_DisplayOptions;
		

		// Get Options from Updates PropertyPage
		pDoc->m_bDisableUpdateonWkends = Page2.m_bDisableUpdateonWkends;
		pDoc->m_bAutoUpdates = Page2.m_bAutoUpdates ;
		pDoc->m_strOpenTime = Page2.m_strOpenTime ;
		pDoc->m_strCloseTime = Page2.m_strCloseTime;
		pDoc->m_nMaxStksInReq = Page2.m_nMaxStksInReq;

		if(pDoc->m_nInterval != Page2.m_nInterval*1000) {
			pDoc->m_nInterval = Page2.m_nInterval;
			pDoc->m_nInterval = pDoc->m_nInterval<=0 ? 15 : pDoc->m_nInterval;
			pDoc->m_nInterval = pDoc->m_nInterval*1000;
		}

		StopTimer(m_nTimerID);
		StopTimer(m_nNextUpdateTimerID);

		if ( pDoc->m_bAutoUpdates == 0) {
			THEAPP()->ShowMsgText((LPCTSTR)"Updates are off.");
		}
		else {
			StartTimers();
		}

		// Get Options from Proxy PropertyPage
		pDoc->m_bUseProxy = Page3.m_bUseProxy;
		pDoc->m_bHangup   = Page3.m_bHangup;
		if (pDoc->m_bUseProxy == 0) { // Modem
			pDoc->m_DUP = Page3.m_DUP;
		}
		else if ( pDoc->m_bUseProxy == 1 ) { // LAN
				pDoc->m_strProxy  = Page3.m_strProxy;
				pDoc->m_strPort   = Page3.m_strPort;
		}
		StartWorkerThread();

		// Get Options from Price Alert PropertyPage
		pDoc->m_Freq = Page4.m_Freq ;
		pDoc->m_AlertType = Page4.m_AlertType;
		if ( pDoc->m_dwSeconds != Page4.m_dwSeconds ) {
			pDoc->m_dwSeconds = Page4.m_dwSeconds;

		}

		// Get Options from Chart PropertyPage
		pDoc->m_strPts						= Page5.m_strPts;
		pDoc->m_strType						=	Page5.m_strType;
		pDoc->m_strImageLocation	= Page5.m_strImageLocation;
		if ( (pDoc->m_strImageLocation).Right(1) != "\\" )
			pDoc->m_strImageLocation += '\\';
    pDoc->m_strChartString = Page5.m_strChartString;
	if (pDoc->m_strChartString.IsEmpty()) {
		pDoc->m_strChartString = _T("&p=e10,m15,m200,m65&l=on&z=l&q=c&a=m26-12-9,ss,vm");
		pDoc->m_bWebSite = CSMDoc::YAHOO;
	}
		//Options from RGB PropertyPage
		pDoc->m_strROE = Page7.m_strROE;

		pDoc->SetModifiedFlag(TRUE);
	}
	delete m_pPS;
	m_pPS = NULL;
}

void CSMView::StartWorkerThread()
{
	StopWorkerThread();

	SYSTEM_INFO si;
	CInternetThread *pThread=NULL;

	GetSystemInfo(&si);
	m_TotThreads = si.dwNumberOfProcessors * 4; 
	
	m_hWorkEvent = CreateSemaphore(NULL, 0, m_TotThreads, NULL);

	for (int i=0; i<m_TotThreads; i++) {

		pThread = (CInternetThread*)
			AfxBeginThread(RUNTIME_CLASS(CInternetThread), THREAD_PRIORITY_NORMAL,
				0, CREATE_SUSPENDED);
		pThread->Init(this->m_hWnd, GetDocument(), HANDLE(m_hWorkEvent), this);
		m_WrkThreadArray.Add(pThread);
		pThread->ResumeThread();
	}
}

void CSMView::StopWorkerThread()
{
	CInternetThread *pThread=NULL;
	LONG l;

	while (m_WrkThreadArray.GetSize()) {
		pThread = (CInternetThread *)m_WrkThreadArray.GetAt(0);
		if( pThread) {
			pThread->m_bDone = TRUE;
			SetEvent(m_hWorkEvent);
			m_WrkThreadArray.RemoveAt(0);
			ReleaseSemaphore(m_hWorkEvent, 1, &l);
		}
	}
  m_TotThreads=0;
//	CloseHandle(m_hWorkEvent);
//	m_hWorkEvent=NULL;
}

BOOL CSMView::IsUpdateWindow()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	BOOL bRet=FALSE;

	if ( pDoc->m_bAutoUpdates == 0) {
		return bRet;
	}

	if(pDoc->m_bAutoUpdates == 1 ) {
		// Enable Updates at all times incl weekends
		return TRUE;
	}

	if ( pDoc->m_bDisableUpdateonWkends ) {
		// Is it the weekend
		CTime t = CTime::GetCurrentTime();		
		int iDay = t.GetDayOfWeek();
		if ( iDay == 1 || iDay == 7 ) {
			return bRet;
		}
	}

	
	int Hr, Min;
	if ( pDoc->m_bAutoUpdates == 2 && !pDoc->m_strOpenTime.IsEmpty() ) {
		CTime t = CTime::GetCurrentTime();
		int iMin = pDoc->m_strOpenTime.Find(':');
		if ( iMin != -1 ) {
			Hr = _wtoi((LPCTSTR)pDoc->m_strOpenTime.Mid(0,iMin));
			Min = _wtoi((LPCTSTR)pDoc->m_strOpenTime.Mid(iMin+1));
		}

		if( t.GetHour() < Hr ) {
			return FALSE;
		}

		if ( t.GetHour() == Hr && t.GetMinute() < Min ) {
			return FALSE;
		}
	}

	if ( pDoc->m_bAutoUpdates == 2 && !pDoc->m_strCloseTime.IsEmpty() ) {
		CTime t = CTime::GetCurrentTime();
		int iMin = pDoc->m_strCloseTime.Find(':');
		if ( iMin != -1 ) {
			Hr = _wtoi((LPCTSTR)pDoc->m_strCloseTime.Mid(0,iMin));
			Min = _wtoi((LPCTSTR)pDoc->m_strCloseTime.Mid(iMin+1));
		}

		if( t.GetHour() > Hr ) {
			return FALSE;
		}

		if ( t.GetHour() == Hr && t.GetMinute() > Min ) {
			return FALSE;
		}

	}

	return TRUE;
}

void CSMView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_POPUP_MENU))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,point.x, point.y,AfxGetMainWnd()); 
	}
	
}

void CSMView::OnPortfolioDeleteticker() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( pDoc->m_bConfirmDel ) {
		CConfirmDelDlg d;
		if (IDOK == d.DoModal()) {
			DeleteSelectedItem();
		}
	}
	else {
		DeleteSelectedItem();
	}
}

void CSMView::OnUpdatePortfolioDeleteticker(CCmdUI* pCmdUI) 
{
	CListCtrl& ListCtrl=GetListCtrl();
	pCmdUI->Enable(ListCtrl.GetSelectedCount());
}

void CSMView::OnPortfolioAddticker() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	// get item data
	WCHAR szBuff[MAX_PATH];
	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.lParam=NULL;
	lvi.stateMask=0xFFFF;		// get all state flags

	int nItem	=	ListCtrl.GetNextItem(-1,LVNI_SELECTED);
	if ( nItem != -1 ) {
		int iIndex = ListCtrl.InsertItem(nItem+1,(LPCTSTR)"New"); 
		ListCtrl.EditLabel(iIndex);
	}
	else {
		int iCount = ListCtrl.GetItemCount();
		int iIndex = ListCtrl.InsertItem(iCount + 1, (LPCTSTR)"New");
		ListCtrl.EditLabel(iIndex);
	}
}

void CSMView::OnPortfolioAddfund() 
{
	m_bAddingFund=TRUE;
	OnPortfolioAddticker();
	
}

int CSMView::GetSelectedRows(CStkTicker **p, int nStartRow)
{
	*p=NULL;
	
	// get item data
	WCHAR szBuff[MAX_PATH];
	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.lParam=NULL;
	lvi.stateMask=0xFFFF;		// get all state flags

	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int nItem=0;

	for(	nItem	=	ListCtrl.GetNextItem(nStartRow,LVNI_SELECTED);
				nItem!=-1; 
				nItem=ListCtrl.GetNextItem(nItem,LVNI_SELECTED)) {

			lvi.iItem = nItem;
			if(ListCtrl.GetItem(&lvi)) {
				*p = (CStkTicker *) lvi.lParam;
				break;
			}
			else {
				nItem=-1;
				break;
			}
	}

	return nItem;
}

void CSMView::OnPortfolioUpdateselected() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  switch (pDoc->m_bWebSite)
  {
  case CSMDoc::YAHOO:
      CWWWYahoo *pWWW = new CWWWYahoo(this);
      if ( !pWWW )
        return;
      else 
        pWWW->UpdateSelected();
  }
}

void CSMView::OnUpdatePortfolioUpdateselected(CCmdUI* pCmdUI) 
{
	CListCtrl& ListCtrl=GetListCtrl();
	pCmdUI->Enable(ListCtrl.GetSelectedCount());
}

static int iColOrder[] = {0,0,0,0,0,0,0,0,0,0,0};
static CSMDoc *pDoc = NULL;

void CSMView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl& ListCtrl=GetListCtrl();
	iColOrder[pNMListView->iSubItem]==0 ? iColOrder[pNMListView->iSubItem]=1 : iColOrder[pNMListView->iSubItem]=0;

	pDoc = CSMView::GetDocument();
	ASSERT_VALID(pDoc);

	ListCtrl.SortItems(CompareFunc, (LPARAM)(pNMListView->iSubItem));
	*pResult = 0;
}

int CALLBACK CSMView::CompareFunc(LPARAM lParam1, LPARAM lParam2, 
	LPARAM lParamSort)
{
	CStkTicker *p1 = (CStkTicker *)lParam1;
	CStkTicker *p2 = (CStkTicker *)lParam2;
	double dRes;
	int iRes=0;
	CString str1, str2;
  CString msg;
  int iDiff=0, iDiff2=0;
	int i=0;
	if ( !p1 || !p2 )
		return iRes;

	switch( lParamSort)
	{
		case 0: // Ticker
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strSymbol, p2->m_strSymbol);
			}
			else {
				iRes = lstrcmpi(p2->m_strSymbol, p1->m_strSymbol);
			}
			break;

		case 1: // Company Name
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strCoName, p2->m_strCoName);
			}
			else {
				iRes = lstrcmpi(p2->m_strCoName, p1->m_strCoName);
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

		case 3: // Change
			str1 = pDoc->ConvertToDecimal(p1->m_strChange);
			str2 = pDoc->ConvertToDecimal(p2->m_strChange);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 4: // PctChange
			str1 = pDoc->ConvertToDecimal(p1->m_strPctChange.Left(p1->m_strPctChange.GetLength()-1));
			str2 = pDoc->ConvertToDecimal(p2->m_strPctChange.Left(p2->m_strPctChange.GetLength()-1));
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;

			break;

		case 5: // Volume
			while ( i<p1->m_strVolume.GetLength() ) {
				if (isdigit(p1->m_strVolume[i])) {
					str1 += p1->m_strVolume[i];
				}
				i++;
			}

			i=0;
			while ( i<p2->m_strVolume.GetLength() ) {
				if (isdigit(p2->m_strVolume[i])) {
					str2 += p2->m_strVolume[i];
				}
				i++;
			}

			if(iColOrder[lParamSort]) {
				iRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				iRes = _wtoi(str2) - _wtoi(str1);			
			}
			break;

		case 6: // High
			str1 = pDoc->ConvertToDecimal(p1->m_strHigh);
			str2 = pDoc->ConvertToDecimal(p2->m_strHigh);
			if(iColOrder[lParamSort]) {
				dRes = _wtof(str1) - _wtof(str2);			
			}
			else {
				dRes = _wtof(str2) - _wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 7: // Low
			str1 = pDoc->ConvertToDecimal(p1->m_strLow);
			str2 = pDoc->ConvertToDecimal(p2->m_strLow);
			if(iColOrder[lParamSort]) {
				dRes = _wtoi(str1) - _wtoi(str2);			
			}
			else {
				dRes = _wtoi(str2) - _wtoi(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 8: // Last Updated
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strLastUpdated, p2->m_strLastUpdated);
			}
			else {
				iRes = lstrcmpi(p2->m_strLastUpdated, p1->m_strLastUpdated);
			}
			break;

		case 9: // Date Picked
			str1 = p1->m_dtPicked;
			str2 = p2->m_dtPicked;
			str1.Trim();
			str2.Trim();

			if (str1.Find('.') != -1) {
				str1 = pDoc->ConvertToDecimal(str1);
				str2 = pDoc->ConvertToDecimal(str2);
				if(iColOrder[lParamSort]) {
					dRes = _wtof(str1)- _wtof(str2);
				}
				else {
					dRes = _wtof(str2) -  _wtof(str1);
				}
				iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			} else {
				if(iColOrder[lParamSort]) {
					iRes = lstrcmpi(p1->m_dtPicked, p2->m_dtPicked);
				}
				else {
					iRes = lstrcmpi(p2->m_dtPicked, p1->m_dtPicked);
				}
			}
			break;

		case CLOSEST_TO_LOW_PRICE: // 10
			str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			str2 = pDoc->ConvertToDecimal(p2->m_strLast);
      iDiff = _wtoi(str1) - _wtoi(p1->m_strAlertLow);
      iDiff2 = _wtoi(str2) - _wtoi(p2->m_strAlertLow);
      if ( _wtoi(p1->m_strAlertLow) <= 0 && _wtoi(p2->m_strAlertLow) <= 0) {
        iRes = 0;
      }
      else if ( _wtoi(p1->m_strAlertLow) <= 0 && _wtoi(p2->m_strAlertLow) > 0) {
        iRes = 1;
      }
      else if ( _wtoi(p1->m_strAlertLow) > 0 && _wtoi(p2->m_strAlertLow) <= 0) {
        iRes = -1;
      }
      else {
        iRes = iDiff < iDiff2 ? -1 : iDiff==iDiff2 ? 0 : 1;
      }


			break;

		case CLOSEST_TO_HI_PRICE: // 11
			  str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			  str2 = pDoc->ConvertToDecimal(p2->m_strLast);
        iDiff = _wtoi(str1) - _wtoi(p1->m_strAlertHi);
        iDiff2 = _wtoi(str2) - _wtoi(p2->m_strAlertHi);
        if ( _wtoi(p1->m_strAlertHi) <= 0 && _wtoi(p2->m_strAlertHi) <= 0) {
          iRes = 0;
        }
        else if ( _wtoi(p1->m_strAlertHi) <= 0 && _wtoi(p2->m_strAlertHi) > 0) {
          iRes = 1;
        }
        else if ( _wtoi(p1->m_strAlertHi) > 0 && _wtoi(p2->m_strAlertHi) <= 0) {
          iRes = -1;
        }
        else {
          iRes = iDiff < iDiff2 ? 1 : iDiff==iDiff2 ? 0 : -1;
        }

			break;

	}
	return iRes;
}


void CSMView::AddStdTickers( UINT nID )
{
	CString str;
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	switch ( nID )
	{
		case ID_PORTFOLIO_ADDINDEXTICKERS_NASDAQCOMPOSITE:
			str = pDoc->m_StdTickerArray[0]; 
			break;

		case ID_PORTFOLIO_ADDINDEXTICKERS_DJIA:
			str = pDoc->m_StdTickerArray[1]; 
			break;

		case ID_PORTFOLIO_ADDINDEXTICKERS_ADDALLOFTHEABOVE:
			{
				for ( int i= ID_PORTFOLIO_ADDINDEXTICKERS_NASDAQCOMPOSITE;
									 i < ID_PORTFOLIO_ADDINDEXTICKERS_ADDALLOFTHEABOVE; i++)
					AddStdTickers(i);
					return;
			}

		case ID_PORTFOLIO_ADDINDEXTICKERS_REMOVEALLOFTHEABOVE :
				RemoveStdTickers();
				return;
			break;

	}

	if(pDoc->m_bMakeSymbolsUpperCase) str.MakeUpper();
	if ( InListCtrl( (LPTSTR)(LPCTSTR)str)) {
		return;
	}
	CStkTicker *p = new CStkTicker(str);
	p->m_bStdTicker=TRUE;
	sLock.Lock();
	pDoc->m_TickerArray.Add(p);
	sLock.Unlock();
	OnPopulateList(0,0);
	pDoc->SetModifiedFlag(TRUE);
  GetQuote(p->m_strSymbol);
}

void CSMView::RemoveStdTickers()
{
	CListCtrl& ListCtrl=GetListCtrl();	
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	sLock.Lock();
	CPtrArray a;
	a.Append(pDoc->m_TickerArray);

	int j=a.GetSize();
	int iDel=0;
	for ( int i=0; i<j; i++) {
		CStkTicker *p = (CStkTicker *) a[i];
		if ( p && p->m_bStdTicker ) {
			pDoc->m_TickerArray.RemoveAt(i-iDel);
			ListCtrl.DeleteItem(p->m_lvi.iItem-iDel);
			iDel++;
			delete p;
		}
	}
	sLock.Unlock();
}

void CSMView::UpdateRow(CStkTicker *p, int iIndex)
{
	if (!p)
		return;

	CListCtrl& ListCtrl=GetListCtrl();	
	int i;

	if ( iIndex == - 1 ) {
		LV_FINDINFO lvf;
		lvf.flags = LVFI_STRING;
		lvf.psz		= (LPCTSTR)p->m_strSymbol;
		i = ListCtrl.FindItem(&lvf);
	}
	else {
		i = iIndex;
	}

	if ( i != -1 ) {
		LV_ITEM lvi;
		lvi = p->m_lvi;
		lvi.iItem = p->m_lvi.iItem =i;
		lvi.iSubItem=0;
		lvi.pszText	=	(LPTSTR)(LPCTSTR)p->m_strSymbol;
		lvi.lParam = (LPARAM)p;
		lvi.iImage = p->m_lvi.iImage;
		ListCtrl.DeleteItem(i);
		ListCtrl.InsertItem(&lvi);

		ListCtrl.SetItemText( i,1,p->m_strCoName.GetBuffer(p->m_strCoName.GetLength()));
    ListCtrl.SetItemText( i,2,p->m_strLast.GetBuffer(p->m_strLast.GetLength()));
		ListCtrl.SetItemText( i,3,(LPTSTR)(LPCTSTR)p->m_strChange);
		ListCtrl.SetItemText( i,4,(LPTSTR)(LPCTSTR)p->m_strPctChange);
		ListCtrl.SetItemText( i,5,(LPTSTR)(LPCTSTR)p->m_strVolume);
		ListCtrl.SetItemText( i,6,(LPTSTR)(LPCTSTR)p->m_strHigh);
		ListCtrl.SetItemText( i,7,(LPTSTR)(LPCTSTR)p->m_strLow);
		ListCtrl.SetItemText( i,8,(LPTSTR)(LPCTSTR)p->m_strLastUpdated);
		ListCtrl.SetItemText( i,9,(LPTSTR)(LPCTSTR)p->m_dtPicked);
	}
}

BOOL CSMView::DoAlert()
{
	static DWORD dwCalls;
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	dwCalls++;

	if ( dwCalls < pDoc->m_dwSeconds ) {
		return FALSE;
	}
	else {
			dwCalls=0;
	}

	int j=pDoc->m_TickerArray.GetSize();
	BOOL bDoSpecific=FALSE;
	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.SendMessage(WM_SETREDRAW,0,0);
	for ( int i=0; i<j; i++) {
		CStkTicker *p = (CStkTicker *) pDoc->m_TickerArray[i];

		if(bDoSpecific) {
			if(DoAlert(p)) {
				UpdateRow(p);
			}
		}
		else {
			bDoSpecific = DoAlert(p);
			if (bDoSpecific) {
				UpdateRow(p);
			}
		}

		if ( pDoc->m_Freq == 0 ) {
			// Produce an alert only once. So set the flag
			p->m_bAlert=0;
		}
		else {
			p->m_bAlert=1;
		}
	}

	if(bDoSpecific)
		DoSpecificAlertType();

	ListCtrl.SendMessage(WM_SETREDRAW,1,0);
	UpdateWindow();

	return (bDoSpecific == TRUE);
}

BOOL CSMView::DoAlert(CStkTicker *p)
{
	if ( !p || !p->m_bAlert == 1) {
		return FALSE; 
	}

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	BOOL bRet=FALSE;

	double last, hi, low;
	CString strL = pDoc->ConvertToDecimal(p->m_strLast);
	last = _wtof(strL);
	if ( last <= 0 ) {
		return FALSE;
	}

	CString strHi = pDoc->ConvertToDecimal(p->m_strHigh);
	hi = _wtof(strHi);
	if ( hi <= 0 ) {
		return FALSE;
	}

	CString strLow = pDoc->ConvertToDecimal(p->m_strLow);
	low = _wtof(strLow);
	if ( low <= 0 ) {
		return FALSE;
	}

	double alerthi;
	if (!p->m_strAlertHi.IsEmpty())  {
		CString str = pDoc->ConvertToDecimal(p->m_strAlertHi);
		alerthi = _wtof(str);
		if (alerthi <= last || (!p->m_bMutualFund && alerthi <= hi) ) {
			p->m_lvi.iImage = m_nSmallIdx+3;
			return TRUE;
		}
	}

	double alertlow;
	if (!p->m_strAlertLow.IsEmpty())  {
		CString str = pDoc->ConvertToDecimal(p->m_strAlertLow);
		alertlow = _wtof(str);
		if (alertlow >= last || (!p->m_bMutualFund && alertlow >= low)) {
			p->m_lvi.iImage = m_nSmallIdx+3;
			return TRUE;
		}
	}
	return bRet;
}

void CSMView::DoSpecificAlertType()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch ( pDoc->m_AlertType ) 
	{
		case 1: // Flash Window
			AfxGetMainWnd()->FlashWindow(TRUE);
			break;

		case 2: // Bring Window to Top ( even if minimized )
			AfxGetMainWnd()->BringWindowToTop();
			AfxGetMainWnd()->ShowWindow(SW_SHOWNORMAL);
			break;

		case 3: // Beep
			Beep(100,1000);
			break;

		case 4: // Play Wav file
			if ( !pDoc->m_strWavFile.IsEmpty()) {
				//PlaySound(pDoc->m_strWavFile, NULL,SND_FILENAME); 
			}
			break;
	}
}

BOOL CSMView::CreateSummaryWindow()
{
	if(!m_pMktSum) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CMktSumVw(this);
			m_pMktSum = (CMktSumVw *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 1;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
      m_pMktSum->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_MKT_SUM_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pMktSum->SendMessage(WM_INITIALUPDATE, 0, 0);

			THEAPP()->SwitchView(m_pMktSum);

	}
	else {
		THEAPP()->SwitchView(m_pMktSum);
	}

	return TRUE;
}

BOOL CSMView::CreateScreenWindow()
{
	if(!m_pScreenVw) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CScreenVw(this);
			m_pScreenVw = (CScreenVw *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 2;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
      m_pScreenVw->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_SCREEN_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pScreenVw->SendMessage(WM_INITIALUPDATE, 0, 0);

			THEAPP()->SwitchView(m_pScreenVw);

	}
	else {
		THEAPP()->SwitchView(m_pScreenVw);
	}

	return TRUE;
}

BOOL CSMView::CreateFundaWindow()
{
	if(!m_pFundaVw) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CFundaVw(this);
			m_pFundaVw = (CFundaVw *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 3;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
      m_pFundaVw->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_FUNDA_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pFundaVw->SendMessage(WM_INITIALUPDATE, 0, 0);

			THEAPP()->SwitchView(m_pFundaVw);

	}
	else {
		THEAPP()->SwitchView(m_pFundaVw);
	}

	return TRUE;
}

BOOL CSMView::CreateBrowserWindow()
{
	if(!m_pBrowserVw) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CBrowserVw(this);
			m_pBrowserVw = (CBrowserVw *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 4;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
	  m_pBrowserVw->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_BROWSER_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pBrowserVw->SendMessage(WM_INITIALUPDATE, 0, 0);

			THEAPP()->SwitchView(m_pBrowserVw);

	}
	else {
		THEAPP()->SwitchView(m_pBrowserVw);
	}

	return TRUE;
}

BOOL CSMView::CreateValuationWindow()
{
	if(!m_pValVw) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CValuationVw(this);
			m_pValVw = (CValuationVw *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 5;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
	  m_pValVw->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_VALUATION_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pValVw->SendMessage(WM_INITIALUPDATE, 0, 0);

			//THEAPP()->SwitchView(m_pValVw);

	}
	else {
		//THEAPP()->SwitchView(m_pValVw);
	}

	return TRUE;
}


BOOL CSMView::CreateRGBWindow()
{
	if(!m_pRGBVw) {
      CView* pActiveView = ((CFrameWnd*) AfxGetMainWnd())->GetActiveView();
      THEAPP()->m_pOldView = pActiveView;
      THEAPP()->m_pNewView = (CView*) new CRGBView(this);
			m_pRGBVw = (CRGBView *)THEAPP()->m_pNewView;
      CDocument* pCurrentDoc =
         ((CFrameWnd*) AfxGetMainWnd())->GetActiveDocument();
 
      // Initialize a CCreateContext to point to the active document.
      // With this context, the new view is added to the document
      // when the view is created in CView::OnCreate().
      CCreateContext newContext;
      newContext.m_pNewViewClass = NULL;
      newContext.m_pNewDocTemplate = NULL;
      newContext.m_pLastView = NULL;
      newContext.m_pCurrentFrame = NULL;
      newContext.m_pCurrentDoc = pCurrentDoc;
 
      // The ID of the initial active view is AFX_IDW_PANE_FIRST.
      // Incrementing this value by one for additional views works
      // in the standard document/view case but the technique cannot
      // be extended for the CSplitterWnd case.
      UINT viewID = AFX_IDW_PANE_FIRST + 6;
      CRect rect(0, 0, 0, 0); // gets resized later
 
      // Create the new view. In this example, the view persists for
      // the life of the application. The application automatically
      // deletes the view when the application is closed.
	  m_pRGBVw->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect,
                              AfxGetMainWnd(), ID_RGB_VIEW, &newContext);
 
      // When a document template creates a view, the WM_INITIALUPDATE
      // message is sent automatically. However, this code must
      // explicitly send the message, as follows.
      m_pRGBVw->SendMessage(WM_INITIALUPDATE, 0, 0);

			//THEAPP()->SwitchView(m_pRGBVw);

	}
	else {
		//THEAPP()->SwitchView(m_pRGBVw);
	}

	return TRUE;
}

void CSMView::OnSummaryNasdaq() 
{
	GetSummary(SUMMARY_NASDAQ);
}

void CSMView::OnSummaryNyse() 
{
	GetSummary(SUMMARY_NYSE);
}

void CSMView::OnSummaryAmex() 
{
	GetSummary(SUMMARY_AMEX);
}

void CSMView::GetSummary(int iID)
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr;
	strAddr = "http://";
	strAddr += pDoc->m_strIP_DBC; 

	CString strAddrYahoo;
	strAddrYahoo = "http://";
	strAddrYahoo += "finance.yahoo.com/";

	CString strAddrYahooIndia;
	strAddrYahooIndia = "http://";
	strAddrYahooIndia += "in.finance.yahoo.com/";


	CRequest *pReq = new CRequest;
	if ( !pReq )
		return;

	switch ( iID )
	{
		case SUMMARY_NYSE:
      strAddr += "/forms/r_nyse.htx";
			pReq->Init(strAddr, (LPCTSTR)"NYSE");
			break;

		case SUMMARY_NASDAQ:
      strAddr += "/forms/r_nasdaq.htx";
			pReq->Init(strAddr, (LPCTSTR)"NASDAQ");
			break;

		case SUMMARY_AMEX:
      strAddr += "/forms/r_amex.htx";
			pReq->Init(strAddr, (LPCTSTR)"AMEX");
			break;

		case SUMMARY_YAHOO_NYSE_VOL_GAINERS:
      strAddrYahoo += "actives?e=nq";
			pReq->Init(strAddrYahoo, (LPCTSTR)"NYSE");
			break;

		case SUMMARY_YAHOO_NYSE_PRICE_GAINERS:
      strAddrYahoo += "gainers?e=nq";
			pReq->Init(strAddrYahoo, (LPCTSTR)"NYSE");
			break;

		case SUMMARY_YAHOO_NASDAQ_VOL_GAINERS:
      strAddrYahoo += "actives?e=o";
			pReq->Init(strAddrYahoo, (LPCTSTR)"NASDAQ");
			break;

		case SUMMARY_YAHOO_NASDAQ_PRICE_GAINERS:
      strAddrYahoo += "gainers?e=o";
			pReq->Init(strAddrYahoo, (LPCTSTR)"NASDAQ");
			break;

		case SUMMARY_YAHOO_AMEX_VOL_GAINERS:
      strAddrYahoo += "actives?e=aq";
			pReq->Init(strAddrYahoo, (LPCTSTR)"AMEX");
			break;

		case SUMMARY_YAHOO_AMEX_PRICE_GAINERS:
      strAddrYahoo += "gainers?e=aq";
			pReq->Init(strAddrYahoo, (LPCTSTR)"AMEX");
			break;

		case SUMMARY_YAHOO_INDIA_BOM_VOL_GAINERS:
      strAddrYahooIndia += "mnvl?e=bo";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"BOMBAY");
			break;

		case SUMMARY_YAHOO_INDIA_NAT_VOL_GAINERS:
      strAddrYahooIndia += "mnvl?e=ns";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"NATIONAL");
			break;

		case SUMMARY_YAHOO_INDIA_CAL_VOL_GAINERS:
      strAddrYahooIndia += "mnvl?e=cl";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"CALCUTTA");
			break;

		case SUMMARY_YAHOO_INDIA_BOM_PRICE_GAINERS:
      strAddrYahooIndia += "mnng?e=bo";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"BOMBAY");
			break;

		case SUMMARY_YAHOO_INDIA_NAT_PRICE_GAINERS:
      strAddrYahooIndia += "mnng?e=ns";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"NATIONAL");
			break;

		case SUMMARY_YAHOO_INDIA_CAL_PRICE_GAINERS:
      strAddrYahooIndia += "mnng?e=cl";
			pReq->Init(strAddrYahooIndia, (LPCTSTR)"CALCUTTA");
			break;

		case SUMMARY_WSJ_100_NYSE:
			strAddrYahoo = "http://online.wsj.com/documents/vpl-nyse.htm";
			pReq->Init(strAddrYahoo, (LPCTSTR)"WSJ_NYSE");
			break;

		case SUMMARY_WSJ_100_NASDAQ:
			strAddrYahoo = "http://online.wsj.com/documents/vpl-nnm.htm";
			pReq->Init(strAddrYahoo, (LPCTSTR)"WSJ_NQ");
			break;

		case SUMMARY_WSJ_100_AMEX:
			strAddrYahoo = "http://online.wsj.com/documents/vpl-amex.htm";
			pReq->Init(strAddrYahoo, (LPCTSTR)"WSJ_AMEX");
			break;

		case SUMMARY_WSJ_SUMMARY:
			strAddrYahoo = "http://online.wsj.com/documents/volper.htm";
			pReq->Init(strAddrYahoo, (LPCTSTR)"WSJ_NYSE");
			break;

		default:
			delete pReq;
			return;
	}


	sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
	sLock.Unlock();
	m_QuotesReq++;

	long l;
  if ( 0 == m_TotThreads) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
	m_bSummaryInProgress = TRUE;
}

void CSMView::OnUpdateSummaryAmex(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bSummaryInProgress);
}

void CSMView::OnUpdateSummaryNasdaq(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bSummaryInProgress);
}

void CSMView::OnUpdateSummaryNyse(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bSummaryInProgress);
}

void CSMView::OnViewMktSummary() 
{
	if (m_pMktSum)
		THEAPP()->SwitchView(m_pMktSum);
}

void CSMView::OnUpdateViewMktSummary(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pMktSum != NULL);
}

void CSMView::OnViewfundamentals() 
{
	if (m_pFundaVw)
		THEAPP()->SwitchView(m_pFundaVw);
}

void CSMView::OnUpdateViewfundamentals(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pFundaVw != NULL);
}



void CSMView::OnUpdateViewRefresh(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetItemCount());
}

void CSMView::OnUpdateViewRefreshvaluation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetItemCount());
}

void CSMView::OnHelpHowtoregister() 
{
	CRegInsDlg d;
	d.m_strInst.LoadString(IDS_HOW_TO_REG);
	d.m_strRegKey = THEAPP()->GetSerialNo();
	d.DoModal();
	
}

void CSMView::OnPortfolioTrade() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int nItem=-1;
	CStkTicker *p=NULL;
	CString strTicker;
	if ( -1 != GetSelectedRows(&p, -1) && p) {
		strTicker = p->m_strSymbol;
	}
	
	CTrdDet d(pDoc->m_TickerArray, pDoc, strTicker);
	d.DoModal();

}


void CSMView::OnPortfolioScreen() 
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  CStkScreenDlg	d(pDoc);
  if (IDOK == d.DoModal() ) {
    pDoc->m_strPrice_Min    = d.m_strPrice_Min;
    pDoc->m_strPrice_Max    = d.m_strPrice_Max;
    pDoc->m_strPBRatio_Min  = d.m_strPBRatio_Min;
    pDoc->m_strPBRatio_Max  = d.m_strPBRatio_Max;
    pDoc->m_strPSRatio_Min  = d.m_strPSRatio_Min;
    pDoc->m_strPSRatio_Max  = d.m_strPSRatio_Max;
    pDoc->m_strPE_Min       = d.m_strPE_Min;
    pDoc->m_strPE_Max       = d.m_strPE_Max;
    pDoc->m_strBeta_Min     = d.m_strBeta_Min;
    pDoc->m_strBeta_Max     = d.m_strBeta_Max;
    pDoc->m_strYield_Min    = d.m_strYield_Min;
    pDoc->m_strYield_Max    = d.m_strYield_Max;
    pDoc->m_strEPSChg_Min   = d.m_strEPSChg_Min;
    pDoc->m_strEPSChg_Max   = d.m_strEPSChg_Max;
    pDoc->m_strGr_Min       = d.m_strGr_Min;
    pDoc->m_strGr_Max       = d.m_strGr_Max;
    pDoc->m_strDPRatio_Min  = d.m_strDPRatio_Min;
    pDoc->m_strDPRatio_Max  = d.m_strDPRatio_Max;
    pDoc->m_strROE_Min      = d.m_strROE_Min;
    pDoc->m_strROE_Max      = d.m_strROE_Max;
    pDoc->m_strDERatio_Min  = d.m_strDERatio_Min;
    pDoc->m_strDERatio_Max  = d.m_strDERatio_Max;
    pDoc->m_strSales_Min    = d.m_strSales_Min;
    pDoc->m_strSales_Max    = d.m_strSales_Max;
    pDoc->m_strMktCap_Min   = d.m_strMktCap_Min;
    pDoc->m_strMktCap_Max   = d.m_strMktCap_Max;
	  pDoc->m_strDowJones     = d.m_strDowJones;
	  pDoc->m_strSP500        = d.m_strSP500;
    pDoc->m_strIndustryGrp  = d.m_strIndustryGrp;
	  pDoc->m_strExchg        = d.m_strExchg;

    SubmitScreeningReq();
  }
}
void CSMView::OnViewViewvaluations() 
{
	if (!m_pValVw) {
		CreateValuationWindow();
	}

	if (m_pValVw)
		THEAPP()->SwitchView(m_pValVw);
  	
}

void CSMView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  OnPortfolioTrade();
}

void CSMView::OnPortfolioGetcompanyfundamentals() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      GetFunda(p);
      --iSelCount;
    }
  }
  else {
	  CSingleLock sLock(&pDoc->m_mutex);
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        GetFunda(p);
      }
      i++;
    }
  }
}

void CSMView::GetFunda(CStkTicker *p)
{
  CSMDoc *pDoc = GetDocument();
  CString strFileName;

  strFileName		=	pDoc->m_strImageLocation;	
  strFileName		+=  p->m_strSymbol;
  strFileName		+=  ".fun";

  CFile f;
  CFileStatus status;
  int bOpen = f.Open(strFileName, CFile::modeRead);

  if( bOpen && f.GetStatus( status ) ) {
    f.Close();
    CTime tCur = CTime::GetCurrentTime();
    if ( status.m_mtime.GetYear() == tCur.GetYear() &&
         status.m_mtime.GetMonth() == tCur.GetMonth() &&
         status.m_mtime.GetDay() == tCur.GetDay() ) {
      if(CreateFundaWindow()) {
        m_pFundaVw->SendMessage(SHOW_FUNDA_FROM_FILE, (WPARAM)(LPCTSTR)p->m_strSymbol, (LPARAM)(LPCTSTR)strFileName);
      }
    }
    else {
      SubmitReqForCoFunda(p);
    }
  }
  else {
    SubmitReqForCoFunda(p);
  }
}

void CSMView::GetValuation(CStkTicker *p)
{
  if (!p) return;

  if ( !m_pValVw ) {
    if (!CreateValuationWindow() ) return;
  }

  CSMDoc *pDoc = GetDocument();
  //if( !p->m_Value.m_bEarnEst ||  !p->m_Value.m_bGrowthRates) {
    SubmitReqForValuation(p);
  //}
  //else {
//    OnViewViewvaluations();
//    m_pValVw->SendMessage(SHOW_VALUATION, (WPARAM)(LPCTSTR)p->m_strSymbol, (LPARAM)p);
 // }
}

void CSMView::GetRGB(CStkTicker *p)
{
  if (!p) return;

  if ( !m_pRGBVw ) {
    if (!CreateRGBWindow() ) return;
  }

  CSMDoc *pDoc = GetDocument();
	/*
	if( !p->m_Value.m_bEarnEst ||  !p->m_Value.m_bGrowthRates) {
    SubmitReqForValuation(p);
  }*/
	if ( p->m_rgb.m_MktCap.GetLength()<=0) SubmitReqForRGB(p);
}

void CSMView::OnUpdatePortfolioGetcompanyfundamentals(CCmdUI* pCmdUI) 
{

	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;

  if ( iSelCount ) {
		  nItem = GetSelectedRows(&p, nItem);
		  if (nItem == -1 || !p ) {
			  pCmdUI->Enable(FALSE);  
        return;
		  }
	  pCmdUI->Enable(!p->m_bStdTicker && !p->m_bMutualFund);  
  }
}




// if pEntryname = NULL, then hangup the connection which matches the 
// entryname in the Doc ( pDoc->m_DUP)
//
// if pEntryname  != NULL then do not hangup if the pEntryName matches the
// the enum
BOOL CSMView::DoHangup(LPCTSTR pEntryName/*=NULL*/)
{
	return TRUE;

#ifdef _DORAS_

    LPRASCONN  lpRasEntry;
    LPRASCONN  lpTemp;
    DWORD cbBuf;
    DWORD cEntry;
    DWORD dwRet;
    UINT  ndx;
    WCHAR  szMessage[256];
	CSMDoc *pDoc = GetDocument();
	BOOL bRet=TRUE;

    cbBuf = sizeof(RASCONN );
    if ((lpRasEntry = ( LPRASCONN  ) malloc((UINT)cbBuf)) != NULL ) 
    {
        lpRasEntry->dwSize = sizeof(RASCONN );
        dwRet = RasEnumConnections( lpRasEntry, &cbBuf, &cEntry );
        if ( dwRet == ERROR_BUFFER_TOO_SMALL )
        {
            if ((lpTemp = ( LPRASCONN  ) realloc ( lpRasEntry, (UINT)cbBuf )) != NULL )
            {
                lpRasEntry = lpTemp;
                dwRet = RasEnumConnections( lpRasEntry, &cbBuf, &cEntry );
            }
            else
            {
                dwRet = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
        else if ( dwRet != 0 ) // other error
        {
            if ( RasGetErrorString( (UINT)dwRet, szMessage, 256 ) != 0 )
                wsprintf( (LPSTR)szMessage, (LPCTSTR)"Error while hanging up the phone." );

            AfxMessageBox((LPSTR)szMessage);
        }

        if ( dwRet == 0 )  // No errors
        {
            for ( ndx = 0; ndx < cEntry; ndx++ ) {
				if ( pEntryName == NULL ) {
					if ( stricmp(lpRasEntry[ndx].szEntryName, pDoc->m_DUP) == 0 )  {
						RasHangUp(lpRasEntry[ndx].hrasconn);
						bRet = TRUE;
					}
				}
				else {
					if ( stricmp(lpRasEntry[ndx].szEntryName, pEntryName))  {
						RasHangUp(lpRasEntry[ndx].hrasconn);
						bRet = TRUE;
					}
					if ( !stricmp(lpRasEntry[ndx].szEntryName, pEntryName))  {
						bRet = FALSE;
						break;
					}


				}
			}
		}

        free( lpRasEntry );
    } 
	return bRet;
#endif

}

void CSMView::OnChartYahooOneDay() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_1_DAY;
    SubmitChartReq_Yahoo(p, YAHOO_1_DAY);
  }
}
void CSMView::OnChartYahoo5Day() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_5_DAY;
    SubmitChartReq_Yahoo(p, YAHOO_5_DAY);
  }
}
void CSMView::OnChartYahoo10Day() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_5_DAY;
    SubmitChartReq_Yahoo(p, YAHOO_10_DAY);
  }
}
void CSMView::OnChartYahoo3Month() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_3_MONTH;
    SubmitChartReq_Yahoo(p, YAHOO_3_MONTH);
  }
	
}

void CSMView::OnChartYahoo6Month() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_6_MONTH;
    SubmitChartReq_Yahoo(p, YAHOO_6_MONTH);
  }

	
}

void CSMView::OnChartYahoo1Year() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_1_YEAR;
    SubmitChartReq_Yahoo(p, YAHOO_1_YEAR);
  }

	
}

void CSMView::OnChartYahoo2Year() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_2_YEAR;
    SubmitChartReq_Yahoo(p, YAHOO_2_YEAR);
  }

	
}

void CSMView::OnChartYahoo5Year() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_5_YEAR;
    SubmitChartReq_Yahoo(p, YAHOO_5_YEAR);
  }

	
}

void CSMView::OnChartYahooMax() 
{
  int nItem=-1;
  CStkTicker *p=NULL;

  while ( TRUE ) {
	  nItem = GetSelectedRows(&p, nItem);
	  if (nItem == -1 || !p ) {
		  break;
	  }
		m_iRange = YAHOO_MAX;
    SubmitChartReq_Yahoo(p, YAHOO_MAX);
  }

}



void CSMView::SubmitChartReq_Yahoo(CStkTicker *p, int iRange)
{
  if ( !p ) return;
	CSMDoc *pDoc = GetDocument();

  CString strURL;
	if ( pDoc->m_bWebSite == CSMDoc::YAHOO) {
		strURL = "http://chart.finance.yahoo.com/z?s=";
		strURL += p->m_strSymbol;
    strURL += pDoc->m_strChartString;
	} else {
	  strURL = "http://stockcharts.com/c-sc/sc?s=";
		strURL += p->m_strSymbol;
    strURL += pDoc->m_strChartString;
	}
  switch(iRange) {
    case YAHOO_1_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=1d" :  "&p=D";
      break;

    case YAHOO_5_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5d" : "&p=D";
      break;

    case YAHOO_10_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5d" : "&p=D";
      break;

    case YAHOO_3_MONTH:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=3m" : "&p=D";
      break;

    case YAHOO_6_MONTH:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=6m" : "&p=D";
      break;
    case YAHOO_1_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=1y&p=e20,e30,m200,m65" : "&p=W";
			break;

    case YAHOO_2_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=2y&p=e40,e60,m200" : "&p=W";
      break;

    case YAHOO_5_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5y&p=m65,m200" : "&p=W";
      break;

    case YAHOO_MAX:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=my&p=e160,e240,m200" : "&p=W";
      break;

    default:
      return;
  }

	if ( pDoc->m_bWebSite == CSMDoc::YAHOO ) {
		strURL += "&l=on&z=l&q=";
		strURL += "c";
		strURL += "&a=m26-12-9,ss,vm&c=";
		strURL += pDoc->m_strCompareWithTicker;
	}
  if(CreateBrowserWindow()) {
    m_pBrowserVw->SendMessage(SHOW_CHART, (WPARAM)(LPCTSTR)strURL, (LPARAM)NULL);
  }
}




void CSMView::OnPortfolioValuation() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      GetValuation(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        GetValuation(p);
      }
      i++;
    }
  }

  OnViewViewvaluations();

}

void CSMView::OnPortfolioRgb()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      GetRGB(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        GetRGB(p);
      }
      i++;
    }
  }

  OnViewRGB();

}

void CSMView::OnValuation() 
{
  OnPortfolioValuation();
}


void CSMView::OnUpdateViewViewvaluations(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(m_pValVw != NULL);
}

void CSMView::OnViewViewbrowser() 
{
  if (!m_pBrowserVw) {
    CreateBrowserWindow();
    m_pBrowserVw->Navigate2((LPCTSTR)"about:blank", 0, NULL);
  }
  else {
    CreateBrowserWindow();
  }

  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
  FillAddressBar();


}

void CSMView::OnUpdateViewViewbrowser(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(m_pBrowserVw != NULL);
}


void CSMView::OnViewRGB()
{
	if (!m_pRGBVw) {
		CreateRGBWindow();
	}
	THEAPP()->SwitchView(m_pRGBVw);
}

void CSMView::OnUpdateViewViewrbg(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(m_pRGBVw != NULL);
}

void CSMView::OnViewscreening() 
{
	if (m_pScreenVw)
		THEAPP()->SwitchView(m_pScreenVw);
}

void CSMView::OnUpdateViewscreening(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pScreenVw != NULL);
}
void CSMView::OnPortfolioGetnews() 
{
  THEAPP()->CheckSerNo(TRUE);

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  switch (pDoc->m_bWebSite)
  {
    case CSMDoc::YAHOO:
//      CWWWMoney *pWWW = new CWWWMoney(this);
      CWWWYahoo *pWWW = new CWWWYahoo(this);
      if ( !pWWW )
        return;
      else 
        pWWW->GetNews();
  }
}

void CSMView::OnUpdatePortfolioGetnews(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CSMView::OnPortfolioSortAlertClosesttolowprice() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.SortItems(CompareFunc, (LPARAM)(CLOSEST_TO_LOW_PRICE));
}

void CSMView::OnPortfolioSortAlertClosesttohighprice() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.SortItems(CompareFunc, (LPARAM)(CLOSEST_TO_HI_PRICE));
	
}
void CSMView::OnViewRefreshvaluation() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();
  if(!pDoc) return;

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      SubmitReqForValuation(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        SubmitReqForValuation(p);
      }
      i++;
    }
  }
}
void CSMView::OnViewRefreshrgb()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();
  if(!pDoc) return;

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
			p->m_rgb.m_MktCap.Empty();
      SubmitReqForRGB(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
				p->m_rgb.m_MktCap.Empty();
        SubmitReqForRGB(p);
      }
      i++;
    }
  }

}


void CSMView::OnPortfolioDelovervalued() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
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

  int iCount = ListCtrl.GetItemCount();
  int iDel=0;
	for(	int idx=0; idx<iCount; idx++ ) {
		lvi.iItem = idx-iDel;
		if(ListCtrl.GetItem(&lvi)) {
			CStkTicker *p = (CStkTicker *) lvi.lParam;
			if ( p ) {
		  sLock.Lock();
		  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
			  CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[i];
			  if ( pTick && pTick->m_strSymbol == p->m_strSymbol && (pTick->m_Value.m_fValPercent>=0 || pTick->m_Value.m_fEstPrice <= 0) ) {
          if ( m_pValVw) m_pValVw->SendMessage(DELVALUATIONTICKER, (WPARAM)(LPCTSTR)pTick->m_strSymbol, NULL);
				  pDoc->SetModifiedFlag(TRUE);
				  pDoc->m_TickerArray.RemoveAt(i);
				  ListCtrl.DeleteItem(lvi.iItem);
				  delete pTick;
          iDel++;
				  break;
			  }
		  }
		  sLock.Unlock();

			}
		}
	}
  OnPopulateList(0,0);

	Invalidate();
  if ( m_pValVw) m_pValVw->SendMessage(REFRESH_VALUATION, 0, 0);
}

void CSMView::OnUpdatePortfolioDelovervalued(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetListCtrl().GetItemCount());
}





void CSMView::OnFileImport() 
{
	CFileDialog dlg( TRUE,_T("TXT"),_T("*.TXT"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,
	                 _T("Text File(*.TXT)|*.TXT|"));

	WCHAR szFn[10000];
	memset(szFn, 0, sizeof(szFn));
	dlg.m_ofn.lpstrFile = szFn;
	dlg.m_ofn.nMaxFile = 10000;

	if( dlg.DoModal() !=IDOK )
	{
		return;
	}

		CString str, empty;
	for (POSITION pos = dlg.GetStartPosition(); pos != NULL; )
	{
		CString szPathName = dlg.GetNextPathName(pos);
		int iPos1 = szPathName.ReverseFind('_');
		int iPos2 = szPathName.ReverseFind('.');
		CString dt = szPathName.Mid(iPos1+1,iPos2-iPos1);
		dt = dt.Left(2) + "/" + dt.Mid(2,2) + "/" + dt.Mid(4,2);

			CString empty;
			CString str = L"";
			CStdioFile fn;
			fn.Open( szPathName, CFile::modeNoTruncate | CFile::shareExclusive | CFile::typeText | CFile::modeRead);
//			CArchive car(&fn, CArchive::load);
			CString lv_szLine;
			CSMDoc *pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			CSingleLock sLock(&pDoc->m_mutex);
			CString strPrice;
			while (fn.ReadString(lv_szLine) == TRUE)
			{
				str = lv_szLine;
				str.TrimLeft();
				str.TrimRight();
				if (str.Find(' ') != -1) {
					strPrice = str.Mid(str.Find(' '));
					str = str.SpanExcluding((LPCTSTR)" ");
					str.TrimLeft();
					str.TrimRight();
					strPrice.TrimLeft();
					strPrice.TrimRight();

				} else {
					strPrice = str.Mid(str.Find('\t')+1);
					str = str.SpanExcluding((LPCTSTR)"\t");
				}
				if ( !FindInArray(str) && !str.IsEmpty() && !InListCtrl(str) && str.Left(1) != "'" && str.Left(1) != "/" ) {
					CStkTicker *p = new CStkTicker;
					p->m_strSymbol = str;
					if ( !strPrice.IsEmpty() && strPrice != str )	
						p->m_dtPicked  = strPrice;
					pDoc->m_TickerArray.Add(p);
				} else {
					CStkTicker *p = InListCtrl(str);
					if (p) {
						p->m_dtPicked = strPrice;
					}
				}
			}
		//fn.Close();
	}
	OnPopulateList(0,0);
}

void CSMView::OnFileImportISM()
{
	// TODO: Add your command handler code here
	CFileDialog dlg( TRUE,_T("ISM"),_T("*.ism"),
	                 OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("Stockmon ISM(*.ISM)|*.ISM|"));

	WCHAR szFn[10000];
	memset(szFn, 0, sizeof(szFn));
	dlg.m_ofn.lpstrFile = szFn;
	dlg.m_ofn.nMaxFile = 10000;
	if( dlg.DoModal() !=IDOK )
	{
		return;
	}

	CString str, empty;
	for (POSITION pos = dlg.GetStartPosition(); pos != NULL; )
	{
		CString szPathName = dlg.GetNextPathName(pos);
		int iPos1 = szPathName.ReverseFind('_');
		int iPos2 = szPathName.ReverseFind('.');
		CString dt = szPathName.Mid(iPos1+1,iPos2-iPos1);
		dt = dt.Left(2) + "/" + dt.Mid(2,2) + "/" + dt.Mid(4,2);


			CFile fn;
			fn.Open( szPathName, CFile::modeRead);
			CArchive car(&fn, CArchive::load);
			CSMDoc *pDoc = GetDocument();
			ASSERT_VALID(pDoc);
			CSingleLock sLock(&pDoc->m_mutex);
			sLock.Lock();

			int nVer;
			car >> nVer;
			car.SetObjectSchema(nVer);
			pDoc->ReadVerZero(car);
			pDoc->ReadVerOne(car);
			pDoc->ReadVerTwo(car);
			pDoc->ReadVerThree(car);
			pDoc->ReadVerFour(car);
			int iSize;
			car >> iSize;


			for ( int i=0; i<iSize; i++) {
				CStkTicker *p = new CStkTicker;
				p->Serialize(car);
				//p->m_dtPicked = dt;
				if ( !pDoc->FindTicker(p->m_strSymbol) )	pDoc->m_TickerArray.Add(p);
			}
			sLock.Unlock();
			fn.Close();
	}
//	delete [] psz;
	OnPopulateList(0,0);
	OnViewRefresh();
}

void CSMView::OnSummaryYahoonysePricegainers() 
{
	GetSummary(SUMMARY_YAHOO_NYSE_PRICE_GAINERS);
}

void CSMView::OnSummaryYahoonyseVolumeleaders() 
{
	GetSummary(SUMMARY_YAHOO_NYSE_VOL_GAINERS);
}

void CSMView::OnSummaryYahoonasdaqVolumeleaders() 
{
	GetSummary(SUMMARY_YAHOO_NASDAQ_VOL_GAINERS);
}

void CSMView::OnSummaryYahoonasdaqPricegainers() 
{
	GetSummary(SUMMARY_YAHOO_NASDAQ_PRICE_GAINERS);
}

void CSMView::OnSummaryYahooamexPricegainers() 
{
	GetSummary(SUMMARY_YAHOO_AMEX_VOL_GAINERS);
}

void CSMView::OnSummaryYahooamexVolumeleaders() 
{
	GetSummary(SUMMARY_YAHOO_AMEX_PRICE_GAINERS);
}

void CSMView::OnSummaryYahooallvolumegainers() 
{
	GetSummary(SUMMARY_YAHOO_NYSE_VOL_GAINERS);
	GetSummary(SUMMARY_YAHOO_NASDAQ_VOL_GAINERS);
	GetSummary(SUMMARY_YAHOO_AMEX_VOL_GAINERS);
}

void CSMView::OnSummaryYahooallpricegainers() 
{
	GetSummary(SUMMARY_YAHOO_NYSE_PRICE_GAINERS);
	GetSummary(SUMMARY_YAHOO_NASDAQ_PRICE_GAINERS);
	GetSummary(SUMMARY_YAHOO_AMEX_PRICE_GAINERS);
}

void CSMView::OnSummaryYahooall() 
{
	OnSummaryYahooallvolumegainers();
	OnSummaryYahooallpricegainers();
}

void CSMView::OnSummaryIndiaallvolumegainers() 
{
	GetSummary(SUMMARY_YAHOO_INDIA_BOM_VOL_GAINERS);
	GetSummary(SUMMARY_YAHOO_INDIA_NAT_VOL_GAINERS);
	GetSummary(SUMMARY_YAHOO_INDIA_CAL_VOL_GAINERS);
	
}

void CSMView::OnSummaryIndiaallpricegainers() 
{
	GetSummary(SUMMARY_YAHOO_INDIA_BOM_PRICE_GAINERS);
	GetSummary(SUMMARY_YAHOO_INDIA_NAT_PRICE_GAINERS);
	GetSummary(SUMMARY_YAHOO_INDIA_CAL_PRICE_GAINERS);
}

void CSMView::OnSummaryWsjall() 
{
	// TODO: Add your command handler code here
	GetSummary(SUMMARY_WSJ_100_NYSE);
	GetSummary(SUMMARY_WSJ_100_NASDAQ);
	GetSummary(SUMMARY_WSJ_100_AMEX);
}

void CSMView::OnSummaryWsjsummary() 
{
	// TODO: Add your command handler code here
	GetSummary(SUMMARY_WSJ_SUMMARY);
	
}

void CSMView::OnChartTypeLine() 
{
	m_cChartType = "l";
	
}

void CSMView::OnUpdateChartTypeLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CSMView::OnChartTypeBar() 
{
	m_cChartType = "b";
	
}

void CSMView::OnUpdateChartTypeBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CSMView::OnChartTypeCandle() 
{
	m_cChartType = "c";
	
}

void CSMView::OnUpdateChartTypeCandle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}



void CSMView::OnPortfolioInittrades()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	sLock.Lock();
	for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[i];
		if ( pTick) {
			if ( pTick->m_Trades.GetCount() <= 0 ) {
				CTradeInf *tf = new CTradeInf();
				tf->m_bBuy=0;
				tf->m_strCommision="11";
				CTime t = CTime::GetCurrentTime();
				tf->m_strDate = t.Format((LPCTSTR)"%m/%d/%y");
				tf->m_strPrice = pTick->m_strLast;
				tf->m_strShares = "100";
				tf->m_strAmount.Format((LPCTSTR)"%9.2f", 100*_wtof((LPCTSTR)pTick->m_strLast)+11);
				pTick->m_Trades.Add(tf);
			}
		}
	}
	sLock.Unlock();

}

void CSMView::OnPortfolioDeletealltrades()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	sLock.Lock();
	for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[i];
		if ( pTick) {
			while ( pTick->m_Trades.GetCount() > 0) {
				delete pTick->m_Trades.GetAt(0);
				pTick->m_Trades.RemoveAt(0);
			}
		}
	}
	sLock.Unlock();

}

void CSMView::OnPortfolioExport()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString strfn = pDoc->GetPathName();
	strfn.Replace((LPCTSTR)"ism", (LPCTSTR)"csv");
	CString cost, profit;
	CString  comm, qty, last, pctProfit;

	CSingleLock sLock(&pDoc->m_mutex);
	CFile fn;
	fn.Open( strfn, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	fn.Write((LPCTSTR)"Ticker", 6);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Company Name", 12);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Bought at", 9);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Quantitiy", 9);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Cost", 4);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Close", 5);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"Profit", 6);
	fn.Write((LPCTSTR)",",1);

	fn.Write((LPCTSTR)"% Profit", 8);

	fn.Write((LPCTSTR)"\r\n", 2);

	sLock.Lock();
	for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		CStkTicker *pTick = (CStkTicker *) pDoc->m_TickerArray[i];
		if ( pTick) {
			fn.Write(pTick->m_strSymbol, pTick->m_strSymbol.GetLength());
			fn.Write((LPCTSTR)",",1);

			fn.Write(pTick->m_strCoName, pTick->m_strCoName.GetLength());
			fn.Write((LPCTSTR)",",1);

			if ( pTick->m_Trades.GetCount()>0) {
				CString strPrice;
				strPrice = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strPrice;
				fn.Write(strPrice, strPrice.GetLength());
			}
			else {
				fn.Write((LPCTSTR)"0", 1);
			}
			fn.Write((LPCTSTR)",",1);


			if ( pTick->m_Trades.GetCount()>0) {
				CString Qty;
				Qty = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strShares;
				fn.Write(Qty, Qty.GetLength());
			}
			else {
				fn.Write((LPCTSTR)"0", 1);
			}
			fn.Write((LPCTSTR)",",1);

			if ( pTick->m_Trades.GetCount()>0) {
				CString cost;
				cost = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strAmount;
				fn.Write(cost, cost.GetLength());
			}
			else {
				fn.Write((LPCTSTR)"0", 1);
			}
			fn.Write((LPCTSTR)",",1);

			fn.Write(pTick->m_strLast, pTick->m_strLast.GetLength());
			fn.Write((LPCTSTR)",",1);

			if ( pTick->m_Trades.GetCount()>0) {
				cost = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strAmount;

				qty = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strShares ;
				comm = ((CTradeInf *)(pTick->m_Trades.GetAt(0)))->m_strCommision ;
				last = pTick->m_strLast ;


				double sold = (_wtof((LPCTSTR)(qty)) * _wtof(LPCTSTR(last))) - _wtof(LPCTSTR(comm));
				profit.Format((LPCTSTR)"$%9.2f", sold - _wtof((LPCTSTR)(cost.Mid(1,cost.GetLength()))));
				pctProfit.Format((LPCTSTR)"%9.2f%", _wtof((LPCTSTR)(profit.Mid(1,cost.GetLength())).TrimLeft())/_wtof((LPCTSTR)(cost.Mid(1,cost.GetLength()))));
				fn.Write(profit, profit.GetLength());
			}
			else {
				fn.Write((LPCTSTR)"0", 1);
			}
			fn.Write((LPCTSTR)",",1);

			if ( pTick->m_Trades.GetCount()>0) {
				fn.Write(pctProfit, pctProfit.GetLength());
			}
			else {
				fn.Write((LPCTSTR)"0", 1);
			}

			fn.Write((LPCTSTR)"\r\n", 2);
		}
	}
	sLock.Unlock();
	fn.Close();

}





void CSMView::OnPortfolioNotes()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString s;
	CString fn = pDoc->GetPathName();
	if ( fn.GetLength() <= 0 ) return;
	fn.Replace((LPCTSTR)"ism", (LPCTSTR)"rtf");
	if ( PathFileExists(fn) ) {
		s = '"';
		s += "C:/Program Files/Windows NT/Accessories/wordpad.exe";
		s += '"';
		s += ' ';
		s += '"';
		s += fn;
		s += '"';
		::WinExec((LPCSTR)s.GetString(), SW_SHOW);
	} else {
		fn.Replace((LPCTSTR)"rtf", (LPCTSTR)"txt");
		if ( PathFileExists(fn) ) {
			s += "notepad.exe";
			s += ' ';
			s += '"';
			s += fn;
			s += '"';
			::WinExec((LPCSTR)s.GetString(), SW_SHOW);
		} else {
			CFile f;
			f.Open(fn, CFile::modeCreate | CFile::modeReadWrite );
			f.Close();
			s += "notepad.exe";
			s += ' ';
			s += '"';
			s += fn;
			s += '"';
			::WinExec((LPCSTR)s.GetString(), SW_SHOW);
		}
	}
}



void CSMView::OnSiteYahoo()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bWebSite = CSMDoc::YAHOO;
	// TODO: Add your command handler code here
}

void CSMView::OnSiteTd()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_bWebSite = CSMDoc::TD;

}

void CSMView::OnPortfolioGettopholdings()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = GetDocument();

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      SubmitReqForTopHolding(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        SubmitReqForTopHolding(p);
      }
      i++;
    }
  }

}
void CSMView::SubmitReqForTopHolding(CStkTicker *pTicker)
{
  if ( !pTicker ) return;

  if ( pTicker->m_bMutualFund) {
	AfxMessageBox((LPCTSTR)"Cannot get Holdings for Mutual Funds");
	return;
  }

  if(pTicker->m_bStdTicker) return;

	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	CString strAddr;
	CString strIden;
	CRequest *pReq=NULL;

	strAddr = "http://";
	strAddr += "finance.yahoo.com/q/hl?s=";
	strAddr += pTicker->m_strSymbol;

  strIden = "TOP_HOLDINGS:";
  strIden += pTicker->m_strSymbol;

  pReq = new CRequest;
	pReq->Init(strAddr, strIden);
  sLock.Lock();
	pDoc->m_ReqArray.Add(pReq);
  sLock.Unlock();
	m_QuotesReq++;

  long l;
  if ( 0 == m_TotThreads ) {
    StartWorkerThread();
  }
	ReleaseSemaphore(m_hWorkEvent, 1, &l);
}
void CSMView::InsertTopHoldings(CString& st)
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);

	//if ( st.Find((LPCTSTR)"Get Quotes for Top 10") <= 0 ) return;

	int iStart,iPos;
	iPos=0;
	iStart=0;
	while ( st.Mid(iPos,1) != "+") iPos++;
	CString s;
	s = st.Mid(iPos-5,st.GetLength());
	iPos = s.Find((LPCTSTR)"=");
	int iPos2 = s.Find((LPCTSTR)"\"");
	s = s.Mid(iPos+1,iPos2-iPos-1);
	
	CString s2;
	while ( s2 = s.Tokenize((LPCTSTR)"+",iStart)){
		if (s2.IsEmpty()) break;
		s2.TrimLeft();
		s2.TrimRight();
		if (s2.Find((LPCTSTR)".") > 0 ) continue;
		if ( !FindInArray(s2) ) {
			CStkTicker *p = new CStkTicker();
			p->m_strSymbol = s2;
			sLock.Lock();

			pDoc->m_TickerArray.Add(p);
			sLock.Unlock();
		}
	}
	OnPopulateList(0,0);

}


void CSMView::OnComparewithSp500()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( pDoc->m_strCompareWithTicker == "%5EGSPC" ) {
		pDoc->m_strCompareWithTicker.Empty();
	} else {
		pDoc->m_strCompareWithTicker = "%5EGSPC";
	}
}

void CSMView::OnComparewithNasdaq()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( pDoc->m_strCompareWithTicker == "%5EIXIC" ) {
		pDoc->m_strCompareWithTicker.Empty();
	} else {
		pDoc->m_strCompareWithTicker = "%5EIXIC";
	}
}

void CSMView::OnComparewithDow()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( pDoc->m_strCompareWithTicker == "%5EDJI" ) {
		pDoc->m_strCompareWithTicker.Empty();
	} else {
		pDoc->m_strCompareWithTicker = "%5EDJI";
	}
}

void CSMView::OnComparewithClear()
{
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_strCompareWithTicker.Empty();
}

void CSMView::OnFileImportTickers()
{
	CFileDialog dlg( TRUE,_T("PDF"),_T("*.*"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER ,
	                 _T("PDF(*.PDF)|*.PDF|"));
	if( dlg.DoModal() !=IDOK )
	{
		return;
	}
	CString path = dlg.GetPathName();
	CString ext = path.Mid(path.Find('.')+1);
	path = path.Left(path.ReverseFind('\\')+1);
	path += "*.";
	path += ext;
	CSMDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSingleLock sLock(&pDoc->m_mutex);
	
	CFileFind finder;
	BOOL bWorking = finder.FindFile(path);
	CString str;
	sLock.Lock();
	while (bWorking) {
		bWorking = finder.FindNextFile();
		str = finder.GetFileName().Left(finder.GetFileName().Find('.'));
		if ( str.Find('_') > 0 ) {
			str = str.Left(str.Find('_'));
		}
		if ( !str.IsEmpty() && !InListCtrl(str) && !pDoc->FindTicker(str)) {
			CStkTicker *p = new CStkTicker;
			p->m_strSymbol = str;
			pDoc->m_TickerArray.Add(p);
		}
	}
	sLock.Unlock();
	OnPopulateList(0,0);
	OnViewRefresh();
}
