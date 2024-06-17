// CDialogInput.cpp: 实现文件
//

#include "pch.h"
#include "Notepad.h"
#include "CDialogInput.h"
#include "afxdialogex.h"


// CDialogInput 对话框

IMPLEMENT_DYNAMIC(CDialogInput, CDialogEx)

CDialogInput::CDialogInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT, pParent)
{

}

CDialogInput::~CDialogInput()
{
}

void CDialogInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}


BEGIN_MESSAGE_MAP(CDialogInput, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT, &CDialogInput::OnEnChangeEdit)
	ON_BN_CLICKED(IDOK, &CDialogInput::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogInput::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialogInput 消息处理程序


BOOL CDialogInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_edit.SetWindowText(strText);
	return TRUE;
}


void CDialogInput::OnEnChangeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strText;
	m_edit.GetWindowText(strText);
	strText = strText;
}


void CDialogInput::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	GetDlgItem(IDC_EDIT)->GetWindowText(strText);
}


void CDialogInput::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
