// car_module_dlg.h : main header file for the CAR_MODULE_DLG application
//

#if !defined(AFX_CAR_MODULE_DLG_H__52E6F048_7744_4467_8AA7_0540E6C7AA49__INCLUDED_)
#define AFX_CAR_MODULE_DLG_H__52E6F048_7744_4467_8AA7_0540E6C7AA49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCar_module_dlgApp:
// See car_module_dlg.cpp for the implementation of this class
//

class CCar_module_dlgApp : public CWinApp
{
public:
	CCar_module_dlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCar_module_dlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCar_module_dlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAR_MODULE_DLG_H__52E6F048_7744_4467_8AA7_0540E6C7AA49__INCLUDED_)
