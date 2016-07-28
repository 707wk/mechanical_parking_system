
// MFCAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "debugmodel.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include "IOCPserver.h"
#include "md5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern struct serverset serverinfo;

extern HANDLE hCom;  //ȫ�ֱ��������ھ��

extern DCB dcb;

extern CCarbarnInfo* garage;

extern CWayFinding* mapinfo;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

// CMFCAppDlg �Ի���

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
	serverinfo.lockflage = 0;
}

CMFCAppDlg::~CMFCAppDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_garage);
	DDX_Control(pDX, IDC_LIST2, m_list_error);
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
END_MESSAGE_MAP()


// CMFCAppDlg ��Ϣ�������

BOOL CMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

//	MYSQL_RES *res;                    //��ѯ�����
//	MYSQL_ROW column;                  //�����е���

	//��ʼ�����߿ؼ�
	CRect rt;
	GetDlgItem(IDC_CUSTOM1)->GetWindowRect(rt);
	ScreenToClient(rt);
	m_Osc.Create(WS_VISIBLE | WS_CHILD, rt, this);
	m_Osc.SetRange(0.0, serverinfo.Threadsum*100, 1);
	m_Osc.SetYUnits(_T(""));
	m_Osc.SetXUnits(_T("����ʹ����"));
	m_Osc.SetBackgroundColor(RGB(0, 0, 64));
	m_Osc.SetGridColor(RGB(192, 192, 255));
	m_Osc.SetPlotColor(RGB(255, 255, 0));
	m_Osc.AppendPoint(0.0);

	//�����б�����
	m_list_garage.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
		| LVS_EX_FULLROWSELECT		// ��������ѡ��
		| LVS_EX_GRIDLINES			// ����������
		);

	m_list_garage.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, 0);
	m_list_garage.InsertColumn(1, _T("��ע"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(3, _T("�����ʱ"), LVCFMT_CENTER, 70, 0);
	m_list_garage.InsertColumn(4, _T("����"), LVCFMT_CENTER, 50, 0);
	m_list_garage.InsertColumn(5, _T("�Ѵ�"), LVCFMT_CENTER, 50, 0);

	//�����б�����
	m_list_error.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
		| LVS_EX_FULLROWSELECT		// ��������ѡ��
		| LVS_EX_GRIDLINES			// ����������
		);

	m_list_error.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, 0);
	m_list_error.InsertColumn(1, _T("��ע"), LVCFMT_CENTER, 70, 0);
	m_list_error.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, 70, 0);

	//�����б�����
	m_list_ioput.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
		| LVS_EX_FULLROWSELECT		// ��������ѡ��
		| LVS_EX_GRIDLINES			// ����������
		);

	m_list_ioput.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, 0);
	//m_list_ioput.InsertColumn(1, _T("��ע"), LVCFMT_CENTER, 87, 0);
	m_list_ioput.InsertColumn(1, _T("����"), LVCFMT_CENTER, 70, 0);
	m_list_ioput.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, 70, 0);//*/

	/*//�����б�����
	m_list_reservation.SetExtendedStyle(
	LVS_EX_FLATSB				// ��ƽ������
	| LVS_EX_FULLROWSELECT		// ��������ѡ��
	| LVS_EX_GRIDLINES			// ����������
	);

	m_list_reservation.InsertColumn(0,"ID"        ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(1,"���ƺ�"    ,LVCFMT_CENTER, 70,0);
	m_list_reservation.InsertColumn(3,"�ȴ�ʱ��"  ,LVCFMT_CENTER, 70 ,0);*/

	//	m_link_info.SetWindowText("δ����");

	/*	for(int i=0;i<sumgarage;i++)
	{
	sumcar+=garage[i].getsumcar();
	spendcar+=garage[i].getspendcar();
	}*/

	/*mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select type_id from t_map where type=1") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result

		while (column = mysql_fetch_row(res))        //��ȡ���������
		{
			CString tmp(column[0]);
			m_list_input.AddString(tmp);
		}
	}
	else
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		exit(1);
	}
	CEdit* pedit = (CEdit*)m_list_input.GetWindow(GW_CHILD);
	pedit->SetReadOnly(true);*/

	//update_list();
	init_list();

	thread01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPoll, NULL, 0, NULL);
	thread02 =CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)iocpstartserver, NULL, 0, NULL);

