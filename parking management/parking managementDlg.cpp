// parking managementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "parking management.h"
#include "parking managementDlg.h"
#include "carbarninfo.h"
#include "showmapinfo.h"
#include "ABOUTSOFT.h"
#include "DataStructure.h"
#include "ControlCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int link=0;

extern MYSQL mysql;

extern struct serverset serverinfo;

//////////////////////////////////////////////////////////////////////////
//这个坑不小,改成动态创建就行了
extern CParkingmanagementDlg *maindlg;
//////////////////////////////////////////////////////////////////////////

extern carbarninfo* (carbarn[30]);
/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementDlg dialog

CParkingmanagementDlg::CParkingmanagementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParkingmanagementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParkingmanagementDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon   =AfxGetApp()->LoadIcon(IDI_ICON1);
	link      =0;
	lockcomm  =0;
	indexcomm =0;
	Volume    =0;
	occupy    =0;
	residue   =0;
}

void CParkingmanagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParkingmanagementDlg)
	DDX_Control(pDX, IDC_EDIT6, m_car_id);
	DDX_Control(pDX, IDC_EDIT1, m_car_plate);
	DDX_Control(pDX, IDC_EDIT5, m_datainfo);
	DDX_Control(pDX, IDC_BUTTON4, m_startend);
	DDX_Control(pDX, IDC_EDIT4, m_status);
	DDX_Control(pDX, IDC_EDIT2, m_car_surplus);
	DDX_Control(pDX, IDC_EDIT3, m_car_sum);
	DDX_Control(pDX, IDC_LIST1, m_carbarn_list);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParkingmanagementDlg, CDialog)
	//{{AFX_MSG_MAP(CParkingmanagementDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementDlg message handlers

BOOL CParkingmanagementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_status.SetWindowText("未连接");
	//设置列表主题
	m_carbarn_list.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);

	char titlename[][20]={"编号","车库名","状态","耗时","容量","已存车辆","层数","列数","横轴速度","纵轴速度"};
	for(int i=0;i<10;i++)
	{
		m_carbarn_list.InsertColumn(i,titlename[i],LVCFMT_CENTER, 70,0);
	}

	MYSQL_RES *res;     //查询结果集
	MYSQL_ROW column;   //数据行的列
	
	for(i=0;i<30;i++)
	{
		carbarn[i]=NULL;
	}
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,"select carbarnid from t_garageinfo")==NULL)
	{
		res=mysql_store_result(&mysql);    //保存查询到的数据到result
		while(column=mysql_fetch_row(res)) //获取具体的数据
		{
			int inttmp;
			if(column)
			{
				inttmp=atoi(*column);
				carbarn[inttmp-1]=new carbarninfo;
				carbarn[inttmp-1]->readdate(inttmp);
			}
			else
			{
				MessageBox("未找到车库数据");
				break;
			}
		}
	}
	
	showcarbarnlist();

	SetTimer(1,serverinfo.refreshinterval,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CParkingmanagementDlg::OnPaint() 
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
HCURSOR CParkingmanagementDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CParkingmanagementDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CParkingmanagementDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	for(int i=0;i<30;i++)
	{
		if(carbarn[i])
		{
			delete carbarn[i];
		}
	}
	CDialog::OnCancel();
}

//编辑地图
void CParkingmanagementDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path+="\\map\\map.tmx";
	ShellExecute(NULL,TEXT("OPEN"),path,NULL,NULL,SW_SHOWNORMAL);
}

//////////////////////////////////////////////////////////////////////////
//开启一个线程
struct threadInfo 
{
	UINT nMilliSecond ;
	CProgressCtrl* pctrlProgress ;
}Info;

UINT Threadshowmap(LPVOID lpParam)
{
	showmapinfo* dlg;
	dlg=new showmapinfo;
	dlg->DoModal();
	delete dlg;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
//显示地图
void CParkingmanagementDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CWinThread* pThread ;
	pThread=AfxBeginThread(Threadshowmap,&Info);
	//showmapinfo dlg;
	//dlg.DoModal();
}

void CParkingmanagementDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

//about
void CParkingmanagementDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	ABOUTSOFT dlg;
	dlg.DoModal();
}

void CParkingmanagementDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	if(!link)
	{
		if(m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(FALSE);
		m_Comm.SetCommPort(serverinfo.mscomm); //选择com，可根据具体情况更改
		m_Comm.SetInBufferSize(1024);          //设置输入缓冲区的大小，Bytes
		m_Comm.SetOutBufferSize(1024);         //设置输入缓冲区的大小，Bytes//
		m_Comm.SetSettings(serverinfo.mscommini);      //波特率9600，无校验，8个数据位，1个停止位
		m_Comm.SetInputMode(1);                //1：表示以二进制方式检取数据
		m_Comm.SetRThreshold(1);               //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_Comm.SetInputLen(0);                 //设置当前接收区数据长度为0
		if( !m_Comm.GetPortOpen())
		{
			m_Comm.SetPortOpen(TRUE);          //打开串口
		}
		else
		{
			m_Comm.SetPortOpen(FALSE);
		}
		m_Comm.GetInput();                     //先预读缓冲区以清除残留数据
		//////////////////////////////////////////////////////////////////////////
		m_status.SetWindowText("已连接");
		m_startend.SetWindowText("断开设备");
		link=1;
	}
	else if(link)
	{
		m_Comm.SetPortOpen(FALSE);
		m_status.SetWindowText("已断开");
		m_startend.SetWindowText("连接设备");
		link=0;
	}
}

