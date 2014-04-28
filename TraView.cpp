// TraView.cpp : implementation of the CTraView class
//

#include "stdafx.h"
#include "Tra.h"

#include "TraDoc.h"
#include "TraView.h"
#include "LeftView.h"
#include "InProgress.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTraView

IMPLEMENT_DYNCREATE(CTraView, CRichEditView)

BEGIN_MESSAGE_MAP(CTraView, CRichEditView)
	//{{AFX_MSG_MAP(CTraView)
	ON_WM_SIZE()
	ON_COMMAND(IDM_FIND_RIGHT, OnFindRight)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_DROPFILES()
	ON_WM_CONTEXTMENU()
	ON_WM_VSCROLL()
	ON_WM_RBUTTONDOWN()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTraView construction/destruction

CTraView::CTraView()
{
	// TODO: add construction code here
	m_preMcmd = NULL;

	m_nWordWrap = WrapNone;

}

CTraView::~CTraView()
{
}

BOOL CTraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= WS_HSCROLL|WS_VSCROLL;
	
	return CRichEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTraView drawing

void CTraView::OnDraw(CDC* pDC)
{
	CTraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//pDC->SetTextColor(RGB(255,0,0));

}

void CTraView::OnInitialUpdate()
{
	CTraDoc* pDoc = GetDocument();
			CHARFORMAT2 cf;
            cf.cbSize = sizeof(cf);
         	cf.dwMask = CFM_COLOR |CFM_BOLD |CFM_FACE |CFM_WEIGHT | CFM_SIZE;
            cf.crTextColor = pDoc->m_OptColor->m_BEYONDClr;
  
            cf.dwEffects = CFE_PROTECTED;
            cf.wWeight = 50;
         	cf.yHeight = 165;
	
        	::lstrcpy(cf.szFaceName,"Arial");	

        	CRichEditCtrl &CRE = GetRichEditCtrl();
        	CRE.SetBackgroundColor(false, pDoc->m_OptColor->m_RPCOLORClr);
        	CRE.SetSel(1,2);
        	CRE.SetWordCharFormat(cf);
        	CRE.SetSel(0,0);
	CRichEditView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// CTraView diagnostics

#ifdef _DEBUG
void CTraView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CTraView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CTraDoc* CTraView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTraDoc)));
	return (CTraDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

BOOL CTraView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	dwStyle |= ES_MULTILINE | ES_AUTOVSCROLL |ES_WANTRETURN |WS_VSCROLL |ES_READONLY;

	

	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CTraView::OnSize(UINT nType, int cx, int cy) 
{
	CRichEditView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here


}


static DWORD CALLBACK 
MyStreamInCallback(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CFile *file= (CFile *) dwCookie;

   *pcb = file->Read(pbBuff, cb);
   
   //strcpy((char*)pbBuff, pStr->GetBuffer(pStr->GetLength()));

   return 0;
}
/*static unsigned long txtIdx = 0;
static DWORD CALLBACK 
MyStreamInCallback2(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   char * txt= (char *) dwCookie;

   if (txtIdx >= strlen(txt))
   {
	   *pcb = 0;
	   return 0;
   }

   if (txtIdx + cb > strlen(txt))
	   cb = strlen(txt) - txtIdx;

	strncpy((char*)pbBuff, txt + txtIdx, cb);
    txtIdx += cb;

   //*pcb = file->Read(pbBuff, cb);
   
   //strcpy((char*)pbBuff, pStr->GetBuffer(pStr->GetLength()));

   return 0;
}*/

void CTraView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{

	
	CTraDoc *pDoc = this->GetDocument();

	if (!pDoc->m_pf)
		return;

	CMcmd *pCurMcmd = (CMcmd *)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];

	LoadText();
	UndecoratePreMcmd();
	DecorateMcmd(pCurMcmd);
	DecorateInterested(pCurMcmd);
	ScorllToMcmd();

	/*CTraDoc *pDoc = this->GetDocument();
	CRichEditCtrl &CRE = this->GetRichEditCtrl();
	   CString txt = "";
    if(pDoc->m_sFileName.GetLength() <= 0)
	return;

	long totline=pDoc->m_pf->GetTotLin();
	int deta=50;
    //CRE.SetBackgroundColor(false, pDoc->m_OptColor->m_RPCOLORClr);


	BOOL bShowAll = pDoc->m_OptMoca->m_bShowAll && !pDoc->m_OptMoca->m_bSupMod;
	static BOOL ShownFlg = FALSE;
	CMcmd * pCurMcmd = NULL;
	static CMcmd *pPreMcmd = NULL;

	// If it's new file open, reset flags.
	if (pDoc->m_bNewFileFlg)
	{
		ShownFlg = FALSE;
		pPreMcmd = NULL;
	}

	if (bShowAll && !ShownFlg)
	{
		this->ShowWindow(SW_HIDE);
		EDITSTREAM es;

		CFile *f = pDoc->GetFile(pDoc->m_sFileName, CFile::modeRead, NULL);
        
        es.pfnCallback = MyStreamInCallback; 
		es.dwCookie = (DWORD) f;

		GetRichEditCtrl().StreamIn(SF_TEXT, es);

		f->Close();

		if(pDoc->m_MHreeItem_To_Mcmd.GetCount()>0 && pDoc->m_ObjArrMcmds.GetSize() >= pDoc->m_iFocusMcmd)
		{
			pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];
			HighLightMcmd(pPreMcmd, pCurMcmd);
			pPreMcmd = pCurMcmd;
		}
		
		ShowWindow(SW_SHOW);
		int fstlin = GetRichEditCtrl().GetFirstVisibleLine();
		GetRichEditCtrl().LineScroll(-fstlin);
		
		if (pCurMcmd)
		{
			GetRichEditCtrl().LineScroll(pCurMcmd->beglin);
		}

		ShownFlg = TRUE;
		pDoc->m_bNewFileFlg = FALSE;
		this->UpdateStatuBar();
		return;
	}
	else if(ShownFlg && bShowAll)
	{
		if(pDoc->m_MHreeItem_To_Mcmd.GetCount()>0 && pDoc->m_ObjArrMcmds.GetSize() >= pDoc->m_iFocusMcmd)
		{
			pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];
			HighLightMcmd(pPreMcmd, pCurMcmd);
			pPreMcmd = pCurMcmd;
		    int lin = GetRichEditCtrl().GetFirstVisibleLine();
		    GetRichEditCtrl().LineScroll(-lin);
			CString begtxt;
			
			FINDTEXTEX ft;
            ft.chrg.cpMin = 0;
            ft.chrg.cpMax = -1;
			pDoc->m_pf->GetLine(begtxt, pCurMcmd->beglin);
            ft.lpstrText = (LPSTR) begtxt.GetBuffer(begtxt.GetLength() + 1);
			int idx = GetRichEditCtrl().FindText(FR_MATCHCASE|FR_WHOLEWORD, &ft);
			lin = GetRichEditCtrl().LineFromChar(idx);
			GetRichEditCtrl().LineScroll(lin);
		}
		this->UpdateStatuBar();
		return;
	}

	//If user switch to SINGLE mode, reset ShownFlg to false.
	ShownFlg = FALSE;
    if(pDoc->m_MHreeItem_To_Mcmd.GetCount()>0 && pDoc->m_ObjArrMcmds.GetSize() > pDoc->m_iFocusMcmd)
	{
	    pCurMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];
		long beglin = pCurMcmd->beglin , endlin = pCurMcmd->endlin;
		long beglin0 = beglin;

		if(pDoc->m_iFocusMcmd - 2 >= 0 && pDoc->m_iFocusMcmd < pDoc->m_ObjArrMcmds.GetSize())
		{
			CMcmd *pPreMcmd = (CMcmd*) (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd - 2];
			CMcmd *pNxtMcmd = (CMcmd*) (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd];
			beglin = pPreMcmd->endlin > (beglin - deta) ? (beglin - deta) : pPreMcmd->endlin;
			endlin = pNxtMcmd->beglin < (endlin + deta) ? ((endlin + deta) < totline ? (endlin + deta) : totline) : pNxtMcmd->beglin;
		}
		else
		{
		    beglin = (beglin - deta) < 1 ? 1 : beglin - deta;
		    endlin = (endlin + deta) > totline ? totline : endlin + deta;
		}

		if(endlin - beglin > 10000)
		{
			CString msg;
			msg.Format("Total %ld lines which exceeds 10000 lines, only load 5000 lines? ", endlin - beglin);
			long ret = AfxMessageBox(msg, MB_YESNOCANCEL|MB_ICONQUESTION);
			if( ret == IDYES)
			{
				endlin = beglin + 5000;
			}
			else if (ret == IDCANCEL)
			{
				this->UpdateStatuBar();
				return;
			}
		}

		pDoc->m_pf->GetLines(txt, beglin, endlin);
	    //for(long i=beglin ; i<= endlin; i++)
		//{
	    //	txt += pDoc->m_strArrLines[i-1] + "\r\n";
		//}
		this->ShowWindow(SW_HIDE);
		
     	SetWindowText(txt);
		HighLightMcmd(pPreMcmd, pCurMcmd);
		this->ShowWindow(SW_SHOW);
		int fstlin = this->GetRichEditCtrl().GetFirstVisibleLine();
		this->GetRichEditCtrl().LineScroll(-fstlin);
		this->GetRichEditCtrl().LineScroll(beglin0 - beglin);
	}
	this->UpdateStatuBar();*/
}

