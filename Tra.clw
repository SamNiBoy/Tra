; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTraDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tra.h"
LastPage=0

ClassCount=18
Class1=CBtnSchLft
Class2=CColorDlg
Class3=CEditFinder
Class4=CFindDlg
Class5=CFindLstDlg
Class6=CGphDlg
Class7=CInProgress
Class8=CLeftView
Class9=CMainFrame
Class10=CMyToolBar
Class11=COptDlg
Class12=COptMTF
Class13=CTraApp
Class14=CAboutDlg
Class15=CTraDoc
Class16=CTraView

ResourceCount=23
Resource1=IDD_FILE_EXPORT
Resource2=IDD_DLG_SPLT_FILE
Resource3=IDR_TOOLBAR
Resource4=IDD_FIND_LIST
Resource5=IDR_MAINFRAME
Resource6=IDD_OPT_COLOR
Resource7=IDD_DLG_GRAPH
Resource8=IDD_ABOUTBOX
Resource9=IDD_OPT_COLOR (English (U.S.))
Resource10=IDD_IN_PROGRESS
Resource11=IDD_OPT_MOCA (English (U.S.))
Resource12=IDR_TOOLBAR (English (U.S.))
Resource13=IDD_ABOUTBOX (English (U.S.))
Resource14=IDD_DLG_GRAPH (English (U.S.))
Resource15=IDD_DLG_FIND (English (U.S.))
Resource16=IDR_MAINFRAME (English (U.S.))
Resource17=IDD_IN_PROGRESS (English (U.S.))
Resource18=IDD_FIND_LIST (English (U.S.))
Resource19=IDD_OPT_MTF (English (U.S.))
Resource20=IDD_OPT_MTF
Class17=CSpltFileDlg
Resource21=IDD_OPT_MOCA
Resource22=IDD_DLG_FIND
Class18=CDlgTransf
Resource23=IDD_DLG_TRANSF

[CLS:CBtnSchLft]
Type=0
BaseClass=CButton
HeaderFile=BtnSchLft.h
ImplementationFile=BtnSchLft.cpp

[CLS:CColorDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=ColorDlg.h
ImplementationFile=ColorDlg.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDM_EXP_MCMD

[CLS:CEditFinder]
Type=0
BaseClass=CEdit
HeaderFile=EditFinder.h
ImplementationFile=EditFinder.cpp

[CLS:CFindDlg]
Type=0
BaseClass=CDialog
HeaderFile=FindDlg.h
ImplementationFile=FindDlg.cpp

[CLS:CFindLstDlg]
Type=0
BaseClass=CDialog
HeaderFile=FindLstDlg.h
ImplementationFile=FindLstDlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CGphDlg]
Type=0
BaseClass=CDialog
HeaderFile=GphDlg.h
ImplementationFile=GphDlg.cpp

[CLS:CInProgress]
Type=0
BaseClass=CDialog
HeaderFile=InProgress.h
ImplementationFile=InProgress.cpp

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CLeftView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=ID_FILE_OPEN
Filter=T
VirtualFilter=fWC

