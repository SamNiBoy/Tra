#if !defined(AFX_MYTOOLBAR_H__45E775F0_4323_47DB_9388_B899BE49D200__INCLUDED_)
#define AFX_MYTOOLBAR_H__45E775F0_4323_47DB_9388_B899BE49D200__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyToolBar.h : header file
//
#include "EditFinder.h"
#include "BtnSchLft.h"
/////////////////////////////////////////////////////////////////////////////
// CMyToolBar window

class CMyToolBar : public CToolBar
{
// Construction
public:
	CMyToolBar();

// Attributes
public:

// Operations
public:

	CEditFinder *m_pEdit;
	CBtnSchLft *m_pBtn;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyToolBar();
	void ToolbarSerachLeft();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLBAR_H__45E775F0_4323_47DB_9388_B899BE49D200__INCLUDED_)
