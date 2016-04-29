#if !defined(AFX_DEBUGMODEL_H__94571C48_AD84_4073_9354_81B6A1C3566D__INCLUDED_)
#define AFX_DEBUGMODEL_H__94571C48_AD84_4073_9354_81B6A1C3566D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// debugmodel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// debugmodel dialog

class debugmodel : public CDialog
{
// Construction
public:
	debugmodel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(debugmodel)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_col;
	CEdit	m_row;
	CComboBox	m_garage_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(debugmodel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(debugmodel)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void savecar();
	afx_msg void delcar();
	afx_msg void stop();
	afx_msg void reset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGMODEL_H__94571C48_AD84_4073_9354_81B6A1C3566D__INCLUDED_)
