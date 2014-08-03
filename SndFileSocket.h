#if !defined(AFX_SNDFILESOCKET_H__D8B4ED65_B5D0_4D7E_B60E_40699D416CFC__INCLUDED_)
#define AFX_SNDFILESOCKET_H__D8B4ED65_B5D0_4D7E_B60E_40699D416CFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SndFileSocket.h : header file
//
#include "afxsock.h"

//#define BUF_SZ 4096*10
/////////////////////////////////////////////////////////////////////////////
// CSndFileSocket command target

class CSndFileSocket : public CAsyncSocket
{
// Attributes
public:
	BOOL m_bConnected;
	UINT m_nLength;
	char *m_szBuffer;
	char ackmsg[4096];
// Operations
public:
	CSndFileSocket();
	virtual ~CSndFileSocket();

// Overrides
public:
	void setFileForSend(CString fn);
	CString m_sFileForSend;
	bool m_bStartTrn;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSndFileSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSndFileSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNDFILESOCKET_H__D8B4ED65_B5D0_4D7E_B60E_40699D416CFC__INCLUDED_)
