
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CMFCAppDlg;


// CMFCAppDlgAutoProxy ����Ŀ��

class CMFCAppDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCAppDlgAutoProxy)

	CMFCAppDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CMFCAppDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CMFCAppDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCAppDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

