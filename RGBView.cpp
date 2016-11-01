// RGBView.cpp : implementation file
//
#include "stdafx.h"
#include "MainFrm.h"
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "SMDoc.h"
#include "BrowserVw.h"

#include "ListVwEx.h"	// base class for CSMView
#include "ui.h"
#include "readmsg.h"
#include "SMView.h"

#include "RGBView.h"
#include ".\rgbview.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CRGBView
#define RGBVIEW_VW_SUBHEADING _T("Settings\\RGB View")

IMPLEMENT_DYNCREATE(CRGBView, CListViewEx)

CRGBView::CRGBView()
{
}

CRGBView::~CRGBView()
{
}
BOOL CRGBView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|= LVS_SHOWSELALWAYS | LVS_REPORT | LVS_EDITLABELS;

	return CListViewEx::PreCreateWindow(cs);
}
BEGIN_MESSAGE_MAP(CRGBView , CListViewEx)
	//{{AFX_MSG_MAP(CRGBView )
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewquotes)
	ON_COMMAND(ID_VIEW_VIEWBROWSER, OnViewViewbrowser)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_PORTFOLIO_DELETETICKER, OnPortfolioDeleteticker)
	//}}AFX_MSG_MAP
 	ON_MESSAGE (SHOW_RGBVIEW, OnShowRGBView)
 	ON_MESSAGE (REFRESH_RGBVIEW, OnRefreshRGB)
	ON_COMMAND(ID_VIEW_REFRESHRGB, OnViewRefreshrgb)
	ON_COMMAND(ID_VIEW_REFILTERRGB, OnViewRefilterrgb)
	ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
	ON_MESSAGE (DELVALUATIONTICKER, OnDeleteTicker)
	ON_COMMAND(ID_VIEW_REFRESHVALUATION, OnViewRefreshvaluation)
END_MESSAGE_MAP()

CRGBView ::CRGBView (CSMView *pOwner)
{
  ASSERT(pOwner);
  m_pOwner = pOwner;
}



// CRGBView diagnostics

#ifdef _DEBUG
void CRGBView::AssertValid() const
{
	CListView::AssertValid();
}

void CRGBView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CRGBView message handlers
afx_msg LRESULT  CRGBView ::OnShowRGBView(WPARAM wParam, LPARAM lParam)
{
  m_strTicker = (LPCTSTR)wParam;
  m_strWebPage = (LPCTSTR)lParam;
	Parse();
	Show();
  return 0;
}
afx_msg LRESULT  CRGBView ::OnRefreshRGB(WPARAM wParam, LPARAM lParam)
{
  ShowAll();
  return 0;
}
void CRGBView::OnViewRefreshvaluation()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
	CSMDoc *pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

  if(!pDoc) return;

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      m_pOwner->SubmitReqForValuation(p);
      --iSelCount;
    }
  }
	else if ( ListCtrl.GetItemCount() > 0 ) {
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
					m_pOwner->SubmitReqForValuation(p);
				}
			}
		}

	} else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
	  int i=0;
	  while ( i < iNumTickers ) {
		  p = (CStkTicker *)pDoc->m_TickerArray[i];
		  if ( p ) {
			m_pOwner->SubmitReqForValuation(p);
		  }
		  i++;
	  }
  }

}

void CRGBView ::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	m_strColWidths = THEAPP()->GetProfileString(RGBVIEW_VW_SUBHEADING, FRM_LHV_COLWIDTH );
  CString strHeadings;
  strHeadings = _T("Ticker");
  strHeadings += _T(',')           ;
  strHeadings += _T( "Company Name");
  strHeadings += _T(','           );
	strHeadings += _T( "Last");
	strHeadings += _T(',')           ;
  strHeadings += _T("Mkt Cap") ;
  strHeadings += _T(',')           ;
  strHeadings += _T("ROE")  ;
  strHeadings += _T(',')           ;
  strHeadings += _T("ROIC")  ;
  strHeadings += _T(',')           ;
  strHeadings += _T("Bond Rel.")   ;
  strHeadings += _T(',')           ;
  strHeadings += _T("EV")  ;
  strHeadings += _T(',')           ;
  strHeadings += _T("CF")   ;
  strHeadings += _T(',')           ;
  strHeadings += _T("Cash");
  strHeadings += _T(',')           ;
  strHeadings += _T("MA - 50");
	strHeadings += _T(',')           ;
	strHeadings += _T("MA - 200");
	strHeadings += _T(',')           ;
	strHeadings += _T("Index");
	strHeadings += _T(',')           ;
	strHeadings += _T("V1");
	strHeadings += _T(',')           ;
	strHeadings += _T("V2");


	
  DisplayColumnHeadings(strHeadings);

}
afx_msg LRESULT  CRGBView ::OnDeleteTicker(WPARAM wParam, LPARAM lParam)
{
  m_strTicker = (LPCTSTR)wParam;

	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_bMakeSymbolsUpperCase) m_strTicker.MakeUpper();
	
	// get item data
	WCHAR szBuff[MAX_PATH];
	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.lParam=NULL;
	lvi.stateMask=0xFFFF;		// get all state flags

	int iCount= ListCtrl.GetItemCount();

	for(	int i=0; i<iCount; i++ ) {
		lvi.iItem = i;
		if(ListCtrl.GetItem(&lvi)) {
			if ( m_strTicker == lvi.pszText) {
				ListCtrl.DeleteItem(i);
			}
		}
	}
  
  ShowAll();
  return 0;
}

