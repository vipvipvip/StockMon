// ui.h : header file
//

#include "afxwin.h"
class CSMView;

/////////////////////////////////////////////////////////////////////////////
// CUPdates dialog
class CUPdates : public CPropertyPage
{
	DECLARE_DYNCREATE(CUPdates)

// Construction
public:
	CUPdates();
	~CUPdates();

// Dialog Data
	//{{AFX_DATA(CUPdates)
	enum { IDD = IDD_PREF_UPDATES };
	DWORD	m_nInterval;
	BOOL	m_bDisableUpdateonWkends;
	int		m_bAutoUpdates;
	CString	m_strOpenTime;
	CString	m_strCloseTime;
	int		m_nMaxStksInReq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUPdates)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUPdates)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CGeneralOptions dialog

class CGeneralOptions : public CPropertyPage
{
	DECLARE_DYNCREATE(CGeneralOptions)

// Construction
public:
	CGeneralOptions();
	~CGeneralOptions();

// Dialog Data
	//{{AFX_DATA(CGeneralOptions)
	enum { IDD = IDD_PREF_GENERAL };
	BOOL	m_bConfirmDel;
	BOOL	m_bAutoSaveDoc;
	BOOL	m_bMakeSymbolsUpperCase;
	int		m_DisplayOptions;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGeneralOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGeneralOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CConfirmDelDlg dialog

class CConfirmDelDlg : public CDialog
{
// Construction
public:
	CConfirmDelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfirmDelDlg)
	enum { IDD = IDD_CONFIRM_DEL_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfirmDelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfirmDelDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CProxyDlg dialog

class CProxyDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CProxyDlg)

// Construction
public:
	CProxyDlg();
	~CProxyDlg();

// Dialog Data
	//{{AFX_DATA(CProxyDlg)
	enum { IDD = IDD_PREF_PROXY };
	CComboBox	m_pLBox;
	CString	m_strProxy;
	CString	m_strPort;
	CString	m_DUP;
	int		m_bUseProxy;
	BOOL	m_bHangup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CProxyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CProxyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewconn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CSetAlertDlg dialog

class CSetAlertDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetAlertDlg)

// Construction
public:
  CSMView *m_pParent;
	CPtrArray m_TickerArray;
	BOOL m_bFractions;
	CSMDoc *m_pDoc;
  CString m_strTicker;
	CSetAlertDlg();   
	CSetAlertDlg(CPtrArray& rPortfolio, CSMDoc *pDoc, CString& rTicker, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetAlertDlg)
	enum { IDD = IDD_SET_ALERT_DLG };
	CListBox	m_LB;
	CString	m_strAlertLow;
	CString	m_strAlertHi;
	CString	m_strLast;
	CString	m_strChange;
	CString	m_strHigh;
	CString	m_strLow;
	CString	m_strVolume;
	CString	m_strLastUpdated;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetAlertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetAlertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSymbols();
	afx_msg void OnApplyAlert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CConfigAlertDlg dialog

class CConfigAlertDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfigAlertDlg)

// Construction
public:
	CConfigAlertDlg();
	~CConfigAlertDlg();

// Dialog Data
	//{{AFX_DATA(CConfigAlertDlg)
	enum { IDD = IDD_CONFIG_ALERT_DLG };
	int		m_Freq;
	int		m_AlertType;
	DWORD	m_dwSeconds;
	CString	m_strWAVFile;
	//}}AFX_DATA
	CString m_strWavFile;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfigAlertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigAlertDlg)
	afx_msg void OnSelectWavFile();
	afx_msg void OnAlertPlayWav();
	afx_msg void OnAlertBeep();
	afx_msg void OnAlertFlashWnd();
	afx_msg void OnAlertNoAlert();
	afx_msg void OnAlertWndTop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CChartPrefDlg dialog

class CChartPrefDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CChartPrefDlg)

// Construction
public:
	CChartPrefDlg();
	~CChartPrefDlg();

// Dialog Data
	//{{AFX_DATA(CChartPrefDlg)
	enum { IDD = IDD_PREF_CHART_DLG };
	CString	m_strPts;
	CString	m_strType;
	CString m_strImageLocation;
	CString m_strChartString;
  //}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChartPrefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChartPrefDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
};
/////////////////////////////////////////////////////////////////////////////
// CRegInsDlg dialog

