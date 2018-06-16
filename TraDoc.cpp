// TraDoc.cpp : implementation of the CTraDoc class
//


#include "stdafx.h"
#include "Tra.h"

//#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>

#include "TraDoc.h"
#include "TraView.h"
#include "LeftView.h"
#include "InProgress.h"
#include "GphDlg.h"
#include "OptMTF.h"
#include "MainFrm.h"
#include "ExportDlg.h"
#include "DlgTransf.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTraDoc


IMPLEMENT_DYNCREATE(CTraDoc, CDocument)

BEGIN_MESSAGE_MAP(CTraDoc, CDocument)
	//{{AFX_MSG_MAP(CTraDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPT_SETTING, OnOptSetting)
	ON_COMMAND(IDM_REFRESH_VIEW, OnRefreshView)
	ON_UPDATE_COMMAND_UI(IDM_REFRESH_VIEW, OnUpdateRefreshView)
	ON_COMMAND(IDM_SHOW_SELECT, OnShowSelect)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_SELECT, OnUpdateShowSelect)
	ON_COMMAND(IDM_SHOW_DELETE, OnShowDelete)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_DELETE, OnUpdateShowDelete)
	ON_COMMAND(IDM_SHOW_MCMD, OnShowMcmd)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_MCMD, OnUpdateShowMcmd)
	ON_COMMAND(IDM_SHOW_INSERT, OnShowInsert)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_INSERT, OnUpdateShowInsert)
	ON_COMMAND(IDM_SHOW_UPDATE, OnShowUpdate)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_UPDATE, OnUpdateShowUpdate)
	ON_COMMAND(IDM_SHOW_ALL, OnShowAll)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_ALL, OnUpdateShowAll)
	ON_COMMAND(IDM_SHOW_GRPH, OnShowGrph)
	ON_COMMAND(IDM_SHOW_BKMK, OnShowBkmk)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_BKMK, OnUpdateShowBkmk)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_FILE_TRNSF, OnFileTrnsf)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_TRNSF, OnUpdateFileTrnsf)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTraDoc construction/destruction

CTraDoc::CTraDoc()
{
	// TODO: add one-time construction code here
	m_OptMoca = new COptDlg;
	m_OptMtf = new COptMTF;
	m_OptColor = new CColorDlg;
	CTraApp *pApp = (CTraApp *) ::AfxGetApp();
	pApp->ReadOptionsFromINI(this);
	m_sFileName ="";
	m_bNewFileFlg = FALSE;
	m_pSheet = NULL;
	m_bRefountRPanel = 0;
	m_pf = NULL;
}

CTraDoc::~CTraDoc()
{
	if(this->m_ObjArrMcmds.GetSize() > 0)
	{
		for(long i=0; i<this->m_ObjArrMcmds.GetSize(); i++)
		{
			delete this->m_ObjArrMcmds[i];
		}
	}
	CTraApp *pApp = (CTraApp *) ::AfxGetApp();
	pApp->WriteOptionsToINI(this);	
	
	if (m_OptMoca->m_bSupMod)
		m_pf->Close();

	//AfxMessageBox("Call destructer of ~CTraDoc");
	
	delete m_pf;
	delete m_OptMoca;
	delete m_OptMtf;
	delete m_OptColor;

}

BOOL CTraDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTraDoc serialization

void CTraDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTraDoc diagnostics

#ifdef _DEBUG
void CTraDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTraDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTraDoc commands

void CTraDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	TCHAR szFilters[]= _T("Moca trace files (*.log)|*.log|Mtf trace files (*.out)|*.out|All files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("log"), _T("*.log"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters);

	if(dlg.DoModal()!=IDOK)
		return;

	CString filename = dlg.GetPathName();

	OpenFile(filename);
	
}

