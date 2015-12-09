; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CParkingmanagementDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "parking management.h"

ClassCount=4
Class1=CParkingmanagementApp
Class2=CParkingmanagementDlg

ResourceCount=5
Resource2=IDD_ABOUT
Resource3=IDD_SHOWMAPINFO
Resource1=IDR_MAINFRAME
Class3=showmapinfo
Resource4=IDD_PARKINGMANAGEMENT_DIALOG
Class4=ABOUTSOFT
Resource5=IDR_MENU1

[CLS:CParkingmanagementApp]
Type=0
HeaderFile=parking management.h
ImplementationFile=parking management.cpp
Filter=N

[CLS:CParkingmanagementDlg]
Type=0
HeaderFile=parking managementDlg.h
ImplementationFile=parking managementDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CParkingmanagementDlg



[DLG:IDD_PARKINGMANAGEMENT_DIALOG]
Type=1
Class=CParkingmanagementDlg
ControlCount=19
Control1=IDC_LIST1,SysListView32,1350631709
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_BUTTON2,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_BUTTON3,button,1342242816
Control13=IDC_BUTTON4,button,1342242816
Control14=IDC_EDIT4,edit,1350633600
Control15=IDC_STATIC,static,1342308352
Control16=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control17=IDC_EDIT5,edit,1352728772
Control18=IDC_EDIT6,edit,1350631552
Control19=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=CParkingmanagementDlg
Command1=ID_MENUITEM32771
Command2=ID_MENUITEM32772
Command3=ID_MENUITEM32773
CommandCount=3

[DLG:IDD_SHOWMAPINFO]
Type=1
Class=showmapinfo
ControlCount=2
Control1=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816
Control2=IDC_BUTTON1,button,1342242816

[CLS:showmapinfo]
Type=0
HeaderFile=showmapinfo.h
ImplementationFile=showmapinfo.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EXPLORER1
VirtualFilter=dWC

[DLG:IDD_ABOUT]
Type=1
Class=ABOUTSOFT
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177294

[CLS:ABOUTSOFT]
Type=0
HeaderFile=ABOUTSOFT.h
ImplementationFile=ABOUTSOFT.cpp
BaseClass=CDialog
Filter=D
LastObject=ABOUTSOFT
VirtualFilter=dWC

