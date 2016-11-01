// ui.cpp : implementation file
//

#include "stdafx.h"
#include <direct.h> // for chdir
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h "
#include "SMDoc.h"
#include "MainFrm.h"
#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"
#include "MktSumVw.h"

#include "ui.h"

/*#include <ras.h>
#include <rassapi.h>
#include <rasdlg.h>
#include <raserror.h>
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUPdates property page

IMPLEMENT_DYNCREATE(CUPdates, CPropertyPage)

CUPdates::CUPdates() : CPropertyPage(CUPdates::IDD)
{
	//{{AFX_DATA_INIT(CUPdates)
	m_nInterval = 0;
	m_bDisableUpdateonWkends = FALSE;
	m_bAutoUpdates = -1;
	m_strOpenTime = _T("");
	m_strCloseTime = _T("");
	m_nMaxStksInReq=0;
	//}}AFX_DATA_INIT
}

CUPdates::~CUPdates()
{
}

void CUPdates::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUPdates)
	DDX_Text(pDX, ID_UPDATES_INTERVAL, m_nInterval);
	DDX_Check(pDX, ID_UPDATES_NO_WKENDS, m_bDisableUpdateonWkends);
	DDX_Radio(pDX, ID_UPDATE_DISABLE_AUTO, m_bAutoUpdates);
	DDX_Text(pDX, ID_UPDATE_OPEN, m_strOpenTime);
	DDX_Text(pDX, ID_UPDATE_CLOSE, m_strCloseTime);
	DDX_Text(pDX, IDC_EDIT2, m_nMaxStksInReq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUPdates, CPropertyPage)
	//{{AFX_MSG_MAP(CUPdates)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUPdates message handlers
/////////////////////////////////////////////////////////////////////////////
// CGeneralOptions property page

IMPLEMENT_DYNCREATE(CGeneralOptions, CPropertyPage)

CGeneralOptions::CGeneralOptions() : CPropertyPage(CGeneralOptions::IDD)
{
	//{{AFX_DATA_INIT(CGeneralOptions)
	m_bConfirmDel = FALSE;
	m_bAutoSaveDoc = FALSE;
	m_bMakeSymbolsUpperCase = FALSE;
	m_DisplayOptions = -1;
	//}}AFX_DATA_INIT
}

CGeneralOptions::~CGeneralOptions()
{
}

void CGeneralOptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralOptions)
	DDX_Check(pDX, D_GEN_CONFIRM_DEL, m_bConfirmDel);
	DDX_Check(pDX, ID_GEN_AUTO_SAVE_DOC, m_bAutoSaveDoc);
	DDX_Check(pDX, ID_GEN_UPPER_CASE, m_bMakeSymbolsUpperCase);
	DDX_Radio(pDX, IDC_VIEW_FRACTIONS, m_DisplayOptions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralOptions, CPropertyPage)
	//{{AFX_MSG_MAP(CGeneralOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralOptions message handlers
/////////////////////////////////////////////////////////////////////////////
// CConfirmDelDlg dialog


CConfirmDelDlg::CConfirmDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfirmDelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfirmDelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfirmDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirmDelDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfirmDelDlg, CDialog)
	//{{AFX_MSG_MAP(CConfirmDelDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirmDelDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CProxyDlg property page

IMPLEMENT_DYNCREATE(CProxyDlg, CPropertyPage)

CProxyDlg::CProxyDlg() : CPropertyPage(CProxyDlg::IDD)
{
	//{{AFX_DATA_INIT(CProxyDlg)
	m_strProxy = _T("");
	m_strPort = _T("");
	m_DUP = _T("");
	m_bUseProxy = -1;
	m_bHangup = FALSE;
	//}}AFX_DATA_INIT
}

CProxyDlg::~CProxyDlg()
{
}

void CProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProxyDlg)
	DDX_Control(pDX, IDC_DUP, m_pLBox);
	DDX_Text(pDX, ID_PROXY_HOST, m_strProxy);
	DDX_Text(pDX, ID_PROXY_PORT, m_strPort);
	DDX_CBString(pDX, IDC_DUP, m_DUP);
	DDX_Radio(pDX, IDC_MODEM, m_bUseProxy);
	DDX_Check(pDX, IDC_HANGUP, m_bHangup);
	//}}AFX_DATA_MAP
}

BOOL CProxyDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
#ifdef _DORAS_

    LPRASENTRYNAME lpRasEntry;
    LPRASENTRYNAME lpTemp;
    DWORD cbBuf;
    DWORD cEntry;
    DWORD dwRet;
    UINT  ndx;
    WCHAR  szMessage[256];

    cbBuf = sizeof(RASENTRYNAME);
    if ((lpRasEntry = ( LPRASENTRYNAME ) malloc((UINT)cbBuf)) != NULL ) 
    {
        lpRasEntry->dwSize = sizeof(RASENTRYNAME);
        dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
        if ( dwRet == ERROR_BUFFER_TOO_SMALL )
        {
            if ((lpTemp = ( LPRASENTRYNAME ) realloc ( lpRasEntry, (UINT)cbBuf )) != NULL )
            {
                lpRasEntry = lpTemp;
                dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
            }
            else
            {
                dwRet = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
        else if ( dwRet != 0 ) // other error
        {
            if ( RasGetErrorString( (UINT)dwRet, szMessage, 256 ) != 0 )
                wsprintf( (LPSTR)szMessage, "Undefined RasEnumEntries Error." );

            AfxMessageBox((LPSTR)szMessage);
        }

        if ( dwRet == 0 )  // No errors
        {
            for ( ndx = 0; ndx < cEntry; ndx++ ) 
				m_pLBox.AddString(lpRasEntry[ndx].szEntryName);
		}

        free( lpRasEntry );
    } 

  m_pLBox.SelectString(-1, m_DUP);

#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProxyDlg::OnNewconn() 
{
#ifdef _DORAS_
	RASPBDLG pb;
	pb.dwSize = sizeof(pb);
	pb.hwndOwner = NULL;
	pb.dwFlags = RASPBDFLAG_ForceCloseOnDial;
	pb.pCallback=NULL;
	RasPhonebookDlg(NULL, NULL, &pb);
#endif
}


BEGIN_MESSAGE_MAP(CProxyDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CProxyDlg)
	ON_BN_CLICKED(IDC_NEWCONN, OnNewconn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProxyDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CSetAlertDlg dialog

IMPLEMENT_DYNCREATE(CSetAlertDlg, CPropertyPage)

CSetAlertDlg::CSetAlertDlg(): CPropertyPage(CSetAlertDlg::IDD)
{
}

CSetAlertDlg::CSetAlertDlg(CPtrArray& rPortfolio,CSMDoc *pDoc, CString& rTicker, CWnd* pParent /*=NULL*/)
	: CPropertyPage(CSetAlertDlg::IDD)
{
	//{{AFX_DATA_INIT(CSetAlertDlg)
	m_strAlertLow = _T("");
	m_strAlertHi = _T("");
	m_strLast = _T("");
	m_strChange = _T("");
	m_strHigh = _T("");
	m_strLow = _T("");
	m_strVolume = _T("");
	m_strLastUpdated = _T("");
	//}}AFX_DATA_INIT
	m_TickerArray.Append(rPortfolio);
	m_pDoc = pDoc;
  m_strTicker = rTicker;
  m_pParent = (CSMView *)pParent;
}

void CSetAlertDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetAlertDlg)
	DDX_Control(pDX, IDC_SYMBOLS, m_LB);
	DDX_Text(pDX, IDC_EDIT1, m_strAlertLow);
	DDX_Text(pDX, IDC_EDIT2, m_strAlertHi);
	DDX_Text(pDX, IDC_LAST, m_strLast);
	DDX_Text(pDX, IDC_CHANGE, m_strChange);
	DDX_Text(pDX, IDC_HIGH, m_strHigh);
	DDX_Text(pDX, IDC_LOW, m_strLow);
	DDX_Text(pDX, IDC_VOLUME, m_strVolume);
	DDX_Text(pDX, IDC_LASTUPDATED, m_strLastUpdated);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetAlertDlg, CDialog)
	//{{AFX_MSG_MAP(CSetAlertDlg)
	ON_LBN_SELCHANGE(IDC_SYMBOLS, OnSelchangeSymbols)
	ON_BN_CLICKED(IDC_APPLY, OnApplyAlert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetAlertDlg message handlers

BOOL CSetAlertDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	

	int iTickers = m_TickerArray.GetSize();
/*
	for ( int i=0; i<iTickers; i++ ) {
		CStkTicker *p = (CStkTicker *)m_TickerArray[i];
		if ( p ) {
			int iPos = m_LB.AddString(p->m_strSymbol);
			m_LB.SetItemData(iPos, (DWORD)p);
		}
	}
*/

  if (m_pParent) {
	  CListCtrl& ListCtrl=m_pParent->GetListCtrl();

	  // get item data
	  WCHAR szBuff[MAX_PATH];
	  LV_ITEM lvi;
	  lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	  lvi.iSubItem=0;
	  lvi.pszText=szBuff;
	  lvi.cchTextMax=sizeof(szBuff);
	  lvi.lParam=NULL;
	  lvi.stateMask=0xFFFF;		// get all state flags


	  for(	int i=0; i<iTickers; i++ ) {
		  lvi.iItem = i;
		  if(ListCtrl.GetItem(&lvi)) {
			  CStkTicker *p = (CStkTicker *) lvi.lParam;
			  if ( p) {
			    int iPos = m_LB.AddString(p->m_strSymbol);
			    m_LB.SetItemData(iPos, (DWORD)p);
			  }
		  }
	  }
  }


	if ( iTickers ) {
		m_LB.SetCurSel(0);
		OnSelchangeSymbols();
	}
	
  if ( !m_strTicker.IsEmpty() ) {
    int iPos = m_LB.SelectString(-1, m_strTicker);
    if ( iPos != LB_ERR ) {
      m_LB.SetCurSel(iPos);
   		OnSelchangeSymbols();
    }
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSetAlertDlg::OnSelchangeSymbols() 
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
		CStkTicker *p = (CStkTicker *)m_LB.GetItemData(iCurSel);
		if ( DWORD(p) != LB_ERR ) {
			m_strLast					= p->m_strLast;
			m_strChange				= p->m_strChange;
			m_strVolume				= p->m_strVolume ;
			m_strHigh					= p->m_strHigh ;
			m_strLow					= p->m_strLow ;
			m_strLastUpdated	= p->m_strLastUpdated	;
			m_strAlertHi			= p->m_strAlertHi			;
			m_strAlertLow			= p->m_strAlertLow			;
			UpdateData(FALSE);
		}
	}
}

