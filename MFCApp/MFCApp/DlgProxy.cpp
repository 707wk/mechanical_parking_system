
// DlgProxy.cpp : 实现文件
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
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMFCAppDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFCApp 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {55B8A36C-FA2F-42DC-B9DD-7CD5CA5A0C21}
static const IID IID_IMFCApp =
{ 0x55B8A36C, 0xFA2F, 0x42DC, { 0xB9, 0xDD, 0x7C, 0xD5, 0xCA, 0x5A, 0xC, 0x21 } };

BEGIN_INTERFACE_MAP(CMFCAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCAppDlgAutoProxy, IID_IMFCApp, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {20513BA5-74E9-424F-ADB7-89D528B9D441}
IMPLEMENT_OLECREATE2(CMFCAppDlgAutoProxy, "MFCApp.Application", 0x20513ba5, 0x74e9, 0x424f, 0xad, 0xb7, 0x89, 0xd5, 0x28, 0xb9, 0xd4, 0x41)


// CMFCAppDlgAutoProxy 消息处理程序
