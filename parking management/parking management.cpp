// parking management.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "parking management.h"
#include "parking managementDlg.h"
#include "md5.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include <stdio.h>
#include <objbase.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MYSQL mysql;

struct serverset serverinfo;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementApp

BEGIN_MESSAGE_MAP(CParkingmanagementApp, CWinApp)
	//{{AFX_MSG_MAP(CParkingmanagementApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementApp construction

CParkingmanagementApp::CParkingmanagementApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CParkingmanagementApp object

CParkingmanagementApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementApp initialization

int check()
{
	//////////////////////////////////////////////////////////////////////////
	//��ȡ�������+�û���
	string str;
	const int MAX_BUFFER_LEN=500 ;
    char szBuffer[MAX_BUFFER_LEN];
    DWORD dwNameLen ;
	OSVERSIONINFOEX ifo;
	ifo.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	GetVersionEx((OSVERSIONINFO *)&ifo);
	
	DWORD a=ifo.dwBuildNumber;
	DWORD b=ifo.dwMajorVersion;
	DWORD c=ifo.dwMinorVersion;
	DWORD d=ifo.dwOSVersionInfoSize;
	DWORD e=ifo.dwPlatformId;
	CString f=ifo.szCSDVersion;
	
	CString qwe;
	qwe.Format("-%X%X%X%X%X",a,b,c,d,e);
    
    dwNameLen=MAX_BUFFER_LEN ;
    if(GetComputerName(szBuffer,&dwNameLen))
		str=szBuffer;
    str+="parking management";
	str+=f;
    dwNameLen=MAX_BUFFER_LEN ;
    if(GetUserName(szBuffer,&dwNameLen))
		str+=szBuffer;
	//////////////////////////////////////////////////////////////////////////
	//md5����
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();
	transform(md5str.begin(), md5str.end(), md5str.begin(), ::toupper);
	//////////////////////////////////////////////////////////////////////////
	md5str+=qwe;

	string query;
	query = "select state from md5 where md5key='";
	query=query+md5str+"'";

	MYSQL check;
	MYSQL_RES *res;
	MYSQL_ROW column;
	mysql_init(&check);
	if (mysql_real_connect(&check, "116.255.150.169" , "carbarn_f", "A5NDSYoUTIcFL65dE1AkzDtDzv675eXr", "carbarn", 14019, NULL, 0) == NULL)
	{
		AfxMessageBox("link:������֤������ʧ��!");
		exit(1);
	}
	mysql_query(&check,"SET NAMES 'UTF-8'");
	if(mysql_real_query(&check,query.c_str(),(UINT)query.size())!=NULL)
	{
		AfxMessageBox("search:������֤������ʧ��!");
		exit(1);
	}
	res = mysql_store_result(&check);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//��ȡ����������������
	if(mysql_num_rows(res)==0)
	{
		AfxMessageBox("δע�����!\n����ϵgtsoft_wk@foxmail.comע��");
		query="INSERT INTO md5 (md5key) VALUES('";
		query=query+md5str+"')";
		mysql_real_query(&check,query.c_str(),(UINT)query.size());
		FILE* fpout;
		fpout=fopen("��װ���к�.txt","w");
		fprintf(fpout,"%s",md5str.c_str());
		fclose(fpout);
		exit(1);
	}
	CString strtime;
	strtime.Format("UPDATE md5 SET lasttime=now() WHERE md5key='%s'",md5str.c_str());
	//״̬:0:δע�� 1:���� 2:ͣ��
	switch(atoi(column[0]))
	{
	case 0:
		AfxMessageBox("δ����!\n����ϵgtsoft_wk@foxmail.com����");
		exit(1);
		break;
	case 1:
		//����¼����
		mysql_query(&check,strtime.GetBuffer(0));
		break;
	case 2:
		AfxMessageBox("�˺���ͣ��!\n����ϵgtsoft_wk@foxmail.com����");
		exit(1);
		break;
	default:
		AfxMessageBox("δ֪����!\n����ϵgtsoft_wk@foxmail.com�޸�");
		exit(1);
		break;
	}

	return 0;
}

void readserverset()
{
	FILE* fp=fopen("serverSet.ini","r");
	if(fp==NULL)
	{
		printf("δ�ҵ������ļ�!");
		exit(1);
	}
	
	fscanf(fp,"server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d\ncost=%lf\nmscomm=%d",
		serverinfo.ip,serverinfo.name,serverinfo.password,serverinfo.database,&serverinfo.port,&serverinfo.cost,&serverinfo.mscomm);
	
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("link:�������ݿ��޷�����!");
		exit(1);
	}
}

BOOL CParkingmanagementApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	HANDLE hMutex=CreateMutex(NULL,FALSE,_T("���峵�����v1.0")); 
	if(hMutex==NULL || GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		CloseHandle(hMutex);
		ExitProcess(0);
	}

	//////////////////////////////////////////////////////////////////////////
	//��д��,���Լ����ĵ���
	check();
	//////////////////////////////////////////////////////////////////////////
	//��ȡ�����ļ�
	readserverset();
	//////////////////////////////////////////////////////////////////////////

	CParkingmanagementDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
