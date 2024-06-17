
// NoteTestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "NoteTest.h"
#include "NoteTestDlg.h"
#include "afxdialogex.h"
#include "FileHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString strOld;           //Eide开始时的内容
CString strNew;			  //Edit改变时的内容
CString strOpenPath = "";   //打开文件时的路径
int Save = 0;               //记录保存文件时是否按下确定（确定：Save=1；取消：Save=0）


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


// CNoteTestDlg 对话框



CNoteTestDlg::CNoteTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTETEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNoteTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_FileText);
}

BEGIN_MESSAGE_MAP(CNoteTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_SAVE, &CNoteTestDlg::OnFileSave)
	ON_COMMAND(ID_SAVE_AS, &CNoteTestDlg::OnSaveAs)
	ON_EN_CHANGE(IDC_EDIT1, &CNoteTestDlg::OnEnChangeEdit1)
	ON_COMMAND(ID_FILE_OPEN, &CNoteTestDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CNoteTestDlg::OnFileNew)
	ON_COMMAND(ID_NEW_WINDOW, &CNoteTestDlg::OnNewWindow)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_EXIT, &CNoteTestDlg::OnFileExit)
	ON_COMMAND(ID_EDIT_UNDO, &CNoteTestDlg::OnEditUndo)
	ON_COMMAND(ID_EDIT_CUT, &CNoteTestDlg::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CNoteTestDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CNoteTestDlg::OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, &CNoteTestDlg::OnEditDelete)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CNoteTestDlg::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_DATA, &CNoteTestDlg::OnEditData)
	ON_COMMAND(ID_EDIT_FONT, &CNoteTestDlg::OnEditFont)
	ON_COMMAND(ID_Note_About, &CNoteTestDlg::OnNoteAbout)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNoteTestDlg 消息处理程序

BOOL CNoteTestDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNoteTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNoteTestDlg::OnPaint()
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
HCURSOR CNoteTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--文件--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//保存子函数
void CNoteTestDlg::FileSave()
{
	CString  strText = "";
	char write[10000];

	//判断文件名中是否含有.TXT或.txt的扩展名
	if ((strOpenPath.Right(4) != ".TXT") && (strOpenPath.Right(4) != ".txt"))
		strOpenPath += ".TXT";//文件名中没有包含扩展名，在最后添加扩展名

	CFile file(_T(strOpenPath), CFile::modeCreate | CFile::modeWrite);
	m_FileText.GetWindowText(strText);          //获取编辑框内的内容
	strcpy(write, strText);						//复制编辑框内的内容
	file.Write(write, strText.GetLength());     //写入
	strOld = strNew;                            //将最开始时记录编辑框的内容更新
	Save = 1;									//记录保存已经确定
	file.Close();
}


//保存
void CNoteTestDlg::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
		//判断文件是否已保存过
	if (strOpenPath == "")
	{
		//文件未保存过，跳转到另保存函数
		OnSaveAs();
	}
	else
	{
		//文件已保存过，跳转到保存函数
		FileSave();
	}
}

//另存为
void CNoteTestDlg::OnSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||", AfxGetMainWnd()); //选择保存的路径及文件名
	CString strPathAs, strText = "";
	char write[10000];
	if (dlg.DoModal() == IDOK)  //判断另保存的确定按键是否按下
	{
		//另保存按键按下
		strPathAs = dlg.GetPathName();  //获取路径及文件名（和扩展名）
		strOpenPath = strPathAs;        //记录当前的文件

		//判断文件名中是否含有.TXT或.txt的扩展名
		if ((strPathAs.Right(4) != ".TXT") && (strPathAs.Right(4) != ".txt"))
			strPathAs += ".TXT";//文件名中没有包含扩展名，在最后添加扩展名

		CFile file(_T(strPathAs), CFile::modeCreate | CFile::modeWrite);
		m_FileText.GetWindowText(strText);       //获取编辑框内的内容
		strcpy(write, strText);                  //复制编辑框内的内容
		file.Write(write, strText.GetLength());  //写入
		strOld = strNew;                         //将最开始时记录编辑框的内容更新
		Save = 1;                                //记录保存已经确定
		file.Close();
	}
	else
	{
		Save = 0;    //记录保存已取消
	}
}

//编辑框消息
void CNoteTestDlg::OnEnChangeEdit1()
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



//打开
void CNoteTestDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	Save = 1;

	//判断编辑框的内容是否发生了改变
	if (strOld != strNew)
	{
		//编辑框的内容已发生了改变
		//判断是否要保存
		if (MessageBox("内容已改变要保存吗？", NULL, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			//要保存改变的内容，跳转到实现菜单下保存的功能函数
			OnFileSave();

			//判断在保存的过程中是否按下了取消
			if (Save == 0)  return;   //按下了取消，退出打开功能
		}
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"All Files(*.TXT)|*.TXT||", AfxGetMainWnd());//选择打开文件的路径及文件名
	CString strText = "";

	if (dlg.DoModal() == IDOK)                      //判断另保存的确定按键是否按下
	{
		strOpenPath = dlg.GetPathName();            //获取打开文件的路径和文件名及扩展名   

		CFile file(strOpenPath, CFile::modeRead);
		char read[10000];
		file.Read(read, 10000);

		//读取文的内容
		for (int i = 0; i < file.GetLength(); i++)
		{
			strText += read[i];
		}
		strOld = strText;                   //记录打开时的文件内容
		strNew = strText;
		file.Close();
		m_FileText.SetWindowText(strOld);   //在编辑框内显示文件的内容
	}
}

