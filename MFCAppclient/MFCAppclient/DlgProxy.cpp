
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCAppclient.h"
#include "DlgProxy.h"
#include "MFCAppclientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppclientDlgAutoProxy

IMPLEMENT_DYNCREATE(CMFCAppclientDlgAutoProxy, CCmdTarget)

CMFCAppclientDlgAutoProxy::CMFCAppclientDlgAutoProxy()
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
		ASSERT_KINDOF(CMFCAppclientDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFCAppclientDlg)))
		{
			m_pDialog = reinterpret_cast<CMFCAppclientDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFCAppclientDlgAutoProxy::~CMFCAppclientDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	//	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCAppclientDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IMFCAppclient ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {2F6BAF5A-4C1D-4790-AD7C-67C8922B14D0}
static const IID IID_IMFCAppclient =
{ 0x2F6BAF5A, 0x4C1D, 0x4790, { 0xAD, 0x7C, 0x67, 0xC8, 0x92, 0x2B, 0x14, 0xD0 } };

BEGIN_INTERFACE_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCAppclientDlgAutoProxy, IID_IMFCAppclient, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {ACCD5739-C80D-4EE4-A07B-DF737ACE53C5}
IMPLEMENT_OLECREATE2(CMFCAppclientDlgAutoProxy, "MFCAppclient.Application", 0xaccd5739, 0xc80d, 0x4ee4, 0xa0, 0x7b, 0xdf, 0x73, 0x7a, 0xce, 0x53, 0xc5)


// CMFCAppclientDlgAutoProxy ��Ϣ�������
