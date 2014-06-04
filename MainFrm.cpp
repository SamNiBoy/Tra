// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Tra.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "TraView.h"
#include "TraDoc.h"
#include "SpltFileDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_CHAR()
	ON_COMMAND(IDM_FIND_NXTMCMD, OnFindNxtmcmd)
	ON_COMMAND(IDM_VIEW_TOOLBAR, OnViewToolbar)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_TOOLBAR, OnUpdateViewToolbar)
	ON_UPDATE_COMMAND_UI(IDM_PERFORM_ALL, OnUpdatePerformAll)
	ON_COMMAND(IDM_PERFORM_ALL, OnPerformAll)
	ON_COMMAND(IDM_PERFORM_SEL, OnPerformSel)
	ON_UPDATE_COMMAND_UI(IDM_PERFORM_SEL, OnUpdatePerformSel)
	ON_COMMAND(IDM_SHOW_PARMCMD, OnShowParmcmd)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_PARMCMD, OnUpdateShowParmcmd)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MCMD, OnUpdateINDMcmd)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_DROPFILES()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_SPLIT, OnFileSplit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_INDICATOR_MCMD,
	ID_INDICATOR_ID,
	ID_INDICATOR_TTME,
	ID_INDICATOR_SELLEN,
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndMyToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		 | CBRS_TOOLTIPS  | CBRS_SIZE_DYNAMIC) ||
		!m_wndMyToolBar.LoadToolBar(IDR_TOOLBAR))
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_RIGHT);
	m_wndMyToolBar.EnableDocking(CBRS_ALIGN_BOTTOM);
	//m_wndMyToolBar.SetSizes(CSize(200, 50), CSize(200,50));
	EnableDocking(CBRS_ALIGN_ANY);
	
	DockControlBar(&m_wndMyToolBar);
	DockControlBar(&m_wndToolBar);

	//m_wndMyToolBar.SetButtonText(0, "Search At Left");
	//this->LoadBarState("abc");
	m_bSearchShwFlg = 0;
	m_wndMyToolBar.ShowWindow(SW_HIDE);
	

	//m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_NORMAL, 300);
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_MCMD, SBPS_NORMAL, 600);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_ID, SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_TTME, SBPS_NORMAL, 150);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_SELLEN, SBPS_NORMAL, 150);
	m_wndStatusBar.ShowWindow(SW_HIDE);
	m_wndToolBar.ShowWindow(SW_HIDE);

	
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(350, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTraView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_wndSplitter.ShowWindow(SW_HIDE);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

	//cs.style |= ~FWS_ADDTOTITLE;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.style &= WS_THICKFRAME;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->SaveBarState("abc");
	CFrameWnd::OnClose();
}


void CMainFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("haha?");
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnFindNxtmcmd() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewToolbar() 
{
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();

	if (pDoc->m_ObjArrMcmds.GetSize() <= 0)
		return;
	// TODO: Add your command handler code here
	if(!m_bSearchShwFlg)
	{
		m_bSearchShwFlg = 1;
	}
	else
	{
		m_bSearchShwFlg = 0;
	}

	ShowControlBar(&m_wndMyToolBar, m_bSearchShwFlg, FALSE);
	CRect rc;
	GetClientRect(&rc);

	CPoint pt;
	pt.x = (rc.right - rc.left)/2;
	pt.y = (rc.bottom - rc.top)/2;
	m_wndMyToolBar.GetClientRect(&rc);

	pt.x -= (rc.right - rc.left)/2;
	pt.y -= (rc.bottom - rc.top)/2;
	ClientToScreen(&pt);
    FloatControlBar(&this->m_wndMyToolBar,pt);
	m_wndMyToolBar.m_pEdit->SetFocus();
}

void CMainFrame::OnUpdateViewToolbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bSearchShwFlg);
	
}

void CMainFrame::OnUpdatePerformAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	pCmdUI->Enable(pDoc->m_ObjArrMcmds.GetSize()>0);
}

void CMainFrame::OnPerformAll() 
{
	// TODO: Add your command handler code here
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	POSITION pos;
	pos=pDoc->GetFirstViewPosition();
	while(pos)
	{
		CView *pV=pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CLeftView)))
			((CLeftView*)pV)->DoPerformance(true);
	}
}

void CMainFrame::OnPerformSel() 
{
	// TODO: Add your command handler code here
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	POSITION pos;
	pos=pDoc->GetFirstViewPosition();
	while(pos)
	{
		CView *pV=pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CLeftView)))
			((CLeftView*)pV)->DoPerformance(false);
	}
}

void CMainFrame::OnUpdatePerformSel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	pCmdUI->Enable(pDoc->m_ObjArrMcmds.GetSize()>0);
}