void CTraView::OnFindRight() 
{
	// TODO: Add your command handler code here
	this->OnEditFindReplace(TRUE);
	this->SetActiveWindow();
	
}

void CTraView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	//pDC->SetTextColor(RGB(255,0,0));
	CRichEditView::OnPrepareDC(pDC, pInfo);
}

void CTraView::DecorateInterested(CMcmd *pCurMcmd)
{
	CString text;
	long begpos=0, begpos0 = 0, beglin=0;
	long endpos, endlin; 
	CTraDoc *pDoc = GetDocument();
	this->GetWindowText(text);
	
	if(text.GetLength() <= 0)
		return;

	if(pDoc->m_OptMoca->m_bShowSingle)
	{
		beglin = 1;
		begpos = 0;
		endlin = GetRichEditCtrl().GetLineCount();
		endpos = text.GetLength();
	}
	else 
	{
		if(pCurMcmd->ID > 1)
		{
			CMcmd *Pre = (CMcmd*)pDoc->m_ObjArrMcmds[pCurMcmd->ID-2];
			//If previous mcmd is parent, beglin shoud be Pre->beglin.
			if (Pre == pCurMcmd->Parent)
				beglin = Pre->beglin;
			else
		        beglin = Pre->endlin;

			//begpos = GetRichEditCtrl().LineIndex(beglin - 1);

			begpos = pDoc->m_pf->GetOffSetForLine(beglin);
			//begpos = text.Find(tb, begpos);
		    //begpos = text.Find(pDoc->m_strArrLines[beglin-1], begpos);

			endlin = pCurMcmd->endlin;

            endpos = pDoc->m_pf->GetOffSetForLine(endlin);

			//endpos = text.Find(pDoc->m_strArrLines[endlin-1]);

			/*int NxtID = pCurMcmd->ID + 1;
			int MaxID = ((CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_ObjArrMcmds.GetSize() - 1])->ID;
			CMcmd *Nxt = (NxtID <= MaxID) ? (CMcmd*) pDoc->m_ObjArrMcmds[NxtID - 1] : NULL;

			while (NxtID < MaxID && Nxt->beglin <= pCurMcmd->endlin)
			{
				Nxt = (CMcmd*) pDoc->m_ObjArrMcmds[NxtID];
				NxtID ++;
			}

			if(Nxt && Nxt->beglin > pCurMcmd->endlin)
			{
			    endlin = Nxt->beglin;
				CString tmp;
				pDoc->m_pf->GetLine(tmp, endlin);
				endpos = text.Find(tmp, endpos);
			    //endpos = text.Find(pDoc->m_strArrLines[endlin-1], endpos);
			}*/
		}
	    else
		{
		    beglin = pCurMcmd->beglin;
			begpos = pDoc->m_pf->GetOffSetForLine(beglin);
		    //begpos = text.Find(pDoc->m_strArrLines[beglin-1]);

			endlin = pCurMcmd->endlin;
			endpos = pDoc->m_pf->GetOffSetForLine(endlin);
			//endpos = text.Find(pDoc->m_strArrLines[endlin-1]);
		}
	}

	// If there is too much work, only process to header.
	if (endlin - beglin > 2000L)
	{
		endlin = beglin + 2000;
		endpos = pDoc->m_pf->GetOffSetForLine(endlin);
	}

	begpos0 = begpos;
	// KeyWord

    text.MakeLower();


	CRichEditCtrl &CRE = GetRichEditCtrl();
    CHARFORMAT2 cf;
    cf.cbSize = sizeof(cf);



	if (pDoc->m_trcTyp == MOCATRACE)
	{
		CString arg = "] argument";
		CString par = "] parameter";
		CString pub = "] published";

		//Hight argument
		int equalmark = 0 , valend;
		CString var, val;
		begpos = text.Find(arg, begpos0);

		cf.dwMask = CFM_COLOR |CFM_BOLD;
		cf.dwEffects = CFE_BOLD;
		while(begpos >= 0 && begpos <= endpos)
		{
			equalmark = text.Find("=", begpos);
			if(equalmark >=0)
			{
				//var = text.Mid(beglin + 10, equalmark - beglin - 10);
				//val =
				CRE.SetSel(begpos + 10, equalmark);
                cf.crTextColor = pDoc->m_OptColor->m_ARGUMENTClr;
				this->SetCharFormat(cf);

				CRE.SetSel(0,0);

				valend = text.Find("(", equalmark);
				if(valend >=0)
				{
					CRE.SetSel(equalmark + 1, valend -1);
					cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
					this->SetCharFormat(cf);
					CRE.SetSel(0,0);
				}
			}
			begpos = text.Find(arg, valend);
		}

		// Parameter
		begpos = begpos0;
	    begpos = text.Find(par, begpos);
		cf.dwMask = CFM_COLOR |CFM_BOLD;
		
		cf.dwEffects = CFE_BOLD;
		while(begpos >= 0 && begpos <= endpos)
		{
			equalmark = text.Find("=", begpos);
			if(equalmark >=0)
			{
				//var = text.Mid(beglin + 10, equalmark - beglin - 10);
				//val =
				CRE.SetSel(begpos + 11, equalmark);
                cf.crTextColor = pDoc->m_OptColor->m_PARAMETERClr;
				this->SetCharFormat(cf);

				CRE.SetSel(0,0);

				valend = text.Find("(", equalmark);
				if(valend >=0)
				{
					CRE.SetSel(equalmark + 1, valend -1);
					cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
					this->SetCharFormat(cf);
					CRE.SetSel(0,0);
				}
			}
			begpos = text.Find(par, valend);
		}

		// Publish
		begpos = begpos0;
	    begpos = text.Find(pub, begpos);
		cf.dwMask = CFM_COLOR |CFM_BOLD;
		
		cf.dwEffects = CFE_BOLD;
		while(begpos >= 0 && begpos <= endpos)
		{
			equalmark = text.Find("=", begpos);
			if(equalmark >=0)
			{
				//var = text.Mid(beglin + 10, equalmark - beglin - 10);
				//val =
				CRE.SetSel(begpos + 11, equalmark);
                cf.crTextColor = pDoc->m_OptColor->m_PUBLISHClr;
				this->SetCharFormat(cf);

				CRE.SetSel(0,0);

				valend = text.Find("(", equalmark);
				valend = valend > text.Find("(", equalmark) ? text.Find("\n", equalmark) : valend;
				if(valend >=0)
				{
					CRE.SetSel(equalmark + 1, valend -1);
					cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
					this->SetCharFormat(cf);
					CRE.SetSel(0,0);
				}
			}
			begpos = text.Find(pub, valend);
		}
	}
	else if(pDoc->m_trcTyp == MTFTRACE)
	{
		begpos = begpos0;
		cf.dwMask = CFM_COLOR |CFM_BOLD;
		cf.dwEffects = CFE_BOLD;
		cf.wWeight = 10;
		cf.yHeight = 200;
		while (begpos < endpos)
		{
			int ep;
			begpos = text.Find("[", begpos);
			if (begpos >=0)
			{
				ep = text.Find("]", begpos);
             	CRE.SetSel(begpos + 1, ep);
				cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
				this->SetCharFormat(cf);
				CRE.SetSel(0,0);
				begpos = ep;
			}
			else
				break;
		}
		begpos = begpos0;
		while (begpos < endpos)
		{
			int ep;
			begpos = text.Find("<on", begpos);
			if (begpos >=0)
			{
				ep = text.Find(">", begpos);
             	CRE.SetSel(begpos + 1, ep);
				cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
				this->SetCharFormat(cf);
				CRE.SetSel(0,0);
				begpos = ep;
			}
			else
				break;
		}

		begpos = begpos0;
		while (begpos < endpos)
		{
			int ep;
			begpos = text.Find("command>", begpos);
			if (begpos >=0)
			{
				cf.wWeight = 30;
				ep = text.Find("\n", begpos);
             	CRE.SetSel(begpos + 8, ep);
				cf.crTextColor = pDoc->m_OptColor->m_MCMDClr;
				this->SetCharFormat(cf);
				CRE.SetSel(0,0);
				begpos = ep;
			}
			else
				break;
		}
		begpos = begpos0;
		while (begpos < endpos)
		{
			int ep;
			begpos = text.Find("error>", begpos);
			if (begpos >=0)
			{
				ep = text.Find("\n", begpos);
             	CRE.SetSel(begpos + 6, ep);
				cf.crTextColor = RGB(255,00,00);
				this->SetCharFormat(cf);
				CRE.SetSel(0,0);
				begpos = ep;
			}
			else
				break;
		}
		begpos = begpos0;
		while (begpos < endpos)
		{
			int ep;
			begpos = text.Find("method - executing>", begpos);
			if (begpos >=0)
			{
				ep = text.Find("\n", begpos);
             	CRE.SetSel(begpos + 19, ep);
				cf.crTextColor = pDoc->m_OptColor->m_MCMDClr;
				this->SetCharFormat(cf);
				CRE.SetSel(0,0);
				begpos = ep;
			}
			else
				break;
		}
	}

	// Here high light some thing in ' and '
	begpos = begpos0;
	while (begpos < endpos)
	{
		int ep;
		begpos = text.Find("'", begpos+1);
		if (begpos >=0)
		{
			ep = text.Find("'", begpos+1);

			if (ep < 0) break;

			if (ep - begpos < 100)
			{
                CRE.SetSel(begpos+1, ep);
			    cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
			    this->SetCharFormat(cf);
			    CRE.SetSel(0,0);
			}
			begpos = ep;
		}
		else
			break;
	}

	//last process keyword
    DecorateKeyWord(begpos0, endpos);

}

