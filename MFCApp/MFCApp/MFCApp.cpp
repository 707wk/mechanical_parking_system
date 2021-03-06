
// MFCApp.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"

#include "IOCPserver.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "ioClient.h"
#include "md5.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include <stdio.h>
#include <objbase.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma warning(disable: 4996)  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Gdiplus::GdiplusStartupInput    m_gdiplusStartupInput;
ULONG_PTR                       m_gdiplusToken;

struct serverset serverinfo;

pthread_mutex_t work_mutex; //全局互斥锁对象

HANDLE hCom;  //全局变量，串口句柄

DCB dcb;

CCarbarnInfo* garage;

CWayFinding* mapinfo;

struct ioClient* ioClient_list;

int* idtoindex_garage;

int* idtoindex_ioClient;

int maxindex_garage = 0;

int maxindex_ioClient = 0;

int sumgarage=0;

int sumioClient=0;

CMFCAppDlg *dlg;

int check()
{
	//////////////////////////////////////////////////////////////////////////
	//获取计算机名+用户名
	string str;
	const int MAX_BUFFER_LEN = 500;
	char szBuffer[MAX_BUFFER_LEN];
	DWORD dwNameLen;
	OSVERSIONINFOEX ifo;
	ifo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&ifo);

	DWORD a = ifo.dwBuildNumber;
	DWORD b = ifo.dwMajorVersion;
	DWORD c = ifo.dwMinorVersion;
	DWORD d = ifo.dwOSVersionInfoSize;
	DWORD e = ifo.dwPlatformId;
//	string f = ifo.szCSDVersion;

	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, ifo.szCSDVersion, -1, NULL, 0, NULL, FALSE);
	char *pValue = new char[COMLEN];
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, ifo.szCSDVersion, -1, pValue, dwNum, NULL, FALSE);
	string f = pValue;
	delete pValue;

//	CString qwe;
	char qwe[COMLEN];
	sprintf(qwe,"-%X%X%X%X%X", a, b, c, d, e);

	//string szBuffer;
	dwNameLen = MAX_BUFFER_LEN;
	if (GetComputerName((LPWSTR)szBuffer, &dwNameLen))
		str = szBuffer;
	str += "parking management system";
	str += f;
	dwNameLen = MAX_BUFFER_LEN;
	if (GetUserName((LPWSTR)szBuffer, &dwNameLen))
		str += szBuffer;
	//////////////////////////////////////////////////////////////////////////
	//md5加密
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str = md5.toString();
	md5.reset();
	transform(md5str.begin(), md5str.end(), md5str.begin(), ::toupper);
	//////////////////////////////////////////////////////////////////////////
	md5str += qwe;

	string query;
	query = "select state from md5 where md5key='";
	query = query + md5str + "'";

	MYSQL check;
	MYSQL_RES *res;
	MYSQL_ROW column;
	mysql_init(&check);
	if (mysql_real_connect(&check, "116.255.150.169", "carbarn_f", "A5NDSYoUTIcFL65dE1AkzDtDzv675eXr", "carbarn", 14019, NULL, 0) == NULL)
	{
		AfxMessageBox(_T("link:连接验证服务器失败!"));
		exit(1);
	}
	mysql_query(&check, "SET NAMES 'GB2312'");
	if (mysql_real_query(&check, query.c_str(), (UINT)query.size()) != NULL)
	{
		AfxMessageBox(_T("search:连接验证服务器失败!"));
		exit(1);
	}
	res = mysql_store_result(&check);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//获取符合条件数据条数
	if (mysql_num_rows(res) == 0)
	{
		//AfxMessageBox("未注册程序!\n请联系gtsoft_wk@foxmail.com注册");
		query = "INSERT INTO md5 (md5key) VALUES('";
		query = query + md5str + "')";
		mysql_real_query(&check, query.c_str(), (UINT)query.size());
		FILE* fpout;
		fpout = fopen("安装序列号.txt", "w");
		fprintf(fpout, "%s", md5str.c_str());
		fclose(fpout);
		exit(1);
	}
//	CString strtime;
	char strtime[COMLEN];
	sprintf(strtime,"UPDATE md5 SET lasttime=now() WHERE md5key='%s'", md5str.c_str());
	//状态:0:未注册 1:激活 2:停用
	switch (atoi(column[0]))
	{
	case 0:
		//AfxMessageBox("未激活!\n请联系gtsoft_wk@foxmail.com激活");
		exit(1);
		break;
	case 1:
		//最后登录日期
		mysql_query(&check, strtime);
		break;
	case 2:
		//AfxMessageBox("账号已停用!\n请联系gtsoft_wk@foxmail.com启用");
		exit(1);
		break;
	default:
		//AfxMessageBox("未知错误!\n请联系gtsoft_wk@foxmail.com修复");
		exit(1);
		break;
	}

	return 0;
}

