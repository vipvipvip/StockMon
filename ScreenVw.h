#if !defined(AFX_SCREENVW_H__8D52FD72_DDB0_11D0_AFD8_00A024943E2B__INCLUDED_)
#define AFX_SCREENVW_H__8D52FD72_DDB0_11D0_AFD8_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScreenVw.h : header file
//

class CScreenVwData {
public:
  CString m_strTicker;
  CString m_strCompany;
  CString m_strLast;
  CString m_strPE;
  CString m_strYield;
  CString m_strROE;
  CString m_strDE;
  CString m_strEPSChg;
  CString m_strEarnGr;
  CString m_strMktCap;
};

/////////////////////////////////////////////////////////////////////////////
// CScreenVw view
#define ID_SCREEN_VIEW 2

#define SHOW_SCREEN_STKS		WM_APP+2000

class CSMView;

class CScreenVw : public CListViewEx
{
protected:
	DECLARE_DYNCREATE(CScreenVw)
  CPtrArray m_DataArray;

// Attributes
public:
	CSMView				*m_pOwner;

// Operations
public:
	CScreenVw();           // protected constructor used by dynamic creation
	CScreenVw(CSMView *pOwner);           

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenVw)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScreenVw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CScreenVw)
	afx_msg void OnViewViewquotes();
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPortfolioAddticker();
	afx_msg void OnViewRefreshvaluation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT  OnShowScreenedStks(WPARAM wParam, LPARAM lParam);

  void ShowScreenedStocks(CString& rWebPage);
  void ParseScreenedStocksHTML(CString& rWebPage);
  void EmptyDataArray();

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
														LPARAM lParamSort);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENVW_H__8D52FD72_DDB0_11D0_AFD8_00A024943E2B__INCLUDED_)