void CRGBView::OnViewquotes() 
{
	THEAPP()->SwitchView(m_pOwner);		
}

void CRGBView::OnViewViewbrowser() 
{
  if (!m_pOwner->m_pBrowserVw) {
    m_pOwner->CreateBrowserWindow();
    m_pOwner->m_pBrowserVw->Navigate2(_T("about:blank"), 0, NULL);
  }
  else {
    m_pOwner->CreateBrowserWindow();
  }

  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
  FillAddressBar();


}
void CRGBView::FillAddressBar()
{
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = m_pOwner->GetDocument();
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
	      item.pszText = (LPWSTR)(LPCTSTR)(p->m_strSymbol);
    	  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.InsertItem(&item);
			}
		}
	}
	((CMainFrame *)THEAPP()->m_pMainWnd)->Invalidate();
}
void CRGBView ::OnDestroy() 
{
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
		strValue +=  strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( RGBVIEW_VW_SUBHEADING, FRM_LHV_COLWIDTH, strValue );
	}

	CListViewEx::OnDestroy();

}

void CRGBView::Parse()
{
	CStkTicker *p = m_pOwner->InListCtrl(m_strTicker);
	if (!p) return;
	
	CSMDoc *pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);
	CString cf1, cf2, cf3, cf4, cf5;
	CString cexp1, cexp2, cexp3, cexp4, cexp5;

	if ( m_strWebPage.Find(_T("Key Statistics for")) != - 1) {
		p->m_rgb.m_MktCap = Get(_T("Market Cap"));
		p->m_rgb.m_MA50  = Get(_T("50-Day Moving Average"));
		p->m_rgb.m_MA200  = Get(_T("200-Day Moving Average"));
		p->m_rgb.m_ROE  = Get(_T("Return on Equity"));
		p->m_rgb.m_EBITDA  = Get(_T(" EBITDA"));
		p->m_rgb.m_EV  = Get(_T("Enterprise Value"));
		//p->m_rgb.m_LCF  = Get(_T("Levered Free Cash Flow"));
		p->m_rgb.m_TotCash  = Get(_T("Total Cash"));
		p->m_rgb.m_AvgVol_10Day = Get(_T("Average Volume (10 day)"));
		p->m_rgb.m_AvgVol_3Mth  = Get(_T("Average Volume (3 month)"));
		p->m_rgb.m_QRG					= Get(_T("Qtrly Revenue Growth (yoy)"));
		p->m_rgb.m_QEG					= Get(_T("Qtrly Earnings Growth (yoy)"));
		p->m_rgb.m_NIAC					= Get(_T("Net Income Avl to Common"));

		// ver 1
		p->m_rgb.m_PE						= Get(_T("E (ttm, intraday)"));
		if (p->m_rgb.m_PE=="N/A") p->m_rgb.m_PE="1";

		p->m_rgb.m_PB						= Get(_T("Book (mrq)"));

		// ver 2
		p->m_rgb.m_Debt					= Get(_T("Total Debt (mrq)"));
		p->m_rgb.m_EPS					= Get(_T("Diluted EPS (ttm)"));
		p->m_rgb.m_SharesOS			= Get(_T("Shares Outstanding"));
		p->m_rgb.m_BVS 					= Get(_T("Book Value Per Share (mrq)"));

		pDoc->CalcROIC(p);
		p->m_rgb.m_divR = Get(_T("Forward Annual Dividend Rate"));
		if (p->m_rgb.m_divR=="N/A") p->m_rgb.m_divR="0";

	} else if ( m_strWebPage.Find(_T("Cash Flow for")) != -1 ) {
		// from Yahoo
		cf1 = Get(_T("Total Cash Flow From Operating Activities"),1);
		cf2 = Get(_T("Total Cash Flow From Operating Activities"),2);
		cf3 = Get(_T("Total Cash Flow From Operating Activities"),3);
		cf4 = "0"; //Get(_T("Total Cash Flow From Operating Activities"),4);

		cexp1 = Get(_T("Capital Expenditures"),1);
		cexp2 = Get(_T("Capital Expenditures"),2);
		cexp3 = Get(_T("Capital Expenditures"),3);
		cexp4 = "0"; //Get(_T("Capital Expenditures"),4);
		long f1, f2, f3, f4;
		f1 = _wtof(cf1);
		f2 = _wtof(cf2);
		f3 = _wtof(cf3);
		f4 = _wtof(cf4);

		long exp1,exp2,exp3,exp4;
		exp1 = _wtof(cexp1);
		exp2 = _wtof(cexp2);
		exp3 = _wtof(cexp3);
		exp4 = _wtof(cexp4);

		float CF = (f1+f2+f3+f4+exp1+exp2+exp3+exp4)/3;
		CF = 1000 * CF;
		p->m_rgb.m_LCF.Format(_T("%12.0f"), CF);
		p->m_rgb.m_LCF.Trim();
	} else if (m_strWebPage.Find(_T("Cash from Operating")) != -1 ) {
		// From moneycentral.msn
		cf1 = Get(_T("Cash from Operating Activities"),1);
		cf2 = Get(_T("Cash from Operating Activities"),3);
		cf3 = Get(_T("Cash from Operating Activities"),5);
		cf4 = Get(_T("Cash from Operating Activities"),7);
		cf5 = Get(_T("Cash from Operating Activities"),9);

		cexp1 = Get(_T("Capital Expenditures"),1);
		cexp2 = Get(_T("Capital Expenditures"),3);
		cexp3 = Get(_T("Capital Expenditures"),5);
		cexp4 = Get(_T("Capital Expenditures"),7);
		cexp5 = Get(_T("Capital Expenditures"),9);

		long f1, f2, f3, f4,f5;
		f1 = _wtof(cf1);
		f2 = _wtof(cf2);
		f3 = _wtof(cf3);
		f4 = _wtof(cf4);
		f5 = _wtof(cf5);
		int cnt=0;
		cnt = f1 != 0 ? cnt+1 : cnt;
		cnt = f2 != 0 ? cnt+1 : cnt;
		cnt = f3 != 0 ? cnt+1 : cnt;
		cnt = f4 != 0 ? cnt+1 : cnt;
		cnt = f5 != 0 ? cnt+1 : cnt;

		long exp1,exp2,exp3,exp4,exp5;
		exp1 = -1*_wtof(cexp1);
		exp2 = -1*_wtof(cexp2);
		exp3 = -1*_wtof(cexp3);
		exp4 = -1*_wtof(cexp4);
		exp5 = -1*_wtof(cexp5);

		float CF = (f1+f2+f3+f4+f5+exp1+exp2+exp3+exp4+exp5)/cnt;
		CF = 1000000 * CF;
		p->m_rgb.m_LCF.Format(_T("%12.0f"), CF);
		p->m_rgb.m_LCF.Trim();

	}

}


