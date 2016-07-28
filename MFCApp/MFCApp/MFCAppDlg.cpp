
// MFCAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "debugmodel.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include "IOCPserver.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

extern DCB dcb;

extern CCarbarnInfo* garage;

extern CWayFinding* mapinfo;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

// CMFCAppDlg 对话框

IMPLEMENT_DYNAMIC(CMFCAppDlg, CDialogEx);

CMFCAppDlg::CMFCAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	serverinfo.sumcar = 0;
	serverinfo.spendcar = 0;
	serverinfo.activeThreadtime = 0;

	serverinfo.runstate = 0;
	serverinfo.lockflage = 0;
}

CMFCAppDlg::~CMFCAppDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_garage);
	DDX_Control(pDX, IDC_LIST2, m_list_error);
	DDX_Control(pDX, IDC_EDIT1, m_sumcar);
	DDX_Control(pDX, IDC_EDIT2, m_freecar);
	DDX_Control(pDX, IDC_EDIT3, m_reservationcar);
	DDX_Control(pDX, IDC_EDIT4, m_Threadinfo);
	DDX_Control(pDX, IDC_LIST3, m_list_ioput);
}

BEGIN_MESSAGE_MAP(CMFCAppDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCAppDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_COMMAND(ID_32774, &CMFCAppDlg::On32774)
	ON_COMMAND(ID_32773, &CMFCAppDlg::On32773)
	ON_COMMAND(ID_32771, &CMFCAppDlg::On32771)
	ON_COMMAND(ID_32772, &CMFCAppDlg::On32772)
	ON_COMMAND(ID_32775, &CMFCAppDlg::On32775)
END_MESSAGE_MAP()


// CMFCAppDlg 消息处理程序

BOOL CMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码

//	MYSQL_RES *res;                    //查询结果集
//	MYSQL_ROW column;                  //数据行的列

	//初始化曲线控件
	CRect rt;
	GetDlgItem(IDC_CUSTOM1)->GetWindowRect(rt);
	ScreenToClient(rt);
	m_Osc.Create(WS_VISIBLE | WS_CHILD, rt, this);
	m_Osc.SetRange(0.0, serverinfo.Threadsum*100, 1);
	m_Osc.SetYUnits(_T(""));
	m_Osc.SetXUnits(_T("服务使用率"));
	m_Osc.SetBackgroundColor(RGB(0, 0, 64));
	m_Osc.SetGridColor(RGB(192, 192, 255));
	m_Osc.SetPlotColor(RGB(255, 255, 0));
	m_Osc.AppendPoint(0.0);

	//设置列表主题
	m_list_garage.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
		| LVS_EX_FULLROWSELECT		// 允许正航选中
		| LVS_EX_GRIDLINES			// 画出网格线
		);

	m_list_garage.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40, 0);
	m_list_garage.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(3, _T("命令耗时"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(4, _T("容量"), LVCFMT_CENTER, 50, 0);
	m_list_garage.InsertColumn(5, _T("已存"), LVCFMT_CENTER, 50, 0);

	//设置列表主题
	m_list_error.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
		| LVS_EX_FULLROWSELECT		// 允许正航选中
		| LVS_EX_GRIDLINES			// 画出网格线
		);

	m_list_error.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40, 0);
	m_list_error.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 70, 0);
	m_list_error.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 70, 0);

	//设置列表主题
	m_list_ioput.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
		| LVS_EX_FULLROWSELECT		// 允许正航选中
		| LVS_EX_GRIDLINES			// 画出网格线
		);

	m_list_ioput.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40, 0);
	//m_list_ioput.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 87, 0);
	m_list_ioput.InsertColumn(1, _T("类型"), LVCFMT_CENTER, 70, 0);
	m_list_ioput.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 70, 0);//*/

	/*//设置列表主题
	m_list_reservation.SetExtendedStyle(
	LVS_EX_FLATSB				// 扁平风格滚动
	| LVS_EX_FULLROWSELECT		// 允许正航选中
	| LVS_EX_GRIDLINES			// 画出网格线
	);

	m_list_reservation.InsertColumn(0,"ID"        ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(1,"车牌号"    ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(3,"等待时间"  ,LVCFMT_CENTER, 70 ,0);*/

	//	m_link_info.SetWindowText("未连接");

	/*	for(int i=0;i<sumgarage;i++)
	{
	sumcar+=garage[i].getsumcar();
	spendcar+=garage[i].getspendcar();
	}*/

	/*mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select type_id from t_map where type=1") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		while (column = mysql_fetch_row(res))        //获取具体的数据
		{
			CString tmp(column[0]);
			m_list_input.AddString(tmp);
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}
	CEdit* pedit = (CEdit*)m_list_input.GetWindow(GW_CHILD);
	pedit->SetReadOnly(true);*/

	//update_list();
	init_list();

	thread01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPoll, NULL, 0, NULL);
	thread02 =CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)iocpstartserver, NULL, 0, NULL);