void CTraView::HighLightMcmd(CMcmd *pPreMcmd, CMcmd * pCurMcmd)
{
	    CHARFORMAT2 cf;
        cf.cbSize = sizeof(cf);

		long beglin, endlin;
		CString text;
		CTraDoc *pDoc = GetDocument();
		CRichEditCtrl &CRE = this->GetRichEditCtrl();
		GetWindowText(text);
		if(pPreMcmd)
		{
			CString tmp;
			pDoc->m_pf->GetLine(tmp, pPreMcmd->beglin);
			beglin = text.Find(tmp);
			pDoc->m_pf->GetLine(tmp, pPreMcmd->endlin);
			endlin = text.Find(tmp, beglin);
		//beglin = text.Find(pDoc->m_strArrLines[pPreMcmd->beglin-1]);
		//endlin = text.Find(pDoc->m_strArrLines[pPreMcmd->endlin-1],beglin);
		if(endlin > beglin)
		{
			//pDoc->m_pf->GetLine(tmp, pPreMcmd->endlin);
			endlin +=tmp.GetLength();
			//endlin +=pDoc->m_strArrLines[pPreMcmd->endlin-1].GetLength();
		}

		CRE.SetSel(beglin, endlin);

        cf.dwMask = CFM_COLOR |CFM_FACE |CFM_WEIGHT |CFM_SIZE;
  
        cf.crTextColor = pDoc->m_OptColor->m_BEYONDClr;   
  
        cf.dwEffects = CFE_PROTECTED;
        cf.wWeight = 10;
	    cf.yHeight = 150;
		::lstrcpy(cf.szFaceName,"Arial");
		this->SetCharFormat(cf);
		CRE.SetSel(0,0);
		}
        CString tmp;
		pDoc->m_pf->GetLine(tmp, pCurMcmd->beglin);
		beglin = text.Find(tmp);
		pDoc->m_pf->GetLine(tmp, pCurMcmd->endlin);
		endlin = text.Find(tmp, beglin);
		//beglin = text.Find(pDoc->m_strArrLines[pCurMcmd->beglin-1]);
		//endlin = text.Find(pDoc->m_strArrLines[pCurMcmd->endlin-1],beglin);
		
		// if it's a prasing mcmd, we should highlight current line.
		if(endlin > beglin)
		{
			//pDoc->m_pf->GetLine(tmp, pCurMcmd->endlin);
			endlin +=tmp.GetLength();
			//endlin +=pDoc->m_strArrLines[pCurMcmd->endlin-1].GetLength();
		}
			

		CRE.SetSel(beglin, endlin>0 ? endlin: text.GetLength());

        cf.dwMask = CFM_COLOR |CFM_FACE |CFM_WEIGHT |CFM_SIZE;
  
        cf.crTextColor = pDoc->m_OptColor->m_RANGEClr;    
        cf.dwEffects = CFE_PROTECTED;
		cf.wWeight = 20;
		cf.yHeight = 200;
		::lstrcpy(cf.szFaceName,"Arial");
		this->SetCharFormat(cf);
		CRE.SetSel(0,0);

		if (pCurMcmd->mcmdTyp == 10)
		{
			CString begtxt;
			pDoc->m_pf->GetLine(begtxt, pCurMcmd->beglin);
			//CString begtxt = pDoc->m_strArrLines[pCurMcmd->beglin-1];
			int PreLen = begtxt.Find("]") + 1;
			beglin = beglin + PreLen;
			endlin = beglin + begtxt.GetLength() - PreLen;
			CRE.SetSel(beglin, endlin);
			cf.dwMask = CFM_COLOR |CFM_BOLD;
			cf.dwEffects =  CFE_BOLD;
			cf.crTextColor = pDoc->m_OptColor->m_MCMDClr;
			this->SetCharFormat(cf);
			int equidx = begtxt.Find("=", PreLen);
			int valbeg, valend;
			while (equidx >= 0)
			{
				valbeg = begtxt.Find("'", equidx) == -1 ? begtxt.Find(" ", equidx) : begtxt.Find("'", equidx);
				valend = begtxt.Find("'", valbeg + 1) == -1 ? (begtxt.Find(" ", equidx) == -1 ? begtxt.GetLength() : begtxt.Find(" ", equidx)) : begtxt.Find("'", valbeg + 1);
				if (valbeg >=0 && valend >=0)
				{
					CRE.SetSel(beglin + valbeg - PreLen, beglin + valend - PreLen + 1);
					cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
					this->SetCharFormat(cf);
				}
				equidx = begtxt.Find("=", valend);
			}
		}
		DecorateInterested(pCurMcmd);
}



