#if !defined(AFX_INPROGRESS_H__8A76B801_0EE4_4717_8AB4_500CDCC331C3__INCLUDED_)
#define AFX_INPROGRESS_H__8A76B801_0EE4_4717_8AB4_500CDCC331C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInProgress dialog

class CInProgress : public CDialog
{
// Construction
public:
	CInProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInProgress)
	enum { IDD = IDD_IN_PROGRESS };
	CProgressCtrl	m_cInPrg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInProgress)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPROGRESS_H__8A76B801_0EE4_4717_8AB4_500CDCC331C3__INCLUDED_)
