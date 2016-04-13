// parking management system.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "parking management system.h"
#include "parking management systemDlg.h"

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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct serverset serverinfo;

HANDLE hCom;  //全局变量，串口句柄

CCarbarnInfo* garage;

CWayFinding* mapinfo;

int* idtoindex;

int maxindex=0;

int sumgarage;

int link = 0;

CParkingmanagementsystemDlg *dlg;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemApp

BEGIN_MESSAGE_MAP(CParkingmanagementsystemApp, CWinApp)
	//{{AFX_MSG_MAP(CParkingmanagementsystemApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemApp construction

CParkingmanagementsystemApp::CParkingmanagementsystemApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CParkingmanagementsystemApp object

CParkingmanagementsystemApp theApp;

int check()
{
	//////////////////////////////////////////////////////////////////////////
	//获取计算机名+用户名
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
    str+="parking management system";
	str+=f;
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
		//AfxMessageBox("未注册程序!\n请联系gtsoft_wk@foxmail.com注册");
		query="INSERT INTO md5 (md5key) VALUES('";
		query=query+md5str+"')";
		mysql_real_query(&check,query.c_str(),(UINT)query.size());
		FILE* fpout;
		fpout=fopen("安装序列号.txt","w");
		fprintf(fpout,"%s",md5str.c_str());
		fclose(fpout);
		exit(1);
	}
	CString strtime;
	strtime.Format("UPDATE md5 SET lasttime=now() WHERE md5key='%s'",md5str.c_str());
	//状态:0:未注册 1:激活 2:停用
	switch(atoi(column[0]))
	{
	case 0:
		//AfxMessageBox("未激活!\n请联系gtsoft_wk@foxmail.com激活");
		exit(1);
		break;
	case 1:
		//最后登录日期
		mysql_query(&check,strtime.GetBuffer(0));
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

void readserverset()
{
	FILE* fp=fopen("serverSet.ini","r");
	if(fp==NULL)
	{
		printf("未找到配置文件!");
		exit(1);
	}
	
	fscanf(fp,"server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d\ncost=%lf\nmscomm=%s\nBaudRate=%d\nByteSize=%d\nParity=%d\nStopBits=%d",
		serverinfo.ip,serverinfo.name,serverinfo.password,serverinfo.database,
		&serverinfo.port,&serverinfo.cost,serverinfo.mscomm,&serverinfo.BaudRate,&serverinfo.ByteSize,&serverinfo.Parity,&serverinfo.StopBits);
	
	mysql_init(&serverinfo.mysql);
	if(mysql_real_connect(&serverinfo.mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("link:本地数据库无法连接!");
		exit(1);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemApp initialization

BOOL CParkingmanagementsystemApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
	}
	else
	{
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
		COleObjectFactory::UpdateRegistryAll();
	}

	HWND wnd;
	wnd=::FindWindow(NULL,_T("堆垛式立体车库管理 v1.2"));
	if(wnd)
	{
		AfxMessageBox(_T("程序已运行"));
		//SendMessage(wnd,WM_CLOSE,0,0);
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	//这写的,把自己恶心到了
	check();
	//////////////////////////////////////////////////////////////////////////
	//读取配置文件
	readserverset();
	//////////////////////////////////////////////////////////////////////////

	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString str;
	str="select max(id) from t_garageinfo";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);              //获取具体的数据
		
		maxindex=atoi(column[0]);
		idtoindex=new int[maxindex+1];
	}
	else
	{
		AfxMessageBox("init:001 数据库连接失败");
		exit(1) ;
	}

	for(int i=0;i<maxindex+1;i++)
	{
		idtoindex[i]=-1;
	}

	str="select id from t_garageinfo";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		int index=0;
		garage=new CCarbarnInfo[mysql_num_rows(res)];
		while(column=mysql_fetch_row(res))        //获取具体的数据
		{
			int tmpid=atoi(column[0]);
			garage[index].readdate(tmpid);
			idtoindex[tmpid]=index;
			index++;
		}
		sumgarage=index;
	}
	else
	{
		AfxMessageBox("init:002 数据库连接失败");
		exit(1) ;
	}

	mapinfo=new CWayFinding;

	dlg=new CParkingmanagementsystemDlg;
	
	m_pMainWnd = dlg;
	int nResponse = dlg->DoModal();
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

CParkingmanagementsystemApp::~CParkingmanagementsystemApp()
{
	link=0;
	//delete garage;
	//delete idtoindex;
}