void CTraView::OnSetFocus(CWnd* pOldWnd) 
{
	CRichEditView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	/*ID_INDICATOR_MCMD,
	ID_INDICATOR_TTME,
	ID_INDICATOR_ID,
	ID_INDICATOR_SELLEN,*/
	
}


void CTraView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    UpdateStatuBar();
	CRichEditView::OnLButtonUp(nFlags, point);
}

void CTraView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_LEFT || nChar == VK_RIGHT || nChar == VK_UP || nChar == VK_DOWN)
	{
	    UpdateStatuBar();
	}
	CRichEditView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CTraView::UpdateStatuBar()
{
	CRichEditCtrl &CRC = this->GetRichEditCtrl();
	//long curChrIdx = CRC.LineIndex(-1);
	
	//long curLinNum = CRC.LineFromChar(-1);
	//curLinNum++;
	CTraDoc *pDoc = this->GetDocument();
	if(pDoc->m_ObjArrMcmds.GetSize() <=0)
		return;
	CMcmd *pMcd = NULL, *pNxt=NULL;
	CString txt;
	CMainFrame * pMFrm = NULL;

	/*if(pDoc->m_OptSetting->m_bShowAll)
	{
		for(long i=0;i < pDoc->m_ObjArrMcmds.GetSize(); i++)
		{
			pNxt = (CMcmd*)pDoc->m_ObjArrMcmds[i];
			if(pNxt->beglin <= curLinNum && pNxt->endlin >= curLinNum)
				pMcd = pNxt;
			else if(pNxt->beglin > curLinNum)
				break;
		}
	}
	else*/
		pMcd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];

	pMFrm = (CMainFrame*)::AfxGetMainWnd();
	if(pMcd)
	{
			pMFrm->m_wndStatusBar.SetPaneText(0, "Cmd: "+ pMcd->mcmd);

			txt.Format("ID: %ld/%ld", pMcd->ID, pDoc->m_ObjArrMcmds.GetSize());
			pMFrm->m_wndStatusBar.SetPaneText(1, txt);

			txt.Format("Time: %.3lf sec", (pMcd->end_time_stmp - pMcd->beg_time_stmp)/1000.0);
			pMFrm->m_wndStatusBar.SetPaneText(2, txt);

	}
	else
	{
		pMFrm->m_wndStatusBar.SetPaneText(0, "Cmd: Root level");
		pMFrm->m_wndStatusBar.SetPaneText(1, "ID: 0");
	}
			CHARRANGE cr;
			CRC.GetSel(cr);
			txt.Format("Selected: %ld chars", cr.cpMax - cr.cpMin);
			pMFrm->m_wndStatusBar.SetPaneText(3, txt);
}

