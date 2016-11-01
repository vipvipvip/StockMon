// ListVwEx.cpp : implementation of the CListViewEx class
//

#include "stdafx.h"
#include "ListVwEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewEx

IMPLEMENT_DYNCREATE(CListViewEx, CListView)

BEGIN_MESSAGE_MAP(CListViewEx, CListView)
	//{{AFX_MSG_MAP(CListViewEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
	ON_MESSAGE(LVM_SETTEXTCOLOR, OnSetTextColor)
	ON_MESSAGE(LVM_SETTEXTBKCOLOR, OnSetTextBkColor)
	ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewEx construction/destruction

CListViewEx::CListViewEx()
{
	m_bFullRowSel=FALSE;
	m_bClientWidthSel=TRUE;

	m_cxClient=0;
	m_cxStateImageOffset=0;

	m_clrText=::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTextBk=::GetSysColor(COLOR_WINDOW);
	m_clrBkgnd=::GetSysColor(COLOR_WINDOW);
}

CListViewEx::~CListViewEx()
{
}

BOOL CListViewEx::PreCreateWindow(CREATESTRUCT& cs)
{
	// default is report view and full row selection
	cs.style&=~LVS_TYPEMASK;
	cs.style|=LVS_REPORT | LVS_OWNERDRAWFIXED;
	m_bFullRowSel=TRUE;

	return(CListView::PreCreateWindow(cs));
}