/*	//////////////////////////////////////////////////////////////////////////
	CString tmp(serverinfo.mscomm);
	hCom = CreateFile(tmp,//COM1��
		GENERIC_READ | GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, //�ص���ʽ
		NULL);
	if (hCom == (HANDLE)-1)
	{
		AfxMessageBox(_T("��COMʧ��!"));
		exit(1);
		return FALSE;
	}

	SetupComm(hCom, COMLEN, COMLEN); //���뻺����������������Ĵ�С����100

	COMMTIMEOUTS TimeOuts;
	//�趨����ʱ
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	//�ڶ�һ�����뻺���������ݺ���������������أ�
	//�������Ƿ������Ҫ����ַ���


	//�趨д��ʱ
	TimeOuts.WriteTotalTimeoutMultiplier = 100;
	TimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ

	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = serverinfo.BaudRate; //������Ϊ9600
	dcb.ByteSize = serverinfo.ByteSize; //ÿ���ֽ���8λ
	dcb.Parity = serverinfo.Parity;   //��żУ��λ
	dcb.StopBits = serverinfo.StopBits; //ֹͣλ
	SetCommState(hCom, &dcb);

	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);
*/	//////////////////////////////////////////////////////////////////////////

//	m_startend.SetWindowText(_T("��ͣ"));
	//	m_link_info.SetWindowText("������");
