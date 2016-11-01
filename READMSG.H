// ReadMsg.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CReadMsg command target

class CReadMsg : public CCmdTarget
{
	DECLARE_DYNCREATE(CReadMsg)

// Attributes
public:
	CReadMsg();           // protected constructor used by dynamic creation
	virtual ~CReadMsg();
	CReadMsg(const CReadMsg& rMsg);

	CString m_strWebPageContent;
	CWinThread *m_pThread;
  CCmdTarget *m_pWWW;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadMsg)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReadMsg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
