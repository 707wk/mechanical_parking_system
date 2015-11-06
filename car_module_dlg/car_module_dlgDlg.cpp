// car_module_dlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "car_module_dlg.h"
#include "car_module_dlgDlg.h"
#include "about.h"
#include "DataStructure.h"
#include "car_module.h"
#include "management.h"
#include "md5.h"
#include "ControlCode.h"

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
	m_hIcon  =AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hicnok =AfxGetApp()->LoadIcon(IDI_ICON3);
	m_hicnno =AfxGetApp()->LoadIcon(IDI_ICON2);
	m_hicncar=AfxGetApp()->LoadIcon(IDI_ICON1);
	m_online =AfxGetApp()->LoadIcon(IDI_ICON4);
	m_offline=AfxGetApp()->LoadIcon(IDI_ICON5);
	m_stop=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON6),IMAGE_ICON,72,72,LR_DEFAULTCOLOR);
	m_reset=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON7),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	btnnum=0;
	btn=NULL;
	lockflage=0;
	//////////////////////////////////////////////////////////////////////////
	//������,����һ����û����
	garage=new car_module;
	//////////////////////////////////////////////////////////////////////////
}

void CCar_module_dlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCar_module_dlgDlg)
	DDX_Control(pDX, IDC_BUTTON6, m_startend);
	DDX_Control(pDX, IDC_BUTTON8, m_resetbut);
	DDX_Control(pDX, IDC_BUTTON7, m_stopbut);
	DDX_Control(pDX, IDC_EDIT8, m_port);
	DDX_Control(pDX, IDC_EDIT1, m_statustext);
	DDX_Control(pDX, IDC_status, m_status);
	DDX_Control(pDX, IDC_COMBO2, m_platelist);
	DDX_Control(pDX, IDC_EDIT9, m_entry);
	DDX_Control(pDX, IDC_COMBO1, m_namelist);
	DDX_Control(pDX, IDC_EDIT7, m_cols);
	DDX_Control(pDX, IDC_EDIT6, m_rows);
	DDX_Control(pDX, IDC_EDIT5, m_speedcols);
	DDX_Control(pDX, IDC_EDIT4, m_speedrows);
	DDX_Control(pDX, IDC_EDIT3, m_finish);
	DDX_Control(pDX, IDC_EDIT2, m_sum);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
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
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_COMMAND(ID_MENUITEM32772, Onexit)
	ON_COMMAND(ID_MENUITEM32773, Onabout)
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
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
	m_stopbut.SetIcon(m_stop);
	m_resetbut.SetIcon(m_reset);
	m_entry.SetWindowText("�豸δ����");

	ShowWindow(SW_MAXIMIZE);

	shownamelist();
	
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

void CCar_module_dlgDlg::Onexit() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

void CCar_module_dlgDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//////////////////////////////////////////////////////////////////////////
	//�رմ���
	if(m_Comm.GetPortOpen())
		m_Comm.SetPortOpen(FALSE);
	//////////////////////////////////////////////////////////////////////////
	delete garage;
	CDialog::OnCancel();
}

//�泵
void CCar_module_dlgDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nIndex = m_namelist.GetCurSel();
	m_namelist.GetLBText( nIndex, str);
	if(str=="")return ;

	CString id;
	m_platelist.GetWindowText(id);
	if(id=="")return ;

	management mana;
	mana.setfindname(str.GetBuffer(0));

	int index=mana.savecar(id.GetBuffer(0));

	int sum=garage->getrows()*garage->getcols();
	if(index!=-1)
	{
		//////////////////////////////////////////////////////////////////////////
		//�±�����Ų���Ӧ
		btn[sum-index].SetIcon(m_hicnno);
		//////////////////////////////////////////////////////////////////////////
		//if(0)	
		strcpy(datastr,"12345");
		datastr[0]=SAVECAR;
		datastr[1]=garage->getcompotr();
		datastr[2]=garage->getrows(index);
		datastr[3]=garage->getcols(index);

		int checknum=0;
		for(int i=0;i<4;i++)
		{
			checknum+=datastr[i];
		}
		datastr[4]=checknum%CHECKMOD;
		
		m_Comm.SetOutput(COleVariant(datastr));//��������

	}
	else
	{
		MessageBox("û�п��೵λ:1");
	}

	upinfodate();
}

