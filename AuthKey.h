// AuthKey.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CAuthKey command target

class CAuthKey : public CCmdTarget
{
	DECLARE_DYNCREATE(CAuthKey)

	CAuthKey();           // protected constructor used by dynamic creation
	virtual ~CAuthKey();

// Attributes
public:
	WCHAR	m_szVolName[MAX_PATH];
	DWORD m_dwVolNameSize;
	DWORD m_dwSerNo;
	DWORD m_dwCompLength;
	DWORD m_dwFSFlags;
	WCHAR	m_szSysName[MAX_PATH];
	DWORD m_dwSysNameSize;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthKey)
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAuthKey)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