[CLS:CMyToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=MyToolBar.h
ImplementationFile=MyToolBar.cpp

[CLS:COptDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=OptDlg.h
ImplementationFile=OptDlg.cpp
LastObject=COptDlg
Filter=D
VirtualFilter=idWC

[CLS:COptMTF]
Type=0
BaseClass=CPropertyPage
HeaderFile=OptMTF.h
ImplementationFile=OptMTF.cpp

[CLS:CTraApp]
Type=0
BaseClass=CWinApp
HeaderFile=Tra.h
ImplementationFile=Tra.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Tra.cpp
ImplementationFile=Tra.cpp

[CLS:CTraDoc]
Type=0
BaseClass=CDocument
HeaderFile=TraDoc.h
ImplementationFile=TraDoc.cpp
LastObject=CTraDoc
Filter=N
VirtualFilter=DC

[CLS:CTraView]
Type=0
BaseClass=CRichEditView
HeaderFile=TraView.h
ImplementationFile=TraView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CTraView

[DLG:IDD_OPT_COLOR]
Type=1
Class=CColorDlg
ControlCount=27
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RD_Value,button,1342177289
Control3=IDC_RD_Range,button,1342177289
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RD_Mcmd,button,1342177289
Control6=IDC_RD_Publish,button,1342177289
Control7=IDC_RD_Parameter,button,1342177289
Control8=IDC_RD_Argument,button,1342177289
Control9=IDC_RD_RPColor,button,1342177289
Control10=IDC_RD_Select,button,1342177289
Control11=IDC_RD_Update,button,1342177289
Control12=IDC_RD_Insert,button,1342177289
Control13=IDC_RD_Delete,button,1342177289
Control14=IDC_RD_LPColor,button,1342177289
Control15=IDC_STATIC,button,1342177287
Control16=IDC_SLD_R,msctls_trackbar32,1342242840
Control17=IDC_STATIC,static,1342308352
Control18=IDC_SLD_G,msctls_trackbar32,1342242840
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SLD_B,msctls_trackbar32,1342242840
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDT_LP,RICHEDIT,1350633476
Control23=IDC_EDT_RP,RICHEDIT,1350633476
Control24=IDC_STC_VAL,static,1342308352
Control25=IDC_BTN_RESET,button,1342242816
Control26=IDC_RD_Beyond,button,1342177289
Control27=IDC_RD_Error,button,1342177289

[DLG:IDD_DLG_FIND]
Type=1
Class=CFindDlg
ControlCount=4
Control1=IDC_EDT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_FIND_LIST]
Type=1
Class=CFindLstDlg
ControlCount=3
Control1=IDOK,button,1342245632
Control2=IDC_FIND_LST,listbox,1353777409
Control3=IDC_BTN_CPALL,button,1342242816

[DLG:IDD_DLG_GRAPH]
Type=1
Class=CGphDlg
ControlCount=0

[DLG:IDD_IN_PROGRESS]
Type=1
Class=CInProgress
ControlCount=1
Control1=IDC_IN_PRG,msctls_progress32,1342177281

[DLG:IDD_OPT_MTF]
Type=1
Class=COptMTF
ControlCount=5
Control1=IDC_LST_MARK,listbox,1352728833
Control2=IDC_EDT_BEGIN,edit,1350631552
Control3=IDC_OPT_ADD,button,1342242816
Control4=IDC_OPT_REMOVE,button,1342242816
Control5=65535,button,1342177287

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_EDT_ABOUT,edit,1352730764
Control4=IDC_STATIC,static,1342177793

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=IDM_REFRESH_VIEW
Command3=IDM_PERFORM_ALL
Command4=IDM_PERFORM_SEL
Command5=IDM_SHOW_PARMCMD
Command6=IDM_SHOW_SELECT
Command7=IDM_SHOW_UPDATE
Command8=IDM_SHOW_INSERT
Command9=IDM_SHOW_DELETE
Command10=IDM_SHOW_MCMD
Command11=IDM_SHOW_ALL
Command12=IDM_SHOW_BKMK
CommandCount=12

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=IDE_TOOLBAR_FIND
CommandCount=1

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_EXPORT
Command3=ID_FILE_SPLIT
Command4=ID_FILE_TRNSF
Command5=ID_APP_EXIT
Command6=IDM_PERFORM_ALL
Command7=IDM_PERFORM_SEL
Command8=IDM_SHOW_PARMCMD
Command9=IDM_SHOW_GRPH
Command10=IDM_TOG_BKMK
Command11=IDM_TOGO_BKMK
Command12=IDM_CLR_BKMK
Command13=IDM_TOG_MCMD
Command14=ID_OPT_SETTING
Command15=IDM_VIEW_TOOLBAR
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_HELP
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_TOG_BKMK
Command2=IDM_CLR_BKMK
Command3=ID_FILE_EXPORT
Command4=IDM_FIND_MCMD
Command5=IDM_TOGO_BKMK
Command6=ID_FILE_OPEN
Command7=ID_FILE_SPLIT
Command8=IDM_REFRESH_VIEW
Command9=IDM_SHOW_BKMK
Command10=IDM_FIND_NXTMCMD
Command11=ID_HIDE_APP
Command12=ID_SHOW_APP
Command13=IDM_TOG_MCMD
CommandCount=13

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=IDM_REFRESH_VIEW
Command3=IDM_PERFORM_ALL
Command4=IDM_PERFORM_SEL
Command5=IDM_SHOW_PARMCMD
Command6=IDM_SHOW_SELECT
Command7=IDM_SHOW_UPDATE
Command8=IDM_SHOW_INSERT
Command9=IDM_SHOW_DELETE
Command10=IDM_SHOW_MCMD
Command11=IDM_SHOW_ALL
Command12=IDM_SHOW_BKMK
CommandCount=12

[TB:IDR_TOOLBAR (English (U.S.))]
Type=1
Class=?
Command1=IDE_TOOLBAR_FIND
CommandCount=1

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_APP_EXIT
Command3=IDM_PERFORM_ALL
Command4=IDM_PERFORM_SEL
Command5=IDM_SHOW_PARMCMD
Command6=IDM_SHOW_GRPH
Command7=IDM_TOG_BKMK
Command8=IDM_TOGO_BKMK
Command9=IDM_CLR_BKMK
Command10=IDM_TOG_MCMD
Command11=ID_OPT_SETTING
Command12=IDM_VIEW_TOOLBAR
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_HELP
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=IDM_TOG_BKMK
Command2=IDM_CLR_BKMK
Command3=IDM_FIND_MCMD
Command4=IDM_TOGO_BKMK
Command5=ID_FILE_OPEN
Command6=IDM_REFRESH_VIEW
Command7=IDM_SHOW_BKMK
Command8=IDM_FIND_NXTMCMD
Command9=ID_HIDE_APP
Command10=ID_SHOW_APP
Command11=IDM_TOG_MCMD
CommandCount=11

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_EDT_ABOUT,edit,1352730764
Control4=IDC_STATIC,static,1342177793

[DLG:IDD_OPT_MOCA (English (U.S.))]
Type=1
Class=COptDlg
ControlCount=25
Control1=IDC_CHK_SELECT,button,1342242819
Control2=IDC_CHK_Update,button,1342242819
Control3=IDC_CHK_DELETE,button,1342242819
Control4=IDC_CHK_INSERT,button,1342242819
Control5=IDC_CHK_MCMD,button,1342242819
Control6=IDC_RAD_SHOWALL,button,1342177289
Control7=IDC_RAD_SHOWSINGLE,button,1342177289
Control8=IDC_EDT_MAXLINENUM,edit,1350631552
Control9=IDC_EDT_THRESHVAL,edit,1350631552
Control10=IDC_LST_BEGIN,listbox,1352728833
Control11=IDC_LST_END,listbox,1352728833
Control12=IDC_EDT_BEGIN,edit,1350631552
Control13=IDC_EDT_END,edit,1350631552
Control14=IDC_OPT_ADD,button,1342242816
Control15=IDC_OPT_REMOVE,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,button,1342177287
Control25=IDC_CHK_SUPMOD,button,1342242819

[DLG:IDD_DLG_FIND (English (U.S.))]
Type=1
Class=CFindDlg
ControlCount=4
Control1=IDC_EDT_TEXT,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_FIND_LIST (English (U.S.))]
Type=1
Class=CFindLstDlg
ControlCount=2
Control1=IDOK,button,1342245632
Control2=IDC_FIND_LST,listbox,1353777409