//ȡ��
void CCar_module_dlgDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int nIndex = m_namelist.GetCurSel();
	m_namelist.GetLBText( nIndex, str);
	if(str=="")return ;
	
	CString id;
	m_platelist.GetWindowText(id);
	if(id=="")return ;
	
	management mana;
	mana.setfindname(str.GetBuffer(0));
	
	int index=mana.deletecar(id.GetBuffer(0));

	int sum=garage->getrows()*garage->getcols();

	if(str.GetBuffer(0)==mana.getname())
	if(index!=-1)
	{
		//////////////////////////////////////////////////////////////////////////
		//�±�����Ų���Ӧ
		btn[sum-index].SetIcon(m_hicnok);
		//////////////////////////////////////////////////////////////////////////
		//if(0)	
		strcpy(datastr,"12345");
		datastr[0]=DELETECAR;
		datastr[1]=garage->getcompotr();
		datastr[2]=garage->getrows(index);
		datastr[3]=garage->getcols(index);

		int checknum=0;
		for(int i=0;i<4;i++)
		{
			checknum+=datastr[i];
		}
		datastr[4]=checknum%CHECKMOD;
		
		m_Comm.SetOutput(COleVariant(datastr));//��������
	}
	else
	{
		MessageBox("δ�ҵ�����");
	}

	upinfodate();
}

//ˢ����Ϣ
void CCar_module_dlgDlg::upinfodate()
{
	CString str;
	
	str.Format("%d",garage->getsumcar());
	m_sum.SetWindowText(str);
	
	str.Format("%d",garage->getspendcar());
	m_finish.SetWindowText(str);

	str.Format("%d",garage->getcompotr());
	m_port.SetWindowText(str);
	
	str.Format("%f",garage->getspeedrows());
	m_speedrows.SetWindowText(str);
	
	str.Format("%f",garage->getspeedcols());
	m_speedcols.SetWindowText(str);
	
	str.Format("%d",garage->getrows());
	m_rows.SetWindowText(str);
	
	str.Format("%d",garage->getcols());
	m_cols.SetWindowText(str);

	showplatelist();
}

//ˢ���б�
void CCar_module_dlgDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	shownamelist();
}

//����
void CCar_module_dlgDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	hidebutton();

	CString str;
	m_namelist.GetWindowText(str);
	if(str=="")return ;

	garage->setname(str.GetBuffer(0));

	m_rows.GetWindowText(str);
	garage->setrows(atoi(str.GetBuffer(0)));

	m_port.GetWindowText(str);
	garage->setcompotr(atoi(str.GetBuffer(0)));

	m_cols.GetWindowText(str);
	garage->setcols(atoi(str.GetBuffer(0)));
	
	m_speedrows.GetWindowText(str);
	garage->setspeedrows(atof(str.GetBuffer(0)));

	m_speedcols.GetWindowText(str);
	garage->setspeedcols(atof(str.GetBuffer(0)));

	garage->newgarage();

	m_entry.GetWindowText(str);
	string tmpstr=str.GetBuffer(0);
	stringstream stream;
	stream<<tmpstr;
	for(int index;stream>>index;)
	{
		garage->setentry(index);
	}

	shownamelist();
	btnnum=0;
}

