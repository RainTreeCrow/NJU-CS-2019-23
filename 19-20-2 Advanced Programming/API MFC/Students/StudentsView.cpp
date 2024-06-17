
// StudentsView.cpp: CStudentsView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Students.h"
#endif

#include "StudentsDoc.h"
#include "StudentsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStudentsView

IMPLEMENT_DYNCREATE(CStudentsView, CScrollView)

BEGIN_MESSAGE_MAP(CStudentsView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStudentsView 构造/析构

CStudentsView::CStudentsView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStudentsView::~CStudentsView()
{
}

BOOL CStudentsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CStudentsView 绘图

void CStudentsView::OnDraw(CDC* pDC)
{
	CStudentsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CString c = pDoc->text;
	pDC->TextOutW(0, 0, c);
	vector<Student>::iterator iter;
	int count = 0;
	/*for (iter = Students.begin(); iter != Students.end(); iter++) {
		CString temp = iter->index + '\t' + iter->name + '\t' +
			iter->sex + '\t' + iter->birthday + '\t' + iter->home;
		pDC->TextOutW(count, 0, temp);

		count++;
	}*/

}

void CStudentsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CStudentsView 打印

BOOL CStudentsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStudentsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStudentsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CStudentsView 诊断

#ifdef _DEBUG
void CStudentsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CStudentsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CStudentsDoc* CStudentsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentsDoc)));
	return (CStudentsDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentsView 消息处理程序
