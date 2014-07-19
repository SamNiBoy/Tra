// Tra.h : main header file for the TRA application
//

#if !defined(AFX_TRA_H__AB414070_43B9_4044_B519_C46A6812DEB9__INCLUDED_)
#define AFX_TRA_H__AB414070_43B9_4044_B519_C46A6812DEB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "tradoc.h"

/////////////////////////////////////////////////////////////////////////////
// CTraApp:
// See Tra.cpp for the implementation of this class
//

class CTraApp : public CWinApp
{
public:

	void ReadOptionsFromINI(CTraDoc * pDoc);
	void WriteOptionsToINI(CTraDoc *);
	CTraApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTraApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTraApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHideApp();
	afx_msg void OnShowApp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRA_H__AB414070_43B9_4044_B519_C46A6812DEB9__INCLUDED_)
