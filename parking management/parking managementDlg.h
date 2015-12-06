// parking managementDlg.h : header file
//

#if !defined(AFX_PARKINGMANAGEMENTDLG_H__D95BBE72_D5CB_44A7_900A_8695E96FDF9D__INCLUDED_)
#define AFX_PARKINGMANAGEMENTDLG_H__D95BBE72_D5CB_44A7_900A_8695E96FDF9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementDlg dialog

class CParkingmanagementDlg : public CDialog
{
// Construction
public:
	CParkingmanagementDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CParkingmanagementDlg)
	enum { IDD = IDD_PARKINGMANAGEMENT_DIALOG };
	CEdit	m_car_id;
	CEdit	m_car_surplus;
	CEdit	m_car_sum;
	CListCtrl	m_carbarn_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CParkingmanagementDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuitem32772();
	afx_msg void OnButton3();
	afx_msg void OnMenuitem32771();
	afx_msg void OnMenuitem32773();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKINGMANAGEMENTDLG_H__D95BBE72_D5CB_44A7_900A_8695E96FDF9D__INCLUDED_)
