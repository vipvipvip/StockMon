// FundaVw.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for CSMView
#include "ui.h"
#include "readmsg.h"
#include "SMView.h"

#include "FundaVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CFundaData::Write(CFile& f)
{
  CArchive ar(&f, CArchive::store);

  ar<< strYr1
    << strYr2
    << strYr3
    << strYr4
    << strYr5
    << strYr6
    << strYr7

    // Income statement
    << strRev1
    << strRev2
    << strRev3
    << strRev4
    << strRev5
    << strRev6
    << strRev7

    << strExp1
    << strExp2
    << strExp3
    << strExp4
    << strExp5
    << strExp6
    << strExp7

    << strIBT1
    << strIBT2
    << strIBT3
    << strIBT4
    << strIBT5
    << strIBT6
    << strIBT7

    << strIT1
    << strIT2
    << strIT3
    << strIT4
    << strIT5
    << strIT6
    << strIT7

    << strIAT1
    << strIAT2
    << strIAT3
    << strIAT4
    << strIAT5
    << strIAT6
    << strIAT7


    << strDivPerShare1
    << strDivPerShare2
    << strDivPerShare3
    << strDivPerShare4
    << strDivPerShare5
    << strDivPerShare6
    << strDivPerShare7

    // Balance Sheet
    << strCA1
    << strCA2
    << strCA3
    << strCA4
    << strCA5
    << strCA6
    << strCA7

    << strCL1
    << strCL2
    << strCL3
    << strCL4
    << strCL5
    << strCL6
    << strCL7

    << strLTD1
    << strLTD2
    << strLTD3
    << strLTD4
    << strLTD5
    << strLTD6
    << strLTD7


    << strSharesOut1
    << strSharesOut2
    << strSharesOut3
    << strSharesOut4
    << strSharesOut5
    << strSharesOut6
    << strSharesOut7

    << strComEq1
    << strComEq2
    << strComEq3
    << strComEq4
    << strComEq5
    << strComEq6
    << strComEq7

    // Ratios
    << strOpMargin1
    << strOpMargin2
    << strOpMargin3
    << strOpMargin4
    << strOpMargin5
    << strOpMargin6
    << strOpMargin7

    << strProfitMargin1
    << strProfitMargin2
    << strProfitMargin3
    << strProfitMargin4
    << strProfitMargin5
    << strProfitMargin6
    << strProfitMargin7

    << strROE1
    << strROE2
    << strROE3
    << strROE4
    << strROE5
    << strROE6
    << strROE7

    << strROA1
    << strROA2
    << strROA3
    << strROA4
    << strROA5
    << strROA6
    << strROA7

    << strDE1
    << strDE2
    << strDE3
    << strDE4
    << strDE5
    << strDE6
    << strDE7

    << strPE1
    << strPE2
    << strPE3
    << strPE4
    << strPE5
    << strPE6
    << strPE7 

    << CurrRatio1
    << CurrRatio2
    << CurrRatio3
    << CurrRatio4
    << CurrRatio5
    << CurrRatio6
    << CurrRatio7

    << strCashOp1
    << strCashOp2
    << strCashOp3
    << strCashOp4
    << strCashOp5
    << strCashOp6
    << strCashOp7

    << strCashInv1
    << strCashInv2
    << strCashInv3
    << strCashInv4
    << strCashInv5
    << strCashInv6
    << strCashInv7

    << strCashFin1
    << strCashFin2
    << strCashFin3
    << strCashFin4
    << strCashFin5
    << strCashFin6
    << strCashFin7

    // Quarterly Performance
    << strQ1
    << strQ2
    << strQ3
    << strQ4
    << strQ5
    << strQ6
    << strQ7

    << strQRev1
    << strQRev2
    << strQRev3
    << strQRev4
    << strQRev5
    << strQRev6
    << strQRev7

    << strQExp1
    << strQExp2
    << strQExp3
    << strQExp4
    << strQExp5
    << strQExp6
    << strQExp7

    << strQIBT1
    << strQIBT2
    << strQIBT3
    << strQIBT4
    << strQIBT5
    << strQIBT6
    << strQIBT7

    << strQDiv1
    << strQDiv2
    << strQDiv3
    << strQDiv4
    << strQDiv5
    << strQDiv6
    << strQDiv7

    << strQShares1
    << strQShares2
    << strQShares3
    << strQShares4
    << strQShares5
    << strQShares6
    << strQShares7

    // IAT Estimate
    << strCurQtrIAT
    << strNextQtrIAT
    << strCurYrIAT
    << strNextYrIAT

    // Company to Industry
    << strPriceToInd
    << strRevToInd
    << strNIToInd
    << strIATToInd
    << strPEToInd
    << strPriceBVToInd
    << strROEToInd
    << strROAToInd
    << strDEToInd
    << strProfitMarginToInd;

  ar.Close();
}

