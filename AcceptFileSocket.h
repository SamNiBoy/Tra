#if !defined(AFX_ACCEPTFILESOCKET_H__548E3319_8711_4FFE_93E5_BF54990CC04D__INCLUDED_)
#define AFX_ACCEPTFILESOCKET_H__548E3319_8711_4FFE_93E5_BF54990CC04D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AcceptFileSocket.h : header file
//
#include<afxsock.h>
#include "rcvfilesocket.h"

/////////////////////////////////////////////////////////////////////////////
// CAcceptSocket command target

class CAcceptSocket : public CAsyncSocket
{
// Attributes
public:

	CRcvFileSocket *m_RcvSocket;
// Operations
public:
	CAcceptSocket();
	virtual ~CAcceptSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcceptSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CAcceptSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCEPTFILESOCKET_H__548E3319_8711_4FFE_93E5_BF54990CC04D__INCLUDED_)