CString CRGBView::Get(CString token, int idx)
{
  int iLen = m_strWebPage.GetLength();
  if (iLen <= 0 ) return "";
	
  int iPos;
  iPos = m_strWebPage.Find(token);
	int iPos2=iPos;
	bool bNeg;
	if ( iPos != -1 ) {
				
		for (int i=0;i<idx; i++) {
			while ( iPos < iLen && !isdigit(m_strWebPage[iPos])) {
				if (m_strWebPage[iPos]=='-' && !isdigit(m_strWebPage[iPos+1])) return "";	
				iPos++;
			}
			bNeg = m_strWebPage[iPos-1]=='(' ? 1 : 0;
			iPos2=iPos;
			while ( iPos2 < iLen && (isdigit(m_strWebPage[iPos2]) || m_strWebPage[iPos2]==',') ) {
				iPos2++;
			}
			if ( idx-i != 1) iPos=iPos2;
		}
		CString s(m_strWebPage.Mid(iPos, iPos2-iPos) );
		if ( bNeg==1) s = "-" + s;
		CSMDoc *pDoc = m_pOwner->GetDocument();
		s = pDoc->RemoveChar(s, ',');
		s.TrimLeft();
		s.TrimRight();
		return s;

	} else {
		return "";
	}

}
CString CRGBView::Get(CString token)
{
  int iLen = m_strWebPage.GetLength();
  if (iLen <= 0 ) return "";

  int iPos;
  iPos = m_strWebPage.Find(token);
	if ( iPos != -1 ) {
		
		while ( iPos < iLen && m_strWebPage[iPos] != ':' ) iPos++;
		while ( iPos < iLen && m_strWebPage[iPos] != '-' && !isdigit(m_strWebPage[iPos]) && m_strWebPage.Mid(iPos,3) != "N/A" ) iPos++;      

		int iPos2=iPos;
	  
		while ( iPos2 < iLen && ( m_strWebPage[iPos2] == ',' || isdigit(m_strWebPage[iPos2]) || m_strWebPage[iPos2] != '\x20') ) iPos2++;
		CString s(m_strWebPage.Mid(iPos, iPos2-iPos) );
		CSMDoc *pDoc = m_pOwner->GetDocument();
		s = pDoc->RemoveChar(s, ',');
		s.TrimLeft();
		s.TrimRight();
		return s;

	} else {
		return "";
	}
}
void CRGBView::Show(CStkTicker *pTicker/*=NULL*/)
{
  CStkTicker *p=NULL;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

  if ( !pTicker) {
    p = m_pOwner->InListCtrl(m_strTicker);
  }
  else {
    p = pTicker;
  }
  if (!p) return;
	UpdateRow(p);  

}
void CRGBView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CListViewEx::OnShowWindow(bShow, nStatus);
  if(bShow) ShowAll();	
  	
}

