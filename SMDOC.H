// SMDoc.h : interface of the CSMDoc class

class CStkTicker;

class CSMDoc : public CDocument
{
protected: // create from serialization only
	CSMDoc();
	//DECLARE_DYNCREATE(CSMDoc)

	// for versioning support
	DECLARE_SERIAL(CSMDoc)

// Attributes
public:
	enum {
		YAHOO,
    TD,
	};

	CStringArray m_StdTickerArray;
	CPtrArray m_ReqArray;
	CPtrArray m_TickerArray;
	CMutex m_mutex;

	// Options from Update PropertyPage
	BOOL	m_bDisableUpdateonWkends;
	int		m_bAutoUpdates;
	CString	m_strOpenTime;
	CString	m_strCloseTime;
	DWORD m_nInterval;
	int m_nMaxStksInReq;

	// Options from General PropertyPage
	BOOL	m_bConfirmDel;
	BOOL	m_bAutoSaveDoc;
	BOOL	m_bMakeSymbolsUpperCase;
	int		m_DisplayOptions;

	// Options from Proxy PropertyPage
	CString	m_strProxy;
	CString	m_strPort;
	CString	m_DUP;
	BOOL	m_bUseProxy;
	BOOL	m_bHangup;
	CString m_strIP_DBC;
	CString m_strIP_MONEY;

	// Options from Price Alert PropertyPage
	int		m_Freq;
	int		m_AlertType;
	DWORD m_dwSeconds;
	CString m_strWavFile;

	// Options from Chart PropertyPage
	CString	m_strPts;
	CString	m_strType;
	CString m_strImageLocation;
  CString m_strChartString; // Not saved in ISM file. Used by Stockcharts.com & it changes everytime.

  // Stock Screen Criteria
	CString	m_strPrice_Min;
	CString	m_strPrice_Max;
	CString	m_strPBRatio_Min;
	CString	m_strPBRatio_Max;
	CString	m_strPSRatio_Min;
	CString	m_strPSRatio_Max;
	CString	m_strPE_Min;
	CString	m_strPE_Max;
	CString	m_strBeta_Min;
	CString	m_strBeta_Max;
	CString	m_strYield_Min;
	CString	m_strYield_Max;
	CString	m_strEPSChg_Min;
	CString	m_strEPSChg_Max;
	CString	m_strGr_Min;
	CString	m_strGr_Max;
	CString	m_strDPRatio_Min;
	CString	m_strDPRatio_Max;
	CString	m_strROE_Min;
	CString	m_strROE_Max;
	CString	m_strDERatio_Min;
	CString	m_strDERatio_Max;
	CString	m_strSales_Min;
	CString	m_strSales_Max;
	CString	m_strMktCap_Min;
	CString	m_strMktCap_Max;
	CString	m_strDowJones;
	CString	m_strSP500;
	CString	m_strIndustryGrp;
	CString	m_strExchg;

  BOOL m_bWebSite;

	//Pref RGB
	CString m_strROE;

	//S&P Reference
	float ROE;
	float PE;
	float PB;
	float GR;

	//Compare (for Yahoo chart)
	CString m_strCompareWithTicker;

// Operations
public:
	CString ConvertToDecimal( CString rString, int nDec=4  );
	BOOL IsStdTicker(CString& rString);
	void *FindTicker(CString& str);
	CString RemoveChar(CString s, WCHAR c);
	BOOL bShowRGB(CStkTicker *p);
	BOOL bShowValuation(CStkTicker *p);
	float CalcRGBIndex(CStkTicker *p);
	void CalcROIC(CStkTicker *p);
	float ConvertToNumber(CString str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CSMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//protected:
	int m_nVer;
  void EmptyTickers();
	void ReadVerZero(CArchive& ar);
	void ReadVerOne(CArchive& ar);
  void ReadVerTwo(CArchive& ar);
  void ReadVerThree(CArchive& ar);
  void ReadVerFour(CArchive& ar);

// Generated message map functions
protected:
	//{{AFX_MSG(CSMDoc)
	afx_msg void OnFileSendMail();
	afx_msg void OnUpdateFileSendMail(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
