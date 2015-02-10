// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Tra.h"

#include "TraDoc.h"
#include "LeftView.h"
#include "OptDlg.h"
#include "FindDlg.h"
#include "Mcmd.h"
#include "Mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CTLCOLOR_REFLECT()
	ON_COMMAND(IDM_FIND_MCMD, OnFindMcmd)
	ON_COMMAND(IDM_FIND_NXTMCMD, OnFindNxtmcmd)
	ON_COMMAND(IDM_PERFORM_ALL, OnPerformAll)
	ON_COMMAND(IDM_PERFORM_SEL, OnPerformSel)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_RDBLCLK, OnRdblclk)
	ON_COMMAND(IDM_SHOW_PARMCMD, OnShowParmcmd)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_COMMAND(IDM_TOG_MCMD, OnTogMcmd)
	ON_COMMAND(IDM_TOG_BKMK, OnTogBkmk)
	ON_COMMAND(IDM_CLR_BKMK, OnClrBkmk)
	ON_COMMAND(IDM_TOGO_BKMK, OnTogoBkmk)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_iFromithMcmd = 0;
	m_imgLst = new CImageList;

	m_imgLst->Create(8, 8, ILC_MASK, 0, 3);

	HICON bOpen, bClose, bBkMK;
	bClose = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICN_CLOSE));
	bOpen = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICN_OPEN));
	bBkMK = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICN_BKMK));
	
	m_imgLst->Add(bClose);
	m_imgLst->Add(bOpen);
	m_imgLst->Add(bBkMK);

	m_bShowBKMK = false;
	
}

CLeftView::~CLeftView()
{

}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs |TVS_HASBUTTONS 
	cs.style |= TVS_HASLINES |TVS_LINESATROOT |TVS_SHOWSELALWAYS |TVS_HASBUTTONS ;
	

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CTraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	//this->MessageBox("haha");
	// TODO: add draw code for native data here
	/*CTreeCtrl ctl;
	ctl.Attach(this->m_hWnd);
	HTREEITEM hItem = ctl.GetFirstVisibleItem();
	CMcmd *pCurMcmd = NULL;
	while(hItem)
	{
		if(pDoc->m_MHreeItem_To_Mcmd.Lookup(hItem, (void*&) pCurMcmd))
		{

			pDC->SetTextColor(pCurMcmd->m_TxtColor);

		}
	}*/
}


void CLeftView::OnInitialUpdate()
{
	
	CTraDoc* pDoc = GetDocument();
    CTreeCtrl &CTC = this->GetTreeCtrl();
	CTC.SetBkColor(pDoc->m_OptColor->m_LPCOLORClr);
	CTC.SetTextColor(pDoc->m_OptColor->m_LPCOLORClr);
	CTC.SetImageList(m_imgLst, LVSIL_NORMAL);

	//CTC.SendMessage(TVM_SETBKCOLOR, 0, (LPARAM)RGB(255,255,255));

	//CTC.SetInsertMarkColor(RGB(255,0,0));
	//CTreeView::OnInitialUpdate();
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTraDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTraDoc)));
	return (CTraDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//AfxMessageBox("Expending");
	*pResult = 0;
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (!this->m_bAddItemFinished) return;
	//TRACE("OnSelChanged called");
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;
	CMcmd * pMcmdSelected = NULL;
	CTraDoc *pDoc = GetDocument();
	pDoc->m_MHreeItem_To_Mcmd.Lookup(hTreeItem, (void *&) pMcmdSelected);
	if(pMcmdSelected)
	{
		pDoc->OnSelectChanged(pMcmdSelected);
	}
	*pResult = 0;
}

HBRUSH CLeftView::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;
}

void CLeftView::OnFindMcmd() 
{
	// TODO: Add your command handler code here

	if (m_strText.GetLength() <= 0)

		return;

		CTraDoc * pDoc = GetDocument();
		for(long i=m_iFromithMcmd; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
		{
			CMcmd *pCmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
			if(pCmd->mcmd.Find(m_strText) >= 0)
			{
				HTREEITEM hTreeItem;
				if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCmd, (void *&)hTreeItem))
				{
					pDoc->m_iFocusMcmd = i+1;
					m_iFromithMcmd = i+1;
					CTreeCtrl &CTC = this->GetTreeCtrl();
					CTC.Select(hTreeItem, TVGN_CARET);
					return;
				}
			}
		}
	    m_iFromithMcmd = 0;
	    MessageBox("\""+m_strText+"\" not found!");

	return;	
}


