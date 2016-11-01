//{{AFX_INCLUDES()
#include "anigif.h"
//}}AFX_INCLUDES
#if !defined(AFX_GIFDLG_H__27B00367_0776_11D1_AFDD_00A024943E2B__INCLUDED_)
#define AFX_GIFDLG_H__27B00367_0776_11D1_AFDD_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GifDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGifDlg dialog

class CGifDlg : public CDialog
{
// Construction
public:
	CGifDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGifDlg)
	enum { IDD = IDD_GIF_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGifDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGifDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFDLG_H__27B00367_0776_11D1_AFDD_00A024943E2B__INCLUDED_)
