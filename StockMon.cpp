// StockMon.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
//#include <wincrypt.h>
#include <afx.h>
#include "StockMon.h"

#include "MainFrm.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static CHAR THIS_FILE[] = __FILE__;
#endif




#ifdef USE_BLOCK_CIPHER
    // defines for RC2 block cipher
    #define ENCRYPT_ALGORITHM	CALG_RC2
    #define ENCRYPT_BLOCK_SIZE	8
#else
    // defines for RC4 stream cipher
    #define ENCRYPT_ALGORITHM	CALG_RC4
    #define ENCRYPT_BLOCK_SIZE	1
#endif

/*
BOOL CAPIDecryptFile(PCHAR szSource, CString& smlic, PCHAR szPassword)
{
// to use this funcion link with crypt32.lib.
  smlic.Empty();

  FILE *hSource      = NULL;
  INT eof = 0;

  HCRYPTPROV hProv   = 0;
  HCRYPTKEY hKey     = 0;
  HCRYPTHASH hHash   = 0;

  PBYTE pbKeyBlob = NULL;
  DWORD dwKeyBlobLen;

  PBYTE pbBuffer = NULL;
  DWORD dwBlockLen;
  DWORD dwBufferLen;
  DWORD dwCount;

  BOOL status = FALSE;

  // Open source file.
  if((hSource = fopen("SM.lic","rb")) == NULL) {
      goto done;
  }

  // Get handle to the default provider.
  if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
      goto done;
  }

  if(szPassword == NULL) {
	  // Decrypt the file with the saved session key.

	  // Read key blob length from source file and allocate memory.
  	  fread(&dwKeyBlobLen, sizeof(DWORD), 1, hSource);
	    if(ferror(hSource) || feof(hSource)) {
	      goto done;
  	  }
      if((pbKeyBlob = (PBYTE) calloc(dwKeyBlobLen,sizeof(BYTE) )) == NULL) {
	      goto done;
  	  }

	    // Read key blob from source file.
	    fread(pbKeyBlob, 1, dwKeyBlobLen, hSource);
	    if(ferror(hSource) || feof(hSource)) {
	        goto done;
	    }

	  // Import key blob into CSP.
	  if(!CryptImportKey(hProv, pbKeyBlob, dwKeyBlobLen, 0, 0, &hKey)) {
	      goto done;
	  }
  }
  else {
    // Decrypt the file with a session key derived from a password.

    // Create a hash object.
    if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	      goto done;
    }

    // Hash in the password data.
    if(!CryptHashData(hHash, (PBYTE)szPassword, wcslen(szPassword), 0)) {
	      goto done;
    }

    // Derive a session key from the hash object.
    if(!CryptDeriveKey(hProv, ENCRYPT_ALGORITHM, hHash, 0, &hKey)) {
	      goto done;
    }

    // Destroy the hash object.
    CryptDestroyHash(hHash);
    hHash = 0;
  }

  // Determine number of bytes to decrypt at a time. This must be a multiple
  // of ENCRYPT_BLOCK_SIZE.
  dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;
  dwBufferLen = dwBlockLen;

  // Allocate memory.
  if((pbBuffer = (PBYTE) calloc(dwBufferLen, sizeof(BYTE))) == NULL) {
    goto done;
  }

  // Decrypt source file and write to destination file.
  do {
	  // Read up to 'dwBlockLen' bytes from source file.
	  dwCount = fread(pbBuffer, 1, dwBlockLen, hSource);
	  if(ferror(hSource)) {
      goto done;
    }
	  eof = feof(hSource);

    // Decrypt data
    if(!CryptDecrypt(hKey, 0, eof, 0, pbBuffer, &dwCount)) {
      goto done;
    }
    smlic += (WCHAR *)pbBuffer;
  } while(!feof(hSource));

  status = TRUE;

  done:

  // Close files.
  if(hSource) fclose(hSource);

  // Free memory.
  if(pbKeyBlob) free(pbKeyBlob);
  if(pbBuffer) free(pbBuffer);

  // Destroy session key.
  if(hKey) CryptDestroyKey(hKey);

  // Destroy hash object.
  if(hHash) CryptDestroyHash(hHash);

  // Release provider handle.
  if(hProv) CryptReleaseContext(hProv, 0);

  return(status);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CSMApp

BEGIN_MESSAGE_MAP(CSMApp, CWinApp)
	//{{AFX_MSG_MAP(CSMApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSMApp construction
#define NUMVIEWS 2

CSMApp::CSMApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	WCHAR	strPath[ MAX_PATH ];
	if ( ::GetModuleFileName( NULL, strPath, MAX_PATH ))
	{
		CString str = strPath;
		int iPos = str.ReverseFind('\\');
		if ( -1 != iPos ) {
//			m_strResDLL = 	str.Left(iPos+1);
			m_strLicFileName = str.Left(iPos+1);
		}
	}
//	m_strResDLL += "SM.DLL";
	m_strLicFileName += "SM.Lic";
  m_pOldView = NULL;
m_strBrowser = "";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSMApp object

CSMApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSMApp initialization

BOOL CSMApp::InitInstance()
{
	// one of the first things in the init code
/*
	HINSTANCE hInst = LoadLibrary(m_strResDLL);
	if (hInst != NULL)
		AfxSetResourceHandle(hInst);
	else {
		CString str;
		str.Format("Unable to load %s", m_strResDLL);
		MessageBox(NULL, str, "Missing DLL", MB_OK);
		return FALSE;
	}
*/
	if ( ! ExtractResVerInfo())
	{
		return (FALSE);
	}


	int iRet = CheckLicKey(TRUE);
	CheckSerNo(iRet);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Added to enable writing ini info to the registry. This is required
	// in the UPersistentFrame Class where the window position is saved.
	m_pszAppName = _wcsdup( m_strProdNameAndVerNum );
	SetRegistryKey( m_strCompanyName );

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSMDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CSMView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	//if (m_lpCmdLine != NULL) {
	//		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	//}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

