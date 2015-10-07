// car_module_dlgDlg.h : header file
//

#if !defined(AFX_CAR_MODULE_DLGDLG_H__29DD8818_DB6E_4FFC_B91B_A1E2A2B224D3__INCLUDED_)
#define AFX_CAR_MODULE_DLGDLG_H__29DD8818_DB6E_4FFC_B91B_A1E2A2B224D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "car_module.h"

/////////////////////////////////////////////////////////////////////////////
// CCar_module_dlgDlg dialog

class CCar_module_dlgDlg : public CDialog
{
// Construction
public:
	CCar_module_dlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCar_module_dlgDlg)
	enum { IDD = IDD_CAR_MODULE_DLG_DIALOG };
	CEdit	m_mac;
	CEdit	m_cols;
	CEdit	m_rows;
	CEdit	m_speedcols;
	CEdit	m_speedrows;
	CEdit	m_finish;
	CEdit	m_sum;
	CEdit	m_carid;
	car_module garage;
	CButton* btn;
	HICON m_hicnok;
	HICON m_hicnno;
	HICON m_hicncar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCar_module_dlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void upinfodate();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCar_module_dlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAR_MODULE_DLGDLG_H__29DD8818_DB6E_4FFC_B91B_A1E2A2B224D3__INCLUDED_)
