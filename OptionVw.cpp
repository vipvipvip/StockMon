// OptionVw.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "stockmon.h"
#include "tradeinf.h"
#include "StkTickr.h"
#include "SMDoc.h"

#include "ListVwEx.h"	// base class for COptionVw
#include "ui.h"
#include "readmsg.h"
#include "SMView.h"

#include "OptionVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionVw

#define OPTIONS_VW_SUBHEADING "Settings\\Options View"

IMPLEMENT_DYNCREATE(COptionVw, CListViewEx)

COptionVw::COptionVw()
{
  m_pOwner=NULL;
  m_bFromFile = FALSE;

}

COptionVw::COptionVw(CSMView *pOwner)
{
  ASSERT(pOwner);
  m_pOwner = pOwner;
  m_bFromFile = FALSE;
}

COptionVw::~COptionVw()
{
}


BEGIN_MESSAGE_MAP(COptionVw, CListViewEx)
	//{{AFX_MSG_MAP(COptionVw)
	ON_COMMAND(ID_VIEW_VIEWQUOTES, OnViewquotes)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
  ON_MESSAGE (SHOW_OPTIONS_FROM_FILE, OnShowOptionsFromFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionVw drawing

void COptionVw::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// COptionVw diagnostics

#ifdef _DEBUG
void COptionVw::AssertValid() const
{
	CListViewEx::AssertValid();
}

void COptionVw::Dump(CDumpContext& dc) const
{
	CListViewEx::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COptionVw message handlers
afx_msg LRESULT COptionVw::OnShowOptionsFromFile(WPARAM wParam, LPARAM lParam)
{

  m_strTicker = (LPCTSTR)wParam;
  CString strFile((LPCTSTR)lParam);

  CStkTicker *p=NULL;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return 0;

  p = m_pOwner->InListCtrl(m_strTicker);
  if (!p) return 0;

  p->EmptyOptionData();

	CFile f;
	CListCtrl& ListCtrl=GetListCtrl();
	if ( f.Open(strFile, CFile::modeRead)) {
    m_bFromFile=TRUE;
    ParseOptions(f, p);
//    ShowOptions(p);
//	  ListCtrl.SortItems(CompareFunc, 3);
    f.Close();
  }
  return 0;
}


void COptionVw::OnViewquotes() 
{
	THEAPP()->SwitchView(m_pOwner);		
}

void COptionVw::OnDestroy() 
{
	CListCtrl& ListCtrl=GetListCtrl();
	int i=0;
	char szT[80];
	CString strValue;
	CString strTemp;
	LV_COLUMN lvc;
	lvc.mask = LVCF_WIDTH | LVCF_TEXT;
	lvc.pszText = szT;
	lvc.cchTextMax = sizeof(szT) - sizeof(char);
	while ( ListCtrl.GetColumn(i++, &lvc) ) {
		strTemp.Format("%d ", lvc.cx);
		strValue += strTemp;
	}
	if ( !strValue.IsEmpty() ) {
		THEAPP()->WriteProfileString( OPTIONS_VW_SUBHEADING, FRM_LHV_COLWIDTH, strValue );
	}

	CListViewEx::OnDestroy();
}

void COptionVw::ShowOptions( CStkTicker *p)
{

  if(!m_bFromFile) {
    CSMDoc *pDoc = (CSMDoc *)GetDocument();
	  CString strFileName		=	pDoc->m_strImageLocation;	
	  strFileName		+=  m_strTicker;
	  strFileName		+=  ".opt";

	  CFile f;
	  if ( f.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {
	  }
	  else {
		  CString str;
		  str.Format("Unable to open %s. Please set a valid directory in the View/Options dialog", strFileName); 
		  AfxMessageBox(str); 
	  }
  }

  CString strHeadings, sT;
  POSITION pos;
  CString key;
  for (int i=0; i<m_aStrikePrices.GetCount(); i++) {
    if (i==0) 
      sT.Format("Strike Price, Net Investment, %d ", i+1);
    else
      sT.Format(", %d ", i+1);
    strHeadings += sT;
  }
  DisplayColumnHeadings(strHeadings);


  pos = m_aStrikePrices.GetStartPosition();
  i=0;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  while (pos) {
    m_aStrikePrices.GetNextAssoc(pos,key, sT);
    AddItem(i, 0, sT);
  }
  return;
  

  
/*
  pos = p->m_OptionData.GetStartPosition();
  COptionData *pData=NULL;
  while (pos) {
    p->m_OptionData.GetNextAssoc(pos,key,(CObject *&)pData);
    UpdateRow(p->m_strSymbol, pData);
  }
*/
}

void COptionVw::UpdateRow(CString& rTicker, COptionData *p)
{
	if (!p)
		return;

	CListCtrl& ListCtrl=GetListCtrl();	
	int i;


	LV_FINDINFO lvf;
	lvf.flags = LVFI_STRING;
	lvf.psz		= (LPCTSTR)p->m_strOptTicker;
	i = ListCtrl.FindItem(&lvf);

  if ( i== -1) i=ListCtrl.GetItemCount();
	LV_ITEM lvi;
	lvi = p->m_lvi;
  lvi.iItem = p->m_lvi.iItem = (i==-1) ? 0 : i;
	lvi.iSubItem=0;
	lvi.pszText	=	(LPTSTR)(LPCTSTR)p->m_strOptTicker;
	lvi.lParam = (LPARAM)p;

	ListCtrl.DeleteItem(i);

//  if (p->m_fGain > 0 ) {
    ListCtrl.InsertItem(&lvi);
    AddItem(i, 1, rTicker);

    AddItem(i, 2, p->m_fLastSale);
    CString msg;
    msg.Format("%.2f", p->m_fGain);

    AddItem(i, 3, msg);
//  }
}


CString ExtractStrikePrice(CString& key)
{
  CString s(key);
  int iPos = s.Find(' ');
  s = s.Mid(iPos+1);

  iPos = s.Find(' ');
  s = s.Mid(iPos+1);

  iPos = s.Find(' ');
  s = s.Left(iPos);
  s.TrimRight();

  return s;
}

CString ExtractStrikeMonth(CString& key)
{
  //00 Jan 5 (QJC AA-E)
  
  CString s(key);
  int iPos = s.Find(' ');
  s = s.Mid(iPos+1);

  iPos = s.Find(' ');
  s = s.Left(iPos);
  s.TrimRight();

  return s;
}

CString ExtractItem(CString& s)
{
  CString sRet;

  int iPos = s.Find(',');
  sRet = s.Left(iPos);

  s = s.Mid(iPos+1);

  return sRet;
}


/*
void COptionVw::ParseOptions(CFile &f, CStkTicker *p)
{
  // Get the associated CStkTicker object
  CTime tCur = CTime::GetCurrentTime();
  CString strThisYr, strNextYr;

  strThisYr.Format("%d",tCur.GetYear());
  strThisYr = strThisYr.Right(2);
  strNextYr.Format("%d",tCur.GetYear()+1);
  strNextYr = strNextYr.Right(2);

  CArchive ac(&f, CArchive::load);
  CString s;
  ac.ReadString(s);
  if ( s.Find(p->m_strSymbol) == -1 ) return;

  // Extract the price
  int iPos = s.Find(',');
  s = s.Mid(iPos+1);
  iPos = s.Find(',');
  s = s.Left(iPos);
  float fPrice = (float)atof(s);


  // Skip next two lines
  ac.ReadString(s);
  ac.ReadString(s);

  // actual data starts
  CString sLast, strike, msg;
  COptionData *pOptionData=NULL;
  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;

  CString sMth,strStrike;

  // Empty the arrays
  m_aMonths.RemoveAll();
  m_aStrikePrices.RemoveAll();

//  for (int i=0;i<2; i++) {
//    ac.ReadString(s);
  while ( ac.ReadString(s) ) { 
    if (s.Left(2) != strThisYr ) continue;

    pOptionData = new COptionData;

    pOptionData->m_strOptTicker = ExtractItem(s);

    sMth = ExtractStrikeMonth(pOptionData->m_strOptTicker);
    m_aMonths.SetAt(sMth, sMth);

    pOptionData->m_fLastSale = (float)atof(ExtractItem(s));

    m_strNet = ExtractItem(s);

    pOptionData->m_fBid = (float)atof(pDoc->ConvertToDecimal(ExtractItem(s)));
    pOptionData->m_fAsk = (float)atof(pDoc->ConvertToDecimal(ExtractItem(s)));
    pOptionData->m_iVol = atoi(ExtractItem(s));
    pOptionData->m_iOpnInt = atoi(ExtractItem(s));

    strStrike = ExtractStrikePrice(pOptionData->m_strOptTicker);
    pOptionData->m_fStrike = (float)atof(pDoc->ConvertToDecimal(strStrike));
    m_aStrikePrices.SetAt(sMth, strStrike);

    if ( pOptionData->m_fStrike > fPrice ) {
//      delete pOptionData;
//      continue;
    }

    //msg.Format("%s,LS=%.3f, Bid=%.3f, Ask=%.3f, Vol=%d, OpnInt=%d, Strike=%.3f", m_strTicker,pOptionData->m_fLastSale,pOptionData->m_fBid,pOptionData->m_fAsk,pOptionData->m_iVol,pOptionData->m_iOpnInt, pOptionData->m_fStrike);
    //AfxMessageBox(msg);

    pOptionData->m_fGain = 100*((pOptionData->m_fStrike - ( fPrice - pOptionData->m_fLastSale ) ) / (fPrice - pOptionData->m_fLastSale ));
    pOptionData->m_lvi.pszText = (LPTSTR)(LPCTSTR)pOptionData->m_strOptTicker;
    pOptionData->m_strTicker = p->m_strSymbol;
    p->m_OptionData.SetAt(pOptionData->m_strOptTicker,pOptionData);
  }

}
*/

void COptionVw::ParseOptions(CFile &f, CStkTicker *p)
{
  if (!p) return;

	CListCtrl& ListCtrl=GetListCtrl();

  // Get the associated CStkTicker object
  CTime tCur = CTime::GetCurrentTime();
  CString strThisYr, strNextYr;

  strThisYr.Format("%d",tCur.GetYear());
  strThisYr = strThisYr.Right(2);
  strNextYr.Format("%d",tCur.GetYear()+1);
  strNextYr = strNextYr.Right(2);

  CSMDoc *pDoc = m_pOwner->GetDocument();
  if (!pDoc) return;
  CArchive ac(&f, CArchive::load);
  CString s;
  ac.ReadString(s);
  if ( s.Find(p->m_strSymbol) == -1 ) return;

  // Extract the price
  int iPos = s.Find(',');
  s = s.Mid(iPos+1);
  iPos = s.Find(',');
  s = s.Left(iPos);
  CString strHeadings;
  strHeadings = m_strTicker + " @ " + s + "," + CString("Bid,") + CString("Strike Price,") + CString("Net Investment");
  DisplayColumnHeadings(strHeadings,TRUE,TRUE);
  float fPrice = (float)atof(pDoc->ConvertToDecimal(s));


  // Skip next two lines
  ac.ReadString(s);
  ac.ReadString(s);

  // actual data starts
  m_aStrikePrices.RemoveAll();
  CString sLast, strike, msg;
  COptionData *pOptionData=NULL;

  CString sOptTicker,sMth,sT,val,strStrike,Temp, strNI;
  float fLast,fBid,fAsk,fStrikePrice,fgain;
  int iVol,iOpnInt;
  LV_COLUMN lvc;
  lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_RIGHT;

  int nCount = 4;
  int iRow=0;
  int iPriceRow=1;
  int iPriceCol=4;
  while ( ac.ReadString(s) ) { 
    if (s.Left(2) != strThisYr ) continue;

    sOptTicker = ExtractItem(s);
    sT = ExtractStrikeMonth(sOptTicker);
    strStrike = ExtractStrikePrice(sOptTicker);
    fStrikePrice = (float)atof(pDoc->ConvertToDecimal(strStrike));
//    if ( fStrikePrice > fPrice ) continue;
    
    if ( sT != sMth ) {
      sMth = sT;
      AddItem(iRow,0,"Calculations for the Month");
      AddItem(iRow++,1,CString("of ") + sT);
      AddItem(iRow++,0,"");

      if ( nCount == 3 ) {
        lvc.pszText = (LPTSTR)(LPCTSTR)strStrike;
	      lvc.cx = 3 * (ListCtrl.GetStringWidth(lvc.pszText) + 15);
        lvc.iSubItem = nCount;
        ListCtrl.InsertColumn(nCount++,&lvc);
        m_aStrikePrices.SetAt(strStrike,strStrike);
        AddItem(iPriceRow,iPriceCol++,strStrike);
      }
    }

    fLast = (float)atof(ExtractItem(s));

    m_strNet = ExtractItem(s);

    fBid = (float)atof(pDoc->ConvertToDecimal(ExtractItem(s)));
    if (fBid<=0) continue;
    fAsk = (float)atof(pDoc->ConvertToDecimal(ExtractItem(s)));
    iVol = atoi(ExtractItem(s));
    iOpnInt = atoi(ExtractItem(s));


    if(!m_aStrikePrices.Lookup(strStrike,val)) {
      m_aStrikePrices.SetAt(strStrike,strStrike);  
      lvc.pszText = (LPTSTR)(LPCTSTR)strStrike;
	    lvc.cx = 3 * (ListCtrl.GetStringWidth(lvc.pszText) + 15);
      lvc.iSubItem = nCount;
      ListCtrl.InsertColumn(nCount++,&lvc);
      AddItem(iPriceRow,iPriceCol++,strStrike);
    }

    AddItem(iRow,0,sOptTicker);
    Temp.Format("%.2f",fBid);
    AddItem(iRow,1,Temp);
    AddItem(iRow,2,strStrike);
    strNI.Format("%.2f", fPrice-fBid);
    AddItem(iRow++,3,strNI);

//    fgain = 100*((pOptionData->m_fStrike - ( fPrice - pOptionData->m_fLastSale ) ) / (fPrice - pOptionData->m_fLastSale ));
  }

  // Now calc gain
  CString SP,EP,INV;
	int nItem=0;
  float fSP,fEP, fINV;
  
	nItem	=	ListCtrl.GetNextItem(-1,LVNI_ALL);
	while (nItem != -1) {
    SP = ListCtrl.GetItemText(nItem,2);
    fSP = (float)atof(pDoc->ConvertToDecimal(SP));

    INV = ListCtrl.GetItemText(nItem,3);
    fINV = (float)atof(pDoc->ConvertToDecimal(INV));

    if ( SP.GetLength() > 0 && isdigit(SP[0])) {
      for (int k=4; k<nCount; k++) {
        EP = ListCtrl.GetItemText(1,k);
        fEP = (float)atof(pDoc->ConvertToDecimal(EP));
          fgain = 100*((__min(fSP,fEP)/fINV) - 1 );
          if ( fgain > 0 ) {
            Temp.Format("%.2f%s",fgain,"%");
            AddItem(nItem,k,Temp);
          }
        }
    }
	  nItem	=	ListCtrl.GetNextItem(nItem,LVNI_ALL);
  }


}

int COptionVw::GetNextValues(CString& rSP, CString& rExpPrice, int nStartRow)
{
	CListCtrl& ListCtrl=GetListCtrl();
	int nItem=0;

	nItem	=	ListCtrl.GetNextItem(nStartRow,LVNI_ALL);
	if ( nItem != -1) {
	}
	return nItem;
}

void COptionVw::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	m_strColWidths = THEAPP()->GetProfileString(OPTIONS_VW_SUBHEADING, FRM_LHV_COLWIDTH );
/*
  CString strHeadings;
  strHeadings = m_strTicker + "," + CString("Strike Price") + "," + CString("Net Investment");
  DisplayColumnHeadings(strHeadings,TRUE,TRUE);
*/
}


static int iColOrder[] = {0,0,0,0};
static CSMDoc *pDoc = NULL;

void COptionVw::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl& ListCtrl=GetListCtrl();
	iColOrder[pNMListView->iSubItem]==0 ? iColOrder[pNMListView->iSubItem]=1 : iColOrder[pNMListView->iSubItem]=0;

	pDoc = m_pOwner->GetDocument();
	ASSERT_VALID(pDoc);

	ListCtrl.SortItems(CompareFunc, (LPARAM)(pNMListView->iSubItem));
	*pResult = 0;

}

int CALLBACK COptionVw::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	COptionData *p1 = (COptionData *)lParam1;
	COptionData *p2 = (COptionData *)lParam2;
	double dRes;
	int iRes=0;
  CString msg;
  int iDiff=0, iDiff2=0;
	int i=0;
	if ( !p1 || !p2 )
		return iRes;

	switch( lParamSort)
	{
		case 0: // Option Ticker
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strOptTicker , p2->m_strOptTicker );
			}
			else {
				iRes = lstrcmpi(p2->m_strOptTicker , p1->m_strOptTicker );
			}
			break;

		case 1: // Stock Ticker
			if(iColOrder[lParamSort]) {
				iRes = lstrcmpi(p1->m_strTicker , p2->m_strTicker );
			}
			else {
				iRes = lstrcmpi(p2->m_strTicker , p1->m_strTicker );
			}
			break;

		case 2: // Last sale
			if(iColOrder[lParamSort]) {
				dRes = p1->m_fLastSale - p2->m_fLastSale;			
			}
			else {
				dRes = p2->m_fLastSale - p1->m_fLastSale;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;
			break;

		case 3: // Gain
			if(iColOrder[lParamSort]) {
				dRes = p1->m_fGain  - p2->m_fGain;			
			}
			else {
				dRes = p2->m_fGain - p1->m_fGain;			
			}
			iRes = dRes<0 ? -1 :dRes==0 ? 0 : 1;
			break;
	}
	return iRes;

}

