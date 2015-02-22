// Tra.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tra.h"

#include "MainFrm.h"
#include "TraDoc.h"
#include "TraView.h"
#include "mcmd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTraApp

BEGIN_MESSAGE_MAP(CTraApp, CWinApp)
	//{{AFX_MSG_MAP(CTraApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HIDE_APP, OnHideApp)
	ON_COMMAND(ID_SHOW_APP, OnShowApp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTraApp construction

CTraApp::CTraApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTraApp object

CTraApp theApp;

#ifdef _DEBUG
CMemoryState m1,m2,m3;
#endif
/////////////////////////////////////////////////////////////////////////////
// CTraApp initialization

BOOL CTraApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	if (!AfxInitRichEdit2())
	{
		AfxMessageBox("Init RichEdit2 failed!");
		return FALSE;
	}
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	//CMcmd *pp = new CMcmd[100];
#ifdef _DEBUG
	m1.Checkpoint();
#endif
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("SAM's Trace Digger"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CTraDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CTraView));
	AddDocTemplate(pDocTemplate);
	//pDocTemplate->m_bAutoDelete = true;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->SetWindowText("Trace Digger");
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	//this->SetDialogBkColor(RGB(100,100,100), RGB(255,0,0));

	return ((CMainFrame*) m_pMainWnd)->StartListenAcceptFile();
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_txtAbout;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_txtAbout = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDT_ABOUT, m_txtAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CTraApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
		aboutDlg.m_txtAbout = 
"                            \r\n\r\n\r\n\
                                            Trace Digger\r\n\r\n\
                                        developed by SAM.NI.\r\n\r\n\
";
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTraApp message handlers


int CTraApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//CTraDoc *pDoc = this->GetMainWnd();
	//this->WriteProfileString(


	
	int retcode = CWinApp::ExitInstance();
#ifdef _DEBUG
	m2.Checkpoint();
	if(m3.Difference(m1,m2))
	{
		::AfxDumpMemoryLeaks();
	}
#endif
	//delete this->m_pDocManager;
	return retcode;
}

void CTraApp::WriteOptionsToINI(CTraDoc *pDoc)
{
	int selectflg,updateflg,insertflg,deleteflg,mcmdflg, supmodflg;
	int ShowAll, ShowSingle, AlwsLines;
	long MaxLinBold;
	double threshold;
	selectflg = pDoc->m_OptMoca->m_bIncludeSelect;
	updateflg = pDoc->m_OptMoca->m_bIncludeUpdate;
	insertflg = pDoc->m_OptMoca->m_bIncludeInsert;
	deleteflg = pDoc->m_OptMoca->m_bIncludeDelete;
	mcmdflg = pDoc->m_OptMoca->m_bIncludeMcmd;
	threshold = pDoc->m_OptMoca->m_dThreshVal;
	MaxLinBold = pDoc->m_OptMoca->m_iMaxLineNum;
	supmodflg = pDoc->m_OptMoca->m_bSupMod;
	AlwsLines = pDoc->m_OptMoca->m_bAlwsLines;

	ShowAll = pDoc->m_OptMoca->m_bShowAll;
	ShowSingle = pDoc->m_OptMoca->m_bShowSingle;

	if (supmodflg)
	{
		ShowAll = 0;
		ShowSingle = 1;
	}

	CString s;
	s.Format("%lf",threshold);

	this->WriteProfileString("ThresholdValue","Thresh",s);
	this->WriteProfileInt("MaxLinBold","Thresh",MaxLinBold);

	this->WriteProfileInt("DisplaySQL","SELECT",selectflg);
	this->WriteProfileInt("DisplaySQL","UPDATE",updateflg);
	this->WriteProfileInt("DisplaySQL","INSERT",insertflg);
	this->WriteProfileInt("DisplaySQL","DELETE",deleteflg);
	this->WriteProfileInt("DisplaySQL","MCMD",mcmdflg);

	this->WriteProfileInt("RightPanelShow","ALL",ShowAll);
	this->WriteProfileInt("RightPanelShow","SINGLE",ShowSingle);

	this->WriteProfileInt("SuperFileMode","SUPMOD",supmodflg);
	this->WriteProfileInt("SuperFileMode","ALWAYSLINES",AlwsLines);


	//color setting
	this->WriteProfileInt("Color","RANGE",pDoc->m_OptColor->m_RANGEClr);
	this->WriteProfileInt("Color","BEYOND",pDoc->m_OptColor->m_BEYONDClr);
	this->WriteProfileInt("Color","ERROR",pDoc->m_OptColor->m_ERRClr);
	this->WriteProfileInt("Color","MCMD",pDoc->m_OptColor->m_MCMDClr);
	this->WriteProfileInt("Color","SELECT",pDoc->m_OptColor->m_SELECTClr);
	this->WriteProfileInt("Color","UPDATE",pDoc->m_OptColor->m_UPDATEClr);
	this->WriteProfileInt("Color","INSERT",pDoc->m_OptColor->m_INSERTClr);
	this->WriteProfileInt("Color","DELETE",pDoc->m_OptColor->m_DELClr);
	this->WriteProfileInt("Color","PUBLISH",pDoc->m_OptColor->m_PUBLISHClr);
	this->WriteProfileInt("Color","ARGUMENT",pDoc->m_OptColor->m_ARGUMENTClr);
	this->WriteProfileInt("Color","PARAMETER",pDoc->m_OptColor->m_PARAMETERClr);
	this->WriteProfileInt("Color","LPCOLOR",pDoc->m_OptColor->m_LPCOLORClr);
	this->WriteProfileInt("Color","RPCOLOR",pDoc->m_OptColor->m_RPCOLORClr);
	this->WriteProfileInt("Color","VALUE",pDoc->m_OptColor->m_VALUEClr);

}