void CSetAlertDlg::OnApplyAlert() 
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
		CStkTicker *p = (CStkTicker *)m_LB.GetItemData(iCurSel);
		if ( DWORD(p) != LB_ERR ) {
			UpdateData(TRUE);
			if (m_pDoc) {
				if( m_pDoc->m_DisplayOptions == 0) {
					p->m_strAlertHi		= m_strAlertHi;
					p->m_strAlertLow	= m_strAlertLow;
				}
				else {
					p->m_strAlertHi		= m_pDoc->ConvertToDecimal(m_strAlertHi);
					p->m_strAlertLow	= m_pDoc->ConvertToDecimal(m_strAlertLow);
				}
			}

			if ( !p->m_strAlertHi.IsEmpty() || !p->m_strAlertLow.IsEmpty() ) {
				p->m_bAlert = TRUE;
			}
			else {
				p->m_bAlert = FALSE;
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CConfigAlertDlg property page

IMPLEMENT_DYNCREATE(CConfigAlertDlg, CPropertyPage)

CConfigAlertDlg::CConfigAlertDlg() : CPropertyPage(CConfigAlertDlg::IDD)
{
	//{{AFX_DATA_INIT(CConfigAlertDlg)
	m_Freq = -1;
	m_AlertType = -1;
	m_dwSeconds = 0;
	m_strWAVFile = _T("");
	//}}AFX_DATA_INIT
}

CConfigAlertDlg::~CConfigAlertDlg()
{
}

void CConfigAlertDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigAlertDlg)
	DDX_Radio(pDX, IDC_ALERT_FREQ_ONCE, m_Freq);
	DDX_Radio(pDX, IDC_ALERT_NO_ALERT, m_AlertType);
	DDX_Text(pDX, IDC_ALERT_SECONDS, m_dwSeconds);
	DDX_Text(pDX, 1022, m_strWAVFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigAlertDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CConfigAlertDlg)
	ON_BN_CLICKED(IDC_SELECT_WAV_FILE, OnSelectWavFile)
	ON_BN_CLICKED(IDC_ALERT_PLAY_WAV, OnAlertPlayWav)
	ON_BN_CLICKED(IDC_ALERT_BEEP, OnAlertBeep)
	ON_BN_CLICKED(IDC_ALERT_FLASH_WND, OnAlertFlashWnd)
	ON_BN_CLICKED(IDC_ALERT_NO_ALERT, OnAlertNoAlert)
	ON_BN_CLICKED(IDC_ALERT_WND_TOP, OnAlertWndTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigAlertDlg message handlers


void CConfigAlertDlg::OnSelectWavFile() 
{
	CFileDialog dlg( TRUE,_T("WAV"),_T("*.WAV"),
	                 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("Wave Files (*.WAV)|*.WAV|"));
	if( dlg.DoModal()==IDOK )
	{
		CSMDoc *pDoc = (CSMDoc *)(((CMainFrame *)AfxGetMainWnd())->GetActiveDocument());
		pDoc->m_strWavFile  = dlg.GetPathName();
		m_strWAVFile = pDoc->m_strWavFile;
		UpdateData(FALSE);
	}
}

void CConfigAlertDlg::OnAlertPlayWav() 
{
	GetDlgItem(IDC_SELECT_WAV_FILE)->EnableWindow(TRUE);;
}

void CConfigAlertDlg::OnAlertBeep() 
{
	GetDlgItem(IDC_SELECT_WAV_FILE)->EnableWindow(FALSE);
}

void CConfigAlertDlg::OnAlertFlashWnd() 
{
	GetDlgItem(IDC_SELECT_WAV_FILE)->EnableWindow(FALSE);
}

void CConfigAlertDlg::OnAlertNoAlert() 
{
	GetDlgItem(IDC_SELECT_WAV_FILE)->EnableWindow(FALSE);
}

void CConfigAlertDlg::OnAlertWndTop() 
{
	GetDlgItem(IDC_SELECT_WAV_FILE)->EnableWindow(FALSE);	
}
/////////////////////////////////////////////////////////////////////////////
// CChartPrefDlg property page

IMPLEMENT_DYNCREATE(CChartPrefDlg, CPropertyPage)

CChartPrefDlg::CChartPrefDlg() : CPropertyPage(CChartPrefDlg::IDD)
{
	//{{AFX_DATA_INIT(CChartPrefDlg)
	m_strPts = _T("");
	m_strType = _T("");
	m_strImageLocation = _T("");
  m_strChartString = _T("&b=5&g=0&i=t12734479682&r=1428604054111");
	//}}AFX_DATA_INIT
}

CChartPrefDlg::~CChartPrefDlg()
{
}

void CChartPrefDlg::DoDataExchange(CDataExchange* pDX)
{
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CChartPrefDlg)
  DDX_CBString(pDX, IDC_CHART_PTS, m_strPts);
  DDX_CBString(pDX, IDC_CHART_TYPE, m_strType);
  DDX_Text(pDX, IDC_CHART_LOC, m_strImageLocation);
  //}}AFX_DATA_MAP
  DDX_CBString(pDX, IDC_CHART_STRING, m_strChartString);
}


BEGIN_MESSAGE_MAP(CChartPrefDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CChartPrefDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartPrefDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CRegInsDlg dialog


CRegInsDlg::CRegInsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegInsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegInsDlg)
	m_strInst = _T("");
	m_strRegKey = _T("");
	//}}AFX_DATA_INIT
}


void CRegInsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegInsDlg)
	DDX_Text(pDX, IDC_REG_INSTRUCTIONS, m_strInst);
	DDX_Text(pDX, IDC_REGISTER_KEY, m_strRegKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegInsDlg, CDialog)
	//{{AFX_MSG_MAP(CRegInsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegInsDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CTradeDlg dialog


CTradeDlg::CTradeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTradeDlg::IDD, pParent)
{
	m_strLast = _T("");
	m_strChange = _T("");
	m_strVolume = _T("");
	m_strDayhi = _T("");
	m_strDaylow = _T("");
	m_strDate = _T("");
	m_strPrice = _T("");
	m_strShares = _T("");
	m_strCommision = _T("");
	m_strAmount = _T("");
}

CTradeDlg::CTradeDlg(CPtrArray& rPortfolio,CSMDoc *pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CTradeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTradeDlg)
	m_strLast = _T("");
	m_strChange = _T("");
	m_strVolume = _T("");
	m_strDayhi = _T("");
	m_strDaylow = _T("");
	m_strDate = _T("");
	m_strPrice = _T("");
	m_strShares = _T("");
	m_strCommision = _T("");
	m_strAmount = _T("");
	m_bBuy = -1;
	//}}AFX_DATA_INIT
	m_TickerArray.Append(rPortfolio);
	m_pDoc = pDoc;

}

void CTradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTradeDlg)
	DDX_Control(pDX, IDB_APPLY, m_rApply);
	DDX_Control(pDX, IDC_COMMISION, m_rCommisions);
	DDX_Control(pDX, IDC_SHARES, m_rShares);
	DDX_Control(pDX, IDC_PRICE, m_rPrice);
	DDX_Control(pDX, IDC_DATE, m_rDate);
	DDX_Control(pDX, IDC_PORTFOLIO, m_LB);
	DDX_Text(pDX, IDC_LAST, m_strLast);
	DDX_Text(pDX, IDC_CHANGE, m_strChange);
	DDX_Text(pDX, IDC_VOLUME, m_strVolume);
	DDX_Text(pDX, IDC_DAY_HI, m_strDayhi);
	DDX_Text(pDX, IDC_DAY_LOW, m_strDaylow);
	DDX_Text(pDX, IDC_DATE, m_strDate);
	DDX_Text(pDX, IDC_PRICE, m_strPrice);
	DDX_Text(pDX, IDC_SHARES, m_strShares);
	DDX_Text(pDX, IDC_COMMISION, m_strCommision);
	DDX_Text(pDX, IDC_AMOUNT, m_strAmount);
	DDX_Radio(pDX, IDC_BUY, m_bBuy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTradeDlg, CDialog)
	//{{AFX_MSG_MAP(CTradeDlg)
	ON_LBN_SELCHANGE(IDC_PORTFOLIO, OnSelchangePortfolio)
	ON_BN_CLICKED(IDC_BUY, OnBuy)
	ON_BN_CLICKED(IDC_SELL, OnSell)
	ON_BN_CLICKED(IDB_APPLY, OnApply)
	ON_LBN_DBLCLK(IDC_PORTFOLIO, OnDblclkPortfolio)
	ON_EN_CHANGE(IDC_PRICE, OnChangePrice)
	ON_EN_CHANGE(IDC_SHARES, OnChangeShares)
	ON_EN_CHANGE(IDC_COMMISION, OnChangeCommision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeDlg message handlers

BOOL CTradeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int iTickers = m_TickerArray.GetSize();
	for ( int i=0; i<iTickers; i++ ) {
		CStkTicker *p = (CStkTicker *)m_TickerArray[i];
		if ( p ) {
			int iPos = m_LB.AddString(p->m_strSymbol);
			m_LB.SetItemData(iPos, (DWORD)p);
		}
	}
	if ( iTickers ) {
		m_LB.SetCurSel(0);
		OnSelchangePortfolio();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTradeDlg::OnSelchangePortfolio() 
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
		CStkTicker *p = (CStkTicker *)m_LB.GetItemData(iCurSel);
		if ( DWORD(p) != LB_ERR ) {
			m_strLast					= p->m_strLast;
			m_strChange				= p->m_strChange;
			m_strVolume				= p->m_strVolume ;
			m_strDayhi				= p->m_strHigh ;
			m_strDaylow				= p->m_strLow ;
		    m_strPrice				= m_strLast;
			m_strShares.Format((LPCTSTR)"%d",p->m_dwSharesBought);
			UpdateData(FALSE);

			CString strTitle((LPCTSTR)"Trade  ");
			strTitle += p->m_strSymbol;
			if (p->m_dwSharesBought>=0 ) {
				CString str;
				str.Format((LPCTSTR)" - Shares on Hand: %d", p->m_dwSharesBought);
				strTitle += str;
			}
			SetWindowText(strTitle);
		}
	}
  if ( m_bBuy != -1 ) {
     CalcAmount();
  }


}