[DLG:IDD_IN_PROGRESS (English (U.S.))]
Type=1
Class=CInProgress
ControlCount=1
Control1=IDC_IN_PRG,msctls_progress32,1342177281

[DLG:IDD_DLG_GRAPH (English (U.S.))]
Type=1
Class=CGphDlg
ControlCount=0

[DLG:IDD_OPT_MTF (English (U.S.))]
Type=1
Class=COptMTF
ControlCount=5
Control1=IDC_LST_MARK,listbox,1352728833
Control2=IDC_EDT_BEGIN,edit,1350631552
Control3=IDC_OPT_ADD,button,1342242816
Control4=IDC_OPT_REMOVE,button,1342242816
Control5=65535,button,1342177287

[DLG:IDD_OPT_COLOR (English (U.S.))]
Type=1
Class=CColorDlg
ControlCount=27
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RD_Value,button,1342177289
Control3=IDC_RD_Range,button,1342177289
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RD_Mcmd,button,1342177289
Control6=IDC_RD_Publish,button,1342177289
Control7=IDC_RD_Parameter,button,1342177289
Control8=IDC_RD_Argument,button,1342177289
Control9=IDC_RD_RPColor,button,1342177289
Control10=IDC_RD_Select,button,1342177289
Control11=IDC_RD_Update,button,1342177289
Control12=IDC_RD_Insert,button,1342177289
Control13=IDC_RD_Delete,button,1342177289
Control14=IDC_RD_LPColor,button,1342177289
Control15=IDC_STATIC,button,1342177287
Control16=IDC_SLD_R,msctls_trackbar32,1342242840
Control17=IDC_STATIC,static,1342308352
Control18=IDC_SLD_G,msctls_trackbar32,1342242840
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SLD_B,msctls_trackbar32,1342242840
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDT_LP,RICHEDIT,1350633476
Control23=IDC_EDT_RP,RICHEDIT,1350633476
Control24=IDC_STC_VAL,static,1342308352
Control25=IDC_BTN_RESET,button,1342242816
Control26=IDC_RD_Beyond,button,1342177289
Control27=IDC_RD_Error,button,1342177289

