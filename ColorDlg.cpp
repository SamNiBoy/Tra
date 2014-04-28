// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tra.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg property page


IMPLEMENT_DYNCREATE(CColorDlg, CPropertyPage)

CColorDlg::CColorDlg() : CPropertyPage(CColorDlg::IDD)
{
	//{{AFX_DATA_INIT(CColorDlg)
	m_iB = 255;
	m_iG = 0;
	m_iR = 0;
	m_sLPTxt = _T("");
	m_sRPTxt = _T("");
	//}}AFX_DATA_INIT
	m_eSelected = RANGE;
	m_sLPTxt = "\r\n"\
		       "   + Mcmd xxxx\r\n"\
			   "\r\n"\
		       "   + Select xxxx\r\n"\
			   "\r\n"\
			   "   + Update xxxx\r\n"\
			   "\r\n"\
			   "   + Insert xxxx\r\n"\
			   "\r\n"\
			   "   + Delete xxxx\r\n"
			   "\r\n"\
			   "   + Status(ERCD)\r\n";

	m_sRPTxt = "Text beyond interest "\
			   "\r\n"\
		       "Server got: Mcmd xxx\r\n"\
               "Looking up Command: mcmd\r\n"\
               "Argument  trlr_num = 'xxx'\r\n"\
               "Published  trlr_num ='yyy'\r\n"\
               "Parameter  wh_id    ='zzz'\r\n"\
               "-----------------------------------\r\n"\
		       "Select xxxx\r\n"\
			   "Update xxxx\r\n"\
			   "Insert xxxx\r\n"\
			   "Delete xxxx\r\n"
               "-----------------------------------\r\n"\
               "Executed Command: package/mcmd\r\n"\
               "Dispatched command\r\n"\
			   "Text beyond interest ";

	m_RANGEClr = RGB(0,0,255);    
	m_BEYONDClr = RGB(50,50,50);
	m_ERRClr = RGB(255,0,0);
    m_MCMDClr  = RGB(0, 0,0);     
    m_SELECTClr= RGB(0, 155,0);
    m_UPDATEClr= RGB(0, 155,155);   
    m_INSERTClr= RGB(155, 155,0);  
    m_DELClr   = RGB(155, 0,155);  
    m_LPCOLORClr= RGB(150, 150, 150);
    m_RPCOLORClr= RGB(150, 150, 150);
    m_VALUEClr  = RGB(200,200,00);    
    m_PARAMETERClr= RGB(255,255,0);
    m_ARGUMENTClr = RGB(255,0,0);
    m_PUBLISHClr  = RGB(0,255,255);  


	m_eSelected = RANGE;
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Slider(pDX, IDC_SLD_B, m_iB);
	DDX_Slider(pDX, IDC_SLD_G, m_iG);
	DDX_Slider(pDX, IDC_SLD_R, m_iR);
	DDX_Text(pDX, IDC_EDT_LP, m_sLPTxt);
	DDX_Text(pDX, IDC_EDT_RP, m_sRPTxt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_BN_CLICKED(IDC_RD_Argument, OnRDArgument)
	ON_BN_CLICKED(IDC_RD_Delete, OnRDDelete)
	ON_BN_CLICKED(IDC_RD_Insert, OnRDInsert)
	ON_BN_CLICKED(IDC_RD_LPColor, OnRDLPColor)
	ON_BN_CLICKED(IDC_RD_Mcmd, OnRDMcmd)
	ON_BN_CLICKED(IDC_RD_Parameter, OnRDParameter)
	ON_BN_CLICKED(IDC_RD_Publish, OnRDPublish)
	ON_BN_CLICKED(IDC_RD_Range, OnRDRange)
	ON_BN_CLICKED(IDC_RD_RPColor, OnRDRPColor)
	ON_BN_CLICKED(IDC_RD_Select, OnRDSelect)
	ON_BN_CLICKED(IDC_RD_Update, OnRDUpdate)
	ON_BN_CLICKED(IDC_RD_Value, OnRDValue)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_B, OnReleasedcaptureSldB)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_B, OnCustomdrawSldB)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLD_G, OnOutofmemorySldG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_G, OnCustomdrawSldG)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_G, OnReleasedcaptureSldG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLD_R, OnCustomdrawSldR)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLD_R, OnReleasedcaptureSldR)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	ON_BN_CLICKED(IDC_RD_Beyond, OnRDBeyond)
	ON_BN_CLICKED(IDC_RD_Error, OnRDError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorDlg message handlers

void CColorDlg::OnRDArgument() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = ARGUMENT;
	
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);
	COLORREF tmp = m_ARGUMENTClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_ARGUMENTClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDDelete() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = DEL;
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);
	
	COLORREF tmp = m_DELClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_DELClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDInsert() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = INSERT;
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);
	COLORREF tmp = m_INSERTClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_INSERTClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDLPColor() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = LPCOLOR;
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_LPCOLORClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_LPCOLORClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDMcmd() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = MCMD;
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_MCMDClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_MCMDClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDParameter() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = PARAMETER;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);
	COLORREF tmp = m_PARAMETERClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_PARAMETERClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDPublish() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = PUBLISH;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_PUBLISHClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_PUBLISHClr = tmp;
	ReColoring();

}