void CTradeDlg::OnBuy() 
{
  UpdateData(TRUE);

	m_rDate.EnableWindow();
	m_rPrice.EnableWindow();
	m_rShares.EnableWindow();
	m_rCommisions.EnableWindow();
  m_rApply.EnableWindow();

  CTime t = CTime::GetCurrentTime();
  m_strDate = t.Format((LPCTSTR)"%m/%d/%y");

  m_strPrice = m_strLast;

  UpdateData(FALSE);
  CalcAmount();

}

void CTradeDlg::OnSell() 
{
	OnBuy();
}

int MakeInt( CString& rStr )
{
	CString s;
	int iLen = rStr.GetLength();
	for ( int i=0; i<iLen; i++) {
		if ( isdigit(rStr[i]) ) {
			s += rStr[i];
		}
	}
	return _wtoi(s);
}

CString GetMiddle( CString& rStr )
{
	static CString s;
	s.Empty();

	int iLen = rStr.GetLength();
	int iPos = rStr.Find('/');
	if ( iPos == -1 ) {
		return rStr.Mid(3,2);
	}

	for ( int i=iPos+1; i<iLen && rStr[i] != '/'; i++) {
		if ( isdigit(rStr[i]) ) {
			s += rStr[i];
		}
	}

	return s;
}

int SortTradesByDate( const void *arg1, const void *arg2 )
{
 	CTradeInf *pObj1 = *(CTradeInf **) arg1;
	CTradeInf *pObj2 = *(CTradeInf **) arg2;

	CString strDate1 = (CString)pObj1->m_strDate;
	CString strDate2 = (CString)pObj2->m_strDate;

	int y1,m1,d1;
	int y2,m2, d2;

	y1 = MakeInt(strDate1.Right(2));
	m1 = MakeInt(strDate1.Left(2));
	d1 = MakeInt(GetMiddle(strDate1));

	y2 = MakeInt(strDate2.Right(2));
	m2 = MakeInt(strDate2.Left(2));
	d2 = MakeInt(GetMiddle(strDate2));

	if ( y1 > y2 )
		return 1;
	else if ( y1 < y2 )
		return -1;
	else if ( y1 == y2 ) {
		if ( m1 > m2 ) {
			return 1;
		}

		if ( m1 < m2 ) {
			return -1;
		}

		if ( m1 == m2 ) {
			if ( d1 > d2 ) {
				return 1;
			}

			if ( d1 < d2 ) {
				return -1;
			}

			if ( d1 == d2 ) {
				if (pObj1->m_bBuy) return 1;
				return 0;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}

void SortTrades(CPtrArray& rArray)
{
	CTradeInf **ppTradeInf;
	int iCount = rArray.GetSize();
	int i;
	ppTradeInf = new (CTradeInf * [iCount]);
	if (!ppTradeInf)
		return;

	for ( i=0; i < iCount; i++) {
		ppTradeInf[i] = 
				(CTradeInf *) rArray.GetAt(i);
	}
	rArray.RemoveAll();
			// sort by date/seq/time
	if (i > 1)
		qsort((void *)ppTradeInf, i, sizeof(CTradeInf *), SortTradesByDate ); 

	for ( int j=0; j<i; j++) {
		rArray.InsertAt(j, ppTradeInf[j]);
	}

	delete [] ppTradeInf;
}

CStkTicker *CTradeDlg::GetSelectedTickerDataFromLB()
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
		CStkTicker *p = (CStkTicker *)m_LB.GetItemData(iCurSel);
		if ( DWORD(p) != LB_ERR ) {
			return p;
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

void CTradeDlg::OnApply() 
{
	CalcAmount();

	CStkTicker *p = GetSelectedTickerDataFromLB();

	if ( p) {

		UpdateData(TRUE);
		if ( m_bBuy == 1 && _wtof(m_strShares) > p->m_dwSharesBought ) {
			AfxMessageBox((LPCTSTR)"You cannot sell more than you have");
			return;
		}

		CTradeInf *pTrade = new CTradeInf;
		if ( !pTrade )
		return;

		pTrade->m_strDate     = m_strDate;
		pTrade->m_strPrice    = m_strPrice;
		pTrade->m_strShares   = m_strShares;
		pTrade->m_strCommision= m_strCommision;
		pTrade->m_strAmount   = m_strAmount;
		pTrade->m_bBuy        = m_bBuy;

		p->m_Trades.Add(pTrade);

		if ( m_bBuy == 1 ) {
			p->m_dwSharesBought	-= _wtof(m_strShares);
			OnSelchangePortfolio();
		}
		m_pDoc->SetModifiedFlag(TRUE);
	}
}


void CTradeDlg::CalcAmount()
{
  UpdateData(TRUE);
  if ( m_strPrice.IsEmpty() || m_strShares.IsEmpty())
    return;

  CString strPriceInDec = m_pDoc->ConvertToDecimal(m_strPrice,7);
  double price = _wtof(strPriceInDec);
  long shares = _wtof(m_strShares);
  
  if ( !m_strCommision.IsEmpty() ) {
    double com = _wtof(m_strCommision);
		if ( 0 == m_bBuy ) {
			m_strAmount.Format((LPCTSTR)"$%f", (price*shares)+com);
		}
		else {
			m_strAmount.Format((LPCTSTR)"$%f", (price*shares)-com);
		}
  }
  else {
    m_strAmount.Format((LPCTSTR)"$%f", price*shares);
  }

  int iPos = m_strAmount.Find('.');
  if ( iPos != -1 ) {
    m_strAmount = m_strAmount.Left(iPos+3);
  }

  UpdateData(FALSE);

}

void CTradeDlg::OnChangePrice() 
{
  OnChangeShares();	
}

void CTradeDlg::OnChangeShares() 
{
  CalcAmount();
}

void CTradeDlg::OnChangeCommision() 
{
  OnChangeShares();		
}

void CTradeDlg::OnDblclkPortfolio() 
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
			CTrdDet d(m_TickerArray, m_pDoc, iCurSel);
			d.DoModal();
	}
}
/////////////////////////////////////////////////////////////////////////////
// CTrdDet dialog
/////////////////////////////////////////////////////////////////////////////
// data for the list view control

#define NUM_COLUMNS	7

static WCHAR *_gszColumnLabel[NUM_COLUMNS]=
{
	_T("Date"), _T("Buy"), _T("Sell"), _T("Shares"), _T("Amount"), _T("Cum. Gain"), _T("Comm")
};

static int _gnColumnFmt[NUM_COLUMNS]=
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT
};

static int _gnColumnWidth[NUM_COLUMNS]=
{
	75, 75, 75, 75, 75,80, 75
};


CTrdDet::CTrdDet(CWnd* pParent /*=NULL*/)
	: CDialog(CTrdDet::IDD, pParent)
{
}

CTrdDet::CTrdDet(CPtrArray& rPortfolio,CSMDoc *pDoc, int iIndex, CWnd* pParent /*=NULL*/)
	: CDialog(CTrdDet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrdDet)
	//}}AFX_DATA_INIT
	m_TickerArray.Append(rPortfolio);
	m_pDoc = pDoc;
	m_iIndex = iIndex;
}

CTrdDet::CTrdDet(CPtrArray& rPortfolio, CSMDoc *pDoc, LPCTSTR lpSymbol, CWnd* pParent)
	: CDialog(CTrdDet::IDD, pParent)
{
	m_TickerArray.Append(rPortfolio);
	m_pDoc = pDoc;
	m_iIndex = -1;
	if (lpSymbol)
		m_strSymbol = lpSymbol;
}

