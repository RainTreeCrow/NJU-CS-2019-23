#pragma once


// CStudentDlg 对话框

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString c_name;
	CString c_index;
	CString c_sex;
	CString c_home;
	CString c_birth;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
