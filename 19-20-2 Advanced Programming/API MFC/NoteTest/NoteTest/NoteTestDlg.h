
// NoteTestDlg.h: 头文件
//

#pragma once


// CNoteTestDlg 对话框
class CNoteTestDlg : public CDialogEx
{
// 构造
public:
	CNoteTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CFont m_Font;//字体


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_FileText;
	afx_msg void OnFileSave();
	afx_msg void OnSaveAs();
	afx_msg void OnEnChangeEdit1();
	afx_msg void FileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnNewWindow();
	afx_msg void OnClose();
	afx_msg void OnFileExit();
	afx_msg void OnEditUndo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditData();
	afx_msg void OnEditFont();
	afx_msg void OnNoteAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
