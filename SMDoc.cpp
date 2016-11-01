// SMDoc.cpp : implementation of the CSMDoc class

#include "stdafx.h"
#include "StockMon.h"
#include "StkTickr.h"
#include "SMDoc.h"
#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"
#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

#define THIS_VERSION 4
/////////////////////////////////////////////////////////////////////////////
// CSMDoc

//IMPLEMENT_DYNCREATE(CSMDoc, CDocument)
IMPLEMENT_SERIAL(CSMDoc, CDocument, VERSIONABLE_SCHEMA|THIS_VERSION)

BEGIN_MESSAGE_MAP(CSMDoc, CDocument)
	//{{AFX_MSG_MAP(CSMDoc)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMDoc construction/destruction

CSMDoc::CSMDoc()
{
	// TODO: add one-time construction code here
	m_nVer	= THIS_VERSION;

	// Options from Update PropertyPage
	m_bDisableUpdateonWkends = FALSE;
	m_bAutoUpdates = TRUE;
	m_strOpenTime.LoadString(IDS_OPEN_TIME);
	m_strCloseTime.LoadString(IDS_CLOSE_TIME);
	m_nInterval = 15*60*1000;   // 15 min
	m_nMaxStksInReq = 50;

	// Options from General PropertyPage
	m_bConfirmDel=FALSE;
	m_bAutoSaveDoc=FALSE;
	m_bMakeSymbolsUpperCase=TRUE;
	m_DisplayOptions = 0;
//	m_strProxy.LoadString(IDS_PROXY);
//	m_strPort.LoadString(IDS_PORT);
	m_bUseProxy = FALSE;
	
	m_strIP_DBC.LoadString(IDS_IP_DBC);
	m_strIP_MONEY.LoadString(IDS_IP_MONEY);

	m_Freq = 0;
	m_AlertType = 0;
	m_dwSeconds = 60;

	m_strPts.LoadString(IDS_POINTS);
	m_strType.LoadString(IDS_TYPES);
  // Select TD Site (actual URL: http://stockcharts.com/c-sc/sc?s=IVV&p=D&b=5&g=0&i=t73156347986&r=1416852482644)
  //m_strChartString = "&b=5&g=0&i=t62341849868&r=1428596408585"; 
  // For Yahoo:
  //http://chart.finance.yahoo.com/z?s=IVV&t=6m&p=e10,e15,m200,m65&l=on&z=l&q=c&a=m26-12-9,ss,vm&c=
  m_strChartString = "&p=e10,m15,m200,m65&l=on&z=l&q=c&a=m26-12-9,ss,vm";
	try {
		CString str;

		str.LoadString(IDS_NASDAQ_COMPX);
		m_StdTickerArray.Add(str);

		str.LoadString(IDS_INDU);
		m_StdTickerArray.Add(str);


		str.LoadString(IDS_INX);
		m_StdTickerArray.Add(str);

		str.LoadString(IDS_OEX);
		m_StdTickerArray.Add(str);


		str.LoadString(IDS_IUX);
		m_StdTickerArray.Add(str);

	}
	catch(...) {
	}

	m_strDowJones = "All Companies                  ()";
	m_strSP500    = "All Companies                  ()";
  m_strIndustryGrp = "All Industries              ()";;
	m_strExchg       = "All Exchanges               ()";;

  m_bWebSite = YAHOO;
	m_bHangup = FALSE;

	m_strROE="20";

	//S&P Reference
	ROE=17.4;
	PE=17.2;
	PB=2.9;
	GR=11;
}

CSMDoc::~CSMDoc()
{
  EmptyTickers();
}

void CSMDoc::EmptyTickers()
{
	CStkTicker *p=NULL;

	for ( int i=0; i<m_TickerArray.GetSize(); i++) {
		p = (CStkTicker *)m_TickerArray[i];
    if(::IsWindow(THEAPP()->m_pMainWnd->GetSafeHwnd())) {
//	    ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.DeleteString(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.FindString(-1,p->m_strSymbol));
	      ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.ResetContent();
    }
		delete p;
	}
	m_TickerArray.RemoveAll();
}

