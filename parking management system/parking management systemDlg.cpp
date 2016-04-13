// parking management systemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "parking management system.h"
#include "parking management systemDlg.h"
#include "debugmodel.h"
#include "DlgProxy.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

extern CCarbarnInfo* garage;

extern CWayFinding* mapinfo;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

extern int link;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlg dialog

IMPLEMENT_DYNAMIC(CParkingmanagementsystemDlg, CDialog);

CParkingmanagementsystemDlg::CParkingmanagementsystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParkingmanagementsystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParkingmanagementsystemDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	
	sumcar=0;
	spendcar=0;
}

CParkingmanagementsystemDlg::~CParkingmanagementsystemDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;

	//m_Comm.SetPortOpen(FALSE);
	m_startend.SetWindowText(_T("连接设备"));
	m_link_info.SetWindowText("未连接");
	link = 0;
	KillTimer(1);
	CloseHandle(thread01);
}

void CParkingmanagementsystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParkingmanagementsystemDlg)
	DDX_Control(pDX, IDC_EDIT3, m_carinfo);
	DDX_Control(pDX, IDC_EDIT4, m_carplate);
	DDX_Control(pDX, IDC_COMBO1, m_list_input);
	DDX_Control(pDX, IDC_EDIT6, m_info);
	DDX_Control(pDX, IDC_BUTTON1, m_startend);
	DDX_Control(pDX, IDC_EDIT5, m_link_info);
	DDX_Control(pDX, IDC_EDIT2, m_freecar);
	DDX_Control(pDX, IDC_EDIT1, m_sumcar);
	DDX_Control(pDX, IDC_LIST2, m_list_error);
	DDX_Control(pDX, IDC_LIST1, m_list_garage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParkingmanagementsystemDlg, CDialog)
	//{{AFX_MSG_MAP(CParkingmanagementsystemDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlg message handlers

BOOL CParkingmanagementsystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列

	//设置列表主题
	m_list_garage.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list_garage.InsertColumn(0,"编号"      ,LVCFMT_CENTER, 70 ,0);
	m_list_garage.InsertColumn(1,"备注"      ,LVCFMT_CENTER, 70 ,0);
	m_list_garage.InsertColumn(2,"状态"      ,LVCFMT_CENTER, 70 ,0);
	m_list_garage.InsertColumn(3,"命令耗时"  ,LVCFMT_CENTER, 70 ,0);
	m_list_garage.InsertColumn(4,"容量"      ,LVCFMT_CENTER, 70 ,0);
	m_list_garage.InsertColumn(5,"已存车辆数",LVCFMT_CENTER, 90 ,0);

	//设置列表主题
	m_list_error.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list_error.InsertColumn(0,"编号"      ,LVCFMT_CENTER, 70,0);
	m_list_error.InsertColumn(1,"备注"      ,LVCFMT_CENTER, 70,0);
	m_list_error.InsertColumn(2,"状态"      ,LVCFMT_CENTER, 70,0);
	m_list_error.InsertColumn(3,"命令耗时"  ,LVCFMT_CENTER, 70 ,0);

	
	/*//设置列表主题
	m_list_reservation.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);
	
	m_list_reservation.InsertColumn(0,"ID"        ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(1,"车牌号"    ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(3,"等待时间"  ,LVCFMT_CENTER, 70 ,0);*/

	m_link_info.SetWindowText("未连接");

	for(int i=0;i<sumgarage;i++)
	{
		sumcar+=garage[i].getsumcar();
		spendcar+=garage[i].getspendcar();
	}

	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,"select type_id from t_map where type=1")==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		while(column=mysql_fetch_row(res))        //获取具体的数据
		{
			m_list_input.AddString(column[0]);
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}
	CEdit* pedit=(CEdit*)m_list_input.GetWindow(GW_CHILD);
	pedit->SetReadOnly(true);

	update_list();

	thread01=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadPoll,NULL,0,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CParkingmanagementsystemDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CParkingmanagementsystemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CParkingmanagementsystemDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CParkingmanagementsystemDlg::OnOK() 
{
	//if (CanExit())
	//	CDialog::OnOK();
}

void CParkingmanagementsystemDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

void CParkingmanagementsystemDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CParkingmanagementsystemDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CParkingmanagementsystemDlg::OnMenuitem32774() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL,"open","http://127.0.0.1/mapedit/",NULL,NULL,SW_SHOWNORMAL);
}

void CParkingmanagementsystemDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL,"open","http://gxy.hunnu.edu.cn/",NULL,NULL,SW_SHOWNORMAL);
}

