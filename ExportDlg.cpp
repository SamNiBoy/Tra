// ExportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "ExportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog


CExportDlg::CExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExportDlg)
	m_bExpNodeOnly = FALSE;
	m_nFrm = 0;
	m_nTo = 0;
	m_sFileName = _T("");
	m_bSelOnly = FALSE;
	//}}AFX_DATA_INIT
}


void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExportDlg)
	DDX_Check(pDX, IDC_EXPORT_CHK_NDOLY, m_bExpNodeOnly);
	DDX_Text(pDX, IDC_EXPORT_EDT_FRM, m_nFrm);
	DDX_Text(pDX, IDC_EXPORT_EDT_TO, m_nTo);
	DDX_Text(pDX, IDC_EXPORT_FILE_NAME, m_sFileName);
	DDX_Check(pDX, IDC_EXPORT_CHK_SELOLY, m_bSelOnly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExportDlg, CDialog)
	//{{AFX_MSG_MAP(CExportDlg)
	ON_BN_CLICKED(IDC_EXPORT_BTN_OPEN, OnExportBtnOpen)
	ON_BN_CLICKED(IDC_EXPORT_CHK_SELOLY, OnExportChkSeloly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExportDlg message handlers

void CExportDlg::OnExportBtnOpen() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFilters[]= _T("Moca trace files (*.log)|*.log|Mtf trace files (*.out)|*.out|All files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("log"), _T("*.log"), OFN_HIDEREADONLY,szFilters);

	if(dlg.DoModal()!=IDOK)
		return;

	m_sFileName = dlg.GetPathName();

	this->UpdateData(false);

	//AfxMessageBox(m_sFileName);

	//OpenFile(filename);	
}

void CExportDlg::OnExportChkSeloly() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (this->m_bSelOnly)
	{
	    GetDlgItem(IDC_EXPORT_EDT_FRM)->EnableWindow(false);
	    GetDlgItem(IDC_EXPORT_EDT_TO)->EnableWindow(false);
	}
	else
	{
	    GetDlgItem(IDC_EXPORT_EDT_FRM)->EnableWindow(true);
	    GetDlgItem(IDC_EXPORT_EDT_TO)->EnableWindow(true);
	}
}

void CExportDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_sFileName.IsEmpty())
	{
		AfxMessageBox("Please specify file to save.", MB_OK|MB_ICONERROR);
		return;
	}

	if (!m_bSelOnly && m_nFrm > m_nTo)
	{
		AfxMessageBox("From ID can not bigger than To ID.", MB_OK|MB_ICONERROR);
		return;
	}

	if (!m_bSelOnly &&m_nTo > m_nMaxID)
	{
		CString s;
		s.Format("Max ID is %ld, To ID must be less than it.", m_nMaxID);
		AfxMessageBox(s, MB_OK|MB_ICONERROR);
		return;
	}
	CDialog::OnOK();
}