void *CSMDoc::FindTicker(CString& str)
{
	CStkTicker *p=NULL;

	for ( int i=0; i<m_TickerArray.GetSize(); i++) {
		p = (CStkTicker *)m_TickerArray[i];
		if (p->m_strSymbol == str) return (void *)p;
	}
	return NULL;
}

BOOL CSMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSMDoc serialization

void CSMDoc::Serialize(CArchive& ar)
{
	CSingleLock sLock(&m_mutex);
	sLock.Lock();

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		// Serialize all the preferences

		ar << THIS_VERSION;

		ar << m_nInterval
			 << m_bDisableUpdateonWkends
			 << m_bAutoUpdates
			 << m_strOpenTime
			 <<	m_strCloseTime
			 <<	m_nInterval
			 << m_nMaxStksInReq
	// Options from General PropertyPage
  		 << m_bConfirmDel
			 << m_bAutoSaveDoc
			 << m_bMakeSymbolsUpperCase
	// Options from Proxy PropertyPage
 			 << m_strProxy
			 << m_strPort
			 <<	m_bUseProxy
			 << m_strIP_DBC
			 << m_strIP_MONEY

	// Options from Price Alert PropertyPage
			 << m_Freq
			 <<	m_AlertType
			 <<	m_dwSeconds
			 <<	m_strWavFile;

	// Begin Addition for version 1 {
 	// Options from Chart PropertyPage
	  ar << m_strPts
			 << m_strType
			 << m_strImageLocation;
	// End Addition for version 1 }

	// Begin Addition for version 2 {
  // Stock Screen Criteria
	  ar << m_strPrice_Min
		   << m_strPrice_Max
		   << m_strPBRatio_Min
       << m_strPBRatio_Max
       << m_strPSRatio_Min
       << m_strPSRatio_Max
       << m_strPE_Min
       << m_strPE_Max
       << m_strBeta_Min
       << m_strBeta_Max
       << m_strYield_Min
       << m_strYield_Max
       << m_strEPSChg_Min
       << m_strEPSChg_Max
       << m_strGr_Min
       << m_strGr_Max
       << m_strDPRatio_Min
       << m_strDPRatio_Max
       << m_strROE_Min
       << m_strROE_Max
       << m_strDERatio_Min
       << m_strDERatio_Max
       << m_strSales_Min
       << m_strSales_Max
       << m_strMktCap_Min
       << m_strMktCap_Max;
	// End Addition for version 2 }

	// Begin Addition for version 3 {
  // Stock Screen Criteria
	  ar << m_strDowJones
	     << m_strSP500
	     << m_strIndustryGrp
	     << m_strExchg;
	// End Addition for version 3 }

	// Begin Addition for version 4 {
      ar	<< m_DUP
	      << m_bHangup;

	// End Addition for version 4 }

    CSMView *p=NULL;
    POSITION pos = GetFirstViewPosition();   
    while (pos != NULL)   {
      CView* pView = GetNextView(pos);
      if ( pView->IsKindOf(RUNTIME_CLASS(CSMView))) {
        p = (CSMView *)pView;
        break;
      }
    }

    if(!p) {
      int iSize = m_TickerArray.GetSize();
      ar << iSize;
      for (int i=0; i<iSize; i++ ) {
	      CStkTicker *p = (CStkTicker *)m_TickerArray.GetAt(i);
	      if(p) {
		      p->Serialize(ar);

          if(::IsWindow(THEAPP()->m_pMainWnd->GetSafeHwnd())) {
      //	    ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.DeleteString(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.FindString(-1,p->m_strSymbol));
// 	            ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.ResetContent();
          }
	      }
      }
    }
    else {
	    CListCtrl& ListCtrl=p->GetListCtrl();

      // get item data
	    WCHAR szBuff[MAX_PATH];
	    LV_ITEM lvi;
	    lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	    lvi.iSubItem=0;
	    lvi.pszText=szBuff;
	    lvi.cchTextMax=sizeof(szBuff);
	    lvi.lParam=NULL;
	    lvi.stateMask=0xFFFF;		// get all state flags

	    int iCount= ListCtrl.GetItemCount();
      ar << iCount;

      for(	int i=0; i<iCount; i++ ) {
		    lvi.iItem = i;
		    if(ListCtrl.GetItem(&lvi)) {
			    CStkTicker *p = (CStkTicker *) lvi.lParam;
			    if (p) {
				    p->Serialize(ar);

            if(::IsWindow(THEAPP()->m_pMainWnd->GetSafeHwnd())) {
        //	    ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.DeleteString(((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.FindString(-1,p->m_strSymbol));
//	              ((CMainFrame *)THEAPP()->m_pMainWnd)->m_wndAddress.ResetContent();
            }
			    }
		    }
	    }
    }
	}
	else
	{
		// TODO: add loading code here
    EmptyTickers();

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

			case (4):
				ReadVerZero(ar);
				ReadVerOne(ar);
				ReadVerTwo(ar);
				ReadVerThree(ar);
				ReadVerFour(ar);
				break;

      default:
				AfxMessageBox((LPCTSTR)"Unsupported document");
				sLock.Unlock();
				return;
		}

		int iSize;
		ar >> iSize;


		for ( int i=0; i<iSize; i++) {
			CStkTicker *p = new CStkTicker;
			p->Serialize(ar);
//			CString szPathName = ar.m_strFileName;
//			int iPos1 = szPathName.ReverseFind('_');
//			int iPos2 = szPathName.ReverseFind('.');
//			CString dt = szPathName.Mid(iPos1+1,iPos2-iPos1);
//			if ( dt.Find((LPCTSTR)"\\") <= 0  ) {
//				dt = dt.Left(2) + "/" + dt.Mid(2,2) + "/" + dt.Mid(4,2);
//				p->m_dtPicked = dt;
//			} else {
//				p->m_dtPicked.Empty();
//			}
			m_TickerArray.Add(p);
		}
	}
	sLock.Unlock();
	m_strIP_DBC.LoadString(IDS_IP_DBC);

}

