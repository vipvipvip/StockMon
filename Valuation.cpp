// Valuation.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
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

#include "Valuation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif
const int SP500_PE = 16;
const float EXP_RET = 15.00; // in %

/////////////////////////////////////////////////////////////////////////////
// CValuationVw 
#define VALUATION_VW_SUBHEADING _T("Settings\\Valuation View")

IMPLEMENT_DYNCREATE(CValuationVw , CListViewEx)

CValuationVw ::CValuationVw (CSMView *pOwner)
{
  ASSERT(pOwner);
  m_pOwner = pOwner;
	m_fMaxScore=1;
}

CValuationVw ::CValuationVw ()
{
	m_fMaxScore=1;
}

CValuationVw ::~CValuationVw ()
{
}

BOOL CValuationVw::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|= LVS_SHOWSELALWAYS | LVS_REPORT | LVS_EDITLABELS;

	return CListViewEx::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CValuationVw , CListViewEx)
	//{{AFX_MSG_MAP(CValuationVw )
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewquotes)
	ON_COMMAND(ID_VIEW_VIEWBROWSER, OnViewViewbrowser)
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(ID_PORTFOLIO_DELETETICKER, OnPortfolioDeleteticker)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PORTFOLIO_ADDTICKER, OnPortfolioAddticker)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_VIEW_REFRESHVALUATION, OnViewRefreshvaluation)
	ON_COMMAND(ID__VALUATION, OnValuation)
	ON_COMMAND(ID_VIEW_REFILTERRGB, OnViewRefilterrgb)

	//}}AFX_MSG_MAP
 	ON_MESSAGE (SHOW_VALUATION, OnShowValuation)
 	ON_MESSAGE (REFRESH_VALUATION, OnRefreshValuation)
 	ON_MESSAGE (DELVALUATIONTICKER, OnDeleteTicker)
	ON_COMMAND(ID_VIEW_REFILTERVALUATION, &CValuationVw::OnViewRefiltervaluation)
	ON_COMMAND(ID_VIEW_SHOWRECOMMENDATIONS, &CValuationVw::OnViewShowrecommendations)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValuationVw  diagnostics

#ifdef _DEBUG
void CValuationVw ::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CValuationVw ::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CValuationVw  message handlers
afx_msg LRESULT  CValuationVw ::OnShowValuation(WPARAM wParam, LPARAM lParam)
{
  m_strTicker = (LPCTSTR)wParam;
  m_strWebPage = (LPCTSTR)lParam;
  Parse();
  Show();
  return 0;
}

afx_msg LRESULT  CValuationVw ::OnRefreshValuation(WPARAM wParam, LPARAM lParam)
{
  ShowAll();
	return 0;
}

afx_msg LRESULT  CValuationVw ::OnDeleteTicker(WPARAM wParam, LPARAM lParam)
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

void CValuationVw ::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	m_strColWidths = THEAPP()->GetProfileString(VALUATION_VW_SUBHEADING, FRM_LHV_COLWIDTH );
  CString strHeadings;
  strHeadings = "Ticker";
  strHeadings +=','           ;
  strHeadings += "Company Name";
  strHeadings +=','           ;
  strHeadings +="EPS" ;
  strHeadings +=','           ;
  strHeadings +="PE" ;
  strHeadings +=','           ;

	strHeadings +="DivR" ;
  strHeadings +=','           ;

	strHeadings +="DivY" ;
  strHeadings +=','           ;

	
	strHeadings +="5Yr Earn.Gr";
	strHeadings +=','           ;
  strHeadings +="Proj 10Yr Price" ;
	strHeadings +=','           ;
  strHeadings +="Sticker Price"  ;
  strHeadings +=','           ;
	strHeadings +="Theo. Price"  ;
  strHeadings +=','           ;
  strHeadings +="MOS"   ;
  strHeadings +=','           ;
  strHeadings +="Last"  ;
  strHeadings +=','           ;
  strHeadings +="Valuation"   ;
  strHeadings +=','           ;
  strHeadings +="FCF/EV";
  strHeadings +=','           ;
  strHeadings +="RGB";
	strHeadings +=','           ;
  strHeadings +="ROIC";
	strHeadings +=','           ;
  strHeadings +="Score";
	strHeadings +=','           ;
  strHeadings +="V1Rank";
	strHeadings +=','           ;
  strHeadings +="V1";
	strHeadings +=','           ;
  strHeadings +="V2";
	strHeadings +=','           ;
  strHeadings +="V3";

  DisplayColumnHeadings(strHeadings);
}

void CValuationVw::OnViewquotes() 
{
	THEAPP()->SwitchView(m_pOwner);		
}

void CValuationVw::OnViewViewbrowser() 
{
  if (!m_pOwner->m_pBrowserVw) {
    m_pOwner->CreateBrowserWindow();
    m_pOwner->m_pBrowserVw->Navigate2((LPCTSTR)"about:blank", 0, NULL);
  }
  else {
    m_pOwner->CreateBrowserWindow();
  }

  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndReBar.ShowWindow(1);
  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndToolBar.ShowWindow(0);
  FillAddressBar();


}
void CValuationVw::FillAddressBar()
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
	      item.pszText = (LPTSTR)(LPCTSTR)p->m_strSymbol;
    	  ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.InsertItem(&item);
			}
		}
	}
	((CMainFrame *)THEAPP()->m_pMainWnd)->Invalidate();
}

