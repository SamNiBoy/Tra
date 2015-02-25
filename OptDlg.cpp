// OptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "OptDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptDlg dialog

COptDlg::COptDlg() : CPropertyPage(COptDlg::IDD)
{
	//{{AFX_DATA_INIT(COptDlg)
	m_bIncludeDelete = TRUE;
	m_bIncludeInsert = TRUE;
	m_bIncludeMcmd = TRUE;
	m_bIncludeSelect = TRUE;
	m_bIncludeUpdate = TRUE;
	m_eMcmdBeg = _T("");
	m_eMcmdEnd = _T("");
	m_iMaxLineNum = 1000;
	m_dThreshVal = 0.01;
	m_bSupMod = FALSE;
	m_bAlwsLines = TRUE;
	//}}AFX_DATA_INIT

	this->begs.Add("Finding command");
	this->begs.Add("Finding command");
	this->begs.Add("Finding command");
	this->begs.Add("] Firing triggers...");
	this->begs.Add("Looking up Command");
	this->begs.Add("Looking up Command");
	//this->begs.Add("Looking up Command");
	this->begs.Add("] Firing triggers");




	
	
	
	//this->begs.Add("If-test");

	this->ends.Add("Executed command");
	this->ends.Add("Invalid command");
	this->ends.Add("Could not construct command");
	this->ends.Add("Finished firing triggers");
	this->ends.Add("Executed Command");
	this->ends.Add("Built-in command");
	//this->ends.Add("CommandNotFoundException");
	this->ends.Add("Done Firing triggers");
	


	m_bShowAll = FALSE;
	m_bShowSingle = TRUE;
	//this->ends.Add("LEVEL");

}


void COptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptDlg)
	DDX_Control(pDX, IDC_LST_END, m_LstEnd);
	DDX_Control(pDX, IDC_LST_BEGIN, m_LstBeg);
	DDX_Check(pDX, IDC_CHK_DELETE, m_bIncludeDelete);
	DDX_Check(pDX, IDC_CHK_INSERT, m_bIncludeInsert);
	DDX_Check(pDX, IDC_CHK_MCMD, m_bIncludeMcmd);
	DDX_Check(pDX, IDC_CHK_SELECT, m_bIncludeSelect);
	DDX_Check(pDX, IDC_CHK_Update, m_bIncludeUpdate);
	DDX_Check(pDX, IDC_RAD_SHOWALL, m_bShowAll);
	DDX_Check(pDX, IDC_RAD_SHOWSINGLE, m_bShowSingle);
	DDX_Text(pDX, IDC_EDT_BEGIN, m_eMcmdBeg);
	DDV_MaxChars(pDX, m_eMcmdBeg, 50);
	DDX_Text(pDX, IDC_EDT_END, m_eMcmdEnd);
	DDV_MaxChars(pDX, m_eMcmdEnd, 50);
	DDX_Text(pDX, IDC_EDT_MAXLINENUM, m_iMaxLineNum);
	DDX_Text(pDX, IDC_EDT_THRESHVAL, m_dThreshVal);
	DDX_Check(pDX, IDC_CHK_SUPMOD, m_bSupMod);
	DDX_Check(pDX, IDC_CHK_LOD3000, m_bAlwsLines);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptDlg, CPropertyPage)
	//{{AFX_MSG_MAP(COptDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_LBN_SELCHANGE(IDC_LST_BEGIN, OnSelchangeLstBegin)
	ON_LBN_SELCHANGE(IDC_LST_END, OnSelchangeLstEnd)
	ON_BN_CLICKED(IDC_OPT_ADD, OnOptAdd)
	ON_BN_CLICKED(IDC_OPT_REMOVE, OnOptRemove)
	ON_BN_CLICKED(IDC_RAD_SHOWALL, OnRadShowall)
	ON_BN_CLICKED(IDC_RAD_SHOWSINGLE, OnRadShowsingle)
	ON_BN_CLICKED(IDC_CHK_SUPMOD, OnChkSupmod)
	ON_COMMAND(IDM_SHOW_ALL, OnShowAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptDlg message handlers

int COptDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class

	//MessageBox("domodel");

	return CDialog::DoModal();
}

int COptDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	//MessageBox("OnCreate");
	// TODO: Add your specialized creation code here

	return 0;
}

