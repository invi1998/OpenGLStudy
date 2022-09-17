// OpenGL_MFC_MDIView.cpp: COpenGLMFCMDIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGL_MFC_MDI.h"
#endif

#include "OpenGL_MFC_MDIDoc.h"
#include "OpenGL_MFC_MDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COpenGLMFCMDIView

IMPLEMENT_DYNCREATE(COpenGLMFCMDIView, CView)

BEGIN_MESSAGE_MAP(COpenGLMFCMDIView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLMFCMDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// COpenGLMFCMDIView 构造/析构

int g_index = 0;

COpenGLMFCMDIView::COpenGLMFCMDIView() noexcept
{
	// TODO: 在此处添加构造代码
}

COpenGLMFCMDIView::~COpenGLMFCMDIView()
{
}

BOOL COpenGLMFCMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COpenGLMFCMDIView 绘图

void COpenGLMFCMDIView::OnDraw(CDC* /*pDC*/)
{
	COpenGLMFCMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	_context.makeCurrent();

	if (_index == 0)
	{
		glClearColor(1, 0, 1, 1);
	}
	else
	{
		glClearColor(0, 0, 1, 1);
	}

	glClear(GL_COLOR_BUFFER_BIT);
	_context.swapBuffer();
}

// COpenGLMFCMDIView 打印

void COpenGLMFCMDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLMFCMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLMFCMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpenGLMFCMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void COpenGLMFCMDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLMFCMDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// COpenGLMFCMDIView 诊断

#ifdef _DEBUG
void COpenGLMFCMDIView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLMFCMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLMFCMDIDoc* COpenGLMFCMDIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLMFCMDIDoc)));
	return (COpenGLMFCMDIDoc*)m_pDocument;
}
#endif //_DEBUG

// COpenGLMFCMDIView 消息处理程序

void COpenGLMFCMDIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	_index = g_index;
	++g_index;

	HDC hDC = ::GetDC(m_hWnd);
	_context.setup(m_hWnd, hDC);
}

void COpenGLMFCMDIView::OnDestroy()
{
	_context.shutdown();
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

BOOL COpenGLMFCMDIView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}