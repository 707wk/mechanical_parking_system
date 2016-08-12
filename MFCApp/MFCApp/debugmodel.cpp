// debugmodel.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp.h"
#include "debugmodel.h"
#include "afxdialogex.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"

#include "GMemDC.h"

#define TESTPUTSEND printf("sen:%02X-%02X-%02X-%02X-%02X -> ",data[1],data[3],data[4],data[5],data[6]);
#define TESTPUTRECN printf("rec:%02X-%02X-%02X-%02X\n",recstr[1],recstr[2],recstr[3],recstr[4]);

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

extern int* idtoindex_garage;

extern int maxindex_garage;

extern int sumgarage;

// debugmodel 对话框

IMPLEMENT_DYNAMIC(debugmodel, CDialogEx)

debugmodel::debugmodel(CWnd* pParent /*=NULL*/)
	: CDialogEx(debugmodel::IDD, pParent)
{

	EnableAutomation();

}

debugmodel::~debugmodel()
{
}

void debugmodel::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void debugmodel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_garage_id);
	DDX_Control(pDX, IDC_EDIT1, m_row);
	DDX_Control(pDX, IDC_EDIT2, m_col);
	DDX_Control(pDX, IDC_EDIT5, m_location);
	DDX_Control(pDX, IDC_EDIT4, m_state);
	DDX_Control(pDX, IDC_BUTTON1, m_save);
	DDX_Control(pDX, IDC_BUTTON2, m_del);
	DDX_Control(pDX, IDC_BUTTON3, m_loca);
	DDX_Control(pDX, IDC_BUTTON4, m_status);
	DDX_Control(pDX, IDC_BUTTON5, m_stop);
}


