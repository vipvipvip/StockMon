#if !defined(AFX_PHONEBKDLG_H__E530BB24_0158_11D2_9AC7_00A024943E2B__INCLUDED_)
#define AFX_PHONEBKDLG_H__E530BB24_0158_11D2_9AC7_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PhoneBkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PhoneBkDlg dialog

class PhoneBkDlg : public CDialog
{
// Construction
public:
	PhoneBkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PhoneBkDlg)
	enum { IDD = IDD_PHONEBOOK };
	CListBox	m_pLBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PhoneBkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PhoneBkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONEBKDLG_H__E530BB24_0158_11D2_9AC7_00A024943E2B__INCLUDED_)
