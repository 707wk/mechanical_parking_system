
// DlgProxy.cpp : 实现文件
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
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
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
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCAppclientDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFCAppclient 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {2F6BAF5A-4C1D-4790-AD7C-67C8922B14D0}
static const IID IID_IMFCAppclient =
{ 0x2F6BAF5A, 0x4C1D, 0x4790, { 0xAD, 0x7C, 0x67, 0xC8, 0x92, 0x2B, 0x14, 0xD0 } };

BEGIN_INTERFACE_MAP(CMFCAppclientDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCAppclientDlgAutoProxy, IID_IMFCAppclient, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {ACCD5739-C80D-4EE4-A07B-DF737ACE53C5}
IMPLEMENT_OLECREATE2(CMFCAppclientDlgAutoProxy, "MFCAppclient.Application", 0xaccd5739, 0xc80d, 0x4ee4, 0xa0, 0x7b, 0xdf, 0x73, 0x7a, 0xce, 0x53, 0xc5)


// CMFCAppclientDlgAutoProxy 消息处理程序
