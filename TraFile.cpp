// TraFile.cpp: implementation of the CTraFile class.
//
//////////////////////////////////////////////////////////////////////
#include"stdafx.h"
//#include "TraDoc.h"
#include "TraFile.h"

#include "Util.h"
#include<iostream>
#include "InProgress.h"
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTraFile::CTraFile()
{
	idxOfLines = 0;
}


CTraFile::~CTraFile()
{
    m_posOfLines.RemoveAll();
}

bool CTraFile::GetLine(CString &line, long lineId)
{

	if (m_pLines->GetSize() == 0)
	{
	    if (lineId > m_posOfLines.GetSize())
		{
		    line = "";
		    return false;
		}

	    unsigned long pos = m_posOfLines[lineId-1];

	    Seek(pos, SEEK_SET);

        if (!ReadString(line))
		{
		    line = "";
	    	return false;
		}
	    return true;
	}
	else if (m_pLines->GetSize() > 0)
	{
     	if (lineId > m_pLines->GetSize())
		{
		    line = "";
		    return false;
		}
		line = (*m_pLines)[lineId - 1];
		return true;
	}
	return false;
}

bool CTraFile::GetNextLine(CString &line, bool resetFlg)
{
	if (m_pLines->GetSize() == 0)
	{
	    if (resetFlg)
		{
		Seek(0, SEEK_SET);
		}

	    if (!ReadString(line))
		{
		    line = "";
		    return false;
		}
	    return true;
	}
	else if (m_pLines->GetSize() > 0)
	{

		if (resetFlg)
			idxOfLines = 0;
		if (idxOfLines >= m_pLines->GetSize())
		{
			line = "";
			return false;
		}

		line = (*m_pLines)[idxOfLines];
		idxOfLines++;
		return true;
	}
	return false;
}

bool CTraFile::BackOneLine(CString &line)
{
	if (m_pLines->GetSize() == 0)
	{
	    /* 2 means '\r\n' */
      	Seek(-(line.GetLength() + 2), SEEK_CUR);
	}
	else
	{
		idxOfLines--;
	}
	    return true;
}

bool CTraFile::GetLines(CString &txt, long frm, long to)
{

	CString line = "";

	txt = "";

	if (m_pLines->GetSize() == 0)
	{

    	if (frm < 1)
	    	frm = 1;

	    if (to > m_posOfLines.GetSize())
		    to = m_posOfLines.GetSize();

	    Seek(m_posOfLines[frm - 1], SEEK_SET);

	    ASSERT(frm <= to);

	     ULONGLONG TotLen, begpos = m_posOfLines[frm-1], endpos;

    	endpos = to < m_posOfLines.GetSize() ? m_posOfLines[to] : GetLength();

    	TotLen = endpos - begpos;

    	/* Because 'Read' function will take '\r\n' as 1 char */
    	TotLen -= (to - frm + 1);

    	TCHAR *buf = new TCHAR[TotLen + 1];
    	memset(buf, 0, sizeof buf);
    	//ReadHuge(buf, TotLen);
    	buf[TotLen] = '\0';
    	txt.Format("%s", buf);
    	delete buf;
     	return true;
	}
	else if (m_pLines->GetSize() > 0)
	{
		 /*if (to - frm > 5000)
		 {
			 CString fn(GetFilePath());
			 CFile file(fn, CFile::modeRead);
	         long TotLen, begpos = m_posOfLines[frm-1], endpos;

    	     endpos = to < m_posOfLines.GetSize() ? m_posOfLines[to] : GetLength();

    	     TotLen = endpos - begpos;
    	     TotLen -= (to - frm + 1);

    	     TCHAR *buf = new TCHAR[TotLen + 1];
    	     memset(buf, 0, sizeof buf);
    	     file.ReadHuge(buf, TotLen);
    	     buf[TotLen] = '\0';
    	     txt.Format("%s", buf);
    	     delete buf;
			 file.Close();
			 return true;
		 }*/

		long totLen = ((to >= m_posOfLines.GetSize()) ? m_posOfLines[m_lTotLin-1] : m_posOfLines[to]) - m_posOfLines[frm-1];
		txt.GetBuffer(totLen);

		 for (long i = frm ; i <= to; i++)
		 {
		     txt += (*m_pLines)[i-1] + "\r\n";
		 }
		 return true;
	}
	return false;
}

void CTraFile::ShowInfo()
{
	cout<<"Information of file: "<< this->GetFileName() <<endl;
	cout<<"Total Lines: "<<m_lTotLin<<endl;
	cout<<"Get line 1, 5, 10..."<<endl;
	CString line;
	GetLine(line, 1);
	cout<<"Line 1:"<<line<<endl;

	GetLine(line, 5);
	cout<<"Line 5:"<<line<<endl;

	GetLine(line, 10);
	cout<<"Line 10:"<<line<<endl;

	cout<<"Get lines from 2-10: "<<endl;

	GetLines(line, 2, 10);

	cout<<"Lines[2-10]: ["<<line <<"]";

	cout<<"Now print the file:"<<endl;

	GetNextLine(line, true);

	int tot = 15, id = 0;
	while(line.GetLength()>0)
	{
		cout<<line<<endl;
		if ((id+1) %3 == 0)
		    BackOneLine(line);
		GetNextLine(line, false);
		id++;
		if(id>=tot)
			break;
	}

	for(unsigned long i = 0; i < m_lTotLin && i < 15; i++)
	{
		cout<<"Line:["<<i+1<<"], Pos:["<<m_posOfLines[i]<<"]"<< endl;
	}
}

