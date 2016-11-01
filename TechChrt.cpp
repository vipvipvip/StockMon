// TechChrt.cpp: implementation of the CTechChartOptions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stockmon.h"
#include "TechChrt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define THIS_VERSION 0
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTechChartOptions::CTechChartOptions()
{
	m_nVer = THIS_VERSION;

	m_strChartType  = "Bar";
	m_strExpMA1			= "50 day";
	m_strExpMA2			= "100 day";
	m_strExpMA3			= "200 day";
	m_strMACD				= "12-25-9";
	m_strPriceROC		= "16-8";
	m_strRSI				= "14";
	m_strStoc				= "15-1-5-5";
	m_strTime				= "6 months";
	m_iIndicators		= 2;
	m_bLogPriceScale= 0;
}

CTechChartOptions::~CTechChartOptions()
{

}

void CTechChartOptions::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code

		ar << THIS_VERSION;

		ar	<< m_strChartType  
				<< m_strExpMA1			
				<< m_strExpMA2			
				<< m_strExpMA3			
				<< m_strMACD				
				<< m_strPriceROC		
				<< m_strRSI				
				<< m_strStoc				
				<< m_strTime				
				<< m_iIndicators		
				<< m_bLogPriceScale;

	}
	else
	{	// loading code
		ar >> m_nVer;

		switch ( m_nVer ) {
			case -1:
			case 0:
				ReadVerZero(ar);
				break;
			default:
				AfxMessageBox((LPCTSTR)"Unable to read techincal chart information.");
				return;
		}

	}
}

void CTechChartOptions::ReadVerZero(CArchive& ar)
{
	ar	>> m_strChartType  
			>> m_strExpMA1		
			>> m_strExpMA2		
			>> m_strExpMA3		
			>> m_strMACD			
			>> m_strPriceROC	
			>> m_strRSI				
			>> m_strStoc			
			>> m_strTime			
			>> m_iIndicators	
			>> m_bLogPriceScale;
}