void CColorDlg::OnRDRange() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = RANGE;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);


	COLORREF tmp = m_RANGEClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_RANGEClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDBeyond() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = BEYOND;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_BEYONDClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_BEYONDClr = tmp;
	ReColoring();	
}

void CColorDlg::OnRDError() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = ERR;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_ERRClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_ERRClr = tmp;
	ReColoring();	
}


void CColorDlg::OnRDRPColor() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = RPCOLOR;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_RPCOLORClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_RPCOLORClr = tmp;
	ReColoring();

}

void CColorDlg::OnRDSelect() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = SELECT;
	
	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_SELECTClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_SELECTClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDUpdate() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = UPDATE;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);


	COLORREF tmp = m_UPDATEClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_UPDATEClr = tmp;
	ReColoring();
}

void CColorDlg::OnRDValue() 
{
	// TODO: Add your control notification handler code here
	m_eSelected = VALUE;

	CSliderCtrl *pSR = (CSliderCtrl*) GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*) GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*) GetDlgItem(IDC_SLD_B);

	COLORREF tmp = m_VALUEClr;
	pSR->SetPos(GetRValue(tmp));
	pSG->SetPos(GetGValue(tmp));
	pSB->SetPos(GetBValue(tmp));
	m_VALUEClr = tmp;
	ReColoring();
}

void CColorDlg::ColoringSelection(SELECTION sel)
{
	CRichEditCtrl *pLPEdt = (CRichEditCtrl *)this->GetDlgItem(IDC_EDT_LP);
	CRichEditCtrl *pRPEdt = (CRichEditCtrl *)this->GetDlgItem(IDC_EDT_RP);
	CString ltxt, rtxt;
	
	pLPEdt->GetWindowText(ltxt);
	pRPEdt->GetWindowText(rtxt);

	CHARFORMAT2 cf;
    cf.cbSize = sizeof(cf);

	cf.dwMask = CFM_COLOR |CFM_BOLD;
	cf.dwEffects = CFE_BOLD;

	cf.wWeight = 100;
	cf.yHeight = 200;

	int beg, end;

	switch(sel)
	{

	case RANGE:
	    pRPEdt->SetSel(0, rtxt.GetLength());
        cf.crTextColor = m_RANGEClr;
    	pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;
	case BEYOND:
		beg = rtxt.Find("Text");
		end = rtxt.Find("\n");
	    pRPEdt->SetSel(beg, end);
        cf.crTextColor = m_BEYONDClr;
    	pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);

		beg = rtxt.Find("Text", beg+1);
		end = rtxt.Find("\n", beg);
	    pRPEdt->SetSel(beg, end);
    	pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;
	case ERR:
		beg = ltxt.Find("Status");
	    end = ltxt.Find("\n", beg);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_ERRClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);
		break;
	case MCMD:
		beg = ltxt.Find("Mcmd");
	    end = ltxt.Find("+", beg+1);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_MCMDClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);

		beg = rtxt.Find("Mcmd");
	    end = rtxt.Find("\n", beg+1);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_MCMDClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;


	case SELECT:
		beg = ltxt.Find("Select");
	    end = ltxt.Find("\n", beg+1);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_SELECTClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);

		beg = rtxt.Find("Select");
	    end = rtxt.Find("\n", beg+1);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_SELECTClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case UPDATE:
		beg = ltxt.Find("Update");
	    end = ltxt.Find("\n", beg+1);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_UPDATEClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);

		beg = rtxt.Find("Update");
	    end = rtxt.Find("\n", beg+1);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_UPDATEClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case INSERT:
		beg = ltxt.Find("Insert");
	    end = ltxt.Find("\n", beg+1);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_INSERTClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);

		beg = rtxt.Find("Insert");
	    end = rtxt.Find("\n", beg+1);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_INSERTClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case DEL:
		beg = ltxt.Find("Delete");
	    end = ltxt.Find("\n", beg+1);
		pLPEdt->SetSel(beg, end);
		cf.crTextColor = m_DELClr;
        pLPEdt->SetWordCharFormat(cf);
    	pLPEdt->SetSel(0,0);

		beg = rtxt.Find("Delete");
	    end = rtxt.Find("\n", beg+1);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_DELClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case PUBLISH:
		beg = rtxt.Find("Published");
	    end = rtxt.Find("=", beg+9);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_PUBLISHClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case ARGUMENT:
		beg = rtxt.Find("Argument");
	    end = rtxt.Find("=", beg+8);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_ARGUMENTClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;

	case PARAMETER:
		beg = rtxt.Find("Parameter");
	    end = rtxt.Find("=", beg+9);
		pRPEdt->SetSel(beg, end);
		cf.crTextColor = m_PARAMETERClr;
        pRPEdt->SetWordCharFormat(cf);
    	pRPEdt->SetSel(0,0);
		break;
	case VALUE:
		beg = rtxt.Find("'");
	    end = rtxt.Find("'", beg+1);
		while(beg != end && beg >=0 && end >= 0)
		{
		    pRPEdt->SetSel(beg, end);
		    cf.crTextColor = m_VALUEClr;
            pRPEdt->SetWordCharFormat(cf);
    	    pRPEdt->SetSel(0,0);
		    beg = rtxt.Find("'", end+1);
	        end = rtxt.Find("'", beg+1);
		}
		break;


	case LPCOLOR:
        pLPEdt->SetBackgroundColor(false, m_LPCOLORClr);
		break;

	case RPCOLOR:
         pRPEdt->SetBackgroundColor(false, m_RPCOLORClr);
			break;
	}

}

