
// InputAndShowDoc.h: CInputAndShowDoc 类的接口
//


#pragma once

class CInputAndShowDoc : public CDocument
{
protected: // 仅从序列化创建
	CInputAndShowDoc() noexcept;
	DECLARE_DYNCREATE(CInputAndShowDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CInputAndShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
//	char filename[100];
public:
//	int SaveToFile();
private:
//	char content[1000];
//	int length;
public:
//	int Input(char ch);
	CString text;
	int UpdateText(UINT nChar);
	const CString& GetText();
};
