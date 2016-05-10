#pragma once


// debugmodel 对话框

class debugmodel : public CDialogEx
{
	DECLARE_DYNAMIC(debugmodel)

public:
	debugmodel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~debugmodel();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
