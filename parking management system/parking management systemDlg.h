// parking management systemDlg.h : header file
//

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
	CParkingmanagementsystemDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CParkingmanagementsystemDlg();

// Dialog Data
	//{{AFX_DATA(CParkingmanagementsystemDlg)
	enum { IDD = IDD_PARKINGMANAGEMENTSYSTEM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParkingmanagementsystemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARKINGMANAGEMENTSYSTEMDLG_H__FF645521_0785_4342_A124_9C0552124F11__INCLUDED_)