void CFundaData::Read(CFile& f)
{
  CArchive ar(&f, CArchive::load);

  ar>> strYr1
    >> strYr2
    >> strYr3
    >> strYr4
    >> strYr5
    >> strYr6
    >> strYr7

    // Income statement
    >> strRev1
    >> strRev2
    >> strRev3
    >> strRev4
    >> strRev5
    >> strRev6
    >> strRev7

    >> strExp1
    >> strExp2
    >> strExp3
    >> strExp4
    >> strExp5
    >> strExp6
    >> strExp7

    >> strIBT1
    >> strIBT2
    >> strIBT3
    >> strIBT4
    >> strIBT5
    >> strIBT6
    >> strIBT7

    >> strIT1
    >> strIT2
    >> strIT3
    >> strIT4
    >> strIT5
    >> strIT6
    >> strIT7

    >> strIAT1
    >> strIAT2
    >> strIAT3
    >> strIAT4
    >> strIAT5
    >> strIAT6
    >> strIAT7


    >> strDivPerShare1
    >> strDivPerShare2
    >> strDivPerShare3
    >> strDivPerShare4
    >> strDivPerShare5
    >> strDivPerShare6
    >> strDivPerShare7

    // Balance Sheet
    >> strCA1
    >> strCA2
    >> strCA3
    >> strCA4
    >> strCA5
    >> strCA6
    >> strCA7

    >> strCL1
    >> strCL2
    >> strCL3
    >> strCL4
    >> strCL5
    >> strCL6
    >> strCL7

    >> strLTD1
    >> strLTD2
    >> strLTD3
    >> strLTD4
    >> strLTD5
    >> strLTD6
    >> strLTD7


    >> strSharesOut1
    >> strSharesOut2
    >> strSharesOut3
    >> strSharesOut4
    >> strSharesOut5
    >> strSharesOut6
    >> strSharesOut7

    >> strComEq1
    >> strComEq2
    >> strComEq3
    >> strComEq4
    >> strComEq5
    >> strComEq6
    >> strComEq7

    // Ratios
    >> strOpMargin1
    >> strOpMargin2
    >> strOpMargin3
    >> strOpMargin4
    >> strOpMargin5
    >> strOpMargin6
    >> strOpMargin7

    >> strProfitMargin1
    >> strProfitMargin2
    >> strProfitMargin3
    >> strProfitMargin4
    >> strProfitMargin5
    >> strProfitMargin6
    >> strProfitMargin7

    >> strROE1
    >> strROE2
    >> strROE3
    >> strROE4
    >> strROE5
    >> strROE6
    >> strROE7

    >> strROA1
    >> strROA2
    >> strROA3
    >> strROA4
    >> strROA5
    >> strROA6
    >> strROA7

    >> strDE1
    >> strDE2
    >> strDE3
    >> strDE4
    >> strDE5
    >> strDE6
    >> strDE7

    >> strPE1
    >> strPE2
    >> strPE3
    >> strPE4
    >> strPE5
    >> strPE6
    >> strPE7 

    >> CurrRatio1
    >> CurrRatio2
    >> CurrRatio3
    >> CurrRatio4
    >> CurrRatio5
    >> CurrRatio6
    >> CurrRatio7

    >> strCashOp1
    >> strCashOp2
    >> strCashOp3
    >> strCashOp4
    >> strCashOp5
    >> strCashOp6
    >> strCashOp7

    >> strCashInv1
    >> strCashInv2
    >> strCashInv3
    >> strCashInv4
    >> strCashInv5
    >> strCashInv6
    >> strCashInv7

    >> strCashFin1
    >> strCashFin2
    >> strCashFin3
    >> strCashFin4
    >> strCashFin5
    >> strCashFin6
    >> strCashFin7

    // Quarterly Performance
    >> strQ1
    >> strQ2
    >> strQ3
    >> strQ4
    >> strQ5
    >> strQ6
    >> strQ7

    >> strQRev1
    >> strQRev2
    >> strQRev3
    >> strQRev4
    >> strQRev5
    >> strQRev6
    >> strQRev7

    >> strQExp1
    >> strQExp2
    >> strQExp3
    >> strQExp4
    >> strQExp5
    >> strQExp6
    >> strQExp7

    >> strQIBT1
    >> strQIBT2
    >> strQIBT3
    >> strQIBT4
    >> strQIBT5
    >> strQIBT6
    >> strQIBT7

    >> strQDiv1
    >> strQDiv2
    >> strQDiv3
    >> strQDiv4
    >> strQDiv5
    >> strQDiv6
    >> strQDiv7

    >> strQShares1
    >> strQShares2
    >> strQShares3
    >> strQShares4
    >> strQShares5
    >> strQShares6
    >> strQShares7

    // IAT Estimate
    >> strCurQtrIAT
    >> strNextQtrIAT
    >> strCurYrIAT
    >> strNextYrIAT

    // Company to Industry
    >> strPriceToInd
    >> strRevToInd
    >> strNIToInd
    >> strIATToInd
    >> strPEToInd
    >> strPriceBVToInd
    >> strROEToInd
    >> strROAToInd
    >> strDEToInd
    >> strProfitMarginToInd;

  ar.Close();

}

/////////////////////////////////////////////////////////////////////////////
// CFundaVw
#define FUNDA_VW_SUBHEADING _T("Settings\\Fundamentals View")

IMPLEMENT_DYNCREATE(CFundaVw, CListViewEx)

CFundaVw::CFundaVw()
{
  m_pOwner=NULL;
  m_bFromFile = FALSE;
}

CFundaVw::CFundaVw(CSMView *pOwner)
{
  ASSERT(pOwner);
  m_pOwner = pOwner;
  m_bFromFile = FALSE;
}


CFundaVw::~CFundaVw()
{
}


BEGIN_MESSAGE_MAP(CFundaVw, CListViewEx)
	//{{AFX_MSG_MAP(CFundaVw)
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewquotes)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
 	ON_MESSAGE (SHOW_FUNDA, OnShowFunda)
  ON_MESSAGE (SHOW_FUNDA_FROM_FILE, OnShowFundaFromFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFundaVw drawing
void CFundaVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}


/////////////////////////////////////////////////////////////////////////////
// CFundaVw diagnostics

#ifdef _DEBUG
void CFundaVw::AssertValid() const
{
	CListViewEx::AssertValid();
}

void CFundaVw::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFundaVw message handlers
afx_msg LRESULT  CFundaVw::OnShowFunda(WPARAM wParam, LPARAM lParam)
{
  CString strTicker = (LPCTSTR)wParam;
	CString strWebPageContent((LPCTSTR)lParam);
  m_strWebPage = strWebPageContent;
  ParseCoFunda(m_strWebPage);
  m_bFromFile=FALSE;
  ShowFunda(strTicker);
  return 0;
}

