// SMView.h : interface of the CSMView class
class CInternetThread;
class CStkTicker;

#define POPULATE_LIST								WM_APP+100
#define READ_COMPLETED							WM_APP+200
#define SHOWMSGTEXT                 WM_APP+300
#define DELVALUATIONTICKER          WM_APP+400


#define CLOSEST_TO_LOW_PRICE        10
#define CLOSEST_TO_HI_PRICE         11

#define UNCONDITIONAL_UPDATE  3
class CMktSumVw;
class CScreenVw;
class CFundaVw;
class CBrowserVw;
class CIAccess;
class CBrowserVw;
class CValuationVw;
class CRGBView;

class CSMView : public CListViewEx
{

protected: // create from serialization only
	CString						strTemp;
	CSMView();
	DECLARE_DYNCREATE(CSMView)

// Attributes
public:
	enum {
		SUMMARY_NYSE,
		SUMMARY_NASDAQ,
		SUMMARY_AMEX,

		SUMMARY_YAHOO_NYSE_VOL_GAINERS,
		SUMMARY_YAHOO_NYSE_PRICE_GAINERS,

		SUMMARY_YAHOO_NASDAQ_VOL_GAINERS,
		SUMMARY_YAHOO_NASDAQ_PRICE_GAINERS,

		SUMMARY_YAHOO_AMEX_VOL_GAINERS,
		SUMMARY_YAHOO_AMEX_PRICE_GAINERS,

		SUMMARY_YAHOO_INDIA_BOM_VOL_GAINERS,
		SUMMARY_YAHOO_INDIA_NAT_VOL_GAINERS,
		SUMMARY_YAHOO_INDIA_CAL_VOL_GAINERS,

		SUMMARY_YAHOO_INDIA_BOM_PRICE_GAINERS,
		SUMMARY_YAHOO_INDIA_NAT_PRICE_GAINERS,
		SUMMARY_YAHOO_INDIA_CAL_PRICE_GAINERS,

		SUMMARY_WSJ_100_NYSE,
		SUMMARY_WSJ_100_NASDAQ,
		SUMMARY_WSJ_100_AMEX,

		SUMMARY_WSJ_SUMMARY
	};

  enum {
    YAHOO_1_DAY,
    YAHOO_5_DAY,
		YAHOO_10_DAY,
    YAHOO_3_MONTH,
    YAHOO_6_MONTH,
    YAHOO_1_YEAR,
    YAHOO_2_YEAR,
    YAHOO_5_YEAR,
    YAHOO_MAX

  };

