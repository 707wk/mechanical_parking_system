// parking management systemDlg.h : header file
//
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#if !defined(AFX_PARKINGMANAGEMENTSYSTEMDLG_H__FF645521_0785_4342_A124_9C0552124F11__INCLUDED_)
#define AFX_PARKINGMANAGEMENTSYSTEMDLG_H__FF645521_0785_4342_A124_9C0552124F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParkingmanagementsystemDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementsystemDlg dialog

class CParkingmanagementsystemDlg : public CDialog
{
	DECLARE_DYNAMIC(CParkingmanagementsystemDlg);
	friend class CParkingmanagementsystemDlgAutoProxy;

// Construction
public:
	void setinfo(char* str);
	CParkingmanagementsystemDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CParkingmanagementsystemDlg();

// Dialog Data
	//{{AFX_DATA(CParkingmanagementsystemDlg)
	enum { IDD = IDD_PARKINGMANAGEMENTSYSTEM_DIALOG };
	CEdit	m_carinfo;
	CEdit	m_carplate;
	CComboBox	m_list_input;
	CEdit	m_info;
	CButton	m_startend;
	CEdit	m_link_info;
	CEdit	m_freecar;
	CEdit	m_sumcar;
	CListCtrl	m_list_error;
	CListCtrl	m_list_garage;
	//}}AFX_DATA

	int sumcar;
	int spendcar;
	//char sendstr[255];
	HANDLE thread01;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementsystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void update_list();
	CParkingmanagementsystemDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CParkingmanagementsystemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuitem32774();
	afx_msg void OnMenuitem32772();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton1();
	afx_msg void OnMenuitem32771();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKINGMANAGEMENTSYSTEMDLG_H__FF645521_0785_4342_A124_9C0552124F11__INCLUDED_)