void CTraDoc::ExactMcmd()
{
	long linenum = this->m_pf->GetTotLin();
	if(linenum <= 0)
		return;

	long i, seqnum =1, flag=0,j;
	CString line, nxtline, content;
	CMcmd *pMcmd, *pLstMcmd = NULL, *pParMcmd = NULL;
	CObArray ParStack;
	CTime ts, te;
	CInProgress *pPrg = new CInProgress;
	pPrg->Create(IDD_IN_PROGRESS, ::AfxGetApp()->GetMainWnd());
	pPrg->SetOwner(::AfxGetApp()->GetMainWnd());
	pPrg->CenterWindow();
	pPrg->ShowWindow(SW_SHOW);
	pPrg->m_cInPrg.SetRange(0,100);
	ts = CTime::GetCurrentTime();
	
	i=0;
	boolean exitflg = false;

#define TRACE_OFF

#ifdef TRACE_ON
	FILE *file=fopen("D:\\Parse.log","w");
	if (!file)
		exit(0);
	CString trace;
#endif

	while(m_pf->GetNextLine(line, i==0?true:false) && !exitflg)
	{
#ifdef TRACE_ON
		trace.Format("Read Line [%d]:%s\n", i+1, line);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
#endif
		if((i+1) % 100 == 0)
		{
		    pPrg->m_cInPrg.SetPos((int)(i*1.0/linenum*100.0));
		}
		//TRACE("i= '%ld'\n",i);
		j = i + 1;

		if (i == 73239)
			TRACE("i = '%d'",i);

		while (1)
		{
			if (!m_pf->GetNextLine(nxtline, false))
			{
				exitflg = true;
				break;
			}

		#ifdef TRACE_ON
		trace.Format("Try Next Line [%d]:%s\n", j+1, nxtline);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif

			int idx = nxtline.Find(':');
			if(idx < 0 || nxtline.GetLength()<= idx+3 || nxtline[idx+3] != ':')
			{
				line += nxtline;
				j++;
			}
			else
			{
				m_pf->BackOneLine(nxtline);
				break;
			}
		}

	    // Trim '[]' from the end of line for new moca trace.
	    if (line.GetLength() >= 2 && 
			line[line.GetLength() - 2] == '['
			&& line[line.GetLength() - 1] == ']')
		{
		    line = line.Left(line.GetLength() - 2);
		}

        
		//if (line.Find("Executing SQL: select * from les_var_config where 1=2") >= 0)
	    //		TRACE(line);

		flag = ParseLine(line , content);
		switch(flag)
		{
		 case 1:
		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif
		        if (pLstMcmd)
				{
					pLstMcmd->GetTimeStamp(line, FALSE);
				}
				pMcmd = new CMcmd;
				pMcmd->mcmd = content;
				pMcmd->beglin = i+1;
				//set endlin with beglin in case no end execution found.
				pMcmd->endlin = pMcmd->beglin;
				pMcmd->ID = seqnum;
				pMcmd->mcmdTyp = 1;

				TRACE("Find mcmd at line [%ld], %s ", i+1, content);
			
				//TRACE("%s\n",pMcmd->mcmd);
				
				pMcmd->GetTimeStamp(line, TRUE);
				if(ParStack.GetSize() == 0)
				{
					pMcmd->level = 1;
					pMcmd->Parent = NULL;
				}
				else
				{
					CMcmd *ParMcmd = (CMcmd *) ParStack.GetAt(ParStack.GetSize()-1);
					pMcmd->Parent = ParMcmd;
					pMcmd->level = ParMcmd->level + 1;
				}
				ParStack.Add(pMcmd);
				m_ObjArrMcmds.Add(pMcmd);
				seqnum++;
				break;
		 case 2:
				if(ParStack.GetSize() > 0)
				{
					CMcmd * pParMcmd = (CMcmd *)ParStack.GetAt(ParStack.GetSize()-1);
			        pParMcmd->endlin = j;
				    pParMcmd->GetTimeStamp(line, FALSE);
					pLstMcmd = pParMcmd;
		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], j:[%d]\n", flag, content, j);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif

				}
				else
				{
					//::AfxMessageBox("Executed Command appeared first!");
					i++;
					continue;
				}
			    ParStack.RemoveAt(ParStack.GetSize()-1);
				break;
		 case 3:
		 case 4:
		 case 5:
		 case 6:
			    if (pLstMcmd)
				{
					pLstMcmd->GetTimeStamp(line, FALSE);
				}
				pMcmd = new CMcmd;
				pMcmd->mcmd = content;
				pMcmd->beglin = i+1;
				//set endlin with beglin in case no end execution found.
				pMcmd->endlin = pMcmd->beglin;
				pMcmd->ID = seqnum;
				pMcmd->GetTimeStamp(line, TRUE);
				pMcmd->mcmdTyp = flag;

		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif



				if(ParStack.GetSize() == 0)
				{
					pMcmd->level = 1;
					pMcmd->Parent = NULL;
				}
				else
				{
					CMcmd *ParMcmd = (CMcmd *) ParStack.GetAt(ParStack.GetSize()-1);
					pMcmd->Parent = ParMcmd;
					pMcmd->level = ParMcmd->level + 1;
				}

				pLstMcmd = pMcmd;

				m_ObjArrMcmds.Add(pMcmd);
				seqnum++;

				break;

	     case 7:
			   if (pLstMcmd)
			   {
			       pLstMcmd->m_Prefix =  content;
				   pLstMcmd->m_TxtColor = RGB(255,0,0);
				   pLstMcmd->m_Bold = true;
				   pLstMcmd->GetTimeStamp(line, FALSE);
		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif
			   }
			   break;
	     case 8:

			   if (!pLstMcmd) break;

			   pLstMcmd->GetTimeStamp(line, FALSE);
			   pLstMcmd->endlin = i+1;
			   if (pLstMcmd && pLstMcmd->m_Prefix.Find("Status(") < 0)
			   {
				   if(content.Find(")") >=0 && pLstMcmd->m_Prefix.Find("0r) ") >= 0)
					 ;
				   else
			       pLstMcmd->m_Prefix =  content + pLstMcmd->m_Prefix;
			   }
		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif
			   break;

		case 9:
			break;
		case 10:
			    if (pLstMcmd)
				{
					pLstMcmd->GetTimeStamp(line, FALSE);
				}
				pMcmd = new CMcmd;
				pMcmd->mcmd = content;
				pMcmd->beglin = i+1;
				//set endlin with beglin in case no end execution found.
				pMcmd->endlin = pMcmd->beglin;
				pMcmd->ID = seqnum;
				pMcmd->mcmdTyp = 10;
				
				pMcmd->GetTimeStamp(line, TRUE);
				pMcmd->level = 1;
				pMcmd->Parent = NULL;

		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif

				ParStack.Add(pMcmd);
				m_ObjArrMcmds.Add(pMcmd);
				seqnum++;
				break;
		case 11:			    
			break;
		case 12:
				if(ParStack.GetSize() > 0)
				{
					pParMcmd = (CMcmd *)ParStack.GetAt(ParStack.GetSize()-1);
					//ASSERT(pParMcmd->mcmdTyp == 10);
				    pParMcmd->GetTimeStamp(line, FALSE);
					pParMcmd->endlin = i+1;
					ParStack.RemoveAt(ParStack.GetSize()-1);
				}
			    pLstMcmd = NULL;
		#ifdef TRACE_ON
		trace.Format("Case:[%d], content:[%s], i+1:[%d]\n", flag, content, i+1);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif
				
		}
		// if j increased because of no timestamp line, we skip those lines by set i=j, 
		// here we set i = j-1 ,because for loop will increase i++;
		if (j != i+1)
		{
			i=j - 1;
		}
        i++;
	}
	for (i=0;i<ParStack.GetSize();i++)
	{
		((CMcmd*)ParStack[i])->endlin = linenum;
		((CMcmd*)ParStack[i])->GetTimeStamp(line, FALSE);
		#ifdef TRACE_ON
		trace.Format("Handle Stacked Mcmd:[%s], endlin:[%d]\n", ((CMcmd*)ParStack[i])->mcmd, linenum);
		fprintf(file, trace.GetBuffer(trace.GetLength()));
        #endif
	}
		#ifdef TRACE_ON
	    fclose(file);
        #endif
	pPrg->ShowWindow(SW_HIDE);
	delete pPrg;

	te = CTime::GetCurrentTime();
	CString txt;
	txt.Format("Total time :%ld seconds", te.GetHour()*60*60+te.GetMinute()*60+te.GetSecond() -
		(ts.GetHour()*60*60+ts.GetMinute()*60+ts.GetSecond()));

	//AfxMessageBox(txt,MB_OK|MB_ICONINFORMATION);
	TRACE("Total mcmd %d\n", m_ObjArrMcmds.GetSize());
}

