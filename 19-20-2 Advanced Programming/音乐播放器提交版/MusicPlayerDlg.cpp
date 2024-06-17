
// MusicPlayerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib,"winmm.lib")

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


// CMusicPlayerDlg 对话框



CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUSICPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSIC_LIST, m_list_music);
	DDX_Control(pDX, IDC_MUSIC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_COMBO, m_cb);
	DDX_Control(pDX, IDC_FAVORITE, m_list_like);
	DDX_Control(pDX, IDC_RECENT, m_list_recent);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CMusicPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_CONTROL, &CMusicPlayerDlg::OnBnClickedControl)
	ON_BN_CLICKED(IDC_STOP, &CMusicPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_ADD, &CMusicPlayerDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CMusicPlayerDlg::OnBnClickedDelete)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PRE, &CMusicPlayerDlg::OnBnClickedPre)
	ON_BN_CLICKED(IDC_NEXT, &CMusicPlayerDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_UP, &CMusicPlayerDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_DOWN, &CMusicPlayerDlg::OnBnClickedDown)
	ON_CBN_SELCHANGE(IDC_COMBO, &CMusicPlayerDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_LIKE, &CMusicPlayerDlg::OnBnClickedLike)
	ON_LBN_SELCHANGE(IDC_FAVORITE, &CMusicPlayerDlg::OnLbnSelchangeFavorite)
	ON_LBN_SELCHANGE(IDC_RECENT, &CMusicPlayerDlg::OnLbnSelchangeRecent)
	ON_LBN_SELCHANGE(IDC_MUSIC_LIST, &CMusicPlayerDlg::OnLbnSelchangeMusicList)
END_MESSAGE_MAP()


// CMusicPlayerDlg 消息处理程序

BOOL CMusicPlayerDlg::OnInitDialog()
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
	m_bPlaying = FALSE;
	m_nTotalLen = 0;
	*m_szFullName = _T('\0');
	*m_szShortName = _T('\0');

	SetTimer(1, 50, NULL);

	m_cb.AddString("列表循环");
	m_cb.AddString("随机播放");
	m_cb.AddString("单曲循环");
	((CComboBox*)GetDlgItem(IDC_COMBO))->SetCurSel(1);
	iPos = 1;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMusicPlayerDlg::OnPaint()
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
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMusicPlayerDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying) {
		CString strCmd;
		DWORD dwErr;
		dwErr = mciSendString(_T("close all"), NULL, MAX_PATH, NULL);
		int nIndex = Box->GetCurSel();
		if (nIndex >= 0) {
			Box->GetText(nIndex, m_szFullName);
			GetShortPathName(m_szFullName, m_szShortName, MAX_PATH);
			strCmd.Format(_T("open %s"), m_szShortName);
			dwErr = mciSendString(strCmd, NULL, MAX_PATH, NULL);
			if (dwErr != 0) {
				TCHAR szBuf[MAX_PATH] = { 0 };
				mciGetErrorString(dwErr, szBuf, MAX_PATH);
				AfxMessageBox(szBuf);
			}
			else {
				strCmd.Format(_T("play %s"), m_szShortName);
				dwErr = mciSendString(strCmd, NULL, MAX_PATH, NULL);
				if (dwErr != 0) {
					TCHAR szBuf[MAX_PATH] = { 0 };
					mciGetErrorString(dwErr, szBuf, MAX_PATH);
					AfxMessageBox(szBuf);
				}
				else {
					TCHAR szReturn[MAX_PATH] = { 0 };
					strCmd.Format(_T("status %s length"), m_szShortName);
					dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
					if (dwErr != 0) {
						TCHAR szBuf[MAX_PATH] = { 0 };
						mciGetErrorString(dwErr, szBuf, MAX_PATH);
						AfxMessageBox(szBuf);
					}
					else {
						m_nTotalLen = _ttoi(szReturn);
						m_slider.SetRange(0, m_nTotalLen, TRUE);
					}
					SetDlgItemText(IDC_EDIT_SONG, m_szFullName);
					if (add)
						m_list_recent.AddString(m_szShortName);
					m_bPlaying = true;
					SetDlgItemText(IDC_CONTROL, _T("暂停"));
				}
			}
		}
	}
	else {
		OnBnClickedStop();
		OnBnClickedPlay();
	}
}


void CMusicPlayerDlg::OnBnClickedControl()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPlaying) {
		CString strCmd;
		DWORD dwErr;
		strCmd.Format(_T("pause %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, MAX_PATH, NULL);
		if (dwErr != 0) {
			TCHAR szBuf[MAX_PATH] = { 0 };
			mciGetErrorString(dwErr, szBuf, MAX_PATH);
			AfxMessageBox(szBuf);
		}
		else {
			m_bPlaying = false;
			SetDlgItemText(IDC_CONTROL, _T("恢复"));
		}
	}
	else {
		CString strCmd;
		DWORD dwErr;
		strCmd.Format(_T("resume %s"), m_szShortName);
		dwErr = mciSendString(strCmd, NULL, MAX_PATH, NULL);
		if (dwErr != 0) {
			TCHAR szBuf[MAX_PATH] = { 0 };
			mciGetErrorString(dwErr, szBuf, MAX_PATH);
			AfxMessageBox(szBuf);
		}
		else {
			m_bPlaying = true;
			SetDlgItemText(IDC_CONTROL, _T("暂停"));
		}
	}
}


void CMusicPlayerDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCmd;
	DWORD dwErr;
	strCmd.Format(_T("stop all", m_szShortName));
	dwErr = mciSendString(strCmd, NULL, MAX_PATH, NULL);
	if (dwErr != 0) {
		TCHAR szBuf[MAX_PATH] = { 0 };
		mciGetErrorString(dwErr, szBuf, MAX_PATH);
		AfxMessageBox(szBuf);
	}
	else {
		dwErr = mciSendString(_T("close all"), NULL, MAX_PATH, NULL);
		m_bPlaying = false;
		SetDlgItemText(IDC_CONTROL, _T("暂停"));
		m_slider.SetPos(0);
	}
}


void CMusicPlayerDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFileFiter[] = "mp3文件(*.mp3)|*.mp3|"
		"wav文件(*.wav)|*.wav|"
		"所有文件(*.*)|*.*|";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT, szFileFiter, this);
	TCHAR* pBuf = new TCHAR[MAX_PATH * 50];
	*pBuf = 0;
	dlg.m_ofn.lpstrFile = pBuf;
	dlg.m_ofn.nMaxFile = MAX_PATH * 50;
	if (dlg.DoModal() == IDOK) {
		POSITION pos = dlg.GetStartPosition();
		CString strFile;
		while (pos != NULL) {
			strFile = dlg.GetNextPathName(pos);
			m_list_music.AddString(strFile);
		}
	}
	GetDlgItem(IDC_PLAY)->EnableWindow(true);
	GetDlgItem(IDC_CONTROL)->EnableWindow(true);
	GetDlgItem(IDC_STOP)->EnableWindow(true);
	GetDlgItem(IDC_PRE)->EnableWindow(true);
	GetDlgItem(IDC_NEXT)->EnableWindow(true);
	delete[] pBuf;
}


void CMusicPlayerDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = Box->GetCurSel();
	if (nIndex >= 0)
		Box->DeleteString(nIndex);
}


void CMusicPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bPlaying) {
		CString strCmd;
		DWORD dwErr;
		TCHAR szReturn[MAX_PATH] = { 0 };
		strCmd.Format(_T("status %s position"), m_szShortName);
		dwErr = mciSendString(strCmd, szReturn, MAX_PATH, NULL);
		if (dwErr != 0) {
			TCHAR szBuf[MAX_PATH] = { 0 };
			mciGetErrorString(dwErr, szBuf, MAX_PATH);
			AfxMessageBox(szBuf);
		}
		else {
			UINT nPosition = _ttoi(szReturn);
			m_slider.SetPos(nPosition);
			if (nPosition == m_nTotalLen) {
				OnBnClickedStop();
				int nIndex = Box->FindString(-1, m_szFullName);
				if (nIndex < 0)
					nIndex = 0;
				else {
					if (iPos == 1) {
						nIndex += 1;
						if (nIndex >= Box->GetCount())
							nIndex = 0;
					}
					else if (iPos == 2)
						nIndex = rand() % Box->GetCount();
				}
				Box->SetCurSel(nIndex);
				OnBnClickedPlay();
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMusicPlayerDlg::OnBnClickedPre()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedStop();
	int nIndex = Box->FindString(-1, m_szFullName);
	if (iPos == 2)
		nIndex = rand() % Box->GetCount();
	else {
		nIndex -= 1;
		if (nIndex < 0)
			nIndex = Box->GetCount() - 1;
	}
	Box->SetCurSel(nIndex);
	OnBnClickedPlay();
}


void CMusicPlayerDlg::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedStop();
	int nIndex = Box->FindString(-1, m_szFullName);
	if (iPos == 2)
		nIndex = rand() % Box->GetCount();
	else {
		nIndex += 1;
		if (nIndex >= Box->GetCount())
			nIndex = 0;
	}
	Box->SetCurSel(nIndex);
	OnBnClickedPlay();
}


void CMusicPlayerDlg::OnBnClickedUp()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD vol;
	waveOutGetVolume(0, &vol);
	vol = vol + 500;
	waveOutSetVolume(0, vol);
}


void CMusicPlayerDlg::OnBnClickedDown()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD vol;
	waveOutGetVolume(0, &vol);
	vol = vol - 500;
	waveOutSetVolume(0, vol);
}


void CMusicPlayerDlg::OnCbnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码
	iPos = ((CComboBox*)GetDlgItem(IDC_COMBO))->GetCurSel();
}


void CMusicPlayerDlg::OnBnClickedLike()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_list_music.GetCurSel();
	if (nIndex >= 0) {
		m_list_music.GetText(nIndex, m_szFullName);
		GetShortPathName(m_szFullName, m_szShortName, MAX_PATH);
		m_list_like.AddString(m_szShortName);
	}
}


void CMusicPlayerDlg::OnLbnSelchangeMusicList()
{
	// TODO: 在此添加控件通知处理程序代码
	Box = &m_list_music;
	add = true;
}


void CMusicPlayerDlg::OnLbnSelchangeFavorite()
{
	// TODO: 在此添加控件通知处理程序代码
	Box = &m_list_like;
	add = true;
}


void CMusicPlayerDlg::OnLbnSelchangeRecent()
{
	// TODO: 在此添加控件通知处理程序代码
	Box = &m_list_recent;
	add = false;
}
