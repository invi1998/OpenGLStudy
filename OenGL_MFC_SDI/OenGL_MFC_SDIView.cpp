// OenGL_MFC_SDIView.cpp: COenGLMFCSDIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OenGL_MFC_SDI.h"
#endif

#include "OenGL_MFC_SDIDoc.h"
#include "OenGL_MFC_SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COenGLMFCSDIView

IMPLEMENT_DYNCREATE(COenGLMFCSDIView, CView)

BEGIN_MESSAGE_MAP(COenGLMFCSDIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COenGLMFCSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// COenGLMFCSDIView 构造/析构

COenGLMFCSDIView::COenGLMFCSDIView() noexcept
{
	// TODO: 在此处添加构造代码
}

COenGLMFCSDIView::~COenGLMFCSDIView()
{
}

BOOL COenGLMFCSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COenGLMFCSDIView 绘图

void COenGLMFCSDIView::OnDraw(CDC* /*pDC*/)
{
	COenGLMFCSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);	// 告诉OpenGL清空的时候只清空颜色缓冲区
	_context.swapBuffer();
}

// COenGLMFCSDIView 打印

void COenGLMFCSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COenGLMFCSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COenGLMFCSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COenGLMFCSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COenGLMFCSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COenGLMFCSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// COenGLMFCSDIView 诊断

#ifdef _DEBUG
void COenGLMFCSDIView::AssertValid() const
{
	CView::AssertValid();
}

void COenGLMFCSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COenGLMFCSDIDoc* COenGLMFCSDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COenGLMFCSDIDoc)));
	return (COenGLMFCSDIDoc*)m_pDocument;
}
#endif //_DEBUG

// COenGLMFCSDIView 消息处理程序

void COenGLMFCSDIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	HDC hDC = ::GetDC(m_hWnd);
	_context.setup(m_hWnd, hDC);
}

void COenGLMFCSDIView::OnDestroy()
{
	_context.shutdown();
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

BOOL COenGLMFCSDIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}