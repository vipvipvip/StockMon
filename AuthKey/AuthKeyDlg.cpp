// AuthKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include <direct.h> // for chdir
#include "AuthKey.h"
#include "AuthKeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <wincrypt.h>

#ifdef USE_BLOCK_CIPHER
    // defines for RC2 block cipher
    #define ENCRYPT_ALGORITHM	CALG_RC2
    #define ENCRYPT_BLOCK_SIZE	8
#else
    // defines for RC4 stream cipher
    #define ENCRYPT_ALGORITHM	CALG_RC4
    #define ENCRYPT_BLOCK_SIZE	1
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
BOOL CAPIDecryptFile(CString szSource, CString& smlic, PCHAR szPassword)
{
  smlic.Empty();


  HCRYPTPROV hProv   = 0;
  HCRYPTKEY hKey     = 0;
  HCRYPTHASH hHash   = 0;

  PBYTE pbKeyBlob = NULL;
  DWORD dwKeyBlobLen = *((PBYTE)szSource.GetBuffer(sizeof(DWORD)));

  PBYTE pbBuffer = NULL;
  DWORD dwBlockLen;
  DWORD dwBufferLen;
  DWORD dwCount;

  BOOL status = FALSE;

  // Get handle to the default provider.
  if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
      goto done;
  }

  if(szPassword == NULL) {
	  // Decrypt the file with the saved session key.

      if((pbKeyBlob = (PBYTE) calloc(dwKeyBlobLen,sizeof(BYTE) )) == NULL) {
	      goto done;
  	  }

	    // Read key blob from source file.
      pbKeyBlob = (PBYTE)szSource.GetBuffer(sizeof(DWORD));

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
    if(!CryptHashData(hHash, (PBYTE)szPassword, strlen(szPassword), 0)) {
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
  // Read up to 'dwBlockLen' bytes from source file.
  dwCount = szSource.GetLength();
  // Decrypt data
  if(!CryptDecrypt(hKey, 0, 1, 0, pbBuffer, &dwCount)) {
    goto done;
  }
  smlic += pbBuffer;

  status = TRUE;

  done:

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

BOOL CAPIEncrypt(CString& szSource, CString& szDestination, PCHAR szPassword)
{
  szDestination.Empty();

  HCRYPTPROV hProv   = 0;
  HCRYPTKEY hKey     = 0;
  HCRYPTKEY hXchgKey = 0;
  HCRYPTHASH hHash   = 0;

  PBYTE pbKeyBlob = NULL;
  DWORD dwKeyBlobLen;

  PBYTE pbBuffer = NULL;
  DWORD dwBlockLen;
  DWORD dwBufferLen;
  DWORD dwCount;

  BOOL status = FALSE;

  // Get handle to the default provider.
  if(!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) {
      goto done;
  }

  if(szPassword == NULL) {
  // Encrypt the file with a random session key.

  // Create a random session key.
  if(!CryptGenKey(hProv, ENCRYPT_ALGORITHM, CRYPT_EXPORTABLE, &hKey)) {
	  goto done;
  }

  // Get handle to key exchange public key.
  if(!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hXchgKey)) {
	  goto done;
  }

  // Determine size of the key blob and allocate memory.
  if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &dwKeyBlobLen)) {
	  goto done;
  }
  if((pbKeyBlob = (PBYTE)calloc(dwKeyBlobLen, sizeof(BYTE))) == NULL) {
	  goto done;
  }

  // Export session key into a simple key blob.
  if(!CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, pbKeyBlob, &dwKeyBlobLen)) {
	  goto done;
  }

  // Release key exchange key handle.
  CryptDestroyKey(hXchgKey);
  hXchgKey = 0;

  szDestination.Format("%d%s", dwKeyBlobLen,pbKeyBlob); 


  } else {
  // Encrypt the file with a session key derived from a password.

  // Create a hash object.
  if(!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
	  goto done;
  }

  // Hash in the password data.
  if(!CryptHashData(hHash, (const PBYTE)(LPSTR)(LPCTSTR)szPassword, strlen(szPassword), 0)) {
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

  // Determine number of bytes to encrypt at a time. This must be a multiple
  // of ENCRYPT_BLOCK_SIZE.
  dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE;

  // Determine the block size. If a block cipher is used this must have
  // room for an extra block.
  if(ENCRYPT_BLOCK_SIZE > 1) {
  dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE;
  } else {
  dwBufferLen = dwBlockLen;
  }

  // Allocate memory.
  if((pbBuffer = (PBYTE)calloc(dwBufferLen, sizeof(BYTE))) == NULL) {
    goto done;
  }

  // Encrypt source file and write to Source file.
  // Read up to 'dwBlockLen' bytes from source file.
  dwCount = szSource.GetLength();

    // Encrypt data
  if(!CryptEncrypt(hKey, 0, 1, 0, pbBuffer, &dwCount, dwBufferLen)) {
          goto done;
  }

  szDestination += pbBuffer;
  status = TRUE;

  done:

  // Free memory.
  if(pbKeyBlob) free(pbKeyBlob);
  if(pbBuffer) free(pbBuffer);

  // Destroy session key.
  if(hKey) CryptDestroyKey(hKey);

  // Release key exchange key handle.
  if(hXchgKey) CryptDestroyKey(hXchgKey);

  // Destroy hash object.
  if(hHash) CryptDestroyHash(hHash);

  // Release provider handle.
  if(hProv) CryptReleaseContext(hProv, 0);

  return(status);
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
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
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthKeyDlg dialog

CAuthKeyDlg::CAuthKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAuthKeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuthKeyDlg)
	m_strEncrypted = _T("");
	m_strSource = _T("");
	m_strDecrypted = _T("");
	m_strLicFileName = _T("");
	m_strEncryptedFile = _T("");
	m_strVersion = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strSource = "2557091597";
	m_strEncryptedFile = "C:\\sm.lic";
}

void CAuthKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthKeyDlg)
	DDX_Text(pDX, IDC_ENCRYPT, m_strEncrypted);
	DDX_Text(pDX, IDC_SOURCE, m_strSource);
	DDX_Text(pDX, IDC_DECRYPT, m_strDecrypted);
	DDX_Text(pDX, IDC_LIC_FILE_DIR, m_strLicFileName);
	DDX_Text(pDX, IDC_EDIT1, m_strEncryptedFile);
	DDX_Text(pDX, IDC_EDIT2, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAuthKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CAuthKeyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDB_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDB_ENCRYPT, OnEncrypt)
	ON_EN_KILLFOCUS(IDC_LIC_FILE_DIR, OnKillfocusLicFileDir)
	ON_BN_CLICKED(IDB_CREATE_LIC_FILE, OnCreateLicFile)
	ON_BN_CLICKED(IDC_READ_ENCRYPTED_FILE, OnReadEncryptedFile)
	ON_BN_CLICKED(IDB_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthKeyDlg message handlers

BOOL CAuthKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAuthKeyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAuthKeyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAuthKeyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
void CAuthKeyDlg::OnDecrypt() 
{
	UpdateData(TRUE);
	CString str;
	str = m_strEncrypted;
	int middle;
	short key, modify;

	middle = str.GetLength()/2;

	if (isdigit(str[middle])) {
		key = str[middle];
		str.SetAt(middle,'9' - str[middle] + '0');
	}
	else if (isalpha( str[middle] )) {
		key = str[middle];
		if (isupper( str[middle] ))
			str.SetAt(middle,'Z' - str[middle] + 'A');
		else
			str.SetAt(middle, 'z' - str[middle] + 'a');
	}
	else {
		return;
	}

	key = abs(key) + 1;
	for (int i=0; i<(int)strlen(str); i++) {
		if (i == middle) continue;
		modify = ((i*i)/key) + ((key*key)/(i+1)) + i*key + i + key;

		if ( isdigit( str[i] )) {
			modify = modify % 9;

			if ( (str[i]-'0') < modify )
				str.SetAt(i,str[i] + 9 - modify);
			else 
				str.SetAt(i,str[i] - modify);
		}
		else if ( isalpha( str[i] )) {
			modify = modify % 25;

			if (isupper( str[i] )) {
				if ( (str[i]-'A') < modify )
					str.SetAt(i,str[i] + 25 - modify);
				else 
					str.SetAt(i,str[i] - modify);
			}
			else {
				if ( (str[i]-'a') < modify )
					str.SetAt(i,str[i] + 25 - modify);
				else 
					str.SetAt(i,str[i]  - modify );
					}
		}
	}
	m_strDecrypted = str;
	UpdateData(FALSE);
}
*/
void CAuthKeyDlg::OnDecrypt() 
{
	UpdateData(TRUE);
	CString str;
	str = m_strEncrypted;

  CAPIDecryptFile((LPTSTR)(LPCTSTR)str, m_strDecrypted,NULL);
	UpdateData(FALSE);
}

/*
void CAuthKeyDlg::OnEncrypt() 
{
	int  middle;
	int  key, modify, newChar;

	UpdateData(TRUE);
	char *pString = new char[m_strSource.GetLength()+m_strVersion.GetLength()+1];
	CString str;
	str = m_strSource;

	int iPos = m_strVersion.Find('.');
	if (iPos != -1 ) {
		str += m_strVersion.Left(iPos);
		str += m_strVersion.Mid(iPos+1);
	}

	middle = strlen(str)/2;

	if (isdigit( str[middle] )) {
		str.SetAt(middle,'9' - str[middle] + '0');
		key = str[middle];
	}
	else if (isalpha( str[middle] )) {
		if (isupper( str[middle] ))
			str.SetAt(middle,'Z' - str[middle] + 'A');
		else
			str.SetAt(middle,'z' - str[middle] + 'a');
		key = str[middle];
	}
	else {		// non-alphanumerical is illegal
		return; 
	}

	key = abs(key) + 1;
	for (int i=0; i<(int)strlen(str); i++) {
		if (i == middle) continue;
		modify = ((i*i)/key) + ((key*key)/(i+1)) + i*key + i + key;

		if ( isdigit( str[i] )) {
			modify = modify % 9;

			newChar = str[i] - '0' + modify;
			if (newChar <= 9)
				str.SetAt(i, newChar + '0');
			else
				str.SetAt(i, newChar - 9 + '0');
		}
		else if ( isalpha( str[i] )) {
			modify = modify % 25;

			if (isupper( str[i] )) {
				newChar = str[i] - 'A' + modify;
				if (newChar <= 25)
					str.SetAt(i, newChar + 'A');
				else
					str.SetAt(i, newChar - 25 + 'A');	
			}
			else {
				newChar = str[i] - 'a' + modify;
				if (newChar <= 25)
					str.SetAt(i, newChar + 'a');
				else
					str.SetAt(i, newChar - 25 + 'a');	
			}
		}
	}
	m_strEncrypted = str;
	UpdateData(FALSE);
}
*/

void CAuthKeyDlg::OnEncrypt() 
{
	UpdateData(TRUE);
	char *pString = new char[m_strSource.GetLength()+m_strVersion.GetLength()+1];
	CString str;
	str = m_strSource;

	int iPos = m_strVersion.Find('.');
	if (iPos != -1 ) {
		str += m_strVersion.Left(iPos);
		str += m_strVersion.Mid(iPos+1);
	}

  CAPIEncrypt(str,m_strEncrypted,NULL);
	UpdateData(FALSE);
}

void CAuthKeyDlg::OnKillfocusLicFileDir() 
{
	UpdateData(TRUE);
	if( !m_strLicFileName.IsEmpty() ) {
		int iPos = m_strLicFileName.ReverseFind('\\');
		if ( iPos != -1 ) {
			CString str = m_strLicFileName.Left(iPos);
			if (-1 == _chdir( str ) ) {
				AfxMessageBox("Please enter a valid directory");
				GetDlgItem(IDC_LIC_FILE_DIR)->SetFocus();
			}
		}
	}
}

void CAuthKeyDlg::OnCreateLicFile() 
{
	UpdateData(TRUE);
	CFile f;
	int iAuth = f.Open(m_strLicFileName, CFile::modeCreate | CFile::modeWrite);
	if ( iAuth ) {
		OnEncrypt();
		f.Write(m_strEncrypted, m_strEncrypted.GetLength() );
	}
}


void CAuthKeyDlg::OnReadEncryptedFile() 
{
	UpdateData(TRUE);
	if ( !m_strEncryptedFile.IsEmpty() ) {
		CFile f;
		int iAuth = f.Open(m_strEncryptedFile, CFile::modeReadWrite);
		if ( iAuth ) {
			CString str;
			int iBytes = f.Read(str.GetBuffer(1000), 1000 );
			if ( iBytes ) {
				str.ReleaseBuffer(-1);
				str.SetAt(iBytes, '\0');
				m_strEncrypted = str;
				UpdateData(FALSE);
				OnDecrypt();
				m_strSource = m_strDecrypted;
				UpdateData(FALSE);
			}
		}
	}
}

void CAuthKeyDlg::OnBrowse() 
{
	CFileDialog dlg( TRUE,_T("LIC"),_T("*.LIC"),
	               OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	                 _T("License File (*.LIC)|*.LIC|"));
	if( dlg.DoModal()==IDOK )
	{
		m_strEncryptedFile  = dlg.GetPathName();
		UpdateData(FALSE);
	}
}
