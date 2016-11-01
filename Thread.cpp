// hread.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "SMDoc.h"
#include "listvwex.h"
#include "SMView.h"
#include "IAccess.h"
#include "ReadMsg.h"
#include "request.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInternetThread

IMPLEMENT_DYNCREATE(CInternetThread, CWinThread)

CInternetThread::CInternetThread()
{
	m_bDone = FALSE;
	m_hOwner = NULL; 
	m_pDoc = NULL; 
	m_hWorkEvent = NULL;
	m_nPendingReq=0;
	m_pView = NULL;
}

CInternetThread::~CInternetThread()
{
}

BOOL CInternetThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CInternetThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CInternetThread, CWinThread)
	//{{AFX_MSG_MAP(CInternetThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CInternetThread::Init(HWND hOwner, CSMDoc *pDoc, HANDLE hWorkEvent, CSMView *pView) 
{ 
	m_hOwner = hOwner; 
	m_pDoc = pDoc; 
	m_hWorkEvent = hWorkEvent;
	m_pView = pView;

}
/////////////////////////////////////////////////////////////////////////////
// CInternetThread message handlers
int CInternetThread::Run() 
{
	CString strProxy;
	if (m_pDoc->m_bUseProxy == 0) {
		if (m_hOwner == NULL || !m_aWWW.OpenSession())
			return -1;
	}
	else {
		if(!m_pDoc->m_strProxy.IsEmpty()) {
			strProxy = m_pDoc->m_strProxy;
		}

		if(!m_pDoc->m_strPort.IsEmpty()) {
			strProxy += ':';
			strProxy += m_pDoc->m_strPort;
		}

		if (m_hOwner == NULL || !m_aWWW.OpenSession(strProxy))
			return -1;
	}


	CSingleLock sLock(&m_pDoc->m_mutex);
	BOOL bErr=TRUE;
	DWORD dwRet;
  CString strIden;
  CCmdTarget *pWWW=NULL;
	while (!m_bDone) {
		dwRet = WaitForSingleObject(m_hWorkEvent, INFINITE);
		while ( !m_bDone && m_pDoc->m_ReqArray.GetSize() ) {
			bErr=TRUE;
			sLock.Lock();
			try {
				CRequest *pReq = (CRequest *)m_pDoc->m_ReqArray[0];
				m_strWebAddress = pReq->m_strWebPageAddress;
				m_strAltImageLocation = pReq->m_strAltImageLocation;
				m_strTicker = pReq->m_strIdentifier;
        pWWW = pReq->m_pWWW;
        strIden = pReq->m_strIdentifier;
				m_pDoc->m_ReqArray.RemoveAt(0);
				delete pReq;
			}
			catch(...) {
				sLock.Unlock();
				continue;
			}
			sLock.Unlock();

			if(m_strWebAddress.IsEmpty())
				continue;

			++m_nPendingReq;

			GetTicker();

			THEAPP()->ShowMsgText(_T("%s: Waiting for a quote."), (LPCTSTR)m_strTicker);
			BOOL bContinue = TRUE;
			CString strAddr = m_strWebAddress;
			while (bContinue) {
				if( m_aWWW.Init(strAddr, m_strTicker, m_nThreadID, m_pDoc, m_pView)) {
					if(m_aWWW.OpenConnection()) {
						if(m_aWWW.Read()) {
							if (-1 != m_strTicker.Find(_T("CHART"))) {
								CString str = m_aWWW.GetWebPageContent();
								CString strToken;
								strToken.LoadString(IDS_TECHSTKS_COY_NOT_FOUND);
								if ( !m_strAltImageLocation.IsEmpty() && -1 != str.Find(strToken)) {
									m_aWWW.CloseConnection();
									strAddr = m_strAltImageLocation;
									continue;
								}
								else {
									WriteImage();
								}

								bContinue=FALSE;
							}
							else {
								CReadMsg msg;
								msg.m_strWebPageContent = m_aWWW.GetWebPageContent();
								msg.m_pThread = this;
                msg.m_pWWW = pWWW;
								if ( !::IsWindow(m_hOwner) ) {
									m_aWWW.CloseConnection();
									bContinue=FALSE;
								}
                if (-1 != strIden.Find(_T("FUNDA")) || -1 != strIden.Find(_T("VALUE")) || -1 != strIden.Find(_T("RGB")) ) {
                  SendMessage(m_hOwner, READ_COMPLETED, (WPARAM)(LPCTSTR)strIden, (LPARAM)&msg);
                  strIden.Empty();
                }
                else {
								  SendMessage(m_hOwner, READ_COMPLETED, (WPARAM)(LPCTSTR)m_strTicker, (LPARAM)&msg);
                }
								--m_nPendingReq;
								bErr=FALSE;
								bContinue = FALSE;
							}
						} // end Read
						else {
							bContinue = FALSE;
						}

						m_aWWW.CloseConnection();
						THEAPP()->ShowProgress(_T("Ready"));

					} // end OpenConnection
					else {
						bContinue = FALSE;
					}
				} // end Init
				else {
					bContinue = FALSE;
				}
			} // end while (bContinue) 

			if (bErr && ::IsWindow(m_hOwner)) {
				SendMessage(m_hOwner, READ_COMPLETED, (WPARAM)0, (LPARAM)0);
			}
		} // end inner while

	} // end while (!m_bDone) 
	m_aWWW.CloseSession();

	while (m_nPendingReq && ::IsWindow(m_hOwner)) {
		SendMessage(m_hOwner, READ_COMPLETED, (WPARAM)0, (LPARAM)0);
		--m_nPendingReq;
	}

	return 0;
}

