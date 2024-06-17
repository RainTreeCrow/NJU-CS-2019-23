
// MFCApplication3View.cpp: CMFCApplication3View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


vector<circle> circles;

// CMFCApplication3View

IMPLEMENT_DYNCREATE(CBallView, CView)

BEGIN_MESSAGE_MAP(CBallView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CBallView::CBallView() noexcept
{
	// TODO: 在此处添加构造代码
	srand(time(0));
}

CBallView::~CBallView()
{
}

BOOL CBallView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication3View 绘图

void CBallView::OnDraw(CDC* /*pDC*/)
{
	CBallDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC* pDC = GetDC();

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetROP2(R2_XORPEN);
	//m_pEnd = point;
	for (int i = 0; i < circles.size(); i++) {
		circle& c = circles[i];
		CBrush fillbrush;
		pDC->SelectObject(CPen(0, 1, RGB(c.r2, c.g2, c.b2)));
		pDC->Ellipse(c.x - c.r, c.y - c.r, c.x + c.r, c.y + c.r);
		fillbrush.CreateSolidBrush(RGB(c.r1, c.g1, c.b1));
		pDC->SelectObject(fillbrush);
		const int len = 5;
		pDC->Ellipse(c.x - c.r + len, c.y - c.r + len, c.x + c.r - len, c.y + c.r - len);
	}
	ReleaseDC(pDC);
}


// CMFCApplication3View 打印

BOOL CBallView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBallView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CBallView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CBallView::AssertValid() const
{
	CView::AssertValid();
}

void CBallView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBallDoc* CBallView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallDoc)));
	return (CBallDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 消息处理程序


void CBallView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	flag_LBTNDown = true;
	m_pStart = point;
	CView::OnLButtonDown(nFlags, point);
}


void CBallView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (flag_LBTNDown) {
		CPoint center;
		double nRadius;
		center.x = (float(m_pStart.x + point.x)) / 2;
		center.y = (float(m_pStart.y + point.y)) / 2;
		nRadius = sqrt((double)(point.y - m_pStart.y) * (point.y - m_pStart.y) +
		(point.x - m_pStart.x) * (point.x - m_pStart.x)) / 2;
		circles.push_back(circle(center.x, center.y, nRadius));
		flag_LBTNDown = false;
	}
	CView::OnMouseMove(nFlags, point);
}

void CBallView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	SetTimer(1, 5, NULL);
}


void CBallView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1) {
		CRect rcClient;
		GetClientRect(rcClient);    // 获取当前视图的客户区大小
		for (int i = 0; i < circles.size(); i++) {
			circle& c = circles[i];
			c.x += dirX[c.dir]; c.y += dirY[c.dir];
			double left = c.x - c.r, right = c.x + c.r;
			double up = c.y - c.r, down = c.y + c.r;
			// 0: 右上, 1: 左上, 2: 左下, 3: 右下
			if (left <= 0) {
				if (c.dir == 1) { c.dir = 0; continue; }
				if (c.dir == 2) { c.dir = 3; continue; }
			}
			if (right >= rcClient.Width()) {
				if (c.dir == 0) { c.dir = 1; continue; }
				if (c.dir == 3) { c.dir = 2; continue; }
			}
			if (up <= 0) {
				if (c.dir == 0) { c.dir = 3; continue; }
				if (c.dir == 1) { c.dir = 2; continue; }
			}
			if (down >= rcClient.Height()) {
				if (c.dir == 2) { c.dir = 1; continue; }
				if (c.dir == 3) { c.dir = 0; continue; }
			}
		}
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}
