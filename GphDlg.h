#if !defined(AFX_GPHDLG_H__8AA527A4_4738_40BD_9A02_A736DDF94FB8__INCLUDED_)
#define AFX_GPHDLG_H__8AA527A4_4738_40BD_9A02_A736DDF94FB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GphDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGphDlg dialog

class CGphDlg : public CDialog
{
// Construction
public:
	CTraDoc * m_pDoc;
	CMcmd * m_RootMcmd;
	CGphDlg(CWnd* pParent = NULL);   // standard constructor

	int m_iCurScrollPos;
	int m_iPageSize;
	int m_iLineSize;
	int m_iMcmdHSize;
	int m_iMcmdWSize;
	int m_iMaxSize;

	int m_iMrgTop;
	int m_iMrgLeft;
	int m_iMrgRight;
	int m_iMrgBottom;

// Dialog Data
	//{{AFX_DATA(CGphDlg)
	enum { IDD = IDD_DLG_GRAPH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGphDlg)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPHDLG_H__8AA527A4_4738_40BD_9A02_A736DDF94FB8__INCLUDED_)
