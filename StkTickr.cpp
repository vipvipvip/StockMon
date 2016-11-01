// StkTickr.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "TradeInf.h"
#include "StkTickr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THIS_VERSION 7
/////////////////////////////////////////////////////////////////////////////
// CStkTicker

//IMPLEMENT_DYNCREATE(CStkTicker, CCmdTarget)
IMPLEMENT_SERIAL(CStkTicker, CCmdTarget, VERSIONABLE_SCHEMA|THIS_VERSION)

CStkTicker::CStkTicker()
{
	m_nVer	= THIS_VERSION;

	m_bStdTicker = 0;
	m_lvi.mask		=	LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE; 
	// The parent window is responsible for storing the text. 
	// The list view control will send an LVN_GETDISPINFO 
	// when it needs the text to display.
	m_lvi.pszText	=	(LPTSTR)(LPCTSTR)m_strSymbol;		//LPSTR_TEXTCALLBACK;
	m_lvi.lParam	= (LPARAM)this;
	m_lvi.cchTextMax = MAX_PATH;
	m_lvi.iImage	=	0; //I_IMAGECALLBACK;
	m_lvi.state = 0;      
	m_lvi.stateMask = 0;  

	m_bAlert = FALSE;
	m_bMutualFund = 0;

	m_Trades.SetSize(0);

  m_bMerge = FALSE;
  m_nTechChartsReq = 0;
}

CStkTicker::CStkTicker(LPCTSTR lpName)
{
	m_nVer	= THIS_VERSION;

	ASSERT(lpName);
	m_strSymbol = lpName;
	m_bStdTicker = 0;
	m_lvi.mask		=	LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE; 
	// The parent window is responsible for storing the text. 
	// The list view control will send an LVN_GETDISPINFO 
	// when it needs the text to display.
	m_lvi.pszText	=	(LPTSTR)(LPCTSTR)m_strSymbol;		//LPSTR_TEXTCALLBACK;
	m_lvi.lParam	= (LPARAM)this;
	m_lvi.cchTextMax = MAX_PATH;
	m_lvi.iImage	=	0; //I_IMAGECALLBACK;
	m_lvi.state = 0;      
	m_lvi.stateMask = 0;  

	m_bAlert = FALSE;
	m_bMutualFund = 0;

	m_Trades.SetSize(0);

  m_bMerge = FALSE;
  m_nTechChartsReq = 0;

}

CStkTicker::CStkTicker(CStkTicker& rSrcTicker)
{
	m_nVer							= rSrcTicker.m_nVer;
	m_strSymbol					= rSrcTicker.m_strSymbol;
	m_bStdTicker				= rSrcTicker.m_bStdTicker;
	m_lvi.mask					=	rSrcTicker.m_lvi.mask; 
	m_lvi.pszText				=	(LPTSTR)m_strSymbol.GetString();
	m_lvi.lParam				= (LPARAM)this;
	m_lvi.cchTextMax		= rSrcTicker.m_lvi.cchTextMax;
	m_lvi.iImage				=	rSrcTicker.m_lvi.iImage;
	m_lvi.state					= rSrcTicker.m_lvi.state;      
	m_lvi.stateMask			=	rSrcTicker.m_lvi.stateMask;  

	m_bAlert						= rSrcTicker.m_bAlert;
	m_bStdTicker				= rSrcTicker.m_bStdTicker				;
	m_bAlert						= rSrcTicker.m_bAlert						;
	m_lvi.mask					= rSrcTicker.m_lvi.mask					;
	m_lvi.iImage				= rSrcTicker.m_lvi.iImage				;
	m_strSymbol					= rSrcTicker.m_strSymbol				;
	m_strLast						= rSrcTicker.m_strLast					;
	m_strChange					= rSrcTicker.m_strChange				;
	m_StrPctChange			= rSrcTicker.m_strPctChange			;
	m_strVolume					= rSrcTicker.m_strVolume				;
	m_strHigh						= rSrcTicker.m_strHigh					;
	m_strLow						= rSrcTicker.m_strLow						;
	m_strLastUpdated		= rSrcTicker.m_strLastUpdated		;
	m_strAlertHi				= rSrcTicker.m_strAlertHi				;
	m_strAlertLow				= rSrcTicker.m_strAlertLow			;

  m_strPctChange      = rSrcTicker.m_strPctChange;
  m_strPrevClose      = rSrcTicker.m_strPrevClose;

	m_bMutualFund				= rSrcTicker.m_bMutualFund;

	// Added for version 1 to handle trade details
	int iTrades = rSrcTicker.m_Trades.GetSize();
	for ( int i=0; i<iTrades; i++) {
		CTradeInf *pTrade = (CTradeInf *)rSrcTicker.m_Trades.GetAt(i);
		if (pTrade) {
			CTradeInf *p = new CTradeInf(*pTrade);
			m_Trades.Add(p);
		}
	}

	// Added for version 2
  m_tcOpt = rSrcTicker.m_tcOpt;

	// Added for version 3
  m_strCoName = rSrcTicker.m_strCoName;
  m_bMerge = rSrcTicker.m_bMerge;
  m_nTechChartsReq = rSrcTicker.m_nTechChartsReq;
  m_dtPicked = rSrcTicker.m_dtPicked;

	m_Value.m_Score = rSrcTicker.m_Value.m_Score;
}