void CValuationVw ::OnDestroy() 
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
		strValue += strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( VALUATION_VW_SUBHEADING, FRM_LHV_COLWIDTH, strValue );
	}

	CListViewEx::OnDestroy();

}

void CValuationVw::ParseGR(CString sToken)
{
  CStkTicker *p = m_pOwner->InListCtrl(m_strTicker);
  if (!p) return;
	if ( p->m_Value.m_b_donot_upd_strProj5YrGrowth>0) return;
	CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;
  
	int iLen = m_strWebPage.GetLength();
  if (iLen <= 0 ) return;

  int iPos;
  iPos = m_strWebPage.Find(sToken);
  if ( iPos == -1 ) return;
  iPos += sToken.GetLength();
	while ( iPos < iLen && m_strWebPage[iPos] == ' ') iPos++;

	if ( m_strWebPage.Mid(iPos,3) == "N/A") {
		if ( sToken == "Next 5 Years (per annum)") {
			p->m_Value.m_strProj5YrGrowth = "-1";
		  p->m_Value.m_bGrowthRates = TRUE;
			return;
		} else {
			p->m_Value.m_strProj5YrGrowth.Format((LPCTSTR)"%2.2f", pDoc->GR);
		  p->m_Value.m_bGrowthRates = TRUE;
			return ParseGR((LPCTSTR)"Next 5 Years (per annum)");
		}
	}

  while ( iPos < iLen && !isdigit(m_strWebPage[iPos])) iPos++;

  CString s;
	
  while ( iPos < iLen && m_strWebPage[iPos] != '%') {
    s += m_strWebPage[iPos];
    iPos++;
  }
  s.TrimLeft();
  s.TrimRight();
	if (s=="N/A" || s.GetLength() <= 0) {
		s="-1";
	} 
	//else {
	//	if ( sToken == "Next 5 Years (per annum)" && s != "N/A" && _wtof(s) > pDoc->GR) {
	//		s.Format((LPCTSTR)"%2.2f", 2*pDoc->GR);
	//	}
	//}
	
  p->m_Value.m_strProj5YrGrowth = s;


  p->m_Value.m_bGrowthRates = TRUE;
}

void CValuationVw::ParseEE()
{
  CStkTicker *p = m_pOwner->InListCtrl(m_strTicker);
  if (!p) return;
	if ( p->m_Value.m_b_donot_upd_strMeanEst4>0) return;
  int iLen = m_strWebPage.GetLength();
  if (iLen <= 0 ) return;

  int iPos;
  iPos = m_strWebPage.Find(_T("Year Ago EPS"));
  if ( iPos == -1 ) return;
  for ( int k=0; k<2; k++ ) {
    while ( iPos < iLen && m_strWebPage.Mid(iPos,3) != "N/A" && !isdigit(m_strWebPage[iPos]) && m_strWebPage[iPos] != '-' ) iPos++;
    while ( iPos < iLen && m_strWebPage[iPos] != '\x20') iPos++;
  }
  while ( iPos < iLen && m_strWebPage.Mid(iPos,3) != "N/A" && !isdigit(m_strWebPage[iPos]) && m_strWebPage[iPos] != '-' ) iPos++;      
//  if ( m_strWebPage[iPos-2] == '-') iPos -= 2;

  int iPos2=iPos;
  
  while ( iPos2 < iLen && m_strWebPage[iPos2] != '\x20') iPos2++;
  CString s(m_strWebPage.Mid(iPos, iPos2-iPos) );
  s.TrimLeft();
  s.TrimRight();
//  s = s.Left(1) == '-' ? s.Right(5) : s.Right(4) ;
  s.TrimLeft();


  p->m_Value.m_strMeanEst4 = s;
  p->m_Value.m_bEarnEst = TRUE;

}

void CValuationVw::ParsePE(CString sToken)
{
  CStkTicker *p = m_pOwner->InListCtrl(m_strTicker);
  if (!p) return;
	if ( p->m_Value.m_b_donot_upd_strPE>0) return;

  int iLen = m_strWebPage.GetLength();
  if (iLen <= 0 ) return;

  int iPos;
  iPos = m_strWebPage.Find(sToken);
  if ( iPos == -1 ) return;
  iPos += sToken.GetLength();
	while ( iPos < iLen && m_strWebPage[iPos] == ' ') iPos++;

	

  while ( iPos < iLen && !isdigit(m_strWebPage[iPos])) iPos++;

  CString s;
  while ( iPos < iLen && m_strWebPage[iPos] != ' ') {
    s += m_strWebPage[iPos];
    iPos++;
  }
  s.TrimLeft();
  s.TrimRight();
	if (s=="N/A" || s.GetLength() <= 0 ) s="1";
  p->m_Value.m_strPE = s;


  p->m_Value.m_bGrowthRates = TRUE;
}

void CValuationVw::Parse()
{

//  if ( -1 != m_strWebPage.Find((LPCTSTR)"Historical Growth Rates") ){
    ParseGR(_T("Next 5 Years (per annum)"));

//  }
  
//  if ( -1 != m_strWebPage.Find((LPCTSTR)"Earnings Estimates Summary") ){
    ParseEE();

//  }

		ParsePE(_T("Price/Earnings (avg. for comparison categories)"));
}

