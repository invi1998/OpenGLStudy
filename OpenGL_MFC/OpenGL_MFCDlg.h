﻿// OpenGL_MFCDlg.h: 头文件
//

#pragma once
#include "GLContext.h"

// COpenGLMFCDlg 对话框
class COpenGLMFCDlg : public CDHtmlDialog
{
	// 构造
public:
	COpenGLMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_MFC_DIALOG, IDH = IDR_HTML_OPENGL_MFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement* pElement);
	HRESULT OnButtonCancel(IHTMLElement* pElement);

protected:
	GLContext _context;

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
