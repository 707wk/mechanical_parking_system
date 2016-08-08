
// MFCAppDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "debugmodel.h"
#include "About.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "ioClient.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include "IOCPserver.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

extern DCB dcb;

extern CCarbarnInfo* garage;

extern CWayFinding* mapinfo;

extern struct ioClient* ioClient_list;

extern int* idtoindex_garage;

extern int* idtoindex_ioClient;

extern int maxindex_garage ;

extern int maxindex_ioClient ;

extern int sumgarage ;

extern int sumioClient ;

static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_01,
	ID_INDICATOR_02
};

//Gdiplus::GdiplusStartupInput    m_gdiplusStartupInput;
//ULONG_PTR                       m_gdiplusToken;
//Image*                          m_pImage;                           //图片对象

// CMFCAppDlg 对话框

IMPLEMENT_DYNAMIC(CMFCAppDlg, CDialogEx);

CMFCAppDlg::CMFCAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	serverinfo.sumcar = 0;
	serverinfo.spendcar = 0;
	serverinfo.activeThreadtime = 0;

	serverinfo.runstate = 0;
	//serverinfo.lockflage = 0;
}

CMFCAppDlg::~CMFCAppDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_garage);
	DDX_Control(pDX, IDC_EDIT1, m_sumcar);
	DDX_Control(pDX, IDC_EDIT2, m_freecar);
	DDX_Control(pDX, IDC_EDIT3, m_reservationcar);
	DDX_Control(pDX, IDC_EDIT4, m_Threadinfo);
	DDX_Control(pDX, IDC_LIST3, m_list_ioput);
}

BEGIN_MESSAGE_MAP(CMFCAppDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCAppDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_COMMAND(ID_32774, &CMFCAppDlg::On32774)
	ON_COMMAND(ID_32773, &CMFCAppDlg::On32773)
	ON_COMMAND(ID_32771, &CMFCAppDlg::On32771)
	ON_COMMAND(ID_32772, &CMFCAppDlg::On32772)
	ON_COMMAND(ID_32775, &CMFCAppDlg::On32775)
	ON_MESSAGE(WM_NOTI , &CMFCAppDlg::OnTrayNotify)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR, Image*&pImg)
{
	HINSTANCE hInst = AfxGetResourceHandle();
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), sTR);
	// type
	if (!hRsrc)
		return FALSE;
	// load resource into memory
	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE*lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	if (!lpRsrc)
		return FALSE;
	// Allocate global memory on which to create stream
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE*pmem = (BYTE*)GlobalLock(m_hMem);
	memcpy(pmem, lpRsrc, len);
	IStream*pstm;
	CreateStreamOnHGlobal(m_hMem, FALSE, &pstm);
	// load from stream
	pImg = Gdiplus::Image::FromStream(pstm);
	// free/release stuff
	GlobalUnlock(m_hMem);
	pstm->Release();
	FreeResource(lpRsrc);
	return TRUE;
}

// CMFCAppDlg 消息处理程序

BOOL CMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);隐藏任务栏图标

	/* 托盘图标的初始化工作 ************************************************************************/
	//初始化 m_NotifyIconData 内存空间
	memset(&m_NotifyIconData, 0, sizeof(NOTIFYICONDATA));
	//使托盘中图标对应于本窗体,这样它便可以把托盘图标的事件发送给窗体程序
	m_NotifyIconData.hWnd = GetSafeHwnd();
	ASSERT(m_NotifyIconData.hWnd != NULL);
	//定托盘图标产生事件时候发出的事件
	m_NotifyIconData.uCallbackMessage = WM_NOTI;
	//填充结构体的大小
	m_NotifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	//加载托盘图标(这里以默认的资源图标)
	m_NotifyIconData.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//设置鼠标移动到托盘图标时候的提示文字
	memcpy(m_NotifyIconData.szTip, L"堆垛式立体车库管理系统", sizeof(L"堆垛式立体车库管理系统"));
	//设置托盘图标的属性
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//设置托盘图标的图标资源 ID
	m_NotifyIconData.uID = IDR_MAINFRAME;

	/* 显示托盘图标 *********************************************************************************/
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);

	//初始化GDI+.  
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	//加载文件  
	//CT2CW strFileName( _T("I:\\编程练习\\CommonFiles\\Test02.png") );  
	//m_pImage = new Image( _T("I:\\编程练习\\CommonFiles\\Test02.png") );  
	//m_pImage=Image::FromFile(_T("I:\\编程练习\\CommonFiles\\Test02.png"));  
	m_pImage = Image::FromFile(_T("res\\bg.png"));
	//ImageFromIDResource(IDB_PNG_BG, _T("png"), (Image*&)m_pImage);

	//错误判断  
	if ((m_pImage == NULL) || (m_pImage->GetLastStatus() != Ok))
	{
		if (m_pImage)
		{
			delete m_pImage;
			m_pImage = NULL;
		}
		exit(1);
		//return FALSE;
	}

