// SpltFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "SpltFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpltFileDlg dialog


CSpltFileDlg::CSpltFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpltFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpltFileDlg)
	m_splt_file_name = _T("");
	m_split_size = 400;
	m_splt_thrd_id = FALSE;
	//}}AFX_DATA_INIT
}


void CSpltFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpltFileDlg)
	DDX_Text(pDX, IDC_EDT_SPLIT_FILE_NAME, m_splt_file_name);
	DDX_Text(pDX, IDC_EDT_SPLIT_SIZE, m_split_size);
	DDX_Check(pDX, IDC_CHK_THD_SPLT, m_splt_thrd_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpltFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSpltFileDlg)
	ON_BN_CLICKED(IDC_SPLIT_OPEN_FILE, OnSplitOpenFile)
	ON_COMMAND(ID_FILE_SPLIT, OnFileSplit)
	ON_BN_CLICKED(ID_SPLT_FILE_START, OnSpltFileStart)
	ON_BN_CLICKED(IDC_CHK_THD_SPLT, OnChkThdSplt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpltFileDlg message handlers

void CSpltFileDlg::OnSplitOpenFile() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFilters[]= _T("Moca trace files (*.log)|*.log|Mtf trace files (*.out)|*.out|All files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("log"), _T("*.log"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters);

	if(dlg.DoModal()!=IDOK)
		return;

	m_splt_file_name = dlg.GetPathName();
	this->UpdateData(false);
}

void CSpltFileDlg::OnFileSplit() 
{
	// TODO: Add your command handler code here
	CSpltFileDlg *p = new CSpltFileDlg;
	p->DoModal();
	delete p;
}

void CSpltFileDlg::OnSpltFileStart() 
{

	if (m_splt_thrd_id)
	{
		SplitFileWithThread();
	}
	else
	{
		SplitFileWithSize();
	}
}

void CSpltFileDlg::OnChkThdSplt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CWnd *pSize = this->GetDlgItem(IDC_EDT_SPLIT_SIZE);
	if (m_splt_thrd_id)
	{
		pSize->EnableWindow(FALSE);
	}
	else
	{
		pSize->EnableWindow(TRUE);
	}
}

