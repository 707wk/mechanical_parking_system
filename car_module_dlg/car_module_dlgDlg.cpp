// car_module_dlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "car_module_dlg.h"
#include "car_module_dlgDlg.h"
#include "car_module.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
}

void CCar_module_dlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCar_module_dlgDlg)
	DDX_Control(pDX, IDC_EDIT8, m_mac);
	DDX_Control(pDX, IDC_EDIT7, m_cols);
	DDX_Control(pDX, IDC_EDIT6, m_rows);
	DDX_Control(pDX, IDC_EDIT5, m_speedcols);
	DDX_Control(pDX, IDC_EDIT4, m_speedrows);
	DDX_Control(pDX, IDC_EDIT3, m_finish);
	DDX_Control(pDX, IDC_EDIT2, m_sum);
	DDX_Control(pDX, IDC_EDIT1, m_carid);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCar_module_dlgDlg, CDialog)
	//{{AFX_MSG_MAP(CCar_module_dlgDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
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
	garage.readdate();
	//////////////////////////////////////////////////////////////////////////
	//��֪��Ϊʲô,���з���,������ʾ��ȴ����ȷ��
	int cols=garage.getcols();
	int rows=garage.getrows();
	//////////////////////////////////////////////////////////////////////////

    btn = new CButton[cols*rows];  
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON|BS_ICON;  
	int startpoint[2]={220,15};       //��ʼ��
	int gao=50;              //�����
	int kuan=50;             //�����
    for(int i = 0; i < cols*rows; i++){ 	
		int num[2]={50,50};      //����
		CString tmp;
tmp.Format("%d",cols*rows-i);
        btn[i].Create(tmp, dwStyle,CRect(startpoint[0]+i%cols*kuan,startpoint[1]+i/cols*gao,startpoint[0]+i%cols*kuan+num[0],startpoint[1]+i/cols*gao+num[1]),this,buttonID+i);   
        //btn[i].SetFont(GetParent()->GetFont());  
		//btn[i].SetIcon(m_hicnok);
		if(garage.getcond(cols*rows-i)==0)
		{
			//tmp="����";
			btn[i].SetIcon(m_hicnok);
		}
		else if(garage.getcond(cols*rows-i)==1)
		{
			//tmp="ռ��";
			btn[i].SetIcon(m_hicnno);
		}
		else if(garage.getcond(cols*rows-i)==2)
		{
			//tmp="���";
			btn[i].SetIcon(m_hicncar);
		}
		else
		{
			tmp.Format("δ֪���� ��%d��λ:%d",cols*rows-i,garage.getcond(cols*rows-i));
			//MessageBox(tmp);
		}
    } 

	CString str;
	str.Format("%d",garage.getmac());
	m_mac.SetWindowText(str);

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

	//////////////////////////////////////////////////////////////////////////
	//���ô��ڴ�С
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
	garage.savedatetomysql();
	CDialog::OnCancel();
}

//�泵
void CCar_module_dlgDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int index=garage.savecar();
	int sum=garage.getrows()*garage.getcols();
	if(index!=-1)
	{
		btn[sum-index-1].SetIcon(m_hicnno);
	}
	else
	{
		MessageBox("û�п��೵λ");
	}
	//garage.readdate();
}

//ȡ��
void CCar_module_dlgDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}
