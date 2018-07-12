// EditFinder.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "EditFinder.h"
#include "MainFrm.h"
#include "TraDoc.h"
#include "LeftView.h"
#include "TraView.h"
#include "FindLstDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditFinder

CEditFinder::CEditFinder()
{
	m_pFindLstDlg = new CFindLstDlg;
}

CEditFinder::~CEditFinder()
{
	delete m_pFindLstDlg;
}


BEGIN_MESSAGE_MAP(CEditFinder, CEdit)
	//{{AFX_MSG_MAP(CEditFinder)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditFinder message handlers

void CEditFinder::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	//MessageBox("haha");
}

void CEditFinder::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEditFinder::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CEditFinder::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{

		short ret = ::GetKeyState(VK_CONTROL);

		//AfxMessageBox("def");
		CMyToolBar *pToolBar=(CMyToolBar*)this->GetParent();
		CTraApp * pApp = (CTraApp *)::AfxGetApp();
	    CMainFrame * pMf = (CMainFrame*)pApp->m_pMainWnd;
        CTraDoc *pDoc = (CTraDoc*) pMf->GetActiveDocument();
		CLeftView* pLVW;
		CTraView *pTVW;
		static CString preText="";
        CString text;
        GetWindowText(text);
		
		boolean SearchInLeftFocusedCmd = pToolBar->m_pBtn->m_bSearchAtLeft;

		if(text.GetLength()<=0) return true;
		
		POSITION pos = pDoc->GetFirstViewPosition();
		while(pos != NULL)
		{
			CView *pVw = pDoc->GetNextView(pos);
			if(pVw->IsKindOf(RUNTIME_CLASS(CLeftView)))
			{
				pLVW = (CLeftView *) pVw;
			}
			else if(pVw->IsKindOf(RUNTIME_CLASS(CTraView)))
			{
				pTVW = (CTraView *) pVw;
			}
		}

		//if didn't press Ctl key, searh right text.
		if(ret>=0)
		{
			
			m_pFindLstDlg->lines.RemoveAll();
			m_pFindLstDlg->mcmds.RemoveAll();
			if(m_pFindLstDlg->m_hWnd != NULL && m_pFindLstDlg->IsWindowVisible())
			{
			    m_pFindLstDlg->ShowWindow(SW_HIDE);
			}
			//m_pFindLstDlg->m_CLstBox.ResetContent();
			CMcmd *pNearestMcmd = NULL, *pCurMcmd = NULL;
			CString line;
			int mcmdidx = 0;

            text.MakeLower();
			pTVW->m_KeyWord = "";

			int beg = 0;
			int end = pDoc->m_pf->GetTotLin();
			//int end = pDoc->m_strArrLines.GetSize();

			if(SearchInLeftFocusedCmd)
			{
				//AfxMessageBox("abc");
				CTreeCtrl &CTC = pLVW->GetTreeCtrl();
				HTREEITEM hItem = CTC.GetSelectedItem();

				if(!hItem)
				{
					AfxMessageBox("No focused command selected from left panel!", MB_OK|MB_ICONINFORMATION);
					this->SetFocus();
					return true;
				}

				pDoc->m_MHreeItem_To_Mcmd.Lookup(hItem, (void*&)pCurMcmd);
				beg = pCurMcmd->beglin;
				end = pCurMcmd->endlin+1;
				//CTC.GetSelectedItem(
				

			}

			CString orgLine;
        	for(int i=beg ; i< end; i++)
			{
				pDoc->m_pf->GetLine(line, i+1);

				orgLine = line;
				//line = pDoc->m_strArrLines[i];
				TRY
                {
                    line.MakeLower();
                }
                CATCH_ALL(e)
                {
                    continue;
                }
                END_CATCH_ALL
				
	        	if(line.Find(text) >= 0)
				{
					for( long j = mcmdidx ; j< pDoc->m_ObjArrMcmds.GetSize() ; j++)
					{
						pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[j];
						if(pCurMcmd->beglin <= i+1)
						{
							pNearestMcmd = pCurMcmd;
						}
						else
						{
							mcmdidx = j;
							break;
						}
					}

					//TRACE("found line %s\n", pDoc->m_strArrLines[i]);
					m_pFindLstDlg->lines.Add(orgLine);
					m_pFindLstDlg->linesId.Add(i + 1);
					//m_pFindLstDlg->lines.Add(pDoc->m_strArrLines[i]);
					m_pFindLstDlg->mcmds.Add(pNearestMcmd);
					pTVW->m_KeyWord = text;
				}
			}
			if(m_pFindLstDlg->lines.GetSize() > 0)
			{
			    //m_pFindLstDlg->DoModal();
				if(m_pFindLstDlg->m_hWnd == NULL)
				{
					m_pFindLstDlg->Create(IDD_FIND_LIST, NULL);//::AfxGetApp()->GetMainWnd());
				}

				m_pFindLstDlg->m_CLstBox.ResetContent();

		        for(long i=0;i<m_pFindLstDlg->lines.GetSize(); i++)
				{
	            	m_pFindLstDlg->m_CLstBox.AddString(m_pFindLstDlg->lines[i]);
				}
				CListBox *pLstBox = (CListBox*) m_pFindLstDlg->GetDlgItem(IDC_FIND_LST);
				pLstBox->SetHorizontalExtent(10000);

				m_pFindLstDlg->CenterWindow();
				m_pFindLstDlg->ShowWindow(SW_SHOW);
				m_pFindLstDlg->SetForegroundWindow();

				if (pToolBar->IsFloating())
				{
				    pToolBar->GetParentFrame()->ShowWindow(SW_HIDE);
				}
				pMf->m_bSearchShwFlg = 0;

			}
			else
			{
				AfxMessageBox("Nothing found!", MB_OK|MB_ICONINFORMATION);
				this->SetFocus();
			}
			
		}
		else
		{
			if(m_pFindLstDlg->m_hWnd != NULL && m_pFindLstDlg->IsWindowVisible())
				m_pFindLstDlg->ShowWindow(SW_HIDE);

			if(preText.GetLength() == 0 || preText != text)
			{
			    preText = text;
			    pLVW->m_iFromithMcmd = 1;
			}
			pTVW->m_KeyWord = text;
			pLVW->m_strText = text;
			pLVW->OnFindNxtmcmd();
			this->SetFocus();
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
