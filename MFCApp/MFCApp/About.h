#pragma once


// CAbout �Ի���

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAbout();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ABOUT };
#endif

public:
	Gdiplus::GdiplusStartupInput    m_gdiplusStartupInput;
	ULONG_PTR                       m_gdiplusToken;
	Image*                          m_pImage;                           //ͼƬ����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
