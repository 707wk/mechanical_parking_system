
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CMFCAppclientDlg;


// CMFCAppclientDlgAutoProxy ����Ŀ��

class CMFCAppclientDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCAppclientDlgAutoProxy)

	CMFCAppclientDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CMFCAppclientDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CMFCAppclientDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCAppclientDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