void CSMDoc::ReadVerZero(CArchive& ar)
{
	ar >> m_nInterval
		 >> m_bDisableUpdateonWkends
		 >>	m_bAutoUpdates
		 >>	m_strOpenTime
		 >>	m_strCloseTime
		 >>	m_nInterval
		 >> m_nMaxStksInReq
	// Options from General PropertyPage
		 >> m_bConfirmDel
		 >> m_bAutoSaveDoc
		 >> m_bMakeSymbolsUpperCase
	// Options from Proxy PropertyPage
 		 >> m_strProxy
		 >> m_strPort
		 >>	m_bUseProxy
		 >> m_strIP_DBC
		 >> m_strIP_MONEY
	// Options from Price Alert PropertyPage
		 >> m_Freq
		 >>	m_AlertType
		 >> m_dwSeconds
		 >> m_strWavFile;

}

void CSMDoc::ReadVerOne(CArchive& ar)
{
	// Options from Chart PropertyPage
	ar >> m_strPts
		 >> m_strType
		 >> m_strImageLocation;
}

void CSMDoc::ReadVerTwo(CArchive& ar)
{
	// Stock Screen Criteria
	ar >> m_strPrice_Min
		 >> m_strPrice_Max
		 >> m_strPBRatio_Min
     >> m_strPBRatio_Max
     >> m_strPSRatio_Min
     >> m_strPSRatio_Max
     >> m_strPE_Min
     >> m_strPE_Max
     >> m_strBeta_Min
     >> m_strBeta_Max
     >> m_strYield_Min
     >> m_strYield_Max
     >> m_strEPSChg_Min
     >> m_strEPSChg_Max
     >> m_strGr_Min
     >> m_strGr_Max
     >> m_strDPRatio_Min
     >> m_strDPRatio_Max
     >> m_strROE_Min
     >> m_strROE_Max
     >> m_strDERatio_Min
     >> m_strDERatio_Max
     >> m_strSales_Min
     >> m_strSales_Max
     >> m_strMktCap_Min
     >> m_strMktCap_Max;
}

void CSMDoc::ReadVerThree(CArchive& ar)
{
	// Stock Screen Criteria
  ar >> m_strDowJones
     >> m_strSP500
     >> m_strIndustryGrp
     >> m_strExchg;
}

void CSMDoc::ReadVerFour(CArchive& ar)
{
	// Dialup Options
  ar >> m_DUP
     >> m_bHangup;
}


/////////////////////////////////////////////////////////////////////////////
// CSMDoc diagnostics

#ifdef _DEBUG
void CSMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSMDoc commands


BOOL CSMDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bAutoSaveDoc) {
		DoFileSave();
		return TRUE;
	}

	return CDocument::SaveModified();
}

void CSMDoc::OnFileSendMail() 
{
	CDocument::OnFileSendMail();
	
}

void CSMDoc::OnUpdateFileSendMail(CCmdUI* pCmdUI) 
{
	CDocument::OnUpdateFileSendMail(pCmdUI) ;
	
}

void CSMDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	EmptyTickers();
//	CDocument::DeleteContents();
}

CString CSMDoc::ConvertToDecimal( CString rString, int nDec/*=4*/ )
{
	CString strRet;

	if ( -1 != rString.Find('.') ) {
		int iComma = rString.Find(',');
		if (iComma >= 0 ) {
			strRet = rString.Left(iComma);
			strRet += rString.Mid(iComma+1);
		}
		else {
			return rString;
		}

		return strRet;
	}


	int iSpace = rString.Find(' ');
	CString strInteger = rString.Left(iSpace==-1 ? 0 : iSpace);
	if ( !strInteger.IsEmpty() && !isdigit(strInteger[0]) ) {
		strInteger = strInteger.Mid(1);
	}


	int iSlash = rString.Find('/');
	if ( iSlash == -1 ) {
		return rString;
	}
	
	rString.Replace(',', ' ');		
	CString strNum(rString.Mid(iSpace+1, iSlash-iSpace-1));
	CString strDenom(rString.Right(rString.GetLength() - iSlash - 1));

	double source = _wtof(strNum) / _wtof(strDenom);
	CString str;
	str.Format((LPCTSTR)"%f", source);

	if ( -1 != rString.Find('+') ) {
		strRet = '+';
	}
	else if ( -1 != rString.Find('-')) {
		strRet = '-';
	}

	if ( iSpace == -1 ) {
		strRet += '0';
	}

	strRet += strInteger;
	strRet += '.';
	strRet += str.Mid(str.Find('.')+1);

	return strRet;
}

BOOL CSMDoc::IsStdTicker(CString& rString)
{
	for ( int i=0; i<m_StdTickerArray.GetSize(); i++ ) {
		CString str = m_StdTickerArray[i];
		if ( str == rString )
			return TRUE;
	}

	return FALSE;
}

CString CSMDoc::RemoveChar(CString s, WCHAR c)
{
	CString ret;
	int iLen=s.GetLength();
	for (int i=0; i<iLen; i++) {
		if ( s.Mid(i,1) == c ) continue;
		ret += s.Mid(i,1);
	}
	return ret;
}
BOOL CSMDoc::bShowRGB(CStkTicker *p)
{
	if (!p) return 0;

//	BOOL bROE = _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()-1)) > 0 && _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()-1)) > _wtof(m_strROE);
	BOOL bROE = _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()-1)) > 0 && _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()-1)) > 0;
	/*
	BOOL bEbitda = _wtof(p->m_rgb.m_EBITDA.Left(p->m_rgb.m_EBITDA.GetLength()-1)) > 0;
	BOOL bOCF = _wtof(p->m_rgb.m_EV.Left(p->m_rgb.m_EV.GetLength()-1)) > 0 || p->m_rgb.m_EV == "N/A";
	BOOL bLCF = _wtof(p->m_rgb.m_LCF.Left(p->m_rgb.m_LCF.GetLength()-1)) > 0 || p->m_rgb.m_LCF == "N/A";
	BOOL bQRG = _wtof(p->m_rgb.m_QRG.Left(p->m_rgb.m_QRG.GetLength()-1)) > 0 || p->m_rgb.m_QRG == "N/A";
	BOOL bQEG = _wtof(p->m_rgb.m_QEG.Left(p->m_rgb.m_QEG.GetLength()-1)) > 0 || p->m_rgb.m_QEG == "N/A";
	BOOL bNIAC = _wtof(p->m_rgb.m_NIAC.Left(p->m_rgb.m_NIAC.GetLength()-1)) > 0 || p->m_rgb.m_NIAC == "N/A";
	*/
	BOOL bROIC = _wtof(p->m_rgb.m_ROIC.Left(p->m_rgb.m_ROIC.GetLength()-1)) > 10 || p->m_rgb.m_ROIC == "N/A";
	//BOOL bShow = bROE  && bEbitda && bOCF & bQRG & bQEG & bNIAC & bROIC;
	BOOL blcf = _wtof(p->m_rgb.m_LCF) > 0;
	BOOL bShow = bROE  & bROIC & blcf;
	
	return bShow;
}