[DLG:IDD_OPT_MOCA]
Type=1
Class=COptDlg
ControlCount=26
Control1=IDC_CHK_SELECT,button,1342242819
Control2=IDC_CHK_Update,button,1342242819
Control3=IDC_CHK_DELETE,button,1342242819
Control4=IDC_CHK_INSERT,button,1342242819
Control5=IDC_CHK_MCMD,button,1342242819
Control6=IDC_RAD_SHOWALL,button,1342177289
Control7=IDC_RAD_SHOWSINGLE,button,1342177289
Control8=IDC_EDT_MAXLINENUM,edit,1350631552
Control9=IDC_EDT_THRESHVAL,edit,1350631552
Control10=IDC_LST_BEGIN,listbox,1352728833
Control11=IDC_LST_END,listbox,1352728833
Control12=IDC_EDT_BEGIN,edit,1350631552
Control13=IDC_EDT_END,edit,1350631552
Control14=IDC_OPT_ADD,button,1342242816
Control15=IDC_OPT_REMOVE,button,1342242816
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,button,1342177287
Control25=IDC_CHK_SUPMOD,button,1342242819
Control26=IDC_CHK_LOD3000,button,1342242819

[DLG:IDD_DLG_SPLT_FILE]
Type=1
Class=CSpltFileDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=ID_SPLT_FILE_START,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDT_SPLIT_FILE_NAME,edit,1350631552
Control5=IDC_SPLIT_OPEN_FILE,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDT_SPLIT_SIZE,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CHK_THD_SPLT,button,1342242819

[CLS:CSpltFileDlg]
Type=0
HeaderFile=SpltFileDlg.h
ImplementationFile=SpltFileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSpltFileDlg
VirtualFilter=dWC

[DLG:IDD_FILE_EXPORT]
Type=1
Class=?
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EXPORT_FILE_NAME,edit,1350631552
Control5=IDC_EXPORT_BTN_OPEN,button,1342242816
Control6=IDC_EXPORT_CHK_NDOLY,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EXPORT_EDT_FRM,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EXPORT_EDT_TO,edit,1350631552
Control11=IDC_EXPORT_CHK_SELOLY,button,1342242819

[DLG:IDD_DLG_TRANSF]
Type=1
Class=CDlgTransf
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IPADDR,SysIPAddress32,1342242816

[CLS:CDlgTransf]
Type=0
HeaderFile=DlgTransf.h
ImplementationFile=DlgTransf.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgTransf

