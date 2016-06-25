
// MFCAppclientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCAppclient.h"
#include "MFCAppclientDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#include "md5.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include <stdio.h>
#include <objbase.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma warning(disable: 4996)  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern struct serverset serverinfo;
// CMFCAppclientDlg 对话框


IMPLEMENT_DYNAMIC(CMFCAppclientDlg, CDialogEx);

CMFCAppclientDlg::CMFCAppclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCAppclientDlg::~CMFCAppclientDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCAppclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, strplateEDIT);
	DDX_Control(pDX, IDC_EDIT2, stateEDIT);
	DDX_Control(pDX, IDC_EDIT3, ioputIdEDIT);
}

BEGIN_MESSAGE_MAP(CMFCAppclientDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCAppclientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCAppclientDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCAppclientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCAppclientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCAppclientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCAppclientDlg 消息处理程序

BOOL CMFCAppclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPoll, NULL, 0, NULL);

	SetTimer(1, 1000, NULL);
	SetTimer(2, serverinfo.intervaltime, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCAppclientDlg::OnPaint()
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
HCURSOR CMFCAppclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMFCAppclientDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFCAppclientDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFCAppclientDlg::OnCancel()
{
	if (CanExit())
	{
		WSACleanup();
		CDialogEx::OnCancel();
	}
}

BOOL CMFCAppclientDlg::CanExit()
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



void CMFCAppclientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CMFCAppclientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMFCAppclientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		serverinfo.overtime++;
		if (serverinfo.overtime > serverinfo.maxovertime)
		{
			stateEDIT.SetWindowTextW(_T("断开"));
		}
		else
		{
			stateEDIT.SetWindowTextW(_T("正常"));
		}
		break;
	case 2:
		struct comNode tmp;
		tmp.IOCTL = PANTBAG;
		sprintf_s(tmp.strplate, COMLEN, "%d", serverinfo.ioId);
		tmp.ioputid = 0;
		serverinfo.command.push(tmp);
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMFCAppclientDlg::OnBnClickedButton1()
{
	// TODO: 入口存车
	DWORD dwNum;
	CString tmp;

	char id[COMLEN];
	char plate[COMLEN];

	ioputIdEDIT.GetWindowTextW(tmp);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, NULL, 0, NULL, FALSE);
	memset(id, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, id, dwNum, NULL, FALSE);

	strplateEDIT.GetWindowTextW(tmp);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, NULL, 0, NULL, FALSE);
	memset(plate, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, plate, dwNum, NULL, FALSE);

	struct comNode qwe;
	qwe.IOCTL = INPUTSAVE;
	sprintf_s(qwe.strplate, COMLEN, "%s", plate);
	qwe.ioputid = atoi(id);
	serverinfo.command.push(qwe);
}


void CMFCAppclientDlg::OnBnClickedButton2()
{
	// TODO: 车库取车
	DWORD dwNum;
	CString tmp;

	char plate[COMLEN];

	strplateEDIT.GetWindowTextW(tmp);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, NULL, 0, NULL, FALSE);
	memset(plate, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, plate, dwNum, NULL, FALSE);

	struct comNode qwe;
	qwe.IOCTL = OUTPUTGARAGE;
	sprintf_s(qwe.strplate, COMLEN, "%s", plate);
	qwe.ioputid = 0;
	serverinfo.command.push(qwe);
}


void CMFCAppclientDlg::OnBnClickedButton3()
{
	// TODO: 出口出车
	DWORD dwNum;
	CString tmp;

	char plate[COMLEN];

	strplateEDIT.GetWindowTextW(tmp);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, NULL, 0, NULL, FALSE);
	memset(plate, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, tmp, -1, plate, dwNum, NULL, FALSE);

	struct comNode qwe;
	qwe.IOCTL = OUTPUTDELE;
	sprintf_s(qwe.strplate, COMLEN, "%s", plate);
	qwe.ioputid = 0;
	serverinfo.command.push(qwe);
}