BOOL CTraView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CRichEditView::OnDrop(pDataObject, dropEffect, point);
}

void CTraView::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	((CMainFrame*)GetParentFrame())->OnDropFiles(hDropInfo);
	//CRichEditView::OnDropFiles(hDropInfo);
}

BOOL CTraView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BOOL ret = CRichEditView::PreTranslateMessage(pMsg);

	if(!ret)
	{
		CTraDoc *pDoc = this->GetDocument();
	    POSITION pos=pDoc->GetFirstViewPosition();
    	CView *pw =  pDoc->GetNextView(pos);
    	while(pw)
		{		
	    	if(pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
			{
				ret = ((CLeftView*)pw)->PreTranslateMessage(pMsg);
				break;
			}
		    pw = pDoc->GetNextView(pos);
		}
	}

	return ret;
}


void CTraView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	AfxMessageBox("abc");
	CMenu menu;
	if(!menu.CreatePopupMenu())
		return;
	CString txt = "Copy";
	menu.AppendMenu(MF_ENABLED|MF_STRING,ID_EDIT_COPY,txt);
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}

void CTraView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRichEditView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTraView::OnCancelMode() 
{
	CRichEditView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CTraView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("abc");
	
	CPoint wp;
	
	::GetCursorPos(&wp);
	CMenu menu;
	if(!menu.CreatePopupMenu())
		return;
	CString txt = "Copy";
	menu.AppendMenu(MF_ENABLED|MF_STRING,ID_EDIT_COPY,txt);
	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,wp.x,wp.y,this);
}