CStkTicker::~CStkTicker()
{
	while (m_Trades.GetSize()) {
		CTradeInf *pTrade = (CTradeInf *)m_Trades.GetAt(0);
		if( pTrade) {
			m_Trades.RemoveAt(0);
			delete pTrade;
      pTrade=NULL;
		}
	}
}


BEGIN_MESSAGE_MAP(CStkTicker, CCmdTarget)
	//{{AFX_MSG_MAP(CStkTicker)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStkTicker message handlers

void CStkTicker::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code

		ar << THIS_VERSION;

    if ( m_strSymbol.Find('$') >= 0 )  {
      m_strSymbol = m_strSymbol.Mid(1);
    }
      
      ar	<< m_bStdTicker
				<< m_bAlert
				<< m_lvi.mask
				<< m_lvi.iImage
				<< m_strSymbol
				<< m_strLast
				<< m_strChange
				<< m_strVolume
				<< m_strHigh
				<< m_strLow
				<< m_strLastUpdated
				<< m_strAlertHi
				<< m_strAlertLow
			  << m_bMutualFund;

		// Added for Version 1
		WriteVerOne(ar);

		// Added for Version 2
		WriteVerTwo(ar);

		// Added for Version 3
		WriteVerThree(ar);

    // Added for version 4
		WriteVerFour(ar);

		// Added for version 5
		WriteVerFive(ar);

		// Added for version 6
		WriteVerSix(ar);

		// Added for version 7 - RGB
		WriteVerSeven(ar);

	}
	else
	{	// loading code
		ar >> m_nVer;

		switch ( m_nVer ) {
			case -1:
			case 0:
				ReadVerZero(ar);
				break;

			case 1:
				ReadVerZero(ar);
				ReadVerOne(ar);
				break;

			case 2:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				break;

			case 3:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				break;

			case 4:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				ReadVerFour(ar);
				break;

			case 5:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				ReadVerFour(ar);
				ReadVerFive(ar);
				break;

			case 6:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				ReadVerFour(ar);
				ReadVerFive(ar);
				ReadVerSix(ar);
				break;

			case 7:
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				ReadVerFour(ar);
				ReadVerFive(ar);
				ReadVerSix(ar);
				ReadVerSeven(ar); // RGB

				break;

			default:
				AfxMessageBox((LPCTSTR)"Unable to read ticker information.");
				return;
		}
	}
}

void CStkTicker::ReadVerZero(CArchive& ar)
{
	ar	>> m_bStdTicker
			>> m_bAlert
			>> m_lvi.mask
			>> m_lvi.iImage
			>> m_strSymbol
			>> m_strLast
			>> m_strChange
			>> m_strVolume
			>> m_strHigh
			>> m_strLow
			>> m_strLastUpdated
			>> m_strAlertHi
			>> m_strAlertLow
			>> m_bMutualFund; 
}