void CLeftView::OnFindNxtmcmd() 
{
	// TODO: Add your command handler code here
	if (m_strText.GetLength() <= 0)
		return;

		CTraDoc * pDoc = GetDocument();
		for(long i=m_iFromithMcmd; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
		{
			CMcmd *pCmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
			if(pCmd->mcmd.Find(m_strText) >= 0)
			{
				HTREEITEM hTreeItem;
				if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCmd, (void *&)hTreeItem))
				{
					pDoc->m_iFocusMcmd = i+1;
					m_iFromithMcmd = i+1;
					CTreeCtrl &CTC = this->GetTreeCtrl();
					CTC.Select(hTreeItem, TVGN_CARET);
					return;
				}
			}
		}
		m_iFromithMcmd = 0;
	    AfxMessageBox("\""+m_strText+"\" not found!", MB_OK|MB_ICONINFORMATION);	
}


void CLeftView::OnPerformAll() 
{
	// TODO: Add your command handler code here

	this->DoPerformance(true);

}



void CLeftView::SortMcmds(CObArray &ary)
{
	CMcmd *pMaxMcmd = NULL, *pCurMcmd, *pPreMcmd;
	CObArray McmdStack, res;
	CUIntArray ParentIdx;
	long MaxSec = -1, CurSec = 0, ParIdx = -1,i;
	for(i=0 ;i < ary.GetSize(); i++)
	{
		pCurMcmd = (CMcmd*) ary[i];
        CurSec = pCurMcmd->end_time_stmp - pCurMcmd->beg_time_stmp;
		if(CurSec > MaxSec)
		{
			pMaxMcmd = pCurMcmd;
			MaxSec = CurSec;
			ParIdx = i;
		}
	}
	while(pMaxMcmd)
	{
		ParentIdx.Add(ParIdx);
		//mark it as processed.
		pMaxMcmd->ID = -pMaxMcmd->ID;
		McmdStack.Add(pMaxMcmd);
		while(McmdStack.GetSize()>0)
		{
			pPreMcmd = (CMcmd*)McmdStack[McmdStack.GetSize()-1];
			McmdStack.RemoveAt(McmdStack.GetSize()-1);
			res.Add(pPreMcmd);
			ParIdx = ParentIdx[ParentIdx.GetSize()-1];
			ParentIdx.RemoveAt(ParentIdx.GetSize()-1);
			pMaxMcmd = NULL;
			for(i = ParIdx +1 ;i< ary.GetSize();  i++)
			{
				pCurMcmd = (CMcmd *) ary[i];
				if((pMaxMcmd == NULL ||
					pMaxMcmd->end_time_stmp - pMaxMcmd->beg_time_stmp <
					pCurMcmd->end_time_stmp - pCurMcmd->beg_time_stmp)
					&& pCurMcmd->Parent == pPreMcmd)
				{
					pMaxMcmd = pCurMcmd;
					ParIdx = i;
				}
				// pCurMcmd may be a grandson or not an descendent of pPreMcmd.
				if(pCurMcmd->level != pPreMcmd->level+1)
				{
					if(pCurMcmd->level <= pPreMcmd->level) // not a descendent.
						break;
					else
					    continue;  // grandson.
				}
			}
			if(pMaxMcmd)
			{
			    McmdStack.Add(pMaxMcmd);
			    pMaxMcmd->ID = -pMaxMcmd->ID;
				ParentIdx.Add(ParIdx);
			}
		}

		MaxSec = 0;
		pMaxMcmd = NULL;
	    for(i=0 ;i < ary.GetSize(); i++)
		{
	    	pCurMcmd = (CMcmd*) ary[i];
			if(pCurMcmd->ID < 0)
				continue;
            CurSec = pCurMcmd->end_time_stmp - pCurMcmd->beg_time_stmp;
	    	if(CurSec > MaxSec || pMaxMcmd == NULL)
			{
	     		pMaxMcmd = pCurMcmd;
				MaxSec = CurSec;
				ParIdx = i;
			}
		}
	}
	for(i = 0 ;i < res.GetSize(); i++)
	{
		pCurMcmd = (CMcmd*) res[i];
		pCurMcmd->ID = - pCurMcmd->ID;
		//pCurMcmd->ID = - pCurMcmd->ID > 0 ? -pCurMcmd->ID :  pCurMcmd->ID;;
		ASSERT(pCurMcmd->ID > 0);
		TRACE("TimeStamp :%ld\n", pCurMcmd->end_time_stmp - pCurMcmd->beg_time_stmp);
	}
	ary.RemoveAll();
	ary.Append(res);
}