afx_msg LRESULT CFundaVw::OnShowFundaFromFile(WPARAM wParam, LPARAM lParam)
{
  CString strTicker = (LPCTSTR)wParam;
  CString strFile((LPCTSTR)lParam);
	CFile f;
	if ( f.Open(strFile, CFile::modeRead)) {
    m_data.Read(f);
    f.Close();
    m_bFromFile=TRUE;
    ShowFunda(strTicker);
  }
  return 0;
}

void CFundaVw::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	m_strColWidths = THEAPP()->GetProfileString(FUNDA_VW_SUBHEADING, FRM_LHV_COLWIDTH );
}

void CFundaVw::OnViewquotes() 
{
	THEAPP()->SwitchView(m_pOwner);		
}

void CFundaVw::OnDestroy() 
{

	CListCtrl& ListCtrl=GetListCtrl();
	int i=0;
	WCHAR szT[80];
	CString strValue;
	CString strTemp;
	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT;
	lvc.pszText = szT;
	lvc.cchTextMax = sizeof(szT) - sizeof(char);
	while ( ListCtrl.GetColumn(i++, &lvc) ) {
		strTemp.Format(_T("%d "), lvc.cx);
		strValue += strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( FUNDA_VW_SUBHEADING, FRM_LHV_COLWIDTH, strValue );
	}

	CListViewEx::OnDestroy();
	
}
void CFundaVw::ShowFunda( CString& rTicker)
{

  if ( m_strTicker != rTicker ) {
    CString strHeadings;
    strHeadings = rTicker       +
                  ','           +
                  m_data.strYr1 +
                  ','           +
                  m_data.strYr2 +
                  ','           +
                  m_data.strYr3 +
                  ','           +
                  m_data.strYr4 +
                  ','           +
                  m_data.strYr5 +
                  ','           +
                  m_data.strYr6; //+
//                  ','           +
//                  m_data.strYr7;
    DisplayColumnHeadings(strHeadings);
    m_strTicker = rTicker;
  }
  else {
    EraseList(TRUE);
  }

  if(!m_bFromFile) {
    CSMDoc *pDoc = (CSMDoc *)GetDocument();
	  CString strFileName		=	pDoc->m_strImageLocation;	
	  strFileName		+=  m_strTicker;
	  strFileName		+=  ".fun";

	  CFile f;
	  if ( f.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {
		  m_data.Write(f);
      f.Close();
	  }
	  else {
		  CString str;
		  str.Format(_T("Unable to open %s. Please set a valid directory in the View/Options dialog"), strFileName);
		  AfxMessageBox(str); 
	  }
  }

  int iRow=0;
  CString str;
  double Gr1=0; 
  double Gr2=0; 
  double Gr3=0;
  double Gr4=0;
  double Gr5=0;

  AddItem(iRow, 0, _T("Income Statement"));
  AddItem(++iRow, 0, _T(" "));

  AddItem(++iRow, 0, _T("Revenue "));
  AddItem(iRow, 1, m_data.strRev1 );
  AddItem(iRow, 2, m_data.strRev2 );
  AddItem(iRow, 3, m_data.strRev3 );
  AddItem(iRow, 4, m_data.strRev4 );
  AddItem(iRow, 5, m_data.strRev5 );
  AddItem(iRow, 6, m_data.strRev6 );
  AddItem(iRow, 7, m_data.strRev7 );

  AddItem(++iRow, 0, _T("Expenses "));
  AddItem(iRow, 1, m_data.strExp1 );
  AddItem(iRow, 2, m_data.strExp2 );
  AddItem(iRow, 3, m_data.strExp3 );
  AddItem(iRow, 4, m_data.strExp4 );
  AddItem(iRow, 5, m_data.strExp5 );
  AddItem(iRow, 6, m_data.strExp6 );
  AddItem(iRow, 7, m_data.strExp7 );

  AddItem(++iRow, 0, _T("Income before taxes"));
  AddItem(iRow, 1, m_data.strIBT1 );
  AddItem(iRow, 2, m_data.strIBT2 );
  AddItem(iRow, 3, m_data.strIBT3 );
  AddItem(iRow, 4, m_data.strIBT4 );
  AddItem(iRow, 5, m_data.strIBT5 );
  AddItem(iRow, 6, m_data.strIBT6 );
  AddItem(iRow, 7, m_data.strIBT7 );

  AddItem(++iRow, 0, _T("Income Taxes"));
  AddItem(iRow, 1, m_data.strIT1 );
  AddItem(iRow, 2, m_data.strIT2 );
  AddItem(iRow, 3, m_data.strIT3 );
  AddItem(iRow, 4, m_data.strIT4 );
  AddItem(iRow, 5, m_data.strIT5 );
  AddItem(iRow, 6, m_data.strIT6 );
  AddItem(iRow, 7, m_data.strIT7 );

  AddItem(++iRow, 0, (LPCTSTR)"Income after taxes" );
  AddItem(iRow, 1, m_data.strIAT1 );
  AddItem(iRow, 2, m_data.strIAT2 );
  AddItem(iRow, 3, m_data.strIAT3 );
  AddItem(iRow, 4, m_data.strIAT4 );
  AddItem(iRow, 5, m_data.strIAT5 );
  AddItem(iRow, 6, m_data.strIAT6 );
  AddItem(iRow, 7, m_data.strIAT7 );

  AddItem(++iRow, 0, (LPCTSTR)"Div/share" );
  AddItem(iRow, 1, m_data.strDivPerShare1 );
  AddItem(iRow, 2, m_data.strDivPerShare2 );
  AddItem(iRow, 3, m_data.strDivPerShare3 );
  AddItem(iRow, 4, m_data.strDivPerShare4 );
  AddItem(iRow, 5, m_data.strDivPerShare5 );
  AddItem(iRow, 6, m_data.strDivPerShare6 );
  AddItem(iRow, 7, m_data.strDivPerShare7 );

  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Balance Sheet" );
  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Current Assets ($mil)" );
  AddItem(iRow, 1, m_data.strCA1 );
  AddItem(iRow, 2, m_data.strCA2 );
  AddItem(iRow, 3, m_data.strCA3 );
  AddItem(iRow, 4, m_data.strCA4 );
  AddItem(iRow, 5, m_data.strCA5 );
  AddItem(iRow, 6, m_data.strCA6 );
  AddItem(iRow, 7, m_data.strCA7 );


  AddItem(++iRow, 0, (LPCTSTR)"Current Liability ($mil)" );
  AddItem(iRow, 1, m_data.strCL1 );
  AddItem(iRow, 2, m_data.strCL2 );
  AddItem(iRow, 3, m_data.strCL3 );
  AddItem(iRow, 4, m_data.strCL4 );
  AddItem(iRow, 5, m_data.strCL5 );
  AddItem(iRow, 6, m_data.strCL6 );
  AddItem(iRow, 7, m_data.strCL7 );

  AddItem(++iRow, 0, (LPCTSTR)"Long-term debt ($mil)");
  AddItem(iRow, 1, m_data.strLTD1 );
  AddItem(iRow, 2, m_data.strLTD2 );
  AddItem(iRow, 3, m_data.strLTD3 );
  AddItem(iRow, 4, m_data.strLTD4 );
  AddItem(iRow, 5, m_data.strLTD5 );
  AddItem(iRow, 6, m_data.strLTD6 );
  AddItem(iRow, 7, m_data.strLTD7 );

  AddItem(++iRow, 0, (LPCTSTR)"Shares Outstanding (000)");
  AddItem(iRow, 1, m_data.strSharesOut1 );
  AddItem(iRow, 2, m_data.strSharesOut2 );
  AddItem(iRow, 3, m_data.strSharesOut3 );
  AddItem(iRow, 4, m_data.strSharesOut4 );
  AddItem(iRow, 5, m_data.strSharesOut5 );
  AddItem(iRow, 6, m_data.strSharesOut6 );
  AddItem(iRow, 7, m_data.strSharesOut7 );

  AddItem(++iRow, 0, (LPCTSTR)"Common Equity ($mil)");
  AddItem(iRow, 1, m_data.strComEq1 );
  AddItem(iRow, 2, m_data.strComEq2 );
  AddItem(iRow, 3, m_data.strComEq3 );
  AddItem(iRow, 4, m_data.strComEq4 );
  AddItem(iRow, 5, m_data.strComEq5 );
  AddItem(iRow, 6, m_data.strComEq6 );
  AddItem(iRow, 7, m_data.strComEq7 );

  AddItem(++iRow, 0, (LPCTSTR)"Cash from Operations");
  AddItem(iRow, 1, m_data.strCashOp1 );
  AddItem(iRow, 2, m_data.strCashOp2 );
  AddItem(iRow, 3, m_data.strCashOp3 );
  AddItem(iRow, 4, m_data.strCashOp4 );
  AddItem(iRow, 5, m_data.strCashOp5 );
  AddItem(iRow, 6, m_data.strCashOp6 );
  AddItem(iRow, 7, m_data.strCashOp7 );

  AddItem(++iRow, 0, (LPCTSTR)"Cash from Investing");
  AddItem(iRow, 1, m_data.strCashInv1 );
  AddItem(iRow, 2, m_data.strCashInv2 );
  AddItem(iRow, 3, m_data.strCashInv3 );
  AddItem(iRow, 4, m_data.strCashInv4 );
  AddItem(iRow, 5, m_data.strCashInv5 );
  AddItem(iRow, 6, m_data.strCashInv6 );
  AddItem(iRow, 7, m_data.strCashInv7 );

  AddItem(++iRow, 0, (LPCTSTR)"Cash from Financing");
  AddItem(iRow, 1, m_data.strCashFin1 );
  AddItem(iRow, 2, m_data.strCashFin2 );
  AddItem(iRow, 3, m_data.strCashFin3 );
  AddItem(iRow, 4, m_data.strCashFin4 );
  AddItem(iRow, 5, m_data.strCashFin5 );
  AddItem(iRow, 6, m_data.strCashFin6 );
  AddItem(iRow, 7, m_data.strCashFin7 );

  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Ratios" );
  AddItem(++iRow, 0, (LPCTSTR)"" );

  AddItem(++iRow, 0, (LPCTSTR)"Profit Margin %" );
  AddItem(iRow, 1, m_data.strProfitMargin1 );
  AddItem(iRow, 2, m_data.strProfitMargin2 );
  AddItem(iRow, 3, m_data.strProfitMargin3 );
  AddItem(iRow, 4, m_data.strProfitMargin4 );
  AddItem(iRow, 5, m_data.strProfitMargin5 );
  AddItem(iRow, 6, m_data.strProfitMargin6 );
  AddItem(iRow, 7, m_data.strProfitMargin7 );

  AddItem(++iRow, 0, (LPCTSTR)"Operating Margin" );
  AddItem(iRow, 1, m_data.strOpMargin1 );
  AddItem(iRow, 2, m_data.strOpMargin2 );
  AddItem(iRow, 3, m_data.strOpMargin3 );
  AddItem(iRow, 4, m_data.strOpMargin4 );
  AddItem(iRow, 5, m_data.strOpMargin5 );
  AddItem(iRow, 6, m_data.strOpMargin6 );
  AddItem(iRow, 7, m_data.strOpMargin7 );


  AddItem(++iRow, 0, (LPCTSTR)"Return on Equity" );
  AddItem(iRow, 1, m_data.strROE1 );
  AddItem(iRow, 2, m_data.strROE2 );
  AddItem(iRow, 3, m_data.strROE3 );
  AddItem(iRow, 4, m_data.strROE4 );
  AddItem(iRow, 5, m_data.strROE5 );
  AddItem(iRow, 6, m_data.strROE6 );
  AddItem(iRow, 7, m_data.strROE7 );

  AddItem(++iRow, 0, (LPCTSTR)"Return on Assets" );
  AddItem(iRow, 1, m_data.strROA1 );
  AddItem(iRow, 2, m_data.strROA2 );
  AddItem(iRow, 3, m_data.strROA3 );
  AddItem(iRow, 4, m_data.strROA4 );
  AddItem(iRow, 5, m_data.strROA5 );
  AddItem(iRow, 6, m_data.strROA6 );
  AddItem(iRow, 7, m_data.strROA7 );

  AddItem(++iRow, 0, (LPCTSTR)"Debt / Equity" );
  AddItem(iRow, 1, m_data.strDE1 );
  AddItem(iRow, 2, m_data.strDE2 );
  AddItem(iRow, 3, m_data.strDE3 );
  AddItem(iRow, 4, m_data.strDE4 );
  AddItem(iRow, 5, m_data.strDE5 );
  AddItem(iRow, 6, m_data.strDE6 );
  AddItem(iRow, 7, m_data.strDE7 );

  AddItem(++iRow, 0, (LPCTSTR)"P/E" );
  AddItem(iRow, 1, m_data.strPE1 );
  AddItem(iRow, 2, m_data.strPE2 );
  AddItem(iRow, 3, m_data.strPE3 );
  AddItem(iRow, 4, m_data.strPE4 );
  AddItem(iRow, 5, m_data.strPE5 );
  AddItem(iRow, 6, m_data.strPE6 );
  AddItem(iRow, 7, m_data.strPE7 );

  AddItem(++iRow, 0, (LPCTSTR)"Current Ratio");
  AddItem(iRow, 1, m_data.CurrRatio1 );
  AddItem(iRow, 2, m_data.CurrRatio2 );
  AddItem(iRow, 3, m_data.CurrRatio3 );
  AddItem(iRow, 4, m_data.CurrRatio4 );
  AddItem(iRow, 5, m_data.CurrRatio5 );
  AddItem(iRow, 6, m_data.CurrRatio6 );
  AddItem(iRow, 7, m_data.CurrRatio7 );

/*
  AddItem(++iRow, 0, (LPCTSTR)"Price to Book");
  AddItem(iRow, 1, m_data.strCashOp1 );
  AddItem(iRow, 2, m_data.strCashOp2 );
  AddItem(iRow, 3, m_data.strCashOp3 );
  AddItem(iRow, 4, m_data.strCashOp4 );
  AddItem(iRow, 5, m_data.strCashOp5 );
  AddItem(iRow, 6, m_data.strCashOp6 );
  AddItem(iRow, 7, m_data.strCashOp7 );

  AddItem(++iRow, 0, (LPCTSTR)"Book Value ($)");
  AddItem(iRow, 1, m_data.strCashInv1 );
  AddItem(iRow, 2, m_data.strCashInv2 );
  AddItem(iRow, 3, m_data.strCashInv3 );
  AddItem(iRow, 4, m_data.strCashInv4 );
  AddItem(iRow, 5, m_data.strCashInv5 );
  AddItem(iRow, 6, m_data.strCashInv6 );
  AddItem(iRow, 7, m_data.strCashInv7 );

  AddItem(++iRow, 0, (LPCTSTR)"Div Payout (%)");
  AddItem(iRow, 1, m_data.strCashFin1 );
  AddItem(iRow, 2, m_data.strCashFin2 );
  AddItem(iRow, 3, m_data.strCashFin3 );
  AddItem(iRow, 4, m_data.strCashFin4 );
  AddItem(iRow, 5, m_data.strCashFin5 );
  AddItem(iRow, 6, m_data.strCashFin6 );
  AddItem(iRow, 7, m_data.strCashFin7 );
*/

  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Quarterly Performance" );
  AddItem(iRow, 1, m_data.strQ1 );
  AddItem(iRow, 2, m_data.strQ2 );
  AddItem(iRow, 3, m_data.strQ3 );
  AddItem(iRow, 4, m_data.strQ4 );
  AddItem(iRow, 5, m_data.strQ5 );
  AddItem(iRow, 6, m_data.strQ6 );

  AddItem(++iRow, 0, (LPCTSTR)"" );


  AddItem(++iRow, 0, (LPCTSTR)"Revenue ($mil)");
  AddItem(iRow, 1, m_data.strQRev1 );
  AddItem(iRow, 2, m_data.strQRev2 );
  AddItem(iRow, 3, m_data.strQRev3 );
  AddItem(iRow, 4, m_data.strQRev4 );
  AddItem(iRow, 5, m_data.strQRev5 );
  AddItem(iRow, 6, m_data.strQRev6 );
  AddItem(iRow, 7, m_data.strQRev7 );

  AddItem(++iRow, 0, (LPCTSTR)"Expense($mil)");
  AddItem(iRow, 1, m_data.strQExp1 );
  AddItem(iRow, 2, m_data.strQExp2 );
  AddItem(iRow, 3, m_data.strQExp3 );
  AddItem(iRow, 4, m_data.strQExp4 );
  AddItem(iRow, 5, m_data.strQExp5 );
  AddItem(iRow, 6, m_data.strQExp6 );
  AddItem(iRow, 7, m_data.strQExp7 );

  AddItem(++iRow, 0, (LPCTSTR)"Income before taxes");
  AddItem(iRow, 1, m_data.strQIBT1 );
  AddItem(iRow, 2, m_data.strQIBT2 );
  AddItem(iRow, 3, m_data.strQIBT3 );
  AddItem(iRow, 4, m_data.strQIBT4 );
  AddItem(iRow, 5, m_data.strQIBT5 );
  AddItem(iRow, 6, m_data.strQIBT6 );
  AddItem(iRow, 7, m_data.strQIBT7 );

  AddItem(++iRow, 0, (LPCTSTR)"Div ($)");
  AddItem(iRow, 1, m_data.strQDiv1 );
  AddItem(iRow, 2, m_data.strQDiv2 );
  AddItem(iRow, 3, m_data.strQDiv3 );
  AddItem(iRow, 4, m_data.strQDiv4 );
  AddItem(iRow, 5, m_data.strQDiv5 );
  AddItem(iRow, 6, m_data.strQDiv6 );
  AddItem(iRow, 7, m_data.strQDiv7 );

  AddItem(++iRow, 0, (LPCTSTR)"Shares outstanding (000)");
  AddItem(iRow, 1, m_data.strQShares1 );
  AddItem(iRow, 2, m_data.strQShares2 );
  AddItem(iRow, 3, m_data.strQShares3 );
  AddItem(iRow, 4, m_data.strQShares4 );
  AddItem(iRow, 5, m_data.strQShares5 );
  AddItem(iRow, 6, m_data.strQShares6 );
  AddItem(iRow, 7, m_data.strQShares7 );

/*
  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"IAT Estimate" );
  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Current Quarter");
  AddItem(iRow, 1, m_data.strCurQtrIAT );

  AddItem(++iRow, 0, (LPCTSTR)"Next Quarter");
  AddItem(iRow, 1, m_data.strNextQtrIAT );

  AddItem(++iRow, 0, (LPCTSTR)"Current Year");
  AddItem(iRow, 1, m_data.strCurYrIAT );

  AddItem(++iRow, 0, (LPCTSTR)"Next Year");
  AddItem(iRow, 1, m_data.strNextYrIAT );

  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Company to Industry (%)" );
  AddItem(++iRow, 0, (LPCTSTR)"" );
  AddItem(++iRow, 0, (LPCTSTR)"Price to Industry");
  AddItem(iRow, 1, m_data.strPriceToInd );

  AddItem(++iRow, 0, (LPCTSTR)"Revenue to Industry");
  AddItem(iRow, 1, m_data.strRevToInd );

  AddItem(++iRow, 0, (LPCTSTR)"Net Income to Industry");
  AddItem(iRow, 1, m_data.strNIToInd );

  AddItem(++iRow, 0, (LPCTSTR)"IAT to Industry");
  AddItem(iRow, 1, m_data.strIATToInd );

  AddItem(++iRow, 0, (LPCTSTR)"PE to Industry");
  AddItem(iRow, 1, m_data.strPEToInd );

  AddItem(++iRow, 0, (LPCTSTR)"Price/Book Value to Industry");
  AddItem(iRow, 1, m_data.strPriceBVToInd );

  AddItem(++iRow, 0, (LPCTSTR)"ROE to Industry");
  AddItem(iRow, 1, m_data.strROEToInd );

  AddItem(++iRow, 0, (LPCTSTR)"ROA to Industry");
  AddItem(iRow, 1, m_data.strROAToInd );

  AddItem(++iRow, 0, (LPCTSTR)"Debt/Equity to Industry");
  AddItem(iRow, 1, m_data.strDEToInd );

  AddItem(++iRow, 0, (LPCTSTR)"Profit Margin to Industry");
  AddItem(iRow, 1, m_data.strProfitMarginToInd );
*/

}

void Sanitize( CString& rStr )
{
  if ( -1 != rStr.Find((LPCTSTR)"Trail") ) return;
  if ( -1 != rStr.Find((LPCTSTR)"(") ) return;

  int iLen = rStr.GetLength();
  for ( int i=0; i<iLen; i++ ) {
    if ( isdigit(rStr[i]) || rStr[i] == '.' || rStr[i] == '-' || rStr[i] == 'B' || rStr[i] == 'M' || rStr[i] == '/') 
      continue;
    else {
      rStr.Format((LPCTSTR)"%d", 0);
      return;
    }
  }
}

void CFundaVw::GetData (int& iPos, CString& rWebPage, int nItems, CString& str1,CString& str2, CString& str3,
              CString& str4,CString& str5, CString& str6,CString& str7,
              LPCTSTR pEnd)
{

  if ( iPos == -1 ) return;
	int iLen = rWebPage.GetLength();

  while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.' && rWebPage[iPos] == '\x0A' && rWebPage[iPos] == '\x20') iPos++;

  if ( nItems >= 1) {
    str1.Empty();
    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str1 += rWebPage[iPos];
      }
      iPos++;
    }
  }
  
  if ( nItems >= 2) {
    str2.Empty();
      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str2 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str2);
  }

  if ( nItems >= 3) {
    str3.Empty();

      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str3 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str3);
  }

  if ( nItems >= 4) {
    str4.Empty();

      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str4 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str4);
  }

  if ( nItems >= 5) {
    str5.Empty();  

      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str5 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str5);
  }

  if ( nItems >= 6) {
    str6.Empty();

      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str6 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str6);
  }

  if ( nItems >= 7) {
    str7.Empty();

    if ( pEnd ) {
      CString s;
      s = pEnd;
      int nEnd = s.GetLength();
      while ( iPos < iLen && rWebPage.Mid(iPos, nEnd) != s ) iPos++;
    }
    else {
      while ( iPos < iLen && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && rWebPage[iPos] != '-'  && rWebPage[iPos] != '.'  && !isdigit(rWebPage[iPos])) iPos++;
    }

    while ( iPos < iLen && rWebPage[iPos] != '\x0A' && rWebPage[iPos] != '\x20'  && rWebPage[iPos] != '\x0D') {
      if (rWebPage[iPos] != ',') {
        str7 += rWebPage[iPos];
      }
      iPos++;
    }
    Sanitize(str7);
  }

