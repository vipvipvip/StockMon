// TechChrt.h: interface for the CTechChartOptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TECHCHRT_H__30390D83_CAE2_11D0_AFD1_00A024943E2B__INCLUDED_)
#define AFX_TECHCHRT_H__30390D83_CAE2_11D0_AFD1_00A024943E2B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTechChartOptions  
{
public:
	CTechChartOptions();
	virtual ~CTechChartOptions();

	int m_nVer;

	CString	m_strChartType;
	CString	m_strExpMA1;
	CString	m_strExpMA2;
	CString	m_strExpMA3;
	CString	m_strMACD;
	CString	m_strPriceROC;
	CString	m_strRSI;
	CString	m_strStoc;
	CString	m_strTime;
	int		m_iIndicators;
	BOOL	m_bLogPriceScale;

	virtual void Serialize(CArchive& ar);
	void ReadVerZero(CArchive& ar);
};

#endif // !defined(AFX_TECHCHRT_H__30390D83_CAE2_11D0_AFD1_00A024943E2B__INCLUDED_)
