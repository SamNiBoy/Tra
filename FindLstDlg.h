#if !defined(AFX_FINDLSTDLG_H__3248D3AA_E3D7_480C_BDB8_BBD4500C1E0C__INCLUDED_)
#define AFX_FINDLSTDLG_H__3248D3AA_E3D7_480C_BDB8_BBD4500C1E0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindLstDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindLstDlg dialog

class CFindLstDlg : public CDialog
{
// Construction
public:
	CFindLstDlg(CWnd* pParent = NULL);   // standard constructor

	CStringArray lines;
	CUIntArray linesId;
	CObArray mcmds;

// Dialog Data
	//{{AFX_DATA(CFindLstDlg)
	enum { IDD = IDD_FIND_LIST };
	CListBox	m_CLstBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindLstDlg)
	public:
	virtual void OnSetFont(CFont* pFont);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindLstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkFindLst();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBtnCpall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDLSTDLG_H__3248D3AA_E3D7_480C_BDB8_BBD4500C1E0C__INCLUDED_)
