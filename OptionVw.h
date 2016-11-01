#if !defined(AFX_OPTIONVW_H__7198FAA4_DBF4_11D3_8DC5_DE5D745C2115__INCLUDED_)
#define AFX_OPTIONVW_H__7198FAA4_DBF4_11D3_8DC5_DE5D745C2115__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionVw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptionVw view
#define ID_OPTION_VIEW 6

#define SHOW_OPTIONS		        WM_APP+6000
#define SHOW_OPTIONS_FROM_FILE  SHOW_OPTIONS+1

class CSMView;


class COptionVw : public CListViewEx
{
protected:
  CString m_strWebPage;
  CString m_strTicker;
  // from the data file

  float m_fLastSale;
  float m_fBid;
  float m_fAsk;
  int   m_iVol;
  int   m_iOpnInt;
  float m_fStrike;
  CString m_strNet;

  BOOL m_bFromFile;

	DECLARE_DYNCREATE(COptionVw)

// Attributes
public:
	CSMView				*m_pOwner;
  CMapStringToString m_aMonths,m_aStrikePrices;

// Operations
public:
	int GetNextValues (CString& rSP, CString& rExpPrice,int nStartRow=-1);
	void UpdateRow(CString& rTicker, COptionData *pData);
	COptionVw();
	COptionVw(CSMView *pOwner);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionVw)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COptionVw();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionVw)
	afx_msg void OnViewquotes();
	afx_msg void OnDestroy();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT  OnShowOptionsFromFile(WPARAM wParam, LPARAM lParam);

  void ShowOptions(CStkTicker *p);
	void ParseOptions(CFile &f, CStkTicker *p);

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
														LPARAM lParamSort);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONVW_H__7198FAA4_DBF4_11D3_8DC5_DE5D745C2115__INCLUDED_)