BOOL CColorDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	SetTextFont();

	CSliderCtrl *pSR = (CSliderCtrl*)this->GetDlgItem(IDC_SLD_R);
	CSliderCtrl *pSG = (CSliderCtrl*)this->GetDlgItem(IDC_SLD_G);
	CSliderCtrl *pSB = (CSliderCtrl*)this->GetDlgItem(IDC_SLD_B);

	pSR->SetRange(0,255,true);

	pSG->SetRange(0,255,true);

	pSB->SetRange(0,255,true);

	CButton *pRd = NULL;
	switch(m_eSelected)
	{
	case RANGE:
		pRd = (CButton*)GetDlgItem(IDC_RD_Range);
        pRd->SetCheck(true);

		break;
	case BEYOND:
		pRd = (CButton*)GetDlgItem(IDC_RD_Beyond);
        pRd->SetCheck(true);

		break;
	case ERR:
		pRd = (CButton*)GetDlgItem(IDC_RD_Error);
        pRd->SetCheck(true);

		break;
	case MCMD:
		pRd = (CButton*)GetDlgItem(IDC_RD_Mcmd);
	
        pRd->SetCheck(true);
		
		break;
	case SELECT:
		pRd = (CButton*)GetDlgItem(IDC_RD_Select);
        pRd->SetCheck(true);
	
		break;
	case UPDATE:
		pRd = (CButton*)GetDlgItem(IDC_RD_Update);
        pRd->SetCheck(true);
	
		break;
	case INSERT:
		pRd = (CButton*)GetDlgItem(IDC_RD_Insert);
        pRd->SetCheck(true);
	
		break;
	case DEL:
		pRd = (CButton*)GetDlgItem(IDC_RD_Delete);
        pRd->SetCheck(true);

		break;
	case PARAMETER:
		pRd = (CButton*)GetDlgItem(IDC_RD_Parameter);
        pRd->SetCheck(true);

		break;
	case ARGUMENT:
		pRd = (CButton*)GetDlgItem(IDC_RD_Argument);
        pRd->SetCheck(true);
		break;
	case PUBLISH:
		pRd = (CButton*)GetDlgItem(IDC_RD_Publish);
        pRd->SetCheck(true);
		break;
	case LPCOLOR:
		pRd = (CButton*)GetDlgItem(IDC_RD_LPColor);
        pRd->SetCheck(true);
		break;
	case RPCOLOR:
		pRd = (CButton*)GetDlgItem(IDC_RD_RPColor);
        pRd->SetCheck(true);
		break;
	case VALUE:
		pRd = (CButton*)GetDlgItem(IDC_RD_Value);
        pRd->SetCheck(true);
		break;
	}

	UpdateData(false);
	
	ReColoring();

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColorDlg::OnReleasedcaptureSldB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString s;
	UpdateData(TRUE);
	UpdateColor();
	*pResult = 0;
}

void CColorDlg::OnCustomdrawSldB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CStatic *pSt =(CStatic*)GetDlgItem(IDC_STC_VAL);
	CString s;

	    UpdateData(TRUE);
	    UpdateColor();
	s.Format("RGB(%d,%d,%d)", m_iR, m_iG, m_iB);
	pSt->SetWindowText(s);

	
	*pResult = 0;
}

