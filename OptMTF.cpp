// OptMTF.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "OptMTF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptMTF property page

IMPLEMENT_DYNCREATE(COptMTF, CPropertyPage)

COptMTF::COptMTF() : CPropertyPage(COptMTF::IDD)
{
	//{{AFX_DATA_INIT(COptMTF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->marks.Add("<FORM FLOW REQUEST> Requested flow into");
	this->marks.Add("<UNWIND - DEST FORM FOUND> ");
	//this->marks.Add("<FORM FLOW UNWIND - INITIATING> Reason:");

}

COptMTF::~COptMTF()
{
}

void COptMTF::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptMTF)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptMTF, CPropertyPage)
	//{{AFX_MSG_MAP(COptMTF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptMTF message handlers

BOOL COptMTF::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Add extra initialization here
	CListBox *pLB = (CListBox *)GetDlgItem(IDC_LST_MARK);

	for(long i = 0 ;i<this->marks.GetSize(); i++)
	{
		pLB->AddString(marks[i]);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