BOOL CListViewEx::SetFullRowSel(BOOL bFullRowSel)
{
	// no painting during change
	LockWindowUpdate();

	m_bFullRowSel=bFullRowSel;

	BOOL bRet;

	if(m_bFullRowSel)
		bRet=ModifyStyle(0L,LVS_OWNERDRAWFIXED);
	else
		bRet=ModifyStyle(LVS_OWNERDRAWFIXED,0L);

	// repaint window if we are not changing view type
	if(bRet && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		Invalidate();

	// repaint changes
	UnlockWindowUpdate();

	return(bRet);
}

BOOL CListViewEx::GetFullRowSel()
{
	return(m_bFullRowSel);
}

/////////////////////////////////////////////////////////////////////////////
// CListViewEx drawing

// offsets for first and other columns
#define OFFSET_FIRST	2
#define OFFSET_OTHER	6

void CListViewEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CListCtrl& ListCtrl=GetListCtrl();
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags=ILD_TRANSPARENT;
	CImageList* pImageList;
	int nItem=lpDrawItemStruct->itemID;
	BOOL bFocus=(GetFocus()==this);
	COLORREF clrTextSave, clrBkSave;
	COLORREF clrImage=m_clrBkgnd;
	static WCHAR szBuff[MAX_PATH];
	memset(szBuff, 0, MAX_PATH);
	LPCTSTR pszText;

// get item data

	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvi.iItem=nItem;
	lvi.iSubItem=0;
	lvi.pszText=szBuff;
	lvi.cchTextMax=sizeof(szBuff);
	lvi.stateMask=0xFFFF;		// get all state flags
	ListCtrl.GetItem(&lvi);

	BOOL bSelected=(bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);

// set colors if item is selected

	CRect rcAllLabels;
	ListCtrl.GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);
	CRect rcLabel;
	ListCtrl.GetItemRect(nItem,rcLabel,LVIR_LABEL);
	rcAllLabels.left=rcLabel.left;
	if(m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right=m_cxClient;

	if(bSelected)
	{
		clrTextSave=pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave=pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		pDC->FillRect(rcAllLabels,&CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
	}
	else
		pDC->FillRect(rcAllLabels,&CBrush(m_clrTextBk));

// set color and mask for the icon

	if(lvi.state & LVIS_CUT)
	{
		clrImage=m_clrBkgnd;
		uiFlags|=ILD_BLEND50;
	}
	else if(bSelected)
	{
		clrImage=::GetSysColor(COLOR_HIGHLIGHT);
		uiFlags|=ILD_BLEND50;
	}

// draw state icon

	UINT nStateImageMask=lvi.state & LVIS_STATEIMAGEMASK;
	if(nStateImageMask)
	{
		int nImage=(nStateImageMask>>12)-1;
		pImageList=ListCtrl.GetImageList(LVSIL_STATE);
		if(pImageList)
			pImageList->Draw(pDC,nImage,CPoint(rcItem.left,rcItem.top),ILD_TRANSPARENT);
	}

// draw normal and overlay icon

	CRect rcIcon;
	ListCtrl.GetItemRect(nItem,rcIcon,LVIR_ICON);

	pImageList=ListCtrl.GetImageList(LVSIL_SMALL);
	if(pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if(rcItem.left<rcItem.right-1)
			ImageList_DrawEx(pImageList->m_hImageList,lvi.iImage,pDC->m_hDC,rcIcon.left,rcIcon.top,16,16,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
	}

// draw item label


	if(!bSelected) {
		if ( lvi.iImage == 1 ) {
			pDC->SetTextColor(RGB(255,0,0));
		}
		else if ( lvi.iImage == 2 ) {
			pDC->SetTextColor(RGB(0,128,0));
		}
		else if ( lvi.iImage == 3 ) {
			pDC->SetTextColor(RGB(0,0,255));
		}
		else if ( lvi.iImage == 4 ) {
			pDC->SetTextColor(RGB(0,0,128));
		}
		else {
			pDC->SetTextColor(RGB(0,0,0));
		}
	}


	ListCtrl.GetItemRect(nItem,rcItem,LVIR_LABEL);
	rcItem.right-=m_cxStateImageOffset;

	pszText=MakeShortString(pDC,szBuff,rcItem.right-rcItem.left,2*OFFSET_FIRST);

	rcLabel=rcItem;
	rcLabel.left+=OFFSET_FIRST;
	rcLabel.right-=OFFSET_FIRST;

	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);

// draw labels for extra columns

	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT | LVCF_WIDTH;

	for(int nColumn=1; ListCtrl.GetColumn(nColumn,&lvc); nColumn++)
	{
		rcItem.left=rcItem.right;
		rcItem.right+=lvc.cx;

		int nRetLen=ListCtrl.GetItemText(nItem,nColumn,szBuff,sizeof(szBuff));
		if(nRetLen==0) continue;

		pszText=MakeShortString(pDC,szBuff,rcItem.right-rcItem.left,2*OFFSET_OTHER);

		UINT nJustify=DT_LEFT;

		if(pszText==szBuff)
		{
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
			case LVCFMT_RIGHT:
				nJustify=DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify=DT_CENTER;
				break;
			default:
				break;
			}
		}

		rcLabel=rcItem;
		rcLabel.left+=OFFSET_OTHER;
		rcLabel.right-=OFFSET_OTHER;

		pDC->DrawText(pszText,-1,rcLabel,nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}

// draw focus rectangle if item has focus

	if(lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);

// set original colors if item was selected

	if(bSelected)
	{
		pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}

}

LPCTSTR CListViewEx::MakeShortString(CDC* pDC, WCHAR* lpszLong, int nColumnLen, int nOffset)
{
	static const WCHAR szThreeDots[]=_T("...");

	int nStringLen=lstrlen(lpszLong);

	if(nStringLen==0 || pDC->GetTextExtent(lpszLong,nStringLen).cx+nOffset<=nColumnLen)
		return(lpszLong);

	static WCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen=pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i=nStringLen-1; i>0; i--)
	{
		szShort[i]=0;
		if(pDC->GetTextExtent(szShort,i).cx+nOffset+nAddLen<=nColumnLen)
			break;
	}

	lstrcat(szShort,szThreeDots);

	return(szShort);
}

