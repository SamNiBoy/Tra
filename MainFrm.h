// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7D006E51_6010_4113_8314_E642F769E997__INCLUDED_)
#define AFX_MAINFRM_H__7D006E51_6010_4113_8314_E642F769E997__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mytoolbar.h"

class CTraView;

class CMainFrame : public CFrameWnd
{
friend class CTraView;	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:
	BOOLEAN StartThreadForAcceptFile();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	boolean m_bSearchShwFlg;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMyToolBar    m_wndMyToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFindNxtmcmd();
	afx_msg void OnViewToolbar();
	afx_msg void OnUpdateViewToolbar(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePerformAll(CCmdUI* pCmdUI);
	afx_msg void OnPerformAll();
	afx_msg void OnPerformSel();
	afx_msg void OnUpdatePerformSel(CCmdUI* pCmdUI);
	afx_msg void OnShowParmcmd();
	afx_msg void OnUpdateShowParmcmd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateINDMcmd(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnPaint();
	afx_msg void OnFileSplit();
	afx_msg LRESULT OnOpenTrnsfFile(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7D006E51_6010_4113_8314_E642F769E997__INCLUDED_)