void CLeftView::DoPerformance(boolean doAll)
{
	CTraDoc *pDoc= this->GetDocument();
	CObArray cpMcmds;

	if(doAll)
	{
	    //cpMcmds.Copy(pDoc->m_ObjArrMcmds);
		POSITION pos = pDoc->m_MHreeItem_To_Mcmd.GetStartPosition();
		CMcmd *pCur = NULL;
		HTREEITEM hItem;
		/*while(pos)
		{
			pDoc->m_MHreeItem_To_Mcmd.GetNextAssoc(pos, (void*&)hItem, (void*&)pCur);
			cpMcmds.Add(pCur);
		}*/
		CTreeCtrl &CTC = this->GetTreeCtrl();
		for (long i = 0 ; i< pDoc->m_ObjArrMcmds.GetSize() ; i++)
		{
			pCur = (CMcmd*) pDoc->m_ObjArrMcmds[i];
			if(pDoc->m_MpMcmd_To_hHreeItem.Lookup((void*)pCur, (void*&)hItem))
			     cpMcmds.Add(pCur);
		}
	}
	else
	{
		if(pDoc->m_ObjArrMcmds.GetSize() <=0) return;
		ASSERT(pDoc->m_iFocusMcmd > 0 && pDoc->m_iFocusMcmd <= pDoc->m_ObjArrMcmds.GetSize());
		CMcmd *pSelectedMcmd =(CMcmd*) pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd -1 ];
		CMcmd *pChildMcmd = NULL;
		cpMcmds.Add(pSelectedMcmd);
		for(long j = pDoc->m_iFocusMcmd; j < pDoc->m_ObjArrMcmds.GetSize(); j++)
		{
			pChildMcmd = (CMcmd *)pDoc->m_ObjArrMcmds[j];
			if(pChildMcmd->Parent == pSelectedMcmd || pChildMcmd->level > pSelectedMcmd->level)
			{
				cpMcmds.Add(pChildMcmd);
			}
			else if(pChildMcmd->level <= pSelectedMcmd->level)
				break;
		}

	}

	if(cpMcmds.GetSize() <=0)
		return;
	this->SortMcmds(cpMcmds);

	this->m_bAddItemFinished = false;
    this->ShowWindow(SW_HIDE);
	CMcmd *pFst , *pLst;
	pFst =  (CMcmd*)cpMcmds[0];
	pLst = (CMcmd*)cpMcmds[cpMcmds.GetSize()-1];
	long tot_period_trace = pLst->end_time_stmp - pFst->beg_time_stmp;
	double thresh_hld = pDoc->m_OptMoca->m_dThreshVal;
	long totlinenum = pDoc->m_OptMoca->m_iMaxLineNum;

	pDoc->m_MpMcmd_To_hHreeItem.RemoveAll();
    pDoc->m_MHreeItem_To_Mcmd.RemoveAll();
	CTreeCtrl &CTC = this->GetTreeCtrl();
	CTC.DeleteAllItems();


	pDoc->m_MpMcmd_To_hHreeItem.InitHashTable(cpMcmds.GetSize() + (int)(cpMcmds.GetSize()*0.2));
	pDoc->m_MHreeItem_To_Mcmd.InitHashTable(cpMcmds.GetSize() + (int)(cpMcmds.GetSize()*0.2));
	CMcmd *pMcmd;
	HTREEITEM hTreeItem, hParTreeItem;
	if (cpMcmds.GetSize() > 0)
	{
		pMcmd = (CMcmd *) cpMcmds[0];
		pDoc->m_iFocusMcmd = pMcmd->ID;
	}

	for (long i=0; i< cpMcmds.GetSize(); i++)
	{
		pMcmd = (CMcmd *) cpMcmds[i];
		
		pMcmd->OverTimeWeight(tot_period_trace, thresh_hld, totlinenum);
				 if(pMcmd->Parent == NULL)
				 {
				     hTreeItem=CTC.InsertItem(pMcmd->m_Subfix + pMcmd->mcmd, TVI_ROOT, TVI_LAST);
					 pDoc->m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					 pDoc->m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
				 else
				 {
					 hParTreeItem = NULL;
					 pDoc->m_MpMcmd_To_hHreeItem.Lookup(pMcmd->Parent, (void *&)hParTreeItem);
					 
					 if(hParTreeItem)
					 {
					     hTreeItem=CTC.InsertItem(pMcmd->m_Subfix + pMcmd->mcmd, hParTreeItem, TVI_LAST);
					 }
					 else
					 {
						 hTreeItem=CTC.InsertItem(pMcmd->m_Subfix + pMcmd->mcmd, TVI_ROOT, TVI_LAST);
					 }

					pDoc->m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					pDoc->m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
	}
	this->m_bAddItemFinished = true;
	this->ShowWindow(SW_SHOW);

}

void CLeftView::OnPerformSel() 
{
	// TODO: Add your command handler code here
	DoPerformance(false);
}

void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hTreeItem , hItem;
	//hTreeItem = pNMTreeView->itemNew.hItem;

	CTreeCtrl &CTC = this->GetTreeCtrl();
	CPoint point;  
    TVHITTESTINFO HitTestInfo;  
    GetCursorPos(&point);
    CTC.ScreenToClient(&point);  
    HitTestInfo.pt = point;
    //hTreeItem = CTC.HitTest(&HitTestInfo);
	hTreeItem = CTC.GetSelectedItem();

	CTraDoc *pDoc = GetDocument();
	CMcmd* pCurMcmd = NULL, *pTopMcmd = NULL;
	int imgID = 0;

	if(pDoc->m_MHreeItem_To_Mcmd.Lookup(hTreeItem, (void*&)pCurMcmd))
	{
		
		int IDSelected = pCurMcmd->ID;
		pTopMcmd = pCurMcmd->Parent;
		if(pTopMcmd != NULL)
		{
            // If pTopMcmd is not in the tree, create it.
			bool TopCreated = false;
			this->m_bAddItemFinished = false;
			
			if(!pDoc->m_MpMcmd_To_hHreeItem.Lookup(pTopMcmd, (void*&)hItem))
			{
				hTreeItem = NULL;
				int PreID = pTopMcmd->ID;
				CMcmd *pPreMcmd = NULL;
				for(long j = PreID-1; j>= 0; j++)
				{
					pPreMcmd = (CMcmd *)pDoc->m_ObjArrMcmds[j];
					if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pPreMcmd, (void*&)hItem))
					{
						hItem=CTC.InsertItem(pTopMcmd->mcmd,
							                 pTopMcmd->m_bBookMarked? 2 : 0,
											 pTopMcmd->m_bBookMarked? 2 : 0,
							                 NULL,
											 hItem);
                        pDoc->m_MHreeItem_To_Mcmd.SetAt(hItem, pTopMcmd);
						pDoc->m_MpMcmd_To_hHreeItem.SetAt(pTopMcmd, hItem);
						TopCreated = true;
						break;
					}
				}
			}
			else
			{
				//Parent exists, don't need to draw it out, return
			    if(hTreeItem)
			    	CTC.SelectItem(hTreeItem);
				this->m_bAddItemFinished = true;
				return;
			}

			if(!TopCreated)
			{
				hItem=CTC.InsertItem(pTopMcmd->mcmd,
					                 pTopMcmd->m_bBookMarked? 2 : 0,
					                 pTopMcmd->m_bBookMarked? 2 : 0
					                 TVI_ROOT, TVI_FIRST);
                pDoc->m_MHreeItem_To_Mcmd.SetAt(hItem, pTopMcmd);
				pDoc->m_MpMcmd_To_hHreeItem.SetAt(pTopMcmd, hItem);
			}


			//delete decedents
		    for(long i= pTopMcmd->ID; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
			{
				pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[i];
				if(pCurMcmd->level <= pTopMcmd->level)
					break;
				if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCurMcmd, (void*&)hItem))
					CTC.DeleteItem(hItem);
			}
			//reinsert all decedents
		    for(int i= pTopMcmd->ID; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
			{
				pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[i];
				if(pCurMcmd->level <= pTopMcmd->level)
					break;
				if(pCurMcmd->Parent)
				{
					if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCurMcmd->Parent, (void*&)hItem))
					{
						 int imgID = 0;
						 if (pCurMcmd->m_bBookMarked)
						 {
							 imgID = 2;
						 }
						 else if (pCurMcmd->ID <= pDoc->m_ObjArrMcmds.GetSize())
						 {
							 CMcmd *pNxt = (CMcmd*)pDoc->m_ObjArrMcmds[pCurMcmd->ID];
							 if (pNxt->Parent == pCurMcmd)
							 {
								 imgID = 0;
							 }
							 else
								 imgID = 1;
						 }
						 else
							 imgID = 0;

				         hItem = CTC.InsertItem(pCurMcmd->mcmd, hItem);
						 CTC.SetItemImage(hItem, imgID, imgID);
						 pDoc->m_MHreeItem_To_Mcmd.SetAt(hItem, pCurMcmd);
						 pDoc->m_MpMcmd_To_hHreeItem.SetAt(pCurMcmd, hItem);
						 if(pCurMcmd->ID == IDSelected)
						 {
							 hTreeItem = hItem;
						 }
					}
					else 
					{
						//This should never happen.
						//::AfxMessageBox("This should never happen.");
					}
				}				
			}
			if(hTreeItem)
				CTC.SelectItem(hTreeItem);
			this->m_bAddItemFinished = true;
		}
		else
		{
			::AfxMessageBox("No Parent command!", MB_OK|MB_ICONINFORMATION);
		}
		
	}
	*pResult = 0;
}

