
// MFCAppclient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCAppclientApp: 
// �йش����ʵ�֣������ MFCAppclient.cpp
//

class CMFCAppclientApp : public CWinApp
{
public:
	CMFCAppclientApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppclientApp theApp;