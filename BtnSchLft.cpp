// BtnSchLft.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "BtnSchLft.h"
#include "MyToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBtnSchLft

CBtnSchLft::CBtnSchLft()
{
	m_bSearchAtLeft = false;
}

CBtnSchLft::~CBtnSchLft()
{
}


BEGIN_MESSAGE_MAP(CBtnSchLft, CButton)
	//{{AFX_MSG_MAP(CBtnSchLft)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBtnSchLft message handlers

void CBtnSchLft::OnClicked() 
{
	// TODO: Add your control notification handler code here
	m_bSearchAtLeft = this->GetCheck();
	CMyToolBar * pTB=(CMyToolBar*) this->GetParent();
	pTB->m_pEdit->SetFocus();
}