//	link = 1;
	serverinfo.runstate = 1;

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_GREEN);
	//m_stateico.SetIcon(hIcon);

	SetTimer(1, 1000, NULL);
	SetTimer(2, 1000, NULL);
	SetTimer(3, 60*1000 , NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCAppDlg::OnPaint()
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
HCURSOR CMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CMFCAppDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFCAppDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFCAppDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFCAppDlg::CanExit()
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



void CMFCAppDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMFCAppDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

/*void CMFCAppDlg::setinfo(char* str)
{
	CString strtmp;
//	m_info.GetWindowText(strtmp);
	strtmp = str;
	m_info.SetWindowText(strtmp);
}*/


void CMFCAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MYSQL_RES *res;                    //��ѯ�����
//	MYSQL_ROW column;                  //�����е���

	switch (nIDEvent)
	{
	case 1:
		if (serverinfo.runstate)
		{
			for (int i = 0; i<sumgarage; i++)
				garage[i].accspendtime();
			update_list();
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
			AfxMessageBox(_T("time:32���ݿ�����ʧ��"));
			exit(1);
		}
		//else AfxMessageBox(_T("delete successful"));

		if (mysql_query(&serverinfo.mysql, "select plate from t_reservation") == NULL)
		{
			res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
			serverinfo.reservation = (int)mysql_num_rows(res);
			//printf("[reservation=%d]", serverinfo.reservation);
		}
		else
		{
			AfxMessageBox(_T("time:31���ݿ�����ʧ��"));
			exit(1);
		}

		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCAppDlg::init_list()
{
	CString tmp;

	m_list_garage.DeleteAllItems();
	m_list_error.DeleteAllItems();

	for (int index = 0; index<sumgarage; index++)
	{
		tmp.Format(_T("%d"), garage[index].getcarbarnid());
		m_list_garage.InsertItem(index, tmp);
		tmp = garage[index].getname().c_str();
		m_list_garage.SetItemText(index, 1, tmp);
		m_list_garage.SetItemText(index, 2, _T("δ֪"));

		m_list_garage.SetItemText(index, 3, _T("00:00:00"));

		tmp.Format(_T("%d"), garage[index].getsumcar());
		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[index].getspendcar());
		m_list_garage.SetItemText(index, 5, tmp);

		serverinfo.sumcar += garage[index].getsumcar();
		serverinfo.spendcar += garage[index].getspendcar();
	}

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
	int index = 0;
	int errorindex = 0;
	int overtime = 0;
	CString tmp;

	//m_list_garage.DeleteAllItems();
	m_list_error.DeleteAllItems();

//	serverinfo.sumcar = 0;
//	serverinfo.spendcar = 0;

	//////////////////////////////////////////////////////////////////////////
	//���ݳ���ģ�������Լ���ѯ���ȷ����ʱʱ��
	overtime = ((maxindex + 1)*serverinfo.intervaltime) / 1000;
	if (overtime<1)overtime = 1;
	//////////////////////////////////////////////////////////////////////////

	for (int i = 0; i<sumgarage; i++)
	{
		//////////////////////////////////////////////////////////////////////////
		//�ඨ����һ������
		index = i;
		//////////////////////////////////////////////////////////////////////////
		tmp.Format(_T("%d"), garage[i].getcarbarnid());
		//m_list_garage.InsertItem(index, tmp);
		m_list_garage.SetItemText(index, 0, tmp);
		tmp = garage[i].getname().c_str();
		m_list_garage.SetItemText(index, 1, tmp);
		/*if (garage[i].getspendtime()>overtime)
		{
			/*if (garage[i].getnowstatus() == ONLINE)
			{
				serverinfo.sumcar-= garage[i].getsumcar();
				serverinfo.spendcar-= garage[i].getspendcar();
				//garage[i].setnowstatus(OFFLINE);
			}//

			//garage[i].setoffline();
			//garage[i].setnowstatus(OFFLINE);
			tmp.Format(_T("%d"), garage[i].getcarbarnid());
			m_list_garage.SetItemText(index, 2, _T("����"));
			m_list_error.InsertItem(errorindex, tmp);
			tmp = garage[i].getname().c_str();
			m_list_error.SetItemText(errorindex, 1, tmp);
			m_list_error.SetItemText(errorindex, 2, _T("����"));
			errorindex++;
		}
		else//*/
		{
			/*if (garage[i].getnowstatus() == OFFLINE)
			{
				serverinfo.sumcar += garage[i].getsumcar();
				serverinfo.spendcar += garage[i].getspendcar();
				//garage[i].setnowstatus(ONLINE);
			}//*/

			switch (garage[i].getnowstatus())
			{
			case STATEFREE:
				m_list_garage.SetItemText(index, 2, _T("����"));
				break;
			case STATESAVE:
				m_list_garage.SetItemText(index, 2, _T("�泵"));
				break;
			case STATEDELETE:
				m_list_garage.SetItemText(index, 2, _T("ȡ��"));
				break;
			case STATESTOP:
				m_list_garage.SetItemText(index, 2, _T("ֹͣ"));
				break;
			case STATERSET:
				m_list_garage.SetItemText(index, 2, _T("��λ"));
				break;
			case ACCEPTED:
				m_list_garage.SetItemText(index, 2, _T("�ѽ���"));
				break;
			case BUSY:
				m_list_garage.SetItemText(index, 2, _T("������"));
				break;
			case OFFLINE:
				m_list_garage.SetItemText(index, 2, _T("����"));

				//////////////////////////////////////////////////////////////////////////
				//������ 2016-7-28
				tmp.Format(_T("%d"), garage[i].getcarbarnid());
				m_list_garage.SetItemText(index, 2, _T("����"));
				m_list_error.InsertItem(errorindex, tmp);
				tmp = garage[i].getname().c_str();
				m_list_error.SetItemText(errorindex, 1, tmp);
				m_list_error.SetItemText(errorindex, 2, _T("����"));
				errorindex++;
				//////////////////////////////////////////////////////////////////////////

				break;
			default:
				m_list_garage.SetItemText(index, 2, _T("δ֪"));
			}
		}

		tmp.Format(_T("%02d:%02d:%02d"), garage[i].getspendtime() / 3600, garage[i].getspendtime() / 60 % 60, garage[i].getspendtime() % 60);
		m_list_garage.SetItemText(index, 3, tmp);

		tmp.Format(_T("%d"), garage[i].getsumcar());
		m_list_garage.SetItemText(index, 4, tmp);

		tmp.Format(_T("%d"), garage[i].getspendcar());
		m_list_garage.SetItemText(index, 5, tmp);
	}

	tmp.Format(_T("%d"), serverinfo.sumcar);
	m_sumcar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation);
	m_freecar.SetWindowText(tmp);

	tmp.Format(_T("%d"), serverinfo.reservation);
	m_reservationcar.SetWindowText(tmp);

	tmp.Format(_T("%d/%d"), serverinfo.Threadwork, serverinfo.Threadsum);
	m_Threadinfo.SetWindowText(tmp);
}

