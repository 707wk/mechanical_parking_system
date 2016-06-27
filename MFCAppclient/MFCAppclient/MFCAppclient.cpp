
// MFCAppclient.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "MFCAppclient.h"
#include "MFCAppclientDlg.h"

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

struct serverset serverinfo;

void checkserver()
{
	SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器 
	GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构 
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&os);

	if (os.wProductType == VER_NT_WORKSTATION||info.wProcessorArchitecture==32)
	{
		AfxMessageBox(_T("建议在 64位 Windows Server 操作系统中运行本程序"));
	}
}

void readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("未找到配置文件!"));
		exit(1);
	}

	fscanf(fp, "ioId=%d\nserver=%s\niocpport=%d\nintervaltime=%d\nmaxovertime=%d",
		&serverinfo.ioId,
		serverinfo.ip, &serverinfo.iocpport,
		&serverinfo.intervaltime,&serverinfo.maxovertime);

	serverinfo.overtime = 0;
}

// CMFCAppclientApp

BEGIN_MESSAGE_MAP(CMFCAppclientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCAppclientApp 构造

CMFCAppclientApp::CMFCAppclientApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFCAppclientApp 对象

CMFCAppclientApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x641E72AF, 0xCA6B, 0x4260, { 0xAE, 0x2A, 0xE0, 0x7C, 0x4, 0xCF, 0xE0, 0xE8 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMFCAppclientApp 初始化

BOOL CMFCAppclientApp::InitInstance()
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
	// TODO: 应适当修改该字符串，
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
	_tsetlocale(LC_ALL, _T("chs"));
	///////////////////////////////////////////////////////////////////////////
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartup失败"));
		exit(1);
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		AfxMessageBox(_T("SOCKET版本不对"));
		WSACleanup();
		exit(1);
	}
	///////////////////////////////////////////////////////////////////////////
	//检测系统版本
	checkserver();
	///////////////////////////////////////////////////////////////////////////
	//读取配置文件
	readserverset();
	//////////////////////////////////////////////////////////////////////////
/*	serverinfo.sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (serverinfo.sockClient == INVALID_SOCKET)
	{
		cout << "socket 失败" << endl;
		WSACleanup();
		return FALSE;
	}
	memset(&serverinfo.addrServer, 0, sizeof(sockaddr_in));
/*	serverinfo.addrServer.sin_family = AF_INET;
	serverinfo.addrServer.sin_addr.s_addr = inet_addr(serverinfo.ip);
	serverinfo.addrServer.sin_port = htons(serverinfo.iocpport);//*/
	//////////////////////////////////////////////////////////////////////////

	CMFCAppclientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
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

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CMFCAppclientApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