void CParkingmanagementsystemDlg::update_list()
{
	int index=0;
	int errorindex=0;
	CString tmp;
	m_list_garage.DeleteAllItems();
	m_list_error.DeleteAllItems();

	for(int i=0;i<sumgarage;i++)
	{
		//////////////////////////////////////////////////////////////////////////
		//多定义了一个变量
		index=i;
		//////////////////////////////////////////////////////////////////////////
		tmp.Format("%d",garage[i].getcarbarnid());
		m_list_garage.InsertItem(index,tmp);
		m_list_garage.SetItemText(index,1,garage[i].getname().c_str());
		if(garage[i].getspendtime()>maxindex+1)
		{
			garage[i].setoffline();
			m_list_garage.SetItemText(index,2,"离线");
			m_list_error.InsertItem(errorindex,tmp);
			m_list_error.SetItemText(errorindex,1,garage[i].getname().c_str());
			m_list_error.SetItemText(errorindex,2,"离线");
			errorindex++;
		}
		else
		{
			switch(garage[i].getnowstatus())
			{
			case STATEFREE:
				m_list_garage.SetItemText(index,2,"空闲");
				break;
			case STATESAVE:
				m_list_garage.SetItemText(index,2,"存车");
				break;
			case STATEDELETE:
				m_list_garage.SetItemText(index,2,"取车");
				break;
			case STATESTOP:
				m_list_garage.SetItemText(index,2,"停止");
				break;
			case STATERSET:
				m_list_garage.SetItemText(index,2,"复位");
				break;
			case BUSY:
				m_list_garage.SetItemText(index,2,"运行中");
				break;
			}
		}

		tmp.Format("%d",garage[i].getspendtime());
		m_list_garage.SetItemText(index,3,tmp);

		tmp.Format("%d",garage[i].getsumcar());
		m_list_garage.SetItemText(index,4,tmp);

		tmp.Format("%d",garage[i].getspendcar());
		m_list_garage.SetItemText(index,5,tmp);

		tmp.Format("%d",sumcar);
		m_sumcar.SetWindowText(tmp);

		tmp.Format("%d",sumcar-spendcar);
		m_freecar.SetWindowText(tmp);
	}
}

void CParkingmanagementsystemDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if (!link)
	{
		/*
		if (m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(FALSE);
		m_Comm.SetCommPort(serverinfo.mscomm); //选择com，可根据具体情况更改
		m_Comm.SetInBufferSize(COMLEN);          //设置输入缓冲区的大小，Bytes
		m_Comm.SetOutBufferSize(COMLEN);         //设置输入缓冲区的大小，Bytes//
		CString tmp;
		tmp = serverinfo.mscommini;
		m_Comm.SetSettings(tmp);      //波特率9600，无校验，8个数据位，1个停止位
		m_Comm.SetInputMode(1);                //1：表示以二进制方式检取数据
		m_Comm.SetRThreshold(1);               //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_Comm.SetInputLen(0);                 //设置当前接收区数据长度为0
		if (!m_Comm.GetPortOpen())
		{
			m_Comm.SetPortOpen(TRUE);          //打开串口
		}
		else
		{
			m_Comm.SetPortOpen(FALSE);
		}
		m_Comm.GetInput();                     //先预读缓冲区以清除残留数据
		//m_Comm.SetOutput(COleVariant("ok")); //发送数据
		//////////////////////////////////////////////////////////////////////////*/
		hCom=CreateFile(serverinfo.mscomm,//COM1口
			GENERIC_READ|GENERIC_WRITE, //允许读和写
			0, //独占方式
			NULL,
			OPEN_EXISTING, //打开而不是创建
			FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //重叠方式
			NULL);
		if(hCom==(HANDLE)-1)
		{
			AfxMessageBox("打开COM失败!");
			return ;
		}
		
		SetupComm(hCom,COMLEN,COMLEN); //输入缓冲区和输出缓冲区的大小都是100
		
		COMMTIMEOUTS TimeOuts;
		//设定读超时
		TimeOuts.ReadIntervalTimeout=MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier=0;
		TimeOuts.ReadTotalTimeoutConstant=0;
		//在读一次输入缓冲区的内容后读操作就立即返回，
		//而不管是否读入了要求的字符。
		
		
		//设定写超时
		TimeOuts.WriteTotalTimeoutMultiplier=100;
		TimeOuts.WriteTotalTimeoutConstant=500;
		SetCommTimeouts(hCom,&TimeOuts); //设置超时
		
		DCB dcb;
		GetCommState(hCom,&dcb);
		dcb.BaudRate=serverinfo.BaudRate; //波特率为9600
		dcb.ByteSize=serverinfo.ByteSize; //每个字节有8位
		dcb.Parity  =serverinfo.Parity;   //奇偶校验位
		dcb.StopBits=serverinfo.StopBits; //停止位
		SetCommState(hCom,&dcb);
		
		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

		m_startend.SetWindowText(_T("断开设备"));
		m_link_info.SetWindowText("已连接");
		link = 1;

		SetTimer(1,1000,NULL);
	}
	else if (link)
	{
		//m_Comm.SetPortOpen(FALSE);
		CloseHandle(hCom);
		m_startend.SetWindowText(_T("连接设备"));
		m_link_info.SetWindowText("未连接");
		link = 0;
		KillTimer(1);
	}
}

