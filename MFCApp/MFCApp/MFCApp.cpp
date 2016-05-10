
// MFCApp.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"

#include "CCarbarnInfo.h"
#include "CWayFinding.h"
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

HANDLE hCom;  //ȫ�ֱ��������ھ��

DCB dcb;

CCarbarnInfo* garage;

CWayFinding* mapinfo;

int reservation = 0;

int* idtoindex;

int maxindex = 0;

int sumgarage;

int link = 0;

CMFCAppDlg *dlg;

int check()
{
	//////////////////////////////////////////////////////////////////////////
	//��ȡ�������+�û���
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
	char *pValue = new char[1024];
	memset(pValue, 0, 1024);
	WideCharToMultiByte(CP_OEMCP, NULL, ifo.szCSDVersion, -1, pValue, dwNum, NULL, FALSE);
	string f = pValue;
	delete pValue;

//	CString qwe;
	char qwe[1024];
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
	//md5����
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
		AfxMessageBox(_T("link:������֤������ʧ��!"));
		exit(1);
	}
	mysql_query(&check, "SET NAMES 'UTF-8'");
	if (mysql_real_query(&check, query.c_str(), (UINT)query.size()) != NULL)
	{
		AfxMessageBox(_T("search:������֤������ʧ��!"));
		exit(1);
	}
	res = mysql_store_result(&check);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//��ȡ����������������
	if (mysql_num_rows(res) == 0)
	{
		//AfxMessageBox("δע�����!\n����ϵgtsoft_wk@foxmail.comע��");
		query = "INSERT INTO md5 (md5key) VALUES('";
		query = query + md5str + "')";
		mysql_real_query(&check, query.c_str(), (UINT)query.size());
		FILE* fpout;
		fpout = fopen("��װ���к�.txt", "w");
		fprintf(fpout, "%s", md5str.c_str());
		fclose(fpout);
		exit(1);
	}
//	CString strtime;
	char strtime[1024];
	sprintf(strtime,"UPDATE md5 SET lasttime=now() WHERE md5key='%s'", md5str.c_str());
	//״̬:0:δע�� 1:���� 2:ͣ��
	switch (atoi(column[0]))
	{
	case 0:
		//AfxMessageBox("δ����!\n����ϵgtsoft_wk@foxmail.com����");
		exit(1);
		break;
	case 1:
		//����¼����
		mysql_query(&check, strtime);
		break;
	case 2:
		//AfxMessageBox("�˺���ͣ��!\n����ϵgtsoft_wk@foxmail.com����");
		exit(1);
		break;
	default:
		//AfxMessageBox("δ֪����!\n����ϵgtsoft_wk@foxmail.com�޸�");
		exit(1);
		break;
	}

	return 0;
}

void readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		printf("δ�ҵ������ļ�!");
		exit(1);
	}

	fscanf(fp, "server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d\ncost=%lf\nmscomm=%s\nBaudRate=%d\nByteSize=%d\nParity=%d\nStopBits=%d\nintervalTime=%d",
		serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database,
		&serverinfo.port, &serverinfo.cost, serverinfo.mscomm, &serverinfo.BaudRate, &serverinfo.ByteSize, &serverinfo.Parity, &serverinfo.StopBits,
		&serverinfo.intervaltime);

	mysql_init(&serverinfo.mysql);
	if (mysql_real_connect(&serverinfo.mysql, serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox(_T("start:�������ݿ��޷�����!"));
		exit(1);
	}
}

// CMFCAppApp

BEGIN_MESSAGE_MAP(CMFCAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCAppApp ����

CMFCAppApp::CMFCAppApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCAppApp ����

CMFCAppApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x66B0105E, 0xC748, 0x4017, { 0xAB, 0xF1, 0x11, 0xC9, 0x5E, 0x6A, 0xF2, 0xBE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CMFCAppApp ��ʼ��

BOOL CMFCAppApp::InitInstance()
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
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
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

	HWND wnd;
	wnd = ::FindWindow(NULL, _T("�Ѷ�ʽ���峵����� v1.3"));
	if (wnd)
	{
		AfxMessageBox(_T("����������"));
		//SendMessage(wnd,WM_CLOSE,0,0);
		return FALSE;
	}
//	AfxMessageBox(_T("001"));
	//////////////////////////////////////////////////////////////////////////
	//��д��,���Լ����ĵ���
	check();
//AfxMessageBox(_T("002"));
	//////////////////////////////////////////////////////////////////////////
	//��ȡ�����ļ�
	readserverset();
//	AfxMessageBox(_T("003"));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	CString tmp(serverinfo.mscomm);
	hCom = CreateFile(tmp,//COM1��
		GENERIC_READ | GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //�ص���ʽ
		NULL);
	if (hCom == (HANDLE)-1)
	{
		AfxMessageBox(_T("��COMʧ��!"));
		exit(1);
		return FALSE;
	}

	SetupComm(hCom, COMLEN, COMLEN); //���뻺����������������Ĵ�С����100

	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���


	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = serverinfo.BaudRate; //������Ϊ9600
	dcb.ByteSize = serverinfo.ByteSize; //ÿ���ֽ���8λ
	dcb.Parity = serverinfo.Parity;   //��żУ��λ
	dcb.StopBits = serverinfo.StopBits; //ֹͣλ
	SetCommState(hCom, &dcb);

	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	//////////////////////////////////////////////////////////////////////////

	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���
	CString str;
//	str = "select max(id) from t_garageinfo";

	mysql_query(&serverinfo.mysql, "SET NAMES 'UTF-8'");

	if (mysql_query(&serverinfo.mysql, "select max(id) from t_garageinfo") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
		column = mysql_fetch_row(res);              //��ȡ���������

		maxindex = atoi(column[0]);
		idtoindex = new int[maxindex + 1];
	}
	else
	{
		AfxMessageBox(_T("init:001 ���ݿ�����ʧ��"));
		exit(1);
	}

	for (int i = 0; i<maxindex + 1; i++)
	{
		idtoindex[i] = -1;
	}
//	AfxMessageBox(_T("004"));
//	str = "select id from t_garageinfo";

	mysql_query(&serverinfo.mysql, "SET NAMES 'UTF-8'");

	if (mysql_query(&serverinfo.mysql, "select id from t_garageinfo") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
		int index = 0;
		garage = new CCarbarnInfo[(unsigned int)mysql_num_rows(res)];
		while (column = mysql_fetch_row(res))        //��ȡ���������
		{
			int tmpid = atoi(column[0]);
			garage[index].readdate(tmpid);
			idtoindex[tmpid] = index;
			index++;
		}
		sumgarage = index;
	}
	else
	{
		AfxMessageBox(_T("init:002 ���ݿ�����ʧ��"));
		exit(1);
	}
//	AfxMessageBox(_T("005"));
	mapinfo = new CWayFinding;
//	AfxMessageBox(_T("006"));
	CMFCAppDlg maindlg;
	dlg = &maindlg;
	m_pMainWnd = &maindlg;
	INT_PTR nResponse = maindlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
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

int CMFCAppApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
