// SndFileSocket.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "SndFileSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSndFileSocket

CSndFileSocket::CSndFileSocket()
{
	m_bStartTrn = false;
	m_sFileForSend = "";
	m_szBuffer = NULL;
	m_nSentLenght = 0;
	m_nLength = 0;
}

CSndFileSocket::~CSndFileSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSndFileSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSndFileSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSndFileSocket member functions

void CSndFileSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(!nErrorCode)
	{
		m_bConnected = TRUE;
		this->AsyncSelect(FD_WRITE);
	}
	else
	{
		CString s;
		s.Format("Connection failed with error %d!", nErrorCode);
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CSndFileSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_nLength = Receive(ackmsg, sizeof(ackmsg), 0);

	ackmsg[m_nLength] = '\0';

	if (strlen(ackmsg) == 0)
	{
		return;
	}

			 if (!m_bStartTrn && strcmp(ackmsg, "REFUSE") == 0)
			 {
				 CString PName;
				 unsigned int PPort;

				 this->GetPeerName(PName, PPort);

				 CString msg;
				 msg.Format("Remote ip[%s] refused your request!", (LPCSTR)PName);
	
				 AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
				 return ;
			 }
			 else if (strcmp(ackmsg, "ACCEPT") == 0)
			 {
				 m_bStartTrn = true;
				 //AfxMessageBox("Now start file transferring");

				 CStdioFile f;

				 if (!f.Open(m_sFileForSend, CFile::modeRead|CFile::typeBinary))
				 {
					 AfxMessageBox("Can not open file to transfer!", MB_OK|MB_ICONERROR);
					 return ;
				 }
				 else {

					 CString line;

					 m_nLength = f.GetLength();

					 if (m_szBuffer)
						 free (m_szBuffer);

					 m_szBuffer = (char*)calloc(1, m_nLength);

					 if (!m_szBuffer)
					 {
						 line.Format("Can not allocate memory %ld bytes!", m_nLength);
						 f.Close();
						 this->Close();
						 return;
					 }
					 
					 f.Read(m_szBuffer, m_nLength);

					 m_nSentLenght = 0;
					 f.Close();
					 AsyncSelect(FD_WRITE);
				 }
			 }
			 else if(strcmp(ackmsg, "ACKFINISHED") == 0)
			 {
		        //memset(ackmsg, 0, sizeof ackmsg);
		        CString s;
		        s.Format("File sent completely.");
		        AfxMessageBox(s, MB_OK|MB_ICONINFORMATION);
			 }
			 else 
			 {
				 AfxMessageBox("Got unexpected response!");
			 }


	//CAsyncSocket::OnReceive(nErrorCode);
}

void CSndFileSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (!m_bStartTrn && strlen(ackmsg) > 0)
	{
		m_nLength = strlen(ackmsg);
	    Send(ackmsg, m_nLength, 0);
	    m_nLength = 0;
	    memset(ackmsg, 0, sizeof(ackmsg));
	    AsyncSelect(FD_READ);
	}
	else if (m_bStartTrn)
	{
		if (m_nSentLenght == m_nLength)
		{
		    AsyncSelect(FD_READ);
		    m_bStartTrn = false;
			return;
		}

		UINT len = 0;
		while (m_nSentLenght < m_nLength)
		{
			if((len = Send(m_szBuffer + m_nSentLenght, m_nLength - m_nSentLenght)) == SOCKET_ERROR)
			{
				if (GetLastError() == WSAEWOULDBLOCK)
					break;
				else
				{
					AfxMessageBox("Socket failed to send!");
					return;
				}
			}
			m_nSentLenght += len;
		}
		AsyncSelect(FD_WRITE);
	}

	CAsyncSocket::OnSend(nErrorCode);
}

void CSndFileSocket::setFileForSend(CString fn)
{
	m_sFileForSend = fn;
}