/*	//////////////////////////////////////////////////////////////////////////
	CString tmp(serverinfo.mscomm);
	hCom = CreateFile(tmp,//COM1口
		GENERIC_READ | GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //重叠方式
		NULL);
	if (hCom == (HANDLE)-1)
	{
		AfxMessageBox(_T("打开COM失败!"));
		exit(1);
		return FALSE;
	}

	SetupComm(hCom, COMLEN, COMLEN); //输入缓冲区和输出缓冲区的大小都是100

	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//在读一次输入缓冲区的内容后读操作就立即返回，
	//而不管是否读入了要求的字符。


	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(hCom, &TimeOuts); //设置超时

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = serverinfo.BaudRate; //波特率为9600
	dcb.ByteSize = serverinfo.ByteSize; //每个字节有8位
	dcb.Parity = serverinfo.Parity;   //奇偶校验位
	dcb.StopBits = serverinfo.StopBits; //停止位
	SetCommState(hCom, &dcb);

	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
*/	//////////////////////////////////////////////////////////////////////////

//	m_startend.SetWindowText(_T("暂停"));
	//	m_link_info.SetWindowText("已连接");
//	link = 1;
	serverinfo.runstate = 1;

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_GREEN);
	//m_stateico.SetIcon(hIcon);

	SetTimer(1, 1000, NULL);
	SetTimer(2, 1000, NULL);
	SetTimer(3, 60*1000 , NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMFCAppDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFCAppDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFCAppDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFCAppDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMFCAppDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMFCAppDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

/*void CMFCAppDlg::setinfo(char* str)
{
	CString strtmp;
//	m_info.GetWindowText(strtmp);
	strtmp = str;
	m_info.SetWindowText(strtmp);
}*/


void CMFCAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MYSQL_RES *res;                    //查询结果集
//	MYSQL_ROW column;                  //数据行的列

	switch (nIDEvent)
	{
	case 1:
		if (serverinfo.runstate)
		{
			for (int i = 0; i<sumgarage; i++)
				garage[i].accspendtime();
			update_list();
		}
		break;
	case 2:
		if (serverinfo.runstate)
		{
			m_Osc.AppendPoint(serverinfo.activeThreadtime/10.0);
			//printf("[%ld]", serverinfo.activeThread);
			serverinfo.activeThreadtime = 0;
		}
		break;
	case 3:
		mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

		if (mysql_query(&serverinfo.mysql, "delete from t_reservation where now()>endtime") != NULL)
		{
			AfxMessageBox(_T("time:32数据库连接失败"));
			exit(1);
		}
		//else AfxMessageBox(_T("delete successful"));

		if (mysql_query(&serverinfo.mysql, "select plate from t_reservation") == NULL)
		{
			res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
			serverinfo.reservation = (int)mysql_num_rows(res);
			//printf("[reservation=%d]", serverinfo.reservation);
		}
		else
		{
			AfxMessageBox(_T("time:31数据库连接失败"));
			exit(1);
		}

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCAppDlg::init_list()
{
	CString tmp;

	m_list_garage.DeleteAllItems();
	m_list_error.DeleteAllItems();

	for (int index = 0; index<sumgarage; index++)
	{
		tmp.Format(_T("%d"), garage[index].getcarbarnid());
		m_list_garage.InsertItem(index, tmp);
		tmp = garage[index].getname().c_str();
		m_list_garage.SetItemText(index, 1, tmp);
		m_list_garage.SetItemText(index, 2, _T("未知"));

		m_list_garage.SetItemText(index, 3, _T("00:00:00"));

		tmp.Format(_T("%d"), garage[index].getsumcar());
		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[index].getspendcar());
		m_list_garage.SetItemText(index, 5, tmp);

		serverinfo.sumcar += garage[index].getsumcar();
		serverinfo.spendcar += garage[index].getspendcar();
	}

	tmp.Format(_T("%d"), serverinfo.sumcar);
	m_sumcar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation);
	m_freecar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.reservation);
	m_reservationcar.SetWindowText(tmp);

	tmp.Format(_T("%d/%d"), serverinfo.Threadwork,serverinfo.Threadsum);
	m_Threadinfo.SetWindowText(tmp);
}

