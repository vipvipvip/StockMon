#if !defined(AFX_VALUATION_H__939A0063_3D3C_11D3_8CA1_204C4F4F5020__INCLUDED_)
#define AFX_VALUATION_H__939A0063_3D3C_11D3_8CA1_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Valuation.h : header file
//
#include <afxrich.h>

/////////////////////////////////////////////////////////////////////////////
// CValuationVw  view
#define ID_VALUATION_VIEW 5

#define SHOW_VALUATION		            WM_APP+5000
#define SHOW_VALUATION_FROM_FILE      WM_APP+5001
#define REFRESH_VALUATION             WM_APP+5002

class CSMView;
class CValuationVw  : public CListViewEx
{
protected:
	DECLARE_DYNCREATE(CValuationVw )

// Attributes
public:

// Operations
public:
	CValuationVw ();
	CSMView				*m_pOwner;
	CValuationVw (CSMView *pOwner);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValuationVw )
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CValuationVw ();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void Show(CStkTicker *pTicker=NULL);
	void Parse();
  void ParseGR(CString sToken);
  void ParseEE();
	void ParsePE(CString sToken);
	void UpdateRow(CStkTicker *p, BOOL bRGBFilter=0);
  void DeleteSelectedItem();
  int GetSelectedRows(CStkTicker **p, int nStartRow=-1);
  void ShowAll();
	void OnViewViewbrowser();
	void FillAddressBar();

	CString m_strWebPage;
  CString m_strTicker;

	//Max Score
	float m_fMaxScore;
	
	//{{AFX_MSG(CValuationVw )
  afx_msg void OnViewquotes();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPortfolioDeleteticker();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPortfolioAddticker();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnViewRefreshvaluation();
	afx_msg void OnValuation();
	afx_msg void OnViewRefilterrgb();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT  OnShowValuation(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnRefreshValuation(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnDeleteTicker(WPARAM wParam, LPARAM lParam);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
														LPARAM lParamSort);

public:
	afx_msg void OnViewRefiltervaluation();
	void ScoreALL();
	void IncrementScore();
	void Set_V1Rank();
	void GenRecommendations();
	afx_msg void OnViewShowrecommendations();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALUATION_H__939A0063_3D3C_11D3_8CA1_204C4F4F5020__INCLUDED_)
