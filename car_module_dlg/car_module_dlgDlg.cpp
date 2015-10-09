// car_module_dlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "car_module_dlg.h"
#include "car_module_dlgDlg.h"
#include "DataStructure.h"
#include "car_module.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

extern struct serverset serverinfo;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCar_module_dlgDlg dialog

CCar_module_dlgDlg::CCar_module_dlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCar_module_dlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCar_module_dlgDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hicnok=AfxGetApp()->LoadIcon(IDI_ICON3);
	m_hicnno=AfxGetApp()->LoadIcon(IDI_ICON2);
	m_hicncar=AfxGetApp()->LoadIcon(IDI_ICON1);
	btnnum=0;
	btn=NULL;
}

void CCar_module_dlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCar_module_dlgDlg)
	DDX_Control(pDX, IDC_EDIT9, m_entry);
	DDX_Control(pDX, IDC_EDIT1, m_carid);
	DDX_Control(pDX, IDC_COMBO1, m_maclist);
	DDX_Control(pDX, IDC_EDIT7, m_cols);
	DDX_Control(pDX, IDC_EDIT6, m_rows);
	DDX_Control(pDX, IDC_EDIT5, m_speedcols);
	DDX_Control(pDX, IDC_EDIT4, m_speedrows);
	DDX_Control(pDX, IDC_EDIT3, m_finish);
	DDX_Control(pDX, IDC_EDIT2, m_sum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCar_module_dlgDlg, CDialog)
	//{{AFX_MSG_MAP(CCar_module_dlgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCar_module_dlgDlg message handlers

BOOL CCar_module_dlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	/*if(garage.readdate(1234))return FALSE;
	
	showbutton();*/
	showmaclist();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCar_module_dlgDlg::OnPaint() 
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
HCURSOR CCar_module_dlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCar_module_dlgDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CCar_module_dlgDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	/*
	CString str;
	int nIndex = m_maclist.GetCurSel();
	m_maclist.GetLBText( nIndex, str);
	if(str=="")return ;
	garage.savedatetomysql(atoi(str.GetBuffer(0)));
	*/
	CDialog::OnCancel();
}

//存车
void CCar_module_dlgDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int index=garage.savecar();
	int sum=garage.getrows()*garage.getcols();
	if(index!=-1)
	{
		//////////////////////////////////////////////////////////////////////////
		//下标与序号不对应
		btn[sum-index].SetIcon(m_hicnno);
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		MessageBox("没有空余车位");
	}
	//garage.readdate();

	CString str;
	int nIndex = m_maclist.GetCurSel();
	m_maclist.GetLBText( nIndex, str);
	if(str=="")return ;
	garage.savedatetomysql(atoi(str.GetBuffer(0)));
	upinfodate();
}

//取车
void CCar_module_dlgDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_carid.GetWindowText(str);

	int index=atoi(str.GetBuffer(0));
	int sum=garage.getrows()*garage.getcols();

	index=garage.deletecar(index);

	if(index!=-1)
	{
		//////////////////////////////////////////////////////////////////////////
		//下标与序号不对应
		btn[sum-index].SetIcon(m_hicnok);
		//////////////////////////////////////////////////////////////////////////
	}
	else
	{
		MessageBox("未找到车辆");
	}

	int nIndex = m_maclist.GetCurSel();
	m_maclist.GetLBText( nIndex, str);
	if(str=="")return ;
	garage.savedatetomysql(atoi(str.GetBuffer(0)));

	upinfodate();
}

//刷新信息
void CCar_module_dlgDlg::upinfodate()
{
	CString str;
	//str.Format("%d",garage.getmac());
	//m_maclist.SetWindowText(str);
	
	str.Format("%d",garage.getsumcar());
	m_sum.SetWindowText(str);
	
	str.Format("%d",garage.getspendcar());
	m_finish.SetWindowText(str);
	
	str.Format("%f",garage.getspeedrows());
	m_speedrows.SetWindowText(str);
	
	str.Format("%f",garage.getspeedcols());
	m_speedcols.SetWindowText(str);
	
	str.Format("%d",garage.getrows());
	m_rows.SetWindowText(str);
	
	str.Format("%d",garage.getcols());
	m_cols.SetWindowText(str);

	m_carid.SetWindowText("");
}

//刷新列表
void CCar_module_dlgDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	showmaclist();
}

//新增
void CCar_module_dlgDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if(garage.checkfist()!=-1)hidebutton();

	CString str;
	m_maclist.GetWindowText(str);
	garage.setmac(atoi(str.GetBuffer(0)));

	m_rows.GetWindowText(str);
	garage.setrows(atoi(str.GetBuffer(0)));

	m_cols.GetWindowText(str);
	garage.setcols(atoi(str.GetBuffer(0)));
	
	m_speedrows.GetWindowText(str);
	garage.setspeedrows(atof(str.GetBuffer(0)));

	m_speedcols.GetWindowText(str);
	garage.setspeedcols(atof(str.GetBuffer(0)));

	garage.newgarage();

	m_entry.GetWindowText(str);
	string tmpstr=str.GetBuffer(0);
	stringstream stream;
	stream<<tmpstr;
	for(int index;stream>>index;)
	{
		//str.Format("%d:%d",index,garage.setentry(index));
		//MessageBox(str);
		garage.setentry(index);
	}
	//garage.savedatetomysql(garage.getmac());

	showmaclist();
	btnnum=0;
}

