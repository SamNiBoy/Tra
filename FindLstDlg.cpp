// FindLstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "FindLstDlg.h"
#include "MainFrm.h"
#include "TraDoc.h"
#include "LeftView.h"
#include "TraView.h"
#include "FindLstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindLstDlg dialog


CFindLstDlg::CFindLstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindLstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindLstDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CFindLstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindLstDlg)
	DDX_Control(pDX, IDC_FIND_LST, m_CLstBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindLstDlg, CDialog)
	//{{AFX_MSG_MAP(CFindLstDlg)
	ON_LBN_DBLCLK(IDC_FIND_LST, OnDblclkFindLst)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BTN_CPALL, OnBtnCpall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindLstDlg message handlers

BOOL CFindLstDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindLstDlg::OnDblclkFindLst() 
{
	// TODO: Add your control notification handler code here
		CTraApp * pApp = (CTraApp *)::AfxGetApp();
	    CMainFrame * pMf = (CMainFrame*)pApp->m_pMainWnd;
        CTraDoc *pDoc = (CTraDoc*) pMf->GetActiveDocument();
		CLeftView* pLVW;
		CTraView *pTVW;
		
		POSITION pos = pDoc->GetFirstViewPosition();
		while(pos != NULL)
		{
			CView *pVw = pDoc->GetNextView(pos);
			if(pVw->IsKindOf(RUNTIME_CLASS(CLeftView)))
			{
				pLVW = (CLeftView *) pVw;
			}
			else if(pVw->IsKindOf(RUNTIME_CLASS(CTraView)))
			{
				pTVW = (CTraView *) pVw;
			}
		}
		

		CListBox *pLB = (CListBox*) this->GetDlgItem(IDC_FIND_LST);
		int curSelIdx;
		curSelIdx = pLB->GetCurSel();
	    CMcmd *pSelectedMcmd = (CMcmd *)mcmds[curSelIdx];
		HTREEITEM hTreeItem;
		if(pDoc->m_MpMcmd_To_hHreeItem.Lookup(pSelectedMcmd, (void *&)hTreeItem))
		{
			pDoc->m_iFocusMcmd = pSelectedMcmd->ID;
			CTreeCtrl &CTC = pLVW->GetTreeCtrl();
			CTC.Select(hTreeItem, TVGN_CARET);
			CRichEditCtrl &CRE = pTVW->GetRichEditCtrl();
			if (linesId[curSelIdx] >= pDoc->m_BegLinId && linesId[curSelIdx] <= pDoc->m_EndLinId)
			{
	            int detLin = linesId[curSelIdx] - pDoc->m_BegLinId - CRE.GetFirstVisibleLine();
	            CRE.LineScroll(detLin);
				pTVW->DecorateKeyWord(pDoc->m_pf->GetOffSetForLine(linesId[curSelIdx]) -
					                  pDoc->m_pf->GetOffSetForLine(pDoc->m_BegLinId),
									  pDoc->m_pf->GetOffSetForLine(linesId[curSelIdx] + 1) -
					                  pDoc->m_pf->GetOffSetForLine(pDoc->m_BegLinId));
			}

			return;
		}
		else
		{
			::AfxMessageBox("The command doesn't exist on the tree!", MB_OK|MB_ICONINFORMATION);
		}
}

void CFindLstDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CButton *pB = (CButton*) this->GetDlgItem(IDOK);
	if(pB != NULL && pB->m_hWnd != NULL)
	{
		CRect rc;
		long len, wid;
		pB->GetWindowRect(&rc);
		ScreenToClient(&rc);
		len = rc.right - rc.left;
		wid = rc.bottom - rc.top;
		pB->MoveWindow(cx/3 - len/2, cy - wid-10, len, wid);
	}


	CButton *pC = (CButton*) this->GetDlgItem(IDC_BTN_CPALL);
	if(pC != NULL && pC->m_hWnd != NULL)
	{
		CRect rc;
		long len, wid;
		pC->GetWindowRect(&rc);
		ScreenToClient(&rc);
		len = rc.right - rc.left;
		wid = rc.bottom - rc.top;
		pC->MoveWindow(2*cx/3 - len/2, cy - wid-10, len, wid);
	}

	if(m_CLstBox.m_hWnd != NULL)
	{
		CRect rc;
	    pB->GetWindowRect(&rc);
		ScreenToClient(&rc);
		cy = rc.top-10;
	    m_CLstBox.MoveWindow(0,0,cx,cy);
	}
	
}

void CFindLstDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}

void CFindLstDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

HBRUSH CFindLstDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(RGB(0,0,255));
	CFont *pFont;
	pFont = new CFont;
	//pFont->CreatePointFont(100,"Arial");
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
    lf.lfHeight = 15;                      // request a 12-pixel-height font
    strcpy(lf.lfFaceName, "Arial");        // request a face name "Arial"
	lf.lfWeight = FW_BOLD;

	pFont->CreateFontIndirect(&lf);
	pDC->SelectObject(pFont);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CFindLstDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CFindLstDlg::OnSetFont(CFont* pFont) 
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnSetFont(pFont);
}

BOOL CFindLstDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= WS_CHILD;
	return CDialog::PreCreateWindow(cs);
}

void CFindLstDlg::OnBtnCpall() 
{
	// TODO: Add your control notification handler code here
	CListBox *pLB = (CListBox*) this->GetDlgItem(IDC_FIND_LST);
	int lincnt = pLB->GetCount();
	CString line, s = "";
	for (int i=0;i<lincnt; i++)
	{
		pLB->GetText(i, line);
		s += line+"\n";
	}

	//::AfxMessageBox(s);

	HGLOBAL g = ::GlobalAlloc(GMEM_MOVEABLE, (s.GetLength() + 1) * sizeof(char));
     if(g == NULL)
        { /* alloc failed */
         ASSERT(FALSE);  // failed to allocate memory
         return;
        } /* alloc failed */

     LPTSTR p = (LPTSTR)::GlobalLock(g);
     if(p == NULL)
        { /* lock failed */
         ASSERT(FALSE);
         return;
        } /* lock failed */

     strcpy(p, (LPCTSTR)s);

     ::GlobalUnlock(g);

     if(!OpenClipboard())
        { /* clipboard open failed */
         ASSERT(FALSE);
         GlobalFree(g);
         return;
        } /* clipboard open failed */

     if(!EmptyClipboard())
        { /* empty failed */
         ASSERT(FALSE);
         GlobalFree(g);
         return;
        } /* empty failed */

#ifdef _UNICODE
#define CF_ CF_UNICODETEXT 
#else
#define CF_ CF_TEXT
#endif
     if(::SetClipboardData(CF_, g) == NULL)
        { /* SetClipboardData failed */
         ASSERT(FALSE); //
         ::CloseClipboard();
         ::GlobalFree(g);
         return;
        } /* SetClipboardData failed */
     ::CloseClipboard();
}