void CTraDoc::UpdateView()
{
	
	POSITION pos=this->GetFirstViewPosition();
	CView *pw =  this->GetNextView(pos);
	while(pw)
	{
		if(pw->IsKindOf(RUNTIME_CLASS(CTraView)))
		{

			if (m_bRefountRPanel)
			{
			CHARFORMAT2 cf;
            cf.cbSize = sizeof(cf);
         	cf.dwMask = CFM_COLOR |CFM_BOLD |CFM_FACE |CFM_WEIGHT | CFM_SIZE;
            cf.crTextColor = m_OptColor->m_BEYONDClr;
  
            cf.dwEffects = CFE_PROTECTED;
            cf.wWeight = 50;
         	cf.yHeight = 165;
	
        	::lstrcpy(cf.szFaceName,"Arial");	

        	CRichEditCtrl &CRE = ((CTraView*)pw)->GetRichEditCtrl();
        	CRE.SetBackgroundColor(false, m_OptColor->m_RPCOLORClr);
			
        	//CRE.SetSel(1,2);
			CRE.SetSel(1, CRE.GetWindowTextLength());
			CRE.SetWordCharFormat(cf);
        	
        	CRE.SetSel(0,0);
			m_bRefountRPanel = 0;
			if (this->m_ObjArrMcmds.GetSize() <=0)
				CRE.Clear();
			}


		//	CString txt = CString(100000);
			
			//if(this->m_ObjArrMcmds.GetSize()>0 && this->m_ObjArrMcmds.GetSize() > this->m_iFocusMcmd)
			//{
				/*CMcmd * pCurMcmd = (CMcmd*)this->m_ObjArrMcmds[this->m_iFocusMcmd-1];
				for(long i=0 ; i<= this->m_strArrLines.GetSize(); i++)
				{
					txt += this->m_strArrLines[i] + "\r\n";
				}
				::AfxMessageBox("add fininshed");
				pw->SetWindowText(txt);*/
				
			//}
		      
		}
		
		if(pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{

			 
			//::AfxMessageBox("hah");
           	 boolean selectflg = this->m_OptMoca->m_bIncludeSelect;
	         boolean updateflg = this->m_OptMoca->m_bIncludeUpdate;
	         boolean insertflg = this->m_OptMoca->m_bIncludeInsert;
	         boolean deleteflg = this->m_OptMoca->m_bIncludeDelete;
	         boolean mcmdflg = this->m_OptMoca->m_bIncludeMcmd;
			 long totalMcmd = this->m_ObjArrMcmds.GetSize();

			 CTreeCtrl &CTC = ((CTreeView *)pw)->GetTreeCtrl();

			 boolean bShowBKMKOnly = ((CLeftView *)pw)->m_bShowBKMK;

			 CTC.SetBkColor(m_OptColor->m_LPCOLORClr);
			 CTC.SetTextColor(m_OptColor->m_LPCOLORClr);

			 if (totalMcmd < 1) 
			 {
				CTC.DeleteAllItems();
				 return;
			 }

			 ((CLeftView*)pw)->m_bAddItemFinished = false;

			 CMcmd *pMcmd , *pNext, *pFstMcmd;
			 HTREEITEM hTreeItem, hParTreeItem;
			 CMcmd *pFst = (CMcmd *)m_ObjArrMcmds[0];
			 CMcmd *pLst = (CMcmd *)m_ObjArrMcmds[m_ObjArrMcmds.GetSize()-1];

             long tot_period_trace = pLst->end_time_stmp - pFst->beg_time_stmp;
             double thresh_hld = m_OptMoca->m_dThreshVal;
			 long totlinenum = m_OptMoca->m_iMaxLineNum;
			 int i;
			 CTC.ShowWindow(SW_HIDE);
			 CTC.DeleteAllItems();

			 m_MpMcmd_To_hHreeItem.RemoveAll();
			 m_MHreeItem_To_Mcmd.RemoveAll();
			 m_MpMcmd_To_hHreeItem.InitHashTable(m_ObjArrMcmds.GetSize() + (int)(m_ObjArrMcmds.GetSize()*0.2));
			 m_MHreeItem_To_Mcmd.InitHashTable(m_ObjArrMcmds.GetSize() + (int)(m_ObjArrMcmds.GetSize()*0.2));

			 int imgID = 1;

			 bool FirstNodeFlg = 1;
			 
			 for(i=0; i< totalMcmd && !bShowBKMKOnly; i++)
			 {
				 pMcmd = (CMcmd *)m_ObjArrMcmds[i];
				 pNext = i<totalMcmd - 1 ? (CMcmd *)m_ObjArrMcmds[i+1] : NULL;

				 if (pNext && pNext->Parent == pMcmd)
					 imgID = 0;
				 else 
					 imgID = 1;

				 switch(pMcmd->mcmdTyp)
				 {
				 case 1:
				 case 10:
					 if(!mcmdflg)
						 continue;
				 case 3:
				 case 4:
				 case 5:
				 case 6:
					 if(pMcmd->mcmdTyp == 3 && !selectflg)
						 continue;
					 else if(pMcmd->mcmdTyp == 4 && !updateflg)
						 continue;
					 else if(pMcmd->mcmdTyp == 5 && !insertflg)
						 continue;
					 else if(pMcmd->mcmdTyp == 6 && !deleteflg)
						 continue;
				 }

				 pMcmd->OverTimeWeight(tot_period_trace, thresh_hld, totlinenum);
				 pMcmd->SetDspStype();

				 if (FirstNodeFlg)
				 {
					 pFstMcmd = pMcmd;
					 FirstNodeFlg = 0;
				 }

			     


				 if(pMcmd->Parent == NULL)
				 {
				     hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
						                      pMcmd->m_bBookMarked? 2 : imgID,
											  pMcmd->m_bBookMarked? 2 : imgID,
						                      TVI_ROOT,
											  TVI_LAST);

					 m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					 m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
				 else
				 {
					 hParTreeItem = NULL;
					 m_MpMcmd_To_hHreeItem.Lookup(pMcmd->Parent, (void *&)hParTreeItem);
					 
					 if(hParTreeItem)
					 {
					     hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
							                      pMcmd->m_bBookMarked? 2 : imgID,
												  pMcmd->m_bBookMarked? 2 : imgID,
							                      hParTreeItem,
												  TVI_LAST);
					 }
					 else
					 {
						 hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
							                      pMcmd->m_bBookMarked? 2 : imgID,
												  pMcmd->m_bBookMarked? 2 : imgID,							                      
							                      TVI_ROOT,
												  TVI_LAST);
					 }

					m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
			 }

			 for(i=0; i< totalMcmd && bShowBKMKOnly; i++)
			 {
				 pMcmd = (CMcmd *)m_ObjArrMcmds[i];

				 if(!pMcmd->m_bBookMarked) continue;

				 if (FirstNodeFlg)
				 {
					 pFstMcmd = pMcmd;
					 FirstNodeFlg = 0;
				 }

				 if(pMcmd->Parent == NULL)
				 {
				     hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
						                      2,
											  2,
						                      TVI_ROOT,
											  TVI_LAST);

					 m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					 m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
				 else
				 {
					 hParTreeItem = NULL;
					 m_MpMcmd_To_hHreeItem.Lookup(pMcmd->Parent, (void *&)hParTreeItem);
					 
					 if(hParTreeItem)
					 {
					     hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
							                      2,
												  2,
							                      hParTreeItem,
												  TVI_LAST);
					 }
					 else
					 {
						 hTreeItem=CTC.InsertItem(pMcmd->m_Prefix + pMcmd->mcmd + pMcmd->m_Subfix,
							                      2,
												  2,							                      
							                      TVI_ROOT,
												  TVI_LAST);
					 }

					m_MpMcmd_To_hHreeItem.SetAt(pMcmd, hTreeItem);
					m_MHreeItem_To_Mcmd.SetAt(hTreeItem, pMcmd);
				 }
			 }

			 if(bShowBKMKOnly)
			 {
			     ((CLeftView *)pw)->m_bShowBKMK=false;
			 }

			 CTC.SetItemHeight(20);
			 CTC.ShowWindow(SW_SHOW);
			 ((CLeftView*)pw)->m_bAddItemFinished = true;
			 m_iFocusMcmd = pFstMcmd->ID;
			 this->UpdateAllViews(pw);
			 this->OnSelectChanged((CMcmd*)m_ObjArrMcmds[m_iFocusMcmd - 1]);
		}
		pw = this->GetNextView(pos);
	}

}

