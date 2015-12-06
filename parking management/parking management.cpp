// parking management.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "parking management.h"
#include "parking managementDlg.h"
#include "md5.h"
#include <stdio.h>
#include <objbase.h>
#include <string>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	//获取计算机名+用户名
	string str;
	const int MAX_BUFFER_LEN=500 ;
    char szBuffer[MAX_BUFFER_LEN];
    DWORD dwNameLen ;
    
    dwNameLen=MAX_BUFFER_LEN ;
    if(GetComputerName(szBuffer,&dwNameLen))
		str=szBuffer;
    str+="707wk";
    dwNameLen=MAX_BUFFER_LEN ;
    if(GetUserName(szBuffer,&dwNameLen))
		str+=szBuffer;
	//////////////////////////////////////////////////////////////////////////
	//md5加密
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();
	//////////////////////////////////////////////////////////////////////////

	string query;
	query = "select state from md5 where md5key='";
	query=query+md5str+"'";

	MYSQL check;
	MYSQL_RES *res;
	MYSQL_ROW column;
	mysql_init(&check);
	if (mysql_real_connect(&check, "116.255.150.169" , "carbarn_f", "A5NDSYoUTIcFL65dE1AkzDtDzv675eXr", "carbarn", 14019, NULL, 0) == NULL)
	{
		AfxMessageBox("link:连接验证服务器失败!");
		exit(1);
	}
	mysql_query(&check,"SET NAMES 'UTF-8'");
	if(mysql_real_query(&check,query.c_str(),(UINT)query.size())!=NULL)
	{
		AfxMessageBox("search:连接验证服务器失败!");
		exit(1);
	}
	res = mysql_store_result(&check);
	column = mysql_fetch_row(res);
	//////////////////////////////////////////////////////////
	//获取符合条件数据条数
	if(mysql_num_rows(res)==0)
	{
		AfxMessageBox("未注册程序!\n请联系gtsoft_wk@foxmail.com注册");
		FILE* fpout;
		fpout=fopen("安装序列号.txt","w");
		fprintf(fpout,"%s",md5str.c_str());
		fclose(fpout);
		exit(1);
	}
	CString strtime;
	strtime.Format("UPDATE md5 SET lasttime=now() WHERE md5key='%s'",md5str.c_str());
	switch(atoi(column[0]))
	{
	case 1:
		AfxMessageBox("账号已到期!\n请联系gtsoft_wk@foxmail.com激活");
		exit(1);
		break;
	case 2:
		//最后登录日期
		mysql_query(&check,strtime.GetBuffer(0));
		break;
	default:
		AfxMessageBox("未知错误!\n请联系gtsoft_wk@foxmail.com");
		exit(1);
		break;
	}

	return 0;
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

	HANDLE hMutex=CreateMutex(NULL,FALSE,_T("立体车库管理v1.0")); 
	if(hMutex==NULL || GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		CloseHandle(hMutex);
		ExitProcess(0);
	}

	//////////////////////////////////////////////////////////////////////////
	//这写的,把自己恶心到了
	check();
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