void CColorDlg::OnOutofmemorySldG(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CColorDlg::OnCustomdrawSldG(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CStatic *pSt =(CStatic*)GetDlgItem(IDC_STC_VAL);

	CString s;
	    UpdateData(TRUE);
	    UpdateColor();
	s.Format("RGB(%d,%d,%d)", m_iR, m_iG, m_iB);
	pSt->SetWindowText(s);

	
	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSldG(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateColor();
	*pResult = 0;	
}

void CColorDlg::OnCustomdrawSldR(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CStatic *pSt =(CStatic*)GetDlgItem(IDC_STC_VAL);

	CString s;

	    UpdateData(TRUE);
	    UpdateColor();

	s.Format("RGB(%d,%d,%d)", m_iR, m_iG, m_iB);
	pSt->SetWindowText(s);

	
	*pResult = 0;
}

void CColorDlg::OnReleasedcaptureSldR(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	UpdateColor();
	*pResult = 0;
}
void CColorDlg::UpdateColor()
{

	COLORREF cv = RGB(m_iR, m_iG, m_iB);

	if(cv == RGB(0,0,0))
	{

		cv =cv;
	}

	switch(m_eSelected)
	{
	case RANGE:
		m_RANGEClr = cv;
		break;

	case MCMD:
		m_MCMDClr = cv;
		break;

	case BEYOND:
		m_BEYONDClr = cv;
		break;

	case ERR:
		m_ERRClr = cv;
		break;

	case SELECT:
		m_SELECTClr = cv;
		break;

	case UPDATE:
		m_UPDATEClr = cv;
		break;

	case INSERT:
		m_INSERTClr = cv;
		break;

	case DEL:
		m_DELClr = cv;
		break;

	case PUBLISH:
		m_PUBLISHClr = cv;
		break;

	case ARGUMENT:
		m_ARGUMENTClr = cv;
		break;

	case PARAMETER:
		m_PARAMETERClr = cv;
		break;

	case VALUE:
		m_VALUEClr = cv;
		break;

	case LPCOLOR:
		m_LPCOLORClr = cv;
		break;

	case RPCOLOR:
		m_RPCOLORClr = cv;
		break;
	}

	this->SetModified();

	ReColoring();
}



void CColorDlg::SetTextFont()
{
    CFont ft;
    //LOGFONT lf;

	CRichEditCtrl *pLPEdt = (CRichEditCtrl *)this->GetDlgItem(IDC_EDT_LP);
	CRichEditCtrl *pRPEdt = (CRichEditCtrl *)this->GetDlgItem(IDC_EDT_RP);

    //lf.lfHeight = 20;                      // request a 12-pixel-height font
    //strcpy(lf.lfFaceName, "Arial");        // request a face name "Arial"
	//lf.lfWeight = 100;//FW_NORMAL;
	//ft.CreateFontIndirect(&lf);
	ft.CreatePointFont(110,"Arial");
	//m_pEdit->GetDC()->SetTextColor(RGB(0,0,255));
	pLPEdt->SetFont(&ft);
	pRPEdt->SetFont(&ft);
}

void CColorDlg::OnBtnReset() 
{
	// TODO: Add your control notification handler code here
	m_RANGEClr = RGB(0,0,255);    
	m_BEYONDClr = RGB(50,50,50);
	m_ERRClr = RGB(255,0,0);
    m_MCMDClr  = RGB(0, 0,0);     
    m_SELECTClr= RGB(0, 155,0);
    m_UPDATEClr= RGB(0, 155,155);   
    m_INSERTClr= RGB(155, 155,0);  
    m_DELClr   = RGB(155, 0,155);  
    m_LPCOLORClr= RGB(150, 150, 150);
    m_RPCOLORClr= RGB(150, 150, 150);
    m_VALUEClr  = RGB(200,00,00);    
    m_PARAMETERClr= RGB(255,255,0);
    m_ARGUMENTClr = RGB(255,0,0);
    m_PUBLISHClr  = RGB(0,255,255); 
	UpdateData(false);

	ReColoring();
}

void CColorDlg::ReColoring()
{
    ColoringSelection(RANGE);
	ColoringSelection(BEYOND);
	ColoringSelection(ERR);
    ColoringSelection(MCMD);
	ColoringSelection(SELECT);
	ColoringSelection(UPDATE);
	ColoringSelection(INSERT);
	ColoringSelection(DEL);
	ColoringSelection(PUBLISH);
	ColoringSelection(PARAMETER);
	ColoringSelection(ARGUMENT);
	ColoringSelection(LPCOLOR);
	ColoringSelection(RPCOLOR);
	ColoringSelection(VALUE);
}