//	MYSQL_RES *res;                    //查询结果集
//	MYSQL_ROW column;                  //数据行的列

	//初始化曲线控件
	CRect rt;
	GetDlgItem(IDC_CUSTOM1)->GetWindowRect(rt);
	ScreenToClient(rt);
	m_Osc.Create(WS_VISIBLE | WS_CHILD, rt, this);
	m_Osc.SetRange(0.0, serverinfo.Threadsum*100, 1);
	m_Osc.SetYUnits(_T(""));
	m_Osc.SetXUnits(_T("服务使用率"));
	m_Osc.SetBackgroundColor(RGB(0, 0, 64));
	m_Osc.SetGridColor(RGB(192, 192, 255));
	m_Osc.SetPlotColor(RGB(255, 255, 0));
	m_Osc.AppendPoint(0.0);

	//设置列表主题
	m_list_garage.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
		| LVS_EX_FULLROWSELECT		// 允许正航选中
		| LVS_EX_GRIDLINES			// 画出网格线
		);

	m_list_garage.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40, 0);
	m_list_garage.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(3, _T("命令耗时"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(4, _T("容量"), LVCFMT_CENTER, 50, 0);
	m_list_garage.InsertColumn(5, _T("已存"), LVCFMT_CENTER, 50, 0);

	//设置列表主题
	m_list_ioput.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
		| LVS_EX_FULLROWSELECT		// 允许正航选中
		| LVS_EX_GRIDLINES			// 画出网格线
		);

	m_list_ioput.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 40, 0);
	//m_list_ioput.InsertColumn(1, _T("备注"), LVCFMT_CENTER, 87, 0);
	m_list_ioput.InsertColumn(1, _T("类型"), LVCFMT_CENTER, 70, 0);
	m_list_ioput.InsertColumn(2, _T("状态"), LVCFMT_CENTER, 70, 0);//*/

	init_list();

	thread01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPoll, NULL, 0, NULL);
	thread02 =CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)iocpstartserver, NULL, 0, NULL);

	serverinfo.runstate = 1;

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_GREEN);
	//m_stateico.SetIcon(hIcon);

	SetTimer(1, 1000, NULL);
	SetTimer(2, 1000, NULL);
	SetTimer(3, 60 * 1000, NULL);
	SetTimer(4, 100, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCAppDlg::OnPaint()
{
	Graphics graphics(GetDC()->GetSafeHdc());
	graphics.DrawImage(m_pImage, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
	//printf("%d %d\n", m_pImage->GetWidth(), m_pImage->GetHeight());
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
HCURSOR CMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMFCAppDlg::OnClose()
{
//	AfxMessageBox(_T("1"));
//	if (CanExit())
//		CDialogEx::OnClose();
}

void CMFCAppDlg::OnOK()
{
//	AfxMessageBox(_T("2"));
//	if (CanExit())
//		CDialogEx::OnOK();
}

void CMFCAppDlg::OnCancel()
{
//	AfxMessageBox(_T("3"));
//	if (CanExit())
//		CDialogEx::OnCancel();
}

BOOL CMFCAppDlg::CanExit()
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

void CMFCAppDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

void CMFCAppDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CMFCAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MYSQL_RES *res;                    //查询结果集
//	MYSQL_ROW column;                  //数据行的列

	switch (nIDEvent)
	{
	case 1:
		if (serverinfo.runstate)
		{
			for (int i = 0; i<sumgarage; i++)
				garage[i].accspendtime();
			for (int i = 0; i < sumioClient; i++)
				ioClient_list[i].spendtime++;
			//update_list();
		}
		break;
	case 2:
		if (serverinfo.runstate)
		{
			m_Osc.AppendPoint(serverinfo.activeThreadtime/10.0);
			//printf("[%ld]", serverinfo.activeThread);
			serverinfo.activeThreadtime = 0;
		}
		break;
	case 3:
		mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

		if (mysql_query(&serverinfo.mysql, "delete from t_reservation where now()>endtime") != NULL)
		{
			AfxMessageBox(_T("time:32数据库连接失败"));
			exit(1);
		}
		//else AfxMessageBox(_T("delete successful"));

		if (mysql_query(&serverinfo.mysql, "select plate from t_reservation") == NULL)
		{
			res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
			serverinfo.reservation = (int)mysql_num_rows(res);
			//printf("[reservation=%d]", serverinfo.reservation);
		}
		else
		{
			AfxMessageBox(_T("time:31数据库连接失败"));
			exit(1);
		}

		break;
	case 4:
		update_list();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCAppDlg::init_list()
{
	CString tmp;

	m_list_garage.DeleteAllItems();
	m_list_ioput.DeleteAllItems();

	for (int index = 0; index<sumgarage; index++)
	{
		tmp.Format(_T("%d"), garage[index].getcarbarnid());
		m_list_garage.InsertItem(index, tmp);
		tmp = garage[index].getname().c_str();
		m_list_garage.SetItemText(index, 1, tmp);
		m_list_garage.SetItemText(index, 2, _T("未知"));

		m_list_garage.SetItemText(index, 3, _T("00:00:00"));

		tmp.Format(_T("%d"), garage[index].getsumcar());
		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[index].getspendcar());
		m_list_garage.SetItemText(index, 5, tmp);

		serverinfo.sumcar += garage[index].getsumcar();
		serverinfo.spendcar += garage[index].getspendcar();
	}

	for (int index = 0; index<sumioClient; index++)
	{
		tmp.Format(_T("%d"), ioClient_list[index].id);
		m_list_ioput.InsertItem(index, tmp);
		switch (ioClient_list[index].type)
		{
		case 1:
			m_list_ioput.SetItemText(index, 1, _T("入口"));
			break;
		case 2:
			m_list_ioput.SetItemText(index, 1, _T("出口"));
			break;
		case 3:
			m_list_ioput.SetItemText(index, 1, _T("出入口"));
			break;
		default:
			break;
		}

		m_list_ioput.SetItemText(index, 2, _T("未知"));
	}//*/

	tmp.Format(_T("%d"), serverinfo.sumcar);
	m_sumcar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation);
	m_freecar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.reservation);
	m_reservationcar.SetWindowText(tmp);

	tmp.Format(_T("%d/%d"), serverinfo.Threadwork,serverinfo.Threadsum);
	m_Threadinfo.SetWindowText(tmp);
}

void CMFCAppDlg::update_list()
{
	static int gindex = 0;
	static int cindex = 0;
//	int errorindex = 0;
//	int overtime = 0;
	CString tmp;

	//m_list_garage.DeleteAllItems();
	//m_list_error.DeleteAllItems();

//	serverinfo.sumcar = 0;
//	serverinfo.spendcar = 0;

	//////////////////////////////////////////////////////////////////////////
	//根据车库模块数量以及查询间隔确定超时时间
//	overtime = ((maxindex_garage + 1)*serverinfo.intervaltime) / 1000;
//	if (overtime<1)overtime = 1;
	//////////////////////////////////////////////////////////////////////////

	//for (;;)
	{
		switch (garage[gindex].getnowstatus())
		{
		case STATEFREE:
			m_list_garage.SetItemText(gindex, 2, _T("空闲"));
			break;
		case STATESAVE:
			m_list_garage.SetItemText(gindex, 2, _T("存车"));
			break;
		case STATEDELETE:
			m_list_garage.SetItemText(gindex, 2, _T("取车"));
			break;
		case STATESTOP:
			m_list_garage.SetItemText(gindex, 2, _T("停止"));
			break;
		case STATERSET:
			m_list_garage.SetItemText(gindex, 2, _T("复位"));
			break;
		case ACCEPTED:
			m_list_garage.SetItemText(gindex, 2, _T("已接收"));
			break;
		case BUSY:
			m_list_garage.SetItemText(gindex, 2, _T("运行中"));
			break;
		case OFFLINE:
			m_list_garage.SetItemText(gindex, 2, _T("离线"));
			break;
		default:
			m_list_garage.SetItemText(gindex, 2, _T("未知"));
		}

		tmp.Format(_T("%02d:%02d:%02d"),
			garage[gindex].getspendtime() / 3600,
			garage[gindex].getspendtime() / 60 % 60,
			garage[gindex].getspendtime() % 60);
		m_list_garage.SetItemText(gindex, 3, tmp);

//		tmp.Format(_T("%d"), garage[i].getsumcar());
//		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[gindex].getspendcar());
		m_list_garage.SetItemText(gindex, 5, tmp);

		gindex = (gindex+1) % sumgarage;
	}

	//for (index = 0; index<sumioClient; index++)
	{
//		printf("%d ", ioClient_list[index].spendtime);
		if (ioClient_list[cindex].spendtime > 10)
		{
			m_list_ioput.SetItemText(cindex, 2, _T("离线"));
		}
		else
		{
			m_list_ioput.SetItemText(cindex, 2, _T("在线"));
		}
		cindex = (cindex+1) % sumioClient;
	}//*/
//	printf("\n");

	tmp.Format(_T("%d"), serverinfo.sumcar);
	m_sumcar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation);
	m_freecar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.reservation);
	m_reservationcar.SetWindowText(tmp);

	tmp.Format(_T("%d/%d"), serverinfo.Threadwork, serverinfo.Threadsum);
	m_Threadinfo.SetWindowText(tmp);
}

