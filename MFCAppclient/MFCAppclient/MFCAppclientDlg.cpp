
// MFCAppclientDlg.cpp : ʵ���ļ�
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
// CMFCAppclientDlg �Ի���


IMPLEMENT_DYNAMIC(CMFCAppclientDlg, CDialogEx);

CMFCAppclientDlg::CMFCAppclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCAppclientDlg::~CMFCAppclientDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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


// CMFCAppclientDlg ��Ϣ�������

BOOL CMFCAppclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPoll, NULL, 0, NULL);

	SetTimer(1, 1000, NULL);
	SetTimer(2, serverinfo.intervaltime, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCAppclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCAppclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMFCAppclientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMFCAppclientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMFCAppclientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		serverinfo.overtime++;
		if (serverinfo.overtime > serverinfo.maxovertime)
		{
			stateEDIT.SetWindowTextW(_T("�Ͽ�"));
		}
		else
		{
			stateEDIT.SetWindowTextW(_T("����"));
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
	// TODO: ��ڴ泵
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
	// TODO: ����ȡ��
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
	// TODO: ���ڳ���
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
