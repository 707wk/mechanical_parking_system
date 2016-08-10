
// MFCAppDlg.h : ͷ�ļ�
//

#include "OScopeCtrl.h"
#include "GdipButton.h"

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_NOTI (WM_USER+1)

class CMFCAppDlgAutoProxy;


// CMFCAppDlg �Ի���
class CMFCAppDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCAppDlg);
	friend class CMFCAppDlgAutoProxy;

// ����
public:
	CMFCAppDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMFCAppDlg();
	void SetButtonBackGrounds(CDC *pDC);

// �Ի�������
	enum { IDD = IDD_MFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//int sumcar;
	//int spendcar;
	//char sendstr[255];
	COScopeCtrl m_Osc;
	HANDLE thread01;
	HANDLE thread02;

//	Image*                          m_pImage;//png����
	HBITMAP m_hBitmap;//bmp����

	NOTIFYICONDATA                  m_NotifyIconData;                   //����ͼ��

// ʵ��
protected:
	void init_list();
	void update_list();
	CMFCAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
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
	CEdit m_reservationcar;
	CEdit m_Threadinfo;
	CListCtrl m_list_ioput;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	CGdipButton m_button1;
	CGdipButton m_button2;
	CGdipButton m_button3;
	CGdipButton m_button4;
	CGdipButton m_button5;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
