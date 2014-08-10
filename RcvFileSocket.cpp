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
	m_szBuffer = NULL;
	m_totToRcvLen = 0;
	m_totRcvedLen = 0;
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
	
	if (!m_bStartTrn)
	{
	    memset(ackmsg, 0, sizeof(ackmsg));
	    m_nLength = Receive(ackmsg, sizeof(ackmsg));
		ackmsg[m_nLength] = '\0';
	}
	else
	{
		while(m_totRcvedLen < m_totToRcvLen)
		{
			if((m_nLength = Receive(m_szBuffer + m_totRcvedLen, m_totToRcvLen - m_totRcvedLen)) == SOCKET_ERROR)
			{
				if (GetLastError() == WSAEWOULDBLOCK)
					break;
				else
				{
					AfxMessageBox("Socket failed to receive!");
					return;
				}
			}
			//m_szBuffer[m_totRcvedLen + m_nLength] = '\0';
			m_totRcvedLen += m_nLength;
		}
	}

	if (m_bStartTrn == false && m_nLength > 0)
	{
		CString PA;
		unsigned int PO;
		GetPeerName(PA, PO);
			CString s;
			s.Format("[%s] send file %s to you, accept?", (LPCSTR)PA, ackmsg);
			if (AfxMessageBox(s, MB_YESNO|MB_ICONQUESTION) != IDYES)
			{
				memset(ackmsg, 0, sizeof ackmsg);
				sprintf(ackmsg, "REFUSE");
			}
			else
			{
				char *p = strstr(ackmsg, "size:");
				p = p+5;
				m_totToRcvLen = atol(p);
				CString mg;
				mg.Format("size is [%u]\n", m_totToRcvLen);

				//AfxMessageBox(mg);

				if (m_szBuffer)
					delete m_szBuffer;

				m_szBuffer = new char[m_totToRcvLen]; //(char*) calloc(1, m_totToRcvLen);

				memset(m_szBuffer, 0, m_totToRcvLen);

				memset(ackmsg, 0, sizeof ackmsg);

				sprintf(ackmsg, "ACCEPT");

				m_bStartTrn = true;

				TCHAR szFilters[]= _T("Moca trace files (*.log)|*.log|Mtf trace files (*.out)|*.out|All files (*.*)|*.*||");
	            CFileDialog dlg(FALSE, _T("log"), _T("*.log"), OFN_HIDEREADONLY,szFilters);

	            if(dlg.DoModal()!=IDOK)
	         	    return;

	             file_name = dlg.GetPathName();
				 if (!m_fileToSave.Open(file_name, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
				 {
					 s.Format("Can not write file %s", (LPCSTR)file_name);

					 AfxMessageBox(s, MB_OK|MB_ICONERROR);
					 sprintf(ackmsg, "REFUSE");
				 }
				 else 
					 m_bStartTrn = true;
			}
			AsyncSelect(FD_WRITE);
			return;
	}

	if (m_totRcvedLen == m_totToRcvLen && m_totRcvedLen > 0)
	{
		file_name = m_fileToSave.GetFilePath();
		m_szBuffer[m_totRcvedLen] = '\0';

			m_fileToSave.Write(m_szBuffer, m_totRcvedLen);
			m_fileToSave.Flush();
			m_fileToSave.Close();
			
			TRACE("Writing[%d]...\n", m_totRcvedLen);

			m_bStartTrn = false;

			sprintf(ackmsg, "ACKFINISHED");

			AsyncSelect(FD_WRITE);



			CString s;

			s.Format("Open file [%s] with trace digger?", (LPCSTR)file_name);
			if (AfxMessageBox(s, MB_YESNO|MB_ICONQUESTION) == IDYES)
			{
						 
				CMainFrame *pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;

				CView * active = pMain->GetActiveView();

				CTraDoc *pDoc = (CTraDoc*) active->GetDocument();

				pDoc->m_sFileName = file_name;

				pMain->PostMessage(WM_OPENTRANFILE);
			}
			m_totRcvedLen = 0;
			return;
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CRcvFileSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//char buff[4096];

	 m_nLength = strlen(ackmsg);

	 if (m_nLength == 0)
		 return;
	 Send(ackmsg, m_nLength, 0);

	 //memset(ackmsg, 0, sizeof ackmsg);

	 AsyncSelect(FD_READ);

	 //memset(ackmsg, 0, sizeof ackmsg);

	//CAsyncSocket::OnSend(nErrorCode);
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
