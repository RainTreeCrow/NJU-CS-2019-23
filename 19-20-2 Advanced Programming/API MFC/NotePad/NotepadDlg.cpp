
// NotepadDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Notepad.h"
#include "NotepadDlg.h"
#include "afxdialogex.h"
#include "CDialogInput.h"
#pragma warning (disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNotepadDlg 对话框



CNotepadDlg::CNotepadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotepadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_FileText);
	DDX_Control(pDX, IDC_FILE, m_FileText);
	DDX_Control(pDX, IDC_FILE, m_FileText);
}

BEGIN_MESSAGE_MAP(CNotepadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SAVE, &CNotepadDlg::OnSave)
	ON_EN_CHANGE(IDC_FILE, &CNotepadDlg::OnEnChangeFile)
	ON_COMMAND(ID_OPEN, &CNotepadDlg::OnOpen)
	ON_COMMAND(ID_FONT, &CNotepadDlg::OnFont)
	ON_COMMAND(ID_COLOR, &CNotepadDlg::OnColor)
	ON_COMMAND(ID_TEXT, &CNotepadDlg::OnText)
END_MESSAGE_MAP()


// CNotepadDlg 消息处理程序

BOOL CNotepadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	AfxInitRichEdit();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNotepadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNotepadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNotepadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNotepadDlg::FileSave()
{
	CString  strText = "";
	char write[10000];
	if ((strOpenPath.Right(4) != ".TXT") && (strOpenPath.Right(4) != ".txt"))
		strOpenPath += ".TXT";
	CFile file(_T(strOpenPath), CFile::modeCreate | CFile::modeWrite);
	m_FileText.GetWindowText(strText);
	strcpy(write, strText);
	file.Write(write, strText.GetLength());
	strOld = strNew;
	Save = 1;
	file.Close();
}


void CNotepadDlg::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	if (strOpenPath == "") {
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"All Files(*.TXT)|*.TXT||", AfxGetMainWnd());
		CString strPathAs, strText = "";
		char write[10000];
		if (dlg.DoModal() == IDOK) {
			strPathAs = dlg.GetPathName();
			strOpenPath = strPathAs;
			if ((strPathAs.Right(4) != ".TXT") && (strPathAs.Right(4) != ".txt"))
				strPathAs += ".TXT";
			CFile file(_T(strPathAs), CFile::modeCreate | CFile::modeWrite);
			m_FileText.GetWindowText(strText);
			strcpy(write, strText);
			file.Write(write, strText.GetLength());
			strOld = strNew;
			Save = 1;
			file.Close();
		}
		else
			Save = 0;
	}
	else
		FileSave();
}


void CNotepadDlg::OnEnChangeFile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strText;
	m_FileText.GetWindowText(strText);
	strNew = strText;
}


void CNotepadDlg::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	Save = 1;
	if (strOld != strNew) {
		if (MessageBox("内容已改变要保存吗？", NULL, MB_YESNO | MB_ICONQUESTION) == IDYES) {
			OnSave();
			if (Save == 0)  return;
		}
	}
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||", AfxGetMainWnd());
	CString strText = "";
	if (dlg.DoModal() == IDOK) {
		strOpenPath = dlg.GetPathName();
		CFile file(strOpenPath, CFile::modeRead);
		char read[10000];
		file.Read(read, 10000);
		for (int i = 0; i < file.GetLength(); i++) {
			strText += read[i];
		}
		strOld = strText;
		strNew = strText;
		file.Close();
		m_FileText.SetWindowText(strOld);
	}
}


void CNotepadDlg::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CHARFORMAT cf = { 0 };
	cf.cbSize = sizeof(cf);
	m_FileText.GetSelectionCharFormat(cf);
	CFontDialog dlg(cf);
	if (dlg.DoModal() == IDOK) {
		dlg.GetCharFormat(cf);
		m_FileText.SetSelectionCharFormat(cf);
	}
}


void CNotepadDlg::OnColor()
{
	// TODO: 在此添加命令处理程序代码
	CHARFORMAT cf = { 0 };
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;
	m_FileText.GetSelectionCharFormat(cf);
	CColorDialog dlg(cf.crTextColor);
	if (dlg.DoModal() == IDOK) {
		cf.crTextColor = dlg.GetColor();
		m_FileText.SetSelectionCharFormat(cf);
	}
}


void CNotepadDlg::OnText()
{
	// TODO: 在此添加命令处理程序代码
	CDialogInput dlg;
	dlg.strText = strNew;
	if (dlg.DoModal() == IDOK) {
		strNew = dlg.strText;
		m_FileText.SetWindowText(strNew);
	}
}