void CRGBView::ShowAll()
{
  CWaitCursor r;
  if(!m_pOwner) return;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	CListCtrl& ListCtrl=GetListCtrl();
  ListCtrl.DeleteAllItems();
	ListCtrl.SendMessage(WM_SETREDRAW,0,0);

	CSingleLock sLock(&pDoc->m_mutex);

	int i=0;
	int iNumTickers = pDoc->m_TickerArray.GetSize();

	sLock.Lock();

  while ( i < iNumTickers ) {
		  CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
		  if(p) {
        Show(p);
		  }
		  i++;
	}
	sLock.Unlock();

	ListCtrl.SortItems(CompareFunc, (LPARAM)(11));
	ListCtrl.SendMessage(WM_SETREDRAW,1,0);
//	UpdateWindow();
}

void CRGBView::UpdateRow(CStkTicker *p, int iIndex)
{
	if (!p)
		return;


	CListCtrl& ListCtrl=GetListCtrl();	
	int i;

  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	LV_FINDINFO lvf;
	lvf.flags = LVFI_STRING;
	lvf.psz		= (p->m_strSymbol);
	i = ListCtrl.FindItem(&lvf);
	

  if ( i== -1) i=ListCtrl.GetItemCount();
	LV_ITEM lvi;
	lvi = p->m_lvi;
  lvi.iItem = p->m_lvi.iItem = (i==-1) ? 0 : i;
	lvi.iSubItem=0;
	lvi.pszText	= (LPWSTR)(LPCTSTR)(p->m_strSymbol);
	lvi.lParam = (LPARAM)p;
/*
	BOOL bROE = _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()).GetString() > 0 && _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()).GetString() > _wtof(pDoc->m_strROE);
	BOOL bEbitda = _wtof(p->m_rgb.m_EBITDA.Left(p->m_rgb.m_EBITDA.GetLength()).GetString() > 0;
	BOOL bOCF = _wtof(p->m_rgb.m_EV.Left(p->m_rgb.m_EV.GetLength()).GetString() > 0 || p->m_rgb.m_EV == "N/A";
	BOOL bLCF = _wtof(p->m_rgb.m_LCF.Left(p->m_rgb.m_LCF.GetLength()).GetString() > 0 || p->m_rgb.m_LCF == "N/A";
	BOOL bQRG = _wtof(p->m_rgb.m_QRG.Left(p->m_rgb.m_QRG.GetLength()).GetString() > 0 || p->m_rgb.m_QRG == "N/A";
	BOOL bQEG = _wtof(p->m_rgb.m_QEG.Left(p->m_rgb.m_QEG.GetLength()).GetString() > 0 || p->m_rgb.m_QEG == "N/A";
	BOOL bNIAC = _wtof(p->m_rgb.m_NIAC.Left(p->m_rgb.m_NIAC.GetLength()).GetString() > 0 || p->m_rgb.m_NIAC == "N/A";
	BOOL bShow = bROE  && bEbitda && bOCF & bQRG & bQEG & bNIAC;
*/	
	CString x;
	CString lcf, lcf2, mc,mc2;
	BOOL bShow;
	bShow = pDoc->bShowRGB(p);
	if ( pDoc->m_strROE != '0' ) {
		if (!bShow)  { 
			ListCtrl.DeleteItem(i);
			return;
		}
	}
  
	{
		if (p->m_rgb.m_MktCap.IsEmpty()) return;
		pDoc->CalcRGBIndex(p);

		float rgb = (_wtof(p->m_rgb.m_MA50)/_wtof(p->m_rgb.m_MA200))  -1;
		BOOL bPrice = _wtof(p->m_strLast) > _wtof(p->m_rgb.m_MA50);
		BOOL bVol = (_wtof(p->m_strVolume) > _wtof(p->m_rgb.m_AvgVol_10Day)) || (_wtof(p->m_strVolume) > _wtof(p->m_rgb.m_AvgVol_3Mth )) || (_wtof(p->m_rgb.m_AvgVol_10Day) > _wtof(p->m_rgb.m_AvgVol_3Mth ));
		float fLCF;
		/*if ( p->m_rgb.m_LCF.Right(1)=="B" ) {
			fLCF = _wtof(p->m_rgb.m_LCF.Left(p->m_rgb.m_LCF.GetLength()).GetString()*1000000000;
		} else if (p->m_rgb.m_LCF.Right(1) == "M") {
			fLCF = _wtof(p->m_rgb.m_LCF.Left(p->m_rgb.m_LCF.GetLength()).GetString()*1000000;
		} else {
			fLCF = _wtof(p->m_rgb.m_LCF);
		}
		*/
		fLCF = 1000* _wtof(p->m_rgb.m_LCF);
		if ( p->m_rgb.m_MktCap.Right(1)=="B") {
			lcf.Format(_T("%15.2f"), fLCF);
			//lcf2.Format(_T("%15.2fB"), fLCF/1000000000);
			if(_wtof(p->m_strLast)>0 && p->m_rgb.m_SharesOS.GetLength() > 0) {
				if ( p->m_rgb.m_SharesOS.Right(1)=="B") {
					mc.Format(_T("%15.2f"), _wtof(p->m_strLast)*pDoc->ConvertToNumber(p->m_rgb.m_SharesOS));
					mc2.Format(_T("%15.2fB"),_wtof(mc)/1000000000);
				} else if (p->m_rgb.m_SharesOS.Right(1)=="M") {
					mc.Format(_T("%15.2f"), _wtof(p->m_strLast)*pDoc->ConvertToNumber(p->m_rgb.m_SharesOS));
					mc2.Format(_T("%15.2fB"),_wtof(mc)/1000000);
				}
			}
			else { 
				mc.Format(_T("%15.2f"), pDoc->ConvertToNumber(p->m_rgb.m_MktCap)*1000000);
				mc2.Format(_T("%15.2fB"),_wtof(mc)/1000000);
			}
		}
		if ( p->m_rgb.m_MktCap.Right(1)=="M") {
			lcf.Format(_T("%15.2f"), fLCF);
			//lcf2.Format(_T("%15.2fM"), fLCF/1000000);
			if(_wtof(p->m_strLast)>0 && p->m_rgb.m_SharesOS.GetLength() > 0) {
				if ( p->m_rgb.m_SharesOS.Right(1)=="B") {
					mc.Format(_T("%15.2f"), _wtof(p->m_strLast)*pDoc->ConvertToNumber(p->m_rgb.m_SharesOS));
					mc2.Format(_T("%15.2fM"),_wtof(mc)/1000000000);
				} else if (p->m_rgb.m_SharesOS.Right(1)=="M") {
					mc.Format(_T("%15.2f"), _wtof(p->m_strLast)*pDoc->ConvertToNumber(p->m_rgb.m_SharesOS));
					mc2.Format(_T("%15.2fM"),_wtof(mc)/1000000);
				}
			}
			else { 
				mc.Format(_T("%15.2f"), pDoc->ConvertToNumber(p->m_rgb.m_MktCap)*1000);
				mc2.Format(_T("%15.2fM"),_wtof(mc)/1000);
			}
		}

		
		//Using OCF to store Enterprise Value to calc CF Yield based on
		//http://www.investopedia.com/articles/fundamental-analysis/09/free-cash-flow-yield.asp
		/*
		if(_wtof(lcf)*.05 > 1000000000.0) {
			p->m_rgb.m_EV.Format(_T("%9.0fB"), .05*_wtof(lcf)/1000000000.0);
		} else if(_wtof(lcf)*.05 > 1000000.0){
			p->m_rgb.m_EV.Format(_T("%9.0fM"), .05*_wtof(lcf)/1000.0);
		} else {
			p->m_rgb.m_EV.Format(_T("%9.0f"), .05*_wtof(lcf));
		}
		*/

		CString ov;
		if ( _wtof(lcf) > _wtof(mc) ) {
			ov.Format(_T("-%4.2f"),(_wtof(lcf)/_wtof(mc)-1)*100);
			p->m_rgb.m_ov = (_wtof(lcf)/_wtof(mc)-1)*100;
		} else {
			ov.Format(_T("+%4.2f"),(_wtof(mc)/_wtof(lcf)-1)*100);
			p->m_rgb.m_ov = -1*(_wtof(mc)/_wtof(lcf)-1)*100;
		}
		//p->m_rgb.m_LCF = lcf2.TrimLeft().TrimRight();;

		p->m_rgb.m_MktCap = mc2.TrimLeft().TrimRight();
		lcf2 = lcf2 + " ((LPCTSTR)" + ov + "%)";
	//	lvi.iImage =  bROE  && bPrice && bVol ? 2 : 1;
		lvi.iImage =  _wtof(mc) < _wtof(lcf) ? 2 : 1;
		x.Format(_T("%4.2f (%4.2f%s"), _wtof(p->m_rgb.m_EPS)/.05, _wtof(p->m_rgb.m_EPS)/_wtof(p->m_strLast)*100,_T("%)"));

	}
	ListCtrl.DeleteItem(i);
  ListCtrl.InsertItem(&lvi);

	AddItem(i, 1, p->m_strCoName);
	AddItem(i, 2, p->m_strLast);
  AddItem(i, 3, mc2);
  AddItem(i, 4, p->m_rgb.m_ROE );
  AddItem(i, 5, p->m_rgb.m_ROIC + CString(_T("%")));
  AddItem(i, 6, x);
  AddItem(i, 7, p->m_rgb.m_EV);
  AddItem(i, 8, p->m_rgb.m_LCF);
  AddItem(i, 9, p->m_rgb.m_TotCash);
  AddItem(i, 10, p->m_rgb.m_MA50);
	AddItem(i, 11, p->m_rgb.m_MA200);

/*
//S&P Reference
	float ROE=17.4;
	float PE=17.2;
	float PB=2.9;
	float GR=11;

	// Calc Index
	float index=0;
	float cmp_ROE = _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()).GetString() / ROE;
	float cmp_PE	= _wtof(p->m_rgb.m_PE) / PE;
	float cmp_PB	= _wtof(p->m_rgb.m_PB) / PB;
	float cmp_GR	= _wtof(p->m_Value.m_strProj5YrGrowth) / GR;

	float v_PE	= min(cmp_ROE * PE,min(_wtof(p->m_rgb.m_PE),PE)) ;
	float v_PB	= min(cmp_ROE * PB, min(_wtof(p->m_rgb.m_PB), PB));
	float v_GR	= cmp_ROE<1 ? (1+5*(1-cmp_ROE))*GR/100 : min(_wtof(p->m_Value.m_strProj5YrGrowth),GR);

	index = _wtof(p->m_rgb.m_PE) >= v_PE ? 0 : 1;
	index += _T( _wtof(p->m_rgb.m_PB) >= v_PB ? 0 : 1;
	index += _T( _wtof(p->m_Value.m_strProj5YrGrowth) >= v_GR ? 1 : 0;

	index += _T( v_PE / _wtof(p->m_rgb.m_PE);
	index += _T( v_PB / _wtof(p->m_rgb.m_PB);
	index += _T( min(v_GR / _wtof(p->m_Value.m_strProj5YrGrowth), _wtof(p->m_Value.m_strProj5YrGrowth)/100);

	p->m_rgb.m_index.Format(_T("%2.2f"), index);
*/
	AddItem(i, 12, p->m_rgb.m_index);
	AddItem(i, 13, _wtof(p->m_rgb.m_LCF)/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS) * _wtof(p->m_Value.m_strProj5YrGrowth) );
	AddItem(i, 14, pDoc->ConvertToNumber(p->m_rgb.m_EV)/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS) );

}

