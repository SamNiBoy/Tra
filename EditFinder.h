#if !defined(AFX_EDITFINDER_H__A962AEF2_E2BC_4B28_8A65_3AA3993D7D5E__INCLUDED_)
#define AFX_EDITFINDER_H__A962AEF2_E2BC_4B28_8A65_3AA3993D7D5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditFinder.h : header file
//
#include"findlstdlg.h"
/////////////////////////////////////////////////////////////////////////////
// CEditFinder window

class CEditFinder : public CEdit
{
// Construction
public:
	CEditFinder();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditFinder)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFindLstDlg * m_pFindLstDlg;
	virtual ~CEditFinder();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditFinder)
	afx_msg void OnChange();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFINDER_H__A962AEF2_E2BC_4B28_8A65_3AA3993D7D5E__INCLUDED_)