//显示车库列表
void CParkingmanagementDlg::showcarbarnlist()
{
	m_carbarn_list.DeleteAllItems();
	CString tmpstr;
	Volume =0;
	residue=0;
	occupy =0;

	for(int i=0;i<30;i++)
	{
		if(carbarn[i]!=NULL)
		{
			tmpstr.Format("%d",carbarn[i]->getcarbarnid());
			m_carbarn_list.InsertItem(i,tmpstr);

			tmpstr=(carbarn[i]->getname()).c_str();
			m_carbarn_list.SetItemText(i,1,tmpstr);

			//tmpstr.Format("%d",carbarn[i]->getnowstatus());
			//m_carbarn_list.SetItemText(i,2,tmpstr);

			int index=carbarn[i]->getoldstatus();
			if(index==STATEFREE)tmpstr="空闲";
			else if(index==STATESAVE)tmpstr="存车";
			else if(index==STATEDELETE)tmpstr="取车";
			else if(index==STATESTOP)tmpstr="停止";
			else if(index==STATERSET)tmpstr="复位";
			else tmpstr="离线";
			m_carbarn_list.SetItemText(i,2,tmpstr);

			tmpstr.Format("%d",carbarn[i]->getspendtime());
			m_carbarn_list.SetItemText(i,3,tmpstr);

			tmpstr.Format("%d",carbarn[i]->getsumcar());
			m_carbarn_list.SetItemText(i,4,tmpstr);

			tmpstr.Format("%d",carbarn[i]->getspendcar());
			m_carbarn_list.SetItemText(i,5,tmpstr);

			tmpstr.Format("%d",carbarn[i]->getrows());
			m_carbarn_list.SetItemText(i,6,tmpstr);

			tmpstr.Format("%d",carbarn[i]->getcols());
			m_carbarn_list.SetItemText(i,7,tmpstr);

			tmpstr.Format("%f",carbarn[i]->getspeedrows());
			m_carbarn_list.SetItemText(i,8,tmpstr);

			tmpstr.Format("%f",carbarn[i]->getspeedcols());
			m_carbarn_list.SetItemText(i,9,tmpstr);

			Volume+=carbarn[i]->getsumcar();
			residue+=carbarn[i]->getspendcar();
		}
	}
	occupy=Volume-residue;

	tmpstr.Format("共%4d个车位",Volume);
	m_car_sum.SetWindowText(tmpstr);
	tmpstr.Format("剩余%4d个车位",occupy);
	m_car_surplus.SetWindowText(tmpstr);
}

BEGIN_EVENTSINK_MAP(CParkingmanagementDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CParkingmanagementDlg)
	ON_EVENT(CParkingmanagementDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CParkingmanagementDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	lockcomm=1;
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048];
	
	char recstr[100];
    if(m_Comm.GetCommEvent()==2)
    {
        variant_inp=m_Comm.GetInput();
        safearray_inp=variant_inp;
        len=safearray_inp.GetOneDimSize();
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);
        for(k=0;k<len;k++)
        {
            BYTE bt=*(char*)(rxdata+k);
			recstr[k]=bt;
        }
		recstr[k]='\0';
		
		string asd=carbarn[recstr[0]]->getcommand();

		CString qew;
		qew.Format("send %d:%d:%d:%d:%d\r\nrecv %d:%d:%d:%d:%d",
			asd[0],asd[1],asd[2],asd[3],asd[4],
			recstr[0],recstr[1],recstr[2],recstr[3],recstr[4]);
		
		if(recstr[0]!=asd[4])
		{
			qew+="\r\n数据";
			//MessageBox("收发数据不一致");
			//m_Comm.SetOutput(COleVariant(datastr));//发送数据
		}
		m_datainfo.SetWindowText(qew);
    }
	lockcomm=0;
}

void CParkingmanagementDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		showcarbarnlist();
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

UINT ThreadDevice(LPVOID lpParam)
{
	string tmpstr;
	char datastr[100];
	int j;

	for(;;)
	{
		for(int i=0;i<30&&link;i++)
		{
			if(carbarn[i]!=NULL)
			{
				tmpstr="00000";
				if(carbarn[i]->getnowstatus()==carbarn[i]->getoldstatus())
				{
					tmpstr[0]=i+1;
					tmpstr[1]=GETSTATE;
					tmpstr[4]=(i+1+GETSTATE+'0'+'0')%CHECKMOD;
				}
				else
				{
					if(carbarn[i]->getcommand()=="")
					{
						tmpstr[0]=i+1;
						tmpstr[1]=GETSTATE;
						tmpstr[4]=(i+1+GETSTATE+'0'+'0')%CHECKMOD;
					}
					else
					{
						tmpstr=carbarn[i]->getcommand();
					}
				}
				for(j=0;j<6;j++)
				{
					datastr[j]=tmpstr[j];
				}
				
				maindlg->senddata(datastr);
			}
		}
		if(!link)Sleep(5000);
	}
	return 0;
}

int CParkingmanagementDlg::senddata(char *str)
{
	if(link)
	{
		m_Comm.SetOutput(COleVariant(str));//发送数据
		return 0;
	}
	else return -1;
}