/*
void CMFCAppDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!link)
	{
		/*
		if (m_Comm.GetPortOpen())
		m_Comm.SetPortOpen(FALSE);
		m_Comm.SetCommPort(serverinfo.mscomm); //ѡ��com���ɸ��ݾ����������
		m_Comm.SetInBufferSize(COMLEN);          //�������뻺�����Ĵ�С��Bytes
		m_Comm.SetOutBufferSize(COMLEN);         //�������뻺�����Ĵ�С��Bytes//
		CString tmp;
		tmp = serverinfo.mscommini;
		m_Comm.SetSettings(tmp);      //������9600����У�飬8������λ��1��ֹͣλ
		m_Comm.SetInputMode(1);                //1����ʾ�Զ����Ʒ�ʽ��ȡ����
		m_Comm.SetRThreshold(1);               //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
		m_Comm.SetInputLen(0);                 //���õ�ǰ���������ݳ���Ϊ0
		if (!m_Comm.GetPortOpen())
		{
		m_Comm.SetPortOpen(TRUE);          //�򿪴���
		}
		else
		{
		m_Comm.SetPortOpen(FALSE);
		}
		m_Comm.GetInput();                     //��Ԥ���������������������
		//m_Comm.SetOutput(COleVariant("ok")); //��������
		//////////////////////////////////////////////////////////////////////////*/
		/*hCom=CreateFile(serverinfo.mscomm,//COM1��
		GENERIC_READ|GENERIC_WRITE, //�������д
		0, //��ռ��ʽ
		NULL,
		OPEN_EXISTING, //�򿪶����Ǵ���
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //�ص���ʽ
		NULL);
		if(hCom==(HANDLE)-1)
		{
		AfxMessageBox("��COMʧ��!");
		return ;
		}

		SetupComm(hCom,COMLEN,COMLEN); //���뻺����������������Ĵ�С����100

		COMMTIMEOUTS TimeOuts;
		//�趨����ʱ
		TimeOuts.ReadIntervalTimeout=MAXDWORD;
		TimeOuts.ReadTotalTimeoutMultiplier=0;
		TimeOuts.ReadTotalTimeoutConstant=0;
		//�ڶ�һ�����뻺���������ݺ���������������أ�
		//�������Ƿ������Ҫ����ַ���


		//�趨д��ʱ
		TimeOuts.WriteTotalTimeoutMultiplier=100;
		TimeOuts.WriteTotalTimeoutConstant=500;
		SetCommTimeouts(hCom,&TimeOuts); //���ó�ʱ

		DCB dcb;
		GetCommState(hCom,&dcb);
		dcb.BaudRate=serverinfo.BaudRate; //������Ϊ9600
		dcb.ByteSize=serverinfo.ByteSize; //ÿ���ֽ���8λ
		dcb.Parity  =serverinfo.Parity;   //��żУ��λ
		dcb.StopBits=serverinfo.StopBits; //ֹͣλ
		SetCommState(hCom,&dcb);

		PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);*/
/*
		m_startend.SetWindowText(_T("��ͣ"));
		//		m_link_info.SetWindowText("������");
		link = 1;

		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_GREEN);
		m_stateico.SetIcon(hIcon);

		SetTimer(1, 1000, NULL);
	}
	else if (link)
	{
		//m_Comm.SetPortOpen(FALSE);
		link = 0;
		//Sleep(500);
		m_startend.SetWindowText(_T("����"));
		//		m_link_info.SetWindowText("������");
		//CloseHandle(hCom);

		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_RED);
		m_stateico.SetIcon(hIcon);

		KillTimer(1);
	}
}//*/