BOOL CSMDoc::bShowValuation(CStkTicker *p)
{
	if (!p) return 0;

	BOOL bROIC = _wtof(p->m_rgb.m_ROIC.Left(p->m_rgb.m_ROIC.GetLength()-1)) > 10 || p->m_rgb.m_ROIC == "N/A";
	return bROIC;
}


float CSMDoc::CalcRGBIndex(CStkTicker *p)
{
	if (!p) return 0;

	// Calc Index
	float index=0;
	float cmp_ROE = _wtof(p->m_rgb.m_ROE.Left(p->m_rgb.m_ROE.GetLength()-1)) / ROE;
	float cmp_PE	= _wtof(p->m_rgb.m_PE) / PE;
	float cmp_PB	= _wtof(p->m_rgb.m_PB) / PB;
	float cmp_GR	= _wtof(p->m_Value.m_strProj5YrGrowth) / GR;

	float v_PE	= (float)min(cmp_ROE * PE,min(_wtof(p->m_rgb.m_PE),PE)) ;
	float v_PB	= min(cmp_ROE * PB, min(_wtof(p->m_rgb.m_PB), PB));
	float v_GR	= cmp_ROE<1 ? (1+5*(1-cmp_ROE))*GR/100 : min(_wtof(p->m_Value.m_strProj5YrGrowth),GR);

	index = _wtof(p->m_rgb.m_PE) >= v_PE ? 0 : 1;
	index += _wtof(p->m_rgb.m_PB) >= v_PB ? 0 : 1;
	index += _wtof(p->m_Value.m_strProj5YrGrowth) >= v_GR ? 1 : 0;

	index += v_PE / _wtof(p->m_rgb.m_PE);
	index += v_PB / _wtof(p->m_rgb.m_PB);
	index += min(v_GR / _wtof(p->m_Value.m_strProj5YrGrowth), _wtof(p->m_Value.m_strProj5YrGrowth)/100);
	//if ( index <=0 ) index=0;
	p->m_rgb.m_index.Format(_T("%2.2f"), index);
}

void CSMDoc::CalcROIC(CStkTicker *p)
{
	if (!p) return;
	float debt, eps, shares, bvs;

	debt = ConvertToNumber(p->m_rgb.m_Debt);
	eps  = ConvertToNumber(p->m_rgb.m_EPS);
	shares = ConvertToNumber(p->m_rgb.m_SharesOS);
	bvs = ConvertToNumber(p->m_rgb.m_BVS);
	if ( eps <=0 && shares <=0 || bvs <=0 ) {
		p->m_rgb.m_ROIC = "999";
	}

	try {
		p->m_rgb.m_ROIC.Empty();
		p->m_rgb.m_ROIC.Format(_T("%2.2f"), 100*(eps/((debt/shares)+bvs)));
		;
	} catch(...) {
	}
}
float CSMDoc::ConvertToNumber(CString str) {
	WCHAR x;
	x = str.Right(1)[0];
	float f=0;
	switch (x) {
		case 'B':
			f = _ttof(str.Left(str.GetLength()-1)) * float(1000000000);
			break;
		case 'K':
			f = _ttof(str.Left(str.GetLength()-1)) * float(1000);
			break;
		case 'M':
			f = _ttof(str.Left(str.GetLength()-1)) * float(1000000);
			break;
		default:
			f = _ttof(str);
	}
	return f;

}