void CParkingmanagementsystemDlg::OnButton2() 
{
	// TODO: 存车
	MYSQL_RES *res;                    //查询结果集
//	MYSQL_ROW column;                  //数据行的列
	CString strplate;
	CString strinput;
	CString strtmp;

	m_carplate.GetWindowText(strplate);
	m_list_input.GetWindowText(strinput);
	
	if(strplate=="")return ;

	if(sumcar==spendcar)
	{
		MessageBox("车位已满");
		return ;
	}

	strtmp.Format("select * from t_reservation where plate='%s'",strplate);
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		
		if(mysql_num_rows(res))
		{
			strtmp.Format("delete from t_reservation where plate='%s'",strplate);
			mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0));
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}

	strtmp.Format("select * from t_carinfo where plate='%s'",strplate);
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		
		if(mysql_num_rows(res))
		{
			MessageBox("车牌重复");
			return ;
		}
	}

	int garageid=mapinfo->nearestcarport(atoi(strinput.GetBuffer(0)));
	if(garageid==-1)
	{
		MessageBox("未找到空闲模块,请稍后再试!");
		return ;
	}
	
	strtmp.Format("最近的车库是第%d号车库",garageid);
	//MessageBox(strtmp);
	m_carinfo.SetWindowText(strtmp);
	//sumcar
	spendcar++;

	strtmp.Format("insert into t_carinfo(plate,start) values('%s',now())",strplate);
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0))!=NULL)
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}

	int index=idtoindex[garageid];
	
	garage[index].setnowstatus(BUSY);

	char sendstr[]="123";
	sendstr[0]=SAVECAR;
	sendstr[1]=garage[index].getrows(garage[index].findemptycarid());
	sendstr[2]=garage[index].getcols(garage[index].findemptycarid());
	garage[index].setcommand(sendstr);

	strtmp.Format("insert into t_carlocation(plate,carbarnid,num) values('%s',%d,%d)",
		strplate,garageid,garage[index].findemptycarid());
	garage[index].setsqlcommand(strtmp.GetBuffer(0));

	garage[index].savecar();
}

void CParkingmanagementsystemDlg::OnButton3() 
{
	// TODO: 取车
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString strplate;
	CString strtmp;

	m_carplate.GetWindowText( strplate );

	if(strplate == "") return ;

	strtmp.Format( "select carbarnid,num from t_carlocation where plate='%s'", strplate );

	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0))!=NULL)
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}
	res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
	
	if(mysql_num_rows(res)==0)
	{
		MessageBox("未找到车辆");
		return ;
	}

	column=mysql_fetch_row(res);

	int garageid = atoi(column[0]);
	int num      = atoi(column[1]);

	int nearoutput = mapinfo->nearestexit(garageid);
	if(nearoutput==-1)
	{
		MessageBox("未找到出口,请检查地图设置!");
		return ;
	}

	strtmp.Format("最近的出口是第%d号出口",nearoutput);
	//MessageBox(strtmp);
	m_carinfo.SetWindowText(strtmp);
	spendcar--;

	int index=idtoindex[garageid];
	
	garage[index].setnowstatus(BUSY);

	char sendstr[]="123";
	sendstr[0]=DELETECAR;
	sendstr[1]=garage[index].getrows(num);
	sendstr[2]=garage[index].getcols(num);
	garage[index].setcommand(sendstr);

	//delete from t_carinfo where plate='%s';
	strtmp.Format("delete from t_carinfo where plate='%s'",strplate);
	if(mysql_query(&serverinfo.mysql,strtmp.GetBuffer(0))!=NULL)
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}

	strtmp.Format("delete from t_carlocation where plate='%s'",strplate);
	garage[index].setsqlcommand(strtmp.GetBuffer(0));

	garage[index].deletecar(num);
}

void CParkingmanagementsystemDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		if(link)
		{
			for(int i=0;i<sumgarage;i++)
				garage[i].accspendtime();
			update_list();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CParkingmanagementsystemDlg::setinfo(char *str)
{
	m_info.SetWindowText(str);
}

BEGIN_EVENTSINK_MAP(CParkingmanagementsystemDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CParkingmanagementsystemDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CParkingmanagementsystemDlg::OnMenuitem32775() 
{
	// TODO: Add your command handler code here
	if(!link)
	{
		return ;
	}

	int tmp=link;
	link=0;
	
	debugmodel dlg;
	dlg.DoModal();

	link=tmp;
}
