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

BOOL CAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//m_pImage = Image::FromFile(_T("res\\about.png"));
	ImageFromIDResource(IDB_PNG_ABOUT, _T("png"), (Image*&)m_pImage);

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
