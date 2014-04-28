// Mcmd.cpp: implementation of the CMcmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Tra.h"
#include "Mcmd.h"
#include "TraDoc.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMcmd::CMcmd()
{
    CMainFrame *pMrm=(CMainFrame*)::AfxGetMainWnd();
    CTraDoc *pDoc =(CTraDoc*)pMrm->GetActiveDocument();

	m_TxtColor=pDoc->m_OptColor->m_MCMDClr;
    m_Bold =false;
	m_Prefix = "";
	m_Subfix = "";
	m_bBookMarked = false;
}

CMcmd::~CMcmd()
{

}

void CMcmd::GetTimeStamp(CString line, boolean beg_flg)
{
	if(line.Find(':',0) < 0)
	{
		CString t;
		t.Format("Time Stamp for ID[%ld], mcmd[%s] not found!", this->ID, this->mcmd);
		//::AfxMessageBox(t);
		if(beg_flg)
		{
		    this->beg_time_stmp = 0;
			this->end_time_stmp = 0;
		}
		else
		{
			this->end_time_stmp = 0;
		}
		return;
	}
	//skip mtf trace's ':' by skipping first 6 chars
	int begpos = line.Find(':',6);
	line = line.Right(line.GetLength() - begpos + 2);
	begpos = line.Find(' ',0);
	line = line.Left(begpos);
	//TRACE(line + "\n");
	CString h = line.Left(2);
	line = line.Right(line.GetLength() - 3);
	CString m = line.Left(2);
	line = line.Right(line.GetLength() - 3);
	CString s = line.Left(2);
	line = line.Right(line.GetLength() - 3);
	CString ms= line;
	//TRACE("H:"+h+"M:"+m+"S:"+s+"MS:"+ms+"\n");
	
	long lh, lm,ls,lms;
	lh=::atol(h);
	lm=::atol(m);
	ls=::atol(s);
	lms=::atol(ms);
	if(beg_flg)
	{
		//Set end with start in case no end execution found.
	    this->beg_time_stmp = lh*3600*1000 + lm*60*1000 + ls*1000 + lms;
		this->end_time_stmp = lh*3600*1000 + lm*60*1000 + +ls*1000 + lms;
	}
	else
	{
		this->end_time_stmp = lh*3600*1000 + lm*60*1000 + +ls*1000 + lms;
		long perid = end_time_stmp - beg_time_stmp;
		double timespent = perid / 1000.0;
		if(timespent >= 0.001)
		{
			CString stmp;
			stmp.Format("(%0.3lfs)",timespent);
			m_Subfix = stmp;
		}
	}
	return;
}

boolean CMcmd::OverTimeWeight(long time_of_trace, double thresh_hld , long totlinnum)
{
	if(this->Parent == NULL)
	{
		long period = this->end_time_stmp-this->beg_time_stmp;
		if((double)period/time_of_trace > thresh_hld)
		{
			
			this->m_Bold = true;
			return TRUE;
		}
		else if (this->mcmdTyp == 10)
		{
			if (this->endlin - this->beglin >= totlinnum)
			{
				
			    this->m_Bold = true;
			    return TRUE;
			}
			else
			{
				this->m_Bold = false;
				return FALSE;
			}
		}
        else
		{
			
			this->m_Bold = false;
			return FALSE;
		}
	}
	else
	{
		long par_period=this->Parent->end_time_stmp-this->Parent->beg_time_stmp;
		long period = this->end_time_stmp-this->beg_time_stmp;
		if((double)period/par_period > thresh_hld)
		{
			this->m_Bold = true;
			return TRUE;
		}
		else
		{
			this->m_Bold = false;
			return FALSE;
		}
	}
}

void CMcmd::SetDspStype()
{
    CMainFrame *pMrm=(CMainFrame*)::AfxGetMainWnd();
    CTraDoc *pDoc =(CTraDoc*)pMrm->GetActiveDocument();

	if (pDoc->m_trcTyp == MOCATRACE)
	{
				switch (this->mcmdTyp)
				{
				case 1:
					if(m_Prefix.Find("Status") >= 0)
						m_TxtColor = pDoc->m_OptColor->m_ERRClr;
					else
						m_TxtColor = pDoc->m_OptColor->m_MCMDClr;
					break;
				case 3://select
					m_TxtColor = pDoc->m_OptColor->m_SELECTClr;
					break;
				case 4://update
					m_TxtColor = pDoc->m_OptColor->m_UPDATEClr;
					break;
				case 5://insert
					m_TxtColor = pDoc->m_OptColor->m_INSERTClr;
					break;
				case 6://delete
					m_TxtColor = pDoc->m_OptColor->m_DELClr;
					break;
				case 10://Parse mcmd
					m_TxtColor = pDoc->m_OptColor->m_MCMDClr;
					
					CMcmd *LstChd = NULL;
						for(int i = this->ID; i< pDoc->m_ObjArrMcmds.GetSize(); i++)
						{
							if(((CMcmd*)pDoc->m_ObjArrMcmds[i])->mcmdTyp == 10)
								break;
							else if (((CMcmd*)pDoc->m_ObjArrMcmds[i])->level == 2)
							{
								LstChd = (CMcmd*)pDoc->m_ObjArrMcmds[i];
							}
						}

						if(LstChd && LstChd->m_Prefix.Find("Status") >= 0)
						{
							this->m_TxtColor = LstChd->m_TxtColor;
							this->m_Prefix = LstChd->m_Prefix;
							this->m_Subfix = LstChd->m_Subfix;
						}

					break;
				}
	}
	else
	{
				switch (this->mcmdTyp)
				{
				case 1:
						m_TxtColor = pDoc->m_OptColor->m_MCMDClr;
					break;
				}

	}

}

void CMcmd::DrawSelf(CDC *pDC, CRect &rt)
{
	CBrush b = RGB(255,0,255);
	CBrush b2 = RGB(255,255,0);
	pDC->SetBkMode(TRANSPARENT);
	int ty = rt.top + (rt.bottom - rt.top)/2 -10;
	int tx = rt.left + 20;
	switch (mcmdTyp)
	{
	case 1:
		
	    pDC->SelectObject(&b);
	    pDC->Rectangle(rt);
		pDC->TextOut(tx,ty,this->mcmd.Left(60));
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	    pDC->SelectObject(&b2);
	    pDC->Rectangle(rt);
		pDC->TextOut(tx,ty,this->mcmd.Left(60));
		break;
	}

}
