// CStudentDlg.cpp: 实现文件
//

#include "pch.h"
#include "Students.h"
#include "CStudentDlg.h"
#include "afxdialogex.h"
#include "StudentsDoc.h"


// CStudentDlg 对话框

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STU, pParent)
	, c_name(_T(""))
	, c_index(_T(""))
	, c_sex(_T(""))
	, c_home(_T(""))
	, c_birth(_T(""))
{

}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, c_name);
	DDX_Text(pDX, IDC_INDEX, c_index);
	DDX_CBString(pDX, IDC_SEX, c_sex);
	DDX_Text(pDX, IDC_HOME, c_home);
	DDX_Text(pDX, IDC_BIRTH, c_birth);
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStudentDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CStudentDlg 消息处理程序


void CStudentDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Student temp;
	GetDlgItemText(ID_INDEX, temp.index);
	GetDlgItemText(ID_NAME, temp.name);
	GetDlgItemText(IDC_SEX, temp.sex);
	GetDlgItemText(IDC_BIRTH, temp.birthday);
	GetDlgItemText(IDC_HOME, temp.home);
	Students.push_back(temp);
	new_stu = &temp;
}


void CStudentDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
