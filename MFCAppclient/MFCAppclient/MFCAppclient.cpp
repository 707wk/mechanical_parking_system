
// MFCAppclient.cpp : ����Ӧ�ó��������Ϊ��
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
	SYSTEM_INFO info;        //��SYSTEM_INFO�ṹ�ж�64λAMD������ 
	GetSystemInfo(&info);    //����GetSystemInfo�������ṹ 
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&os);

	if (os.wProductType == VER_NT_WORKSTATION||info.wProcessorArchitecture==32)
	{
		AfxMessageBox(_T("������ 64λ Windows Server ����ϵͳ�����б�����"));
	}
}

void readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("δ�ҵ������ļ�!"));
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


// CMFCAppclientApp ����

CMFCAppclientApp::CMFCAppclientApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCAppclientApp ����

CMFCAppclientApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x641E72AF, 0xCA6B, 0x4260, { 0xAE, 0x2A, 0xE0, 0x7C, 0x4, 0xCF, 0xE0, 0xE8 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMFCAppclientApp ��ʼ��

BOOL CMFCAppclientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	// �����Զ������ػ�ע��/ע�����ص������С�
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Ӧ�ó������� /Embedding �� /Automation ���������ġ�
	//ʹӦ�ó�����Ϊ�Զ������������С�
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// ͨ�� CoRegisterClassObject() ע���๤����
		COleTemplateServer::RegisterAll();
	}
	// Ӧ�ó������� /Unregserver �� /Unregister ���������ġ�  �Ƴ�
	// ע����е��
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// Ӧ�ó������Զ�����ʽ������������(�� /Register
	// �� /Regserver)�����ġ�  ����ע�����������Ϳ⡣
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
		AfxMessageBox(_T("����̨����ʧ�ܡ�"));
	}
	SetConsoleTitle(_T("Debug Window"));
	_tfreopen_s(&fpDebugOut, _T("CONOUT$"), _T("w"), stdout);
	_tfreopen_s(&fpDebugIn, _T("CONIN$"), _T("r"), stdin);
	_tsetlocale(LC_ALL, _T("chs"));
	///////////////////////////////////////////////////////////////////////////
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		AfxMessageBox(_T("WSAStartupʧ��"));
		exit(1);
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		AfxMessageBox(_T("SOCKET�汾����"));
		WSACleanup();
		exit(1);
	}
	///////////////////////////////////////////////////////////////////////////
	//���ϵͳ�汾
	checkserver();
	///////////////////////////////////////////////////////////////////////////
	//��ȡ�����ļ�
	readserverset();
	//////////////////////////////////////////////////////////////////////////
/*	serverinfo.sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (serverinfo.sockClient == INVALID_SOCKET)
	{
		cout << "socket ʧ��" << endl;
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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMFCAppclientApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