void CTraDoc::ClearDoc()
{
	for(long i=0;i<this->m_ObjArrMcmds.GetSize();i++)
	{
		delete m_ObjArrMcmds[i];
	}
	m_ObjArrMcmds.RemoveAll();
	m_strArrLines.RemoveAll();
	this->m_MHreeItem_To_Mcmd.RemoveAll();
	this->m_MpMcmd_To_hHreeItem.RemoveAll();

}

void CTraDoc::OnOptSetting() 
{
	// TODO: Add your command handler code here
	if(m_pSheet == NULL)
	{
		m_pSheet = new CPropertySheet("Setting");
		m_pSheet->AddPage(m_OptMoca);
		m_pSheet->AddPage(m_OptMtf);
		m_pSheet->AddPage(m_OptColor);
	}

	BOOL OriShowAll = m_OptMoca->m_bShowAll;
    CTraApp *pApp = (CTraApp *) ::AfxGetApp();
    pApp->ReadOptionsFromINI(this);

    long ans = m_pSheet->DoModal();
    if (ans == IDOK)
	{
        pApp->WriteOptionsToINI(this);
		if (OriShowAll != m_OptMoca->m_bShowAll)
		    m_bRefountRPanel = 1;
		this->OnRefreshView();
	}
    else if (ans == IDCANCEL)
    {

        pApp->ReadOptionsFromINI(this);

        //m_pSheet->UpdateData(FALSE);

    }
}


// 0. not mcmd mark
// 1. is mcmd begin
// 2. is mcmd end
// 3. is Select
// 4. is Update
// 5. is Insert
// 6. is Delete
// 7. is return code
// 8. is SQL return


// 9  is parsing mcmd begin
// 10 geting mcmd
// 11 parsing mcmd end
// 12 parsed mcmd finished

int CTraDoc::ParseLine(CString line, CString &mcmd)
{
	CString mcmdbeg, mcmdend;
	int mcmdbegidx, id1, id2, linlen = line.GetLength();
	static int WhatWeFound = -1;

	//convert to lowcase to do non case match
	line.MakeLower();


	// Check if mcmd header.
	int cnt = this->m_OptMoca->begs.GetSize();
	for(long i = 0; i< cnt; i++)
	{
		mcmdbeg = this->m_OptMoca->begs[i];
		mcmdend = this->m_OptMoca->ends[i];
		mcmdbeg.MakeLower();
		mcmdend.MakeLower();
		id1 = line.Find(mcmdbeg);
		id2 = line.Find(')');
		if(id1>0)
		{
			mcmdbegidx = line.Find('(', id1);
			if(mcmdbegidx >= 0)
			{
			    line = line.Right(linlen - mcmdbegidx - 1);
			    mcmd = line.Left(id2 > (mcmdbegidx + 1) ? id2 - (mcmdbegidx+1) : linlen);
			}
			else
			{
				// If we found something doesn't has '(', we get next word.

				line = line.Right(linlen - id1 - mcmdbeg.GetLength()-1);
				line = line.Right(linlen - line.Find("/") - 1);
				line.TrimLeft();
				mcmd = line;
			}
			if(mcmdbeg.Find("trigger") >= 0)
				mcmd = "Triggers: "+mcmd;
			WhatWeFound = 1;
			return 1;
		}

		id1 = line.Find(mcmdend);
		if(id1 >0)
		{
			id2 = id2 > 0 ? id2 : 0;

			mcmdbegidx = line.Find('/', id2);
			if(mcmdbegidx >=0 )
			{
			    line = line.Right(linlen - mcmdbegidx - 1);
			    mcmd = line.Left(id2 > 0 ? id2 : linlen);
			}
			else
			{
			    // If we found something doesn't has '/', we get what we found.
				mcmd = line.Right(linlen - id1);
			}
			WhatWeFound = 2;
			return 2;
		}
				
	}
	

	// Check if SQL
	static CString s1 = "==> select", s2 = "unbind:" , s3 = "==>  select", s4 = "==>   select";
	static CString u1 = "==> update", u2 = "unbind:" , u3 = "==>  update", u4 = "==>   update";
	static CString i1 = "==> insert", i2 = "unbind:" , i3 = "==>  insert", i4 = "==>   insert";
	static CString d1 = "==> delete", d2 = "unbind:" , d3 = "==>  delete", d4 = "==>   delete";

	static CString SA="Statement affected", SA2 = " row(s) affected", SA3 = " rows affected";
	static CString QR="Query returned", QR2 ="Throwing NotFoundException", QR3 = "no rows affected";
	static CString TP="==> T_PERF =", TP2 = "Execute Time: ";

	if(SA[0] == 'S')
	{
		SA.MakeLower();
		QR.MakeLower();
		QR2.MakeLower();
		TP.MakeLower();
		TP2.MakeLower();
	}

	// for 'delete from xxx where exists (select ...)' purpose we put delete ahead.
	if((line.Find("delete")>=0) && (line.Find(d1) >= 0 || line.Find(d2) >= 0 || line.Find(d3) >= 0 || line.Find(d4) >= 0))
	{
		if(line.Find("] ==>") < 0)
		{
		    mcmd = line.Right(linlen - line.Find("delete"));
		    WhatWeFound = 6;
		    return 6;
		}
	}

	if((line.Find("insert")>=0) && (line.Find(i1) >= 0 || line.Find(i2) >= 0 || line.Find(i3) >= 0 || line.Find(i4) >= 0) /*&& line.Find(':', line.Find("insert")) < 0*/)
	{
		if(line.Find("] ==>") < 0)
		{
		    mcmd = line.Right(linlen - line.Find("insert"));
		    WhatWeFound = 5;
		    return 5;
		}
	}

	

	if((line.Find("update") >= 0) && 
	   (line.Find(u1) >= 0 || line.Find(u2) >= 0 || line.Find(u3) >= 0 || line.Find(u4) >= 0) &&
	   (line.Find(':', line.Find("update")) < 0 || !::isalpha(line[line.Find(':', line.Find("update")) + 1])))
	{
		if(line.Find("] ==>") < 0 && !(line.Find("select") >= 0 && line.Find("select") < line.Find("update")))
		{
		    mcmd = line.Right(linlen - line.Find("update"));
		    WhatWeFound = 4;
		    return 4;
		}
	}


	if((line.Find("select")>=0) && (line.Find(s1) >= 0 || line.Find(s2) >= 0 || line.Find(s3) >= 0 || line.Find(s4) >= 0) && WhatWeFound != 3)
	{
		//Not Trunk, for trunk , we use "Executing SQL: select".
		if(line.Find("] ==>") < 0)
		{
		    mcmd = line.Right(linlen - line.Find("select"));
		    WhatWeFound = 3;
		    return 3;
		}
	}

	if((line.Find(TP) >= 0 || line.Find(TP2) >= 0 ) && WhatWeFound != 2)
	{
	    int idx = line.Find(TP) >= 0? line.Find(TP) : line.Find(TP2);
		CString suffix = line.Find(TP) >= 0? "s|" : "|";
		mcmd = "Status(" + line.Right(linlen - idx - 13) + suffix;
		WhatWeFound = 8;
		return 8;
	}
	// Check if Return code.
	if((line.Find(QR) >= 0 || line.Find(QR2) >= 0 || line.Find(QR3) >= 0) && WhatWeFound == 3)
	{
		if(line.Find(QR) >= 0)
		{
		    mcmd = line.Right(linlen - line.Find(QR) - 15);
		    mcmd = mcmd.Left(mcmd.Find("row")-1) +"r) ";
			WhatWeFound = 8;
			return 8;
		}
		else
		{
			mcmd = "0r) ";
			WhatWeFound = 8;
		    return 8;
		}
	}



	// Check if Return code.
	if(line.Find(SA) >= 0 && (WhatWeFound == 3 || WhatWeFound == 4 || WhatWeFound == 5 || WhatWeFound == 6))
	{
		mcmd = line.Right(linlen - line.Find(SA) - 19);
		mcmd = mcmd.Left(mcmd.Find("row")-1) +"r) ";
		WhatWeFound = 8;
		return 8;
	}


	// Check if Return code.
	if(line.Find(SA2) >= 0 && (WhatWeFound == 3 || WhatWeFound == 4 || WhatWeFound == 5 || WhatWeFound == 6))
	{
		mcmd = line.Left(line.Find(SA2));
		mcmd = mcmd.Right(mcmd.GetLength() - mcmd.Find("*** ") - 4) +"r) ";
		WhatWeFound = 8;
		return 8;
	}
   


	// Check if Return code.
	if(line.Find(SA3) >= 0 && (WhatWeFound == 3 || WhatWeFound == 4 || WhatWeFound == 5 || WhatWeFound == 6))
	{
		mcmd = line.Left(line.Find(SA3));
		mcmd = mcmd.Right(mcmd.GetLength() - mcmd.Find("*** ") - 4) +"r) ";
		WhatWeFound = 8;
		return 8;
	}

// Check if Return code.
	static CString errorstr ="*** raising error";
	if(line.Find(errorstr) >= 0)
	{
		mcmd = "Status("+line.Right(linlen - line.Find(errorstr) - 17) +") ";
		WhatWeFound = 7;
		return 7;
	}

	// Below is for exacting mcmd begin with parsing...
	/*if (line.Find("[0] parsing command") >= 0 && WhatWeFound != 10)
	{
		WhatWeFound = 9;
		return WhatWeFound;
	}
	else*/ if (line.Find("[0] server got: ") >= 0)
	{
		mcmd = line.Right(linlen - line.Find("[0] server got: ") - 16);
		WhatWeFound = 10;
	    return 10;
	}
	/*else if (line.Find("command initiated: [") >= 0)
	{
		mcmd = line.Right(line.GetLength() - line.Find("command initiated: [") - 21);
		mcmd = mcmd.Right(mcmd.GetLength() - (mcmd.Find("[") >= 0 ? 1 : 0));
		mcmd = mcmd.Left(mcmd.Find("]"));
		WhatWeFound = 10;
	    return 10;
	}*/

	/*if (WhatWeFound == 9)
	{
		mcmd = line.Right(line.GetLength() - line.Find("[0] ") - 4);
		WhatWeFound = 10;
	    return 10;
	}*/

	if (WhatWeFound == 10)
	{
		if (line.Find("[0] parsed command") >= 0)
		{
			WhatWeFound = 11;
			return WhatWeFound;
		}
		/*else
		{
		    mcmd = line.Right(line.GetLength() - line.Find("[0] "));
		return WhatWeFound;
		}*/
	}

	if (line.Find("[0] dispatched command") >= 0 || line.Find("] returning error") >= 0)
	{
		WhatWeFound = 12;
		return WhatWeFound;
	}

	return 0;
}

