#if !defined(AFX_ABOUTSOFT_H__B0738F1A_B135_4CA3_B680_199B97ED2278__INCLUDED_)
#define AFX_ABOUTSOFT_H__B0738F1A_B135_4CA3_B680_199B97ED2278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ABOUTSOFT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ABOUTSOFT dialog

class ABOUTSOFT : public CDialog
{
// Construction
public:
	ABOUTSOFT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ABOUTSOFT)
	enum { IDD = IDD_ABOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ABOUTSOFT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ABOUTSOFT)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTSOFT_H__B0738F1A_B135_4CA3_B680_199B97ED2278__INCLUDED_)
