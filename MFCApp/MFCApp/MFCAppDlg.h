
// MFCAppDlg.h : 头文件
//

#include "OScopeCtrl.h"

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_NOTI (WM_USER+1)

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

	//int sumcar;
	//int spendcar;
	//char sendstr[255];
	COScopeCtrl m_Osc;
	HANDLE thread01;
	HANDLE thread02;

	Gdiplus::GdiplusStartupInput    m_gdiplusStartupInput;
	ULONG_PTR                       m_gdiplusToken;
	Image*                          m_pImage;                           //图片对象

	NOTIFYICONDATA                  m_NotifyIconData;                   //托盘图标

// 实现
protected:
	void init_list();
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
	CEdit m_sumcar;
	CEdit m_freecar;
	afx_msg void On32774();
	afx_msg void On32773();
	afx_msg void On32771();
	afx_msg void On32772();
	CEdit m_reservationcar;
	CEdit m_Threadinfo;
	CListCtrl m_list_ioput;
	afx_msg void On32775();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
};
