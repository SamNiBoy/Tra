// GphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "Mcmd.h"
#include "TraDoc.h"
#include "GphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGphDlg dialog


CGphDlg::CGphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGphDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGphDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iCurScrollPos = 0;
	m_iMrgTop = 100;
	m_iMrgLeft = 100;
	m_iMrgRight = 100;
	m_iMrgBottom = 100;
}


void CGphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGphDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGphDlg, CDialog)
	//{{AFX_MSG_MAP(CGphDlg)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGphDlg message handlers

void CGphDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rt;
	int McmdCnt = 0;
	this->GetClientRect(&rt);
	CBrush b=RGB(120,120,120);
	
	dc.SetWindowOrg(0, m_iCurScrollPos);
	//dc.Rectangle(rt);
	if(m_RootMcmd)
	{
		McmdCnt++;
		for(int i = m_RootMcmd->ID; i< m_pDoc->m_ObjArrMcmds.GetSize(); i++)
		{
			CMcmd *pCur = (CMcmd*) m_pDoc->m_ObjArrMcmds[i];
			if(pCur->level <= m_RootMcmd->level)
				break;
			McmdCnt++;
			//dc.TextOut(0, i*20, pCur->mcmd);
		}

	    SCROLLINFO si;

		si.cbSize = sizeof(si);
		si.fMask = SIF_PAGE | SIF_RANGE |SIF_POS;
		si.nMax = McmdCnt * (m_iMcmdHSize + 10) + m_iMrgTop + m_iMrgBottom;
		si.nMin = 1 * m_iMcmdHSize;
		si.nPage = m_iPageSize;
		si.nPos = m_iCurScrollPos;

		m_iMaxSize = si.nMax;
		//si.nTrackPos = 1;
		//this->SetScrollRange(SB_HORZ, 100, si.nMax, true);
		this->SetScrollInfo(SB_VERT, (struct tagSCROLLINFO *)&si, true);

		rt.left = m_iMrgLeft;
		rt.top = m_iMrgTop;
		rt.right = rt.left + m_iMcmdWSize;
		rt.bottom = rt.top + m_iMcmdHSize;
		dc.SelectObject(&b);
		CRect layer = rt;
		layer.bottom = si.nMax - m_iMrgBottom;
		layer.DeflateRect(-10, -10, -10, -10);
		dc.Rectangle(layer);
		CBrush b2=RGB(255,255,0);
		dc.SelectObject(b2);
		for(i = m_RootMcmd->ID - 1; i< m_RootMcmd->ID + McmdCnt - 1; i++)
		{
			CMcmd *pCur = (CMcmd*) m_pDoc->m_ObjArrMcmds[i];
		    pCur->DrawSelf(&dc, rt);
			rt.top += m_iMcmdHSize + 10;
			rt.bottom = rt.top + m_iMcmdHSize;
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CGphDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	//pScrollBar->ScrollWindow(50, 0);
	int deta;
	switch(nSBCode)
	{
	case SB_LINEUP:
		deta = -m_iLineSize;
		break;
	case SB_PAGEUP:
		deta = -m_iPageSize;
		break;
	case SB_PAGEDOWN:
		deta = m_iPageSize;
		break;
	case SB_THUMBTRACK:
		deta = (int)nPos - m_iCurScrollPos;
		break;
	case SB_LINEDOWN:
		deta = m_iLineSize;
		break;
	default:
		return;
	}
	if(deta != 0)
	{
		if (deta < 0 && m_iCurScrollPos <= -deta)
			deta = - m_iCurScrollPos;
		else if(deta > 0 && m_iMaxSize < m_iCurScrollPos + deta)
			deta = m_iMaxSize - m_iCurScrollPos;
	    m_iCurScrollPos += deta;
		this->SetScrollPos(SB_VERT, m_iCurScrollPos, TRUE);
		this->ScrollWindow(0, deta);
		this->Invalidate();
	}
	//CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGphDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	m_iPageSize = cy;
	m_iLineSize = m_iPageSize / 5;
	m_iMcmdWSize = 500;
	m_iMcmdHSize = 50;
	// TODO: Add your message handler code here
	
}
