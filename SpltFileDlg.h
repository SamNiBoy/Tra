#if !defined(AFX_SPLTFILEDLG_H__2C52193B_89E4_4E97_9116_F21D06E6248F__INCLUDED_)
#define AFX_SPLTFILEDLG_H__2C52193B_89E4_4E97_9116_F21D06E6248F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpltFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpltFileDlg dialog

class CSpltFileDlg : public CDialog
{
// Construction
public:
	void SplitFileWithThread();
	CSpltFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpltFileDlg)
	enum { IDD = IDD_DLG_SPLT_FILE };
	CString	m_splt_file_name;
	int		m_split_size;
	BOOL	m_splt_thrd_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpltFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpltFileDlg)
	afx_msg void OnSplitOpenFile();
	afx_msg void OnFileSplit();
	afx_msg void OnSpltFileStart();
	afx_msg void OnChkThdSplt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SplitFileWithSize();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLTFILEDLG_H__2C52193B_89E4_4E97_9116_F21D06E6248F__INCLUDED_)
