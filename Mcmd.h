// Mcmd.h: interface for the CMcmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCMD_H__5008E09A_95FD_4E10_9C9A_AFAD73121BB6__INCLUDED_)
#define AFX_MCMD_H__5008E09A_95FD_4E10_9C9A_AFAD73121BB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMcmd : public CObject  
{
public:
	int ID;
	CMcmd *Parent;
	CString mcmd;
	int level;
	long beg_time_stmp, end_time_stmp;
	long beglin;
	long endlin;
	int mcmdTyp; //1.mcmd, 3. select, 4. update 5. insert 6.delete
public:
	bool m_bBookMarked;
	CString m_Subfix;
	CString m_Prefix;
	void DrawSelf(CDC *pDC, CRect &rt);
	void SetDspStype();
	BOOL m_Bold;
	COLORREF m_TxtColor;

	boolean OverTimeWeight(long tot_period_of_trace, double thresh_hld, long totlinnum);
	void GetTimeStamp(CString line, boolean beg_flg);
	CMcmd();
	virtual ~CMcmd();

};

#endif // !defined(AFX_MCMD_H__5008E09A_95FD_4E10_9C9A_AFAD73121BB6__INCLUDED_)
