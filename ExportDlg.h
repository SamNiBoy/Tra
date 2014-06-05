#if !defined(AFX_EXPORTDLG_H__E70B2C08_507F_4AEC_9FA7_9CE9EEC7BADC__INCLUDED_)
#define AFX_EXPORTDLG_H__E70B2C08_507F_4AEC_9FA7_9CE9EEC7BADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog

class CExportDlg : public CDialog
{
// Construction
public:
	long m_nMaxID;
	CExportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExportDlg)
	enum { IDD = IDD_FILE_EXPORT };
	BOOL	m_bExpNodeOnly;
	int		m_nFrm;
	int		m_nTo;
	CString	m_sFileName;
	BOOL	m_bSelOnly;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExportDlg)
	afx_msg void OnExportBtnOpen();
	afx_msg void OnExportChkSeloly();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTDLG_H__E70B2C08_507F_4AEC_9FA7_9CE9EEC7BADC__INCLUDED_)