void CSpltFileDlg::SplitFileWithSize()
{
	CString msg;

	this->UpdateData(true);

	if (m_splt_file_name.GetLength() <= 0)
	{
        msg.Format("Please specify which file to split!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}
	CStdioFile file;
	if(!file.Open(m_splt_file_name, CFile::modeRead))
	{
        msg.Format("Can not open file:" + m_splt_file_name + "!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}
	DWORD sz = m_split_size * 1024 * 1024;

	m_splt_file_name.MakeLower();
	int n = m_splt_file_name.Find(".log");

	if (n < 0)
	    n = m_splt_file_name.Find(".out");

	if (n < 0)
	{
        msg.Format("File " + m_splt_file_name + " must be suffixed with .log or .out!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}

	CString sub_file_name = m_splt_file_name;
	CString sufix = ".log";
	if (n >= 0)
	{
		sub_file_name = m_splt_file_name.Left(n);
		sufix = m_splt_file_name.Right(m_splt_file_name.GetLength()-n);
    	//::AfxMessageBox(sufix);
	}
	DWORD totsz = file.GetLength();

	int subFiles = totsz / sz + (totsz%sz == 0 ? 0 : 1);

	CStdioFile Writer;
	bool finishedFile = false;

	for (int i=0 ; i<subFiles && !finishedFile; i++)
	{
		CString fn;
		fn.Format("%s_splt%d%s", sub_file_name, i, sufix);

		//::AfxMessageBox("Open " + fn);
		if (!Writer.Open(fn, CFile::modeCreate|CFile::modeWrite))
		{
			::AfxMessageBox("Can not create file: " + fn, MB_OK);
			file.Close();
			return;
		}

		CString line;

		//::AfxMessageBox("Before " + fn);
		for (DWORD j = 0; j<sz; j += line.GetLength())
		{
			if (!file.ReadString(line))
			{
				finishedFile = true;
				break;
			}

			Writer.WriteString(line+"\n");
		}
		Writer.Close();
		//::AfxMessageBox("After " + fn);
	}
	file.Close();

	
	msg.Format("Split into %d files successfully!", (i<subFiles? i: subFiles));
	::AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
}

void CSpltFileDlg::SplitFileWithThread()
{
	CString msg;
	CStdioFile file;

	if (m_splt_file_name.GetLength() <= 0)
	{
        msg.Format("Please specify which file to split!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}

	if(!file.Open(m_splt_file_name, CFile::modeRead))
	{
        msg.Format("Can not open file:" + m_splt_file_name + "!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}

	m_splt_file_name.MakeLower();
	int n = m_splt_file_name.Find(".log");

	if (n < 0)
		n = m_splt_file_name.Find(".out");

	if (n < 0)
	{
        msg.Format("File " + m_splt_file_name + " must be suffixed with .log or .out!");
	    ::AfxMessageBox(msg, MB_OK|MB_ICONERROR);
		return;
	}

	CString sub_file_name = m_splt_file_name;
	CString sufix = ".log";
	if (n >= 0)
	{
		sub_file_name = m_splt_file_name.Left(n);
		sufix = m_splt_file_name.Right(m_splt_file_name.GetLength()-n);
    	//::AfxMessageBox(sufix);
	}

	CMapStringToOb tTof;
	CString line;
	CString threadId = "", pre_threadId = "0NoThread"; //as default.
	CStdioFile *pWrite = NULL;
	int idx;
	
	while (file.ReadString(line))
	{
		idx = line.Find(' ', 1);

		if (line == "2924 8ed5 D 18:20:36,458 (DefaultSer) [0] Parsed command")
			idx = idx;


		if (idx > 0)
		{
			threadId = line.Left(idx);
			threadId.TrimLeft();
			threadId.TrimRight();
			//If find '-' which means it's a date like '2014-06-10', so we should
			//get thread ID from: "2014-06-10 09:05:53,198 DEBUG [142 fea0] Argument..."
			if (threadId.Find('-') >=0)
			{
				threadId = "";
				idx = line.Find('[');
				if (idx >=0 )
				{
					int idx2 = line.Find(' ',idx);
					if (idx2 >=0 && idx2 > idx)
					{
						threadId = line.Left(idx2);
						threadId = threadId.Right(threadId.GetLength() - idx -1);
					}
				}
			}
		}

		if (threadId.GetLength()<= 0)
			threadId = pre_threadId;

		if (!(threadId[0] >= '0' && threadId[0] <= '9'))
			threadId = pre_threadId;

		//::AfxMessageBox("Getting thread: "+threadId);

		if (pre_threadId != threadId)
		{
			pWrite = NULL;
		    tTof.Lookup(threadId, (CObject*&)pWrite);
			pre_threadId = threadId;
		}

		if (pWrite == NULL)
		{
			CString fn = sub_file_name + "_thread" + threadId + sufix;
			pWrite = new CStdioFile();
			if (!pWrite->Open(fn, CFile::modeCreate|CFile::modeWrite))
			{
			    ::AfxMessageBox("Can not create file: " + fn, MB_OK);
			    file.Close();
			    return;
			}
			tTof.SetAt(threadId, pWrite);
			pre_threadId = threadId;
		}
		pWrite->WriteString(line + "\n");
	}

	file.Close();

	POSITION pos = tTof.GetStartPosition();

	int cnt = 0;
	while(pos)
	{
		pWrite = NULL;
		tTof.GetNextAssoc(pos, threadId, (CObject*&)pWrite);
		if (pWrite)
		{
			cnt++;
			pWrite->Close();
		}
	}

	msg.Format("Split into %d files successfully!", cnt);
	::AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
}
