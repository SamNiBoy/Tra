// TraView.h : interface of the CTraView class
//
/////////////////////////////////////////////////////////////////////////////
#include<afxrich.h>
#include"mcmd.h"
#if !defined(AFX_TRAVIEW_H__E2702514_7968_45E3_A43C_FB4631393E83__INCLUDED_)
#define AFX_TRAVIEW_H__E2702514_7968_45E3_A43C_FB4631393E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTraView : public CRichEditView
{
protected: // create from serialization only
	CTraView();
	DECLARE_DYNCREATE(CTraView)

// Attributes
public:
	CTraDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTraView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DecorateKeyWord(long begpos, long endpos);
	void ScorllToMcmd();
	void UndecoratePreMcmd();
	void DecorateMcmd(CMcmd *pMcmd);
	void LoadText();
	void UpdateStatuBar();
	void HighLightMcmd(CMcmd *pPreMcmd, CMcmd * pMcmd);
	CString m_KeyWord;
	void DecorateInterested(CMcmd * pMcmd);

	virtual ~CTraView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTraView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFindRight();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMcmd * m_preMcmd;
};

#ifndef _DEBUG  // debug version in TraView.cpp
inline CTraDoc* CTraView::GetDocument()
   { return (CTraDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAVIEW_H__E2702514_7968_45E3_A43C_FB4631393E83__INCLUDED_)