void CMainFrame::OnUpdateINDMcmd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	if(pDoc->m_ObjArrMcmds.GetSize()>0)
	{
		CMcmd *pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd -1];
		CSize sz = m_wndStatusBar.GetDC()->GetTextExtent(pCurMcmd->mcmd);
		m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_MCMD, SBPS_NORMAL, sz.cx);
	   pCmdUI->SetText(pCurMcmd->mcmd);
	}*/
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam ==VK_CONTROL || pMsg->wParam == VK_SPACE || pMsg->wParam == VK_ESCAPE))
	{

		short ret = ::GetKeyState(VK_CONTROL);

		//AfxMessageBox("here?");
		if( ret < 0)
		{
			m_wndMyToolBar.m_pBtn->m_bSearchAtLeft = !m_wndMyToolBar.m_pBtn->m_bSearchAtLeft;
			m_wndMyToolBar.m_pBtn->SetCheck(m_wndMyToolBar.m_pBtn->m_bSearchAtLeft);
			return TRUE;
		}

		if(pMsg->wParam == VK_ESCAPE)
		{
			if(m_wndMyToolBar.m_pEdit->m_pFindLstDlg->m_hWnd != NULL && 
				m_wndMyToolBar.m_pEdit->m_pFindLstDlg->IsWindowVisible())
				m_wndMyToolBar.m_pEdit->m_pFindLstDlg->ShowWindow(SW_HIDE);
		}

		if(m_bSearchShwFlg && pMsg->wParam == VK_ESCAPE)
		{
		    OnViewToolbar();
			return TRUE;
		}
		else if(!m_bSearchShwFlg && (pMsg->wParam == VK_SPACE))
		{
			OnViewToolbar();
			return TRUE;
		}
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnShowParmcmd() 
{
	// TODO: Add your command handler code here
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	POSITION pos;
	pos=pDoc->GetFirstViewPosition();
	while(pos)
	{
		CView *pV=pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CLeftView)))
			((CLeftView*)pV)->OnShowParmcmd();
	}	
}

void CMainFrame::OnUpdateShowParmcmd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
	pCmdUI->Enable(pDoc->m_ObjArrMcmds.GetSize()>0);
	
}

void CMainFrame::OnHelp() 
{
	// TODO: Add your command handler code here
	CFrameWnd::OnHelpIndex();
}

void CMainFrame::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	CTraDoc *pDoc=(CTraDoc*)GetActiveDocument();
    UINT nFiles = ::DragQueryFile(hDropInfo, (UINT) -1, NULL, 0);
	if(nFiles > 1)
	{
	    ::AfxMessageBox("Doesn't support opening multiple files!", MB_OK|MB_ICONERROR);
		return;
	}
    TCHAR szFileName[_MAX_PATH];
    ::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
	CString fn(szFileName);
    //::AfxMessageBox(szFileName);
	pDoc->OpenFile(fn);
    ::DragFinish(hDropInfo);
	//CFrameWnd::OnDropFiles(hDropInfo);
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CTraDoc* pDoc = (CTraDoc*)this->GetActiveDocument();
	if(pDoc)
	{	
	    CView *pViw = NULL;
	    POSITION pos = pDoc->GetFirstViewPosition();
	    while(pos)
		{
		    pViw = pDoc->GetNextView(pos);
		    if(pViw->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			    return TRUE;
		}
	}

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CTraDoc* pDoc = (CTraDoc*)this->GetActiveDocument();
	SetWindowText(pDoc->m_sFileName);

	if (!m_wndSplitter.IsWindowVisible())
	{
	    CRect rt;
		CBrush b;
		b.CreateSolidBrush(RGB(150,150,150));
	    this->GetClientRect(&rt);
		//dc.SetBkColor(0xAAAAAA);
		dc.FillRect(&rt, &b);
	    //dc.Rectangle(&rt);
		
        CFont font, font2, *pOldFont= NULL;

        font.CreatePointFont(300, "impact", &dc);
		font2.CreatePointFont(100, "impact", &dc);  
        pOldFont = dc.SelectObject(&font);   
        dc.SetBkMode(TRANSPARENT);

		TEXTMETRIC tm;
	    dc.GetTextMetrics(&tm);

        dc.SetTextColor(0xFFFFFF);
		
        dc.TextOut(rt.right/2-tm.tmAveCharWidth*6, rt.bottom/2-tm.tmHeight, "Trace Digger");

		dc.SelectObject(&font2);

		dc.TextOut(rt.right/2+ tm.tmAveCharWidth*3, rt.bottom/2+tm.tmHeight * 1, "Version 2.0");
        dc.SelectObject(pOldFont);
        if(pOldFont)
            font.DeleteObject(); 
	}
	// Do not call CFrameWnd::OnPaint() for painting messages
}

void CMainFrame::OnFileSplit() 
{
	// TODO: Add your command handler code here
    CSpltFileDlg *p = new CSpltFileDlg;
	p->DoModal();
	delete p;
}
