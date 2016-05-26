
// MFCAppDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

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

// �Ի�������
	enum { IDD = IDD_MFCAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	int sumcar;
	int spendcar;
	//char sendstr[255];
	HANDLE thread01;

// ʵ��
protected:
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