void CTrdDet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrdDet)
	DDX_Control(pDX, IDC_TRADE_DTLS, m_ListCtrl);
	DDX_Control(pDX, IDC_PORTFOLIO, m_LB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrdDet, CDialog)
	//{{AFX_MSG_MAP(CTrdDet)
	ON_LBN_SELCHANGE(IDC_PORTFOLIO, OnSelchangePortfolio)
	ON_NOTIFY(LVN_KEYDOWN, IDC_TRADE_DTLS, OnKeydownTradeDtls)
	ON_LBN_DBLCLK(IDC_PORTFOLIO, OnDblclkPortfolio)
	ON_BN_CLICKED(IDB_TRADE, OnTrade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrdDet message handlers

BOOL CTrdDet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int iTickers = m_TickerArray.GetSize();
	for ( int i=0; i<iTickers; i++ ) {
		CStkTicker *p = (CStkTicker *)m_TickerArray[i];
		if ( p ) {
			int iPos = m_LB.AddString(p->m_strSymbol);
			m_LB.SetItemData(iPos, (DWORD)p);
		}
	}

	LV_COLUMN lvc;

	lvc.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(int i=0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem=i;
		lvc.pszText=_gszColumnLabel[i];
		lvc.cx=_gnColumnWidth[i];
		lvc.fmt=_gnColumnFmt[i];
		m_ListCtrl.DeleteColumn(i);
		m_ListCtrl.InsertColumn(i,&lvc);
	}

	if ( iTickers ) {
		if ( m_iIndex != -1 ) {
			m_LB.SetCurSel(m_iIndex);
		}
		if ( !m_strSymbol.IsEmpty() ) {
			m_LB.SelectString(-1, m_strSymbol);
		}
		else {
			m_LB.SetCurSel(0);
		}
		OnSelchangePortfolio();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CStkTicker *CTrdDet::GetSelectedTickerDataFromLB()
{
	int iCurSel  = m_LB.GetCurSel();	
	CString strTicker;
	if ( LB_ERR != iCurSel ) {
		CStkTicker *p = (CStkTicker *)m_LB.GetItemData(iCurSel);
		if ( DWORD(p) != LB_ERR ) {
			return p;
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

void CTrdDet::OnSelchangePortfolio() 
{
	CStkTicker *p = GetSelectedTickerDataFromLB();
	if (p) {
		SortTrades(p->m_Trades);
		CalcGain(p);
		ShowData(p);
		CString strTitle((LPCTSTR)"Trade Details for ");
		strTitle += p->m_strSymbol;
		if (p->m_dwSharesBought>=0 ) {
			CString str;
			str.Format((LPCTSTR)" - Shares on Hand: %d", p->m_dwSharesBought);
			strTitle += str;
		}
		SetWindowText(strTitle);
	}
}

void CTrdDet::CalcGain(CStkTicker *p)
{
	if ( !p ) {
		return;
	}
	
	int nCount = p->m_Trades.GetSize();
	p->m_dwSharesBought = 0;

	CTradeInf *pTrade=NULL;
	double dwAmountPaid=0;
	DWORD dwSharesBought=0;

	for ( int i=0; i<nCount; i++) {
		pTrade = (CTradeInf *)p->m_Trades[i];
		if (!pTrade)
			break;

		if ( pTrade->m_bBuy == 0 ) {
			CString str = m_pDoc->ConvertToDecimal(pTrade->m_strAmount.Mid(1));
			dwAmountPaid += _wtof(str);

			dwSharesBought += _wtof(pTrade->m_strShares);
		}
		else 		if ( pTrade->m_bBuy == 1 ) {
			if ( dwSharesBought &&  pTrade->m_strShares ) {

				double Gain=0.0;
				double avgpurchaseprice = dwAmountPaid / dwSharesBought;

				CString str = m_pDoc->ConvertToDecimal(pTrade->m_strPrice);	
				Gain = (_wtof(str) - avgpurchaseprice) * _wtof(pTrade->m_strShares);
				str = m_pDoc->ConvertToDecimal(pTrade->m_strCommision);
				Gain -= _wtof(str);
				pTrade->m_strGain.Format((LPCTSTR)"%f",Gain);

				dwSharesBought -= _wtof(pTrade->m_strShares);
				dwAmountPaid   -= _wtof(m_pDoc->ConvertToDecimal(pTrade->m_strAmount.Mid(1)));
			}
			else {
				pTrade->m_strGain.Empty();
			}

		}
		p->m_dwSharesBought = dwSharesBought;
	}
}

void CTrdDet::ShowData(CStkTicker *p)
{
	if ( !p )
		return;

	m_ListCtrl.DeleteAllItems();
	LV_ITEM lvi;


	// insert items
	int nCount = p->m_Trades.GetSize();

	for(int i=0; i<nCount; i++)
	{
		CTradeInf *pTrade = (CTradeInf *)p->m_Trades[i];
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.pszText = (LPTSTR)(LPCTSTR)pTrade->m_strDate;
		lvi.iItem=i;
		lvi.iSubItem=0;
		lvi.lParam = (LPARAM)pTrade;
		m_ListCtrl.InsertItem(&lvi);

		if ( pTrade->m_bBuy==0 ) {
			m_ListCtrl.SetItemText(i,1, pTrade->m_strPrice);
		}
		else if ( pTrade->m_bBuy==1 ){
			m_ListCtrl.SetItemText(i,2, pTrade->m_strPrice);

			if (!pTrade->m_strGain.IsEmpty()) {
				CString str;
				str = "$";
				str += pTrade->m_strGain;

				int iPos = str.Find('.');
				if ( iPos != -1 ) {
					str = str.Left(iPos+3);
				}
				m_ListCtrl.SetItemText(i,5, str);
			}
			else {
				m_ListCtrl.SetItemText(i,5, pTrade->m_strGain);
			}
		}

		m_ListCtrl.SetItemText(i,3, pTrade->m_strShares);
		m_ListCtrl.SetItemText(i,4, pTrade->m_strAmount);
		m_ListCtrl.SetItemText(i,6, pTrade->m_strCommision);

	}
}

void CTrdDet::OnKeydownTradeDtls(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	if ( !pLVKeyDow )
		return;

	if(m_ListCtrl.GetSelectedCount())
	{
		if ( pLVKeyDow->wVKey == 46  ) {
			// Delete Key pressed
			DeleteSelectedItem();
			OnSelchangePortfolio();
		}
	}

	if ( pLVKeyDow->wVKey == 45  ) {
		// Insert Key pressed
		Transact();
		OnSelchangePortfolio();
	}
	
	*pResult = 0;
}

void CTrdDet::DeleteSelectedItem()
{
		// get item data
	WCHAR szBuff[MAX_PATH];
	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.lParam=NULL;
	lvi.stateMask=0xFFFF;		// get all state flags
	int nItem;

	for(nItem=m_ListCtrl.GetNextItem(-1,LVNI_SELECTED);
			nItem!=-1;
			nItem=m_ListCtrl.GetNextItem(-1,LVNI_SELECTED))
	{
		lvi.iItem=nItem;
		m_ListCtrl.GetItem(&lvi);
		CTradeInf *pTrade = (CTradeInf *)lvi.lParam;
		RemoveTrade(pTrade);

		m_ListCtrl.DeleteItem(nItem);
	}

	Invalidate();

}

void CTrdDet::RemoveTrade(CTradeInf *pTrade)
{
	if ( !pTrade )
		return;

	CStkTicker *p = GetSelectedTickerDataFromLB();
	if ( !p )
		return;

	// insert items
	int nCount = p->m_Trades.GetSize();

	for(int i=0; i<nCount; i++)
	{
		if ( pTrade == p->m_Trades[i] ) {
			p->m_Trades.RemoveAt(i);
			m_pDoc->SetModifiedFlag(TRUE);
			break;
		}
	}
}

void CTrdDet::Transact()
{
	CStkTicker *p = GetSelectedTickerDataFromLB();
	if (p) {
		CPtrArray a;
		try {
			a.SetSize(1);
			a.Add(p);
		}
		catch (...) {
			return;
		}

		CTradeDlg d(a, m_pDoc);
		if (IDOK == d.DoModal() ) {
			OnSelchangePortfolio();
		}
	}
}

void CTrdDet::OnDblclkPortfolio() 
{
	Transact();
}


void CTrdDet::OnTrade() 
{
	Transact();
}
/////////////////////////////////////////////////////////////////////////////
// CStkScreenDlg dialog


CStkScreenDlg::CStkScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStkScreenDlg::IDD, pParent)
{
	m_strPrice_Min = _T("");
	m_strPrice_Max = _T("");
	m_strPBRatio_Min = _T("");
	m_strPBRatio_Max = _T("");
	m_strPSRatio_Min = _T("");
	m_strPSRatio_Max = _T("");
	m_strPE_Min = _T("");
	m_strPE_Max = _T("");
	m_strBeta_Min = _T("");
	m_strBeta_Max = _T("");
	m_strYield_Min = _T("");
	m_strYield_Max = _T("");
	m_strEPSChg_Min = _T("");
	m_strEPSChg_Max = _T("");
	m_strGr_Min = _T("");
	m_strGr_Max = _T("");
	m_strDPRatio_Min = _T("");
	m_strDPRatio_Max = _T("");
	m_strROE_Min = _T("");
	m_strROE_Max = _T("");
	m_strDERatio_Min = _T("");
	m_strDERatio_Max = _T("");
	m_strSales_Min = _T("");
	m_strSales_Max = _T("");
	m_strMktCap_Min = _T("");
	m_strMktCap_Max = _T("");

	m_strDowJones = "All Companies                  ()";
	m_strSP500    = "All Companies                  ()";
  m_strIndustryGrp = "All Industries              ()";;
	m_strExchg       = "All Exchanges               ()";;

}

CStkScreenDlg::CStkScreenDlg(CSMDoc *pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CStkScreenDlg::IDD, pParent)
{
  ASSERT(pDoc != NULL );
  m_pDoc = pDoc;

	//{{AFX_DATA_INIT(CStkScreenDlg)
	m_strPrice_Min = _T("");
	m_strPrice_Max = _T("");
	m_strPBRatio_Min = _T("");
	m_strPBRatio_Max = _T("");
	m_strPSRatio_Min = _T("");
	m_strPSRatio_Max = _T("");
	m_strPE_Min = _T("");
	m_strPE_Max = _T("");
	m_strBeta_Min = _T("");
	m_strBeta_Max = _T("");
	m_strYield_Min = _T("");
	m_strYield_Max = _T("");
	m_strEPSChg_Min = _T("");
	m_strEPSChg_Max = _T("");
	m_strGr_Min = _T("");
	m_strGr_Max = _T("");
	m_strDPRatio_Min = _T("");
	m_strDPRatio_Max = _T("");
	m_strROE_Min = _T("");
	m_strROE_Max = _T("");
	m_strDERatio_Min = _T("");
	m_strDERatio_Max = _T("");
	m_strSales_Min = _T("");
	m_strSales_Max = _T("");
	m_strMktCap_Min = _T("");
	m_strMktCap_Max = _T("");
	m_strDowJones = _T("");
	m_strSP500 = _T("");
	m_strIndustryGrp = _T("");
	m_strExchg = _T("");
	m_strDowJones = _T("All Companies                  ()");
	m_strSP500    = _T("All Companies                  ()");
  m_strIndustryGrp = _T("All Industries              ()");;
	m_strExchg       = _T("All Exchanges               ()");;

	//}}AFX_DATA_INIT

  m_strPrice_Min    = m_pDoc->m_strPrice_Min;
  m_strPrice_Max    = m_pDoc->m_strPrice_Max;
  m_strPBRatio_Min  = m_pDoc->m_strPBRatio_Min;
  m_strPBRatio_Max  = m_pDoc->m_strPBRatio_Max;
  m_strPSRatio_Min  = m_pDoc->m_strPSRatio_Min;
  m_strPSRatio_Max  = m_pDoc->m_strPSRatio_Max;
  m_strPE_Min       = m_pDoc->m_strPE_Min;
  m_strPE_Max       = m_pDoc->m_strPE_Max;
  m_strBeta_Min     = m_pDoc->m_strBeta_Min;
  m_strBeta_Max     = m_pDoc->m_strBeta_Max;
  m_strYield_Min    = m_pDoc->m_strYield_Min;
  m_strYield_Max    = m_pDoc->m_strYield_Max;
  m_strEPSChg_Min   = m_pDoc->m_strEPSChg_Min;
  m_strEPSChg_Max   = m_pDoc->m_strEPSChg_Max;
  m_strGr_Min       = m_pDoc->m_strGr_Min;
  m_strGr_Max       = m_pDoc->m_strGr_Max;
  m_strDPRatio_Min  = m_pDoc->m_strDPRatio_Min;
  m_strDPRatio_Max  = m_pDoc->m_strDPRatio_Max;
  m_strROE_Min      = m_pDoc->m_strROE_Min;
  m_strROE_Max      = m_pDoc->m_strROE_Max;
  m_strDERatio_Min  = m_pDoc->m_strDERatio_Min;
  m_strDERatio_Max  = m_pDoc->m_strDERatio_Max;
  m_strSales_Min    = m_pDoc->m_strSales_Min;
  m_strSales_Max    = m_pDoc->m_strSales_Max;
  m_strMktCap_Min   = m_pDoc->m_strMktCap_Min;
  m_strMktCap_Max   = m_pDoc->m_strMktCap_Max;
	m_strDowJones     = m_pDoc->m_strDowJones;
	m_strSP500        = m_pDoc->m_strSP500;        
  m_strIndustryGrp  = m_pDoc->m_strIndustryGrp;  
	m_strExchg        = m_pDoc->m_strExchg;        
}

void CStkScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStkScreenDlg)
	DDX_Control(pDX, IDC_INDUSTRY_GRP, m_rIGroup);
	DDX_Text(pDX, IDC_SCR_PRICE_MIN, m_strPrice_Min);
	DDX_Text(pDX, IDC_SCR_PRICE_MAX, m_strPrice_Max);
	DDX_Text(pDX, IDC_SCR_PB_RATIO_MIN, m_strPBRatio_Min);
	DDX_Text(pDX, IDC_SCR_PB_RATIO_MAX, m_strPBRatio_Max);
	DDX_Text(pDX, IDC_SCR_PS_RATIO_MIN, m_strPSRatio_Min);
	DDX_Text(pDX, IDC_SCR_PS_RATIO_MAX, m_strPSRatio_Max);
	DDX_Text(pDX, IDC_SCR_PE_MIN, m_strPE_Min);
	DDX_Text(pDX, IDC_SCR_PE_MAX, m_strPE_Max);
	DDX_Text(pDX, IDC_SCR_BETA_MIN, m_strBeta_Min);
	DDX_Text(pDX, IDC_SCR_BETA_MAX, m_strBeta_Max);
	DDX_Text(pDX, IDC_SCR_YIELD_MIN, m_strYield_Min);
	DDX_Text(pDX, IDC_SCR_YIELD_MAX, m_strYield_Max);
	DDX_Text(pDX, IDC_SCR_EPS_CHG_MIN, m_strEPSChg_Min);
	DDX_Text(pDX, IDC_SCR_EPS_CHG_MAX, m_strEPSChg_Max);
	DDX_Text(pDX, IDC_SCR_GR_MIN, m_strGr_Min);
	DDX_Text(pDX, IDC_SCR_GR_MAX, m_strGr_Max);
	DDX_Text(pDX, IDC_SCR_DP_MIN, m_strDPRatio_Min);
	DDX_Text(pDX, IDC_SCR_DP_MAX, m_strDPRatio_Max);
	DDX_Text(pDX, IDC_SCR_ROE_MIN, m_strROE_Min);
	DDX_Text(pDX, IDC_SCR_ROE_MAX, m_strROE_Max);
	DDX_Text(pDX, IDC_SCR_DE_MIN, m_strDERatio_Min);
	DDX_Text(pDX, IDC_SCR_DE_MAX, m_strDERatio_Max);
	DDX_Text(pDX, IDC_SCR_SALES_MIN, m_strSales_Min);
	DDX_Text(pDX, IDC_SCR_SALES_MAX, m_strSales_Max);
	DDX_Text(pDX, IDC_SCR_MKTCAP_MIN, m_strMktCap_Min);
	DDX_Text(pDX, IDC_SCR_MKTCAP_MAX, m_strMktCap_Max);
	DDX_CBString(pDX, IDC_DJ, m_strDowJones);
	DDX_CBString(pDX, IDC_SP500, m_strSP500);
	DDX_CBString(pDX, IDC_INDUSTRY_GRP, m_strIndustryGrp);
	DDX_CBString(pDX, IDC_EXCHANGES, m_strExchg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStkScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CStkScreenDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStkScreenDlg message handlers

BOOL CStkScreenDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*
  m_rIGroup.AddString((LPCTSTR)"All Industries                                                                ()");
  m_rIGroup.AddString((LPCTSTR)"Aerospace: Aircraft Mfrs, Services                                            (13)");
  m_rIGroup.AddString((LPCTSTR)"Aerospace: Components                                                         (12)");
  m_rIGroup.AddString((LPCTSTR)"Aerospace: Industries                                                         (11)");
  m_rIGroup.AddString((LPCTSTR)"Airlines: Regional Airlines                                                   (22)");
  m_rIGroup.AddString((LPCTSTR)"Airlines: Trunk Airlines                                                      (21)");
  m_rIGroup.AddString((LPCTSTR)"Auto: Manufacturers                                                           (31)");
  m_rIGroup.AddString((LPCTSTR)"Auto: Parts, Accessories                                                      (32)");
  m_rIGroup.AddString((LPCTSTR)"Banking: East North Central Banks                                             (44)");
  m_rIGroup.AddString((LPCTSTR)"Banking: East South Central Banks                                             (45)");
  m_rIGroup.AddString((LPCTSTR)"Banking: Middle Atlantic Banks                                                (42)");
  m_rIGroup.AddString((LPCTSTR)"Banking: Mountain Stat Banks                                                  (48)");
  m_rIGroup.AddString((LPCTSTR)"Banking: New England Banks                                                    (41)");
  m_rIGroup.AddString((LPCTSTR)"Banking: Pacific State Banks                                                  (49)");
  m_rIGroup.AddString((LPCTSTR)"Banking: South Atlantic Banks                                                 (43)");
  m_rIGroup.AddString((LPCTSTR)"Banking: West North Central Banks                                             (46)");
  m_rIGroup.AddString((LPCTSTR)"Banking: West South Central Banks                                             (47)");
  m_rIGroup.AddString((LPCTSTR)"Building: Cement                                                              (54)");
  m_rIGroup.AddString((LPCTSTR)"Building: Clay Products                                                       (55)");
  m_rIGroup.AddString((LPCTSTR)"Building: Contractors - General                                               (61)");
  m_rIGroup.AddString((LPCTSTR)"Building: Contractors - Special                                               (62)");
  m_rIGroup.AddString((LPCTSTR)"Building: Glass                                                               (56)");
  m_rIGroup.AddString((LPCTSTR)"Building: Lumber, Wood Products                                               (53)");
  m_rIGroup.AddString((LPCTSTR)"Building: Manufactured Housing                                                (52)");
  m_rIGroup.AddString((LPCTSTR)"Building: Materials & Component Mfrs                                          (64)");
  m_rIGroup.AddString((LPCTSTR)"Building: Other Building Materials                                            (58)");
  m_rIGroup.AddString((LPCTSTR)"Building: Paints                                                              (57)");
  m_rIGroup.AddString((LPCTSTR)"Building: Plumbing, Heating, Air Conditioning                                 (59)");
  m_rIGroup.AddString((LPCTSTR)"Building: Residential Construction                                            (51)");
  m_rIGroup.AddString((LPCTSTR)"Business Equipment: Copying Machines                                          (82)");
  m_rIGroup.AddString((LPCTSTR)"Business Equipment: Office Machines                                           (81)");
  m_rIGroup.AddString((LPCTSTR)"Business Equipment: Office Supplies                                           (84)");
  m_rIGroup.AddString((LPCTSTR)"Business Equipment: Other Business Equipment                                  (83)");
  m_rIGroup.AddString((LPCTSTR)"Business Services: Advertising Agencies                                       (91)");
  m_rIGroup.AddString((LPCTSTR)"Business Services: Insurance Brokers                                          (92)");
  m_rIGroup.AddString((LPCTSTR)"Business Services: Other Business Services                                    (94)");
  m_rIGroup.AddString((LPCTSTR)"Business Services: Printing                                                   (93)");
  m_rIGroup.AddString((LPCTSTR)"Business Services: Waste Management                                           (95)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals: Specialty Chemicals                                                (103)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals: Sulpher and Nitrates                                               (102)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals: Synthetics                                                         (101)");
  m_rIGroup.AddString((LPCTSTR)"Communications                                                                (111)");
  m_rIGroup.AddString((LPCTSTR)"Cosmetics, Grooming                                                           (121)");
  m_rIGroup.AddString((LPCTSTR)"Credit: Business Credit                                                       (132)");
  m_rIGroup.AddString((LPCTSTR)"Credit: Personal Credit                                                       (131)");
  m_rIGroup.AddString((LPCTSTR)"Data Processing: Computer Leasing                                             (73)");
  m_rIGroup.AddString((LPCTSTR)"Data Processing: Computers, Subsys, Peripherals                               (71)");
  m_rIGroup.AddString((LPCTSTR)"Data Processing: Software                                                     (72)");
  m_rIGroup.AddString((LPCTSTR)"Distillers                                                                    (141)");
  m_rIGroup.AddString((LPCTSTR)"Distillers: Brewers, Wineries                                                 (142)");
  m_rIGroup.AddString((LPCTSTR)"Drug Manufactures                                                             (151)");
  m_rIGroup.AddString((LPCTSTR)"Electrical Equipment                                                          (161)");
  m_rIGroup.AddString((LPCTSTR)"Electronic: Equipment                                                         (171)");
  m_rIGroup.AddString((LPCTSTR)"Electronic: Radio-TV                                                          (172)");
  m_rIGroup.AddString((LPCTSTR)"Food - Packed Goods Mill Products                                             (192)");
  m_rIGroup.AddString((LPCTSTR)"Food - Packed Goods Products                                                  (193)");
  m_rIGroup.AddString((LPCTSTR)"Food - Packed Goods: Soaps and Cleansers                                      (191)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Canned, Cured, Frozen Food                                   (182)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Confectioners                                                (212)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Dairy Products                                               (203)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Farm Products                                                (181)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Livestock                                                    (201)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Meat and Poultry                                             (202)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Soft Drinks                                                  (213)");
  m_rIGroup.AddString((LPCTSTR)"Food Production: Sugar                                                        (211)");
  m_rIGroup.AddString((LPCTSTR)"Freight: Air Freight                                                          (223)");
  m_rIGroup.AddString((LPCTSTR)"Freight: Freight Forwarding                                                   (225)");
  m_rIGroup.AddString((LPCTSTR)"Freight: Truck, Rail Leasing                                                  (227)");
  m_rIGroup.AddString((LPCTSTR)"Freight: Trucking                                                             (221)");
  m_rIGroup.AddString((LPCTSTR)"Freight: Water Transport                                                      (222)");
  m_rIGroup.AddString((LPCTSTR)"Health: Institutional Services                                                (232)");
  m_rIGroup.AddString((LPCTSTR)"Health: Medical Instruments, Supplies                                         (231)");
  m_rIGroup.AddString((LPCTSTR)"Hotels, Motels, Resorts                                                       (241)");
  m_rIGroup.AddString((LPCTSTR)"Houseware: Appliances                                                         (251)");
  m_rIGroup.AddString((LPCTSTR)"Houseware: Furniture, Furnishings                                             (253)");
  m_rIGroup.AddString((LPCTSTR)"Houseware: Home Fixtures                                                      (252)");
  m_rIGroup.AddString((LPCTSTR)"Houseware: Rugs and Carpets                                                   (255)");
  m_rIGroup.AddString((LPCTSTR)"Housewares                                                                    (254)");
  m_rIGroup.AddString((LPCTSTR)"Instruments: Electronic Instruments                                           (403)");
  m_rIGroup.AddString((LPCTSTR)"Instruments: Mechanical Devices                                               (402)");
  m_rIGroup.AddString((LPCTSTR)"Instruments: Photographic Equipment, Supplies                                 (404)");
  m_rIGroup.AddString((LPCTSTR)"Instruments: Scientific Instruments                                           (401)");
  m_rIGroup.AddString((LPCTSTR)"Insurance: Life, Accident, Health                                             (261)");
  m_rIGroup.AddString((LPCTSTR)"Insurance: Lire, marine, Casualty, Title                                      (262)");
  m_rIGroup.AddString((LPCTSTR)"Investments: Closed-End Funds                                                 (272)");
  m_rIGroup.AddString((LPCTSTR)"Investments: Financial, Fund Management                                       (271)");
  m_rIGroup.AddString((LPCTSTR)"Investments: Investment Bankers, Brokers                                      (273)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Engines and Turbines                                               (285)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Farm, Construction, Mining                                         (281)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: General Industrial Machines                                        (283)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Light Machine Equipment                                            (295)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Machine Accessories                                                (294)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Machine Tools, Accessories                                         (291)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Pollution Controls                                                 (286)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Railroad Equipment                                                 (284)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Screw Machine Products                                             (293)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Small Tools                                                        (292)");
  m_rIGroup.AddString((LPCTSTR)"Machinery: Special Industrial Machines                                        (282)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Aluminum Refining                                                     (324)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Copper Mining                                                         (321)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Copper Refining                                                       (322)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Iron Mining                                                           (311)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Iron, Steel Mills                                                     (312)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Lead, Nickel, Zinc, Mining and Refining                               (325)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Metals Fabrication                                                    (301)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Mining, Rare Metals                                                   (331)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Other Metal Refining                                                  (329)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Other Mining, Coal                                                    (328)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Refining, Rare Metals                                                 (332)");
  m_rIGroup.AddString((LPCTSTR)"Metals: Uranium Mining                                                        (327)");
  m_rIGroup.AddString((LPCTSTR)"Multi-Industry                                                                (341)");
  m_rIGroup.AddString((LPCTSTR)"Oil Refining: Marketing                                                       (371)");
  m_rIGroup.AddString((LPCTSTR)"Oil, Natural Gas: Exploration                                                 (353)");
  m_rIGroup.AddString((LPCTSTR)"Oil, Natural Gas: Production                                                  (361)");
  m_rIGroup.AddString((LPCTSTR)"Oil: Offshore Drilling                                                        (352)");
  m_rIGroup.AddString((LPCTSTR)"Oil: Oil Field Services                                                       (351)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Glass Containers                                            (384)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Metal Cans                                                  (382)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Paper Containers, Boxes                                     (383)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Paper Products                                              (381)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Plastic Packaging                                           (386)");
  m_rIGroup.AddString((LPCTSTR)"Pager, Packaging: Special Containers                                          (385)");
  m_rIGroup.AddString((LPCTSTR)"Personal Services                                                             (391)");
  m_rIGroup.AddString((LPCTSTR)"Personal Services: Automotice                                                 (393)");
  m_rIGroup.AddString((LPCTSTR)"Personal Services: Educational                                                (392)");
  m_rIGroup.AddString((LPCTSTR)"Personal Services: Photographic                                               (395)");
  m_rIGroup.AddString((LPCTSTR)"Personal Services: Vending Machine Supply                                     (396)");
  m_rIGroup.AddString((LPCTSTR)"Publishing: Books                                                             (413)");
  m_rIGroup.AddString((LPCTSTR)"Publishing: Newspapers                                                        (411)");
  m_rIGroup.AddString((LPCTSTR)"Publishing: Periodicals                                                       (412)");
  m_rIGroup.AddString((LPCTSTR)"Railroads                                                                     (421)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate: Investment Trust                                                 (432)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate: Mortgage Investment                                              (431)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate: Operating and Leasing                                            (441)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate: Subdivision Development                                          (442)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Broadcasting                                                      (461)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: CATV Systems                                                      (462)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Jewelry                                                           (456)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Movie Production, Theaters                                        (471)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Musical Instruments, Equipment                                    (454)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Other Entertainment                                               (474)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Sport Vehicles                                                    (453)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Sporting Events                                                   (473)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Sporting Goods                                                    (452)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Toys and Games                                                    (451)");
  m_rIGroup.AddString((LPCTSTR)"Recreation: Watches and Clocks                                                (457)");
  m_rIGroup.AddString((LPCTSTR)"Restaurants                                                                   (242)");
  m_rIGroup.AddString((LPCTSTR)"Restaurants Misc                                                              (243)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Aparel, Accessory Stores                                              (481)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Auto Parts                                                            (521)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Building Materials                                                    (522)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Department Stores                                                     (491)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Discount, Variety Stores                                              (502)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Drug Wholesales                                                       (523)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Drug, Proprietary Stores                                              (501)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Electrial Equipment                                                   (524)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Electronic Equipment                                                  (525)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Grocery Wholesalers                                                   (527)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Metal Distributors                                                    (528)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Other                                                                 (529)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Radio, TV Distributors                                                (526)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Retail Food Stores                                                    (511)");
  m_rIGroup.AddString((LPCTSTR)"Retail: Shoe Stores                                                           (482)");
  m_rIGroup.AddString((LPCTSTR)"Rubber, Plastic: Products                                                     (532)");
  m_rIGroup.AddString((LPCTSTR)"Rubber, Plastic: Tires, Inner Tubes                                           (531)");
  m_rIGroup.AddString((LPCTSTR)"Savings and Loan                                                              (541)");
  m_rIGroup.AddString((LPCTSTR)"Shoes, Leather: Footwear                                                      (552)");
  m_rIGroup.AddString((LPCTSTR)"Shoes, Leather: Leather Tanning & Products                                    (551)");
  m_rIGroup.AddString((LPCTSTR)"Textiles: Apparel                                                             (571)");
  m_rIGroup.AddString((LPCTSTR)"Textiles: Knitting Mills                                                      (562)");
  m_rIGroup.AddString((LPCTSTR)"Textiles: Misc Textile Goods                                                  (563)");
  m_rIGroup.AddString((LPCTSTR)"Textiles: Weaving Mills                                                       (561)");
  m_rIGroup.AddString((LPCTSTR)"Tobacco: Cigarettes                                                           (581)");
  m_rIGroup.AddString((LPCTSTR)"Tobacco: Other Tabacco Products                                               (582)");
  m_rIGroup.AddString((LPCTSTR)"Utilities: Electric Companies                                                 (591)");
  m_rIGroup.AddString((LPCTSTR)"Utilities: Electric Gas Companies                                             (592)");
  m_rIGroup.AddString((LPCTSTR)"Utilities: Gas Utilities                                                      (602)");
  m_rIGroup.AddString((LPCTSTR)"Utilities: Gas, Oil Pipelines                                                 (601)");
  m_rIGroup.AddString((LPCTSTR)"Utilities: Water Utilities                                                    (604)");
*/

m_rIGroup.AddString((LPCTSTR)"All Industries                                                                                                           ()");
/*
  m_rIGroup.AddString((LPCTSTR)"Chemicals - Major Diversified                                                                                            (110)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals - Synthetics                                                                                                   (111)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals - Agricultural Chemicals                                                                                       (112)");
  m_rIGroup.AddString((LPCTSTR)"Chemicals - Specialty Chemicals                                                                                          (113)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Major Integrated Oil & Gas                                                                                      (120)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Independent Oil & Gas                                                                                           (121)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Oil & Gas Refining & Marketing                                                                                  (122)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Oil & Gas Drilling & Exploration                                                                                (123)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Oil & Gas Equipment & Services                                                                                  (124)");
  m_rIGroup.AddString((LPCTSTR)"Energy - Oil & Gas Pipelines                                                                                             (125)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Steel & Iron                                                                                           (130)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Copper                                                                                                 (131)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Aluminum                                                                                               (132)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Industrial Metals & Minerals                                                                           (133)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Gold                                                                                                   (134)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Silver                                                                                                 (135)");
  m_rIGroup.AddString((LPCTSTR)"Metals & Mining - Nonmetallic Mineral Mining                                                                             (136)");
  m_rIGroup.AddString((LPCTSTR)"Conglomerates                                                                                                            (210)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Appliances                                                                                           (310)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Home Furnishings & Fixtures                                                                          (311)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Housewares & Accessories                                                                             (312)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Business Equipment                                                                                   (313)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Electronic Equipment                                                                                 (314)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Toys & Games                                                                                         (315)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Sporting Goods                                                                                       (316)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Recreational Goods, Other                                                                            (317)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Durables - Photographic Equipment & Supplies                                                                    (318)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Textile - Apparel Clothing                                                                       (320)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Textile - Apparel Footwear & Accessories                                                         (321)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Rubber & Plastics                                                                                (322)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Personal Products                                                                                (323)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Paper & Paper Products                                                                           (324)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Packaging & Containers                                                                           (325)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Cleaning Products                                                                                (326)");
  m_rIGroup.AddString((LPCTSTR)"Consumer Non-Durables - Office Supplies                                                                                  (327)");
  m_rIGroup.AddString((LPCTSTR)"Automotive - Auto Manufacturers - Major                                                                                  (330)");
  m_rIGroup.AddString((LPCTSTR)"Automotive - Trucks & Other Vehicles                                                                                     (331)");
  m_rIGroup.AddString((LPCTSTR)"Automotive - Recreational Vehicles                                                                                       (332)");
  m_rIGroup.AddString((LPCTSTR)"Automotive - Auto Parts                                                                                                  (333)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Food - Major Diversified                                                                               (340)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Farm Products                                                                                          (341)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Processed & Packaged Goods                                                                             (342)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Meat Products                                                                                          (343)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Dairy Products                                                                                         (344)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Confectioners                                                                                          (345)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Beverages - Brewers                                                                                    (346)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Beverages - Wineries & Distillers                                                                      (347)");
  m_rIGroup.AddString((LPCTSTR)"Food & Beverage - Beverages - Soft Drinks                                                                                (348)");
  m_rIGroup.AddString((LPCTSTR)"Tobacco - Cigarettes                                                                                                     (350)");
  m_rIGroup.AddString((LPCTSTR)"Tobacco - Tobacco Products, Other                                                                                        (351)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Money Center Banks                                                                                             (410)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Northeast Banks                                                                                     (411)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Mid-Atlantic Banks                                                                                  (412)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Southeast Banks                                                                                     (413)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Midwest Banks                                                                                       (414)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Southwest  Banks                                                                                    (415)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Regional - Pacific Banks                                                                                       (416)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Foreign Money Center Banks                                                                                     (417)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Foreign Regional Banks                                                                                         (418)");
  m_rIGroup.AddString((LPCTSTR)"Banking - Savings & Loans                                                                                                (419)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Investment Brokerage - National                                                                     (420)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Investment Brokerage - Regional                                                                     (421)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Asset Management                                                                                    (422)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Diversified Investments                                                                             (423)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Credit Services                                                                                     (424)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Closed-End Fund - Debt                                                                              (425)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Closed-End Fund - Equity                                                                            (426)");
  m_rIGroup.AddString((LPCTSTR)"Financial Services - Closed-End Fund - Foreign                                                                           (427)");
  m_rIGroup.AddString((LPCTSTR)"Insurance - Life Insurance                                                                                               (430)");
  m_rIGroup.AddString((LPCTSTR)"Insurance - Accident & Health Insurance                                                                                  (431)");
  m_rIGroup.AddString((LPCTSTR)"Insurance - Property & Casualty Insurance                                                                                (432)");
  m_rIGroup.AddString((LPCTSTR)"Insurance - Surety & Title Insurance                                                                                     (433)");
  m_rIGroup.AddString((LPCTSTR)"Insurance - Insurance Brokers                                                                                            (434)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Diversified                                                                                         (440)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Office                                                                                              (441)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Healthcare Facilities                                                                               (442)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Hotel/Motel                                                                                         (443)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Industrial                                                                                          (444)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Residential                                                                                         (445)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - REIT - Retail                                                                                              (446)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - Mortgage Investment                                                                                        (447)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - Property Management                                                                                        (448)");
  m_rIGroup.AddString((LPCTSTR)"Real Estate - Real Estate Development                                                                                    (449)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Drug Manufacturers - Major                                                                                       (510)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Drug Manufacturers - Other                                                                                       (511)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Drugs - Generic                                                                                                  (512)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Drug Delivery                                                                                                    (513)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Drug Related Products                                                                                            (514)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Biotechnology                                                                                                    (515)");
  m_rIGroup.AddString((LPCTSTR)"Drugs - Diagnostic Substances                                                                                            (516)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Medical Instruments & Supplies                                                                         (520)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Medical Appliances & Equipment                                                                         (521)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Health Care Plans                                                                                      (522)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Long-Term Care Facilities                                                                              (523)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Hospitals                                                                                              (524)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Medical Laboratories & Research                                                                        (525)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Home Health Care                                                                                       (526)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Medical Practitioners                                                                                  (527)");
  m_rIGroup.AddString((LPCTSTR)"Health Services - Specialized Health Services                                                                            (528)");
  m_rIGroup.AddString((LPCTSTR)"Aerospace/Defense - Major Diversified                                                                                    (610)");
  m_rIGroup.AddString((LPCTSTR)"Aerospace/Defense Products & Services                                                                                    (611)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Farm & Construction Machinery                                                                            (620)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Industrial Equipment & Components                                                                        (621)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Diversified Machinery                                                                                    (622)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Pollution & Treatment Controls                                                                           (623)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Machine Tools & Accessories                                                                              (624)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Small Tools & Accessories                                                                                (625)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Metal Fabrication                                                                                        (626)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Industrial Electrical Equipment                                                                          (627)");
  m_rIGroup.AddString((LPCTSTR)"Manufacturing - Textile Manufacturing                                                                                    (628)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Residential Construction                                                                      (630)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Manufactured Housing                                                                          (631)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Lumber, Wood Production                                                                       (632)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Cement                                                                                        (633)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - General Building Materials                                                                    (634)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Heavy Construction                                                                            (635)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - General Contractors                                                                           (636)");
  m_rIGroup.AddString((LPCTSTR)"Materials & Construction - Waste Management                                                                              (637)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Lodging                                                                                                        (710)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Resorts & Casinos                                                                                              (711)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Restaurants                                                                                                    (712)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Specialty Eateries                                                                                             (713)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Gaming Activities                                                                                              (714)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - Sporting Activities                                                                                            (715)");
  m_rIGroup.AddString((LPCTSTR)"Leisure - General Entertainment                                                                                          (716)");
  m_rIGroup.AddString((LPCTSTR)"Media - Advertising Agencies                                                                                             (720)");
  m_rIGroup.AddString((LPCTSTR)"Media - Marketing Services                                                                                               (721)");
  m_rIGroup.AddString((LPCTSTR)"Media - Entertainment - Diversified                                                                                      (722)");
  m_rIGroup.AddString((LPCTSTR)"Media - Broadcasting - TV                                                                                                (723)");
  m_rIGroup.AddString((LPCTSTR)"Media - Broadcasting - Radio                                                                                             (724)");
  m_rIGroup.AddString((LPCTSTR)"Media - CATV Systems                                                                                                     (725)");
  m_rIGroup.AddString((LPCTSTR)"Media - Movie Production, Theaters                                                                                       (726)");
  m_rIGroup.AddString((LPCTSTR)"Media - Publishing - Newspapers                                                                                          (727)");
  m_rIGroup.AddString((LPCTSTR)"Media - Publishing - Periodicals                                                                                         (728)");
  m_rIGroup.AddString((LPCTSTR)"Media - Publishing - Books                                                                                               (729)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Apparel Stores                                                                                                  (730)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Department Stores                                                                                               (731)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Discount, Variety Stores                                                                                        (732)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Drug Stores                                                                                                     (733)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Grocery Stores                                                                                                  (734)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Electronics Stores                                                                                              (735)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Home Improvement Stores                                                                                         (736)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Home Furnishing Stores                                                                                          (737)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Auto Parts Stores                                                                                               (738)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Catalog & Mail Order Houses                                                                                     (739)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Sporting Goods Stores                                                                                           (740)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Toy & Hobby Stores                                                                                              (741)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Jewelry Stores                                                                                                  (742)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Music & Video Stores                                                                                            (743)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Auto Dealerships                                                                                                (744)");
  m_rIGroup.AddString((LPCTSTR)"Retail - Specialty Retail, Other                                                                                         (745)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Auto Parts Wholesale                                                                                         (750)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Building Materials Wholesale                                                                                 (751)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Industrial Equipment Wholesale                                                                               (752)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Electronics Wholesale                                                                                        (753)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Medical Equipment Wholesale                                                                                  (754)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Computers Wholesale                                                                                          (755)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Drugs Wholesale                                                                                              (756)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Food Wholesale                                                                                               (757)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Basic Materials Wholesale                                                                                    (758)");
  m_rIGroup.AddString((LPCTSTR)"Wholesale - Wholesale, Other                                                                                             (759)");
  m_rIGroup.AddString((LPCTSTR)"Services - Business Services                                                                                             (760)");
  m_rIGroup.AddString((LPCTSTR)"Services - Rental & Leasing Services                                                                                     (761)");
  m_rIGroup.AddString((LPCTSTR)"Services - Personal Services                                                                                             (762)");
  m_rIGroup.AddString((LPCTSTR)"Services - Consumer Services                                                                                             (763)");
  m_rIGroup.AddString((LPCTSTR)"Services - Staffing & Outsourcing Services                                                                               (764)");
  m_rIGroup.AddString((LPCTSTR)"Services - Security & Protection Services                                                                                (765)");
  m_rIGroup.AddString((LPCTSTR)"Services - Education & Training Services                                                                                 (766)");
  m_rIGroup.AddString((LPCTSTR)"Services - Technical Services                                                                                            (767)");
  m_rIGroup.AddString((LPCTSTR)"Services - Research Services                                                                                             (768)");
  m_rIGroup.AddString((LPCTSTR)"Services - Management Services                                                                                           (769)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Major Airlines                                                                                          (770)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Regional Airlines                                                                                       (771)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Air Services, Other                                                                                     (772)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Air Delivery & Freight Services                                                                         (773)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Trucking                                                                                                (774)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Shipping                                                                                                (775)");
  m_rIGroup.AddString((LPCTSTR)"Transportation - Railroads                                                                                               (776)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Diversified Computer Systems                                                                         (810)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Personal Computers                                                                                   (811)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Computer Based Systems                                                                               (812)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Data Storage Devices                                                                                 (813)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Networking & Communication Devices                                                                   (814)");
  m_rIGroup.AddString((LPCTSTR)"Computer Hardware - Computer Peripherals                                                                                 (815)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Multimedia & Graphics Software                                                                       (820)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Application Software                                                                                 (821)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Technical & System Software                                                                          (822)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Security Software & Services                                                                         (823)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Information Technology Services                                                                      (824)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Healthcare Information Services                                                                      (825)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Business Software & Services                                                                         (826)");
  m_rIGroup.AddString((LPCTSTR)"Computer Software - Information & Delivery Services                                                                      (827)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Semiconductor - Broad Line                                                                                 (830)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Semiconductor - Memory Chips                                                                               (831)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Semiconductor - Specialized                                                                                (832)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Semiconductor - Integrated Circuits                                                                        (833)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Semiconductor Equipment & Materials                                                                        (834)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Printed Circuit Boards                                                                                     (835)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Diversified Electronics                                                                                    (836)");
  m_rIGroup.AddString((LPCTSTR)"Electronics - Scientific & Technical Instruments                                                                         (837)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Wireless Communications                                                                                        (840)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Communication Equipment                                                                                        (841)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Processing Systems & Products                                                                                  (842)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Long Distance Carriers                                                                                         (843)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Telecom Services - Domestic                                                                                    (844)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Telecom Services - Foreign                                                                                     (845)");
  m_rIGroup.AddString((LPCTSTR)"Telecom - Diversified Communication Services                                                                             (846)");
  m_rIGroup.AddString((LPCTSTR)"Internet - Internet Service Providers                                                                                    (850)");
  m_rIGroup.AddString((LPCTSTR)"Internet - Internet Information Providers                                                                                (851)");
  m_rIGroup.AddString((LPCTSTR)"Internet - Internet Software & Services                                                                                  (852)");
  m_rIGroup.AddString((LPCTSTR)"Utilities - Foreign Utilities                                                                                            (910)");
  m_rIGroup.AddString((LPCTSTR)"Utilities - Electric Utilities                                                                                           (911)");
  m_rIGroup.AddString((LPCTSTR)"Utilities - Gas Utilities                                                                                                (912)");
  m_rIGroup.AddString((LPCTSTR)"Utilities - Diversified Utilities                                                                                        (913)");
  m_rIGroup.AddString((LPCTSTR)"Utilities - Water Utilities                                                                                              (914)");
*/
  m_rIGroup.SelectString(-1,m_pDoc->m_strIndustryGrp);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CValDlg dialog


CValDlg::CValDlg(CStkTicker *pTicker, CWnd* pParent /*=NULL*/)
	: CDialog(CValDlg::IDD, pParent)
	, m_val_PE(_T(""))
{
	//{{AFX_DATA_INIT(CValDlg)
	m_fBuyBelow = 0.0f;
	m_fEstPrice = 0.0f;
	m_strLast = _T("");
	m_strNextYrEPS = _T("");
	m_strSymbol = _T("");
	m_fValPercent = 0.0f;
	m_strProj5YrGr = _T("");
	m_fCGI = 0.0f;
	//}}AFX_DATA_INIT
  m_pTicker = pTicker;
}


void CValDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValDlg)
	DDX_Text(pDX, IDC_VAL_BUY_BELOW, m_fBuyBelow);
	DDX_Text(pDX, IDC_VAL_EST_PRICE, m_fEstPrice);
	DDX_Text(pDX, IDC_VAL_LAST_QUOTE, m_strLast);
	DDX_Text(pDX, IDC_VAL_NEXT_YR_EPS, m_strNextYrEPS);
	DDX_Text(pDX, IDC_VAL_TICKER, m_strSymbol);
	DDX_Text(pDX, IDC_VAL_VALUATION, m_fValPercent);
	DDX_Text(pDX, IDC_VAL_PROJ_5YR_GROWTH, m_strProj5YrGr);
	DDX_Text(pDX, IDC_VAL_CGI, m_fCGI);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_VAL_UPD_PE, m_b_donot_upd_PE);
	DDX_Check(pDX, IDC_VAL_UPD_NEXT_YR_EPS, m_b_donot_upd_EPS);
	DDX_Check(pDX, IDC_VAL_UPD_EARN_GRWTH, m_b_donot_upd_Earn_Growth);
	DDX_Text(pDX, IDC_VAL_PE, m_val_PE);
}


BEGIN_MESSAGE_MAP(CValDlg, CDialog)
	//{{AFX_MSG_MAP(CValDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValDlg message handlers

BOOL CValDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  if (m_pTicker) {
	  m_fBuyBelow     = m_pTicker->m_Value.m_fBuyBelow;
	  m_fEstPrice     = m_pTicker->m_Value.m_fEstPrice;
	  m_strLast       = m_pTicker->m_strLast;
	  m_strNextYrEPS  = m_pTicker->m_Value.m_strMeanEst4;
	  m_strSymbol     = m_pTicker->m_strSymbol;
	  m_fValPercent   = m_pTicker->m_Value.m_fValPercent;
    m_strProj5YrGr  = m_pTicker->m_Value.m_strProj5YrGrowth;
    m_fCGI          = m_pTicker->m_Value.m_fCGI;
		m_val_PE				= m_pTicker->m_Value.m_strPE;
		m_b_donot_upd_PE			= m_pTicker->m_Value.m_b_donot_upd_strPE;
		m_b_donot_upd_EPS			= m_pTicker->m_Value.m_b_donot_upd_strMeanEst4;
		m_b_donot_upd_Earn_Growth = m_pTicker->m_Value.m_b_donot_upd_strProj5YrGrowth;
    UpdateData(FALSE);
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// CPref_RGB dialog

IMPLEMENT_DYNAMIC(CPref_RGB, CPropertyPage)
CPref_RGB::CPref_RGB()
	: CPropertyPage(CPref_RGB::IDD)
	, m_strROE(_T(""))
{
}

CPref_RGB::~CPref_RGB()
{
}

void CPref_RGB::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strROE);
}


BEGIN_MESSAGE_MAP(CPref_RGB, CPropertyPage)
END_MESSAGE_MAP()


// CPref_RGB message handlers