void CTraView::LoadText()
{
	CTraDoc *pDoc = this->GetDocument();
	unsigned long beglin = pDoc->m_BegLinId, endlin = pDoc->m_EndLinId;

	if (pDoc->m_OptMoca->m_bShowAll)
	{
		if (pDoc->m_bNewFileFlg || pDoc->m_bRefountRPanel)
		{
		ShowWindow(SW_HIDE);
		EDITSTREAM es;

		CFile *f = pDoc->GetFile(pDoc->m_sFileName, CFile::modeRead, NULL);
        
        es.pfnCallback = MyStreamInCallback; 
		es.dwCookie = (DWORD) f;

		GetRichEditCtrl().StreamIn(SF_TEXT, es);
		f->Close();
		ShowWindow(SW_SHOW);
		
		}
	}
	else
	{
		CRichEditCtrl &CRE = this->GetRichEditCtrl();
		//ShowWindow(SW_HIDE);
		CString txt;

		if(endlin - beglin > 5000 && !pDoc->m_OptMoca->m_bAlwsLines)
		{
			CString msg;
			msg.Format("Total %ld lines , only load 3000 lines? ", endlin - beglin);
			long ret = AfxMessageBox(msg, MB_YESNO|MB_ICONQUESTION);
			if( ret == IDYES)
			{
				endlin = beglin + 3000;
			}
		}
		else if (endlin - beglin > 5000 && pDoc->m_OptMoca->m_bAlwsLines)
		{
			endlin = beglin + 3000;
		}

		pDoc->m_pf->GetLines(txt, beglin, endlin);

		CRE.Clear();
		SetWindowText(txt);
		/*EDITSTREAM es;
		txtIdx = 0;
        es.pfnCallback = MyStreamInCallback2; 
		es.dwCookie = (DWORD) txt.GetBuffer(txt.GetLength());

		GetRichEditCtrl().StreamIn(SF_TEXT, es);*/
		SCROLLINFO si;
		si.fMask = SIF_RANGE|SIF_POS;
		si.nMin = 0 ;
		si.nPos = 0;
		si.nMax = endlin - beglin;
		CRE.SetScrollInfo(SB_VERT, &si);
		//ShowWindow(SW_SHOW);

	}
}