void CMFCAppDlg::On32774()
{
	// TODO:  在此添加命令处理程序代码
	CAbout dlg;
	dlg.DoModal();
	//ShellExecute(NULL, _T("open"), _T("http://gxy.hunnu.edu.cn/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32773()
{
	// TODO:  Web端
	ShellExecute(NULL, _T("open"), _T("http://127.0.0.1/manage/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32771()
{
	// TODO:  在此添加命令处理程序代码
	if (CanExit())
		CDialog::OnCancel();
}

void CMFCAppDlg::On32772()
{
	// TODO:  在此添加命令处理程序代码
	serverinfo.runstate = 0;

	debugmodel dlg;
	dlg.DoModal();

	serverinfo.runstate = 1;
}

void CMFCAppDlg::On32775()
{
	// TODO: 设置
}


void CMFCAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
/*	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);//*/
	//RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
	}

	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc);
	//获得窗口矩形
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 15, 15);
	//根据窗口矩形创建一个圆角矩形最后两个是形成圆角的大小
	SetWindowRgn(rgn, TRUE);//*/
}


void CMFCAppDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
}


BOOL CMFCAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
	{
		pMsg->wParam = VK_RETURN;
		//将ESC键的消息替换为回车键的消息，这样，按ESC的时候
		//也会去调用OnOK函数，而OnOK什么也不做，这样ESC也被屏蔽
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

LRESULT CMFCAppDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	static int flage = 1;
	UINT uMsg = (UINT)lParam;

	switch (uMsg)
	{
	case WM_RBUTTONUP:
		{
		//右键处理
		CMenu menuTray;
		CPoint point;
		int id;
		GetCursorPos(&point);

		menuTray.LoadMenu(IDR_MENU2);
		id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		switch (id)
		{
		case ID_TRAY_EXIT:
			if (CanExit())
				CDialog::OnCancel();
			break;
		default:
			break;
		}
		break;
		}
	case WM_LBUTTONDBLCLK:
		if (flage)
		{
			ShowWindow(SW_HIDE);
			flage = 0;
		}
		else
		{
			SetForegroundWindow();
			ShowWindow(SW_SHOWNORMAL);
			flage = 1;
		}
		break;
	default:
		break;
	}
	return 0;
}