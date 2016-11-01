// Request.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "Request.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequest

IMPLEMENT_DYNCREATE(CRequest, CCmdTarget)

CRequest::CRequest()
{
}

CRequest::~CRequest()
{
}


BEGIN_MESSAGE_MAP(CRequest, CCmdTarget)
	//{{AFX_MSG_MAP(CRequest)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRequest message handlers