void CTraView::DecorateMcmd(CMcmd *pCurMcmd)
{
	    CHARFORMAT2 cf;
        cf.cbSize = sizeof(cf);

		int begpos, endpos;
		CString text;
		CTraDoc *pDoc = GetDocument();
		CRichEditCtrl &CRE = this->GetRichEditCtrl();

	    //CRE.GetLine(pCurMcmd->beglin - pDoc->m_BegLinId, text.GetBuffer(10000), 20000);
		//AfxMessageBox(text);
		begpos = CRE.LineIndex(pCurMcmd->beglin - pDoc->m_BegLinId);
		endpos = CRE.LineIndex(pCurMcmd->endlin - pDoc->m_BegLinId + 1);

		CRE.SetSel(begpos, endpos);

        cf.dwMask = CFM_COLOR |CFM_FACE |CFM_WEIGHT |CFM_SIZE;
  
        cf.crTextColor = pDoc->m_OptColor->m_RANGEClr;    
        cf.dwEffects = CFE_PROTECTED;
		cf.wWeight = 20;
		cf.yHeight = 200;
		::lstrcpy(cf.szFaceName,"Arial");
		this->SetCharFormat(cf);
		CRE.SetSel(0,0);

		if (pCurMcmd->mcmdTyp == 10)
		{
			CString begtxt;
			pDoc->m_pf->GetLine(begtxt, pCurMcmd->beglin);
			int PreLen = begtxt.Find("]") + 1;
			begpos = begpos + PreLen;
			endpos = begpos + begtxt.GetLength() - PreLen;
			CRE.SetSel(begpos, endpos);
			cf.dwMask = CFM_COLOR |CFM_BOLD;
			cf.dwEffects =  CFE_BOLD;
			cf.crTextColor = pDoc->m_OptColor->m_MCMDClr;
			SetCharFormat(cf);
			int equidx = begtxt.Find("=", PreLen);
			int valbeg, valend;
			while (equidx >= 0)
			{
				valbeg = begtxt.Find("'", equidx) == -1 ? begtxt.Find(" ", equidx) : begtxt.Find("'", equidx);
				valend = begtxt.Find("'", valbeg + 1) == -1 ? (begtxt.Find(" ", equidx) == -1 ? begtxt.GetLength() : begtxt.Find(" ", equidx)) : begtxt.Find("'", valbeg + 1);
				if (valbeg >=0 && valend >=0)
				{
					CRE.SetSel(begpos + valbeg - PreLen, begpos + valend - PreLen + 1);
					cf.crTextColor = pDoc->m_OptColor->m_VALUEClr;
					this->SetCharFormat(cf);
				}
				equidx = begtxt.Find("=", valend);
			}
		}
		m_preMcmd = pCurMcmd;
}