void CListViewEx::RepaintSelectedItems()
{
	CListCtrl& ListCtrl=GetListCtrl();
	CRect rcItem, rcLabel;

// invalidate focused item so it can repaint properly

	int nItem=ListCtrl.GetNextItem(-1,LVNI_FOCUSED);

	if(nItem!=-1)
	{
		ListCtrl.GetItemRect(nItem,rcItem,LVIR_BOUNDS);
		ListCtrl.GetItemRect(nItem,rcLabel,LVIR_LABEL);
		rcItem.left=rcLabel.left;

		InvalidateRect(rcItem,FALSE);
	}

// if selected items should not be preserved, invalidate them

	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem=ListCtrl.GetNextItem(-1,LVNI_SELECTED);
			nItem!=-1; nItem=ListCtrl.GetNextItem(nItem,LVNI_SELECTED))
		{
			ListCtrl.GetItemRect(nItem,rcItem,LVIR_BOUNDS);
			ListCtrl.GetItemRect(nItem,rcLabel,LVIR_LABEL);
			rcItem.left=rcLabel.left;

			InvalidateRect(rcItem,FALSE);
		}
	}

// update changes 

	UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CListViewEx diagnostics

#ifdef _DEBUG

void CListViewEx::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);

	dc << "m_bFullRowSel = " << (UINT)m_bFullRowSel;
	dc << "\n";
	dc << "m_cxStateImageOffset = " << m_cxStateImageOffset;
	dc << "\n";
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewEx message handlers

LRESULT CListViewEx::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
	if((int)wParam==LVSIL_STATE)
	{
		int cx, cy;

		if(::ImageList_GetIconSize((HIMAGELIST)lParam,&cx,&cy))
			m_cxStateImageOffset=cx;
		else
			m_cxStateImageOffset=0;
	}

	return(Default());
}

LRESULT CListViewEx::OnSetTextColor(WPARAM wParam, LPARAM lParam)
{
	m_clrText=(COLORREF)lParam;
	return(Default());
}

LRESULT CListViewEx::OnSetTextBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrTextBk=(COLORREF)lParam;
	return(Default());
}

LRESULT CListViewEx::OnSetBkColor(WPARAM wParam, LPARAM lParam)
{
	m_clrBkgnd=(COLORREF)lParam;
	return(Default());
}

void CListViewEx::OnSize(UINT nType, int cx, int cy) 
{
	m_cxClient=cx;
	CListView::OnSize(nType, cx, cy);
}

void CListViewEx::OnPaint() 
{
	// in full row select mode, we need to extend the clipping region
	// so we can paint a selection all the way to the right
//#if 0
	if(m_bClientWidthSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT && GetFullRowSel())
	{
		CRect rcAllLabels;
		GetListCtrl().GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

		if(rcAllLabels.right<m_cxClient)
		{
			// need to call BeginPaint (in CPaintDC c-tor)
			// to get correct clipping rect
			CPaintDC dc(this);

			CRect rcClip;
			dc.GetClipBox(rcClip);

			rcClip.left=min(rcAllLabels.right-1,rcClip.left);
			rcClip.right=m_cxClient;

			InvalidateRect(rcClip,FALSE);
			// EndPaint will be called in CPaintDC d-tor
		}
	}
//#endif
	CListView::OnPaint();
}

void CListViewEx::OnSetFocus(CWnd* pOldWnd) 
{
	CListView::OnSetFocus(pOldWnd);

	// check if we are getting focus from label edit box
	if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}

void CListViewEx::OnKillFocus(CWnd* pNewWnd) 
{
	CListView::OnKillFocus(pNewWnd);

	// check if we are losing focus to label edit box
	if(pNewWnd!=NULL && pNewWnd->GetParent()==this)
		return;

	// repaint items that should change appearance
	if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
		RepaintSelectedItems();
}


