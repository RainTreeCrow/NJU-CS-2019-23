// FileHelp.cpp: 实现文件
//

#include "stdafx.h"
#include "NoteTest.h"
#include "FileHelp.h"
#include "afxdialogex.h"


// FileHelp 对话框

IMPLEMENT_DYNAMIC(FileHelp, CDialogEx)

FileHelp::FileHelp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

FileHelp::~FileHelp()
{
}

void FileHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	CFont font;
	font.CreateFont(20, 20, 0, 0, FW_NORMAL, FALSE, FALSE,
		FALSE, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_MODERN, _T("华文楷体"));

	GetDlgItem(IDC_STATIC1)->SetFont(&font);

	CString strText;
	strText = "记事本\n华晴1398";
	GetDlgItem(IDC_STATIC3)->SetWindowText(strText);
}


BEGIN_MESSAGE_MAP(FileHelp, CDialogEx)
END_MESSAGE_MAP()


// FileHelp 消息处理程序