void CStkTicker::WriteVerOne(CArchive& ar)
{
	int iSize = m_Trades.GetSize();
	ar << iSize;

	for (int i=0; i<iSize; i++ ) {
		CTradeInf *p = (CTradeInf *)m_Trades.GetAt(i);
		if(p) {
			p->Serialize(ar);
		}
	}
}

void CStkTicker::ReadVerOne(CArchive& ar)
{
	int iSize;
	ar >> iSize;

	for ( int i=0; i<iSize; i++) {
		CTradeInf *p = new CTradeInf;
		p->Serialize(ar);
		m_Trades.Add(p);
	}
}

void CStkTicker::WriteVerTwo(CArchive& ar)
{
	m_tcOpt.Serialize(ar);
}

void CStkTicker::ReadVerTwo(CArchive& ar)
{
	m_tcOpt.Serialize(ar);
}

void CStkTicker::WriteVerThree(CArchive& ar)
{
  ar << m_strCoName;
}

void CStkTicker::ReadVerThree(CArchive& ar)
{
	ar >> m_strCoName;
}

void CStkTicker::WriteVerFour(CArchive& ar)
{
  m_Value.Serialize(ar);
}

void CStkTicker::WriteVerFive(CArchive& ar)
{
  ar << m_strPctChange;
}
void CStkTicker::WriteVerSix(CArchive& ar)
{
  ar << m_dtPicked;
}
void CStkTicker::WriteVerSeven(CArchive& ar)
{
  m_rgb.Serialize(ar);
}
void CStkTicker::ReadVerFour(CArchive& ar)
{
  m_Value.Serialize(ar);
}

void CStkTicker::ReadVerFive(CArchive& ar)
{
  ar >> m_strPctChange;
}

void CStkTicker::ReadVerSix(CArchive& ar)
{
  ar >> m_dtPicked;
}
void CStkTicker::ReadVerSeven(CArchive& ar)
{
  m_rgb.Serialize(ar);
}



/////////////////////////////////////////////////////////////////////////////
// CValueData

IMPLEMENT_DYNCREATE(CValueData, CCmdTarget)

CValueData::~CValueData()
{

}


BEGIN_MESSAGE_MAP(CValueData, CCmdTarget)
	//{{AFX_MSG_MAP(CValueData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValueData message handlers

void CValueData::Serialize(CArchive& ar) 
{
	if ( m_b_donot_upd_strMeanEst4 > 1 ) m_b_donot_upd_strMeanEst4 = 0;
	if ( m_b_donot_upd_strPE > 1 ) m_b_donot_upd_strPE = 0;
	if ( m_b_donot_upd_strProj5YrGrowth > 1 ) m_b_donot_upd_strProj5YrGrowth = 0;


	if (ar.IsStoring())
	{	// storing code
    ar << VALUE_VERSION
        <<  m_strMeanEst1
        <<  m_strMeanEst2
        <<  m_strMeanEst3
        <<  m_strMeanEst4

        <<  m_strHiEst1
        <<  m_strHiEst2
        <<  m_strHiEst3
        <<  m_strHiEst4

        <<  m_strLowEst1
        <<  m_strLowEst2
        <<  m_strLowEst3
        <<  m_strLowEst4

        
        <<  m_strRevGrowth1
        <<  m_strRevGrowth2

        <<  m_strNetIncGrowth1
        <<  m_strNetIncGrowth2

        <<  m_strEPSGrowth1
        <<  m_strEPSGrowth2

        <<  m_strEquityGrowth1
        <<  m_strPE

        <<  m_strProj5YrGrowth
        <<  m_fCGI
        <<  m_bEarnEst
        <<  m_bGrowthRates
				<<  m_b_donot_upd_strMeanEst4
				<<  m_b_donot_upd_strPE
				<<  m_b_donot_upd_strProj5YrGrowth;
	}
	else
	{	// loading code

		int nVer;
		ar >> nVer;
		ar.SetObjectSchema(nVer);

		switch ( nVer ) {
			case (-1):
			case (0):
				ReadVerZero(ar);
				break;
			case (1):
				ReadVerZero(ar);
				ReadVerOne(ar);
				break;
	  }
  }
}

