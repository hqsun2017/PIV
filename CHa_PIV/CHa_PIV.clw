; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPivView
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CHa_PIV.h"
LastPage=0

ClassCount=6
Class1=CHa_PIVApp
Class2=CPivDoc
Class3=CPivView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_GRIDSEL
Resource3=IDD_AMPLIFIER (English (U.S.))
Class6=CGridSel
Resource4=IDR_MAINFRAME (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_GRIDSEL (English (U.S.))

[CLS:CHa_PIVApp]
Type=0
HeaderFile=CHa_PIV.h
ImplementationFile=CHa_PIV.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CHa_PIVApp

[CLS:CPivDoc]
Type=0
HeaderFile=PivDoc.h
ImplementationFile=PivDoc.cpp
Filter=N

[CLS:CPivView]
Type=0
HeaderFile=PivView.h
ImplementationFile=PivView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_APP_CC_FFT

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=CHa_PIV.cpp
ImplementationFile=CHa_PIV.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_ABOUT
CommandCount=1

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_BMP_READ1
Command5=ID_BMP_READ2
Command6=ID_BMP_SHOW1
Command7=ID_BMP_SHOW2
Command8=ID_APP_GRIDSEL
Command9=ID_APP_CC_FFT
Command10=ID_APP_PC_FFT
Command11=ID_APP_CC_FHT
Command12=ID_APP_PAUSE
Command13=ID_APP_STOP
Command14=ID_VEC_READ
Command15=ID_VEC_SAVE
Command16=ID_VEC_SHOW
Command17=ID_APP_ABOUT
CommandCount=17

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GRIDSEL]
Type=1
Class=CGridSel
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control5=IDC_STATIC
Control6=IDC_STATIC
Control7=IDC_ED_SIZEX
Control8=IDC_ED_SIZEY
Control9=IDC_STATIC
Control4=IDC_STATIC

[CLS:CGridSel]
Type=0
HeaderFile=MyDlg.h
ImplementationFile=MyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_WINDOWED
VirtualFilter=dWC

[DLG:IDD_GRIDSEL (English (U.K.))]
Type=1
Class=CGridSel
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control5=IDC_STATIC
Control6=IDC_STATIC
Control7=IDC_ED_SIZEX
Control8=IDC_ED_SIZEY
Control4=IDC_STATIC

[DLG:IDD_AMPLIFIER (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ED_AMPLIFIER,edit,1350631552

[DLG:IDD_GRIDSEL (English (U.S.))]
Type=1
Class=CGridSel
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_ED_STEPX,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ED_SIZEX,edit,1350631552
Control8=IDC_ED_SIZEY,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_ED_STEPY,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_ED_AMPLIFIER,edit,1350631552
Control13=IDC_CHECK_WINDOWED,button,1342242819