void CTraDoc::OnRefreshView() 
{
	// TODO: Add your command handler code here

	UpdateView();

    //this->m_iFocusMcmd = 1;
}

void CTraDoc::OnUpdateRefreshView(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowSelect() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = true;
	this->m_OptMoca->m_bIncludeUpdate = false;
	this->m_OptMoca->m_bIncludeInsert = false;
	this->m_OptMoca->m_bIncludeDelete = false;
	this->m_OptMoca->m_bIncludeMcmd = false;
	this->UpdateView();
}

void CTraDoc::OnUpdateShowSelect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowDelete() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = false;
	this->m_OptMoca->m_bIncludeUpdate = false;
	this->m_OptMoca->m_bIncludeInsert = false;
	this->m_OptMoca->m_bIncludeDelete = true;
	this->m_OptMoca->m_bIncludeMcmd = false;
	this->UpdateView();	
}

void CTraDoc::OnUpdateShowDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowMcmd() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = false;
	this->m_OptMoca->m_bIncludeUpdate = false;
	this->m_OptMoca->m_bIncludeInsert = false;
	this->m_OptMoca->m_bIncludeDelete = false;
	this->m_OptMoca->m_bIncludeMcmd = true;
	this->UpdateView();	
}

void CTraDoc::OnUpdateShowMcmd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowInsert() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = false;
	this->m_OptMoca->m_bIncludeUpdate = false;
	this->m_OptMoca->m_bIncludeInsert = true;
	this->m_OptMoca->m_bIncludeDelete = false;
	this->m_OptMoca->m_bIncludeMcmd = false;
	this->UpdateView();		
}

void CTraDoc::OnUpdateShowInsert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowUpdate() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = false;
	this->m_OptMoca->m_bIncludeUpdate = true;
	this->m_OptMoca->m_bIncludeInsert = false;
	this->m_OptMoca->m_bIncludeDelete = false;
	this->m_OptMoca->m_bIncludeMcmd = false;
	this->UpdateView();	
}

void CTraDoc::OnUpdateShowUpdate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OnShowAll() 
{
	// TODO: Add your command handler code here
	this->m_OptMoca->m_bIncludeSelect = true;
	this->m_OptMoca->m_bIncludeUpdate = true;
	this->m_OptMoca->m_bIncludeInsert = true;
	this->m_OptMoca->m_bIncludeDelete = true;
	this->m_OptMoca->m_bIncludeMcmd = true;
	this->UpdateView();		
}

void CTraDoc::OnUpdateShowAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_ObjArrMcmds.GetSize()>0);
}