void CLeftView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CTraDoc *pDoc = this->GetDocument();
	CTreeCtrl &CTC = this->GetTreeCtrl();

	
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	GetClientRect(&rcClient);


	CBitmap bitmap;
    bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
    memDC.SelectObject( &bitmap );
	

	CRgn rgn;
    rgn.CreateRectRgnIndirect( &rcClip );
    memDC.SelectClipRgn(&rgn);
    rgn.DeleteObject();

	memDC.SelectObject(*CTC.GetFont());
	memDC.SetBkMode(TRANSPARENT);
	
	//memDC.SelectStockObject(BLACK_BRUSH);
	//memDC.SetROP2(DM_COPY);
	
	
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	if(m_hWnd)
	{
	    HTREEITEM hItem = CTC.GetFirstVisibleItem();
    	CMcmd *pCurMcmd = NULL;
    	CString iTxt="";
		LOGFONT lf;
		CFont *pFnt = NULL, fb;

		//fb.CreatePointFont(50,"Arial");
		//CTC.SetFont(&fb);

		
		pFnt = CTC.GetFont();
		
		pFnt->GetLogFont(&lf);
		lf.lfWeight = lf.lfWeight + 700;
		fb.CreateFontIndirect(&lf);
	
    	while(hItem)
		{
	    	if(pDoc->m_MHreeItem_To_Mcmd.Lookup(hItem, (void*&) pCurMcmd))
			{
		    	iTxt = CTC.GetItemText(hItem);
		    	CTC.GetItemRect(hItem, &rcClient, true);
				
		    	memDC.SetTextColor(pCurMcmd->m_TxtColor);
				if(pCurMcmd->m_Bold)
				{
					memDC.SelectObject(&fb);
					CTC.SetItemState(hItem,TVIS_BOLD,TVIS_BOLD);
				    memDC.TextOut(rcClient.left+1, rcClient.top+2, iTxt);
				}
				else
				{
					memDC.SelectObject(*pFnt);
		    	    memDC.TextOut(rcClient.left+1, rcClient.top+2, iTxt);
				}

			}
	    	hItem = CTC.GetNextVisibleItem(hItem);
		}
	}

	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC,
    rcClip.left, rcClip.top, SRCCOPY );
	// Do not call CTreeView::OnPaint() for painting messages
}


