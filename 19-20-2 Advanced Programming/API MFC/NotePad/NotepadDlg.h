
// NotepadDlg.h: 头文件
//

#pragma once


// CNotepadDlg 对话框
class CNotepadDlg : public CDialogEx
{
// 构造
public:
	CNotepadDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont m_Font;
public:
	CString strOld = "";
	CString strNew = "";
	CString strOpenPath = "";
	int Save = 0;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_FileText;
	afx_msg void OnSave();
	afx_msg void OnEnChangeFile();
	afx_msg void FileSave();
	afx_msg void OnOpen();
	afx_msg void OnFont();
	afx_msg void OnColor();
	afx_msg void OnText();
};