int CRGBView::GetSelectedRows(CStkTicker **p, int nStartRow)
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
	CSMDoc *pDoc = m_pOwner->GetDocument();
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


void CRGBView::OnViewRefreshrgb()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if(!pDoc) return;

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      m_pOwner->SubmitReqForRGB(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        m_pOwner->SubmitReqForRGB(p);
      }
      i++;
    }
  }
	}

void CRGBView::OnViewRefilterrgb()
{
	CListCtrl& ListCtrl=GetListCtrl();
	int iSelCount = ListCtrl.GetSelectedCount();
	int nItem=-1;
	CStkTicker *p=NULL;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if(!pDoc) return;

    if ( iSelCount ) {
    while ( iSelCount ) {
      nItem = GetSelectedRows(&p, nItem);
      if (nItem == -1 || !p ) {
        break;
      }
      UpdateRow(p);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        UpdateRow(p);
      }
      i++;
    }
  }
}

void CRGBView::OnViewOptions()
{
	m_pOwner->OnViewOptions();
}

static int iColOrder[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static CSMDoc *pDoc = NULL;

void CRGBView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl& ListCtrl=GetListCtrl();
	iColOrder[pNMListView->iSubItem]==0 ? iColOrder[pNMListView->iSubItem]=1 : iColOrder[pNMListView->iSubItem]=0;

	pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	ListCtrl.SortItems(CompareFunc, (LPARAM)(pNMListView->iSubItem));
	*pResult = 0;
}