void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{

	CPoint point;  
	GetCursorPos(&point);
	CMenu mn, *pMenu;
	mn.LoadMenu(IDR_MAINFRAME);
	pMenu=mn.GetSubMenu(1);
    pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x,point.y,this);
    
	*pResult = 0;
}

void CLeftView::OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//::AfxMessageBox("OK?");
	//NM_TREEVIEW* pNMTreeView;
	
	*pResult = 0;
}

void CLeftView::OnShowParmcmd() 
{
	// TODO: Add your command handler code here
	LRESULT res;
	OnDblclk(NULL, &res);
}

void CLeftView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void CLeftView::OnTogMcmd() 
{
	// TODO: Add your command handler code here
	static int expandflg = 1;

	HTREEITEM hItem = NULL;
	CTraDoc *pDoc = this->GetDocument();
	CMcmd *pMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[0];
	int cnt = pDoc->m_ObjArrMcmds.GetSize();
	int i = 0;
	pDoc->m_MpMcmd_To_hHreeItem.Lookup(pMcmd, (void*&) hItem);
	CTreeCtrl &CTC = this->GetTreeCtrl();
    
	CTC.ShowWindow(SW_HIDE);
	while(hItem)
	{

		if(expandflg)
		{
            CTC.Expand(hItem, TVE_EXPAND );
			hItem = CTC.GetNextVisibleItem(hItem);
		}
		else
		{
			CTC.Expand(hItem, TVE_COLLAPSE );

			i++;

			if ( i == cnt )
				hItem = NULL;
			else
			{
			    pMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[i];
                pDoc->m_MpMcmd_To_hHreeItem.Lookup(pMcmd, (void*&) hItem);
			}
			//hItem = CTC.GetNextItem(hItem,TVGN_NEXT);

		}
       	//
		
		//CTC.GetNextItem(
	}

	CTC.ShowWindow(SW_SHOW);
	expandflg = !expandflg;
}