void CTraApp::ReadOptionsFromINI(CTraDoc *pDoc)
{

	CString s;
	s=this->GetProfileString("ThresholdValue","Thresh");
	pDoc->m_OptMoca->m_dThreshVal = ::atof(s);
	pDoc->m_OptMoca->m_iMaxLineNum = this->GetProfileInt("MaxLinBold", "Thresh", 1000);
	pDoc->m_OptMoca->m_bIncludeSelect = this->GetProfileInt("DisplaySQL","SELECT",1);
	pDoc->m_OptMoca->m_bIncludeUpdate = this->GetProfileInt("DisplaySQL","UPDATE",1);
	pDoc->m_OptMoca->m_bIncludeInsert = this->GetProfileInt("DisplaySQL","INSERT",1);
	pDoc->m_OptMoca->m_bIncludeDelete = this->GetProfileInt("DisplaySQL","DELETE",1);
	pDoc->m_OptMoca->m_bIncludeMcmd = this->GetProfileInt("DisplaySQL","MCMD",1);

	pDoc->m_OptMoca->m_bShowAll = this->GetProfileInt("RightPanelShow","ALL",0);
	pDoc->m_OptMoca->m_bShowSingle = this->GetProfileInt("RightPanelShow","SINGLE",1);

	pDoc->m_OptMoca->m_bSupMod = this->GetProfileInt("SuperFileMode","SUPMOD",0);
	pDoc->m_OptMoca->m_bAlwsLines = this->GetProfileInt("SuperFileMode","ALWAYSLINES",1);

	if (pDoc->m_OptMoca->m_bSupMod)
	{
		pDoc->m_OptMoca->m_bShowAll = 0;
		pDoc->m_OptMoca->m_bShowSingle = 1;
	}



	//reading color setting
    pDoc->m_OptColor->m_RANGEClr = this->GetProfileInt("Color","RANGE",RGB(0,0,255));
    pDoc->m_OptColor->m_MCMDClr = this->GetProfileInt("Color","MCMD", RGB(0, 0,0));
    pDoc->m_OptColor->m_SELECTClr = this->GetProfileInt("Color","SELECT",RGB(0, 155,0));
    pDoc->m_OptColor->m_BEYONDClr = this->GetProfileInt("Color","BEYOND", RGB(50, 50,50));
    pDoc->m_OptColor->m_ERRClr = this->GetProfileInt("Color","ERROR",RGB(255, 0,0));
    pDoc->m_OptColor->m_UPDATEClr =this->GetProfileInt("Color","UPDATE", RGB(0, 155,155));
    pDoc->m_OptColor->m_INSERTClr =this->GetProfileInt("Color","INSERT", RGB(155, 155,0));
    pDoc->m_OptColor->m_DELClr =this->GetProfileInt("Color","DELETE", RGB(155, 0,155));
    pDoc->m_OptColor->m_PUBLISHClr =this->GetProfileInt("Color","PUBLISH",RGB(0,255,255));
    pDoc->m_OptColor->m_ARGUMENTClr =this->GetProfileInt("Color","ARGUMENT",RGB(255,0,0));
    pDoc->m_OptColor->m_PARAMETERClr =this->GetProfileInt("Color","PARAMETER",RGB(255,255,0));
    pDoc->m_OptColor->m_LPCOLORClr =this->GetProfileInt("Color","LPCOLOR", RGB(150, 150, 150));
    pDoc->m_OptColor->m_RPCOLORClr =this->GetProfileInt("Color","RPCOLOR", RGB(150, 150, 150));
    pDoc->m_OptColor->m_VALUEClr =this->GetProfileInt("Color","VALUE", RGB(200,00,00));

}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	/*CEdit edt;
	edt.Attach(GetDlgItem(IDC_EDT_ABOUT)->m_hWnd);
	CBrush b=RGB(255,0,0);
	CRect rc;
	edt.GetClientRect(&rc);
	edt.GetDC()->SelectObject(&b);
	edt.GetDC()->Rectangle(rc);
	edt.GetDC()->SetTextColor(RGB(0,255,255));
	edt.Detach();
	*/
	pWnd->GetDC()->SetTextColor(RGB(255,0,0));
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CTraApp::OnHideApp() 
{
	// TODO: Add your command handler code here
	//this->m_pMainWnd->ShowWindow(SW_HIDE);
}

void CTraApp::OnShowApp() 
{
	// TODO: Add your command handler code here
	//this->m_pMainWnd->ShowWindow(SW_SHOW);
}

CDocument* CTraApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CTraDoc *pDoc = (CTraDoc*)((CMainFrame*)m_pMainWnd)->GetActiveDocument();
	CString filename = lpszFileName;
	//pDoc->OpenFile(filename);
	//AfxMessageBox(lpszFileName);
	CTraDoc *pDoc = (CTraDoc*)CWinApp::OpenDocumentFile(lpszFileName);
	pDoc->OpenFile(filename);
	return pDoc;
}