void CListViewEx::EraseList(BOOL bDelRows, BOOL bDelCols)
{
	CListCtrl& ctlList = (CListCtrl&) GetListCtrl();
	if ( bDelRows)
		ctlList.DeleteAllItems();
	if ( bDelCols )
		while(ctlList.DeleteColumn(0));

	UpdateWindow();
}

void CListViewEx::DisplayColumnHeadings(UINT nStringID)
{
	CString strHeadings;
	strHeadings.LoadString(nStringID);

  DisplayColumnHeadings(strHeadings);

/*
	CListCtrl& ctlList = (CListCtrl&) GetListCtrl();

	int nPos;
	int nCount = 0;

	EraseList(TRUE, TRUE);

	while ((nPos = strHeadings.Find(_T(","))) != -1){
		CString strItem;
		strItem = strHeadings.Left(nPos);
		AddColumn(strItem,nCount++);
		strItem = strHeadings.Mid(nPos + 1);
		strHeadings = strItem;
	}

	AddColumn(strHeadings,nCount);
	m_nColumns = nCount;
*/

}

void CListViewEx::DisplayColumnHeadings(CString& rCols)
{
	CString strHeadings;
	strHeadings=rCols;

	CListCtrl& ctlList = (CListCtrl&) GetListCtrl();

	int nPos;
	int nCount = 0;

	EraseList(TRUE, TRUE);

	while ((nPos = strHeadings.Find(_T(","))) != -1){
		CString strItem;
		strItem = strHeadings.Left(nPos);
		AddColumn(strItem,nCount++);
		strItem = strHeadings.Mid(nPos + 1);
		strHeadings = strItem;
	}

	AddColumn(strHeadings,nCount);
	m_nColumns = nCount;
}

BOOL CListViewEx::AddColumn(LPCTSTR strItem,int nItem,int nSubItem,int nMask,int nFmt)
{
	CListCtrl& ctlList = (CListCtrl&) GetListCtrl();
	LV_COLUMN lvc;
	lvc.mask = nMask;
	lvc.fmt = (nItem==0 || nItem==1) ? nFmt : LVCFMT_RIGHT;
	lvc.pszText = (LPTSTR) strItem;
	lvc.cx = -1;
	if ( m_strColWidths.IsEmpty() ) {
		lvc.cx = 3 * (ctlList.GetStringWidth(lvc.pszText) + 15);
	}
	else {
		int iPos=-1;
		CString str;
		str = m_strColWidths;
		for ( int i=0; i<=nItem; i++) {
			iPos = str.Find(_T(' '));
			if ( iPos != -1 ) {
				lvc.cx = _wtoi(str.Left(iPos));
				str = str.Mid(iPos+1);
			}
		}
	}

	if ( lvc.cx == -1) {
		lvc.cx = 3 * (ctlList.GetStringWidth(lvc.pszText) + 15);
	}

	if(nMask & LVCF_SUBITEM){
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}

	return ctlList.InsertColumn(nItem,&lvc);
}


BOOL CListViewEx::AddItem(int nItem,int nSubItem,LPCTSTR strItem, LPVOID pData)
{
	CListCtrl& ctlList = (CListCtrl&) GetListCtrl();
	LV_ITEM lvItem;
  lvItem.mask = pData==NULL ? LVIF_TEXT : LVIF_TEXT | LVIF_PARAM;
  lvItem.lParam = pData==NULL ? NULL : (LPARAM)pData;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR) strItem;

	if(nSubItem == 0)
		return ctlList.InsertItem(&lvItem);

	return ctlList.SetItem(&lvItem);
}

BOOL CListViewEx::AddItem(int nItem,int nSubItem,double strItem, LPVOID pData)
{
	CString str;
	str.Format(_T("%5.2f"), strItem);
	return AddItem(nItem, nSubItem, str,pData);
}

BOOL CListViewEx::AddItem(int nItem,int nSubItem,int strItem, LPVOID pData)
{
	CString str;
	str.Format(_T("%d"), strItem);
	return AddItem(nItem, nSubItem, str,pData);
}
