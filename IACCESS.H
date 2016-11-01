// IAccess.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CIAccess command target
class CSMDoc;
class CSMView;

class CIAccess : public CCmdTarget
{
	DECLARE_DYNCREATE(CIAccess)

// Attributes
public:
	void ConfigureSession();
	wchar_t * GetWebPageContent();
	int GetWebPageBytes();
	void FreeWebPageContent();
	BOOL CloseSession();
	BOOL CloseConnection();
	BOOL Read();
	BOOL ReadImage();
	BOOL OpenConnection();
	BOOL OpenSession(LPCTSTR lpProxy=NULL);
	BOOL Init(CString& rWebAddress, CString& rstrTicker, DWORD dwThreadID, CSMDoc *pDoc, CSMView *pView);

// Operations
public:
	CIAccess();           // protected constructor used by dynamic creation
	virtual ~CIAccess();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIAccess)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSMView * m_pView;
	BOOL DoConnect();
	DWORD m_dwDataReceiveTimeOut;
	DWORD m_dwDataSendTimeOut;
	DWORD m_dwDataConnectTimeOut;
	CString m_strWebAddress;
	CString m_strTicker;
	CString m_strProxy;
	wchar_t *m_pszWebPageContent;	
	CHttpFile *m_pHTTPFile;
	INTERNET_PORT m_nPort;
	CString m_strObject;
	CString m_strServer;
	DWORD m_dwServiceType;
	CHttpConnection *m_pHTTPConnection;
	CInternetSession *m_pInetSession;
	DWORD m_dwThreadID;
	int m_nWebBytesRecd;
	CSMDoc *m_pDoc;

	void GetTicker();

	// Generated message map functions
	//{{AFX_MSG(CIAccess)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
