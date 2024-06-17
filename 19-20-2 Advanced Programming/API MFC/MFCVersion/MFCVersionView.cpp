
// MFCVersionView.cpp: CMFCVersionView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCVersion.h"
#endif

#include "MFCVersionDoc.h"
#include "MFCVersionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCVersionView

IMPLEMENT_DYNCREATE(CMFCVersionView, CView)

BEGIN_MESSAGE_MAP(CMFCVersionView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_CUT, &CMFCVersionView::OnEditCut)
END_MESSAGE_MAP()

// CMFCVersionView 构造/析构

CMFCVersionView::CMFCVersionView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCVersionView::~CMFCVersionView()
{
}

BOOL CMFCVersionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCVersionView 绘图

void CMFCVersionView::OnDraw(CDC* /*pDC*/)
{
	CMFCVersionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCVersionView 打印

BOOL CMFCVersionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCVersionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCVersionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCVersionView 诊断

#ifdef _DEBUG
void CMFCVersionView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCVersionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCVersionDoc* CMFCVersionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCVersionDoc)));
	return (CMFCVersionDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCVersionView 消息处理程序


void CMFCVersionView::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(_T("Paste"), _T("Msg"), 0);
}
