// ReadMsg.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "ReadMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadMsg

IMPLEMENT_DYNCREATE(CReadMsg, CCmdTarget)

CReadMsg::CReadMsg()
{
	m_pThread = NULL;
  m_pWWW = NULL;
}

CReadMsg::CReadMsg(const CReadMsg& rMsg)
{
	m_strWebPageContent = rMsg.m_strWebPageContent;
	m_pThread = rMsg.m_pThread;
  m_pWWW = rMsg.m_pWWW;
}

CReadMsg::~CReadMsg()
{
}


BEGIN_MESSAGE_MAP(CReadMsg, CCmdTarget)
	//{{AFX_MSG_MAP(CReadMsg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadMsg message handlers