void CInternetThread::WriteImage()
{
	CString strFileName;


	// Parse out the ticker
	CString strTicker;
	int iPos = m_strTicker.Find(':');
	if ( iPos != -1 ) {
		strTicker = m_strTicker.Left(iPos);
	}
	else {
		strTicker = m_strTicker;
	}

	strFileName		=	m_pDoc->m_strImageLocation;	
	strFileName		+=  strTicker;
	strFileName		+=  _T(".gif");

	CFile f;
	if ( f.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {
		f.Write(m_aWWW.GetWebPageContent(), m_aWWW.GetWebPageBytes());
	}
	else {
		CString str;
		str.Format(_T("Unable to open %s. Please set a valid charts directory in the View/Options dialog"), strFileName); 
		AfxMessageBox(str); 
	}
		m_aWWW.FreeWebPageContent();
}

void CInternetThread::GetTicker()
{
	if ( -1 != m_strTicker.Find(_T("SCREEN"))) {
		return;
	}

	if ( -1 != m_strTicker.Find(_T("CHART"))) {
		return;
	}

	if ( -1 != m_strTicker.Find(_T("GRAPH"))) {
		return;
	}

	if ( -1 != m_strTicker.Find(_T("CONAME"))) {
		return;
	}

	if ( -1 != m_strTicker.Find(_T("FUNDA"))) {
		return;
	}

	if ( -1 != m_strTicker.Find(_T("VALUE"))) {
		int iPos = m_strTicker.ReverseFind(':');
    if ( iPos != -1 ) {
  		m_strTicker = m_strTicker.Mid(iPos+1);
    }
		return;
	}

		if ( -1 != m_strTicker.Find(_T("RGB"))) {
		int iPos = m_strTicker.ReverseFind(':');
    if ( iPos != -1 ) {
  		m_strTicker = m_strTicker.Mid(iPos+1);
    }
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
		m_strTicker = _T("AMEX");
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

void CInternetThread::SetWebAddress(CString& rWebAddress)
{
	m_strWebAddress = rWebAddress;
}

wchar_t * CInternetThread::GetWebPageContent()
{
	return m_aWWW.GetWebPageContent();
}

void CInternetThread::FreeWebPageContent()
{
	m_aWWW.FreeWebPageContent();
}