float ConvertToNumber(CString str) {
	WCHAR x;
	x = str.Right(1)[0];
	
	switch (x) {
		case 'B':
			return _wtof(str.Left(str.GetLength()-1)) * float(1000000000);
			break;
		case 'K':
			return _wtof(str.Left(str.GetLength()-1)) * float(1000);
			break;
		case 'M':
			return _wtof(str.Left(str.GetLength()-1)) * float(1000000);
			break;
		default:
			return _wtof(str);
	}
}
int Sort_ROE(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_rgb.m_ROE.Left((*a1)->m_rgb.m_ROE.GetLength()-1))   < _wtof((*a2)->m_rgb.m_ROE.Left((*a2)->m_rgb.m_ROE.GetLength()-1)))	//Desc
		n = -1; 
	else if (_wtof((*a1)->m_rgb.m_ROE.Left((*a1)->m_rgb.m_ROE.GetLength()-1))  > _wtof((*a2)->m_rgb.m_ROE.Left((*a2)->m_rgb.m_ROE.GetLength()-1)))
		n = 1; 

	return n;
}

int Sort_ROIC(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_rgb.m_ROIC)   < _wtof((*a2)->m_rgb.m_ROIC))	//Desc
		n = -1; 
	else if (_wtof((*a1)->m_rgb.m_ROIC)  > _wtof((*a2)->m_rgb.m_ROIC))
		n = 1; 

	return n;
}

int Sort_PE(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_rgb.m_PE)   < _wtof((*a2)->m_rgb.m_PE))	//Desc
		n = 1; 
	else if (_wtof((*a1)->m_rgb.m_PE)  > _wtof((*a2)->m_rgb.m_PE))
		n = -1; 

	return n;
}
int Sort_Valuation(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if ((*a1)->m_Value.m_fValPercent   < (*a2)->m_Value.m_fValPercent)	//Desc
		n = 1; 
	else if ((*a1)->m_Value.m_fValPercent  > (*a2)->m_Value.m_fValPercent)
		n = -1; 

	return n;
}

int Sort_PB(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_rgb.m_PB)   < _wtof((*a2)->m_rgb.m_PB))	//Desc
		n = 1; 
	else if (_wtof((*a1)->m_rgb.m_PB)  > _wtof((*a2)->m_rgb.m_PB))
		n = -1; 

	return n;
}

int Sort_GR(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_Value.m_strProj5YrGrowth)   < _wtof((*a2)->m_Value.m_strProj5YrGrowth))	//Desc
		n = -1; 
	else if (_wtof((*a1)->m_Value.m_strProj5YrGrowth)  > _wtof((*a2)->m_Value.m_strProj5YrGrowth))
		n = 1; 

	return n;
}
int Sort_RGB(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (_wtof((*a1)->m_rgb.m_index)   < _wtof((*a2)->m_rgb.m_index))	
		n = -1; 
	else if (_wtof((*a1)->m_rgb.m_index)  > _wtof((*a2)->m_rgb.m_index))
		n = 1; 

	return n;
}

int Sort_FCF_Yield(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (ConvertToNumber((*a1)->m_rgb.m_LCF) / ConvertToNumber((*a1)->m_rgb.m_EV) < ConvertToNumber((*a2)->m_rgb.m_LCF) / ConvertToNumber((*a2)->m_rgb.m_EV))	//Desc
		n = -1; 
	else if (ConvertToNumber((*a1)->m_rgb.m_LCF) / ConvertToNumber((*a1)->m_rgb.m_EV) > ConvertToNumber((*a2)->m_rgb.m_LCF) / ConvertToNumber((*a2)->m_rgb.m_EV))
		n = 1; 

	return n;
}


int Sort_Score(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if ((*a1)->m_Value.m_Score   < (*a2)->m_Value.m_Score)	//Desc
		n = 1; 
	else if ((*a1)->m_Value.m_Score  > (*a2)->m_Value.m_Score)
		n = -1; 

	return n;
}

int Sort_DivY(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 

	if (ConvertToNumber((*a1)->m_rgb.m_divR)/ConvertToNumber((*a1)->m_strLast)  <= ConvertToNumber((*a2)->m_rgb.m_divR)/ConvertToNumber((*a2)->m_strLast))	//Desc
		n = -1; 
	else if (ConvertToNumber((*a1)->m_rgb.m_divR)/ConvertToNumber((*a1)->m_strLast) > ConvertToNumber((*a2)->m_rgb.m_divR)/ConvertToNumber((*a2)->m_strLast))
		n = 1; 

	return n;
}
int Sort_V1Rank(void *p1,void *p2)
{
	short n=0;
	
	CStkTicker **a1 = (CStkTicker **)p1;
	CStkTicker **a2 = (CStkTicker **)p2; 
	float V1, V2;
	V1 = _wtof((*a1)->m_rgb.m_LCF)/ConvertToNumber((*a1)->m_rgb.m_SharesOS) * _wtof((*a1)->m_Value.m_strProj5YrGrowth);
	V2 = _wtof((*a2)->m_rgb.m_LCF)/ConvertToNumber((*a2)->m_rgb.m_SharesOS) * _wtof((*a2)->m_Value.m_strProj5YrGrowth);


	if (V1/_wtof((*a1)->m_strLast) > V2/_wtof((*a2)->m_strLast))	//Desc
		n = 1; 
	else if (V1/_wtof((*a1)->m_strLast) <= V2/_wtof((*a2)->m_strLast))
		n = -1; 

	return n;
}

