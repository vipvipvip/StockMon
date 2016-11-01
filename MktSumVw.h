// MktSumVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMktSumVw view
#define ID_MKT_SUM_VIEW 1

#define SHOW_MKT_SUMMARY		WM_APP+1000

class CSMView;

class CMktSumVw : public CListViewEx
{
protected:

	DECLARE_DYNCREATE(CMktSumVw)
// Attributes
public:
	CSMView				*m_pOwner;

// Operations
public:
	CMktSumVw();           
	CMktSumVw(CSMView *pOwner);           
	virtual ~CMktSumVw();
	void SubmitReqForTechChart(CStkTicker *p)	;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMktSumVw)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList		m_LargeImageList;
	CImageList		m_SmallImageList;
	CBitmap				m_bmLarge, m_bmSmall;
	int						m_nLargeIdx, m_nSmallIdx;
	CPtrArray			m_VolumeArray;
	CPtrArray			m_PctGainersArray;
	CPtrArray			m_PctLosersArray;
	CString				m_strExchg;

	void DisplayQuote(CString& rWebPage);
	void GetData	(CString rWebPage, CPtrArray& rArray);
	void OnPopulateList();
	void EmptyTickers();
	int GetImageIndex( CString& rString );
	int GetExchange( CString& rExchg, const CString& rWebPage);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMktSumVw)
	afx_msg void OnViewViewquotes();
	afx_msg void OnHelpHowtoregister();
	afx_msg void OnPortfolioAddticker();
	afx_msg void OnUpdatePortfolioAddticker(CCmdUI* pCmdUI);
	afx_msg void OnChartsTechnicalcharting();
	afx_msg void OnUpdateChartsTechnicalcharting(CCmdUI* pCmdUI);
	afx_msg void OnSummaryNyse();
	afx_msg void OnSummaryNasdaq();
	afx_msg void OnSummaryAmex();
	//}}AFX_MSG
	afx_msg LRESULT  OnShowMktSummary(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
