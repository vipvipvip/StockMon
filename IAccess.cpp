// IAccess.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "mainfrm.h"
#include "SMDoc.h"
#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"
#include "IAccess.h"

#ifdef _DORAS_
#include <ras.h>
#include <rassapi.h>
#include <rasdlg.h>
#include <raserror.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIAccess

IMPLEMENT_DYNCREATE(CIAccess, CCmdTarget)

CIAccess::CIAccess()
{
	m_pInetSession=NULL;
	m_pHTTPConnection = NULL;
	m_pHTTPFile = NULL;
	m_pszWebPageContent = NULL;
	m_dwDataSendTimeOut = m_dwDataReceiveTimeOut = 60000;
	m_dwDataConnectTimeOut = 2*60000; // 2 minutes
	m_nWebBytesRecd=0;
	m_pDoc = NULL;
	m_pView = NULL;
}

CIAccess::~CIAccess()
{
	CloseConnection();
	CloseSession();
}


BEGIN_MESSAGE_MAP(CIAccess, CCmdTarget)
	//{{AFX_MSG_MAP(CIAccess)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIAccess message handlers

BOOL CIAccess::Init(CString& rWebAddress, CString& rstrTicker, DWORD dwThreadID, CSMDoc *pDoc, CSMView *pView)
{
	m_pDoc = pDoc;
	m_pView = pView;

	m_strWebAddress = rWebAddress;
	m_strTicker = rstrTicker;
	GetTicker();

	m_dwThreadID = dwThreadID;

	if(!AfxParseURL(m_strWebAddress, m_dwServiceType, m_strServer, m_strObject, m_nPort) ||
			m_dwServiceType != AFX_INET_SERVICE_HTTP )
		return FALSE;

	m_dwServiceType = AFX_INET_SERVICE_HTTP;
	return TRUE;
}

void CIAccess::GetTicker()
{
	if ( -1 != m_strTicker.Find((LPCTSTR)"SCREEN")) {
		return;
	}

	if ( -1 != m_strTicker.Find((LPCTSTR)"CHART")) {
		return;
	}

	if ( -1 != m_strTicker.Find((LPCTSTR)"GRAPH")) {
		return;
	}

	if ( -1 != m_strWebAddress.Find((LPCTSTR)"msshtml")) {
		return;
	}

	m_strTicker.Empty();
	CString strNasdaq, strAmex, strNyse;
	strNasdaq.LoadString(IDS_NASDAQT);
	strAmex.LoadString(IDS_AMEXT);
	strNyse.LoadString(IDS_NYSET);

	if ( -1 != m_strWebAddress.Find(strNasdaq) ) {
		m_strTicker = _T("NASDAQ");
	}
	else if (-1 != m_strWebAddress.Find(strAmex) ){
		m_strTicker = "AMEX";
	}
	else if (-1 != m_strWebAddress.Find(strNyse) ){
		m_strTicker = _T("NYSE");
	}
	else {
		int iPos = m_strWebAddress.ReverseFind('=');
    if ( iPos == -1 ) {
      iPos = m_strWebAddress.ReverseFind('?');
    }
		m_strTicker = m_strWebAddress.Mid(iPos+1);
	}
}


BOOL CIAccess::OpenSession(LPCTSTR lpProxy/*=NULL*/)
{
	if ( m_pInetSession )
		return TRUE;

	if (lpProxy) {
		m_strProxy = lpProxy;
		if(m_strProxy.IsEmpty()) {
			m_pInetSession = new CInternetSession(_T(""));
		}
		else {
			m_pInetSession = new CInternetSession(_T(""), 1, INTERNET_OPEN_TYPE_PROXY,(LPCTSTR)m_strProxy);
		}
	}
	else {
		m_pInetSession = new CInternetSession(_T(""));
	}

	ConfigureSession();

	return ( m_pInetSession != NULL );
}

void CIAccess::ConfigureSession()
{
	if ( !m_pInetSession )
		return;

	m_pInetSession->SetOption(INTERNET_OPTION_DATA_SEND_TIMEOUT,m_dwDataSendTimeOut); 
	m_pInetSession->SetOption(INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,m_dwDataReceiveTimeOut); 
	m_pInetSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, m_dwDataConnectTimeOut);
}


BOOL CIAccess::OpenConnection()
{
	if ( !m_pInetSession ) {
		return FALSE;
	}

	if ( -1 != m_strTicker.Find((LPCTSTR)"CHART")) {
		return TRUE;
	}

  THEAPP()->ShowProgress(_T("%s: Opening a connection ..."), m_strTicker);

	try {
		if ( !DoConnect() ) return FALSE;
		m_pHTTPConnection = m_pInetSession->GetHttpConnection(m_strServer);
		return TRUE;
	}
	catch (CInternetException *pEx ) {
		//pEx->ReportError();
		return FALSE;
	}
}