void CValuationVw::IncrementScore() {
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	CSingleLock sLock(&pDoc->m_mutex);

	int i=0;
	int iNumTickers = pDoc->m_TickerArray.GetSize();

	sLock.Lock();
	i=0;
  while ( i < iNumTickers ) {
		  CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
		  if(p) {
					p->m_Value.m_Score += i+1;
		  }
		  i++;
	}
	sLock.Unlock();
}
void CValuationVw::Set_V1Rank() {
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	CSingleLock sLock(&pDoc->m_mutex);

	int i=0;
	int iNumTickers = pDoc->m_TickerArray.GetSize();
	float V1,V2,V3;
	int r_max=0;

	sLock.Lock();
	i=0;
  while ( i < iNumTickers ) {
		  CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
		  if(p) {
				V1 = _wtof(p->m_rgb.m_LCF)/ConvertToNumber(p->m_rgb.m_SharesOS) * _wtof(p->m_Value.m_strProj5YrGrowth);
				V2 = pDoc->ConvertToNumber(p->m_rgb.m_EV)/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS);
				V3 = pDoc->ConvertToNumber(p->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS);
				//if ( V1/_wtof(p->m_strLast) > 1.0 && V2 > 0){
				if ( V1/_wtof(p->m_strLast) > 1.0 && V2 > 0 && V3/_wtof(p->m_strLast) > 1.0 ){
					p->m_rgb.m_V1Rank += r_max+1;
					r_max = p->m_rgb.m_V1Rank;
				}
				else
					p->m_rgb.m_V1Rank = 0;
		  }
		  i++;
	}
	i=0;
  while ( i < iNumTickers ) {
	  CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
	  if(p) {
			if (p->m_rgb.m_V1Rank > 0 )
				p->m_rgb.m_V1Rank = r_max - p->m_rgb.m_V1Rank + 1;
			else {
				p->m_rgb.m_V1Rank = iNumTickers + i;
			}
		}
	  i++;
	}


	sLock.Unlock();
}

void CValuationVw::Show(CStkTicker *pTicker/*=NULL*/)
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

  if ( !p->m_Value.m_bEarnEst && !p->m_Value.m_bGrowthRates ) return;

  int iRow=0;
  float FutureEPS;
	
	FutureEPS = (float)((float)_wtof(p->m_Value.m_strMeanEst4) * pow(1+(float)_wtof(p->m_Value.m_strProj5YrGrowth)/100,10));

	float fDisc=10.0;
	if ( _wtof(p->m_rgb.m_ROIC)  >= 25.0) {
		fDisc = fDisc * .7;
	} else 	if ( _wtof(p->m_rgb.m_ROIC)  >= 15.0) {
		fDisc = fDisc * .8;
	} else 	if ( _wtof(p->m_rgb.m_ROIC)  >= 10.0) {
		fDisc = fDisc * .9;
	} else 	if ( _wtof(p->m_rgb.m_ROIC)  < 10.0) {
		fDisc = fDisc * 1.2;
	}

	CString s;
	s.Format(_T("%5.2f"), fDisc);
	//p->m_dtPicked  = s;
  p->m_Value.m_FuturePrice = FutureEPS * min(50, min((float)_wtof(p->m_Value.m_strPE), (float)_wtof(p->m_Value.m_strProj5YrGrowth)*2));
  p->m_Value.m_fEstPrice =  p->m_Value.m_FuturePrice/pow(1+fDisc/100,10);

	FutureEPS = (float)((float)_wtof(p->m_Value.m_strMeanEst4) * pow(1+(float)_wtof(p->m_Value.m_strProj5YrGrowth)/100,10));
  //p->m_Value.m_max_Sticker = FutureEPS * min(50,max((float)_wtof(p->m_Value.m_strPE),(float)_wtof(p->m_Value.m_strProj5YrGrowth)*2));
	//p->m_Value.m_max_Sticker = p->m_Value.m_max_Sticker/pow(1+EXP_RET/100,10);
	p->m_Value.m_max_Sticker  = p->m_Value.m_FuturePrice / (pow(1+(float)_wtof(p->m_Value.m_strProj5YrGrowth)/100,10));
  p->m_Value.m_fBuyBelow =  (float)p->m_Value.m_fEstPrice*(.5);

  if ( p->m_Value.m_fBuyBelow > 0 ) {
    p->m_Value.m_fValPercent = (float) (_wtof(pDoc->ConvertToDecimal(p->m_strLast)) - p->m_Value.m_fBuyBelow ) / p->m_Value.m_fBuyBelow;
    p->m_Value.m_fCGI = (float)_wtof(p->m_Value.m_strProj5YrGrowth) / p->m_Value.m_fValPercent ;
    if(p->m_Value.m_fCGI < 0 ) 
      p->m_Value.m_fCGI = (p->m_Value.m_fCGI * -1) + 1000;
  }

  UpdateRow(p);
}

