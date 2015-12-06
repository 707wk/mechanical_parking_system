//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_SHOWMAPINFO_H__735D715C_F2CF_477B_846F_8608F089D977__INCLUDED_)
#define AFX_SHOWMAPINFO_H__735D715C_F2CF_477B_846F_8608F089D977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// showmapinfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// showmapinfo dialog

class showmapinfo : public CDialog
{
// Construction
public:
	showmapinfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(showmapinfo)
	enum { IDD = IDD_SHOWMAPINFO };
	CWebBrowser2	m_webmap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(showmapinfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(showmapinfo)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWMAPINFO_H__735D715C_F2CF_477B_846F_8608F089D977__INCLUDED_)
