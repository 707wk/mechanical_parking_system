#pragma once


// CAbout 对话框

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAbout();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABOUT };
#endif

public:
	Gdiplus::GdiplusStartupInput    m_gdiplusStartupInput;
	ULONG_PTR                       m_gdiplusToken;
	Image*                          m_pImage;                           //图片对象

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
