#if !defined(AFX_BTNSCHLFT_H__92FF8B1A_861C_41EB_8231_139AE99A5F4A__INCLUDED_)
#define AFX_BTNSCHLFT_H__92FF8B1A_861C_41EB_8231_139AE99A5F4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BtnSchLft.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBtnSchLft window

class CBtnSchLft : public CButton
{
// Construction
public:
	CBtnSchLft();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBtnSchLft)
	//}}AFX_VIRTUAL

// Implementation
public:
	boolean m_bSearchAtLeft;
	virtual ~CBtnSchLft();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBtnSchLft)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNSCHLFT_H__92FF8B1A_861C_41EB_8231_139AE99A5F4A__INCLUDED_)
