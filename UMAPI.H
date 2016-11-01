// UMapi.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMapi thread
#include "mapi.h"
class CMapi : public CWinThread
{
	DECLARE_DYNCREATE(CMapi)
protected:
	HINSTANCE m_hInstMail;      // handle to MAPI32.DLL

	// Attributes
public:
	CMapi();           // constructor used by dynamic creation
	
// Operations
public:
	virtual ~CMapi();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapi)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int SendMail();

	// Generated message map functions
	//{{AFX_MSG(CMapi)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
