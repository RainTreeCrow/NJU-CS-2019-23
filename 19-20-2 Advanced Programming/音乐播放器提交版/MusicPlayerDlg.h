
// MusicPlayerDlg.h: 头文件
//

#pragma once


// CMusicPlayerDlg 对话框
class CMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CMusicPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	BOOL m_bPlaying;
	TCHAR m_szFullName[MAX_PATH];
	TCHAR m_szShortName[MAX_PATH];
	UINT m_nTotalLen;
	int iPos;
	CListBox* Box;
	bool add;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedControl();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedAdd();
	CListBox m_list_music;
	afx_msg void OnBnClickedDelete();
	CSliderCtrl m_slider;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPre();
	afx_msg void OnBnClickedNext();
	CEdit m_edit_song;
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	CComboBox m_cb;
	afx_msg void OnCbnSelchangeCombo();
	CListBox m_list_like;
	CListBox m_list_recent;
	afx_msg void OnBnClickedLike();
	afx_msg void OnLbnSelchangeFavorite();
	afx_msg void OnLbnSelchangeRecent();
	afx_msg void OnLbnSelchangeMusicList();
};