void CValueData::ReadVerZero(CArchive& ar)
{
  ar >>  m_strMeanEst1
  >>  m_strMeanEst2
  >>  m_strMeanEst3
  >>  m_strMeanEst4

  >>  m_strHiEst1
  >>  m_strHiEst2
  >>  m_strHiEst3
  >>  m_strHiEst4

  >>  m_strLowEst1
  >>  m_strLowEst2
  >>  m_strLowEst3
  >>  m_strLowEst4


  >>  m_strRevGrowth1
  >>  m_strRevGrowth2

  >>  m_strNetIncGrowth1
  >>  m_strNetIncGrowth2

  >>  m_strEPSGrowth1
  >>  m_strEPSGrowth2

  >>  m_strEquityGrowth1
  >>  m_strPE

  >>  m_strProj5YrGrowth
  >>  m_fCGI
  >>  m_bEarnEst
  >>  m_bGrowthRates;

}
void CValueData::ReadVerOne(CArchive& ar)
{
	ar >> m_b_donot_upd_strMeanEst4
		 >> m_b_donot_upd_strPE
		 >> m_b_donot_upd_strProj5YrGrowth;

	if ( m_b_donot_upd_strMeanEst4 > 1 ) m_b_donot_upd_strMeanEst4 = 0;
	if ( m_b_donot_upd_strPE > 1 ) m_b_donot_upd_strPE = 0;
	if ( m_b_donot_upd_strProj5YrGrowth > 1 ) m_b_donot_upd_strProj5YrGrowth = 0;

}

////////////////////////////////////////////////////////////////////////////
// CRGBData

IMPLEMENT_DYNCREATE(CRGBData, CCmdTarget)

CRGBData::~CRGBData()
{
}


BEGIN_MESSAGE_MAP(CRGBData, CCmdTarget)
	//{{AFX_MSG_MAP(CRGBData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGBData message handlers

void CRGBData::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
    ar << RGB_VERSION
        <<  m_MktCap
        <<  m_MA50
        <<  m_MA200
        <<  m_ROE

        <<  m_EBITDA
        <<  m_EV
        <<  m_LCF
        <<  m_LCF
				<< m_TotCash
				<< m_AvgVol_10Day
				<< m_AvgVol_3Mth
				<< m_QRG
				<< m_QEG
				<< m_NIAC
				<< m_PE
				<< m_PB
				<< m_index
				<< m_Debt
				<< m_SharesOS
				<< m_EPS
				<< m_BVS
				<< m_ROIC
				<< m_divR;
	}
	else
	{	// loading code

		int nVer;
		ar >> nVer;
		ar.SetObjectSchema(nVer);

		switch ( nVer ) {
			case (-1):
			case (0):
				ReadVerZero(ar);
				break;
			case (1):
				ReadVerZero(ar);
				ReadVerOne(ar);
				break;
			case (2):
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				break;
			case (3):
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				break;


	  }
  }
}

void CRGBData::ReadVerZero(CArchive& ar)
{
  ar		>>  m_MktCap
        >>  m_MA50
        >>  m_MA200
        >>  m_ROE

        >>  m_EBITDA
        >>  m_EV
        >>  m_LCF
        >>  m_Dummy 
				>> m_TotCash
				>> m_AvgVol_10Day
				>> m_AvgVol_3Mth
				>> m_QRG
				>> m_QEG
				>> m_NIAC;

}
void CRGBData::ReadVerOne(CArchive& ar)
{
  ar		>>  m_PE
        >>  m_PB
        >>  m_index;
}

void CRGBData::ReadVerTwo(CArchive& ar)
{
  ar		>> m_Debt
				>> m_SharesOS
				>> m_EPS
				>> m_BVS
				>> m_ROIC;
}
void CRGBData::ReadVerThree(CArchive& ar)
{
  ar		>> m_divR;
}
