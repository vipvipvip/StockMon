#if !defined(AFX_DATAFILE_H__CB6F75F1_A5EE_11D0_AFCD_00A024943E2B__INCLUDED_)
#define AFX_DATAFILE_H__CB6F75F1_A5EE_11D0_AFCD_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DataFile.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDataFile command target
class CSMDoc;

class CDataFile : public CCmdTarget
{
	DECLARE_DYNCREATE(CDataFile)

	CDataFile();           // protected constructor used by dynamic creation

public:
	CDataFile ( CSMDoc *pDoc );
	virtual ~CDataFile();

// Attributes
public:
	CSMDoc *m_pDoc;

// Operations
public:
	void GetFiles(CStringArray& rArray, CString& rSymbol);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataFile)
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataFile)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAFILE_H__CB6F75F1_A5EE_11D0_AFCD_00A024943E2B__INCLUDED_)
