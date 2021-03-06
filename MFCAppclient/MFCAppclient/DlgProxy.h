
// DlgProxy.h: 头文件
//

#pragma once

class CMFCAppclientDlg;


// CMFCAppclientDlgAutoProxy 命令目标

class CMFCAppclientDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMFCAppclientDlgAutoProxy)

	CMFCAppclientDlgAutoProxy();           // 动态创建所使用的受保护的构造函数

// 特性
public:
	CMFCAppclientDlg* m_pDialog;

// 操作
public:

// 重写
	public:
	virtual void OnFinalRelease();

// 实现
protected:
	virtual ~CMFCAppclientDlgAutoProxy();

	// 生成的消息映射函数

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMFCAppclientDlgAutoProxy)

	// 生成的 OLE 调度映射函数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