AFX_STATIC_DATA int _afxPropSheetButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL COptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CListBox *pLB = (CListBox *)GetDlgItem(IDC_LST_BEGIN);
	CListBox *pLE = (CListBox *)GetDlgItem(IDC_LST_END);

	for(long i = 0 ;i<this->begs.GetSize(); i++)
	{
		pLB->AddString(begs[i]);
		pLE->AddString(ends[i]);
	}

    CMainFrame *pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();
    CTraDoc *pDoc = (CTraDoc*)pMain->GetActiveDocument();

    for (int i = 0; i < _countof(_afxPropSheetButtons); i++)
    {
        HWND hWndButton = ::GetDlgItem(pDoc->m_pSheet->m_hWnd, _afxPropSheetButtons[i]);
        if (hWndButton != NULL && (_afxPropSheetButtons[i] == ID_APPLY_NOW || _afxPropSheetButtons[i] == IDHELP))
        {
            ::ShowWindow(hWndButton, SW_HIDE);
            ::EnableWindow(hWndButton, FALSE);
        }
        else if (hWndButton != NULL)
        {
            CRect btnRt, sheetRt;
            ::GetWindowRect(hWndButton, &btnRt);
            ::GetWindowRect(pDoc->m_pSheet->m_hWnd, &sheetRt);

            CSize btnSz(100, 25);

            pDoc->m_pSheet->ScreenToClient(&btnRt);
            pDoc->m_pSheet->ScreenToClient(&sheetRt);

            btnSz.cx = (sheetRt.right - sheetRt.left) / 4;

            if (_afxPropSheetButtons[i] == IDOK)
            {
                ::MoveWindow(hWndButton, sheetRt.left + (sheetRt.right - sheetRt.left)/8, btnRt.top, btnSz.cx, btnSz.cy, false);
            }
            else if (_afxPropSheetButtons[i] == IDCANCEL)
            {
                ::MoveWindow(hWndButton, sheetRt.left + (sheetRt.right - sheetRt.left)*5/8, btnRt.top, btnSz.cx, btnSz.cy, false);
            }

        }
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   MSG const *  pMsg = CWnd::GetCurrentMessage();
   CString str;
   str.Format("Message id is '%ld",pMsg->message);
   //MessageBox(str);	
	CRect rc;

	CListBox *pB=(CListBox*)this->GetDlgItem(IDC_LST_BEGIN);
	CListBox *pE=(CListBox*)this->GetDlgItem(IDC_LST_END);
	//dc.SelectObject
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH COptDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

//	static HBRUSH mybsh =0;

	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
    if(nCtlColor == CTLCOLOR_BTN)
	{
	static CBrush br(RGB(255,0,0));
	
	//pDC->SelectObject(&br);
	pDC->SetTextColor(RGB(0,255,0));
	pDC->SetBkMode(TRANSPARENT);
	//pWnd->RedrawWindow();
	return br;
	}
	return hbr;
}

void COptDlg::OnSelchangeLstBegin() 
{
	// TODO: Add your control notification handler code here
	//::AfxMessageBox("haha");
	int idx=m_LstBeg.GetCurSel();
	m_LstEnd.SetCurSel(idx);
}

void COptDlg::OnSelchangeLstEnd() 
{
	// TODO: Add your control notification handler code here
	int idx=m_LstEnd.GetCurSel();
	m_LstBeg.SetCurSel(idx);	
}

void COptDlg::OnOptAdd() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	m_eMcmdBeg.TrimLeft();
	m_eMcmdBeg.TrimRight();
	m_eMcmdEnd.TrimLeft();
	m_eMcmdEnd.TrimRight();

	if(m_eMcmdBeg.GetLength() > 0 && m_eMcmdEnd.GetLength() > 0)
	{
		m_LstBeg.AddString(m_eMcmdBeg);
		begs.Add(m_eMcmdBeg);

		m_LstEnd.AddString(m_eMcmdEnd);
		ends.Add(m_eMcmdEnd);
	}
}

void COptDlg::OnOptRemove() 
{
	// TODO: Add your control notification handler code here
	int idx = m_LstBeg.GetCurSel();
	if(idx >= 0 )
	{
	    m_LstBeg.DeleteString(idx);
	    m_LstEnd.DeleteString(idx);
	    begs.RemoveAt(idx);
	    ends.RemoveAt(idx);
	}
}

void COptDlg::OnRadShowall() 
{
	// TODO: Add your control notification handler code here
	if (m_bSupMod)
	{
		m_bShowAll = FALSE;
		m_bShowSingle = TRUE;
		AfxMessageBox("Super file mode, can not turn show all flag on!");
        CButton *pE=(CButton*)this->GetDlgItem(IDC_RAD_SHOWALL);
		pE->SetCheck(m_bShowAll);
		pE=(CButton*)this->GetDlgItem(IDC_RAD_SHOWSINGLE);
		pE->SetCheck(m_bShowSingle);
	}
	m_bShowAll = TRUE;
	m_bShowSingle = FALSE;
}

void COptDlg::OnRadShowsingle() 
{
	// TODO: Add your control notification handler code here
	m_bShowAll = FALSE;
	m_bShowSingle = TRUE;
}

void COptDlg::OnChkSupmod() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pMain =	(CMainFrame*)::AfxGetApp()->GetMainWnd();
	CTraDoc *pDoc = (CTraDoc*)pMain->GetActiveDocument();
	if (pDoc->m_pf)
	{
		AfxMessageBox("You can not change this mode while you have trace opened, try to change it before opening trace file!");
        CButton *pE=(CButton*)this->GetDlgItem(IDC_CHK_SUPMOD);
		pE->SetCheck(m_bSupMod);
	}

	if (m_bShowAll)
	{
		AfxMessageBox("Show All mode will be turn off if enabling super file mode!");
		m_bShowAll = FALSE;
		m_bShowSingle = TRUE;
        CButton *pE=(CButton*)this->GetDlgItem(IDC_RAD_SHOWALL);
		pE->SetCheck(m_bShowAll);
		pE=(CButton*)this->GetDlgItem(IDC_RAD_SHOWSINGLE);
		pE->SetCheck(m_bShowSingle);
	}
	
	CButton *pE=(CButton*)this->GetDlgItem(IDC_CHK_SUPMOD);
	m_bSupMod = pE->GetCheck();

}

void COptDlg::OnShowAll() 
{
	// TODO: Add your command handler code here

}
