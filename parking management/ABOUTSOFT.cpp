// ABOUTSOFT.cpp : implementation file
//

#include "stdafx.h"
#include "parking management.h"
#include "ABOUTSOFT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ABOUTSOFT dialog


ABOUTSOFT::ABOUTSOFT(CWnd* pParent /*=NULL*/)
	: CDialog(ABOUTSOFT::IDD, pParent)
{
	//{{AFX_DATA_INIT(ABOUTSOFT)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ABOUTSOFT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ABOUTSOFT)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ABOUTSOFT, CDialog)
	//{{AFX_MSG_MAP(ABOUTSOFT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ABOUTSOFT message handlers

void ABOUTSOFT::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ABOUTSOFT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