void CValuationVw::UpdateRow(CStkTicker *p, BOOL bRGBFilter)
{
	if (!p)
		return;

	CListCtrl& ListCtrl=GetListCtrl();	
	int i;

	CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	LV_FINDINFO lvf;
	lvf.flags = LVFI_STRING;
	lvf.psz		= (LPCTSTR)p->m_strSymbol;
	i = ListCtrl.FindItem(&lvf);

	if ( i== -1) {
		if ( bRGBFilter==0) {
				i=ListCtrl.GetItemCount();
		} else {
			return;
		}
	}
	LV_ITEM lvi;
	lvi = p->m_lvi;
  lvi.iItem = p->m_lvi.iItem = (i==-1) ? 0 : i;
	lvi.iSubItem=0;
	lvi.pszText	=	(LPTSTR)(LPCTSTR)p->m_strSymbol;
	lvi.lParam = (LPARAM)p;

	if (p->m_Value.m_fValPercent>0)
	{
		if ( _wtof(p->m_strLast) <= p->m_Value.m_fEstPrice) 
				lvi.iImage =  3;
		else {
			if ( _wtof(p->m_strLast) <= p->m_Value.m_max_Sticker) {
				lvi.iImage = 4;
			} else {
				lvi.iImage =  1;
			}
		}
	} else 	if (p->m_Value.m_fValPercent<0) 
	{
		if ( _wtof(p->m_strLast) >=  p->m_Value.m_fEstPrice) 
			if ( _wtof(p->m_strLast) <= p->m_Value.m_max_Sticker) {
				lvi.iImage = 4;
			} else {
				lvi.iImage =  1;
			}
		else
		lvi.iImage = 2;
	} else return;
	pDoc->CalcRGBIndex(p);
	if (_wtof(p->m_rgb.m_index) <= 0) p->m_rgb.m_index=".01";
	pDoc->CalcROIC(p);
	
	if ( p->m_Value.m_fCGI <=0 || _wtof(p->m_rgb.m_index) <=0) {
			ListCtrl.DeleteItem(i);
			ListCtrl.SortItems(CompareFunc, (LPARAM)(10));
			ListCtrl.SendMessage(WM_SETREDRAW,1,0);
			return;
	}
	
	if (bRGBFilter==1) {
		if (!pDoc->bShowRGB(p) ) {
			ListCtrl.DeleteItem(i);
			ListCtrl.SortItems(CompareFunc, (LPARAM)(10));
			ListCtrl.SendMessage(WM_SETREDRAW,1,0);
			return;
		} else {
			pDoc->CalcRGBIndex(p);
		}
	}
	if (bRGBFilter==2) {
		if (!pDoc->bShowValuation(p) ) {
			ListCtrl.DeleteItem(i);
			ListCtrl.SortItems(CompareFunc, (LPARAM)(10));
			ListCtrl.SendMessage(WM_SETREDRAW,1,0);
			return;
		} else {
			pDoc->CalcRGBIndex(p);
		}
	}
		ListCtrl.DeleteItem(i);
		ListCtrl.InsertItem(&lvi);
		CString s;

		p->m_strAlertLow.Format(_T("%.2f"), p->m_Value.m_fBuyBelow>0 ? p->m_Value.m_fBuyBelow : -1);
		AddItem(i, 1, p->m_strCoName);
		AddItem(i, 2, p->m_Value.m_strMeanEst4);
		AddItem(i, 3, p->m_Value.m_strPE);

		AddItem(i, 4, p->m_rgb.m_divR);
		if (_wtof(p->m_rgb.m_divR)>0) s.Format(_T("%5.2f"), _wtof(p->m_rgb.m_divR)/_wtof(p->m_strLast)*100); else s="0";
		AddItem(i, 5, s);

		AddItem(i, 6, p->m_Value.m_strProj5YrGrowth);
		AddItem(i, 7, p->m_Value.m_FuturePrice);
		AddItem(i, 8, p->m_Value.m_fEstPrice);
		AddItem(i, 9, p->m_Value.m_max_Sticker);
		AddItem(i, 10, p->m_Value.m_fBuyBelow);
		AddItem(i, 11, p->m_strLast);
		AddItem(i, 12, p->m_Value.m_fValPercent);
		//AddItem(i, 11, p->m_Value.m_fCGI);
		float fLCF, fEV;
		fLCF = pDoc->ConvertToNumber(p->m_rgb.m_LCF);
		fEV = pDoc->ConvertToNumber(p->m_rgb.m_EV);
		s.Format(_T("%5.2f"), 100 * fLCF / fEV); 
		AddItem(i, 13, s);
		AddItem(i, 14, p->m_rgb.m_index);
		AddItem(i, 15, p->m_rgb.m_ROIC);
		//p->m_Value.m_Score = p->m_Value.m_Score * _wtof(p->m_rgb.m_index) / 100;
		s.Format(_T("%5.2f"), p->m_Value.m_Score / m_fMaxScore * 100);
		AddItem(i, 16, s);
		AddItem(i,17, p->m_rgb.m_V1Rank);
		AddItem(i, 18, _wtof(p->m_rgb.m_LCF)/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS) * _wtof(p->m_Value.m_strProj5YrGrowth) );
		AddItem(i, 19, pDoc->ConvertToNumber(p->m_rgb.m_EV)/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS) );
		AddItem(i, 20, pDoc->ConvertToNumber(p->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p->m_rgb.m_SharesOS) );

}

static int iColOrder[] = {0,0,0, 0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static CSMDoc *pDoc = NULL;

void CValuationVw::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl& ListCtrl=GetListCtrl();
	iColOrder[pNMListView->iSubItem]==0 ? iColOrder[pNMListView->iSubItem]=1 : iColOrder[pNMListView->iSubItem]=0;

	pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	ListCtrl.SortItems(CompareFunc, (LPARAM)(pNMListView->iSubItem));
	
	*pResult = 0;
}