BEGIN_MESSAGE_MAP(debugmodel, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &debugmodel::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &debugmodel::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &debugmodel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &debugmodel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &debugmodel::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &debugmodel::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &debugmodel::OnBnClickedButton4)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(debugmodel, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_Idebugmodel 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {ABBA8598-9C60-4A1F-90DF-ED4EB9BE8697}
static const IID IID_Idebugmodel =
{ 0xABBA8598, 0x9C60, 0x4A1F, { 0x90, 0xDF, 0xED, 0x4E, 0xB9, 0xBE, 0x86, 0x97 } };

BEGIN_INTERFACE_MAP(debugmodel, CDialogEx)
	INTERFACE_PART(debugmodel, IID_Idebugmodel, Dispatch)
END_INTERFACE_MAP()


// debugmodel 消息处理程序

void debugmodel::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void debugmodel::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


BOOL debugmodel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_save.LoadStdImage(IDB_PNG_SAVE    , _T("PNG"));
	m_del.LoadStdImage(IDB_PNG_DEL      , _T("PNG"));
	m_loca.LoadStdImage(IDB_PNG_LOCATION, _T("PNG"));
	m_status.LoadStdImage(IDB_PNG_STATUS, _T("PNG"));
	m_stop.LoadStdImage(IDB_PNG_STOP    , _T("PNG"));
	m_stop.LoadAltImage(IDB_PNG_RESET   , _T("PNG"));
	m_stop.EnableToggle(TRUE);

	HINSTANCE	hInstResource = NULL;
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BITMAP_DEBUG), RT_BITMAP);
	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_BITMAP_DEBUG), IMAGE_BITMAP, 0, 0, 0);//*/

	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, "select id from t_garageinfo") == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		while (column = mysql_fetch_row(res))        //获取具体的数据
		{
			CString tmp(column[0]);
			m_garage_id.AddString(tmp);
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

	CEdit* pedit = (CEdit*)m_garage_id.GetWindow(GW_CHILD);
	pedit->SetReadOnly(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void debugmodel::OnBnClickedButton1()
{
	// TODO:  存车
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = SAVECAR;
	m_row.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[4] = _wtoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[5] = _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	TESTPUTSEND

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	TESTPUTRECN
	//putinfo(recstr);
}


void debugmodel::OnBnClickedButton2()
{
	// TODO:  取车
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = DELETECAR;
	m_row.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[4] = _wtoi(tmp.GetBuffer(0));
	m_col.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[5] = _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	TESTPUTSEND

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	TESTPUTRECN
	//putinfo(recstr);
}


void debugmodel::OnBnClickedButton5()
{
	// TODO:  急停
	static int flage = 1;

	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	if (flage)
	{
		data[3] = STOP;
		flage = 0;
	}
	else
	{
		data[3] = RESET;
		flage = 1;
	}

	//m_row.GetWindowText(tmp);
	data[4] = 0;// _wtoi(tmp.GetBuffer(0));
	//m_col.GetWindowText(tmp);
	data[5] = 0;// _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	TESTPUTSEND

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	TESTPUTRECN
	//putinfo(recstr);
}

/*
void debugmodel::OnBnClickedButton6()
{
	// TODO:  复位
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = RESET;
	//m_row.GetWindowText(tmp);
	data[4] = 0;// _wtoi(tmp.GetBuffer(0));
	//m_col.GetWindowText(tmp);
	data[5] = 0;// _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	putinfo(recstr);
}//*/


void debugmodel::OnBnClickedButton3()
{
	// TODO:  获取位置
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = GETLOCATION;
	//m_row.GetWindowText(tmp);
	data[4] = 0;// _wtoi(tmp.GetBuffer(0));
	//m_col.GetWindowText(tmp);
	data[5] = 0;// _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	TESTPUTSEND

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	TESTPUTRECN
	//putinfo(recstr);

	tmp.Format(_T("第%d行第%d列"),recstr[2],recstr[1]);
	m_location.SetWindowTextW(tmp);
}


void debugmodel::OnBnClickedButton4()
{
	// TODO:  获取状态
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = GETSTATE;
	//m_row.GetWindowText(tmp);
	data[4] = 0;// _wtoi(tmp.GetBuffer(0));
	//m_col.GetWindowText(tmp);
	data[5] = 0;// _wtoi(tmp.GetBuffer(0));

	data[6] = (data[1] + data[3] + data[4] + data[5]) % CHECKMOD;

	TESTPUTSEND

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	TESTPUTRECN
	//putinfo(recstr);

	switch (recstr[1])
	{
	case STATEFREE:
		m_state.SetWindowTextW(_T("空闲"));
		break;
	case STATESAVE:
		m_state.SetWindowTextW(_T("存车"));
		break;
	case STATEDELETE:
		m_state.SetWindowTextW(_T("取车"));
		break;
	case STATESTOP:
		m_state.SetWindowTextW(_T("停止"));
		break;
	case STATERSET:
		m_state.SetWindowTextW(_T("复位"));
		break;
	case ACCEPTED:
		m_state.SetWindowTextW(_T("已接收"));
		break;
	case BUSY:
		m_state.SetWindowTextW(_T("运行中"));
		break;
	default:
		m_state.SetWindowTextW(_T("未知"));
	}
}

void debugmodel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

BOOL debugmodel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(rect);

	GCMemDC pDevC(pDC, rect);

	/////////////////////////////////////////////////////////////////////////////////
	// just put something in the background - unrelated to GdipButton
	/////////////////////////////////////////////////////////////////////////////////
	if (m_hBitmap)
	{
		pDevC->SelectObject(m_hBitmap);
	}//
	 /////////////////////////////////////////////////////////////////////////////////


	 /////////////////////////////////////////////////////////////////////////////////
	 // Since this function just painted the background into the memory DC,
	 // this is the correct information that can be provided to the buttons
	 /////////////////////////////////////////////////////////////////////////////////
	SetButtonBackGrounds(pDevC);
	/////////////////////////////////////////////////////////////////////////////////

	//return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}

void debugmodel::SetButtonBackGrounds(CDC *pDC)
{
	// call with a memory DC or don't even bother since
	// it will defeat the purpose of doing this
	m_save.SetBkGnd(pDC);
	m_del.SetBkGnd(pDC);
	m_loca.SetBkGnd(pDC);
	m_status.SetBkGnd(pDC);
	m_stop.SetBkGnd(pDC);
}//*/
