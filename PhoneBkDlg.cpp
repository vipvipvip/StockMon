// PhoneBkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyRas.h"
#include "PhoneBkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PhoneBkDlg dialog


PhoneBkDlg::PhoneBkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PhoneBkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PhoneBkDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PhoneBkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PhoneBkDlg)
	DDX_Control(pDX, IDC_ENTRIES, m_pLBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PhoneBkDlg, CDialog)
	//{{AFX_MSG_MAP(PhoneBkDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PhoneBkDlg message handlers

BOOL PhoneBkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    LPRASENTRYNAME lpRasEntry;
    LPRASENTRYNAME lpTemp;
    DWORD cbBuf;
    DWORD cEntry;
    DWORD dwRet;
    UINT  ndx;
    char  szMessage[256];

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
  
	return TRUE;
}


void PhoneBkDlg::OnOk() 
{
	RASENTRYDLG e;
	e.dwSize = sizeof(e);
	e.hwndOwner = NULL;
	e.dwFlags = RASEDFLAG_CloneEntry;
	LPTSTR p = "Prodigy";


//	RasEditPhonebookEntry(NULL, NULL, "Prodigy");

	RASPBDLG pb;
	pb.dwSize = sizeof(pb);
	pb.hwndOwner = NULL;
	pb.dwFlags = RASPBDFLAG_ForceCloseOnDial;
	pb.pCallback=NULL;
	RasPhonebookDlg(NULL, NULL, &pb);
}
