// TraFile.h: interface for the CTraFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TRAFILE_H
#define AFX_TRAFILE_H

#include"stdafx.h"

//enum TRACETYPE{MOCATRACE, MTFTRACE};
class CTraDoc;
class CTraFile : public CStdioFile  
{
public:
	CTraFile();//, CTraDoc *pDoc);
	virtual ~CTraFile();

public:
	unsigned long GetOffSetForLine(long LineId);
	bool InitFile(CString fileName,CStringArray& m_strArrLines, BOOL & ShowAll, BOOL &SubMod, TRACETYPE &TT);
	bool CTraFile::ConvertToDosFormat(CString & fileName);
	unsigned long GetTotLin();
	void ShowInfo();
	bool GetLine(CString &line, long lineId);
	bool GetNextLine(CString &line, bool resetFlg);
	bool BackOneLine(CString &line);
	bool GetLines(CString &txt, long frm, long to);

private:
	long idxOfLines;
	unsigned long m_lTotLin;
	CUIntArray m_posOfLines;
	CStringArray * m_pLines;


};

#endif // !defined(AFX_TRAFILE_H__B925FB3D_BC8D_43F9_A3B2_667E17CD4B9D__INCLUDED_)