void CCar_module_dlgDlg::showbutton()
{
	//////////////////////////////////////////////////////////////////////////
	//��֪��Ϊʲô,���з���,������ʾ��ȴ����ȷ��
	int cols=garage->getcols();
	int rows=garage->getrows();
	//////////////////////////////////////////////////////////////////////////

    btn = new CButton[cols*rows];  
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON|BS_ICON;//|WS_DISABLED;  
	int startpoint[2]={380,15};           //��ʼ��
	int gao=50;                           //�����
	int kuan=50;                          //�����
	int num[2]={50,50};                   //����
    for(int i = 0; i < cols*rows; i++){
		CString tmp;
		tmp.Format("%d ",cols*rows-i);

        btn[i].Create(tmp, dwStyle,CRect(startpoint[0]+i%cols*kuan,startpoint[1]+i/cols*gao,startpoint[0]+i%cols*kuan+num[0],startpoint[1]+i/cols*gao+num[1]),this,buttonID+i);   

		//////////////////////////////////////////////////////////////////////////
		//���겻һ��,������һ����λ
		int index=garage->getcond(cols*rows-i);
		if(index==0)
		{
			//tmp="����";
			btn[i].SetIcon(m_hicnok);
		}
		else if(index==1)
		{
			//tmp="ռ��";
			btn[i].SetIcon(m_hicnno);
		}
		else if(index==2)
		{
			//tmp="���";
			btn[i].SetIcon(m_hicncar);
		}
		else
		{
			tmp.Format("δ֪���� ��%d��λ:%d",cols*rows-i,index);
			MessageBox(tmp);
		}
		//////////////////////////////////////////////////////////////////////////
    } 
	
	upinfodate();
}

void CCar_module_dlgDlg::hidebutton()
{
	if(btn==NULL)
	{
		return ;
	}
	//////////////////////////////////////////////////////////////////////////
	//��֪��Ϊʲô,���з���,������ʾ��ȴ����ȷ��
	int cols=garage->getcols();
	int rows=garage->getrows();
	//////////////////////////////////////////////////////////////////////////

	int startpoint[2]={220,15};           //��ʼ��
	int gao=50;                           //�����
	int kuan=50;                          //�����
	int num[2]={50,50};                   //����

    for(int i = 0; i < btnnum; i++){
			btn[i].DestroyWindow();	
			delete btn[i];
    }
}

void CCar_module_dlgDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	delete garage;
	garage=new car_module;
	
	hidebutton();
	CString str;
	int nIndex = m_namelist.GetCurSel();
	m_namelist.GetLBText( nIndex, str);
	
	if(garage->readdate(str.GetBuffer(0)))return ;
	btnnum=garage->getrows()*garage->getcols();

	if(garage->getstatus())
	{
		m_status.SetIcon(m_online);
		m_statustext.SetWindowText("����");
	}
	else	
	{
		m_status.SetIcon(m_offline);
		m_statustext.SetWindowText("����");
	}

	showplatelist();
	showbutton();
	upinfodate();
}

void CCar_module_dlgDlg::shownamelist()
{
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("1���ݿ��޷�����!");
		return ;
	}

	CString str="select name from t_garageinfo";

	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		m_namelist.ResetContent();
		res=mysql_store_result(&mysql);    //�����ѯ�������ݵ�result
		while(column=mysql_fetch_row(res)) //��ȡ���������
		{
			if(column)
			{
				m_namelist.AddString(column[0]);
			}
			else
			{
				MessageBox("δ�ҵ���������");
				break;
			}
		}
	}
	else
	{
		AfxMessageBox("2���ݿ�����ʧ��");
	}

	mysql_close(&mysql);
}

void CCar_module_dlgDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_namelist.GetWindowText(str);
	if(str=="")return ;

	garage->readdate(str.GetBuffer(0));

	garage->deletedate();
	hidebutton();
	
	shownamelist();
	btnnum=0;
}


