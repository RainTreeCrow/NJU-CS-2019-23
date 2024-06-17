
// StudentsDoc.cpp: CStudentsDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Students.h"
#endif

#include "StudentsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStudentsDoc

IMPLEMENT_DYNCREATE(CStudentsDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentsDoc, CDocument)
	ON_COMMAND(ID_ADD, &CStudentsDoc::OnAdd)
END_MESSAGE_MAP()


// CStudentsDoc 构造/析构

CStudentsDoc::CStudentsDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	text = _T("");
}

CStudentsDoc::~CStudentsDoc()
{
}

BOOL CStudentsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	text = _T("");
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CStudentsDoc 序列化

void CStudentsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		ar << text;
	}
	else
	{
		// TODO:  在此添加加载代码
		ar >> text;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CStudentsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CStudentsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CStudentsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CStudentsDoc 诊断

#ifdef _DEBUG
void CStudentsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStudentsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStudentsDoc 命令


#include "CStudentDlg.h"
void CStudentsDoc::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	CStudentDlg dlg;
	if (dlg.DoModal() == IDOK) {
		CString temp = new_stu->index + '\t' + new_stu->name + '\t' +
			new_stu->sex + '\t' + new_stu->birthday + '\t' + new_stu->home + '\n';
		text.Append(temp);
		UpdateAllViews(NULL);
		SetModifiedFlag(true);
	}
}
