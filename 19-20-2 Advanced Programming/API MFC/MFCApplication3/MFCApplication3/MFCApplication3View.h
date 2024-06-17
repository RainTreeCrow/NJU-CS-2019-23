
// MFCApplication3View.h: CMFCApplication3View 类的接口
//

#pragma once

#include <vector>
using namespace std;
const double walk = 5.0;
const double dirX[] = { walk, -walk, -walk, walk };
const double dirY[] = { -walk, -walk, walk, walk };

struct circle {
	double x, y, r, r1, g1, b1, r2, g2, b2;
	int dir;
	circle(double x, double y, double r) {
		this->x = x; this->y = y; this->r = r;
		this->r1 = rand() % 256;
		this->r2 = rand() % 256;
		this->g1 = rand() % 256;
		this->g2 = rand() % 256;
		this->b1 = rand() % 256;
		this->b2 = rand() % 256;
		dir = 0;
	}
};

extern vector<circle> circles;

class CBallView : public CView
{
protected: // 仅从序列化创建
	CBallView() noexcept;
	DECLARE_DYNCREATE(CBallView)

// 特性
public:
	CBallDoc* GetDocument() const;

// 操作
public:
	bool flag_LBTNDown;
	CPoint m_pStart;
	CPoint m_pEnd;

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
	virtual ~CBallView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFCApplication3View.cpp 中的调试版本
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