void CCar_module_dlgDlg::showplatelist()
{
	MYSQL_RES *res;     //��ѯ�����
	MYSQL_ROW column;   //�����е���
	MYSQL mysql;
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		MessageBox("���ݿ��޷�����!");
		return ;
	}
	
	CString tmp;
	int nIndex = m_namelist.GetCurSel();
	m_namelist.GetLBText( nIndex, tmp);

	CString str;
	str.Format("select plate from t_carinfo where name='%s'",tmp.GetBuffer(0));
	
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		m_platelist.ResetContent();
		res=mysql_store_result(&mysql);    //�����ѯ�������ݵ�result
		while(column=mysql_fetch_row(res)) //��ȡ���������
		{
			if(column)
			{
				m_platelist.AddString(column[0]);
			}
			else
			{
				MessageBox("δ�ҵ���������");
				break;
			}
		}
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��");
	}
	
	mysql_close(&mysql);
}


void CCar_module_dlgDlg::Onabout() 
{
	// TODO: Add your command handler code here
	about dlg;
	dlg.DoModal();
}

BEGIN_EVENTSINK_MAP(CCar_module_dlgDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CCar_module_dlgDlg)
	ON_EVENT(CCar_module_dlgDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCar_module_dlgDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	lockflage=1;
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
		
		CString qew;
		qew.Format("send %d:%d:%d:%d:%d\r\nrecv %d:%d:%d:%d:%d",datastr[0],datastr[1],datastr[2],datastr[3],datastr[4],
			recstr[0],recstr[1],recstr[2],recstr[3],recstr[4]);
		m_entry.SetWindowText(qew);

		if(strcmp(recstr,datastr)!=0)
		{
			MessageBox("�շ����ݲ�һ��");
			//m_Comm.SetOutput(COleVariant(datastr));//��������
		}
    }
	lockflage=0;
}

void CCar_module_dlgDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	ShellExecute(NULL,TEXT("OPEN"),"map.xls",NULL,NULL,SW_SHOWNORMAL);
}

void CCar_module_dlgDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	static int link=0;
	if(!link)
	{
		if(m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(FALSE);
	
		m_Comm.SetCommPort(serverinfo.mscomm); //ѡ��com1���ɸ��ݾ����������
		m_Comm.SetInBufferSize(1024);          //�������뻺�����Ĵ�С��Bytes
		m_Comm.SetOutBufferSize(1024);         //�������뻺�����Ĵ�С��Bytes//
		m_Comm.SetSettings("9600,n,8,1");      //������9600����У�飬8������λ��1��ֹͣλ
		m_Comm.SetInputMode(1);                //1����ʾ�Զ����Ʒ�ʽ��ȡ����
		m_Comm.SetRThreshold(1);               //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
		m_Comm.SetInputLen(0);                 //���õ�ǰ���������ݳ���Ϊ0
		if( !m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(TRUE);          //�򿪴���
		else
			m_Comm.SetPortOpen(FALSE);
		m_Comm.GetInput();                     //��Ԥ���������������������
		//m_Comm.SetOutput(COleVariant("ok")); //��������
		//////////////////////////////////////////////////////////////////////////

		m_startend.SetWindowText("�Ͽ��豸");
		link=1;
	}
	else if(link)
	{
		m_Comm.SetPortOpen(FALSE);
		m_startend.SetWindowText("�����豸");
		link=0;
	}
}

//����ֹͣ
void CCar_module_dlgDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	strcpy(datastr,"10000");
	datastr[0]=STOP;
	
	int checknum=0;
	for(int i=0;i<4;i++)
	{
		checknum+=datastr[i];
	}
	datastr[4]=checknum%CHECKMOD;
	
	m_Comm.SetOutput(COleVariant(datastr));//��������
}

//��λ
void CCar_module_dlgDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	strcpy(datastr,"10000");
	datastr[0]=RESET;
	
	int checknum=0;
	for(int i=0;i<4;i++)
	{
		checknum+=datastr[i];
	}
	datastr[4]=checknum%CHECKMOD;
	
	m_Comm.SetOutput(COleVariant(datastr));//��������
}