void CTraDoc::OpenFile(CString &fileName)
{

	if (m_OptMoca->m_bSupMod && m_pf)
		m_pf->Close();

	if (m_pf)	
	    delete m_pf;

	ClearDoc();
	m_trcTyp = MOCATRACE;
    m_sFileName = fileName;
	m_pf = new CTraFile();

	if (!IsDosFormat(fileName))
	{
		long ret = AfxMessageBox("Converting to DOS format?", MB_YESNO|MB_ICONQUESTION);
		if (ret == IDYES)
		{
		    m_pf->ConvertToDosFormat(fileName);
			m_sFileName = fileName;
		}
		else
		{
			::AfxMessageBox("File " + m_sFileName + " is not a DOS format, please convert to DOS format before processing.", MB_OK|MB_ICONINFORMATION);
			return;
		}
	}
	
	m_pf->InitFile(fileName, 
		           this->m_strArrLines,
				   this->m_OptMoca->m_bShowAll,
				   this->m_OptMoca->m_bSupMod,
				   this->m_trcTyp);

    if(m_trcTyp == MOCATRACE)
	{

	    ExactMcmd();
	}
	else
	{

		ExactMcmdForMTF();
	}

	if (!this->m_OptMoca->m_bSupMod)
	{
		m_pf->Close();
	}



	if (m_ObjArrMcmds.GetSize() <= 0)
	{
		POSITION pos=this->GetFirstViewPosition();
	    CView *pw =  this->GetNextView(pos);
	    while(pw)
		{
		    if(pw->IsKindOf(RUNTIME_CLASS(CTraView)))
			{
			    ((CTraView*)pw)->GetRichEditCtrl().SetWindowText("");		      
			}
		
		    if(pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
			{
			    ((CLeftView*)pw)->GetTreeCtrl().DeleteAllItems();
			}
            pw = this->GetNextView(pos);
		}
		::AfxMessageBox("No moca command or SQL found in the trace file!", MB_OK|MB_ICONINFORMATION);
		return;
	}

	m_iFocusMcmd = 1;

	m_bNewFileFlg = true;

	m_BegLinId = CalBegLinId();
	m_EndLinId = CalEndLinId();
	
	OnRefreshView();
    ::AfxGetApp()->m_pMainWnd->SetWindowText(fileName);

	CMainFrame * pMain = (CMainFrame *)::AfxGetApp()->m_pMainWnd;
	pMain->m_wndSplitter.ShowWindow(SW_SHOW);
	pMain->ShowControlBar(&pMain->m_wndToolBar, true, false);
	pMain->ShowControlBar(&pMain->m_wndStatusBar, true, false);
	
	//::AfxMessageBox(fileName);
}

void CTraDoc::OnShowGrph() 
{
	// TODO: Add your command handler code here
	CGphDlg dlg;
	dlg.m_pDoc = this;
	if(m_ObjArrMcmds.GetSize() > 0)
	{
	    dlg.m_RootMcmd = (CMcmd*) this->m_ObjArrMcmds[this->m_iFocusMcmd-1];
	}
	else
		dlg.m_RootMcmd = NULL;
	dlg.DoModal();
}

void CTraDoc::ExactMcmdForMTF()
{


	long linenum = m_strArrLines.GetSize();
	if(linenum <= 0)
		return;

	long i, seqnum =1, flag=0,j;
	CString line, nxtline, content;
	CMcmd *pMcmd, *pLstMcmd = NULL, *pParMcmd = NULL;
	CObArray ParStack;
	CInProgress *pPrg = new CInProgress;
	pPrg->Create(IDD_IN_PROGRESS, ::AfxGetApp()->GetMainWnd());
	pPrg->SetOwner(::AfxGetApp()->GetMainWnd());
	pPrg->CenterWindow();
	pPrg->ShowWindow(SW_SHOW);
	pPrg->m_cInPrg.SetRange(0,100);
	//TRACE("linenum is %ld ", linenum);
	for(i=0; i<linenum; i++)
	{
		if((i+1) % 100 == 0)
		{
		    pPrg->m_cInPrg.SetPos((int)(i*1.0/linenum*100.0));
		}
		//TRACE("i= '%ld'\n",i);
        line = m_strArrLines[i];
		j = i + 1;

		while (j < linenum)
		{
			nxtline = m_strArrLines[j];
			if(nxtline.Find(':') < 0)
			{
				line += nxtline;
				j++;
			}
			else
			{
				break;
			}
		}

		flag = ParseLineForMTF(line , content);

		switch(flag)
		{
		case 1:
				pMcmd = new CMcmd;
				pMcmd->mcmd = content;
				pMcmd->beglin = i+1;
				//set endlin with beglin in case no end execution found.
				pMcmd->endlin = pMcmd->beglin;
				pMcmd->ID = seqnum;
				pMcmd->mcmdTyp = 1;
			
				//TRACE("%s\n",pMcmd->mcmd);
				
				pMcmd->GetTimeStamp(line, TRUE);
				
				pMcmd->level = 1;
				pMcmd->Parent = NULL;

				if(ParStack.GetSize() > 0)
				{
					CMcmd *ParMcmd = (CMcmd *) ParStack.GetAt(ParStack.GetSize()-1);
					ParMcmd->endlin = pMcmd->beglin-1;

					ParMcmd->GetTimeStamp(line, FALSE);

					ParMcmd->endlin = ParMcmd->endlin>=ParMcmd->beglin ? ParMcmd->endlin : ParMcmd->beglin;
					pMcmd->Parent = ParMcmd;
					ParMcmd->Parent = NULL;
					ParStack.RemoveAt(ParStack.GetSize()-1);
				}
				ParStack.Add(pMcmd);
				m_ObjArrMcmds.Add(pMcmd);
				seqnum++;
				break;
		case 2:
				if(ParStack.GetSize() > 0)
				{
					CMcmd *ChldMcmd = (CMcmd *) ParStack.GetAt(ParStack.GetSize()-1);

					ChldMcmd->GetTimeStamp(line, FALSE);

					ChldMcmd->endlin = i+1;
					ChldMcmd->endlin = ChldMcmd->endlin>=ChldMcmd->beglin ? ChldMcmd->endlin : ChldMcmd->beglin;
					ParStack.RemoveAt(ParStack.GetSize()-1);
					if (ChldMcmd->Parent)
					{
						ParStack.Add(ChldMcmd->Parent);
					}
				}
		}
		// if j increased because of no timestamp line, we skip those lines by set i=j, 
		// here we set i = j-1 ,because for loop will increase i++;
		if (j != i+1)
		{
			i=j - 1;
		}

	}

	for (i=0;i<ParStack.GetSize();i++)
	{
		((CMcmd*)ParStack[i])->endlin = linenum;
		((CMcmd*)ParStack[i])->GetTimeStamp(line, FALSE);
	}

	pPrg->ShowWindow(SW_HIDE);
	delete pPrg;
	TRACE("Total mcmd %d\n", m_ObjArrMcmds.GetSize());

}

// 0 nothing
// 1 new form
// 2 new block

int CTraDoc::ParseLineForMTF(CString line, CString &form)
{

	CString formmark;
	static int NewFormFound = 0;

	//convert to lowcase to do non case match
	line.MakeLower();
	// Check if mcmd header.
	int cnt = this->m_OptMtf->marks.GetSize();
	for(long i = 0; i< cnt; i++)
	{
		formmark = this->m_OptMtf->marks[i];
		formmark.MakeLower();
		if(line.Find(formmark)>0)
		{
			if (line.Find("[") >= 0)
			{
				form = line.Right(line.GetLength() - line.Find("[")-1);
				form = form.Left(form.Find("]"));
				form.MakeUpper();
				if (formmark.Find("unwind") >= 0)
				{
					form = form+"<";
				}
				else
				{
				    form = ">"+form;
				}

			}
			else
			{
				form = line.Right(line.GetLength() - line.Find(">") -2);
				form.MakeUpper();
				form = form +"<";
			}
			return 1;
		}		
	}

	if (line.Find("and returning (fformresult)") >=0 || line.Find("linked command key (vkid_f1) to command (cmdfkeyback)") >= 0)
	{
		// last mcmd needs parent
		return 2;
	}


	return 0;
}

void CTraDoc::OnShowBkmk() 
{
	// TODO: Add your command handler code here
	POSITION pos=this->GetFirstViewPosition();
	CView *pw =  this->GetNextView(pos);
	while(pw)
	{		
		if(pw->IsKindOf(RUNTIME_CLASS(CLeftView)))
		{

			((CLeftView*)pw)->m_bShowBKMK = true;
			break;
		}
		pw = this->GetNextView(pos);
	}
	this->UpdateView();		
}

void CTraDoc::OnUpdateShowBkmk(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	for(int i = 0; i< this->m_ObjArrMcmds.GetSize(); i++)
	{
		if(((CMcmd*)this->m_ObjArrMcmds[i])->m_bBookMarked)
		{
			pCmdUI->Enable();
			return;
		}
	}
	pCmdUI->Enable(FALSE);
}


void CTraDoc::OnSelectChanged(CMcmd *SelectMcmd)
{
	m_iFocusMcmd = SelectMcmd->ID;

	
	m_BegLinId = CalBegLinId();
	m_EndLinId = CalEndLinId();

    UpdateAllViews(NULL);
}

unsigned long CTraDoc::CalBegLinId()
{
	CMcmd *pCurMcmd = (CMcmd *) m_ObjArrMcmds[m_iFocusMcmd-1];

	long beglin;
	long MrgLinNum = 50;

	if (m_iFocusMcmd == 1 || m_OptMoca->m_bShowAll)
		return 1;

    CMcmd *Pre = (CMcmd*)m_ObjArrMcmds[pCurMcmd->ID-2];
	//If previous mcmd is parent, beglin shoud be Pre->beglin.
	if (Pre == pCurMcmd->Parent)
		beglin = Pre->beglin;
	else
		beglin = Pre->endlin;

	beglin = (pCurMcmd->beglin - beglin) < MrgLinNum ? pCurMcmd->beglin - MrgLinNum : beglin;
	beglin = beglin <= 0 ? 1 : beglin;
	return beglin;


	/*if(m_OptMoca->m_bShowSingle)
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


			//begpos = GetRichEditCtrl().LineIndex(beglin - 1);
			CString tb, te;
			pDoc->m_pf->GetLine(tb, beglin);
			begpos = text.Find(tb, begpos);
		    //begpos = text.Find(pDoc->m_strArrLines[beglin-1], begpos);

			endlin = pCurMcmd->endlin;
			pDoc->m_pf->GetLine(te, endlin);
            endpos = text.Find(te);

			//endpos = text.Find(pDoc->m_strArrLines[endlin-1]);

			int NxtID = pCurMcmd->ID + 1;
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
			}
		}
	    else
		{
		    beglin = pCurMcmd->beglin;
			CString tmp;
			pDoc->m_pf->GetLine(tmp, beglin);
			begpos = text.Find(tmp);
		    //begpos = text.Find(pDoc->m_strArrLines[beglin-1]);

			endlin = pCurMcmd->endlin;
			pDoc->m_pf->GetLine(tmp, endlin);
			endpos = text.Find(tmp);
			//endpos = text.Find(pDoc->m_strArrLines[endlin-1]);
		}
	}
	return 0;*/

}

unsigned long CTraDoc::CalEndLinId()
{
	CMcmd *pCurMcmd = (CMcmd *) m_ObjArrMcmds[m_iFocusMcmd-1];

	unsigned long endlin;

	unsigned MrgLinNum = 50;

	if (m_iFocusMcmd == m_ObjArrMcmds.GetSize() || m_OptMoca->m_bShowAll)
		return m_pf->GetTotLin();

    CMcmd *Aft = (CMcmd*)m_ObjArrMcmds[pCurMcmd->ID];
	//If Cur mcmd is parent, beglin shoud be Aft->beglin.
	if (Aft->Parent == pCurMcmd)
		endlin = pCurMcmd->endlin;
	else
		endlin = Aft->beglin;

	endlin = (endlin - pCurMcmd->endlin) < MrgLinNum ? pCurMcmd->endlin + MrgLinNum : endlin;
	endlin = endlin >= m_pf->GetTotLin() ? m_pf->GetTotLin() : endlin;

	return endlin;
}

bool CTraDoc::IsDosFormat(CString &filename)
{
    CFile fl;
	if (!fl.Open(filename, CFile::modeRead))
	{
		//cout<<"Can not open file "<<fileName<<endl;
		exit(0);
	}

	this->m_fileLength = fl.GetLength();

	char buff[500];

	fl.Read(buff, 500);

	for(int i=1;i<500;i++)
	{
		if (buff[i-1] != '\r' && buff[i] == '\n')
		{
			//::AfxMessageBox("File " + filename + " is not a DOS format, please convert to DOS format before processing.", MB_OK|MB_ICONINFORMATION);
			fl.Close();
			return false;
		}
	}

	fl.Close();
	return true;
}


void CTraDoc::OnFileExport() 
{
	// TODO: Add your command handler code here
	CExportDlg dlg;

	dlg.m_nFrm = 1;
	dlg.m_nTo = m_ObjArrMcmds.GetSize();
	dlg.m_nMaxID = dlg.m_nTo;
	//dlg.UpdateData(false);

    if(dlg.DoModal()!=IDOK)
		return;

	BOOL nodeOnly = dlg.m_bExpNodeOnly;
	BOOL selectOnly = dlg.m_bSelOnly;
	long frm = dlg.m_nFrm;
	long to = dlg.m_nTo;
	CString filename = dlg.m_sFileName;

	if (selectOnly)
	{
		frm = to = this->m_iFocusMcmd;
	}

    CFile fl;
	if (!fl.Open(filename, CFile::modeCreate|CFile::modeReadWrite))
	{
		//cout<<"Can not open file "<<fileName<<endl;
		exit(0);
	}

	if (nodeOnly)
	{
		if (frm == to)
		{
			CMcmd *p = (CMcmd*)m_ObjArrMcmds[frm-1];

			while(to < m_ObjArrMcmds.GetSize())
			{
			    CMcmd *pNxt = (CMcmd*)m_ObjArrMcmds[to];
				if (pNxt->level <= p->level)
					break;
				to++;
			}

		}

	    for (long i=frm; i<= to; i++)
		{
			CMcmd *p = (CMcmd*)m_ObjArrMcmds[i-1];
			CMcmd *pNxt = NULL;
			
			if (i==to)
				pNxt = NULL;
			else
			{
				pNxt = (CMcmd*)m_ObjArrMcmds[i];
			}
			BOOL isLeaf = !pNxt ? TRUE : (pNxt->level <= p->level);
			CString s = isLeaf ? "    " : "   +";

			int j;
			for (j=0; j<p->level-1; j++)
			{
				fl.Write("    ",4);
			}



			fl.Write(p->m_Prefix, p->m_Prefix.GetLength());
			fl.Write(p->mcmd, p->mcmd.GetLength());
			fl.Write(p->m_Subfix, p->m_Subfix.GetLength());

			if (!isLeaf)
			{
				fl.Write("+",1);
			}

			fl.Write("\r\n", 2);
		}
		fl.Close();
		AfxMessageBox("Nodes exported successful!", MB_OK|MB_ICONINFORMATION);
	}
	else
	{

		CMcmd *p = (CMcmd*)m_ObjArrMcmds[frm-1];
		long linFrm = p->beglin;

		p = (CMcmd*)m_ObjArrMcmds[to-1];

		long linTo = p->endlin;

		for (long i=linFrm-1; i<linTo; i++)
		{

			fl.Write(m_strArrLines[i], m_strArrLines[i].GetLength());
			fl.Write("\r\n",2);

		}

		fl.Close();
		
		AfxMessageBox("Trace exported successful!", MB_OK|MB_ICONINFORMATION);
	}
}

void CTraDoc::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ObjArrMcmds.GetSize() > 0);
}

