
// InputAndShowView.h: CInputAndShowView 类的接口
//

#pragma once


class CInputAndShowView : public CView
{
protected: // 仅从序列化创建
	CInputAndShowView() noexcept;
	DECLARE_DYNCREATE(CInputAndShowView)

// 特性
public:
	CInputAndShowDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CInputAndShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // InputAndShowView.cpp 中的调试版本
inline CInputAndShowDoc* CInputAndShowView::GetDocument() const
   { return reinterpret_cast<CInputAndShowDoc*>(m_pDocument); }
#endif