class CRegInsDlg : public CDialog
{
// Construction
public:
	CRegInsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegInsDlg)
	enum { IDD = IDD_REGISTER_DLG };
	CString	m_strInst;
	CString	m_strRegKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegInsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegInsDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CTradeDlg dialog

class CTradeDlg : public CDialog
{
// Construction
public:
	CPtrArray m_TickerArray;
	CSMDoc *m_pDoc;

	CTradeDlg(CWnd* pParent = NULL);   // standard constructor
	CTradeDlg(CPtrArray& rPortfolio, CSMDoc *pDoc, CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CTradeDlg)
	enum { IDD = IDD_TRADE_DLG };
	CButton	m_rApply;
	CEdit	m_rCommisions;
	CEdit	m_rShares;
	CEdit	m_rPrice;
	CEdit	m_rDate;
	CListBox	m_LB;
	CString	m_strLast;
	CString	m_strChange;
	CString	m_strVolume;
	CString	m_strDayhi;
	CString	m_strDaylow;
	CString	m_strDate;
	CString	m_strPrice;
	CString	m_strShares;
	CString	m_strCommision;
	CString	m_strAmount;
	int		m_bBuy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTradeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void CalcAmount();
	CStkTicker *GetSelectedTickerDataFromLB();

	// Generated message map functions
	//{{AFX_MSG(CTradeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePortfolio();
	afx_msg void OnBuy();
	afx_msg void OnSell();
	afx_msg void OnApply();
	afx_msg void OnDblclkPortfolio();
	afx_msg void OnChangePrice();
	afx_msg void OnChangeShares();
	afx_msg void OnChangeCommision();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CTrdDet dialog

class CTrdDet : public CDialog
{
// Construction
public:
	CPtrArray m_TickerArray;
	int m_iIndex;
	CString m_strSymbol;
	CSMDoc *m_pDoc;

	CTrdDet(CWnd* pParent = NULL);   // standard constructor
	CTrdDet(CPtrArray& rPortfolio, CSMDoc *pDoc, int iIndex=-1, CWnd* pParent = NULL);   // standard constructor
	CTrdDet(CPtrArray& rPortfolio, CSMDoc *pDoc, LPCTSTR lpSymbol=NULL, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CTrdDet)
	enum { IDD = IDD_TRADE_DETAILS_DLG };
	CListCtrl	m_ListCtrl;
	CListBox	m_LB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrdDet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowData(CStkTicker *p);
	void DeleteSelectedItem();
	CStkTicker *GetSelectedTickerDataFromLB();
	void RemoveTrade(CTradeInf *pTrade);
	void Transact();
	void CalcGain(CStkTicker *p);

	// Generated message map functions
	//{{AFX_MSG(CTrdDet)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePortfolio();
	afx_msg void OnKeydownTradeDtls(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkPortfolio();
	afx_msg void OnTrade();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CStkScreenDlg dialog

class CStkScreenDlg : public CDialog
{
// Construction
public:
	CStkScreenDlg(CWnd* pParent = NULL);   // standard constructor
	CStkScreenDlg(CSMDoc *pDoc, CWnd* pParent = NULL);   

	CSMDoc *m_pDoc;

// Dialog Data
	//{{AFX_DATA(CStkScreenDlg)
	enum { IDD = IDD_STK_SCREEN_DLG };
	CComboBox	m_rIGroup;
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
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStkScreenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


  // Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStkScreenDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CValDlg dialog

class CValDlg : public CDialog
{
// Construction
public:
	CValDlg(CStkTicker *pTicker, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CValDlg)
	enum { IDD = IDD_VALUATION_DLG };
	float	m_fBuyBelow;
	float	m_fEstPrice;
	CString	m_strLast;
	CString	m_strNextYrEPS;
	CString	m_strSymbol;
	float	m_fValPercent;
	CString	m_strProj5YrGr;
	float	m_fCGI;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  CStkTicker *m_pTicker;
	// Generated message map functions
	//{{AFX_MSG(CValDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_b_donot_upd_PE;
public:
	BOOL m_b_donot_upd_EPS;
public:
	BOOL m_b_donot_upd_Earn_Growth;
public:
	CString m_val_PE;
};

#pragma once


// CPref_RGB dialog

class CPref_RGB : public CPropertyPage
{
	DECLARE_DYNAMIC(CPref_RGB)

public:
	CPref_RGB();
	virtual ~CPref_RGB();

// Dialog Data
	enum { IDD = IDD_PREF_RGB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	// Cutoff value for ROE
	CString m_strROE;
};