WCHAR *CSMApp::GetSerialNo()
{
//  static WCHAR *p = "995430623StockMon14";
//  return p;

	static WCHAR szT[MAX_PATH];

	_ultow(m_AuthKey.m_dwSerNo, szT, 10);
	CString str;
	str = "StockMon"; //m_pszAppName;

	int iPos = str.Find(' ');
	if ( iPos != -1 ) {
		wcscat(szT, str.Left(iPos));
	}
	else {
		wcscat ( szT, str);
	}

	// Append the serial number

	iPos = m_strVersionNum.Find('.');
	if (iPos != -1 ) {
		wcscat(szT,m_strVersionNum.Left(iPos));
		wcscat(szT,m_strVersionNum.Mid(iPos+1));
	}

	return szT;
}

BOOL CSMApp::CheckLicKey(BOOL bMsg)
{
  CString s;
  s = __DATE__;
  s.MakeReverse();
  s = s.Left(4);
  s.MakeReverse();

  time_t aclock;
  time(&aclock);
  struct tm *today;
  today = localtime( &aclock );  
  CString sTime = asctime( today ) ;
  sTime.MakeReverse();
  sTime = sTime.Left(5);
  sTime.MakeReverse();

	if ( _wtoi(sTime) > _wtoi(s)) {
    if ( bMsg ) {
      CString str;
      str = "This trial period for this software has expired. Contact the author at dikesh@hotmail.com";
      str = str + " and provide the following registration number. " + GetSerialNo();
		  MessageBox(NULL, str, m_strProdNameAndVerNum, MB_OK);
    }
    return FALSE;
	}
  else return TRUE;

/*	CFile f;
	int iAuth = f.Open(m_strLicFileName, CFile::modeRead);
	if ( !iAuth ) {
		if ( bMsg ) {
			CString strNotLic;
			strNotLic.LoadString(IDS_NOT_LIC_MSG);
			CString str;
			str.Format(strNotLic, GetSerialNo());
			MessageBox(NULL, str, m_strProdNameAndVerNum, MB_OK);
		}
		return FALSE;
	}
	else {
		return TRUE;
	}
*/
}