void CMFCAppDlg::update_list()
{
	int index = 0;
	int errorindex = 0;
	int overtime = 0;
	CString tmp;

	//m_list_garage.DeleteAllItems();
	m_list_error.DeleteAllItems();

//	serverinfo.sumcar = 0;
//	serverinfo.spendcar = 0;

	//////////////////////////////////////////////////////////////////////////
	//根据车库模块数量以及查询间隔确定超时时间
	overtime = ((maxindex + 1)*serverinfo.intervaltime) / 1000;
	if (overtime<1)overtime = 1;
	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i<sumgarage; i++)
	{
		//////////////////////////////////////////////////////////////////////////
		//多定义了一个变量
		index = i;
		//////////////////////////////////////////////////////////////////////////
		tmp.Format(_T("%d"), garage[i].getcarbarnid());
		//m_list_garage.InsertItem(index, tmp);
		m_list_garage.SetItemText(index, 0, tmp);
		tmp = garage[i].getname().c_str();
		m_list_garage.SetItemText(index, 1, tmp);
		/*if (garage[i].getspendtime()>overtime)
		{
			/*if (garage[i].getnowstatus() == ONLINE)
			{
				serverinfo.sumcar-= garage[i].getsumcar();
				serverinfo.spendcar-= garage[i].getspendcar();
				//garage[i].setnowstatus(OFFLINE);
			}//

			//garage[i].setoffline();
			//garage[i].setnowstatus(OFFLINE);
			tmp.Format(_T("%d"), garage[i].getcarbarnid());
			m_list_garage.SetItemText(index, 2, _T("离线"));
			m_list_error.InsertItem(errorindex, tmp);
			tmp = garage[i].getname().c_str();
			m_list_error.SetItemText(errorindex, 1, tmp);
			m_list_error.SetItemText(errorindex, 2, _T("离线"));
			errorindex++;
		}
		else//*/
		{
			/*if (garage[i].getnowstatus() == OFFLINE)
			{
				serverinfo.sumcar += garage[i].getsumcar();
				serverinfo.spendcar += garage[i].getspendcar();
				//garage[i].setnowstatus(ONLINE);
			}//*/

			switch (garage[i].getnowstatus())
			{
			case STATEFREE:
				m_list_garage.SetItemText(index, 2, _T("空闲"));
				break;
			case STATESAVE:
				m_list_garage.SetItemText(index, 2, _T("存车"));
				break;
			case STATEDELETE:
				m_list_garage.SetItemText(index, 2, _T("取车"));
				break;
			case STATESTOP:
				m_list_garage.SetItemText(index, 2, _T("停止"));
				break;
			case STATERSET:
				m_list_garage.SetItemText(index, 2, _T("复位"));
				break;
			case ACCEPTED:
				m_list_garage.SetItemText(index, 2, _T("已接收"));
				break;
			case BUSY:
				m_list_garage.SetItemText(index, 2, _T("运行中"));
				break;
			case OFFLINE:
				m_list_garage.SetItemText(index, 2, _T("离线"));

				//////////////////////////////////////////////////////////////////////////
				//忘加了 2016-7-28
				tmp.Format(_T("%d"), garage[i].getcarbarnid());
				m_list_garage.SetItemText(index, 2, _T("离线"));
				m_list_error.InsertItem(errorindex, tmp);
				tmp = garage[i].getname().c_str();
				m_list_error.SetItemText(errorindex, 1, tmp);
				m_list_error.SetItemText(errorindex, 2, _T("离线"));
				errorindex++;
				//////////////////////////////////////////////////////////////////////////

				break;
			default:
				m_list_garage.SetItemText(index, 2, _T("未知"));
			}
		}

		tmp.Format(_T("%02d:%02d:%02d"), garage[i].getspendtime() / 3600, garage[i].getspendtime() / 60 % 60, garage[i].getspendtime() % 60);
		m_list_garage.SetItemText(index, 3, tmp);

		tmp.Format(_T("%d"), garage[i].getsumcar());
		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[i].getspendcar());
		m_list_garage.SetItemText(index, 5, tmp);
	}

	tmp.Format(_T("%d"), serverinfo.sumcar);
	m_sumcar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation);
	m_freecar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.reservation);
	m_reservationcar.SetWindowText(tmp);

	tmp.Format(_T("%d/%d"), serverinfo.Threadwork, serverinfo.Threadsum);
	m_Threadinfo.SetWindowText(tmp);
}

/*
void CMFCAppDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
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
		/*hCom=CreateFile(serverinfo.mscomm,//COM1口
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

		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);*/
/*
		m_startend.SetWindowText(_T("暂停"));
		//		m_link_info.SetWindowText("已连接");
		link = 1;

		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_GREEN);
		m_stateico.SetIcon(hIcon);

		SetTimer(1, 1000, NULL);
	}
	else if (link)
	{
		//m_Comm.SetPortOpen(FALSE);
		link = 0;
		//Sleep(500);
		m_startend.SetWindowText(_T("继续"));
		//		m_link_info.SetWindowText("已连接");
		//CloseHandle(hCom);

		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_RED);
		m_stateico.SetIcon(hIcon);

		KillTimer(1);
	}
}//*/

