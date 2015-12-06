// showmapinfo.cpp : implementation file
//

#include "stdafx.h"
#include "parking management.h"
#include "showmapinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// showmapinfo dialog


showmapinfo::showmapinfo(CWnd* pParent /*=NULL*/)
	: CDialog(showmapinfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(showmapinfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void showmapinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(showmapinfo)
	DDX_Control(pDX, IDC_EXPLORER1, m_webmap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(showmapinfo, CDialog)
	//{{AFX_MSG_MAP(showmapinfo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// showmapinfo message handlers

void showmapinfo::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void showmapinfo::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL showmapinfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path+="\\map\\map.png";
	m_webmap.Navigate(path, NULL, NULL, NULL, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//±à¼­µØÍ¼
void showmapinfo::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path+="\\map\\map.tmx";
	ShellExecute(NULL,TEXT("OPEN"),path,NULL,NULL,SW_SHOWNORMAL);
}
