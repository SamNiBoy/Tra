#if !defined(AFX_COLORDLG_H__8449CA4F_6D08_4A20_B7B4_8A3BE415525D__INCLUDED_)
#define AFX_COLORDLG_H__8449CA4F_6D08_4A20_B7B4_8A3BE415525D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog
enum SELECTION{RANGE,BEYOND,ERR,MCMD,SELECT,UPDATE,INSERT,DEL,LPCOLOR,RPCOLOR,VALUE,PARAMETER,ARGUMENT,PUBLISH};
class CColorDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CColorDlg)

// Construction
public:
	void ReColoring();
	void SetTextFont();
	void UpdateColor();
	void ColoringSelection(SELECTION sel);
	CColorDlg();
	~CColorDlg();

	SELECTION m_eSelected;
// Dialog Data
	//{{AFX_DATA(CColorDlg)
	enum { IDD = IDD_OPT_COLOR };
	int		m_iB;
	int		m_iG;
	int		m_iR;
	CString	m_sLPTxt;
	CString	m_sRPTxt;
	//}}AFX_DATA

	COLORREF m_RANGEClr;
	COLORREF m_BEYONDClr;
	COLORREF m_ERRClr;
	COLORREF m_MCMDClr;
	COLORREF m_SELECTClr;
	COLORREF m_UPDATEClr;
	COLORREF m_INSERTClr;
	COLORREF m_DELClr;
	COLORREF m_LPCOLORClr;
	COLORREF m_RPCOLORClr;
	COLORREF m_VALUEClr;
	COLORREF m_PARAMETERClr;
	COLORREF m_ARGUMENTClr;
	COLORREF m_PUBLISHClr;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CColorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorDlg)
	afx_msg void OnRDArgument();
	afx_msg void OnRDDelete();
	afx_msg void OnRDInsert();
	afx_msg void OnRDLPColor();
	afx_msg void OnRDMcmd();
	afx_msg void OnRDParameter();
	afx_msg void OnRDPublish();
	afx_msg void OnRDRange();
	afx_msg void OnRDRPColor();
	afx_msg void OnRDSelect();
	afx_msg void OnRDUpdate();
	afx_msg void OnRDValue();
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSldB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSldB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySldG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSldG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSldG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSldR(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSldR(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnReset();
	afx_msg void OnRDBeyond();
	afx_msg void OnRDError();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORDLG_H__8449CA4F_6D08_4A20_B7B4_8A3BE415525D__INCLUDED_)