unsigned long CTraFile::GetTotLin()
{
    return m_lTotLin;
}

bool CTraFile::ConvertToDosFormat(CString & fileName)
{
	CFile fin, fout;

	int dotPos = fileName.Find(".");
	int strLen = dotPos > 0 ? dotPos : fileName.GetLength();

	CString fileOut = fileName.Left(strLen) + "_dos.log";
	
	if (!fin.Open(fileName, CFile::modeRead))
	{
		//cout<<"Can not open file "<<fileName<<endl;
		exit(0);
	}
	
	
	if (!fout.Open(fileOut, CFile::modeCreate|CFile::modeWrite))
	{
		//cout<<"Can not open file "<<fileName<<endl;
		exit(0);
	}

	char *c = (char*)malloc(1024 * 1024 + 1);
	memset(c,0, 1024 * 10 + 1);
    char outLine[10000];
	memset(outLine,0, sizeof(outLine));
	//Seek to skip first 4 chars which defines file format.
	//strcpy(outLine,"CVRT");
	ULONGLONG fileSize = fin.GetLength();

    CInProgress *pPrg = new CInProgress;
	pPrg->Create(IDD_IN_PROGRESS, ::AfxGetApp()->GetMainWnd());
	pPrg->SetOwner(::AfxGetApp()->GetMainWnd());
	pPrg->CenterWindow();
	pPrg->ShowWindow(SW_SHOW);
	pPrg->m_cInPrg.SetRange(0,100);

	long j = 0, i = 0;
	long n = 0, cnt = 0;
	while(n = fin.Read(c, 1024 * 10))
	{

		for (i = 0; i < n; i++)
		{
		    if (c[i] == 13)
		    {
			//fin.Seek(-3, SEEK_CUR);
			//fin.Write(" \r\n",3);
			//fin.Seek(3, SEEK_CUR);
			strcat(outLine, "\r\n");
			fout.Write(outLine, strlen(outLine));
			memset(outLine, 0, sizeof(outLine));
			j = 0;
		   }
		   else
		   {
			   outLine[j++] = c[i];
			//strcat(outLine, c);
		   }
		}

		cnt+= i;
	
		//memset(c,0, sizeof(c));
		if (cnt % 1000 == 0)
		{
			pPrg->m_cInPrg.SetPos((int)(cnt *1.0/fileSize*100.0));
			pPrg->m_cInPrg.SetActiveWindow();
		}
	}
	fin.Close();
	fout.Close();
	//fileName = newFileName;
	fileName = fileOut;
    pPrg->ShowWindow(SW_HIDE);
	delete c;
	delete pPrg;
	return true;
}

bool CTraFile::InitFile(CString fileName,
						CStringArray & Lines, 
						BOOL & ShowAll, 
						BOOL &SupMod, 
						TRACETYPE & trcTyp)
{
	m_pLines = & Lines;

	if (!Open(fileName, CFile::modeRead))
	{
		//cout<<"Can not open file "<<fileName<<endl;
		exit(0);
	}

	CString line;

    ULONGLONG pos, fileSize = GetLength();

	BOOL doSupMod = false;

	doSupMod = SupMod;

	if (!doSupMod)
	{
		if (fileSize >= 500 * 1024 * 1024)
		{
			if(::AfxMessageBox("File is over 500M, turn super file mode flag on?", MB_YESNO|MB_ICONINFORMATION) == IDYES)
			{
				SupMod = doSupMod = true;
			}

	        if(ShowAll)
			{
	            ShowAll = false;
			}
		}
	}

	if (doSupMod)
	{
	   Lines.RemoveAll();
	   m_posOfLines.RemoveAll();
	   //m_posOfLines.SetSize(fileSize /100);
	   long lineId = 0;
	   pos = GetPosition();
	    while(ReadString(line))
		{
	        if(trcTyp != MTFTRACE && line.GetLength()>0 && line.Find("CTerminalInputReader") >= 0)
			{
	            trcTyp = MTFTRACE;
			}

	        m_posOfLines.InsertAt(lineId, pos);
	        pos = GetPosition();
	        lineId++;
		}

	    m_lTotLin = m_posOfLines.GetSize(); 
	}
	else {
		m_lTotLin = 0;
		Lines.RemoveAll();
		m_posOfLines.RemoveAll();
		//m_posOfLines.SetSize(fileSize /100);
		//Lines.SetSize(fileSize /100);
		pos = GetPosition();

	    while(ReadString(line))
		//while(CUtil::ReadLineFromFile((CStdioFile &)*this, line))
		{
		    if(trcTyp != MTFTRACE && line.GetLength()>0 && line.Find("CTerminalInputReader") >= 0)
			{
	    	    trcTyp = MTFTRACE;
			}
			m_posOfLines.InsertAt(m_lTotLin, pos);
			pos = GetPosition();
			Lines.InsertAt(m_lTotLin, line);
			m_lTotLin++;
		}
	}
    return true;
}

unsigned long CTraFile::GetOffSetForLine(long LineId)
{
	if (LineId > m_posOfLines.GetSize())
		return m_lTotLin;

	unsigned long pos = m_posOfLines[LineId-1];
    return pos;
}
