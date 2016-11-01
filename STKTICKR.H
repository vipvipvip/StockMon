// StkTickr.h : header file
//

#include "TechChrt.h"


#define VALUE_VERSION 1
/////////////////////////////////////////////////////////////////////////////
// CValueData command target

class CValueData : public CCmdTarget
{
	DECLARE_DYNCREATE(CValueData)

// Attributes
public:
  // Earnings Estimates
  CString m_strMeanEst1;
  CString m_strMeanEst2;
  CString m_strMeanEst3;
  CString m_strMeanEst4;

  CString m_strHiEst1;
  CString m_strHiEst2;
  CString m_strHiEst3;
  CString m_strHiEst4;

  CString m_strLowEst1;
  CString m_strLowEst2;
  CString m_strLowEst3;
  CString m_strLowEst4;

  // Growth Rates
  CString m_strRevGrowth1;
  CString m_strRevGrowth2;

  CString m_strNetIncGrowth1;
  CString m_strNetIncGrowth2;

  CString m_strEPSGrowth1;
  CString m_strEPSGrowth2;

  CString m_strEquityGrowth1;
  CString m_strPE;

  CString m_strProj5YrGrowth;
  float   m_fCGI;

  BOOL m_bEarnEst;
  BOOL m_bGrowthRates;
	float m_max_Sticker;

	//Ver 1 enh
	BOOL m_b_donot_upd_strMeanEst4;
	BOOL m_b_donot_upd_strPE;
	BOOL m_b_donot_upd_strProj5YrGrowth;

  // Results
  float   m_fEstPrice;
  float   m_fBuyBelow;
  float   m_fValPercent;
	float m_FuturePrice;

	// Not saved to ISM File
	float m_Score;

// Operations
public:
  CValueData() {
    m_bEarnEst      = FALSE;
    m_bGrowthRates  = FALSE;
    m_fEstPrice     = 0;
    m_fBuyBelow     = 0;
    m_fValPercent   = 0;
    m_fCGI  = 0;
		m_FuturePrice=0;
		m_b_donot_upd_strMeanEst4 = 0;
		m_b_donot_upd_strPE = 0;
		m_b_donot_upd_strProj5YrGrowth = 0;
    m_nVer = VALUE_VERSION;
		m_Score = 0;

  }
	virtual ~CValueData();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValueData)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nVer;
	// Generated message map functions
	//{{AFX_MSG(CValueData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

  void ReadVerZero(CArchive& ar);
	void ReadVerOne(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////
// CRGBData command target
#define RGB_VERSION 3
class CRGBData : public CCmdTarget
{
	DECLARE_DYNCREATE(CRGBData)
	
// Attributes
public:
	int m_nVer;
	CString m_MktCap;
	CString m_MA50;
	CString m_MA200;
	CString m_ROE;
	CString m_EBITDA;
	CString m_OCF;
	CString m_EV;
  CString m_LCF;
	CString m_Dummy;
	CString m_TotCash;
	CString m_AvgVol_10Day;
	CString m_AvgVol_3Mth;
	CString m_QRG;
	CString m_QEG;
	CString m_NIAC;
	

	// ver 1 addition
	CString m_PE;
	CString m_PB;
	CString m_index;

	// ver 2 addition
	CString m_Debt;
	CString m_SharesOS;
	CString m_EPS;
	CString m_BVS;

	//Ver 3 addition
	CString m_divR;

	// Calculated
	CString m_ROIC;
	float m_ov;
	int m_V1Rank; //not saved to file - calc in Valuation.cpp

// Operations
public:
	virtual ~CRGBData();
	CRGBData() {
		m_nVer = RGB_VERSION;
		m_ROIC = "9999";
		m_V1Rank=0;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGBData)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:

	void ReadVerZero(CArchive& ar);
	void WriteVerZero(CArchive& ar); 

	void ReadVerOne(CArchive& ar);
	void WriteVerOne(CArchive& ar); 

	void ReadVerTwo(CArchive& ar);
	void WriteVerTwo(CArchive& ar); 

	void ReadVerThree(CArchive& ar);
	void WriteVerThree(CArchive& ar); 

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CStkTicker command target

class CStkTicker : public CCmdTarget
{
//	DECLARE_DYNCREATE(CStkTicker)
	// for versioning support
	DECLARE_SERIAL(CStkTicker)

	CStkTicker();           // protected constructor used by dynamic creation

// Attributes
public:
	int m_nVer;
	BOOL m_bStdTicker;
	BOOL m_bAlert;

	CStkTicker(LPCTSTR lpName);
	CStkTicker(CStkTicker& rSrcTicker);

	LV_ITEM	m_lvi;
	CString m_strSymbol;
	CString m_strLast;
	CString m_strChange;
	CString m_strPctChange;
	CString m_strVolume;
	CString m_strHigh;
	CString m_strLow;
	CString m_strLastUpdated;
  CString m_strPrevClose;

	CString m_strAlertHi;
	CString m_strAlertLow;

	BOOL m_bMutualFund;

	// Add for Version 1
	CPtrArray m_Trades;	 // Array of CTradeInf objects

	// Added for Version 1 but not archived. It is calculated while trading
	DWORD m_dwSharesBought;

	// Add for Version 2
	CTechChartOptions m_tcOpt;

	// Add for Version 3
	CString m_strCoName;

	// Added for Version 3 but not archived. 
  BOOL m_bMerge;
  int m_nTechChartsReq;

  CValueData m_Value;

	CString m_StrPctChange;
	CString m_dtPicked;
  
	CRGBData m_rgb;

// Operations
public:
	virtual ~CStkTicker();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStkTicker)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
protected:

	void ReadVerZero(CArchive& ar);

	void WriteVerOne(CArchive& ar);
	void ReadVerOne(CArchive& ar);

	void WriteVerTwo(CArchive& ar);
	void ReadVerTwo(CArchive& ar);

	void WriteVerThree(CArchive& ar);
	void ReadVerThree(CArchive& ar);

	void WriteVerFour(CArchive& ar);
	void ReadVerFour(CArchive& ar);

	void WriteVerFive(CArchive& ar);
	void ReadVerFive(CArchive& ar);

	void WriteVerSix(CArchive& ar);
	void ReadVerSix(CArchive& ar);

	// RGB
	void WriteVerSeven(CArchive& ar);
	void ReadVerSeven(CArchive& ar);

	// Generated message map functions
	//{{AFX_MSG(CStkTicker)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
