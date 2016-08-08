
// MFCAppDlg.cpp : ʵ���ļ�
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

extern HANDLE hCom;  //ȫ�ֱ��������ھ��

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
//Image*                          m_pImage;                           //ͼƬ����

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
	//serverinfo.lockflage = 0;
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

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);����������ͼ��

	/* ����ͼ��ĳ�ʼ������ ************************************************************************/
	//��ʼ�� m_NotifyIconData �ڴ�ռ�
	memset(&m_NotifyIconData, 0, sizeof(NOTIFYICONDATA));
	//ʹ������ͼ���Ӧ�ڱ�����,����������԰�����ͼ����¼����͸��������
	m_NotifyIconData.hWnd = GetSafeHwnd();
	ASSERT(m_NotifyIconData.hWnd != NULL);
	//������ͼ������¼�ʱ�򷢳����¼�
	m_NotifyIconData.uCallbackMessage = WM_NOTI;
	//���ṹ��Ĵ�С
	m_NotifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	//��������ͼ��(������Ĭ�ϵ���Դͼ��)
	m_NotifyIconData.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��������ƶ�������ͼ��ʱ�����ʾ����
	memcpy(m_NotifyIconData.szTip, L"�Ѷ�ʽ���峵�����ϵͳ", sizeof(L"�Ѷ�ʽ���峵�����ϵͳ"));
	//��������ͼ�������
	m_NotifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//��������ͼ���ͼ����Դ ID
	m_NotifyIconData.uID = IDR_MAINFRAME;

	/* ��ʾ����ͼ�� *********************************************************************************/
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIconData);

	//��ʼ��GDI+.  
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	//�����ļ�  
	//CT2CW strFileName( _T("I:\\�����ϰ\\CommonFiles\\Test02.png") );  
	//m_pImage = new Image( _T("I:\\�����ϰ\\CommonFiles\\Test02.png") );  
	//m_pImage=Image::FromFile(_T("I:\\�����ϰ\\CommonFiles\\Test02.png"));  
	m_pImage = Image::FromFile(_T("res\\bg.png"));
	//ImageFromIDResource(IDB_PNG_BG, _T("png"), (Image*&)m_pImage);

	//�����ж�  
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
	m_list_ioput.SetExtendedStyle(
		LVS_EX_FLATSB				// ��ƽ������
		| LVS_EX_FULLROWSELECT		// ��������ѡ��
		| LVS_EX_GRIDLINES			// ����������
		);

	m_list_ioput.InsertColumn(0, _T("���"), LVCFMT_CENTER, 40, 0);
	//m_list_ioput.InsertColumn(1, _T("��ע"), LVCFMT_CENTER, 87, 0);
	m_list_ioput.InsertColumn(1, _T("����"), LVCFMT_CENTER, 70, 0);
	m_list_ioput.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, 70, 0);//*/

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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCAppDlg::OnPaint()
{
	Graphics graphics(GetDC()->GetSafeHdc());
	graphics.DrawImage(m_pImage, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
	//printf("%d %d\n", m_pImage->GetWidth(), m_pImage->GetHeight());
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
		m_list_garage.SetItemText(index, 2, _T("δ֪"));

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
			m_list_ioput.SetItemText(index, 1, _T("���"));
			break;
		case 2:
			m_list_ioput.SetItemText(index, 1, _T("����"));
			break;
		case 3:
			m_list_ioput.SetItemText(index, 1, _T("�����"));
			break;
		default:
			break;
		}

		m_list_ioput.SetItemText(index, 2, _T("δ֪"));
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
	//���ݳ���ģ�������Լ���ѯ���ȷ����ʱʱ��
//	overtime = ((maxindex_garage + 1)*serverinfo.intervaltime) / 1000;
//	if (overtime<1)overtime = 1;
	//////////////////////////////////////////////////////////////////////////

	//for (;;)
	{
		switch (garage[gindex].getnowstatus())
		{
		case STATEFREE:
			m_list_garage.SetItemText(gindex, 2, _T("����"));
			break;
		case STATESAVE:
			m_list_garage.SetItemText(gindex, 2, _T("�泵"));
			break;
		case STATEDELETE:
			m_list_garage.SetItemText(gindex, 2, _T("ȡ��"));
			break;
		case STATESTOP:
			m_list_garage.SetItemText(gindex, 2, _T("ֹͣ"));
			break;
		case STATERSET:
			m_list_garage.SetItemText(gindex, 2, _T("��λ"));
			break;
		case ACCEPTED:
			m_list_garage.SetItemText(gindex, 2, _T("�ѽ���"));
			break;
		case BUSY:
			m_list_garage.SetItemText(gindex, 2, _T("������"));
			break;
		case OFFLINE:
			m_list_garage.SetItemText(gindex, 2, _T("����"));
			break;
		default:
			m_list_garage.SetItemText(gindex, 2, _T("δ֪"));
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
			m_list_ioput.SetItemText(cindex, 2, _T("����"));
		}
		else
		{
			m_list_ioput.SetItemText(cindex, 2, _T("����"));
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
	// TODO:  �ڴ���������������
	CAbout dlg;
	dlg.DoModal();
	//ShellExecute(NULL, _T("open"), _T("http://gxy.hunnu.edu.cn/"), NULL, NULL, SW_SHOWNORMAL);
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


void CMFCAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	//��ô��ھ���
	rc -= rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 15, 15);
	//���ݴ��ھ��δ���һ��Բ�Ǿ�������������γ�Բ�ǵĴ�С
	SetWindowRgn(rgn, TRUE);//*/
}


void CMFCAppDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Shell_NotifyIcon(NIM_DELETE, &m_NotifyIconData);
}


BOOL CMFCAppDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
	{
		pMsg->wParam = VK_RETURN;
		//��ESC������Ϣ�滻Ϊ�س�������Ϣ����������ESC��ʱ��
		//Ҳ��ȥ����OnOK��������OnOKʲôҲ����������ESCҲ������
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
		//�Ҽ�����
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