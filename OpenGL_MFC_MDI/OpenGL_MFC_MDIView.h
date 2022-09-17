// OpenGL_MFC_MDIView.h: COpenGLMFCMDIView 类的接口
//

#pragma once
#include "GLContext.h"

class COpenGLMFCMDIView : public CView
{
protected: // 仅从序列化创建
	COpenGLMFCMDIView() noexcept;
	DECLARE_DYNCREATE(COpenGLMFCMDIView)

	// 特性
public:
	COpenGLMFCMDIDoc* GetDocument() const;

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
	virtual ~COpenGLMFCMDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GLContext _context;
	int _index;

	// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // OpenGL_MFC_MDIView.cpp 中的调试版本
inline COpenGLMFCMDIDoc* COpenGLMFCMDIView::GetDocument() const
{
	return reinterpret_cast<COpenGLMFCMDIDoc*>(m_pDocument);
}
#endif
