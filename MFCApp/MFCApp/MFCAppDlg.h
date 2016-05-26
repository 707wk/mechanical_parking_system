
// MFCAppDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CMFCAppDlgAutoProxy;


// CMFCAppDlg 对话框
class CMFCAppDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCAppDlg);
	friend class CMFCAppDlgAutoProxy;

// 构造
public:
	CMFCAppDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMFCAppDlg();

// 对话框数据
	enum { IDD = IDD_MFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	int sumcar;
	int spendcar;
	//char sendstr[255];
	HANDLE thread01;

// 实现
protected:
	void update_list();
	CMFCAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_list_garage;
	CListCtrl m_list_error;
	CEdit m_sumcar;
	CEdit m_freecar;
	CComboBox m_list_input;
	CButton m_startend;
	CStatic m_stateico;
	afx_msg void OnBnClickedButton3();
	CEdit m_carplate;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list_passageway;
	afx_msg void OnBnClickedButton2();
	afx_msg void On32774();
	afx_msg void On32773();
	afx_msg void On32771();
	afx_msg void On32772();
};
