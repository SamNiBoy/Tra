// InProgress.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "InProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInProgress dialog


CInProgress::CInProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CInProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInProgress)
	//}}AFX_DATA_INIT
}


void CInProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInProgress)
	DDX_Control(pDX, IDC_IN_PRG, m_cInPrg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInProgress, CDialog)
	//{{AFX_MSG_MAP(CInProgress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInProgress message handlers