int CALLBACK CRGBView::CompareFunc(LPARAM lParam1, LPARAM lParam2, 
	LPARAM lParamSort)
{
	CStkTicker *p1 = (CStkTicker *)lParam1;
	CStkTicker *p2 = (CStkTicker *)lParam2;
	double dRes;
	int iRes=0;
	CString str1, str2;
	float x;
	int i=0;
	if ( !p1 || !p2 )
		return iRes;

	CString mc1, mc2;
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

		case 2: //Last
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

		case 3: // Mkt Cap
			if ( p1->m_rgb.m_MktCap.Right(1)=="B") {
				//mc1.Format("%15.2f"), _wtof(p1->m_rgb.m_MktCap.Left(p1->m_rgb.m_MktCap.GetLength()-1).GetString()) * 1000000.00);
			} else if ( p1->m_rgb.m_MktCap.Right(1)=="M") {
				mc1.Format(_T("%15.2f"), _wtof(p1->m_rgb.m_MktCap.Left(p1->m_rgb.m_MktCap.GetLength()-1).GetString()) * 1000.00);
			}else {
				mc1.Format(_T("%15.2f"),_wtof(p1->m_rgb.m_MktCap.Left(p1->m_rgb.m_MktCap.GetLength()-1).GetString()));
			}

			if ( p2->m_rgb.m_MktCap.Right(1)=="B") {
				mc2.Format(_T("%15.2f"), _wtof(p2->m_rgb.m_MktCap.Left(p2->m_rgb.m_MktCap.GetLength()-1).GetString()) * 1000000.00);
			} else if ( p2->m_rgb.m_MktCap.Right(1)=="M") {
				mc2.Format(_T("%15.2f"), _wtof(p2->m_rgb.m_MktCap.Left(p2->m_rgb.m_MktCap.GetLength()-1).GetString()) * 1000.00);
			}else {
				mc2.Format(_T("%15.2f"),_wtof(p2->m_rgb.m_MktCap.Left(p2->m_rgb.m_MktCap.GetLength()-1).GetString()));
			}

			if(iColOrder[lParamSort]) {
				dRes = _wtof(mc1.GetString()) - _wtof(mc2.GetString());
			}
			else {
				dRes = _wtof(mc2.GetString()) - _wtof(mc1.GetString());
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 4: // ROE
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_ROE.Left(p1->m_rgb.m_ROE.GetLength()-1).GetString()) - _wtof(p2->m_rgb.m_ROE.Left(p2->m_rgb.m_ROE.GetLength()-1).GetString());
			}
			else {
				dRes = _wtof(p2->m_rgb.m_ROE.Left(p2->m_rgb.m_ROE.GetLength()-1).GetString()) - _wtof(p1->m_rgb.m_ROE.Left(p1->m_rgb.m_ROE.GetLength()-1).GetString());
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 5: // ROIC
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_ROIC.Left(p1->m_rgb.m_ROIC.GetLength()-1).GetString()) - _wtof(p2->m_rgb.m_ROIC.Left(p2->m_rgb.m_ROIC.GetLength()-1).GetString());
			}
			else {
				dRes = _wtof(p2->m_rgb.m_ROIC.Left(p2->m_rgb.m_ROIC.GetLength()-1).GetString()) - _wtof(p1->m_rgb.m_ROIC.Left(p1->m_rgb.m_ROIC.GetLength()-1).GetString());
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 6: // EBITDA
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_EPS)/_wtof(p1->m_strLast)*100 - _wtof(p2->m_rgb.m_EPS)/_wtof(p2->m_strLast)*100;
			}
			else {
				dRes = _wtof(p2->m_rgb.m_EPS)/_wtof(p2->m_strLast)*100 - _wtof(p1->m_rgb.m_EPS)/_wtof(p1->m_strLast)*100;
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 7: // EV
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_EV.Left(p1->m_rgb.m_EV.GetLength()).GetString()) - _wtof(p2->m_rgb.m_EV.Left(p2->m_rgb.m_EV.GetLength()).GetString());			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_EV.Left(p2->m_rgb.m_EV.GetLength()).GetString()) - _wtof(p1->m_rgb.m_EV.Left(p1->m_rgb.m_EV.GetLength()).GetString());			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 8: // LCF
			if(iColOrder[lParamSort]) {

				dRes = pDoc->ConvertToNumber(p1->m_rgb.m_LCF) > pDoc->ConvertToNumber(p2->m_rgb.m_LCF) ;
			}
			else {
				dRes = pDoc->ConvertToNumber(p2->m_rgb.m_LCF) > pDoc->ConvertToNumber(p1->m_rgb.m_LCF) ;
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 9: // Cash
			if ( p1->m_rgb.m_TotCash.Right(1)=="B") {
				mc1.Format(_T("%15.2f"), _wtof(p1->m_rgb.m_TotCash.Left(p1->m_rgb.m_TotCash.GetLength()).GetString()) * 1000000);
			} else if ( p1->m_rgb.m_TotCash.Right(1)=="M") {
				mc1.Format(_T("%15.2f"), _wtof(p1->m_rgb.m_TotCash.Left(p1->m_rgb.m_TotCash.GetLength()).GetString()) * 1000);
			}else {
				mc1.Format(_T("%15.2f"),_wtof(p1->m_rgb.m_TotCash.Left(p1->m_rgb.m_TotCash.GetLength()).GetString()));
			}

			//if ( p2->m_rgb.m_TotCash.Right(1)=="B") {
			//	mc2.Format(_T("%15.2f"), _wtof(p2->m_rgb.m_TotCash.Left(p2->m_rgb.m_TotCash.GetLength()).GetString()) * 1000000));
			//} else if ( p2->m_rgb.m_TotCash.Right(1)=="M") {
			//	mc2.Format(_T("%15.2f"), _wtof(p2->m_rgb.m_TotCash.Left(p2->m_rgb.m_TotCash.GetLength()).GetString()) * 1000));
			//}else {
			//	mc2.Format(_T("%15.2f"),_wtof(p2->m_rgb.m_TotCash.Left(p2->m_rgb.m_TotCash.GetLength()).GetString()));
			//}

			if(iColOrder[lParamSort]) {
				dRes = _wtof(mc1) - _wtof(mc2);			
			}
			else {
				dRes = _wtof(mc2) - _wtof(mc1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 10: // MA-50
			str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			str2 = pDoc->ConvertToDecimal(p2->m_strLast);

			//if(iColOrder[lParamSort]) {
			//	dRes = (_wtof(str1)-_wtof(p1->m_rgb.m_MA50.Left(p1->m_rgb.m_MA50.GetLength()).GetString()) - (_wtof(str2)-_wtof(p2->m_rgb.m_MA50.Left(p2->m_rgb.m_MA50.GetLength()).GetString());			
			//}
			//else {
			//	dRes = (_wtof(str2)-_wtof(p2->m_rgb.m_MA50.Left(p2->m_rgb.m_MA50.GetLength()).GetString()) - (_wtof(str1)-_wtof(p1->m_rgb.m_MA50.Left(p1->m_rgb.m_MA50.GetLength()).GetString());			
			//}
			//iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 11: // MA-200
			str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			str2 = pDoc->ConvertToDecimal(p2->m_strLast);
			//if(iColOrder[lParamSort]) {
			//	dRes = (_wtof(str1)-_wtof(p1->m_rgb.m_MA200.Left(p1->m_rgb.m_MA200.GetLength()).GetString()) - (_wtof(str2)-_wtof(p2->m_rgb.m_MA200.Left(p2->m_rgb.m_MA200.GetLength()).GetString());			
			//}
			//else {
			//	dRes = (_wtof(str2)-_wtof(p2->m_rgb.m_MA200.Left(p2->m_rgb.m_MA200.GetLength()).GetString()) - (_wtof(str1)-_wtof(p1->m_rgb.m_MA200.Left(p1->m_rgb.m_MA200.GetLength()).GetString()));			
			//}
			//iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 12: // index
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_index) - _wtof(p2->m_rgb.m_index);			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_index) - _wtof(p1->m_rgb.m_index);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 13: // v1
			if(iColOrder[lParamSort]) {
				dRes =  (_wtof(p1->m_rgb.m_LCF)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_strLast)) - (_wtof(p2->m_rgb.m_LCF)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_strLast));			
			}
			else {
				dRes =  (_wtof(p2->m_rgb.m_LCF)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_strLast)) - (_wtof(p1->m_rgb.m_LCF)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_strLast));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 14: // v1
			if(iColOrder[lParamSort]) {
				dRes =  (_wtof(p1->m_rgb.m_EV)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS)  - _wtof(p1->m_strLast)) - (_wtof(p2->m_rgb.m_EV)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_strLast));			
			}
			else {
				dRes =  (_wtof(p2->m_rgb.m_EV)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS)  - _wtof(p2->m_strLast)) - (_wtof(p1->m_rgb.m_EV)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_strLast));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;
  }
	return iRes;
}
void CRGBView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl& ListCtrl=GetListCtrl();	
	int nItems = ListCtrl.GetItemCount();

	if(ListCtrl.GetSelectedCount())
	{
		if ( nChar == 46  ) {
			// Delete Key pressed
			DeleteSelectedItem();
		}
	}

	CListViewEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRGBView::DeleteSelectedItem()
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
	int nItem;

	for(nItem=ListCtrl.GetNextItem(-1,LVNI_SELECTED);
			nItem!=-1;
			nItem=ListCtrl.GetNextItem(-1,LVNI_SELECTED))
	{
			lvi.iItem = nItem;
			if(ListCtrl.GetItem(&lvi)) {
  			CStkTicker *p = (CStkTicker *) lvi.lParam;
        if (p) {
					p->m_rgb.m_MktCap.Empty();
        }
      }

			ListCtrl.DeleteItem(nItem);
	}
	Invalidate();
}

void CRGBView::OnPortfolioDeleteticker() 
{
  DeleteSelectedItem();
}
