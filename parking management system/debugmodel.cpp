// debugmodel.cpp : implementation file
//

#include "stdafx.h"
#include "parking management system.h"
#include "debugmodel.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

//extern CCarbarnInfo* garage;

//extern CWayFinding* mapinfo;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

extern int link;

/////////////////////////////////////////////////////////////////////////////
// debugmodel dialog


debugmodel::debugmodel(CWnd* pParent /*=NULL*/)
	: CDialog(debugmodel::IDD, pParent)
{
	//{{AFX_DATA_INIT(debugmodel)
	//}}AFX_DATA_INIT
}


void debugmodel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(debugmodel)
	DDX_Control(pDX, IDC_EDIT2, m_col);
	DDX_Control(pDX, IDC_EDIT1, m_row);
	DDX_Control(pDX, IDC_COMBO1, m_garage_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(debugmodel, CDialog)
	//{{AFX_MSG_MAP(debugmodel)
	ON_BN_CLICKED(IDC_BUTTON1, savecar)
	ON_BN_CLICKED(IDC_BUTTON2, delcar)
	ON_BN_CLICKED(IDC_BUTTON3, stop)
	ON_BN_CLICKED(IDC_BUTTON4, reset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// debugmodel message handlers

BOOL debugmodel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列

	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,"select id from t_garageinfo")==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		
		while(column=mysql_fetch_row(res))        //获取具体的数据
		{
			m_garage_id.AddString(column[0]);
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}

	CEdit* pedit=(CEdit*)m_garage_id.GetWindow(GW_CHILD);
	pedit->SetReadOnly(true);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void debugmodel::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void debugmodel::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void debugmodel::savecar() 
{
	// TODO: Add your control notification handler code here
	char data[6] = "12345";
	CString tmp;
	m_garage_id.GetWindowText(tmp);
	
	data[0] = atoi(tmp.GetBuffer(0));
	data[1] = SAVECAR;
	m_row.GetWindowText(tmp);
	data[2] = atoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);
	data[3] = atoi(tmp.GetBuffer(0));
	
	data[4]=(data[0]+data[1]+data[2]+data[3])%CHECKMOD;
	
	OnSend(data,5);
}

void debugmodel::delcar() 
{
	// TODO: Add your control notification handler code here
	char data[6] = "12345";
	CString tmp;
	m_garage_id.GetWindowText(tmp);
	
	data[0] = atoi(tmp.GetBuffer(0));
	data[1] = DELETECAR;
	m_row.GetWindowText(tmp);
	data[2] = atoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);
	data[3] = atoi(tmp.GetBuffer(0));
	
	data[4]=(data[0]+data[1]+data[2]+data[3])%CHECKMOD;
	
	OnSend(data,5);
}

void debugmodel::stop() 
{
	// TODO: Add your control notification handler code here
	char data[6] = "12345";
	CString tmp;
	m_garage_id.GetWindowText(tmp);
	
	data[0] = atoi(tmp.GetBuffer(0));
	data[1] = STOP;
	m_row.GetWindowText(tmp);
	data[2] = atoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);
	data[3] = atoi(tmp.GetBuffer(0));
	
	data[4]=(data[0]+data[1]+data[2]+data[3])%CHECKMOD;
	
	OnSend(data,5);
}

void debugmodel::reset() 
{
	// TODO: Add your control notification handler code here
	char data[6] = "12345";
	CString tmp;
	m_garage_id.GetWindowText(tmp);
	
	data[0] = atoi(tmp.GetBuffer(0));
	data[1] = RESET;
	m_row.GetWindowText(tmp);
	data[2] = atoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);
	data[3] = atoi(tmp.GetBuffer(0));
	
	data[4]=(data[0]+data[1]+data[2]+data[3])%CHECKMOD;
	
	OnSend(data,5);
}
