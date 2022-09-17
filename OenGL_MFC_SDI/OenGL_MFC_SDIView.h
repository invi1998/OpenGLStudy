﻿// OenGL_MFC_SDIView.h: COenGLMFCSDIView 类的接口
//

#pragma once
#include "GLContext.h"

class COenGLMFCSDIView : public CView
{
protected: // 仅从序列化创建
	COenGLMFCSDIView() noexcept;
	DECLARE_DYNCREATE(COenGLMFCSDIView)

	// 特性
public:
	COenGLMFCSDIDoc* GetDocument() const;

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
	virtual ~COenGLMFCSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GLContext _context;

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

#ifndef _DEBUG  // OenGL_MFC_SDIView.cpp 中的调试版本
inline COenGLMFCSDIDoc* COenGLMFCSDIView::GetDocument() const
{
	return reinterpret_cast<COenGLMFCSDIDoc*>(m_pDocument);
}
#endif