BOOL CIAccess::Read()
{
	if ( -1 != m_strTicker.Find(_T("CHART"))) {
		return ReadImage();
	}

	if ( !m_pHTTPConnection ) {
		return FALSE;
	}

	THEAPP()->ShowProgress(_T("%s: Waiting for response. Using proxy %s"), m_strTicker, m_strProxy);  
	m_pHTTPFile = m_pHTTPConnection->OpenRequest(1,(LPCTSTR)m_strObject, NULL, 1, NULL, NULL,INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
	if( m_pHTTPFile ) {
		CString str;
		try {
			m_pHTTPFile->SendRequest();
		}
		catch (CInternetException *pEx ) {
			m_pHTTPFile->Close();
			m_pHTTPFile=NULL;
			//pEx->ReportError();
			return FALSE;
		}
	}
	else {
		return FALSE;
	}

	try {
		THEAPP()->ShowProgress(_T("%s: Receiving data..."), m_strTicker);
		char sz[2048];
		memset(sz, 0, sizeof(sz)/sizeof(char));
		int iCount=0;
		CString str="";
		while ( (iCount=m_pHTTPFile->Read((char *)sz, (sizeof(sz)/sizeof(char)) ))) {
			str += sz;
			memset(sz, 0, sizeof(sz));
			m_nWebBytesRecd += iCount;
			THEAPP()->ShowProgress(_T("%s: Received %d bytes"), m_strTicker, str.GetLength());
		}

		if ( str.IsEmpty() ) 
			return FALSE;

		m_pszWebPageContent = (wchar_t *)calloc(str.GetLength() * sizeof(wchar_t), sizeof(wchar_t)) ;
		if(!m_pszWebPageContent) {
			return FALSE;
		}
		else {
			memcpy(m_pszWebPageContent, (wchar_t *)(LPCTSTR)str, str.GetLength() * sizeof(wchar_t));
		}
		
		//m_pszWebPageContent[str.GetLength()] = '\0';
		m_pHTTPFile->Close();
		m_pHTTPFile = NULL;
		return TRUE;
	}
	catch (CInternetException *pEx ) {
		m_pHTTPFile->Close();
		m_pHTTPFile=NULL;
		//pEx->ReportError();
		return FALSE;
	}
}

BOOL CIAccess::ReadImage()
{
	if ( !m_pInetSession )
		return FALSE;

	m_nWebBytesRecd = 0;

	m_pHTTPFile = (	CHttpFile* )m_pInetSession->OpenURL(m_strWebAddress);
	try {
		m_pszWebPageContent = new wchar_t[65535] ;
		if(!m_pszWebPageContent) {
			return FALSE;
		}
		else {
			memset(m_pszWebPageContent, 0, 65535);
		}
		
		THEAPP()->ShowProgress(_T("%s: Receiving data..."), m_strTicker);
		int iBytesRecd=0;
		WCHAR szT[4*1024];
		while (m_nWebBytesRecd < 65535 && (iBytesRecd = m_pHTTPFile->Read(szT, sizeof(szT)-1 ))) {
			memcpy(m_pszWebPageContent+m_nWebBytesRecd, szT, iBytesRecd);
			memset(szT, 0, sizeof(szT));
			m_nWebBytesRecd += iBytesRecd ;
			THEAPP()->ShowProgress(_T("%s: Received %d bytes"), m_strTicker, m_nWebBytesRecd );
		}

		m_pHTTPFile->Close();
		m_pHTTPFile = NULL;
		return TRUE;
	}
	catch (CInternetException *pEx ) {
		m_pHTTPFile->Close();
		m_pHTTPFile=NULL;
		FreeWebPageContent();
		//pEx->ReportError();
		return FALSE;
	}
}

BOOL CIAccess::CloseConnection()
{
	if (m_pHTTPConnection != NULL)
	{
		THEAPP()->ShowProgress(_T("%s: Closing a connection."), m_strTicker);
		m_pHTTPConnection->Close();
		m_pHTTPConnection = NULL;
	}
	return TRUE;
}

BOOL CIAccess::CloseSession()
{
	if (m_pInetSession != NULL)
	{
		m_pInetSession->Close();
		delete m_pInetSession;
		m_pInetSession = NULL;
	}
	return TRUE;
}

wchar_t *CIAccess::GetWebPageContent()
{
	return m_pszWebPageContent;
}

int CIAccess::GetWebPageBytes()
{
	return m_nWebBytesRecd;
}

void CIAccess::FreeWebPageContent()
{
	delete m_pszWebPageContent;
	m_pszWebPageContent = NULL;
	m_nWebBytesRecd = 0;
}


BOOL CIAccess::DoConnect()
{
	if (!m_pDoc) return FALSE;

	BOOL bRet = FALSE;
//	DWORD dwRet;
	CSingleLock sLock(&m_pDoc->m_mutex);
	
	try {
		sLock.Lock();
		if ( m_pDoc->m_bUseProxy == 0 ) { // Modem Connection
			if ( m_pDoc->m_DUP.IsEmpty() ) {
				// no entry is specified. Let it default to the setting
				// prefconfigured by the browser.
				return TRUE;
			}

			if ( m_pView->DoHangup(m_pDoc->m_DUP) == TRUE ) {
#ifdef _DORAS_
				// Do the RAS stuff
				RASDIALDLG rd;
				memset(&rd, 0, sizeof(rd) );
				rd.dwSize = sizeof(rd);
				rd.hwndOwner = NULL;
				dwRet = RasDialDlg(NULL,(LPSTR)(LPCTSTR)m_pDoc->m_DUP, NULL, &rd);

				if ( dwRet != 0 ) {
					bRet = TRUE;
				}
				else {
					char szBuf[256];
					if ( 0 == RasGetErrorString(dwRet, szBuf, sizeof(szBuf)) ) {
						AfxMessageBox(szBuf);
					}
					bRet = FALSE;
				}
#endif
			}
			else {
				// We already connected to the correct ISP
				bRet = TRUE;
			}
		}
		else {
			// Nothing to do for a lan connection
			bRet = TRUE;
		}
	}
	catch(...) {
		sLock.Unlock();
		return bRet;
	}

	sLock.Unlock();
	return bRet;
}
