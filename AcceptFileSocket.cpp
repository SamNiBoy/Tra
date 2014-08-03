// AcceptFileSocket.cpp : implementation file
//

#include "stdafx.h"
#include "tra.h"
#include "AcceptFileSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAcceptSocket

CAcceptSocket::CAcceptSocket()
{
	m_RcvSocket = NULL;
}

CAcceptSocket::~CAcceptSocket()
{
}

void CAcceptSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRcvFileSocket *pSocket = new CRcvFileSocket();

	if (Accept(*pSocket))
	{
		if (m_RcvSocket)
		{
			m_RcvSocket->Close();
			delete m_RcvSocket;
		}

		m_RcvSocket = pSocket;
		//CString s;
		//s.Format("Accept connection!");
		//AfxMessageBox(s);

		m_RcvSocket->AsyncSelect(FD_READ);
	}
	else
		delete pSocket;
	//CAsyncSocket::OnAccept(nErrorCode);
}
// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CAcceptSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CAcceptSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CAcceptSocket member functions