/*
void CMFCAppDlg::OnBnClickedButton1()
{
	// TODO:  �泵
	MYSQL_RES *res;                    //��ѯ�����
	//	MYSQL_ROW column;                  //�����е���
	CString strplate;
	CString strinput;
//	CString strtmp;
	char strtmp[COMLEN];
	char pValue[COMLEN];
	DWORD dwNum;

	//DWORD start;
	//DWORD stop;
	
	m_carplate.GetWindowText(strplate);
	m_list_input.GetWindowText(strinput);

	if (strplate == "")return;

	if (strinput == "")return;

	if (serverinfo.sumcar == serverinfo.spendcar)
	{
		MessageBox(_T("��λ����"));
		return;
	}

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select plate from t_reservation where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result

		if (mysql_num_rows(res))
		{
//			strtmp.Format(
			sprintf_s(strtmp, COMLEN, "delete from t_reservation where plate='%s'", pValue);
			mysql_query(&serverinfo.mysql, strtmp);
		}
	}
	else
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		exit(1);
	}

//stop = GetTickCount();
//printf("<1<%ld>", stop - start);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select plate from t_carinfo where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result

		if (mysql_num_rows(res))
		{
			MessageBox(_T("�����ظ�"));
			return;
		}
	}

//stop = GetTickCount();
//printf("<2<%ld>", stop - start);

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strinput, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strinput, -1, pValue, dwNum, NULL, FALSE);
	
//start = GetTickCount();

	int garageid = mapinfo->nearestcarport(atoi(pValue));

//stop = GetTickCount();
//printf("<3<%ld>", stop - start);

//	delete pValue;
	if (garageid == -1)
	{
		MessageBox(_T("δ�ҵ�����ģ��,���Ժ�����!"));
		return;
	}

//	strtmp.Format(
	printf("����ĳ����ǵ�%d�ų���\n", garageid);
	//MessageBox(strtmp);
//	CString tmp(strtmp);
//	m_carinfo.SetWindowText(tmp);
	//sumcar
	//spendcar++;

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//start = GetTickCount();

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "insert into t_carinfo(plate,start) values('%s',now())", pValue);
	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		exit(1);
	}

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = SAVECAR;
	sendstr[1] = garage[index].getrows(garage[index].findemptycarid());
	sendstr[2] = garage[index].getcols(garage[index].findemptycarid());
	garage[index].setcommand(sendstr);

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN ,"update t_carinfo set carbarnid=%d,num=%d where plate='%s'",
		garageid, garage[index].findemptycarid(), pValue);
	garage[index].setsqlcommand(strtmp);

	garage[index].savecar();

	//stop = GetTickCount();
	//printf("<4<%ld>", stop - start);

	serverinfo.spendcar++;
}
//*/
/*
void CMFCAppDlg::OnBnClickedButton2()
{
	// TODO:  ȡ��
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���
	CString strplate;
//	CString strtmp;
	char strtmp[COMLEN];
	char pValue[COMLEN];
	DWORD dwNum;

	m_carplate.GetWindowText(strplate);

	if (strplate == "") return;

	dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, NULL, 0, NULL, FALSE);
	memset(pValue, 0, COMLEN);
	WideCharToMultiByte(CP_OEMCP, NULL, strplate, -1, pValue, dwNum, NULL, FALSE);

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "select carbarnid,num from t_carinfo where plate='%s'", pValue);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		exit(1);
	}
	res = mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result

	if (mysql_num_rows(res) == 0)
	{
		MessageBox(_T("δ�ҵ�����"));
		return;
	}

	column = mysql_fetch_row(res);

	int garageid = atoi(column[0]);
	int num = atoi(column[1]);

	int nearoutput = mapinfo->nearestexit(garageid);
	if (nearoutput == -1)
	{
		MessageBox(_T("δ�ҵ�����,�����ͼ����!"));
		return;
	}

//	CString tmp;
	printf("����ĳ����ǵ�%d�ų���\n", nearoutput);
	//MessageBox(strtmp);
//	m_carinfo.SetWindowText(tmp);
	//spendcar--;

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = DELETECAR;
	sendstr[1] = garage[index].getrows(num);
	sendstr[2] = garage[index].getcols(num);
	garage[index].setcommand(sendstr);

	//delete from t_carinfo where plate='%s';
//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "update t_carinfo set carbarnid=0,num=0 where plate='%s'", pValue);
	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		exit(1);
	}

//	strtmp.Format(
	sprintf_s(strtmp, COMLEN, "delete from t_carinfo where plate='%s'", pValue);
	garage[index].setsqlcommand(strtmp);

	garage[index].deletecar(num);

	serverinfo.spendcar--;
}
//*/

void CMFCAppDlg::On32774()
{
	// TODO:  �ڴ���������������
	ShellExecute(NULL, _T("open"), _T("http://gxy.hunnu.edu.cn/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32773()
{
	// TODO:  Web��
	ShellExecute(NULL, _T("open"), _T("http://127.0.0.1/manage/"), NULL, NULL, SW_SHOWNORMAL);
}

void CMFCAppDlg::On32771()
{
	// TODO:  �ڴ���������������
	if (CanExit())
		CDialog::OnCancel();
}

void CMFCAppDlg::On32772()
{
	// TODO:  �ڴ���������������
	serverinfo.runstate = 0;

	debugmodel dlg;
	dlg.DoModal();

	serverinfo.runstate = 1;
}

void CMFCAppDlg::On32775()
{
	// TODO: ����
}
