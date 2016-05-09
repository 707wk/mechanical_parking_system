
// MFCAppDlg.h : ͷ�ļ�
//

#pragma once

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


// ʵ��
protected:
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
};