typedef struct para
{
	CTraDoc *p;
	BYTE a1;
	BYTE a2;
	BYTE a3;
	BYTE a4;
} PARAFT;

PARAFT paraft;

unsigned WINAPI FileTrnsf(void *arg) 
{
	// TODO: Add your command handler code here

	PARAFT *p = (PARAFT*) arg;
		if (p->p->m_sFileName.GetLength() > 0)
		{
			SOCKET servSock;
			REQACK action = TRANFILE;
			char msg[1024];

			int clnSz;

			 SOCKADDR_IN clnAdr;

			 servSock = socket(AF_INET, SOCK_STREAM, 0);

			 if (servSock == INVALID_SOCKET)
			 {
				 AfxMessageBox("Can not create server socket!", MB_OK|MB_ICONERROR);
				 return -1;
			 }

			 CString ip;
			 //ip.Format("%d.%d.%d.%d", 127,0,0,1);
			 ip.Format("%d.%d.%d.%d", p->a1,p->a2,p->a3,p->a4);

			 //AfxMessageBox(ip);

			 DWORD IPPP=inet_addr(ip);

			 clnAdr.sin_family = AF_INET;
			 clnAdr.sin_addr.s_addr = IPPP;
			 clnAdr.sin_port = htons(34);

			 clnSz = sizeof clnAdr;

			 if (connect(servSock, (SOCKADDR*) &clnAdr,  clnSz) == SOCKET_ERROR)
			 {
		        AfxMessageBox("Connect error");
	            return -1;
			 }

			 memcpy(msg, &action, sizeof action);
			 memcpy(msg+sizeof action, (LPCTSTR)p->p->m_sFileName, p->p->m_sFileName.GetLength());

			 //strcpy(msg, "hello, sam");

			 send(servSock, 
				    msg,
					sizeof action + p->p->m_sFileName.GetLength(),
					0);

			 //Sleep(5000);

			 memset(msg, 0, sizeof msg);
			
			 recv(servSock,
				      msg,
					  1024,
					  0);

			action = *((REQACK*)msg);

			 if (action == REFUSE)
			 {
				 CString msg;
				 msg.Format("Remote ip[%s] refused your request!", inet_ntoa(clnAdr.sin_addr));
	
				 AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
				 return 0;
			 }
			 else {
				 AfxMessageBox("Now start file transferring");

				 CStdioFile f;

				 if (!f.Open(p->p->m_sFileName, CFile::modeRead))
				 {
					 AfxMessageBox("Can not open file to transfer!", MB_OK|MB_ICONERROR);
					 return -1;
				 }
				 else {

					 CString line;

					 while(f.ReadString(line))
					 {

					     strcpy(msg, (LPCTSTR) line);
			             send(servSock, 
				                msg,
					            strlen(msg),
					            0);
					 }
					 f.Close();
					 //closesocket(servSock);
				 }

			 }

			 //closesocket(servSock);
			 return 0;
		}
	return 0;
}

void CTraDoc::OnFileTrnsf() 
{	
	if (m_dtf.DoModal() == IDOK)
	{
		paraft.p = this;
		paraft.a1 = m_dtf.a1;
		paraft.a2 = m_dtf.a2;
		paraft.a3 = m_dtf.a3;
		paraft.a4 = m_dtf.a4;

	    //_beginthreadex(NULL, 0, FileTrnsf, &paraft, 0, NULL);

		if (m_sFileName.GetLength() > 0)
		{

			REQACK action = TRANFILE;

        	m_SndFileSocket.ShutDown(2);
	        m_SndFileSocket.m_hSocket = INVALID_SOCKET;
	        m_SndFileSocket.m_bConnected = FALSE;
			m_SndFileSocket.m_bStartTrn = false;
			m_SndFileSocket.setFileForSend(m_sFileName);


			 CString ip;
			 //ip.Format("%d.%d.%d.%d", 127,0,0,1);
			 ip.Format("%d.%d.%d.%d", m_dtf.a1,m_dtf.a2,m_dtf.a3,m_dtf.a4);

			 //AfxMessageBox(ip);

			 if (m_SndFileSocket.m_hSocket == INVALID_SOCKET)
			 {
				 BOOL bFlag = m_SndFileSocket.Create(0, SOCK_STREAM, FD_CONNECT);
		         if(!bFlag)
				 {
			         AfxMessageBox("Socket error!");
			         m_SndFileSocket.Close();
			         return;
				 }
			 }

	         m_SndFileSocket.Connect(ip, 34);

			 //memcpy(m_SndFileSocket.m_szBuffer, &action, sizeof action);
			 memset(m_SndFileSocket.ackmsg, 0, sizeof m_SndFileSocket.ackmsg);

			 sprintf(m_SndFileSocket.ackmsg, "%s, size:%u", (LPCTSTR)m_sFileName, m_fileLength);
			 //memcpy(m_SndFileSocket.m_szBuffer, (LPCTSTR)m_sFileName, m_sFileName.GetLength());
			 //m_SndFileSocket.Send(m_SndFileSocket.m_szBuffer, strlen(m_SndFileSocket.m_szBuffer), 0);

			 m_SndFileSocket.AsyncSelect(FD_WRITE);

		}
	}
}

void CTraDoc::OnUpdateFileTrnsf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(this->m_sFileName.GetLength() > 0);
}
