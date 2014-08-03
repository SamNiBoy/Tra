// RcvFileSocket.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "RcvFileSocket.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRcvFileSocket

CRcvFileSocket::CRcvFileSocket()
{
	m_bStartTrn = false;
}

CRcvFileSocket::~CRcvFileSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CRcvFileSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CRcvFileSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CRcvFileSocket member functions

void CRcvFileSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CString a;
	unsigned int p;

	this->GetPeerName(a, p);

	CString s;
	s.Format("Looks Client %s, %d disconnected!", a, p);

	AfxMessageBox(s);

	CAsyncSocket::OnClose(nErrorCode);
}

void CRcvFileSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString file_name;
	memset(m_szBuffer, 0, sizeof(m_szBuffer));
	m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer));

	if (m_bStartTrn == false && m_nLength > 0)
	{
		CString PA;
		unsigned int PO;
		GetPeerName(PA, PO);
			CString s;
			s.Format("[%s] send file %s to you, accept?", (LPCSTR)PA, m_szBuffer);
			if (AfxMessageBox(s, MB_YESNO|MB_ICONQUESTION) != IDYES)
			{
				memset(m_szBuffer, 0, sizeof m_szBuffer);
				sprintf(m_szBuffer, "REFUSE");
			}
			else
			{
				memset(m_szBuffer, 0, sizeof m_szBuffer);
				sprintf(m_szBuffer, "ACCEPT");

				m_bStartTrn = true;

				TCHAR szFilters[]= _T("Moca trace files (*.log)|*.log|Mtf trace files (*.out)|*.out|All files (*.*)|*.*||");
	            CFileDialog dlg(FALSE, _T("log"), _T("*.log"), OFN_HIDEREADONLY,szFilters);

	            if(dlg.DoModal()!=IDOK)
	         	    return;

	             file_name = dlg.GetPathName();
				 if (!m_fileToSave.Open(file_name, CFile::modeCreate|CFile::modeWrite))
				 {
					 s.Format("Can not write file %s", (LPCSTR)file_name);

					 AfxMessageBox(s, MB_OK|MB_ICONERROR);
					 sprintf(m_szBuffer, "REFUSE");
				 }
				 else 
					 m_bStartTrn = true;
			}
			AsyncSelect(FD_WRITE);
			return;
	}

	if (m_nLength)
	{
		if (strcmp(m_szBuffer, "FINISHED") == 0)
			//AfxMessageBox("FINISHED GOT");
		{
			m_fileToSave.Close();
			this->Close();
			CString s;

			

					 s.Format("Open file [%s] with trace digger?", (LPCSTR)m_fileToSave.GetFilePath());
			         if (AfxMessageBox(s, MB_YESNO|MB_ICONQUESTION) == IDYES)
					 {
						 
						 CMainFrame *pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;

						 CView * active = pMain->GetActiveView();

						 CTraDoc *pDoc = (CTraDoc*) active->GetDocument();

						 pDoc->m_sFileName = m_fileToSave.GetFilePath();

						 pMain->PostMessage(WM_OPENTRANFILE);
						 //pDoc->OpenFile(fn);
						 //AfxGetApp()->PostThreadMessage(WM_OPENTRANFILE, 0, 0);

					 }
			return;
		}
		else
		{
			CString s;
			s.Format("%s", m_szBuffer);
			m_fileToSave.WriteString(s);
		}
	}

	AsyncSelect(FD_READ);

	CAsyncSocket::OnReceive(nErrorCode);
}

void CRcvFileSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//char buff[4096];

	m_nLength = strlen(m_szBuffer);
	Send(m_szBuffer, m_nLength, 0);
	memset(m_szBuffer, 0, sizeof m_szBuffer);

	if (m_bStartTrn)
	{
	    AsyncSelect(FD_READ);
	}

	CAsyncSocket::OnSend(nErrorCode);
}

void CRcvFileSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!nErrorCode)
	{
		this->AsyncSelect(FD_READ);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
