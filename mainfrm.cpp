// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "StockMon.h"
#include "MainFrm.h"
#include "SMDoc.h"
#include "ListVwEx.h"	// base class for CSMView
#include "SMView.h"
#include "BrowserVw.h"
#include "StkTickr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, UPersistentFrame)

BEGIN_MESSAGE_MAP(CMainFrame, UPersistentFrame)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_CBN_SELENDOK(AFX_IDW_TOOLBAR + 1,OnNewAddress)
	ON_COMMAND(IDOK, OnNewAddressEnter)
	//}}AFX_MSG_MAP
  ON_MESSAGE (SHOWMSGTEXT, OnShowMsgText)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
	ID_MESSAGE_INDICATOR

};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (UPersistentFrame::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndReBar.Create(this))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

 	// create a combo box for the address bar
	if (!m_wndAddress.Create(CBS_DROPDOWN | CBS_SORT | WS_CHILD, CRect(0, 0, 200, 120), this, AFX_IDW_TOOLBAR + 1))
	{
		TRACE0("Failed to create combobox\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndReBar.AddBar(&m_wndAddress, _T("Address"), NULL, RBBS_FIXEDBMP | RBBS_BREAK);
  m_wndReBar.ShowWindow (0);

// set up Favorites menu
	WCHAR           sz[MAX_PATH];
	WCHAR           szPath[MAX_PATH];
	HKEY            hKey;
	DWORD           dwSize;
	CMenu*          pMenu;

	// first get rid of bogus submenu items.
	pMenu = GetMenu()->GetSubMenu(5);
	while(pMenu->DeleteMenu(0, MF_BYPOSITION));

	// find out from the registry where the favorites are located.
	if(RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders"), &hKey) != ERROR_SUCCESS)
	{
		TRACE0("Favorites folder not found\n");
		return 0;
	}
	dwSize = sizeof(sz);
	RegQueryValueEx(hKey, _T("Favorites"), NULL, NULL, (LPBYTE)sz, &dwSize);
	ExpandEnvironmentStrings(sz, szPath, MAX_PATH);
	RegCloseKey(hKey);

	BuildFavoritesMenu(szPath, 0, pMenu);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style&=~FWS_ADDTOTITLE;

	return UPersistentFrame::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	UPersistentFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	UPersistentFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

afx_msg LRESULT  CMainFrame::OnShowMsgText(WPARAM wParam, LPARAM lParam)
{
  CString str((LPCTSTR)lParam);
  m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_MESSAGE_INDICATOR), str);
  return 0;
}


CString CMainFrame::MakeURL(CString strTicker)
{
 CSMDoc *pDoc = (CSMDoc *)GetActiveView()->GetDocument();

 if (pDoc->m_bWebSite == CSMDoc::TD ) return MakeTDURL(strTicker);

  CString strURL = "http://chart.finance.yahoo.com/z?s=";
  strURL += strTicker;
  strURL += pDoc->m_strChartString;

  CBrowserVw *pVw = (CBrowserVw*)GetActiveView();

  switch (pVw->m_iRange) {
		case CSMView::YAHOO_1_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=1d" :  "&time=1dy&freq=5mi";
      break;

    case CSMView::YAHOO_5_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5d" : "&time=5dy&freq=15mi";
      break;

    case CSMView::YAHOO_10_DAY:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5d" : "&time=10dy&freq=1hr";
      break;

    case CSMView::YAHOO_3_MONTH:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=3m" : "&time=3mo&freq=1dy";
      break;

    case CSMView::YAHOO_6_MONTH:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=6m" : "&time=6mo&freq=1dy";
      break;
    case CSMView::YAHOO_1_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=1y&p=e20,e30,m200,m65" : "&time=1yr&freq=1wk";
			break;

    case CSMView::YAHOO_2_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=2y&p=e40,e60,m200" : "&time=2yr&freq=1wk";
      break;

    case CSMView::YAHOO_5_YEAR:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=5y&p=m65,m200" : "&time=5yr&freq=1wk";
      break;

    case CSMView::YAHOO_MAX:
			strURL += pDoc->m_bWebSite == CSMDoc::YAHOO ? "&t=my&p=e160,e240,m200" : "&time=10yr&freq=1wk";
      break;
  }
	strURL += "&l=on&z=l&q=";
	strURL += "c";
	strURL += "&a=m26-12-9,ss,vm&c=";
	strURL += pDoc->m_strCompareWithTicker;
	return strURL;
}

CString CMainFrame::MakeTDURL(CString strTicker)
{
  CSMDoc *pDoc = (CSMDoc *)GetActiveView()->GetDocument();
  CString strURL = "http://stockcharts.com/c-sc/sc?s=";
  strURL += strTicker;


  CBrowserVw *pVw = (CBrowserVw*)GetActiveView();
  strURL += pDoc->m_strChartString;
  return strURL;

}

void CMainFrame::OnNewAddress()
{
	// gets called when an item in the Address combo box is selected
	// just navigate to the newly selected location.
	CString URL;

	m_wndAddress.GetLBText(m_wndAddress.GetCurSel(), URL);
  if ( URL.IsEmpty() ) return;

  // See if it is a ticker symbol
  CSMDoc *pDoc = (CSMDoc *)GetActiveView()->GetDocument();

  if (pDoc) {
	  if(pDoc->m_bMakeSymbolsUpperCase) URL.MakeUpper();
	  CStkTicker *p = NULL;

	  for ( int i=0; i<pDoc->m_TickerArray.GetSize(); i++) {
		  p = (CStkTicker *) pDoc->m_TickerArray[i];
		  if ( p->m_strSymbol == URL ) {
        URL = MakeURL(URL);
        break;
      }
	  }
  }
	((CBrowserVw*)GetActiveView())->Navigate2(URL, 0, NULL);
}


void CMainFrame::OnNewAddressEnter()
{
	// gets called when an item is entered manually into the edit box portion
	// of the Address combo box.
	// navigate to the newly selected location and also add this address to the
	// list of addresses in the combo box.
	CString str;

	m_wndAddress.GetEditCtrl()->GetWindowText(str);
  if (str.IsEmpty() ) return;

  CSMView *pVw = (CSMView *)THEAPP()->m_pOldView;
  if (pVw) {
    if ( pVw->InListCtrl(str) ) {
      OnNewAddress();
      return;
    }
  }

  if (str.GetLength() <= 5 || str.Find('.') > 0) {
    str = MakeURL(str);
  }

	((CBrowserVw*)GetActiveView())->Navigate2(str, 0, NULL);

	COMBOBOXEXITEM item;

	item.mask = CBEIF_TEXT;
	item.iItem = -1;
	item.pszText = (LPTSTR)(LPCTSTR)str;
	m_wndAddress.InsertItem(&item);
}

int CMainFrame::BuildFavoritesMenu(LPCTSTR pszPath, int nStartPos, CMenu* pMenu)
{
	CString         strPath(pszPath);
	CString         strPath2;
	CString         str;
	WIN32_FIND_DATA wfd;
	HANDLE          h;
	int             nPos;
	int             nEndPos;
	int             nNewEndPos;
	int             nLastDir;
	WCHAR           buf[INTERNET_MAX_PATH_LENGTH];
	CStringArray    astrFavorites;
	CStringArray    astrDirs;
	CMenu*          pSubMenu;

	// make sure there's a trailing backslash
	if(strPath[strPath.GetLength() - 1] != _T('\\'))
		strPath += _T('\\');
	strPath2 = strPath;
	strPath += "*.*";

	// now scan the directory, first for .URL files and then for subdirectories
	// that may also contain .URL files
	h = FindFirstFile(strPath, &wfd);
	if(h != INVALID_HANDLE_VALUE)
	{
		nEndPos = nStartPos;
		do
		{
			if((wfd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY|FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM))==0)
			{
				str = wfd.cFileName;
				if(str.Right(4) == _T(".url"))
				{
					// an .URL file is formatted just like an .INI file, so we can
					// use GetPrivateProfileString() to get the information we want
					::GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),
											  _T(""), buf, INTERNET_MAX_PATH_LENGTH,
											  strPath2 + str);
					str = str.Left(str.GetLength() - 4);

					// scan through the array and perform an insertion sort
					// to make sure the menu ends up in alphabetic order
					for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
					{
						if(str.CompareNoCase(astrFavorites[nPos]) < 0)
							break;
					}
					astrFavorites.InsertAt(nPos, str);
					m_astrFavoriteURLs.InsertAt(nPos, buf);
					++nEndPos;
				}
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);
		// Now add these items to the menu
		for(nPos = nStartPos ; nPos < nEndPos ; ++nPos)
		{
			pMenu->AppendMenu(MF_STRING | MF_ENABLED, 0xe00 + nPos, astrFavorites[nPos]);
		}


		// now that we've got all the .URL files, check the subdirectories for more
		nLastDir = 0;
		h = FindFirstFile(strPath, &wfd);
		ASSERT(h != INVALID_HANDLE_VALUE);
		do
		{
			if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// ignore the current and parent directory entries
				if(lstrcmp(wfd.cFileName, _T(".")) == 0 || lstrcmp(wfd.cFileName, _T("..")) == 0)
					continue;

				for(nPos = 0 ; nPos < nLastDir ; ++nPos)
				{
					if(astrDirs[nPos].CompareNoCase(wfd.cFileName) > 0)
						break;
				}
				pSubMenu = new CMenu;
				pSubMenu->CreatePopupMenu();

				// call this function recursively.
				nNewEndPos = BuildFavoritesMenu(strPath2 + wfd.cFileName, nEndPos, pSubMenu);
				if(nNewEndPos != nEndPos)
				{
					// only intert a submenu if there are in fact .URL files in the subdirectory
					nEndPos = nNewEndPos;
					pMenu->InsertMenu(nPos, MF_BYPOSITION | MF_POPUP | MF_STRING, (UINT)pSubMenu->m_hMenu, wfd.cFileName);
					pSubMenu->Detach();
					astrDirs.InsertAt(nPos, wfd.cFileName);
					++nLastDir;
				}
				delete pSubMenu;
			}
		} while(FindNextFile(h, &wfd));
		FindClose(h);
	}
	return nEndPos;
}

