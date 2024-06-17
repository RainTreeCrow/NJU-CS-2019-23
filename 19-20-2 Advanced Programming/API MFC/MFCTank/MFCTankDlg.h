
// MFCTankDlg.h: 头文件
//

#pragma once
DWORD static WINAPI MyPaint(LPVOID lpParam);

// CMFCTankDlg 对话框
class CMFCTankDlg : public CDialogEx
{
// 构造
public:
	CMFCTankDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTANK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HDC hdc, mdc, bufdc;
	HBITMAP BackGround, hBitmap, HTank;
	CBitmap Back, Tank;
};
