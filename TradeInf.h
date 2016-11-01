// TradeInf.h: interface for the CTradeInf class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRADEINF_H__11A38DB2_9C83_11D0_AFCC_00A024943E2B__INCLUDED_)
#define AFX_TRADEINF_H__11A38DB2_9C83_11D0_AFCC_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTradeInf : public CCmdTarget  
{
public:
	DECLARE_SERIAL(CTradeInf)

	CTradeInf();
	CTradeInf(CTradeInf& rSrcTrade);
	virtual ~CTradeInf();

	int m_nVer;

	CString	m_strDate;
	CString	m_strPrice;
	CString	m_strShares;
	CString	m_strCommision;
	CString	m_strAmount;
	int		m_bBuy;
	CString m_strGain;

	int operator ==(const CTradeInf& rTrade);

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTradeInf)
	public:
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

protected:
	void ReadVerZero(CArchive& ar);

};

#endif // !defined(AFX_TRADEINF_H__11A38DB2_9C83_11D0_AFCC_00A024943E2B__INCLUDED_)


