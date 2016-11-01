// MainFrm.h : interface of the CMainFrame class
//
#include "Persist.h"

class CMainFrame : public UPersistentFrame
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CReBar      m_wndReBar;
	CToolBar    m_wndToolBar;
	CStringArray m_astrFavoriteURLs;
	CComboBoxEx m_wndAddress;
// Operations
public:
	int BuildFavoritesMenu(LPCTSTR pszPath, int nStartPos, CMenu* pMenu);
  CString MakeURL(CString strTicker);
	CString MakeTDURL(CString strTicker);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNewAddress();
	afx_msg void OnNewAddressEnter();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
  afx_msg LRESULT  OnShowMsgText(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
