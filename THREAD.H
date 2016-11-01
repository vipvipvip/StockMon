// Thread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CInternetThread thread
class CSMDoc;
class CIAccess;

class CInternetThread : public CWinThread
{
	DECLARE_DYNCREATE(CInternetThread)
protected:
	long m_nPendingReq;
	CString m_strTicker;
	CString m_strWebAddress;
	// This is mainly for charts
	CString m_strAltImageLocation;

	CInternetThread();           // protected constructor used by dynamic creation
	HWND m_hOwner;
	CSMDoc *m_pDoc;
	HANDLE m_hWorkEvent;
	CIAccess m_aWWW;	

// Attributes
public:
	wchar_t * GetWebPageContent();
	void FreeWebPageContent();
	void SetWebAddress(CString& rWebAddress);
	BOOL m_bDone;
	void Init(HWND hOwner, CSMDoc *pDoc, HANDLE hWorkEvent, CSMView *pView);

	// Operations
public:
	~CInternetThread();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSMView * m_pView;
	void GetTicker();
	void WriteImage();

	// Generated message map functions
	//{{AFX_MSG(CInternetThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
