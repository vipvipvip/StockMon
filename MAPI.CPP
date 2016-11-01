// Mapi.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "Mapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapi

IMPLEMENT_DYNCREATE(CMapi, CWinThread)

CMapi::CMapi()
{
	m_hInstMail = NULL;
	m_lpfnSendMail = NULL;
}

CMapi::~CMapi()
{
	if (m_hInstMail != NULL)
		::FreeLibrary(m_hInstMail);
}

BOOL CMapi::InitInstance()
{
	if (m_hInstMail == NULL)
		m_hInstMail = ::LoadLibraryA("MAPI32.DLL");

	if (m_hInstMail == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD);
		return FALSE;
	}

	ASSERT(m_hInstMail != NULL);

	ULONG (PASCAL *lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
	(FARPROC&)m_lpfnSendMail = GetProcAddress(pMailState->m_hInstMail, "MAPISendMail");

	if (m_lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
		return FALSE;
	}

	ASSERT(lpfnSendMail != NULL);
	return TRUE;
}

int CMapi::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMapi, CWinThread)
	//{{AFX_MSG_MAP(CMapi)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapi message handlers
