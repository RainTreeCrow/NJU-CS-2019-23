
// MFCApplicationDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <cmath>
using std::vector;
vector<POINT> points;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CString plus(CString num1, CString num2);
CString minus(CString num1, CString num2);
CString multiply(CString num1, CString num2);
CString division(CString num1, CString num2);
CString toCString(int num);
int toInt(CString num);
void calcLongestDistance(POINT& p1, POINT& p2);

// CMFCApplicationDlg 对话框



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLUS, &CMFCApplicationDlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MINUS, &CMFCApplicationDlg::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_MULTIPLY, &CMFCApplicationDlg::OnBnClickedMultiply)
	ON_BN_CLICKED(IDC_DIVISION, &CMFCApplicationDlg::OnBnClickedDivision)
	ON_COMMAND(ID_PLUS, &CMFCApplicationDlg::OnPlus)
	ON_COMMAND(ID_MINUS, &CMFCApplicationDlg::OnMinus)
	ON_COMMAND(ID_MULTIPLY, &CMFCApplicationDlg::OnMultiply)
	ON_COMMAND(ID_DIVISION, &CMFCApplicationDlg::OnDivision)
	ON_COMMAND(ID_POINT, &CMFCApplicationDlg::OnPoint)
	ON_COMMAND(ID_DISTANCE, &CMFCApplicationDlg::OnDistance)
	ON_COMMAND(ID_LETTER, &CMFCApplicationDlg::OnLetter)
	ON_COMMAND(ID_EXIT, &CMFCApplicationDlg::OnExit)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCApplicationDlg 消息处理程序

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	menu.LoadMenuW(IDR_MENU1);
	SetMenu(&menu);
	this->GetSafeHwnd();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplicationDlg::OnPaint()
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
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCApplicationDlg::OnBnClickedPlus()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strA, strB;
	// TODO: 在此添加命令处理程序代码
	GetDlgItemText(IDC_EDITNUM1, strA);
	GetDlgItemText(IDC_EDITNUM2, strB);
	AfxMessageBox(plus(strA, strB));
}


void CMFCApplicationDlg::OnBnClickedMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strA, strB;
	// TODO: 在此添加命令处理程序代码
	GetDlgItemText(IDC_EDITNUM1, strA);
	GetDlgItemText(IDC_EDITNUM2, strB);
	AfxMessageBox(minus(strA, strB));
}


void CMFCApplicationDlg::OnBnClickedMultiply()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strA, strB;
	// TODO: 在此添加命令处理程序代码
	GetDlgItemText(IDC_EDITNUM1, strA);
	GetDlgItemText(IDC_EDITNUM2, strB);
	AfxMessageBox(multiply(strA, strB));
}


void CMFCApplicationDlg::OnBnClickedDivision()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strA, strB;
	// TODO: 在此添加命令处理程序代码
	GetDlgItemText(IDC_EDITNUM1, strA);
	GetDlgItemText(IDC_EDITNUM2, strB);
	AfxMessageBox(division(strA, strB));
}



void CMFCApplicationDlg::OnPlus()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_PLUS)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnMinus()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_MINUS)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnMultiply()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_MULTIPLY)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnDivision()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_DIVISION)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnPoint()
{
	// TODO: 在此添加命令处理程序代码
	
	GetDlgItem(IDC_SHOW1)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnDistance()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_DISTANCE)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnLetter()
{
	// TODO: 在此添加命令处理程序代码
	GetDlgItem(IDC_LETTER)->ShowWindow(TRUE);
}


void CMFCApplicationDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}

int toInt(CString num) {
	int sum = 0;
	int len = num.GetLength();
	for (int i = 0; i < len; i++) {
		sum = sum * 10 + (num[i] - '0');
	}
	return sum;
}
CString toCString(int num) {
	CString result;
	if (num == 0) { result = "0"; return result; }
	int temp = num;
	int len = 0;
	while (temp > 0) { len++; temp = temp / 10; }
	char tempstr[100];
	tempstr[len] = 0;
	for (int i = len - 1; i >= 0; i--) {
		tempstr[i] = (num % 10 + '0');
		num = num / 10;
	}
	result = tempstr;
	return result;
}

CString plus(CString num1, CString num2) {
	int ans = toInt(num1) + toInt(num2);
	return toCString(ans);
}

CString minus(CString num1, CString num2) {
	int ans = toInt(num1) - toInt(num2);
	return toCString(ans);
}

CString multiply(CString num1, CString num2) {
	int ans = toInt(num1) * toInt(num2);
	return toCString(ans);
}

CString division(CString num1, CString num2) {
	int ans = toInt(num1) / toInt(num2);
	return toCString(ans);
}

void calcLongestDistance(POINT& p1, POINT& p2) {
	if (points.size() == 0) { return; }
	POINT ansp1 = points[0], ansp2 = points[0];
	double distance = 0.0;
	for (int i = 0; i < points.size(); i++) {
		for (int j = 0; j < points.size(); j++) {
			if (i == j) { continue; }
			double newdis = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2);
			if (newdis > distance) {
				distance = newdis;
				ansp1 = points[i];
				ansp2 = points[j];
			}
		}
	}
	p1 = ansp1;
	p2 = ansp2;
}

void CMFCApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString str = CString("x: ") + toCString(point.x) + CString(", y:") + toCString(point.y);
	SetDlgItemText(IDC_POINT, str);
	points.push_back(point);
	POINT p1, p2;
	calcLongestDistance(p1, p2);
	CString str2 = CString("x1: ") + toCString(p1.x) + CString(", y1:") + toCString(p1.y) + \
		CString("; x2: ") + toCString(p2.x) + CString(", y2:") + toCString(p2.y);
	SetDlgItemText(IDC_DISTANCE, str2);

	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CMFCApplicationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		SetDlgItemText(IDC_LETTER, CString("ASCII: ") + toCString((int)pMsg->wParam));
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
