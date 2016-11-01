// AuthKey.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuthKey

IMPLEMENT_DYNCREATE(CAuthKey, CCmdTarget)

CAuthKey::CAuthKey()
{
	memset(m_szVolName, 0, sizeof(m_szVolName));
	memset(m_szSysName, 0, sizeof(m_szSysName));

	m_dwVolNameSize=MAX_PATH-1;
	m_dwSysNameSize=MAX_PATH-1;

	GetVolumeInformation(	NULL,
												m_szVolName,  
												m_dwVolNameSize,
												&m_dwSerNo,
												&m_dwCompLength,
												&m_dwFSFlags,
												m_szSysName,
												m_dwSysNameSize);

}


CAuthKey::~CAuthKey()
{
}


BEGIN_MESSAGE_MAP(CAuthKey, CCmdTarget)
	//{{AFX_MSG_MAP(CAuthKey)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthKey message handlers
