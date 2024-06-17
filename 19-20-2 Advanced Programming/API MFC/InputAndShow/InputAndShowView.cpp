
// InputAndShowView.cpp: CInputAndShowView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "InputAndShow.h"
#endif

#include "InputAndShowDoc.h"
#include "InputAndShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInputAndShowView

IMPLEMENT_DYNCREATE(CInputAndShowView, CView)

BEGIN_MESSAGE_MAP(CInputAndShowView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_CHAR()
ON_WM_CHAR()
END_MESSAGE_MAP()

// CInputAndShowView 构造/析构

CInputAndShowView::CInputAndShowView() noexcept
{
	// TODO: 在此处添加构造代码
	//CInputAndShowDoc* pDoc = GetDocument();
	//if (pDoc != NULL)
		//text = pDoc->GetText();
}

CInputAndShowView::~CInputAndShowView()
{
}

BOOL CInputAndShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CInputAndShowView 绘图

void CInputAndShowView::OnDraw(CDC* pDC)
{
	CInputAndShowDoc* pDoc = GetDocument();
	pDC->TextOutW(0, 0, pDoc->GetText());
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CInputAndShowView 打印

BOOL CInputAndShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CInputAndShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CInputAndShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CInputAndShowView 诊断

#ifdef _DEBUG
void CInputAndShowView::AssertValid() const
{
	CView::AssertValid();
}

void CInputAndShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CInputAndShowDoc* CInputAndShowView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInputAndShowDoc)));
	return (CInputAndShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CInputAndShowView 消息处理程序


//void CInputAndShowView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CInputAndShowDoc* pDoc = GetDocument();
//	pDoc->Input(nChar);
//	CView::OnChar(nChar, nRepCnt, nFlags);
//}


void CInputAndShowView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Invalidate();
	CInputAndShowDoc* pDoc = GetDocument();
	pDoc->UpdateText(nChar);
	CView::OnChar(nChar, nRepCnt, nFlags);
}
