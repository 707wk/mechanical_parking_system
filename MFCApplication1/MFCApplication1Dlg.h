
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"

class CMFCApplication1DlgAutoProxy;


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCApplication1Dlg);
	friend class CMFCApplication1DlgAutoProxy;

// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMFCApplication1Dlg();

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CMFCApplication1DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CMscomm1 m_Comm;
	CEdit m_parkid;
	CEdit m_row;
	CEdit m_col;
	afx_msg void savecar();
	afx_msg void delcar();
	afx_msg void stop();
	afx_msg void reset();
	afx_msg void start();
	CEdit m_info;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	CButton m_startend;
};
