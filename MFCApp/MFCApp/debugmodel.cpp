// debugmodel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApp.h"
#include "debugmodel.h"
#include "afxdialogex.h"


// debugmodel �Ի���

IMPLEMENT_DYNAMIC(debugmodel, CDialogEx)

debugmodel::debugmodel(CWnd* pParent /*=NULL*/)
	: CDialogEx(debugmodel::IDD, pParent)
{

	EnableAutomation();

}

debugmodel::~debugmodel()
{
}

void debugmodel::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void debugmodel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(debugmodel, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &debugmodel::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &debugmodel::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(debugmodel, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_Idebugmodel ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {ABBA8598-9C60-4A1F-90DF-ED4EB9BE8697}
static const IID IID_Idebugmodel =
{ 0xABBA8598, 0x9C60, 0x4A1F, { 0x90, 0xDF, 0xED, 0x4E, 0xB9, 0xBE, 0x86, 0x97 } };

BEGIN_INTERFACE_MAP(debugmodel, CDialogEx)
	INTERFACE_PART(debugmodel, IID_Idebugmodel, Dispatch)
END_INTERFACE_MAP()


// debugmodel ��Ϣ�������

void debugmodel::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void debugmodel::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}
