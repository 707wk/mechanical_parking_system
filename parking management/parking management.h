// parking management.h : main header file for the PARKING MANAGEMENT application
//

#if !defined(AFX_PARKINGMANAGEMENT_H__4C2D4AE9_9581_4300_82C3_CEEB911EDDF3__INCLUDED_)
#define AFX_PARKINGMANAGEMENT_H__4C2D4AE9_9581_4300_82C3_CEEB911EDDF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "parking managementDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementApp:
// See parking management.cpp for the implementation of this class
//

class CParkingmanagementApp : public CWinApp
{
public:
	CParkingmanagementApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CParkingmanagementApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKINGMANAGEMENT_H__4C2D4AE9_9581_4300_82C3_CEEB911EDDF3__INCLUDED_)
