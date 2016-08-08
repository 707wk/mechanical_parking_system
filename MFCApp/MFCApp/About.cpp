// About.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApp.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout 对话框

IMPLEMENT_DYNAMIC(CAbout, CDialogEx)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ABOUT, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAbout::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAbout::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAbout 消息处理程序


void CAbout::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CAbout::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_pImage = Image::FromFile(_T("res\\about.png"));
	//ImageFromIDResource(IDB_PNG_ABOUT, _T("png"), (Image*&)m_pImage);

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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAbout::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	Graphics graphics(GetDC()->GetSafeHdc());
	graphics.DrawImage(m_pImage, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
}
