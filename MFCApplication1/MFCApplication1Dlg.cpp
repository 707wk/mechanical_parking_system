
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "ControlCode.h"
#include "DataStructure.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct serverset serverinfo;

char data[6] = "12345";
int lockflage = 0;
int link = 0;

CString history;

//读取配置文件
int readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("未找到配置文件!"));
		exit(1);
	}

	fscanf(fp, "server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d\ncost=%lf\nmscomm=%d\nmscommini=%s\nrefreshinterval=%d",
		serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database,
		&serverinfo.port, &serverinfo.cost, &serverinfo.mscomm, serverinfo.mscommini, &serverinfo.refreshinterval);

	return 0;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框


IMPLEMENT_DYNAMIC(CMFCApplication1Dlg, CDialogEx);

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	DDX_Control(pDX, IDC_EDIT1, m_parkid);
	DDX_Control(pDX, IDC_EDIT2, m_row);
	DDX_Control(pDX, IDC_EDIT3, m_col);
	DDX_Control(pDX, IDC_EDIT4, m_info);
	DDX_Control(pDX, IDC_BUTTON5, m_startend);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::savecar)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::delcar)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::stop)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::reset)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::start)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	readserverset();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMFCApplication1Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFCApplication1Dlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFCApplication1Dlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFCApplication1Dlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::savecar()
{
	// TODO:  在此添加控件通知处理程序代码
	strcpy(data, "12345");
	CString tmp;
	m_parkid.GetWindowTextW(tmp);

	data[0] = _ttoi(tmp.GetBuffer(0));
	data[1] = SAVECAR;
	m_row.GetWindowTextW(tmp);
	data[2] = _ttoi(tmp.GetBuffer(0));
	m_col.GetWindowTextW(tmp);
	data[3] = _ttoi(tmp.GetBuffer(0));

	int checknum = 0;
	for (int i = 0; i<4; i++)
	{
		checknum += data[i];
	}
	data[4] = checknum%CHECKMOD;

	variant_t a;
	a.SetString(data);
	m_Comm.put_Output(a);//发送数据
}


void CMFCApplication1Dlg::delcar()
{
	// TODO:  在此添加控件通知处理程序代码
	strcpy(data, "12345");
	CString tmp;
	m_parkid.GetWindowTextW(tmp);

	data[0] = _ttoi(tmp.GetBuffer(0));
	data[1] = DELETECAR;
	m_row.GetWindowTextW(tmp);
	data[2] = _ttoi(tmp.GetBuffer(0));
	m_col.GetWindowTextW(tmp);
	data[3] = _ttoi(tmp.GetBuffer(0));

	int checknum = 0;
	for (int i = 0; i<4; i++)
	{
		checknum += data[i];
	}
	data[4] = checknum%CHECKMOD;

	variant_t a;
	a.SetString(data);
	m_Comm.put_Output(a);//发送数据
}


void CMFCApplication1Dlg::stop()
{
	// TODO:  在此添加控件通知处理程序代码
	strcpy(data, "10000");
	CString tmp;
	m_parkid.GetWindowTextW(tmp);

	data[0] = _ttoi(tmp.GetBuffer(0));
	data[1] = STOP;

	int checknum = 0;
	for (int i = 0; i<4; i++)
	{
		checknum += data[i];
	}
	data[4] = checknum%CHECKMOD;

	variant_t a;
	a.SetString(data);
	m_Comm.put_Output(a);//发送数据
}


void CMFCApplication1Dlg::reset()
{
	// TODO:  在此添加控件通知处理程序代码
	strcpy(data, "12345");
	CString tmp;
	m_parkid.GetWindowTextW(tmp);

	data[0] = _ttoi(tmp.GetBuffer(0));
	data[1] = RESET;

	int checknum = 0;
	for (int i = 0; i<4; i++)
	{
		checknum += data[i];
	}
	data[4] = checknum%CHECKMOD;

	variant_t a;
	a.SetString(data);
	m_Comm.put_Output(a);//发送数据
}


void CMFCApplication1Dlg::start()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!link)
	{
		if (m_Comm.get_PortOpen())
			m_Comm.put_PortOpen(FALSE);
		m_Comm.put_CommPort(serverinfo.mscomm); //选择com，可根据具体情况更改
		m_Comm.put_InBufferSize(1024);          //设置输入缓冲区的大小，Bytes
		m_Comm.put_OutBufferSize(1024);         //设置输入缓冲区的大小，Bytes//
		CString tmp;
		tmp = serverinfo.mscommini;
		m_Comm.put_Settings(tmp);      //波特率9600，无校验，8个数据位，1个停止位
		m_Comm.put_InputMode(1);                //1：表示以二进制方式检取数据
		m_Comm.put_RThreshold(1);               //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_Comm.put_InputLen(0);                 //设置当前接收区数据长度为0
		if (!m_Comm.get_PortOpen())
		{
			m_Comm.put_PortOpen(TRUE);          //打开串口
		}
		else
		{
			m_Comm.put_PortOpen(FALSE);
		}
		m_Comm.get_Input();                     //先预读缓冲区以清除残留数据
		//m_Comm.SetOutput(COleVariant("ok")); //发送数据
		//////////////////////////////////////////////////////////////////////////
		m_info.SetWindowText(_T(""));
		m_startend.SetWindowText(_T("断开设备"));
		link = 1;
	}
	else if (link)
	{
		m_Comm.put_PortOpen(FALSE);
		m_startend.SetWindowText(_T("连接设备"));
		link = 0;
	}
}


BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMFCApplication1Dlg::OnCommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
	lockflage = 1;
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048];

	char recstr[100];
	if (m_Comm.get_CommEvent() == 2)
	{
		variant_inp = m_Comm.get_Input();
		safearray_inp = variant_inp;
		len = safearray_inp.GetOneDimSize();
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k<len; k++)
		{
			BYTE bt = *(char*)(rxdata + k);
			recstr[k] = bt;
		}
		recstr[k] = '\0';

		CString qew;
		qew.Format(_T("send %d:%d:%d:%d:%d\r\nrecv %d:%d:%d:%d:%d\r\n"), data[0], data[1], data[2], data[3], data[4],
			recstr[0], recstr[1], recstr[2], recstr[3], recstr[4]);
		//m_entry.SetWindowText(qew);

		if (recstr[0] != data[4])
		{
			qew += "no\r\n";
		}
		history = qew+history;
		m_info.SetWindowText(history);
	}
	lockflage = 0;
}
