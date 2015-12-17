
// MFCApplication1Dlg.cpp : ʵ���ļ�
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

//��ȡ�����ļ�
int readserverset()
{
	FILE* fp = fopen("serverSet.ini", "r");
	if (fp == NULL)
	{
		AfxMessageBox(_T("δ�ҵ������ļ�!"));
		exit(1);
	}

	fscanf(fp, "server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d\ncost=%lf\nmscomm=%d\nmscommini=%s\nrefreshinterval=%d",
		serverinfo.ip, serverinfo.name, serverinfo.password, serverinfo.database,
		&serverinfo.port, &serverinfo.cost, &serverinfo.mscomm, serverinfo.mscommini, &serverinfo.refreshinterval);

	return 0;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication1Dlg �Ի���


IMPLEMENT_DYNAMIC(CMFCApplication1Dlg, CDialogEx);

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	readserverset();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳���  ��Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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



void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::savecar()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	m_Comm.put_Output(a);//��������
}


void CMFCApplication1Dlg::delcar()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	m_Comm.put_Output(a);//��������
}


void CMFCApplication1Dlg::stop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	m_Comm.put_Output(a);//��������
}


void CMFCApplication1Dlg::reset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	m_Comm.put_Output(a);//��������
}


void CMFCApplication1Dlg::start()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!link)
	{
		if (m_Comm.get_PortOpen())
			m_Comm.put_PortOpen(FALSE);
		m_Comm.put_CommPort(serverinfo.mscomm); //ѡ��com���ɸ��ݾ����������
		m_Comm.put_InBufferSize(1024);          //�������뻺�����Ĵ�С��Bytes
		m_Comm.put_OutBufferSize(1024);         //�������뻺�����Ĵ�С��Bytes//
		CString tmp;
		tmp = serverinfo.mscommini;
		m_Comm.put_Settings(tmp);      //������9600����У�飬8������λ��1��ֹͣλ
		m_Comm.put_InputMode(1);                //1����ʾ�Զ����Ʒ�ʽ��ȡ����
		m_Comm.put_RThreshold(1);               //����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
		m_Comm.put_InputLen(0);                 //���õ�ǰ���������ݳ���Ϊ0
		if (!m_Comm.get_PortOpen())
		{
			m_Comm.put_PortOpen(TRUE);          //�򿪴���
		}
		else
		{
			m_Comm.put_PortOpen(FALSE);
		}
		m_Comm.get_Input();                     //��Ԥ���������������������
		//m_Comm.SetOutput(COleVariant("ok")); //��������
		//////////////////////////////////////////////////////////////////////////
		m_info.SetWindowText(_T(""));
		m_startend.SetWindowText(_T("�Ͽ��豸"));
		link = 1;
	}
	else if (link)
	{
		m_Comm.put_PortOpen(FALSE);
		m_startend.SetWindowText(_T("�����豸"));
		link = 0;
	}
}


BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMFCApplication1Dlg::OnCommMscomm1()
{
	// TODO:  �ڴ˴������Ϣ����������
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