int CALLBACK CValuationVw::CompareFunc(LPARAM lParam1, LPARAM lParam2, 
	LPARAM lParamSort)
{
	CStkTicker *p1 = (CStkTicker *)lParam1;
	CStkTicker *p2 = (CStkTicker *)lParam2;
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

		case 2: // Mean EPS
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_Value.m_strMeanEst4) - _wtof(p2->m_Value.m_strMeanEst4);			
			}
			else {
				dRes = _wtof(p2->m_Value.m_strMeanEst4) - _wtof(p1->m_Value.m_strMeanEst4);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
      break;
		
		case 3: // PE
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_Value.m_strPE) - _wtof(p2->m_Value.m_strPE);			
			}
			else {
				dRes = _wtof(p2->m_Value.m_strPE) - _wtof(p1->m_Value.m_strPE);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
      break;


		case 4: //DivR
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_divR) - _wtof(p2->m_rgb.m_divR);			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_divR) - _wtof(p1->m_rgb.m_divR);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;

			break;
		
		case 5: //DivY
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_divR)/_wtof(p1->m_strLast) - _wtof(p2->m_rgb.m_divR)/_wtof(p2->m_strLast);			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_divR)/_wtof(p2->m_strLast) - _wtof(p1->m_rgb.m_divR)/_wtof(p1->m_strLast);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;

			break;

		case 6: // Earning Growth
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_Value.m_strProj5YrGrowth);			
			}
			else {
				dRes = _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_Value.m_strProj5YrGrowth);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
      break;

		case 7: // 10 Yr Future Price
			if(iColOrder[lParamSort]) {
				dRes = p1->m_Value.m_FuturePrice - p2->m_Value.m_FuturePrice;			
			}
			else {
				dRes = p2->m_Value.m_FuturePrice - p1->m_Value.m_FuturePrice;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
      break;

		case 8: // Sticker Price 
			if(iColOrder[lParamSort]) {
				dRes = p1->m_Value.m_fEstPrice - p2->m_Value.m_fEstPrice;			
			}
			else {
				dRes = p2->m_Value.m_fEstPrice - p1->m_Value.m_fEstPrice;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 9: // Theo. Current Price
			str1 = pDoc->ConvertToDecimal(p1->m_strLast);
			str2 = pDoc->ConvertToDecimal(p2->m_strLast);
			if(iColOrder[lParamSort]) {
				dRes = ((_wtof(str1) - p1->m_Value.m_max_Sticker)  - (_wtof(str2)-p2->m_Value.m_max_Sticker))/_wtof(str2);			
			}
			else {
				dRes = ((_wtof(str2)-p2->m_Value.m_max_Sticker) - (_wtof(str1)-p1->m_Value.m_max_Sticker))/_wtof(str1);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 10: // Buy Below (MOS)
			if(iColOrder[lParamSort]) {
				dRes = p1->m_Value.m_fBuyBelow - p2->m_Value.m_fBuyBelow;			
			}
			else {
				dRes = p2->m_Value.m_fBuyBelow - p1->m_Value.m_fBuyBelow;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;


		case 11: // Latest Quote
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

		case 12: // Val Percent
			if(iColOrder[lParamSort]) {
				dRes = p1->m_Value.m_fValPercent - p2->m_Value.m_fValPercent;			
			}
			else {
				dRes = p2->m_Value.m_fValPercent - p1->m_Value.m_fValPercent;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 13: // Val Percent / Growth
			if(iColOrder[lParamSort]) {
				//dRes = p1->m_Value.m_fCGI - p2->m_Value.m_fCGI;			
				dRes = pDoc->ConvertToNumber(p1->m_rgb.m_LCF) / pDoc->ConvertToNumber(p1->m_rgb.m_EV) - pDoc->ConvertToNumber(p2->m_rgb.m_LCF) / pDoc->ConvertToNumber(p2->m_rgb.m_EV); 
			}
			else {
				//dRes = p2->m_Value.m_fCGI - p1->m_Value.m_fCGI;
				dRes = pDoc->ConvertToNumber(p2->m_rgb.m_LCF) / pDoc->ConvertToNumber(p2->m_rgb.m_EV) - pDoc->ConvertToNumber(p1->m_rgb.m_LCF) / pDoc->ConvertToNumber(p1->m_rgb.m_EV); 
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

	  case 14: // RGB Index
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_index) - _wtof(p2->m_rgb.m_index);			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_index) - _wtof(p1->m_rgb.m_index);			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

	  case 15: // ROIC
			if(iColOrder[lParamSort]) {
				dRes = _wtof(p1->m_rgb.m_ROIC.Left(p1->m_rgb.m_ROIC.GetLength()-1)) - _wtof(p2->m_rgb.m_ROIC.Left(p2->m_rgb.m_ROIC.GetLength()-1));			
			}
			else {
				dRes = _wtof(p2->m_rgb.m_ROIC.Left(p2->m_rgb.m_ROIC.GetLength()-1)) - _wtof(p1->m_rgb.m_ROIC.Left(p1->m_rgb.m_ROIC.GetLength()-1));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 16: // Score
			if(iColOrder[lParamSort]) {
				dRes = p1->m_Value.m_Score - p2->m_Value.m_Score;			
			}
			else {
				dRes = p2->m_Value.m_Score - p1->m_Value.m_Score;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 17: // V1 Rank
			if(iColOrder[lParamSort]) {
				dRes = p1->m_rgb.m_V1Rank - p2->m_rgb.m_V1Rank;			
			}
			else {
				dRes = p2->m_rgb.m_V1Rank - p1->m_rgb.m_V1Rank;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 18: // V1
			if(iColOrder[lParamSort]) {
				dRes =  (_wtof(p1->m_rgb.m_LCF)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_strLast)) - (_wtof(p2->m_rgb.m_LCF)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_strLast));			
			}
			else {
				dRes =  (_wtof(p2->m_rgb.m_LCF)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) - _wtof(p2->m_strLast)) - (_wtof(p1->m_rgb.m_LCF)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) - _wtof(p1->m_strLast));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

		case 19: // v2
			if(iColOrder[lParamSort]) {
				dRes =  (_wtof(p1->m_rgb.m_EV)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS)  / _wtof(p1->m_strLast)) - (_wtof(p2->m_rgb.m_EV)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS) * _wtof(p2->m_Value.m_strProj5YrGrowth) / _wtof(p2->m_strLast));			
			}
			else {
				dRes =  (_wtof(p2->m_rgb.m_EV)/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS)  / _wtof(p2->m_strLast)) - (_wtof(p1->m_rgb.m_EV)/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) * _wtof(p1->m_Value.m_strProj5YrGrowth) / _wtof(p1->m_strLast));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;
		case 20: // v3
			if(iColOrder[lParamSort]) {
				dRes =  (_wtof(p1->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS)  / _wtof(p1->m_strLast)) - (_wtof(p2->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS)  / _wtof(p2->m_strLast));			
			}
			else {
				dRes =  (_wtof(p2->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p2->m_rgb.m_SharesOS)  / _wtof(p2->m_strLast)) - (_wtof(p1->m_rgb.m_LCF)/3/.03/pDoc->ConvertToNumber(p1->m_rgb.m_SharesOS) / _wtof(p1->m_strLast));			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;

	}
	return iRes;
}

