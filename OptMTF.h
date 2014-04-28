#if !defined(AFX_OPTMTF_H__DC9D732B_DA5A_46B4_9F8D_7348B4036180__INCLUDED_)
#define AFX_OPTMTF_H__DC9D732B_DA5A_46B4_9F8D_7348B4036180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptMTF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptMTF dialog

class COptMTF : public CPropertyPage
{
	DECLARE_DYNCREATE(COptMTF)

// Construction
public:
	COptMTF();
	~COptMTF();

	CStringArray marks;
// Dialog Data
	//{{AFX_DATA(COptMTF)
	enum { IDD = IDD_OPT_MTF };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COptMTF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COptMTF)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTMTF_H__DC9D732B_DA5A_46B4_9F8D_7348B4036180__INCLUDED_)
