#if !defined(AFX_OPTDLG_H__914F745D_E5A1_40F5_BFF6_0A02DFFBA87F__INCLUDED_)
#define AFX_OPTDLG_H__914F745D_E5A1_40F5_BFF6_0A02DFFBA87F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptDlg dialog

class COptDlg : public CPropertyPage
{
// Construction
public:
	COptDlg();   // standard constructor

	CStringArray begs;
	CStringArray ends;

// Dialog Data
	//{{AFX_DATA(COptDlg)
	enum { IDD = IDD_OPT_MOCA };
	CListBox	m_LstEnd;
	CListBox	m_LstBeg;
	BOOL	m_bIncludeDelete;
	BOOL	m_bIncludeInsert;
	BOOL	m_bIncludeMcmd;
	BOOL	m_bIncludeSelect;
	BOOL	m_bIncludeUpdate;
	BOOL  m_bShowAll;
	BOOL  m_bShowSingle;
	CString	m_eMcmdBeg;
	CString	m_eMcmdEnd;
	int		m_iMaxLineNum;
	double	m_dThreshVal;
	BOOL	m_bSupMod;
	BOOL	m_bAlwsLines;
	//}}AFX_DATA




// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeLstBegin();
	afx_msg void OnSelchangeLstEnd();
	afx_msg void OnOptAdd();
	afx_msg void OnOptRemove();
	afx_msg void OnRadShowall();
	afx_msg void OnRadShowsingle();
	afx_msg void OnChkSupmod();
	afx_msg void OnShowAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTDLG_H__914F745D_E5A1_40F5_BFF6_0A02DFFBA87F__INCLUDED_)