//  AfxMessageBox(str1 + " " + str2 + " " + str3 + " " + str4 + " " + str5 + " " + str6 + " " + str7);

}


void CFundaVw::ParseCoFunda(CString& rWebPage)
{

	int iLen = rWebPage.GetLength();
  int iPos = 0;
  iPos = rWebPage.Find((LPCTSTR)"STATEMENT:");
  if ( iPos == -1 ) return;

  rWebPage=rWebPage.Mid(iPos+10);
	iLen = rWebPage.GetLength();
  iPos=0;

      while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;


  int iRow=0;
  int iCol=0;

  int nItems =6;

  GetData(iPos, rWebPage, nItems, m_data.strYr1,m_data.strYr2,m_data.strYr3,m_data.strYr4,m_data.strYr5,m_data.strYr6, m_data.strYr7);
  if ( -1 != m_data.strYr7.Find((LPCTSTR)"NA") ) {
    nItems = 6;
  }

  // Get Income Statement
  iPos = rWebPage.Find((LPCTSTR)"Revenue");
  if ( iPos != -1 ) {
    while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strRev1,m_data.strRev2,m_data.strRev3,m_data.strRev4,m_data.strRev5,m_data.strRev6,m_data.strRev7);
  } // end Revenue


  iPos = rWebPage.Find((LPCTSTR)"Expenses");
  if ( iPos != -1 ) {
    while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strExp1,m_data.strExp2,m_data.strExp3,m_data.strExp4,m_data.strExp5,m_data.strExp6,m_data.strExp7);
  } // end Expenses


  iPos = rWebPage.Find((LPCTSTR)"Income before taxes");
  if ( iPos != -1 ) {
    while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strIBT1,m_data.strIBT2,m_data.strIBT3,m_data.strIBT4,m_data.strIBT5,m_data.strIBT6, m_data.strIBT7);
  } // end Income before taxes


  iPos = rWebPage.Find((LPCTSTR)"Income taxes");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strIT1,m_data.strIT2,m_data.strIT3,m_data.strIT4,m_data.strIT5,m_data.strIT6, m_data.strIT7);
  } // end Income taxes


  iPos = rWebPage.Find((LPCTSTR)"Income after taxes ");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strIAT1,m_data.strIAT2,m_data.strIAT3,m_data.strIAT4,m_data.strIAT5,m_data.strIAT6,m_data.strIAT7);
  } // end Income after taxes


  iPos = rWebPage.Find((LPCTSTR)"Dividends per share");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strDivPerShare1,m_data.strDivPerShare2,m_data.strDivPerShare3,m_data.strDivPerShare4,m_data.strDivPerShare5,m_data.strDivPerShare6,m_data.strDivPerShare7);
  } // end Dividends


  // Balance sheet

  iPos = rWebPage.Find((LPCTSTR)"Current assets");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strCA1,m_data.strCA2,m_data.strCA3,m_data.strCA4,m_data.strCA5,m_data.strCA6,m_data.strCA7);
  } // end CA

  iPos = rWebPage.Find((LPCTSTR)"Current liabilities");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strCL1,m_data.strCL2,m_data.strCL3,m_data.strCL4,m_data.strCL5,m_data.strCL6,m_data.strCL7);
  } // end Current Liabilities 

  iPos = rWebPage.Find((LPCTSTR)"Long term debt");
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strLTD1,m_data.strLTD2,m_data.strLTD3,m_data.strLTD4,m_data.strLTD5,m_data.strLTD6, m_data.strLTD7);
  } // end Long Term Debt 


  iPos = rWebPage.Find((LPCTSTR)"Shares outstanding");  
  if ( iPos != -1 ) {
    iPos += 16;
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;
    GetData(iPos, rWebPage, nItems, m_data.strSharesOut1,m_data.strSharesOut2,m_data.strSharesOut3,m_data.strSharesOut4,m_data.strSharesOut5,m_data.strSharesOut6,m_data.strSharesOut7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Total equity");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strComEq1,m_data.strComEq2,m_data.strComEq3,m_data.strComEq4,m_data.strComEq5,m_data.strComEq6,m_data.strComEq7);
  }


  iPos = rWebPage.Find((LPCTSTR)"Cash from operations");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashOp1,m_data.strCashOp2,m_data.strCashOp3,m_data.strCashOp4,m_data.strCashOp5,m_data.strCashOp6,m_data.strCashOp7);
  } // Cash from operations


  iPos = rWebPage.Find((LPCTSTR)"Cash from investing");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashInv1,m_data.strCashInv2,m_data.strCashInv3,m_data.strCashInv4,m_data.strCashInv5,m_data.strCashInv6,m_data.strCashInv7);
  } // Cash from investing


  iPos = rWebPage.Find((LPCTSTR)"Cash from financing");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashFin1,m_data.strCashFin2,m_data.strCashFin3,m_data.strCashFin4,m_data.strCashFin5,m_data.strCashFin6,m_data.strCashFin7);
  } // Cash from financing



  // Ratios
  iPos = rWebPage.Find((LPCTSTR)"Profit Margin");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strProfitMargin1,m_data.strProfitMargin2,m_data.strProfitMargin3,m_data.strProfitMargin4,m_data.strProfitMargin5,m_data.strProfitMargin6,m_data.strProfitMargin7);
  } // Profit Margin 


  iPos = rWebPage.Find((LPCTSTR)"Operating Margin");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strOpMargin1,m_data.strOpMargin2,m_data.strOpMargin3,m_data.strOpMargin4,m_data.strOpMargin5,m_data.strOpMargin6,m_data.strOpMargin7);
  } // Operating Margin


  iPos = rWebPage.Find((LPCTSTR)"Return on equity");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strROE1,m_data.strROE2,m_data.strROE3,m_data.strROE4,m_data.strROE5,m_data.strROE6,m_data.strROE7);
  } // Return on Equity 

  iPos = rWebPage.Find((LPCTSTR)"Return on assets");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strROA1,m_data.strROA2,m_data.strROA3,m_data.strROA4,m_data.strROA5,m_data.strROA6,m_data.strROA7);
  } // Return on Asset 


  iPos = rWebPage.Find((LPCTSTR)"Debt/Equity");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strDE1,m_data.strDE2,m_data.strDE3,m_data.strDE4,m_data.strDE5,m_data.strDE6,m_data.strDE7);
  } // Debt/Equity Ratio


  iPos = rWebPage.Find((LPCTSTR)"P/E");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strPE1,m_data.strPE2,m_data.strPE3,m_data.strPE4,m_data.strPE5,m_data.strPE6,m_data.strPE7);
  } // P/E Ratio


  iPos = rWebPage.Find((LPCTSTR)"Current ratio");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.CurrRatio1,m_data.CurrRatio2,m_data.CurrRatio3,m_data.CurrRatio4,m_data.CurrRatio5,m_data.CurrRatio6,m_data.CurrRatio7);
  } // Current ratio