void CLeftView::OnTogBkmk() 
{
	// TODO: Add your command handler code here
	HTREEITEM hTreeItem;
	//hTreeItem = pNMTreeView->itemNew.hItem;

	CTreeCtrl &CTC = this->GetTreeCtrl();
	CPoint point;  
    TVHITTESTINFO HitTestInfo;  
    GetCursorPos(&point);
    CTC.ScreenToClient(&point);  
    HitTestInfo.pt = point;
    //hTreeItem = CTC.HitTest(&HitTestInfo);
	hTreeItem = CTC.GetSelectedItem();

	CTraDoc *pDoc = GetDocument();
	CMcmd* pCurMcmd = NULL, *pTopMcmd = NULL;

	if(pDoc->m_MHreeItem_To_Mcmd.Lookup(hTreeItem, (void*&)pCurMcmd))
	{
		if (pCurMcmd)
		{
			pCurMcmd->m_bBookMarked = !pCurMcmd->m_bBookMarked;
		}
		if (pCurMcmd->m_bBookMarked)
		{
		    CTC.SetItemImage(hTreeItem, 2, 2);
		}
		else if (pCurMcmd->ID <= pDoc->m_ObjArrMcmds.GetSize())
		{
			CMcmd *pNxt = (CMcmd*)pDoc->m_ObjArrMcmds[pCurMcmd->ID];
			if (pNxt->Parent == pCurMcmd)
			{
                CTC.SetItemImage(hTreeItem, 0, 0);
			}
			else
			{
                CTC.SetItemImage(hTreeItem, 1, 1);
			}
		}
		else
			CTC.SetItemImage(hTreeItem, 1, 1);
	}	
}