void CCar_module_dlgDlg::showbutton()
{
	//////////////////////////////////////////////////////////////////////////
	//不知道为什么,行列反了,但在显示的却是正确的
	int cols=garage.getcols();
	int rows=garage.getrows();
	//////////////////////////////////////////////////////////////////////////
	
    btn = new CButton[cols*rows];  
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON|BS_ICON;//|WS_DISABLED;  
	int startpoint[2]={220,15};           //起始点
	int gao=50;                           //间隔高
	int kuan=50;                          //间隔宽
	int num[2]={50,50};                   //长宽
    for(int i = 0; i < cols*rows; i++){
		CString tmp;
		tmp.Format("%d",cols*rows-i);
        btn[i].Create(tmp, dwStyle,CRect(startpoint[0]+i%cols*kuan,startpoint[1]+i/cols*gao,startpoint[0]+i%cols*kuan+num[0],startpoint[1]+i/cols*gao+num[1]),this,buttonID+i);   
        //btn[i].SetFont(GetParent()->GetFont());  
		//btn[i].SetIcon(m_hicnok);
		//////////////////////////////////////////////////////////////////////////
		//坐标不一致,导致少一个车位
		if(garage.getcond(cols*rows-i)==0)
		{
			//tmp="空闲";
			btn[i].SetIcon(m_hicnok);
		}
		else if(garage.getcond(cols*rows-i)==1)
		{
			//tmp="占用";
			btn[i].SetIcon(m_hicnno);
		}
		else if(garage.getcond(cols*rows-i)==2)
		{
			//tmp="入口";
			btn[i].SetIcon(m_hicncar);
		}
		else
		{
			tmp.Format("未知数据 第%d车位:%d",cols*rows-i,garage.getcond(cols*rows-i));
			MessageBox(tmp);
		}
		//////////////////////////////////////////////////////////////////////////
    } 
	
	upinfodate();
	
	//////////////////////////////////////////////////////////////////////////
	//设置窗口大小
	CRect rect;
	GetClientRect (&rect);
	int cx=rect.Width ();
	int cy=rect.Height ();
	
	cx=startpoint[0]+cols*kuan+30;
	cy=startpoint[1]+rows*gao;
	cy=cy>rect.Height ()?cy+startpoint[1]:rect.Height ()+8;
	cy+=(startpoint[1]*2);
	
	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,cx,cy,SWP_NOZORDER|SWP_NOMOVE);
	//////////////////////////////////////////////////////////////////////////
}

void CCar_module_dlgDlg::hidebutton()
{
	if(btn==NULL)
	{
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	//不知道为什么,行列反了,但在显示的却是正确的
	int cols=garage.getcols();
	int rows=garage.getrows();
	//////////////////////////////////////////////////////////////////////////

	int startpoint[2]={220,15};           //起始点
	int gao=50;                           //间隔高
	int kuan=50;                          //间隔宽
	int num[2]={50,50};                   //长宽

    for(int i = 0; i < btnnum; i++){
			btn[i].DestroyWindow();	
			delete btn[i];
    }
	
	//upinfodate();
	/*
	//////////////////////////////////////////////////////////////////////////
	//设置窗口大小
	CRect rect;
	GetClientRect (&rect);
	int cx=rect.Width ();
	int cy=rect.Height ();
	
	cx=startpoint[0]+cols*kuan+30;
	cy=startpoint[1]+rows*gao;
	cy=cy>rect.Height ()?cy+startpoint[1]:rect.Height ();
	cy+=(startpoint[1]*2);
	
	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,0,cx,cy,SWP_NOZORDER|SWP_NOMOVE);
	//////////////////////////////////////////////////////////////////////////
	*/
}

void CCar_module_dlgDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	if(garage.checkfist()!=-1)hidebutton();
	CString str;
	int nIndex = m_maclist.GetCurSel();
	m_maclist.GetLBText( nIndex, str);
	//if(str=="")return ;
	garage.clear();
	if(garage.readdate(atoi(str.GetBuffer(0))))return ;
	btnnum=garage.getrows()*garage.getcols();
	showbutton();
	upinfodate();
}

void CCar_module_dlgDlg::showmaclist()
{
	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("数据库无法连接!");
		return ;
	}

	CString str="select mac from t_garageinfo";

	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		m_maclist.ResetContent();
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		while(column=mysql_fetch_row(res))//获取具体的数据
		{
			if(column)
			{
				m_maclist.AddString(column[0]);
			}
			else
			{
				MessageBox("未找到车库数据");
				break;
			}
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return ;
	}
}