//新建
void CNoteTestDlg::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	Save = 1;
	if (strOld != strNew)   //判断编辑框内的内容是否改变了
	{
		//编辑框内的内容已改变
		//判断是否要保存
		if (MessageBox("内容已改变要保存吗？", NULL, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			//要保存编辑框内改变的内容
			if (strOpenPath == "") //判断是否是已经保存过了的文件
			{
				//文件没有保存过，转到另保存函数，选择保存的路径及文件名
				OnSaveAs();

			}
			else
			{
				//文件已保存过了，转到保存函数
				FileSave();
			}
		}
	}

	//判断在新建文件时是否按下了确定
	if (Save == 1)
	{
		//确定了新建文件
		strOld = "";       //清除之前所记录的内容
		strNew = "";
		strOpenPath = "";  //清除之前的文件路径
		m_FileText.SetWindowText(strOld); //清空编辑框内的内容
	}

}

//新窗口
void CNoteTestDlg::OnNewWindow()
{
	// TODO: 在此添加命令处理程序代码
	WinExec(AfxGetApp()->m_pszExeName, SW_SHOW);
}


//主窗口退出
void CNoteTestDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int YesNo;  //记录已改变的内容是“是”或“否”保存,或“取消”退出
	if (strOld != strNew) //发的编辑框内的内容是否发生了改变
	{
		//编辑框内的内容发生了改变
		YesNo = MessageBox("内容已改变要保存吗？", NULL, MB_YESNOCANCEL | MB_ICONQUESTION);

		//判断是否要保存
		if (YesNo == IDYES)   //确定要保存
		{
			if (strOpenPath == "")  //判断是否是已保存过的文件
			{
				//文件没有保存过，跳转到另保存函数
				OnSaveAs();
			}
			else
			{
				//文件已保存过，跳转到保存函数
				FileSave();
			}
			if (Save == 1) //判断是否已按下确定保存，若按下了取消，将不关闭窗口
			{
				//按下了确定保存，关闭窗口
				CDialogEx::OnClose();
			}

		}
		else if (YesNo == IDNO)  //按下“否”(不保存改变的内容),关闭窗口
		{
			CDialogEx::OnClose();
		}
		else if (YesNo == IDCANCEL)   //按下取消
		{
			Save = 0;
		}
	}
	else
	{
		//编辑框内的内容没有发生改变，关闭窗口
		CDialogEx::OnClose();
	}
}

//退出(菜单下)
void CNoteTestDlg::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	Save = 1;

	OnClose();

	//判断在退出的过程中是否按下了取消
	if (Save == 1) EndDialog(IDCANCEL);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--编辑--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//撤销
void CNoteTestDlg::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->Undo();
}

//剪切
void CNoteTestDlg::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->Cut();
}

//复制
void CNoteTestDlg::OnEditCopy()
{
	// TODO: 在此添加命令处理程序代码
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->Copy();
}


//粘贴
void CNoteTestDlg::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->Paste();
}


//删除
void CNoteTestDlg::OnEditDelete()
{
	// TODO: 在此添加命令处理程序代码
	CEdit * pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->Clear();
}

//全选
void CNoteTestDlg::OnEditSelectAll()
{
	// TODO: 在此添加命令处理程序代码
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->SetSel(0, -1);
}

//时间&日期
void CNoteTestDlg::OnEditData()
{
	// TODO: 在此添加命令处理程序代码
	CTime t = CTime::GetCurrentTime();

	CString str = t.Format("%Y年%m月%d日 %H:%M:%S");
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->ReplaceSel(str, TRUE);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%--格式--%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//字体
void CNoteTestDlg::OnEditFont()
{
	// TODO: 在此添加命令处理程序代码
	CFont* TempFont = m_FileText.GetFont(); //获取编辑框当前字体

	LOGFONT LogFont;

	TempFont->GetLogFont(&LogFont);

	CFontDialog dlg(&LogFont);           //初始化字体信息

	if (dlg.DoModal() == IDOK)
	{
		m_Font.Detach();
		LOGFONT temp;
		dlg.GetCurrentFont(&temp);        //获取当前字体信息
		m_Font.CreateFontIndirect(&temp); //直接创建字体
		m_FileText.SetFont(&m_Font);          //设置字体
	}
}

//关于记事本
void CNoteTestDlg::OnNoteAbout()
{
	// TODO: 在此添加命令处理程序代码
	FileHelp dlg;
	dlg.DoModal(); //创建模态对话框
}


void CNoteTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CWnd* pEdit = GetDlgItem(IDC_EDIT1);
	if (pEdit)
		pEdit->MoveWindow(0, 0, cx, cy);
}
