// StockMon.h : main header file for the ROWLIST application
#ifndef _StockMon_h_
#define _StockMon_h_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSMApp:
// See RowList.cpp for the implementation of this class
//
#include "AuthKey.h"

class CSMApp : public CWinApp
{
public:
	void ShowProgress ( LPCTSTR lpszFormat, ...);
	void ShowMsgText  ( LPCTSTR lpszFormat, ...);
	BOOL CheckLicKey(BOOL bMsg=FALSE);
	BOOL CheckSerNo(BOOL bMsg=FALSE);
	WCHAR *Encrypt(WCHAR *pString);
	WCHAR *Decrypt(WCHAR *pString);
	WCHAR *GetSerialNo();
	BOOL ChkForNine(CString szLic);
	void StripTags(LPWSTR pszBuffer);
	LPCTSTR GetBrowser();

	CSMApp();

  CView* m_pOldView;
  CView* m_pNewView;
  CView* SwitchView(CView* pNewView);
	CAuthKey m_AuthKey;
	CString m_strResDLL;
	CString m_strLicFileName;

	CString m_strCompanyName;
	CString m_strProductName;
	CString m_strProdNameAndVerNum;
	CString m_strVersionNum;
	CString m_strBrowser;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSMApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	BOOL ExtractResVerInfo();
};

inline CSMApp * THEAPP() {
	return (CSMApp *)AfxGetApp();
}


/////////////////////////////////////////////////////////////////////////////
#endif // _StockMon_h_