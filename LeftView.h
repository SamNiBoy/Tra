// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////
#include "OptDlg.h"
#include "FindDlg.h"

#if !defined(AFX_LEFTVIEW_H__20B14C43_477D_4FB6_8FDE_B8002A7C6951__INCLUDED_)
#define AFX_LEFTVIEW_H__20B14C43_477D_4FB6_8FDE_B8002A7C6951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTraDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:

// Operations
public:
	CTraDoc* GetDocument();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	boolean m_bAddItemFinished;

	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	boolean m_bShowBKMK;
	CImageList* m_imgLst;
	CString m_strText;
	int m_iFromithMcmd;
	void DoPerformance(boolean doAll);
	void SortMcmds(CObArray &ary);
	//{{AFX_MSG(CLeftView)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnFindMcmd();
	afx_msg void OnFindNxtmcmd();
	afx_msg void OnPerformAll();
	afx_msg void OnPerformSel();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowParmcmd();
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTogMcmd();
	afx_msg void OnTogBkmk();
	afx_msg void OnClrBkmk();
	afx_msg void OnTogoBkmk();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CTraDoc* CLeftView::GetDocument()
   { return (CTraDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__20B14C43_477D_4FB6_8FDE_B8002A7C6951__INCLUDED_)
