#pragma once


// CDialogInput 对话框

class CDialogInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogInput)

public:
	CDialogInput(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogInput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString strText = "";
	CEdit m_edit;
	afx_msg void OnEnChangeEdit();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
