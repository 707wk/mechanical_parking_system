
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApp.h"
#include "DlgProxy.h"
#include "MFCAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CMFCAppDlgAutoProxy, CCmdTarget)

CMFCAppDlgAutoProxy::CMFCAppDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ���  ���ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMFCAppDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFCAppDlg)))
		{
			m_pDialog = reinterpret_cast<CMFCAppDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFCAppDlgAutoProxy::~CMFCAppDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCAppDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IMFCApp ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {55B8A36C-FA2F-42DC-B9DD-7CD5CA5A0C21}
static const IID IID_IMFCApp =
{ 0x55B8A36C, 0xFA2F, 0x42DC, { 0xB9, 0xDD, 0x7C, 0xD5, 0xCA, 0x5A, 0xC, 0x21 } };

BEGIN_INTERFACE_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCAppDlgAutoProxy, IID_IMFCApp, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {20513BA5-74E9-424F-ADB7-89D528B9D441}
IMPLEMENT_OLECREATE2(CMFCAppDlgAutoProxy, "MFCApp.Application", 0x20513ba5, 0x74e9, 0x424f, 0xad, 0xb7, 0x89, 0xd5, 0x28, 0xb9, 0xd4, 0x41)


// CMFCAppDlgAutoProxy ��Ϣ�������
