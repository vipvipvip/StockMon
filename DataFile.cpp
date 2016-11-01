// DataFile.cpp : implementation file
//

#include "stdafx.h"
#include "stockmon.h"
#include "SMDoc.h"
#include "DataFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataFile

IMPLEMENT_DYNCREATE(CDataFile, CCmdTarget)

CDataFile::CDataFile()
{
}

CDataFile::CDataFile ( CSMDoc *pDoc )
{
	m_pDoc = pDoc;
}

CDataFile::~CDataFile()
{
	m_pDoc = NULL;
}


BEGIN_MESSAGE_MAP(CDataFile, CCmdTarget)
	//{{AFX_MSG_MAP(CDataFile)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataFile message handlers

void CDataFile::GetFiles(CStringArray & rArray, CString& rSymbol)
{
  if ( !m_pDoc ) return;

	CString strTemp;
	WCHAR	strPath[ MAX_PATH ];
	if ( ::GetModuleFileName( NULL, strPath, MAX_PATH ))
	{
		CString str = strPath;
		int iPos = str.ReverseFind('\\');
		if ( -1 != iPos ) {
			strTemp = str.Left(iPos+1);
		}
	}

  int iPos = m_pDoc->m_strImageLocation.Find('\\');
  if ( -1 != iPos ) {
	  strTemp += m_pDoc->m_strImageLocation.Mid(iPos+1);
  }
  else {
    strTemp += m_pDoc->m_strImageLocation;
  }

	CreateDirectory(strTemp, NULL);
	if (strTemp.Right(1) != '\\')
    strTemp += "\\";

  CString Path(strTemp);

	strTemp += rSymbol;
	strTemp += "_*.*";

	WIN32_FIND_DATA w;
	HANDLE h = FindFirstFile(strTemp, &w);
	BOOL bContinue = ( h !=INVALID_HANDLE_VALUE) ? TRUE : FALSE;

	while ( bContinue ) 
	{
    CString s;
    s = Path;
    s += w.cFileName;
		rArray.Add(s);
		bContinue = FindNextFile(h, &w);
	}

}
