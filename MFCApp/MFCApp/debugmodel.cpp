// debugmodel.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp.h"
#include "debugmodel.h"
#include "afxdialogex.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

//extern CCarbarnInfo* garage;

//extern CWayFinding* mapinfo;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

extern int link;

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
	DDX_Control(pDX, IDC_EDIT3, m_info);
	DDX_Control(pDX, IDC_EDIT5, m_location);
	DDX_Control(pDX, IDC_EDIT4, m_state);
}


BEGIN_MESSAGE_MAP(debugmodel, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &debugmodel::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &debugmodel::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &debugmodel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &debugmodel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &debugmodel::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &debugmodel::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &debugmodel::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &debugmodel::OnBnClickedButton4)
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
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列

	mysql_query(&serverinfo.mysql, "SET NAMES 'UTF-8'");

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

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	putinfo(recstr);
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

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	putinfo(recstr);
}


void debugmodel::OnBnClickedButton5()
{
	// TODO:  急停
	char data[] = "1234567";

	data[0] = ADDFIRST;
	data[2] = ADDEND;

	CString tmp;
	m_garage_id.GetWindowText(tmp);

	if (tmp == "")
		return;

	data[1] = _wtoi(tmp.GetBuffer(0));
	data[3] = STOP;
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
}


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
}


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

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	putinfo(recstr);

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

	OnSend(data, 7);
	Sleep(100);
	memset(recstr, '\0', COMLEN);
	OnReceive(recstr, 4);

	putinfo(recstr);

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

void debugmodel::putinfo(char* recstr)
{
	CString tmp;
	tmp.Format(_T("rev:%02X-%02X-%02X-%02X"),
		recstr[0], recstr[1], recstr[2], recstr[3]);
	CString strtmp;
	m_info.GetWindowText(strtmp);
	strtmp = _T("\r\n") + strtmp;
	strtmp = tmp + strtmp;
	m_info.SetWindowText(strtmp);
}