#pragma once


// CRGBView view
#define ID_RGB_VIEW 6

#define SHOW_RGBVIEW	            WM_APP+6000
#define REFRESH_RGBVIEW           WM_APP+6001

class CSMView;

class CRGBView : public CListViewEx
{
	DECLARE_DYNCREATE(CRGBView)

protected:
	CRGBView();           // protected constructor used by dynamic creation
	virtual ~CRGBView();
	void Parse();
	CString Get(CString token);
	CString Get(CString token, int idx);

	void Show(CStkTicker *pTicker=NULL);
	void UpdateRow(CStkTicker *p, int iIndex=-1);
	void CRGBView::OnPortfolioDeleteticker();
  void DeleteSelectedItem();
	void OnViewViewbrowser();
	void FillAddressBar();
	void ShowAll();
	void CalcROIC(CStkTicker *p);

	//{{AFX_MSG(CRGBView )
  afx_msg void OnViewquotes();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
public:
	CSMView				*m_pOwner;
	CRGBView (CSMView *pOwner);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGBView )
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewRefreshvaluation();
	afx_msg LRESULT  OnShowRGBView(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnRefreshRGB(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnDeleteTicker(WPARAM wParam, LPARAM lParam);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
														LPARAM lParamSort);

	int GetSelectedRows(CStkTicker **p, int nStartRow);
  CString m_strWebPage;
  CString m_strTicker;

public:
	afx_msg void OnViewRefreshrgb();
	afx_msg void OnViewRefilterrgb();
	afx_msg void OnViewOptions();
};


