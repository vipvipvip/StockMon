#if !defined(AFX_BROWSERVW_H__887EB224_AA92_11D2_B9AA_0060672CD3C5__INCLUDED_)
#define AFX_BROWSERVW_H__887EB224_AA92_11D2_B9AA_0060672CD3C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowserVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowserVw html view
#define ID_BROWSER_VIEW 4

#define SHOW_CHART		        WM_APP+4000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CSMView;

class CBrowserVw : public CHtmlView
{
protected:
	CBrowserVw();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBrowserVw)

// html Data
public:
  CBrowserVw(CSMView *pOwner);
	//{{AFX_DATA(CBrowserVw)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CSMView				*m_pOwner;
// Operations
public:
	int m_iRange;
	CString	m_cChartType; // b=bar, l=line, c=candle

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserVw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBrowserVw();
	void GenReq();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CBrowserVw)
  afx_msg void OnViewViewquotes();
	afx_msg void OnViewRGB();
	afx_msg void OnViewViewvaluations();
	afx_msg void OnBrowserStop();
	afx_msg void OnBrowserBack();
	afx_msg void OnBrowserForward();
	afx_msg void OnBrowserRefresh();
	afx_msg void OnPortfolioGetnews();
	afx_msg void OnViewOptions();
	afx_msg void OnChartYahooOneDay();
	afx_msg void OnChartYahoo5Day();
	afx_msg void OnChartYahoo10Day();
	afx_msg void OnChartYahoo3Month();
	afx_msg void OnChartYahoo6Month();
	afx_msg void OnChartYahoo1Year();
	afx_msg void OnChartYahoo2Year();
	afx_msg void OnChartYahoo5Year();
	afx_msg void OnChartYahooMax();
	afx_msg void OnChartTypeLine();
	afx_msg void OnChartTypeBar();
	afx_msg void OnChartTypeCandle();
	afx_msg void OnViewRefreshvaluation();

	afx_msg void OnPortfolioDeleteticker();
	afx_msg void OnPortfolioAddticker();

public:
	afx_msg void OnComparewithSp500();
public:
	afx_msg void OnComparewithNasdaq();
public:
	afx_msg void OnComparewithDow();
public:
	afx_msg void OnComparewithClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFavorite(UINT nID);
	afx_msg LRESULT  OnShoWCHARt(WPARAM wParam, LPARAM lParam);
	public:
	afx_msg void OnSiteYahoo();
	afx_msg void OnSiteTd();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERVW_H__887EB224_AA92_11D2_B9AA_0060672CD3C5__INCLUDED_)
