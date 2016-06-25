
// MFCAppclientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

class CMFCAppclientDlgAutoProxy;


// CMFCAppclientDlg �Ի���
class CMFCAppclientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMFCAppclientDlg);
	friend class CMFCAppclientDlgAutoProxy;

// ����
public:
	CMFCAppclientDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CMFCAppclientDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CMFCAppclientDlgAutoProxy* m_pAutoProxy;
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
	CEdit strplateEDIT;
	CEdit stateEDIT;
	CEdit ioputIdEDIT;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