BOOL CSMApp::ChkForNine(CString szLic) 
{
	CString str = GetSerialNo();
	CString strDec = Decrypt((LPTSTR)(LPCTSTR)szLic);

	if ( str.GetLength() != strDec.GetLength() ) {
		return FALSE;
	}

	int iLen = str.GetLength();
	for (int i=0; i<iLen; i++ ) {
		if ( str[i] != strDec[i] && str[i] != '9' ) {
			return FALSE;
		}
	}

	return TRUE;

}

BOOL CSMApp::CheckSerNo(BOOL bMsg) 
{
  CString s;
  s = __DATE__;
  s.MakeReverse();
  s = s.Left(4);
  s.MakeReverse();

  time_t aclock;
  time(&aclock);
  struct tm *newtime;
  newtime = localtime( &aclock );  
  CString sTime = asctime( newtime ) ;
  sTime.MakeReverse();
  sTime = sTime.Left(5);
  sTime.MakeReverse();

	if ( _wtoi(sTime) > _wtoi(s)) {
    if ( bMsg ) {
      CString str;
      str = "This trial period for this software has expired. Contact the author at dikesh@bigfoot.com";
      str = str + " and provide the following registration number. " + GetSerialNo();
		  MessageBox(NULL, str, m_strProdNameAndVerNum, MB_OK);
    }
    return FALSE;
	}
  else return TRUE;


/*
BOOL bRet=FALSE;
	CFile f;
	int iAuth = f.Open(m_strLicFileName, CFile::modeRead);
  if (iAuth) f.Close();

	if ( bMsg ) {
		CString strNotLic;
		if (!iAuth) {
			CString strNotLic;
			strNotLic.LoadString(IDS_NOT_LIC_MSG);
			CString str;
			str.Format(strNotLic, GetSerialNo());
			MessageBox(NULL, str, m_strProdNameAndVerNum, MB_OK);
		}
	}

	CString str1;
  CString str2(GetSerialNo());
  if ( iAuth && !CAPIDecryptFile((LPTSTR)(LPCTSTR)m_strLicFileName, str1,NULL) ) {
		CString strNotLic;
		if (bMsg) {
			strNotLic.LoadString(IDS_INVALID_SER_NO_MSG);
			CString str;
			str.Format(strNotLic, m_strLicFileName);
			MessageBox(NULL, str, m_strProdNameAndVerNum, MB_OK);
		}
  }

	if ( str1.Left(str2.GetLength()) == str2) {
		return TRUE;
  }


	return bRet;
*/
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strAuthKey;
	CString	m_strAuthMsg;
	CString	m_strBuildDate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strAuthKey = _T("");
	m_strAuthMsg = _T("");
	m_strBuildDate = _T("");
	//}}AFX_DATA_INIT
	m_strAuthKey = "ILLEGAL COPY";
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_AUTH_KEY, m_strAuthKey);
	DDX_Text(pDX, IDC_MESSAGE, m_strAuthMsg);
	DDX_Text(pDX, IDC_BUILD_DATE, m_strBuildDate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// App command to run the dialog
void CSMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.m_strAuthMsg = THEAPP()->m_strProdNameAndVerNum;
	aboutDlg.m_strAuthKey = GetSerialNo();
	if ( CheckLicKey(FALSE) && CheckSerNo(FALSE) ) {
		aboutDlg.m_strAuthMsg.LoadString(IDS_ABOUT_LEGAL);
	}
	else {
		aboutDlg.m_strAuthMsg.LoadString(IDS_ABOUT_ILLEGAL);
	}
  aboutDlg.m_strBuildDate = __DATE__;
  aboutDlg.m_strBuildDate += " @ "  __TIME__;
  aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSMApp commands

void CSMApp::ShowProgress ( LPCTSTR lpszFormat, ...)
{
	if (lpszFormat) {
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		va_list args;
		va_start(args, lpszFormat);
		WCHAR szBuffer[512];
		vswprintf(szBuffer, lpszFormat, args);
		pMainWnd->SetMessageText((LPCTSTR)szBuffer);
	}
}

void CSMApp::ShowMsgText ( LPCTSTR lpszFormat, ...)
{
	if (lpszFormat) {
		CMainFrame *pMainWnd = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		va_list args;
		va_start(args, lpszFormat);
		WCHAR szBuffer[512];
		memset(szBuffer, 0, sizeof(szBuffer));
		vswprintf(szBuffer, lpszFormat, args);
		SendMessage(pMainWnd->m_hWnd, SHOWMSGTEXT, 0, (LPARAM)szBuffer);
	}
}

BOOL CSMApp::ExtractResVerInfo()
{
	WCHAR	strPath[ MAX_PATH ];
//	strcpy(strPath, (LPTSTR)(LPCTSTR)m_strResDLL);


	if ( ! ::GetModuleFileName( NULL, strPath, MAX_PATH ))
	{
		return (FALSE);
	}


	DWORD dwHandle;
	DWORD dwVerInfoSize = ::GetFileVersionInfoSize( strPath, &dwHandle );
	if (dwVerInfoSize == 0)
	{
		return (FALSE);
	}

	/*
	** Allocate and lock a memory block large enough to hold the version information.
	*/
	HGLOBAL hGlbl = ::GlobalAlloc( GMEM_MOVEABLE, dwVerInfoSize );
	if (hGlbl == NULL)
	{
		return (FALSE);
	}
	LPVOID pVerInfo = ::GlobalLock( hGlbl );

	/*
	** Load the version information into memory.
	*/
	if ( ! ::GetFileVersionInfo( strPath, dwHandle, dwVerInfoSize, pVerInfo ))
	{
		(void)GlobalFree( hGlbl );
		return (FALSE);
	}

	DWORD*	pnXlate;
	UINT		uLen;
	long		vqvRet;

	vqvRet = (long)::VerQueryValue( pVerInfo, _T("\\VarFileInfo\\Translation"),
													(LPVOID*)&pnXlate, &uLen );
	if ((vqvRet == 0) || (uLen == 0))
	{
		(void)::GlobalUnlock( hGlbl );
		(void)::GlobalFree( hGlbl );
		return (FALSE);
	}

	WCHAR	szBuf[ 200 ];
	WCHAR*	pstrData;

	swprintf( szBuf, _T("\\StringFileInfo\\%04x%04x\\CompanyName"),
				LOWORD( *pnXlate ), HIWORD( *pnXlate ) );
	vqvRet = (long)::VerQueryValue( pVerInfo, szBuf, (LPVOID*)&pstrData, &uLen );
	if ((vqvRet == 0) || (uLen == 0))
	{
		(void)::GlobalUnlock( hGlbl );
		(void)::GlobalFree( hGlbl );
		return (FALSE);
	}
	m_strCompanyName = pstrData;

	swprintf( szBuf, _T("\\StringFileInfo\\%04x%04x\\ProductName"),
				LOWORD( *pnXlate ), HIWORD( *pnXlate ) );
	vqvRet = (long)::VerQueryValue( pVerInfo, szBuf, (LPVOID*)&pstrData, &uLen );
	if ((vqvRet == 0) || (uLen == 0))
	{
		(void)::GlobalUnlock( hGlbl );
		(void)::GlobalFree( hGlbl );
		return (FALSE);
	}
	m_strProductName = pstrData;

	swprintf( szBuf, _T("\\StringFileInfo\\%04x%04x\\ProductVersion"),
				LOWORD( *pnXlate ), HIWORD( *pnXlate ) );
	vqvRet = (long)::VerQueryValue( pVerInfo, szBuf, (LPVOID*)&pstrData, &uLen );
	if ((vqvRet == 0) || (uLen == 0))
	{
		(void)::GlobalUnlock( hGlbl );
		(void)::GlobalFree( hGlbl );
		return (FALSE);
	}

	/*
	** Parse out the product version number: EE.ee.II.ii
	*/
	WCHAR * pstr = pstrData;
	long	verNumExternalMajor = wcstol(   pstr, &pstr, 10 );
	long	verNumExternalMinor = wcstol( ++pstr, &pstr, 10 );
	long	verNumInternalMajor = wcstol( ++pstr, &pstr, 10 );
/*	long	verNumInternalMinor = wcstol( ++pstr, &pstr, 10 ); - Unused as of 7/12/95 */

	(void)::GlobalUnlock( hGlbl );
	(void)::GlobalFree( hGlbl );

	if (verNumInternalMajor > 0)
	{
		m_strVersionNum.Format( (LPCTSTR) "%ld.%ld.%ld",
			verNumExternalMajor, verNumExternalMinor, verNumInternalMajor );
	}
	else
	{
		m_strVersionNum.Format(_T("%ld.%ld"),
			verNumExternalMajor, verNumExternalMinor );
	}

	m_strProdNameAndVerNum.Format(_T("%s %s"), m_strProductName, m_strVersionNum);

	return (TRUE);

} 


CView* CSMApp::SwitchView(CView* pNewView)
{
  m_pOldView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

  // Exchange view window ID's so RecalcLayout() works.
  #ifndef _WIN32
  UINT temp = ::GetWindowWord(m_pOldView->m_hWnd, GWW_ID);
  ::SetWindowWord(pActiveView->m_hWnd, GWW_ID,
                 ::GetWindowWord(pNewView->m_hWnd, GWW_ID));
  ::SetWindowWord(pNewView->m_hWnd, GWW_ID, temp);
  #else
  UINT temp = ::GetWindowLong(m_pOldView->m_hWnd, GWL_ID);
  ::SetWindowLong(m_pOldView->m_hWnd, GWL_ID,
                 ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
  ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
  #endif

  m_pOldView->ShowWindow(SW_HIDE);
  pNewView->ShowWindow(SW_SHOW);
  ((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView);
  ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
  pNewView->Invalidate();
  return m_pOldView;
}


WCHAR *CSMApp::Encrypt(WCHAR *pString)
{
	if ( !pString ) {
		return NULL;
	}

	unsigned short middle;
	short key, modify, neWCHAR;

	if (!wcslen(pString)) return pString;	// nothing to encrypt
	middle = wcslen(pString)/2;

	if (isdigit( pString[middle] )) {
		pString[middle] = '9' - pString[middle] + '0';
		key = pString[middle];
	}
	else if (isalpha( pString[middle] )) {
		if (isupper( pString[middle] ))
			pString[middle] = 'Z' - pString[middle] + 'A';
		else
			pString[middle] = 'z' - pString[middle] + 'a';
		key = pString[middle];
	}
	else		// non-alphanumerical is illegal
		return pString;

	key = abs(key) + 1;
	for (unsigned short i=0; i<wcslen(pString); i++) {
		if (i == middle) continue;
		modify = ((i*i)/key) + ((key*key)/(i+1)) + i*key + i + key;
		if ( isdigit( pString[i] )) {
			modify = modify % 9;

			neWCHAR = pString[i] - '0' + modify;
			if (neWCHAR <= 9)
				pString[i] = neWCHAR + '0';
			else
				pString[i] = neWCHAR - 9 + '0';
		}
		else if ( isalpha( pString[i] )) {
			modify = abs(modify) % 25;

			if (isupper( pString[i] )) {
				neWCHAR = pString[i] - 'A' + modify;
				if (neWCHAR <= 25)
					pString[i] = neWCHAR + 'A';
				else
					pString[i] = neWCHAR - 25 + 'A';	
			}
			else {
				neWCHAR = pString[i] - 'a' + modify;
				if (neWCHAR <= 25)
					pString[i] = neWCHAR + 'a';
				else
					pString[i] = neWCHAR - 25 + 'a';	
			}
		}
	}
	return pString;
}

WCHAR *CSMApp::Decrypt(WCHAR *pString)
{
	unsigned short middle, i;
	short key, modify;

	if (!wcslen(pString)) return pString;	// nothing to decrypt
	middle = wcslen(pString)/2;

	if (isdigit( pString[middle] )) {
		key = pString[middle];
		pString[middle] = '9' - pString[middle] + '0';
	}
	else if (isalpha( pString[middle] )) {
		key = pString[middle];
		if (isupper( pString[middle] ))
			pString[middle] = 'Z' - pString[middle] + 'A';
		else
			pString[middle] = 'z' - pString[middle] + 'a';
	}
	else		// non-alphanumerical is illegal
		return pString;

	key = abs(key) + 1;
	for (i=0; i<wcslen(pString); i++) {
		if (i == middle) continue;
		modify = ((i*i)/key) + ((key*key)/(i+1)) + i*key + i + key;
		if ( isdigit( pString[i] )) {
			modify = modify % 9;

			if ( (pString[i]-'0') < modify )
				pString[i] = pString[i] + 9 - modify;
			else 
				pString[i] = pString[i]  - modify;
		}
		else if ( isalpha( pString[i] )) {
			modify = modify % 25;

			if (isupper( pString[i] )) {
				if ( (pString[i]-'A') < modify )
					pString[i] = pString[i] + 25 - modify;
				else 
					pString[i] = pString[i]  - modify;
			}
			else {
				if ( (pString[i]-'a') < modify )
					pString[i] = pString[i] + 25 - modify;
				else 
					pString[i] = pString[i]  - modify;
			}
		}
	}
	return pString;
}

// StripTags() rips through a buffer and removes HTML tags from it.
// The function uses a static variable to remember its state in case
// a HTML tag spans a buffer boundary.

void CSMApp::StripTags(LPWSTR pszBuffer)
{
	static BOOL bInTag = FALSE;
	LPTSTR pszSource = pszBuffer;
	LPWSTR pszDest = pszBuffer;
  int iCount=0;
  LPWSTR p = pszDest;

	while (*pszSource != '\0')
	{
		if (bInTag)
		{
			if (*pszSource == '>') {
				bInTag = FALSE;
				*pszDest = '\x20';
				pszDest++;
				iCount++;
			}
			pszSource++;
		}
		else
		{
			if (*pszSource == '<')
				bInTag = TRUE;
			else
			{
				*pszDest = *pszSource;
				pszDest++;
		        iCount++;
			}
			pszSource++;
		}
	}
	*pszDest = '\0';

#ifdef  _DEBUG
	CFile f;
	int bOpen = f.Open(_T("c:\\temp\\x.htm"), CFile::modeCreate | CFile::modeWrite);
	if ( bOpen ) {
		f.Write(pszBuffer, iCount);
		f.Close();
	}
#endif

}
LPCTSTR CSMApp::GetBrowser()
{
  // Have we already got the browser?
  if (m_strBrowser.IsEmpty())
  {
   // Get the default browser from HKCR\http\shell\open\command
   HKEY hKey = NULL;
   // Open the registry
   if (::RegOpenKeyEx(HKEY_CLASSES_ROOT, _T("http\\shell\\open\\command"),
     0, KEY_READ, &hKey) == ERROR_SUCCESS)
   {
    // Data size
    DWORD cbData = 0;
    // Get the default value
    if (::RegQueryValueEx(hKey, NULL, NULL, NULL, NULL, &cbData) 
        == ERROR_SUCCESS && cbData > 0)
    {
     // Allocate a suitable buffer
     WCHAR* psz = new WCHAR [cbData];
     // Success?
     if (psz != NULL)
     {
      if (::RegQueryValueEx(hKey, NULL, NULL,
       NULL, (LPBYTE)psz, &cbData) ==
       ERROR_SUCCESS)
      {
       // Success!
       m_strBrowser = psz;
      }
      delete [] psz;
     }
    }
    ::RegCloseKey(hKey);
   }
   // Do we have the browser?
   if (m_strBrowser.GetLength() > 0)
   {
    // Strip the full path from the string
    int nStart = m_strBrowser.Find('"');
    int nEnd = m_strBrowser.ReverseFind('"');
    // Do we have either quote?
    // If so, then the path contains spaces
    if (nStart >= 0 && nEnd >= 0)
    {
     // Are they the same?
     if (nStart != nEnd)
     {   
      // Get the full path
      m_strBrowser = m_strBrowser.Mid(nStart + 1, nEnd - nStart - 1);
     }
    }
    else
    {
     // We may have a pathname with spaces but
     // no quotes (Netscape), e.g.:
     //   C:\PROGRAM FILES\NETSCAPE\COMMUNICATOR\PROGRAM\NETSCAPE.EXE -h "%1"
     // Look for the last backslash
     int nIndex = m_strBrowser.ReverseFind('\\');
     // Success?
     if (nIndex > 0)
     {
      // Look for the next space after the final
      // backslash
      int nSpace = m_strBrowser.Find(' ', nIndex);
      // Do we have a space?
      if (nSpace > 0)
       m_strBrowser = m_strBrowser.Left(nSpace);    
     }
    }
   }
  }
  // Done
  return m_strBrowser;
 }

