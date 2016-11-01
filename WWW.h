#if !defined(AFX_WWW_H__1B9B7971_0810_11D1_AFDD_00A024943E2B__INCLUDED_)
#define AFX_WWW_H__1B9B7971_0810_11D1_AFDD_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WWW.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWWW command target

class CWWW : public CCmdTarget
{
	DECLARE_DYNCREATE(CWWW)

	CWWW();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void GetNews();
	virtual ~CWWW();
  void Release();
  void AddRef(int iCount=0);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWWW)
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetALLQuotes();
	void GetQuote(CString& rStr);
	void UpdateSelected();


	// Generated message map functions
	//{{AFX_MSG(CWWW)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CString m_strAddr;
  CSMDoc * m_pDoc;
  CSMView * m_pView;

  int m_nRef;

};

inline void CWWW::Release()
{
  if ( m_nRef ) {
    --m_nRef;
  }
  if ( m_nRef == 0 ) {
    delete this;
  }
}

inline void CWWW::AddRef(int iCount/*=0*/)
{
  if (iCount == 0 ) 
    m_nRef++;
  else 
    m_nRef += iCount;
}

/////////////////////////////////////////////////////////////////////////////
// CWWWYahoo command target

class CWWWYahoo : public CWWW
{
	DECLARE_DYNCREATE(CWWWYahoo)

	CWWWYahoo();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void GetNews(CString strTicker);
	void GetNews();
  CWWWYahoo (CSMView *pView);
	virtual ~CWWWYahoo();
	void UpdateSelected();
	void HandleQuote(CString& rTicker, CString& rWebPage);
	void HandleIndex(CString& rSymbol, CString& rWebPage);
	void GetQuote(CString& rStr);
	void GetALLQuotes();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWWWYahoo)
	//}}AFX_VIRTUAL

// Implementation
protected:
  void DisplayMultiQuote(CString& rSymbol, CString& rWebPage);
  void DisplaySingleQuote(CString& rSymbol, CString& rWebPage);

	// Generated message map functions
	//{{AFX_MSG(CWWWYahoo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WWW_H__1B9B7971_0810_11D1_AFDD_00A024943E2B__INCLUDED_)
