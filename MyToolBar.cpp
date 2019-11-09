// MyToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "MyToolBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyToolBar

CMyToolBar::CMyToolBar()
{
	m_pEdit = new CEditFinder;
	m_pBtn = new CBtnSchLft;
}

CMyToolBar::~CMyToolBar()
{
	delete m_pEdit;
	delete m_pBtn;
}


BEGIN_MESSAGE_MAP(CMyToolBar, CToolBar)
	//{{AFX_MSG_MAP(CMyToolBar)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyToolBar message handlers
CFont ft;
LOGFONT lf;
int CMyToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->cx = 60;
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	CRect rc;
	rc.left = 0;
	rc.top = 0;
	rc.bottom = rc.top + 30;
	rc.right = rc.left + 400;
	m_pEdit->Create(WS_CHILD | WS_VISIBLE| WS_TABSTOP |ES_WANTRETURN, rc, this, IDE_TOOLBAR_FIND);
	//static CFont ft;

	
    lf.lfHeight = 25;                      // request a 12-pixel-height font
    strcpy(lf.lfFaceName, "Times New Roman");        // request a face name "Arial"
	lf.lfWeight = FW_NORMAL;
	ft.CreateFontIndirect(&lf);
	//ft.CreatePointFont(160,"Arial");
	//m_pEdit->GetDC()->SetTextColor(RGB(0,0,255));
	m_pEdit->SetFont(&ft);
	rc.bottom = rc.top + 30;
	rc.left = rc.right+5;
	rc.right = rc.left + 200;
	m_pBtn->Create("In Mcmd", BS_NOTIFY|BS_FLAT|WS_CHILD | WS_VISIBLE, rc, this, IDE_TOOLBAR_SERLFT);

	m_pBtn->SetButtonStyle(BS_AUTOCHECKBOX);
	m_pBtn->SetCheck(false);

	this->SetWindowText("Search:");
	return 0;
}

HBRUSH CMyToolBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CToolBar::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
	CEdit *pEdit = (CEdit *) this->GetDlgItem(IDE_TOOLBAR_FIND);
	
	/*CFont ft;
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT));       // zero out structure
    lf.lfHeight = 15;                      // request a 12-pixel-height font
    strcpy(lf.lfFaceName, "Arial");        // request a face name "Arial"
	lf.lfWeight = FW_BOLD;
	ft.CreateFontIndirect(&lf);
	*///pEdit->SetFont(&ft);
	//pDC->SelectObject(&ft);
	pDC->SetTextColor(RGB(0,0,255));
	pDC->SetBkMode(TRANSPARENT);
	//pDC->SetTextAlign(TA_CENTER);

	// TODO: Return a different brush if the default is not desired
	return hbr;
}



void CMyToolBar::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	::AfxMessageBox("close?");
	CMainFrame *pFrm=(CMainFrame*)(::AfxGetApp()->GetMainWnd());
	pFrm->m_bSearchShwFlg = false;
	CToolBar::OnClose();
}