void CLeftView::OnClrBkmk() 
{
	// TODO: Add your command handler code here



	CTraDoc *pDoc = GetDocument();
	CMcmd* pCurMcmd = NULL, *pTopMcmd = NULL;
	int cnt= 0;
	for(int i=0; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
	{
		pCurMcmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
        if (pCurMcmd->m_bBookMarked) cnt ++;
		//pCurMcmd->m_bBookMarked = false;
	}
	if (cnt > 0)
	{
		CString s;
		s.Format("There total %d bookmark(s), are you sure removing them?", cnt);
       long ret = AfxMessageBox(s, MB_YESNO|MB_ICONQUESTION);
	   if( ret != IDYES)
	   {
	    	return;
	   }
	   for(int i=0; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
	   {
		   pCurMcmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
		   pCurMcmd->m_bBookMarked = false;
	   }
	    pDoc->UpdateView();
	}
}

void CLeftView::OnTogoBkmk() 
{
	// TODO: Add your command handler code here
	CTraDoc *pDoc = GetDocument();
	CMcmd* pCurMcmd = NULL, *pTopMcmd = NULL;
	boolean bkfound = false;
	for(int i= pDoc->m_iFocusMcmd; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
	{
		pCurMcmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
        bkfound = pCurMcmd->m_bBookMarked;
		if(bkfound) break;
	}

	if (!bkfound)
	{
		for(int i= 0; i< pDoc->m_iFocusMcmd; i++)
		{
	       	pCurMcmd = (CMcmd*) pDoc->m_ObjArrMcmds[i];
            bkfound = pCurMcmd->m_bBookMarked;
		    if(bkfound) break;
		}
	}

	if (bkfound)
	{
		pDoc->m_iFocusMcmd = pCurMcmd->ID;
		HTREEITEM hTreeItem;
		if (pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCurMcmd, (void*&)hTreeItem))
		{
			this->GetTreeCtrl().SelectItem(hTreeItem);
		}
	}
}

BOOL CLeftView::PreTranslateMessage(MSG* pMsg) 
{
	static int Id = -1, preID = -1;
	CTraDoc *pDoc = GetDocument();
	CMainFrame *pMFrm;
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam =='g' || pMsg->wParam == 'G'))
	{

		short ret = ::GetKeyState(VK_SHIFT);

		//CString s;
		//s.Format("pMsg->wParam = '%c'", pMsg->wParam);
		//AfxMessageBox(s);

		if(ret < 0 && (pMsg->wParam == 'g' || pMsg->wParam == 'G'))
		{

			preID = (Id == -1 ? pDoc->m_iFocusMcmd : Id);
			if (Id == -1)
				Id = pDoc->m_iFocusMcmd;
			else Id = Id + 1;

			while(Id%pDoc->m_ObjArrMcmds.GetSize() != preID)
			{

				TRACE("Id = %d, preID = %d\n", Id, preID);

				CMcmd *pCur = (CMcmd*) pDoc->m_ObjArrMcmds[Id];
				if (pCur->m_bBookMarked)
				{
					CString txt;

					pMFrm = (CMainFrame*)::AfxGetMainWnd();
					pMFrm->m_wndStatusBar.SetPaneText(0, "Goto bookmark: "+ pCur->mcmd);
					break;
				}
				Id = (Id+1)%pDoc->m_ObjArrMcmds.GetSize();
			}
			return true;
		}
		
	}

	if (pMsg->message == WM_KEYUP && (pMsg->wParam == VK_SHIFT))
	{

		short ret = ::GetKeyState(VK_SHIFT);

		CString s;
		s.Format("pMsg->wParam = '%c', ret = %d\n", pMsg->wParam, ret);
		//AfxMessageBox(s);
			//s.Format("Id = '%d', preID=%d\n", Id, preID);
			//AfxMessageBox(s);
			if (Id * preID >= 0 && Id != preID)
			{
			    pDoc->m_iFocusMcmd = Id;
		        HTREEITEM hTreeItem;
				CMcmd *pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[Id];
		        if (pDoc->m_MpMcmd_To_hHreeItem.Lookup(pCurMcmd, (void*&)hTreeItem))
				{
			        this->GetTreeCtrl().SelectItem(hTreeItem);
				}
			}
			return true;
	}
    
	return CTreeView::PreTranslateMessage(pMsg);
}

void CLeftView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	//AfxMessageBox("key donw");
	//set pResult with 1 to superess tree contorl key event.
	*pResult = 1;
}
