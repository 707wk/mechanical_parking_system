#pragma once
#include "afxwin.h"
#include "ControlCode.h"
#include "DataStructure.h"
#include "GdipButton.h"


// debugmodel �Ի���

class debugmodel : public CDialogEx
{
	DECLARE_DYNAMIC(debugmodel)

public:
	debugmodel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~debugmodel();
	void SetButtonBackGrounds(CDC *pDC);

	char recstr[COMLEN];

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEBUG };
	HBITMAP m_hBitmap;//bmp����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_garage_id;
	afx_msg void OnBnClickedButton1();
	CEdit m_row;
	CEdit m_col;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_location;
	CEdit m_state;
	CGdipButton m_save;
	CGdipButton m_del;
	CGdipButton m_loca;
	CGdipButton m_status;
	CGdipButton m_stop;
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
