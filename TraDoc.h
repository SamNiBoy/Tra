// TraDoc.h : interface of the CTraDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef AFX_TRADOC_H
#define AFX_TRADOC_H

#include"mcmd.h"
#include"TraFile.h"
#include"OptDlg.h"
#include"optmtf.h"
#include"colorDlg.h"

#include<afxrich.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRichEditDoc;
class CTraFile;

class CTraDoc : public CDocument
{
protected: // create from serialization only
	CTraDoc();
	DECLARE_DYNCREATE(CTraDoc)

// Attributes
public:

CObArray m_ObjArrMcmds;
CMapPtrToPtr m_MpMcmd_To_hHreeItem;
CMapPtrToPtr m_MHreeItem_To_Mcmd;
CStringArray m_strArrLines;
COptDlg * m_OptMoca;
COptMTF * m_OptMtf;
CColorDlg * m_OptColor;
CPropertySheet *m_pSheet;
CTraFile * m_pf;
TRACETYPE m_trcTyp;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTraDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
	//}}AFX_VIRTUAL

// Implementation
public:
	
	int m_bRefountRPanel;
	int ParseLineForMTF(CString line, CString &mcmd);
	void ExactMcmdForMTF();
	BOOL m_bNewFileFlg;
	CString m_sFileName;
	void OpenFile(CString &fileName);
	int ParseLine(CString line ,CString &mcmd);
	void ClearDoc();
	long m_iFocusMcmd;
	void UpdateView();
	void ExactMcmd();
	virtual ~CTraDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTraDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnOptSetting();
	afx_msg void OnRefreshView();
	afx_msg void OnUpdateRefreshView(CCmdUI* pCmdUI);
	afx_msg void OnShowSelect();
	afx_msg void OnUpdateShowSelect(CCmdUI* pCmdUI);
	afx_msg void OnShowDelete();
	afx_msg void OnUpdateShowDelete(CCmdUI* pCmdUI);
	afx_msg void OnShowMcmd();
	afx_msg void OnUpdateShowMcmd(CCmdUI* pCmdUI);
	afx_msg void OnShowInsert();
	afx_msg void OnUpdateShowInsert(CCmdUI* pCmdUI);
	afx_msg void OnShowUpdate();
	afx_msg void OnUpdateShowUpdate(CCmdUI* pCmdUI);
	afx_msg void OnShowAll();
	afx_msg void OnUpdateShowAll(CCmdUI* pCmdUI);
	afx_msg void OnShowGrph();
	afx_msg void OnShowBkmk();
	afx_msg void OnUpdateShowBkmk(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnFileTrnsf();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	unsigned long CalEndLinId();
	unsigned long CalBegLinId();
	void OnSelectChanged(CMcmd *SelectMcmd);
	unsigned long m_EndLinId;
	unsigned long m_BegLinId;
private:
	bool IsDosFormat(CString &filename);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRADOC_H__4D467D98_1E5F_437F_ADC9_BD9860C6DFA8__INCLUDED_)
