
// InputAndShowDoc.cpp: CInputAndShowDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "InputAndShow.h"
#endif

#include "InputAndShowDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CInputAndShowDoc

IMPLEMENT_DYNCREATE(CInputAndShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CInputAndShowDoc, CDocument)
END_MESSAGE_MAP()


// CInputAndShowDoc 构造/析构

CInputAndShowDoc::CInputAndShowDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

	//  length = 0;
	text = _T("");
}

CInputAndShowDoc::~CInputAndShowDoc()
{
}

BOOL CInputAndShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CInputAndShowDoc 序列化

void CInputAndShowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << text;
		// TODO:  在此添加存储代码
	}
	else
	{
		ar >> text;
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CInputAndShowDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CInputAndShowDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CInputAndShowDoc::SetSearchContent(const CString& value)
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

// CInputAndShowDoc 诊断

#ifdef _DEBUG
void CInputAndShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInputAndShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CInputAndShowDoc 命令


//int CInputAndShowDoc::SaveToFile()
//{
//	// TODO: 在此处添加实现代码.
//	return 0;
//}


//int CInputAndShowDoc::Input(char ch)
//{
//	// TODO: 在此处添加实现代码.
//	content[length] = ch;
//	length++;
//	UpdateAllViews(NULL);
//	SetModifiedFlag(true);
//	return 0;
//}


int CInputAndShowDoc::UpdateText(UINT nChar)
{
	// TODO: 在此处添加实现代码.
	text.AppendChar(wchar_t(nChar));
	UpdateAllViews(NULL);
	SetModifiedFlag(true);
	return 0;
}

const CString& CInputAndShowDoc::GetText()
{
	// TODO: 在此处添加实现代码.
	return text;
}
