#if !defined(AFX_FUNDAVW_H__808D6611_F2EF_11D0_AFDA_00A024943E2B__INCLUDED_)
#define AFX_FUNDAVW_H__808D6611_F2EF_11D0_AFDA_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FundaVw.h : header file
//
#include <afxrich.h>

class CFundaData {
public:
  void Read(CFile& f);
  void Write(CFile& f);


  CString strYr1;
  CString strYr2;
  CString strYr3;
  CString strYr4;
  CString strYr5;
  CString strYr6;
  CString strYr7;

  // Income statement
  CString strRev1;
  CString strRev2;
  CString strRev3;
  CString strRev4;
  CString strRev5;
  CString strRev6;
  CString strRev7;


  CString strExp1;
  CString strExp2;
  CString strExp3;
  CString strExp4;
  CString strExp5;
  CString strExp6;
  CString strExp7;

  CString strIBT1;
  CString strIBT2;
  CString strIBT3;
  CString strIBT4;
  CString strIBT5;
  CString strIBT6;
  CString strIBT7;

  CString strIT1;
  CString strIT2;
  CString strIT3;
  CString strIT4;
  CString strIT5;
  CString strIT6;
  CString strIT7;

  CString strIAT1;
  CString strIAT2;
  CString strIAT3;
  CString strIAT4;
  CString strIAT5;
  CString strIAT6;
  CString strIAT7;


  CString strDivPerShare1;
  CString strDivPerShare2;
  CString strDivPerShare3;
  CString strDivPerShare4;
  CString strDivPerShare5;
  CString strDivPerShare6;
  CString strDivPerShare7;

  // Balance Sheet
  CString strCA1;
  CString strCA2;
  CString strCA3;
  CString strCA4;
  CString strCA5;
  CString strCA6;
  CString strCA7;

  CString strCL1;
  CString strCL2;
  CString strCL3;
  CString strCL4;
  CString strCL5;
  CString strCL6;
  CString strCL7;

  CString strLTD1;
  CString strLTD2;
  CString strLTD3;
  CString strLTD4;
  CString strLTD5;
  CString strLTD6;
  CString strLTD7;


  CString strSharesOut1;
  CString strSharesOut2;
  CString strSharesOut3;
  CString strSharesOut4;
  CString strSharesOut5;
  CString strSharesOut6;
  CString strSharesOut7;

  CString strComEq1;
  CString strComEq2;
  CString strComEq3;
  CString strComEq4;
  CString strComEq5;
  CString strComEq6;
  CString strComEq7;

  // Ratios
  CString strOpMargin1;
  CString strOpMargin2;
  CString strOpMargin3;
  CString strOpMargin4;
  CString strOpMargin5;
  CString strOpMargin6;
  CString strOpMargin7;

  CString strProfitMargin1;
  CString strProfitMargin2;
  CString strProfitMargin3;
  CString strProfitMargin4;
  CString strProfitMargin5;
  CString strProfitMargin6;
  CString strProfitMargin7;

  CString strROE1;
  CString strROE2;
  CString strROE3;
  CString strROE4;
  CString strROE5;
  CString strROE6;
  CString strROE7;

  CString strROA1;
  CString strROA2;
  CString strROA3;
  CString strROA4;
  CString strROA5;
  CString strROA6;
  CString strROA7;

  CString strDE1;
  CString strDE2;
  CString strDE3;
  CString strDE4;
  CString strDE5;
  CString strDE6;
  CString strDE7;

  CString strPE1;
  CString strPE2;
  CString strPE3;
  CString strPE4;
  CString strPE5;
  CString strPE6;
  CString strPE7; 

  CString CurrRatio1;
  CString CurrRatio2;
  CString CurrRatio3;
  CString CurrRatio4;
  CString CurrRatio5;
  CString CurrRatio6;
  CString CurrRatio7;

  CString strCashOp1;
  CString strCashOp2;
  CString strCashOp3;
  CString strCashOp4;
  CString strCashOp5;
  CString strCashOp6;
  CString strCashOp7;

  CString strCashInv1;
  CString strCashInv2;
  CString strCashInv3;
  CString strCashInv4;
  CString strCashInv5;
  CString strCashInv6;
  CString strCashInv7;

  CString strCashFin1;
  CString strCashFin2;
  CString strCashFin3;
  CString strCashFin4;
  CString strCashFin5;
  CString strCashFin6;
  CString strCashFin7;

  // Quarterly Performance
  CString strQ1;
  CString strQ2;
  CString strQ3;
  CString strQ4;
  CString strQ5;
  CString strQ6;
  CString strQ7;

  CString strQRev1;
  CString strQRev2;
  CString strQRev3;
  CString strQRev4;
  CString strQRev5;
  CString strQRev6;
  CString strQRev7;

  CString strQExp1;
  CString strQExp2;
  CString strQExp3;
  CString strQExp4;
  CString strQExp5;
  CString strQExp6;
  CString strQExp7;

  CString strQIBT1;
  CString strQIBT2;
  CString strQIBT3;
  CString strQIBT4;
  CString strQIBT5;
  CString strQIBT6;
  CString strQIBT7;

  CString strQDiv1;
  CString strQDiv2;
  CString strQDiv3;
  CString strQDiv4;
  CString strQDiv5;
  CString strQDiv6;
  CString strQDiv7;

  CString strQShares1;
  CString strQShares2;
  CString strQShares3;
  CString strQShares4;
  CString strQShares5;
  CString strQShares6;
  CString strQShares7;

  // IAT Estimate
  CString strCurQtrIAT;
  CString strNextQtrIAT;
  CString strCurYrIAT;
  CString strNextYrIAT;

  // Company to Industry
  CString strPriceToInd;
  CString strRevToInd;
  CString strNIToInd;
  CString strIATToInd;
  CString strPEToInd;
  CString strPriceBVToInd;
  CString strROEToInd;
  CString strROAToInd;
  CString strDEToInd;
  CString strProfitMarginToInd;

};

/////////////////////////////////////////////////////////////////////////////
// CFundaVw view
#define ID_FUNDA_VIEW 3

#define SHOW_FUNDA		        WM_APP+3000
#define SHOW_FUNDA_FROM_FILE  SHOW_FUNDA+1

class CSMView;

class CFundaVw : public CListViewEx
{
protected:
  CString m_strWebPage;
  CString m_strTicker;
  BOOL m_bFromFile;

	DECLARE_DYNCREATE(CFundaVw)


// Attributes
public:
	CSMView				*m_pOwner;
  CFundaData m_data;

// Operations
public:
	CFundaVw();           // protected constructor used by dynamic creation
	CFundaVw(CSMView *pOwner);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFundaVw)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFundaVw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFundaVw)
	afx_msg void OnViewquotes();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT  OnShowFunda(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnShowFundaFromFile(WPARAM wParam, LPARAM lParam);

  void ShowFunda(CString& rTicker);
  void ParseCoFunda(CString& rWebPage);
  void GetData (int& iPos, CString& rWebPage, int nItems, CString& str1,CString& str2, CString& str3,
              CString& str4,CString& str5, CString& str6, CString& str7,
              LPCTSTR pEnd=NULL);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNDAVW_H__808D6611_F2EF_11D0_AFDA_00A024943E2B__INCLUDED_)