void CValuationVw::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
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

void CValuationVw::DeleteSelectedItem()
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
          p->m_Value.m_bEarnEst = FALSE;
          p->m_Value.m_bGrowthRates = FALSE;
        }
      }

			ListCtrl.DeleteItem(nItem);
	}
	Invalidate();
}

void CValuationVw::OnPortfolioDeleteticker() 
{
  DeleteSelectedItem();
}

void CValuationVw::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int nItem=-1;
	CStkTicker *p=NULL;

  if ( -1 != GetSelectedRows(&p, -1) && p) {
	  CValDlg d(p);
	  int ret = d.DoModal();
    if (ret==IDOK) {
	    p->m_Value.m_fBuyBelow    = d.m_fBuyBelow     ;
	    p->m_Value.m_fEstPrice    = d.m_fEstPrice     ;
	    p->m_strLast              = d.m_strLast       ;
	    p->m_Value.m_strMeanEst4  = d.m_strNextYrEPS  ;
	    p->m_strSymbol            = d.m_strSymbol     ;
	    p->m_Value.m_fValPercent  = d.m_fValPercent   ;
      p->m_Value.m_strProj5YrGrowth  = d.m_strProj5YrGr  ;
      p->m_Value.m_fCGI         = d.m_fCGI;
			p->m_Value.m_strPE				= d.m_val_PE;
			p->m_Value.m_b_donot_upd_strPE  = d.m_b_donot_upd_PE;
			p->m_Value.m_b_donot_upd_strMeanEst4 = d.m_b_donot_upd_EPS;
			p->m_Value.m_b_donot_upd_strProj5YrGrowth = d.m_b_donot_upd_Earn_Growth;

      Show(p);
    }
	}
}

int CValuationVw::GetSelectedRows(CStkTicker **p, int nStartRow)
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

void CValuationVw::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_POPUP_MENU))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,point.x, point.y,AfxGetMainWnd()); 
	}
	
}


void CValuationVw::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CListViewEx::OnShowWindow(bShow, nStatus);
  if(bShow) ShowAll();	
  	
}

void CValuationVw::ScoreALL()
{
  if(!m_pOwner) return;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

	//Sort, Rank and calc Score
	CSingleLock sLock(&pDoc->m_mutex);

	int i=0;
	int iNumTickers = pDoc->m_TickerArray.GetSize();

	//Zero out score
	sLock.Lock();
  while ( i < iNumTickers ) {
		  CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray[i];
		  if(p) {
				p->m_Value.m_Score=0;
				p->m_rgb.m_V1Rank = 0;
		  }
		  i++;
	}
	sLock.Unlock();
		qsort((void*)&pDoc->m_TickerArray[0],
						(size_t)pDoc->m_TickerArray.GetSize(), 
						sizeof(CPtrArray *),
						(int(*)(const void *, const void *))Sort_V1Rank);
		
		Set_V1Rank();

	if (1) {
		//Rank by ROIC Desc
		qsort((void*)&pDoc->m_TickerArray[0],
						(size_t)pDoc->m_TickerArray.GetSize(), 
						sizeof(CPtrArray *),
						(int(*)(const void *, const void *))Sort_ROIC);


		IncrementScore();
	}
	

	if (0) {
		//Rank by ROE Desc
		qsort((void*)&pDoc->m_TickerArray[0],
						(size_t)pDoc->m_TickerArray.GetSize(), 
						sizeof(CPtrArray *),
						(int(*)(const void *, const void *))Sort_ROE);


		IncrementScore();
	}
	
	if (1) {
	//Rank by PE Asc
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_PE);


	IncrementScore();

	}
	
	if (0) {
	//Rank by PB Asc
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_PB);


	IncrementScore();

	}
	
	if (0) {
	//Rank by Growth Desc
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_GR);


	IncrementScore();

	}
	if (1) {
	//Rank by FCF/EV
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_FCF_Yield);


	IncrementScore();

	}

	if (1) {
	//Rank by RGB
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_RGB);


	IncrementScore();

	}
	if (1) {
	//Rank by Valuation
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_Valuation);


	IncrementScore();

	}

	if (1) {
	//Rank by Div Yield
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_DivY);

	IncrementScore();

	}

	//Find Max Score to do relative valuation
	qsort((void*)&pDoc->m_TickerArray[0],
		      (size_t)pDoc->m_TickerArray.GetSize(), 
		      sizeof(CPtrArray *),
		      (int(*)(const void *, const void *))Sort_Score);

	CStkTicker *p = (CStkTicker *)pDoc->m_TickerArray.GetAt(0);
	m_fMaxScore = p->m_Value.m_Score;
}

