/****************************** MFC Includes *******************************/
#include "StdAfx.h"

/*************************** C-Runtime Includes ****************************/
/* None */

/************************** Application Includes ***************************/
/* None */

/*************************** Directory Includes ****************************/
#include "Persist.h"
#include "StockMon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(UPersistentFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(UPersistentFrame, CFrameWnd)
    //{{AFX_MSG_MAP(UPersistentFrame)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// UPersistentFrame message handlers


void UPersistentFrame::OnDestroy()
{
	CString text, temp;
	CWnd*   pBar;
	BOOL    bIconic, bMaximized;
	WINDOWPLACEMENT wndpl;

	wndpl.length = sizeof(WINDOWPLACEMENT);
	
	GetWindowPlacement(&wndpl);

	if (wndpl.showCmd == SW_SHOWNORMAL) 
	{
		bIconic = FALSE;
		bMaximized = FALSE;
	}
	else if (wndpl.showCmd == SW_SHOWMAXIMIZED)
	{
		bIconic = FALSE;
		bMaximized = TRUE;
	} 
	else if (wndpl.showCmd == SW_SHOWMINIMIZED) 
	{
		bIconic = TRUE;
		if (wndpl.flags)
		{
		  bMaximized = TRUE;
		}
		else
		{
		  bMaximized = FALSE;
		}
	}
	wsprintf(text.GetBuffer(20), _T("%04d %04d %04d %04d"),
					wndpl.rcNormalPosition.left, wndpl.rcNormalPosition.top,
					wndpl.rcNormalPosition.right, wndpl.rcNormalPosition.bottom);

	text.ReleaseBuffer();
	THEAPP()->WriteProfileString( FRM_SUBKEY_HEADING, FRM_LHV_RECT, text );
	THEAPP()->WriteProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_ICON, bIconic );
	THEAPP()->WriteProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_MAX, bMaximized );

	if (pBar = GetDescendantWindow(AFX_IDW_TOOLBAR))
	{
	  THEAPP()->WriteProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_TOOL,
//			(pBar->GetStyle() & WS_VISIBLE) != 0L);
			1);
	}

	if (pBar = GetDescendantWindow(AFX_IDW_STATUS_BAR))
	{
	  THEAPP()->WriteProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_STATUS,
			(pBar->GetStyle() & WS_VISIBLE) != 0L);
	}

	CFrameWnd::OnDestroy();
}


void UPersistentFrame::ActivateFrame(int nCmdShow)
{
	CWnd*           pBar;
	CString         text;
	BOOL            bIconic, bMaximized, bTool, bStatus;
	UINT            flags;
	WINDOWPLACEMENT wndpl;
	CRect           rect;

	text = THEAPP()->GetProfileString( FRM_SUBKEY_HEADING, FRM_LHV_RECT );

	if (!text.IsEmpty())
	{
		rect.left = _ttoi(text);
		rect.top = _ttoi((LPCTSTR)text + 5);
		rect.right = _ttoi((LPCTSTR)text + 10);
		rect.bottom = _ttoi((LPCTSTR)text + 15);
	}
	else
	{
		CClientDC	dc( (CWnd*)this );

		LONG	nWidth  = dc.GetDeviceCaps( HORZRES );
		LONG	nHeight = dc.GetDeviceCaps( VERTRES );

		LONG	nLeft = nWidth  / 6;
		LONG	nTop  = nHeight / 6;

		rect.SetRect( nLeft, nTop, nWidth - nLeft, nHeight - nTop );
	}

	bIconic		= THEAPP()->GetProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_ICON, 0 );
	bMaximized	= THEAPP()->GetProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_MAX, 0 );

	if (bIconic) 
	{
		// Following line was commented out so that the application
		// opens and becomes visible even when it was iconic when
		// last closed.  This is keeping in mind that the taskbar at the
		// bottom on NT4.0 may not be visible is so set by the user.
	  //nCmdShow = SW_SHOWMINNOACTIVE;
	  if (bMaximized) 
	  {
		 flags = WPF_RESTORETOMAXIMIZED;
	  }
	}
	else
	{
	  if (bMaximized)
	  {
		 nCmdShow = SW_SHOWMAXIMIZED;
		 flags = WPF_RESTORETOMAXIMIZED;
	  }
	  else
	  {
		 nCmdShow = SW_NORMAL;
		 flags = 0;
	  }
	}

	wndpl.length = sizeof(WINDOWPLACEMENT);
	wndpl.showCmd = nCmdShow;
	wndpl.flags = flags;
	wndpl.ptMinPosition = CPoint(0, 0);
	wndpl.ptMaxPosition = CPoint(-::GetSystemMetrics(SM_CXBORDER),
										  -::GetSystemMetrics(SM_CYBORDER));
	wndpl.rcNormalPosition = rect;

	bTool = THEAPP()->GetProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_TOOL, 1 );

	if (pBar = GetDescendantWindow(AFX_IDW_TOOLBAR))
	{
		 pBar->ShowWindow(bTool);
	}

	bStatus = THEAPP()->GetProfileInt( FRM_SUBKEY_HEADING, FRM_LHV_STATUS, 1 );

	if (pBar = GetDescendantWindow(AFX_IDW_STATUS_BAR))
	{
		 pBar->ShowWindow(bStatus);
	}

	// sets window's position and iconized/maximized status
	SetWindowPlacement(&wndpl);

	CDocument *pDoc = (CDocument *)(((CFrameWnd *)AfxGetMainWnd())->GetActiveDocument());
	if (!pDoc)
		return;

	CString str = THEAPP()->m_strProdNameAndVerNum;

	CString strTitle = pDoc->GetTitle();
	str += _T(" - ");
	str += strTitle;
	SetWindowText(str);

	CFrameWnd::ActivateFrame(nCmdShow);
}
