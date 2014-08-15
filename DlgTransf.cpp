// DlgTransf.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "DlgTransf.h"
//#include <winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTransf dialog


CDlgTransf::CDlgTransf(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTransf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	a1 = a2 = a3 = a4 = 0;
}


void CDlgTransf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTransf)
	DDX_Control(pDX, IDC_IPADDR, m_cIPAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTransf, CDialog)
	//{{AFX_MSG_MAP(CDlgTransf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTransf message handlers

BOOL CDlgTransf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString ips;
	if (a1 != 0)
	{

		ips.Format("%d.%d.%d.%d", a1, a2, a3, a4);
	}
	else
		ips = "127.0.0.1";

	DWORD IPPP=inet_addr(ips);
	m_cIPAddr.SetAddress(ntohl(IPPP));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTransf::OnOK() 
{
	// TODO: Add extra validation here
	m_cIPAddr.GetAddress(a1,a2,a3,a4);

	CDialog::OnOK();
}