void checkserver()
{
	SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器 
	GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构 
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&os);

	if (os.wProductType == VER_NT_WORKSTATION || info.wProcessorArchitecture == 32)
	{
		//AfxMessageBox(_T("建议在 64位 Windows Server 操作系统中运行本程序"));
		printf("建议在 64位 Windows Server 操作系统中运行本程序\n");
	}
}

void readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("未找到配置文件!"));
		//printf("未找到配置文件!");
		exit(1);
	}

	fscanf(fp, "server=%s\nusername=%s\npwd=%s\ndatabase=%s\ndataport=%d\niocpport=%d\ncost=%lf\nreservationtime=%d\nmscomm=%s\nBaudRate=%d\nByteSize=%d\nParity=%d\nStopBits=%d\nintervalTime=%d",
		serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database,
		&serverinfo.dataport, &serverinfo.iocpport,
		&serverinfo.cost, &serverinfo.reservationtime,
		serverinfo.mscomm, &serverinfo.BaudRate, &serverinfo.ByteSize, &serverinfo.Parity, &serverinfo.StopBits,
		&serverinfo.intervaltime);

	mysql_init(&serverinfo.mysql);
	if (mysql_real_connect(&serverinfo.mysql, serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.dataport, NULL, 0) == NULL)
	{
		AfxMessageBox(_T("start:本地数据库无法连接!"));
		exit(1);
	}

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	serverinfo.Threadsum = SystemInfo.dwNumberOfProcessors*2;

}

void getlocationip()
{
	WSADATA wsadata;
	WORD dwVersionRequested=0;
	int err;
	err = WSAStartup(dwVersionRequested, &wsadata);
	char hostname[128];
	if (gethostname(hostname, 128) == 0)
	{
		printf("%s\n", hostname);
		//计算机名字
	}
	//char buf[20];
	memset(serverinfo.locationip,0,40);
	struct hostent*pHost = gethostbyname(hostname);
	for (int i = 0;pHost != NULL&&pHost->h_addr_list[i] != NULL;i++)
	{
		//将它放入字符数组中便于应用
		strcpy(serverinfo.locationip, inet_ntoa(*(struct in_addr*)pHost->h_addr_list[i]));
		//inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]);
		//IP地址
		printf("%s\n", serverinfo.locationip);
	}
	WSACleanup();
}

// CMFCAppApp

BEGIN_MESSAGE_MAP(CMFCAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCAppApp 构造

CMFCAppApp::CMFCAppApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	serverinfo.sumcar = 0;
	serverinfo.spendcar = 0;
	serverinfo.Threadsum = 0;
	serverinfo.Threadwork = 0;
	serverinfo.activeThreadtime = 0;
	serverinfo.runstate = 0;
	//serverinfo.lockflage = 0;
}


// 唯一的一个 CMFCAppApp 对象

CMFCAppApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x66B0105E, 0xC748, 0x4017, { 0xAB, 0xF1, 0x11, 0xC9, 0x5E, 0x6A, 0xF2, 0xBE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMFCAppApp 初始化

BOOL CMFCAppApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	// 分析自动化开关或注册/注销开关的命令行。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	//使应用程序作为自动化服务器运行。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// 通过 CoRegisterClassObject() 注册类工厂。
		COleTemplateServer::RegisterAll();
	}
	// 应用程序是用 /Unregserver 或 /Unregister 开关启动的。  移除
	// 注册表中的项。
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// 应用程序是以独立方式或用其他开关(如 /Register
	// 或 /Regserver)启动的。  更新注册表项，包括类型库。
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	HWND wnd;
	wnd = ::FindWindow(NULL, _T("堆垛式立体车库管理系统"));
	if (wnd)
	{
		AfxMessageBox(_T("程序已运行"));
		//SendMessage(wnd,WM_CLOSE,0,0);
		return FALSE;
	}

	///////////////////////////////////////////////////////////////////////////
	FILE* fpDebugOut = NULL;
	FILE* fpDebugIn = NULL;
	if (!AllocConsole())
	{
		AfxMessageBox(_T("控制台生成失败。"));
	}
	SetConsoleTitle(_T("Debug Window"));
	_tfreopen_s(&fpDebugOut, _T("CONOUT$"), _T("w"), stdout);
	_tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin);
	_tsetlocale(LC_ALL, _T("chs"));     //这是必要的，否则unicode模式下使用C库函数控制台输出不了中文
	/////////////////////////////////////////////////////////////////////////*/
	//检测系统版本号
	checkserver();
	//////////////////////////////////////////////////////////////////////////
	//这写的,把自己恶心到了
	//check();
	//////////////////////////////////////////////////////////////////////////
	//读取配置文件
	readserverset();
	//////////////////////////////////////////////////////////////////////////
	//获取本机ip
	getlocationip();
	//////////////////////////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////////////////////
	//读取车库模块列表
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString str;

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select max(id) from t_garageinfo") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column = mysql_fetch_row(res);              //获取具体的数据

		maxindex_garage = atoi(column[0]);
		idtoindex_garage = new int[maxindex_garage + 1];
	}
	else
	{
		AfxMessageBox(_T("init:001 数据库连接失败"));
		exit(1);
	}

	for (int i = 0; i<maxindex_garage + 1; i++)
	{
		idtoindex_garage[i] = -1;
	}

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select id from t_garageinfo ORDER BY id ASC") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		int index = 0;
		garage = new CCarbarnInfo[(unsigned int)mysql_num_rows(res)];
		while (column = mysql_fetch_row(res))        //获取具体的数据
		{
			int tmpid = atoi(column[0]);
			garage[index].readdate(tmpid);

//			serverinfo.sumcar += garage[index].getsumcar();读取异常
//			serverinfo.spendcar += garage[index].getspendcar();读取异常

			idtoindex_garage[tmpid] = index;
			index++;
		}
		sumgarage = index;
	}
	else
	{
		AfxMessageBox(_T("init:002 数据库连接失败"));
		exit(1);
	}
	////////////////////////////////////////////////////////////////////////*/

	//////////////////////////////////////////////////////////////////////////
	//读取出入客户端列表
	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select max(type_id) from t_map where type in (1,2)") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column = mysql_fetch_row(res);              //获取具体的数据

		maxindex_ioClient = atoi(column[0]);
		idtoindex_ioClient = new int[maxindex_ioClient + 1];
	}
	else
	{
		AfxMessageBox(_T("init:003 数据库连接失败"));
		exit(1);
	}

	for (int i = 0; i<maxindex_ioClient + 1; i++)
	{
		idtoindex_ioClient[i] = -1;
	}

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select type_id,type,value from t_map where type in (1,2) ORDER BY type_id ASC") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		int index = 0;
		sumioClient = (unsigned int)mysql_num_rows(res);
		ioClient_list = new struct ioClient[sumioClient];

		for (int i = 0; i<sumioClient; i++)//对于下标越界，我确实没话说 2016-07-28
		{
			ioClient_list[i].type = 0;
			ioClient_list[i].nowstatus = ONLINE;
			ioClient_list[i].spendtime = 0;
		}

		while (column = mysql_fetch_row(res))        //获取具体的数据
		{
			//AfxMessageBox(_T("1"));
			int tmpid = atoi(column[0]);
			//ioClient_list[index].readdate(tmpid);

			if(idtoindex_ioClient[tmpid]==-1)
			{
				idtoindex_ioClient[tmpid] = index;

				ioClient_list[index].id = tmpid;
				ioClient_list[index].type = ioClient_list[index].type | atoi(column[1]);
				ioClient_list[index].name = column[2];

				index++;
			}
			else
			{
				ioClient_list[idtoindex_ioClient[tmpid]].type = ioClient_list[idtoindex_ioClient[tmpid]].type | atoi(column[1]);
			}
		}
		sumioClient = index;
	}
	else
	{
		AfxMessageBox(_T("init:004 数据库连接失败"));
		exit(1);
	}
	////////////////////////////////////////////////////////////////////////*/

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select plate from t_reservation") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		serverinfo.reservation = (int)mysql_num_rows(res);
	}
	else
	{
		AfxMessageBox(_T("init:005 数据库连接失败"));
		exit(1);
	}

	mapinfo = new CWayFinding;

	//初始化GDI+.  
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	CMFCAppDlg maindlg;
	dlg = &maindlg;
	m_pMainWnd = &maindlg;
	INT_PTR nResponse = maindlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	fclose(fpDebugOut);
	fclose(fpDebugIn);
	FreeConsole();

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CMFCAppApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	
	return CWinApp::ExitInstance();
}