void CValuationVw::ShowAll()
{
	ScoreALL();

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

	ListCtrl.SortItems(CompareFunc, (LPARAM)(10));
	ListCtrl.SendMessage(WM_SETREDRAW,1,0);
//	UpdateWindow();
}


void CValuationVw::OnViewRefreshvaluation() 
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
      m_pOwner->SubmitReqForValuation(p);
      --iSelCount;
    }
  }
  else {
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

void CValuationVw::OnValuation() 
{
  OnViewRefreshvaluation();
}


void CValuationVw::OnPortfolioAddticker() 
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
void CValuationVw::OnViewRefilterrgb()
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
      UpdateRow(p,1);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        UpdateRow(p,1);
      }
      i++;
    }
  }
}


void CValuationVw::OnViewRefiltervaluation()
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
      UpdateRow(p,2);
      --iSelCount;
    }
  }
  else {
	  int iNumTickers = pDoc->m_TickerArray.GetSize();
    int i=0;

	  while ( i < iNumTickers ) {
      p = (CStkTicker *)pDoc->m_TickerArray[i];
      if ( p ) {
        UpdateRow(p,2);
      }
      i++;
    }
  }
}
void CValuationVw::GenRecommendations()
{
	CListCtrl& ListCtrl=GetListCtrl();
	CSMDoc *pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	CTime t = CTime::GetCurrentTime();
	CString strTime = t.Format((LPCTSTR)"%x");

	CString strfn = pDoc->GetPathName();
	strfn.Replace((WCHAR)".ism", (WCHAR)"_Reco.txt");
	strfn.Replace((LPCTSTR)"Reco", strTime + "_Reco");
	strfn.Replace((WCHAR)"/", (WCHAR)"_");
	CFile fn;
	fn.Open( strfn, CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	fn.Write((LPCTSTR)"// ",3);
	fn.Write(strTime, strTime.GetLength());
	fn.Write((LPCTSTR)"\r\n",2);
	CString txt = "// Score (>=80) and Last is 10% < min(V1,V2) OR \r\n";
	fn.Write(txt, txt.GetLength());
	txt = "// RGB >= 5.0 and  Last is 10% < min(V1,V2) OR \r\n";
	fn.Write(txt, txt.GetLength());
	txt = "// Last is 10% < min(V1,V2) OR \r\n";
	fn.Write(txt, txt.GetLength());
	txt = "// V1_Rank > 0 \r\n";
	fn.Write(txt, txt.GetLength());


	fn.Write((LPCTSTR)"\r\n",2);

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
	CStkTicker *p=NULL;

	ListCtrl.SortItems(CompareFunc, (LPARAM)(16));

	float price, fScore, v1, v2, rgb;
	CString strTicker;
	int v1_r;

	for(	int i=0; i<iCount; i++ ) {
		lvi.iItem = i;

		lvi.iSubItem = 16; 
		ListCtrl.GetItem(&lvi);
		fScore = _wtof(lvi.pszText); //Score

		lvi.iSubItem = 0;
		ListCtrl.GetItem(&lvi);
		strTicker = lvi.pszText; // ticker
		strTicker.Trim();

		lvi.iSubItem = 11;
		ListCtrl.GetItem(&lvi);
		price = _wtof(lvi.pszText); // price

		lvi.iSubItem = 14; // RGB
		ListCtrl.GetItem(&lvi);
		rgb = _wtof(lvi.pszText); //RGB

		lvi.iSubItem = 17; // V1 Rank
		ListCtrl.GetItem(&lvi);
		v1_r = _wtof(lvi.pszText); //V1 Rank

		lvi.iSubItem = 18;
		ListCtrl.GetItem(&lvi);
		v1 = _wtof(lvi.pszText); // v1

		lvi.iSubItem = 19;
		ListCtrl.GetItem(&lvi);
		v2 = _wtof(lvi.pszText); // v2

		if (fScore >= 80 && price <= min(v1,v2)*.90) { 
			if ( v1_r > 0 )
				strTicker += "  // 1 & 4 \r\n";
			else
				strTicker += "  // 1\r\n";
			fn.Write(strTicker, strTicker.GetLength());
		} 
		else if (rgb>=5 && price <= min(v1,v2)*.90) { 
			if ( v1_r > 0 )
				strTicker += "  // 2 & 4 \r\n";
			else
				strTicker += "  // 2\r\n";
			fn.Write(strTicker, strTicker.GetLength());
		} 
		else if (price <= min(v1,v2)*.90) { 
			if ( v1_r > 0 )
				strTicker += "  // 3 & 4 \r\n";
			else
				strTicker += "  // 3\r\n";
			fn.Write(strTicker, strTicker.GetLength());
		} 
	}
	fn.Close();
}
void CValuationVw::OnViewShowrecommendations()
{
	
	GenRecommendations();
}
