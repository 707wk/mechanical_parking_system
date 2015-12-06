// parking managementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "parking management.h"
#include "parking managementDlg.h"
#include "showmapinfo.h"
#include "ABOUTSOFT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementDlg dialog

CParkingmanagementDlg::CParkingmanagementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParkingmanagementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParkingmanagementDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CParkingmanagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParkingmanagementDlg)
	DDX_Control(pDX, IDC_EDIT1, m_car_id);
	DDX_Control(pDX, IDC_EDIT2, m_car_surplus);
	DDX_Control(pDX, IDC_EDIT3, m_car_sum);
	DDX_Control(pDX, IDC_LIST1, m_carbarn_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParkingmanagementDlg, CDialog)
	//{{AFX_MSG_MAP(CParkingmanagementDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParkingmanagementDlg message handlers

BOOL CParkingmanagementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//设置列表主题
	m_carbarn_list.SetExtendedStyle(
		LVS_EX_FLATSB				// 扁平风格滚动
        | LVS_EX_FULLROWSELECT		// 允许正航选中
        | LVS_EX_GRIDLINES			// 画出网格线
		);

	char titlename[][20]={"编号","车库名","状态","耗时","容量","已存车辆","层数","列数","横轴速度","纵轴速度"};
	for(int i=0;i<10;i++)
	{
		m_carbarn_list.InsertColumn(i,titlename[i],LVCFMT_CENTER, 70,0);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CParkingmanagementDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CParkingmanagementDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CParkingmanagementDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CParkingmanagementDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

//编辑地图
void CParkingmanagementDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	CString path;
	GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	path = path.Left(pos);
	path+="\\map\\map.tmx";
	ShellExecute(NULL,TEXT("OPEN"),path,NULL,NULL,SW_SHOWNORMAL);
}

/*////////////////////////////////////////////////////////////////////////
//开启一个线程
struct threadInfo 
{
	UINT nMilliSecond ;
	CProgressCtrl* pctrlProgress ;
}Info;

UINT Threadcheckupdate(LPVOID lpParam)
{
	showmapinfo dlg;
	dlg.DoModal();
	return 0;
}
*/////////////////////////////////////////////////////////////////////////
//显示地图
void CParkingmanagementDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	/*CWinThread* pThread ;
	pThread=AfxBeginThread(Threadcheckupdate,&Info);*/
	showmapinfo dlg;
	dlg.DoModal();
}

void CParkingmanagementDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	OnCancel();
}

//about
void CParkingmanagementDlg::OnMenuitem32773() 
{
	// TODO: Add your command handler code here
	ABOUTSOFT dlg;
	dlg.DoModal();
}
