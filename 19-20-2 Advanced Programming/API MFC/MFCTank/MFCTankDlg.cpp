
// MFCTankDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCTank.h"
#include "MFCTankDlg.h"
#include "afxdialogex.h"

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


// CMFCTankDlg 对话框



CMFCTankDlg::CMFCTankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTANK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTankDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	//ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCTankDlg 消息处理程序

BOOL CMFCTankDlg::OnInitDialog()
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
	int nFullWidth = GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight = GetSystemMetrics(SM_CXSCREEN);
	MoveWindow(0, 0, nFullWidth, nFullHeight);
	
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MyPaint, this, 0, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTankDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

/*void CMFCTankDlg::OnPaint()
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
}*/

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCTankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD static WINAPI MyPaint(LPVOID lpParam)
{
	CMFCTankDlg* c = (CMFCTankDlg*)lpParam;
	HWND hWnd = c->GetSafeHwnd();
	c->hdc = ::GetDC(hWnd);
	c->mdc = ::CreateCompatibleDC(c->hdc);
	c->bufdc = ::CreateCompatibleDC(c->hdc);
	RECT rect;
	::GetWindowRect(hWnd, &rect);
	c->hBitmap = ::CreateCompatibleBitmap(c->hdc, rect.right, rect.bottom);
	SelectObject(c->mdc, c->hBitmap);
	c->Back.LoadBitmap(IDB_BITMAP1);
	c->BackGround = HBITMAP(c->Back);
	c->Tank.LoadBitmap(IDB_BITMAP2);
	c->HTank = HBITMAP(c->Tank);
	while (true)
	{
		SelectObject(c->bufdc, c->BackGround);
		BitBlt(c->mdc, 0, 0, rect.right, rect.bottom, c->bufdc, 0, 0, SRCCOPY);
		SelectObject(c->bufdc, c->HTank);
		BitBlt(c->mdc, 100, 200, 50, 50, c->bufdc, 0, 0, SRCCOPY);
		BitBlt(c->hdc, 0, 0, rect.right, rect.bottom, c->bufdc, 0, 0, SRCCOPY);
		::Sleep(1);
	}
	::ReleaseDC(hWnd, c->hdc);
	::DeleteDC(c->mdc);
	::DeleteDC(c->bufdc);
	return TRUE;
}