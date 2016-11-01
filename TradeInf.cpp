// TradeInf.cpp: implementation of the CTradeInf class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TradeInf.h"

#define THIS_VERSION 0

IMPLEMENT_SERIAL(CTradeInf, CCmdTarget, VERSIONABLE_SCHEMA|THIS_VERSION)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTradeInf::CTradeInf()
{
	m_nVer	= THIS_VERSION;
}

CTradeInf::CTradeInf(CTradeInf& rSrcTrade)
{
	m_nVer	= rSrcTrade.m_nVer;

	m_strDate				= rSrcTrade.m_strDate;			
	m_strPrice			= rSrcTrade.m_strPrice;		
	m_strShares			= rSrcTrade.m_strShares;		
	m_strCommision	= rSrcTrade.m_strCommision;
	m_strAmount			= rSrcTrade.m_strAmount;		
	m_bBuy					= rSrcTrade.m_bBuy;

}

CTradeInf::~CTradeInf()
{

}

int CTradeInf::operator ==(const CTradeInf& rTrade)
{
	if (	m_strDate				== rTrade.m_strDate			&&
				m_strPrice			== rTrade.m_strPrice		&&
				m_strShares			== rTrade.m_strShares		&&
				m_strCommision	== rTrade.m_strCommision &&
				m_strAmount			== rTrade.m_strAmount			&&
				m_bBuy					== rTrade.m_bBuy
		 )
		 return TRUE;
	else 
		return FALSE;

}

void CTradeInf::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code

		ar << THIS_VERSION;

		ar	<< m_strDate
				<< m_strPrice
				<< m_strShares
				<< m_strCommision
				<< m_strAmount
				<< m_bBuy;
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
				AfxMessageBox((LPCTSTR)"Unable to read trade information.");
				return;
		}

	}
}

void CTradeInf::ReadVerZero(CArchive& ar)
{
	ar	>> m_strDate
			>> m_strPrice
			>> m_strShares
			>> m_strCommision
			>> m_strAmount
			>> m_bBuy;
}