/*
void CMFCAppDlg::OnBnClickedButton1()
{
	// TODO:  存车
	MYSQL_RES *res;                    //查询结果集
	//	MYSQL_ROW column;                  //数据行的列
	CString strplate;
	CString strinput;
//	CString strtmp;
	char strtmp[COMLEN];
	char pValue[COMLEN];
	DWORD dwNum;

	//DWORD start;
	//DWORD stop;
	
	m_carplate.GetWindowText(strplate);
	m_list_input.GetWindowText(strinput);

	if (strplate == "")return;

	if (strinput == "")return;

	if (serverinfo.sumcar == serverinfo.spendcar)
	{
		MessageBox(_T("车位已满"));
		return;
	}

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select plate from t_reservation where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		if (mysql_num_rows(res))
		{
//			strtmp.Format(
			sprintf_s(strtmp, COMLEN, "delete from t_reservation where plate='%s'", pValue);
			mysql_query(&serverinfo.mysql, strtmp);
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

//stop = GetTickCount();
//printf("<1<%ld>", stop - start);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select plate from t_carinfo where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		if (mysql_num_rows(res))
		{
			MessageBox(_T("车牌重复"));
			return;
		}
	}

//stop = GetTickCount();
//printf("<2<%ld>", stop - start);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strinput, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strinput, -1, pValue, dwNum, NULL, FALSE);
	
//start = GetTickCount();

	int garageid = mapinfo->nearestcarport(atoi(pValue));

//stop = GetTickCount();
//printf("<3<%ld>", stop - start);

//	delete pValue;
	if (garageid == -1)
	{
		MessageBox(_T("未找到空闲模块,请稍后再试!"));
		return;
	}

//	strtmp.Format(
	printf("最近的车库是第%d号车库\n", garageid);
	//MessageBox(strtmp);
//	CString tmp(strtmp);
//	m_carinfo.SetWindowText(tmp);
	//sumcar
	//spendcar++;

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "insert into t_carinfo(plate,start) values('%s',now())", pValue);
	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = SAVECAR;
	sendstr[1] = garage[index].getrows(garage[index].findemptycarid());
	sendstr[2] = garage[index].getcols(garage[index].findemptycarid());
	garage[index].setcommand(sendstr);

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN ,"update t_carinfo set carbarnid=%d,num=%d where plate='%s'",
		garageid, garage[index].findemptycarid(), pValue);
	garage[index].setsqlcommand(strtmp);

	garage[index].savecar();

	//stop = GetTickCount();
	//printf("<4<%ld>", stop - start);

	serverinfo.spendcar++;
}
//*/
/*
void CMFCAppDlg::OnBnClickedButton2()
{
	// TODO:  取车
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString strplate;
//	CString strtmp;
	char strtmp[COMLEN];
	char pValue[COMLEN];
	DWORD dwNum;

	m_carplate.GetWindowText(strplate);

	if (strplate == "") return;

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select carbarnid,num from t_carinfo where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}
	res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

	if (mysql_num_rows(res) == 0)
	{
		MessageBox(_T("未找到车辆"));
		return;
	}

	column = mysql_fetch_row(res);

	int garageid = atoi(column[0]);
	int num = atoi(column[1]);

	int nearoutput = mapinfo->nearestexit(garageid);
	if (nearoutput == -1)
	{
		MessageBox(_T("未找到出口,请检查地图设置!"));
		return;
	}

//	CString tmp;
	printf("最近的出口是第%d号出口\n", nearoutput);
	//MessageBox(strtmp);
//	m_carinfo.SetWindowText(tmp);
	//spendcar--;

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = DELETECAR;
	sendstr[1] = garage[index].getrows(num);
	sendstr[2] = garage[index].getcols(num);
	garage[index].setcommand(sendstr);

	//delete from t_carinfo where plate='%s';
//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "update t_carinfo set carbarnid=0,num=0 where plate='%s'", pValue);
	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "delete from t_carinfo where plate='%s'", pValue);
	garage[index].setsqlcommand(strtmp);

	garage[index].deletecar(num);

	serverinfo.spendcar--;
}
//*/

void CMFCAppDlg::On32774()
{
	// TODO:  在此添加命令处理程序代码
	ShellExecute(NULL, _T("open"), _T("http://gxy.hunnu.edu.cn/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32773()
{
	// TODO:  Web端
	ShellExecute(NULL, _T("open"), _T("http://127.0.0.1/manage/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32771()
{
	// TODO:  在此添加命令处理程序代码
	if (CanExit())
		CDialog::OnCancel();
}

void CMFCAppDlg::On32772()
{
	// TODO:  在此添加命令处理程序代码
	serverinfo.runstate = 0;

	debugmodel dlg;
	dlg.DoModal();

	serverinfo.runstate = 1;
}

void CMFCAppDlg::On32775()
{
	// TODO: 设置
}