void CTraView::UndecoratePreMcmd()
{
	CTraDoc *pDoc = GetDocument(); 
	if (!m_preMcmd)
		return;
	if (pDoc->m_bNewFileFlg)
	{
		m_preMcmd = NULL;
	    return;
	}
	unsigned long begpos, endpos;       
	CString text;
	CHARFORMAT2 cf;                                             
    CRichEditCtrl &CRE = GetRichEditCtrl();    
                             
	begpos = CRE.LineIndex(m_preMcmd->beglin - pDoc->m_BegLinId);
	endpos = CRE.LineIndex(m_preMcmd->endlin - pDoc->m_BegLinId + 1); 

	CRE.SetSel(begpos, endpos);                               
    cf.dwMask = CFM_COLOR |CFM_FACE |CFM_WEIGHT |CFM_SIZE;
    cf.crTextColor = pDoc->m_OptColor->m_BEYONDClr;       
    cf.dwEffects = CFE_PROTECTED;                         
    cf.wWeight = 10;                                      
	cf.yHeight = 150;                                       
	::lstrcpy(cf.szFaceName,"Arial");                         
	SetCharFormat(cf);                                        
	CRE.SetSel(0,0);                                          
}


void CTraView::ScorllToMcmd()
{
	CTraDoc *pDoc = this->GetDocument();
	CMcmd *pFocusMcmd = (CMcmd*)pDoc->m_ObjArrMcmds[pDoc->m_iFocusMcmd-1];
	CRichEditCtrl &CRE = this->GetRichEditCtrl();
    CRE.ShowWindow(SW_HIDE);
	//CString t;
	int detLin = pFocusMcmd->beglin - pDoc->m_BegLinId - CRE.GetFirstVisibleLine();
	//t.Format("First Vis Line:%ld, firstLine:%ld, beglin:%ld, SrollLine:%ld", CRE.GetFirstVisibleLine(),
	//	pDoc->m_BegLinId,pFocusMcmd->beglin, detLin);
	//AfxMessageBox(t);
	CRE.LineScroll(detLin);
	//CRE.LineScroll(pFocusMcmd->beglin - pDoc->m_BegLinId - m_preMcmd->beglin);
	CRE.ShowWindow(SW_SHOW);

	if (pDoc->m_bNewFileFlg)
		pDoc->m_bNewFileFlg = false;
}

void CTraView::DecorateKeyWord(long begpos, long endpos)
{

		//last process keyword
	if(m_KeyWord.GetLength() > 0)
	{
		CHARFORMAT2 cf;
		CRichEditCtrl &CRE = GetRichEditCtrl();
		m_KeyWord.MakeLower();

		CString text;
		GetWindowText(text);
	    
	    begpos = text.Find(m_KeyWord, begpos);
		int keywordlen = m_KeyWord.GetLength();
		cf.dwMask = CFM_UNDERLINE |CFM_COLOR |CFM_BOLD |CFM_BACKCOLOR|CFM_WEIGHT |CFM_SIZE;
		
		cf.dwEffects = CFE_UNDERLINE | CFE_BOLD;
		cf.crTextColor = RGB(200, 155, 0);
		//cf.crBackColor = RGB(255, 0,0);
		cf.wWeight = 10;
		cf.yHeight = 250;
		while(begpos >= 0 && begpos <= endpos)
		{
			CRE.SetSel(begpos, begpos + keywordlen);
			this->SetCharFormat(cf);
			CRE.SetSel(0,0);
			begpos = text.Find(m_KeyWord, begpos + keywordlen);
		}
	}
}
