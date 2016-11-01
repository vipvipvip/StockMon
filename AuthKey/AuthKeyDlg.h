// AuthKeyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuthKeyDlg dialog

class CAuthKeyDlg : public CDialog
{
// Construction
public:
	CAuthKeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAuthKeyDlg)
	enum { IDD = IDD_AUTHKEY_DIALOG };
	CString	m_strEncrypted;
	CString	m_strSource;
	CString	m_strDecrypted;
	CString	m_strLicFileName;
	CString	m_strEncryptedFile;
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAuthKeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnKillfocusLicFileDir();
	afx_msg void OnCreateLicFile();
	afx_msg void OnReadEncryptedFile();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
