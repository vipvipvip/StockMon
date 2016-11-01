// Request.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRequest command target

class CRequest : public CCmdTarget
{
	DECLARE_DYNCREATE(CRequest)

	CRequest();           // protected constructor used by dynamic creation
	virtual ~CRequest();

// Attributes
public:
	CString m_strWebPageAddress;
	CString m_strIdentifier;
  CCmdTarget *m_pWWW;

	// This is mainly for charts
	CString m_strAltImageLocation;

// Operations
public:
	void Init( LPCTSTR lpWebAddress, LPCTSTR lpIden, CCmdTarget *pWWW=NULL, LPCTSTR lpAltWebAddress=NULL);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRequest)
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CRequest)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
inline void CRequest::Init( LPCTSTR lpWebAddress, LPCTSTR lpIden, CCmdTarget *pWWW, LPCTSTR lpAltWebAddress)
{
	m_strWebPageAddress = lpWebAddress;
	m_strIdentifier = lpIden;
	if(lpAltWebAddress)
		m_strAltImageLocation = lpAltWebAddress;
  m_pWWW = pWWW;
}