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

				 if (!f.Open(m_sFileForSend, CFile::modeRead))
				 {
					 AfxMessageBox("Can not open file to transfer!", MB_OK|MB_ICONERROR);
					 return ;
				 }
				 else {

					 CString line;

					 DWORD fl = f.GetLength();
					 m_szBuffer = (char*)calloc(1, fl);

					 if (!m_szBuffer)
					 {
						 line.Format("Can not allocate memory %ld bytes!", f.GetLength());
						 f.Close();
						 this->Close();
						 return;
					 }
					 
					 memset(m_szBuffer, 0, fl);
					 while(f.ReadString(line))
					 {
						sprintf(m_szBuffer, "%s\n", (LPCSTR)line);
						Send(m_szBuffer, strlen(m_szBuffer), 0);
						AsyncSelect(FD_WRITE);
						memset(m_szBuffer, 0, sizeof m_szBuffer);
					 }

					 f.Close();
					 memset(m_szBuffer, 0, fl);
					 sprintf(m_szBuffer, "FINISHED");
					 Send(m_szBuffer, strlen(m_szBuffer), 0);
					 AsyncSelect(FD_WRITE);

					 CString s;
					 s.Format("File sent completely.");
					 AfxMessageBox(s);
					 //closesocket(servSock);
				 }
			 }
			 else 
			 {
				 AfxMessageBox("Got unexpected response!");
			 }

	//memset(m_szBuffer, 0, sizeof(m_szBuffer));

	//CAsyncSocket::OnReceive(nErrorCode);
}

void CSndFileSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_nLength = strlen(ackmsg);

	if (m_nLength <= 0)
		return;

	Send(ackmsg, m_nLength, 0);
	m_nLength = 0;
	memset(ackmsg, 0, sizeof(ackmsg));

	if (!m_bStartTrn)
	{
	    AsyncSelect(FD_READ);
	}
	else
	{
		AsyncSelect(FD_WRITE);
	}

	CAsyncSocket::OnSend(nErrorCode);
}

void CSndFileSocket::setFileForSend(CString fn)
{
	m_sFileForSend = fn;
}