	CSMDoc* GetDocument();
	CPtrArray m_WrkThreadArray;
	BOOL m_bSummaryInProgress;

// Operations
public:
  void SubmitChartReq_Yahoo(CStkTicker *p, int iRange);
  void SubmitReqForChart(CStkTicker *p, int iType);
  void SubmitScreeningReq();
	CStkTicker *InListCtrl( LPCTSTR pTicker );
  void SubmitReqForCoFunda(CStkTicker *pTicker);
  void SubmitReqForValuation(CStkTicker *pTicker);
	void SubmitReqForTopHolding(CStkTicker *pTicker);
	void SubmitReqForRGB(CStkTicker *pTicker);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSMView)
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewFullRowDetails();
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFullRowDetails(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewClientwidthsel();
	afx_msg void OnUpdateViewClientwidthsel(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnViewRefresh();
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewOptions();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPortfolioDeleteticker();
	afx_msg void OnUpdatePortfolioDeleteticker(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioAddticker();
	afx_msg void OnPortfolioUpdateselected();
	afx_msg void OnUpdatePortfolioUpdateselected(CCmdUI* pCmdUI);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSummaryNasdaq();
	afx_msg void OnSummaryNyse();
	afx_msg void OnSummaryAmex();
	afx_msg void OnUpdateSummaryAmex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSummaryNasdaq(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSummaryNyse(CCmdUI* pCmdUI);
	afx_msg void OnViewMktSummary();
	afx_msg void OnUpdateViewMktSummary(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioAddfund();
	afx_msg void OnUpdateViewRefresh(CCmdUI* pCmdUI);
	afx_msg void OnHelpHowtoregister();
	afx_msg void OnPortfolioTrade();
	afx_msg void OnPortfolioScreen();
	afx_msg void OnViewscreening();
	afx_msg void OnUpdateViewscreening(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPortfolioGetcompanyfundamentals();
	afx_msg void OnViewfundamentals();
	afx_msg void OnUpdateViewfundamentals(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePortfolioGetcompanyfundamentals(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioValuation();
	afx_msg void OnViewViewvaluations();
	afx_msg void OnValuation();
	afx_msg void OnUpdateViewViewvaluations(CCmdUI* pCmdUI);
	afx_msg void OnViewViewbrowser();
	afx_msg void OnUpdateViewViewbrowser(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioGetnews();
	afx_msg void OnUpdatePortfolioGetnews(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioSortAlertClosesttolowprice();
	afx_msg void OnPortfolioSortAlertClosesttohighprice();
	afx_msg void OnViewRefreshvaluation();
	afx_msg void OnUpdateViewRefreshvaluation(CCmdUI* pCmdUI);
	afx_msg void OnPortfolioDelovervalued();
	afx_msg void OnUpdatePortfolioDelovervalued(CCmdUI* pCmdUI);
	afx_msg void OnChartYahooOneDay();
	afx_msg void OnChartYahoo5Day();
	afx_msg void OnChartYahoo10Day();
	afx_msg void OnChartYahoo3Month();
	afx_msg void OnChartYahoo6Month();
	afx_msg void OnChartYahoo1Year();
	afx_msg void OnChartYahoo2Year();
	afx_msg void OnChartYahoo5Year();
	afx_msg void OnChartYahooMax();
	afx_msg void OnFileImport();
	afx_msg void OnFileImportISM();
	afx_msg void OnSummaryYahoonysePricegainers();
	afx_msg void OnSummaryYahoonyseVolumeleaders();
	afx_msg void OnSummaryYahoonasdaqVolumeleaders();
	afx_msg void OnSummaryYahoonasdaqPricegainers();
	afx_msg void OnSummaryYahooamexPricegainers();
	afx_msg void OnSummaryYahooamexVolumeleaders();
	afx_msg void OnSummaryYahooallvolumegainers();
	afx_msg void OnSummaryYahooallpricegainers();
	afx_msg void OnSummaryYahooall();
	afx_msg void OnSummaryIndiaallvolumegainers();
	afx_msg void OnSummaryIndiaallpricegainers();
	afx_msg void OnSummaryWsjall();
	afx_msg void OnSummaryWsjsummary();
	afx_msg void OnChartTypeLine();
	afx_msg void OnUpdateChartTypeLine(CCmdUI* pCmdUI);
	afx_msg void OnChartTypeBar();
	afx_msg void OnUpdateChartTypeBar(CCmdUI* pCmdUI);
	afx_msg void OnChartTypeCandle();
	afx_msg void OnUpdateChartTypeCandle(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT  OnPopulateList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnReadCompleted(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()


public:
	BOOL SetViewType(DWORD dwViewType);
	DWORD GetViewType();
  CBrowserVw        *m_pBrowserVw;

protected:
	BOOL DoHangup(LPCTSTR pEntryName=NULL);

	CImageList				m_LargeImageList;
	CImageList				m_SmallImageList;
	BOOL							m_bStateIcons;
	int								m_nCheckedItem;
	int								m_TotThreads;
	CPropertySheet		*m_pPS;
	DWORD							m_QuotesReq;
	CTime							m_time;
	CBitmap						m_bmLarge, m_bmSmall;
	int								m_nLargeIdx, m_nSmallIdx;
	CMktSumVw					*m_pMktSum;
  CScreenVw         *m_pScreenVw;
  CFundaVw          *m_pFundaVw;

  CValuationVw      *m_pValVw;
	CRGBView					*m_pRGBVw;

	HANDLE						m_hWorkEvent;
	UINT							m_nTimerID;
  UINT							m_nNextUpdateTimerID;
	BOOL							m_bAddingFund;
	int								m_iRange;
	CString						m_cChartType; // b=bar, l=line, c=candle

  void MergeTechCharts(CStkTicker *p);

	void DeleteSelectedItem();
	void StartWorkerThread();
	void StopWorkerThread();
	void AddStdTickers( UINT nID );
	void RemoveStdTickers();
	void UpdateRow(CStkTicker *p, int iIndex = -1);
	BOOL CreateSummaryWindow();
  BOOL CreateScreenWindow();
  BOOL CreateFundaWindow();
  BOOL CreateBrowserWindow();
  BOOL CreateValuationWindow();
	BOOL CreateRGBWindow();
	void DoSpecificAlertType();
	BOOL DoAlert();
	BOOL DoAlert(CStkTicker *p );
	BOOL IsUpdateWindow();
	CStkTicker *InsertTicker(CString& rSymbol, CString& rStrLast, 
										CString& rStrChange, CString& rStrPctChange,CString& rStrHigh, 
										CString& rStrLow, CString& rStrVolume,
                    CString& rStrCoName, CString& strLastTraded);


	void GetAllQuotes();
  void GetQuote(CString& rStr);
	void StopTimer(UINT& nID);
	void StartTimers();
	long GetSecsToNextUpdate();
	int GetSelectedRows(CStkTicker **p, int nStartRow=-1);
	void GetSummary(int iID);
  void GetFunda(CStkTicker *p);
  void GetValuation(CStkTicker *p);
	void GetRGB(CStkTicker *p);
  void FillAddressBar();
	void InsertSummaryValues(CString& st);
	void InsertWSJSummaryValues(CString& st);
	void InsertTopHoldings(CString& st);

	CStkTicker *FindInArray(CString& s);

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
														LPARAM lParamSort);

  friend class CWWW;
  friend class CWWWYahoo;
  friend class CIAccess;
  friend class CBrowserVw;
  friend class CValuationVw;
  friend class CMktSumVw;
  friend class CScreenVw;
	friend class CRGBView;

public:
	afx_msg void OnMenu();
	afx_msg void OnPortfolioInittrades();
	afx_msg void OnPortfolioDeletealltrades();
	afx_msg void OnPortfolioExport();
	afx_msg void OnViewRGB();
	afx_msg void OnUpdateViewViewrbg(CCmdUI *pCmdUI);
	afx_msg void OnPortfolioRgb();
	afx_msg void OnPortfolioNotes();
	afx_msg void OnViewRefreshrgb();
public:
	afx_msg void OnSiteYahoo();
public:
	afx_msg void OnSiteTd();
public:
	afx_msg void OnPortfolioGettopholdings();

public:
	afx_msg void OnComparewithSp500();
public:
	afx_msg void OnComparewithNasdaq();
public:
	afx_msg void OnComparewithDow();
public:
	afx_msg void OnComparewithClear();
public:
	afx_msg void OnFileImportTickers();
};

#ifndef _DEBUG  // debug version in RListVw.cpp
inline CSMDoc* CSMView::GetDocument()
{ return (CSMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
