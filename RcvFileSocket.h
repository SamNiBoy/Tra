#if !defined(AFX_RCVFILESOCKET_H__FD4315CB_ADC5_4AC9_A47D_D3CED4A41006__INCLUDED_)
#define AFX_RCVFILESOCKET_H__FD4315CB_ADC5_4AC9_A47D_D3CED4A41006__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RcvFileSocket.h : header file
//
#include<afxsock.h>


/////////////////////////////////////////////////////////////////////////////
// CRcvFileSocket command target

class CRcvFileSocket : public CAsyncSocket
{
// Attributes
public:
	char *m_szBuffer;
	char ackmsg[4096];
	int m_nLength;
	DWORD m_totToRcvLen;
	DWORD m_totRcvedLen;
// Operations
public:
	CRcvFileSocket();
	virtual ~CRcvFileSocket();

// Overrides
public:
	CStdioFile m_fileToSave;
	bool m_bStartTrn;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcvFileSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CRcvFileSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCVFILESOCKET_H__FD4315CB_ADC5_4AC9_A47D_D3CED4A41006__INCLUDED_)
