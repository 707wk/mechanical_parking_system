// parking management system.h : main header file for the PARKING MANAGEMENT SYSTEM application
//

#if !defined(AFX_PARKINGMANAGEMENTSYSTEM_H__EC9BF26C_F84A_4CCF_B2B9_47E628FA35E6__INCLUDED_)
#define AFX_PARKINGMANAGEMENTSYSTEM_H__EC9BF26C_F84A_4CCF_B2B9_47E628FA35E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemApp:
// See parking management system.cpp for the implementation of this class
//

class CParkingmanagementsystemApp : public CWinApp
{
public:
	CParkingmanagementsystemApp();
	~CParkingmanagementsystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementsystemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CParkingmanagementsystemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKINGMANAGEMENTSYSTEM_H__EC9BF26C_F84A_4CCF_B2B9_47E628FA35E6__INCLUDED_)
