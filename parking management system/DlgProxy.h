// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__0B8880E0_E95C_4810_90ED_6E39380E0D2A__INCLUDED_)
#define AFX_DLGPROXY_H__0B8880E0_E95C_4810_90ED_6E39380E0D2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParkingmanagementsystemDlg;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlgAutoProxy command target

class CParkingmanagementsystemDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CParkingmanagementsystemDlgAutoProxy)

	CParkingmanagementsystemDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CParkingmanagementsystemDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementsystemDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CParkingmanagementsystemDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CParkingmanagementsystemDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CParkingmanagementsystemDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CParkingmanagementsystemDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__0B8880E0_E95C_4810_90ED_6E39380E0D2A__INCLUDED_)
