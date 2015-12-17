
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgProxy.h"
#include "MFCApplication1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1DlgAutoProxy

IMPLEMENT_DYNCREATE(CMFCApplication1DlgAutoProxy, CCmdTarget)

CMFCApplication1DlgAutoProxy::CMFCApplication1DlgAutoProxy()
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
		ASSERT_KINDOF(CMFCApplication1Dlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFCApplication1Dlg)))
		{
			m_pDialog = reinterpret_cast<CMFCApplication1Dlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFCApplication1DlgAutoProxy::~CMFCApplication1DlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCApplication1DlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCApplication1DlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCApplication1DlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFCApplication1 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {A91E7995-AE86-4A7B-9695-13EB4416AF32}
static const IID IID_IMFCApplication1 =
{ 0xA91E7995, 0xAE86, 0x4A7B, { 0x96, 0x95, 0x13, 0xEB, 0x44, 0x16, 0xAF, 0x32 } };

BEGIN_INTERFACE_MAP(CMFCApplication1DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCApplication1DlgAutoProxy, IID_IMFCApplication1, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {F27FD3A9-7089-4E35-8673-965C015F2C87}
IMPLEMENT_OLECREATE2(CMFCApplication1DlgAutoProxy, "MFCApplication1.Application", 0xf27fd3a9, 0x7089, 0x4e35, 0x86, 0x73, 0x96, 0x5c, 0x1, 0x5f, 0x2c, 0x87)


// CMFCApplication1DlgAutoProxy 消息处理程序
