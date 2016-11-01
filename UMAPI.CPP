// UMapi.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "UMapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static ULONG (PASCAL *m_lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);

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

	(FARPROC&)m_lpfnSendMail = GetProcAddress(m_hInstMail, "MAPISendMail");
	if (m_lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL);
		return FALSE;
	}

	ASSERT(m_lpfnSendMail != NULL);

	return SendMail();
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
int CMapi::SendMail()
{
	// prepare the message (empty with 1 attachment)
	MapiMessage message;
	memset(&message, 0, sizeof(message));

	// prepare for modal dialog box
	AfxGetApp()->EnableModeless(FALSE);
	HWND hWndTop;
	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop);

	// some extra precautions are required to use MAPISendMail as it
	// tends to enable the parent window in between dialogs (after
	// the login dialog, but before the send note dialog).
	pParentWnd->SetCapture();
	::SetFocus(NULL);
	pParentWnd->m_nFlags |= WF_STAYDISABLED;

	int nError = m_lpfnSendMail(0, (ULONG)pParentWnd->GetSafeHwnd(),
		&message, MAPI_LOGON_UI|MAPI_DIALOG, 0);

	// after returning from the MAPISendMail call, the window must
	// be re-enabled and focus returned to the frame to undo the workaround
	// done before the MAPI call.
	::ReleaseCapture();
	pParentWnd->m_nFlags &= ~WF_STAYDISABLED;

	pParentWnd->EnableWindow(TRUE);
	::SetActiveWindow(NULL);
	pParentWnd->SetActiveWindow();
	pParentWnd->SetFocus();
	if (hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE);
	AfxGetApp()->EnableModeless(TRUE);

	if (nError != SUCCESS_SUCCESS &&
		nError != MAPI_USER_ABORT && nError != MAPI_E_LOGIN_FAILURE)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND);
		return FALSE;
	}
	return (nError==SUCCESS_SUCCESS ? 1 : 0);
}