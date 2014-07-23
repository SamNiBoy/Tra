#if !defined(AFX_DLGTRANSF_H__85E43940_4EEB_4011_B857_66917E3484C8__INCLUDED_)
#define AFX_DLGTRANSF_H__85E43940_4EEB_4011_B857_66917E3484C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTransf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTransf dialog

class CDlgTransf : public CDialog
{
public:
	BYTE a1,a2,a3,a4;
// Construction
public:
	CDlgTransf(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTransf)
	enum { IDD = IDD_DLG_TRANSF };
	CIPAddressCtrl	m_cIPAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTransf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTransf)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRANSF_H__85E43940_4EEB_4011_B857_66917E3484C8__INCLUDED_)