/*
  iPos = rWebPage.Find((LPCTSTR)"Price/Book");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashOp1,m_data.strCashOp2,m_data.strCashOp3,m_data.strCashOp4,m_data.strCashOp5,m_data.strCashOp6,m_data.strCashOp7);
  } // Price/Book


  iPos = rWebPage.Find((LPCTSTR)"Book Value");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashInv1,m_data.strCashInv2,m_data.strCashInv3,m_data.strCashInv4,m_data.strCashInv5,m_data.strCashInv6,m_data.strCashInv7);
  } // Book Value 


  iPos = rWebPage.Find((LPCTSTR)"Dividend Payout");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCashFin1,m_data.strCashFin2,m_data.strCashFin3,m_data.strCashFin4,m_data.strCashFin5,m_data.strCashFin6,m_data.strCashFin7);
  } // Dividend Payout 
*/



  // Quarterly Performance
  nItems=6;
  // First get the dates
  iPos = rWebPage.Find((LPCTSTR)"STATEMENT:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQ1,m_data.strQ2,m_data.strQ3,m_data.strQ4,m_data.strQ5,m_data.strQ6,m_data.strQ7);
  } //


  iPos = rWebPage.Find((LPCTSTR)"Revenue");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQRev1,m_data.strQRev2,m_data.strQRev3,m_data.strQRev4,m_data.strQRev5,m_data.strQRev6,m_data.strQRev7);
  } // Revenue


  iPos = rWebPage.Find((LPCTSTR)"Expenses");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQExp1,m_data.strQExp2,m_data.strQExp3,m_data.strQExp4,m_data.strQExp5,m_data.strQExp6,m_data.strQExp7);
  } // Net Income 


  iPos = rWebPage.Find((LPCTSTR)"Income before taxes");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQIBT1,m_data.strQIBT2,m_data.strQIBT3,m_data.strQIBT4,m_data.strQIBT5,m_data.strQIBT6,m_data.strQIBT7);
  } // IAT


  iPos = rWebPage.Find((LPCTSTR)"Dividends per share");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQDiv1,m_data.strQDiv2,m_data.strQDiv3,m_data.strQDiv4,m_data.strQDiv5,m_data.strQDiv6,m_data.strQDiv7);
  } // Dividend

  iPos = rWebPage.Find((LPCTSTR)"Shares outstanding");  
  if ( iPos != -1 ) {
    iPos += 12;
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strQShares1,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  // IAT Estimate
  nItems=1;
  iPos = rWebPage.Find((LPCTSTR)"Current Quarter:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCurQtrIAT,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Current Year:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strCurYrIAT,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Next Quarter:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strNextQtrIAT,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Next Year:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strNextYrIAT,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  // Company to Industry
  iPos = rWebPage.Find((LPCTSTR)"Price to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strPriceToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Revenue to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strRevToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Net Income to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strNIToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"IAT to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strIATToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"P/E Ratio to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strPEToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Price/Book to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strPriceBVToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"ROE to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strROEToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }


  iPos = rWebPage.Find((LPCTSTR)"ROA to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strROAToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Debt/Equity to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strDEToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

  iPos = rWebPage.Find((LPCTSTR)"Profit Margin to Industry:");  
  if ( iPos != -1 ) {
        while ( iPos < iLen  && rWebPage[iPos] != '.' && rWebPage.Mid(iPos,2) != "NA" && rWebPage.Mid(iPos,2) != "NE" && rWebPage.Mid(iPos,2) != "NC"  && !isdigit(rWebPage[iPos])) iPos++;
    rWebPage=rWebPage.Mid(iPos);
	  iLen = rWebPage.GetLength();
    iPos=0;

    GetData(iPos, rWebPage, nItems, m_data.strProfitMarginToInd,m_data.strQShares2,m_data.strQShares3,m_data.strQShares4,m_data.strQShares5,m_data.strQShares6,m_data.strQShares7);
  }

}


