// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "parking management system.h"
#include "DlgProxy.h"
#include "parking management systemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlgAutoProxy

IMPLEMENT_DYNCREATE(CParkingmanagementsystemDlgAutoProxy, CCmdTarget)

CParkingmanagementsystemDlgAutoProxy::CParkingmanagementsystemDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CParkingmanagementsystemDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CParkingmanagementsystemDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CParkingmanagementsystemDlgAutoProxy::~CParkingmanagementsystemDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CParkingmanagementsystemDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CParkingmanagementsystemDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CParkingmanagementsystemDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CParkingmanagementsystemDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CParkingmanagementsystemDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IParkingmanagementsystem to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B304C1C1-CD84-4CEA-8B16-F89EC840F8AD}
static const IID IID_IParkingmanagementsystem =
{ 0xb304c1c1, 0xcd84, 0x4cea, { 0x8b, 0x16, 0xf8, 0x9e, 0xc8, 0x40, 0xf8, 0xad } };

BEGIN_INTERFACE_MAP(CParkingmanagementsystemDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CParkingmanagementsystemDlgAutoProxy, IID_IParkingmanagementsystem, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {FE3A4693-8122-4837-B9D2-93BA87450BCD}
IMPLEMENT_OLECREATE2(CParkingmanagementsystemDlgAutoProxy, "Parkingmanagementsystem.Application", 0xfe3a4693, 0x8122, 0x4837, 0xb9, 0xd2, 0x93, 0xba, 0x87, 0x45, 0xb, 0xcd)

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlgAutoProxy message handlers
