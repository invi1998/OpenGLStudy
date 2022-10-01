#include <windows.h>
#include <tchar.h>
#include "GLContext.h"

LRESULT CALLBACK  wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
{
	switch (msgId)
	{
	case WM_CLOSE:
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hWnd, msgId, wParam, lParam);
	}
	return  0;
}

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	//1 注册窗口类
	WNDCLASSEX  wnd;

	memset(&wnd, 0, sizeof(wnd));

	wnd.cbSize = sizeof(wnd);
	wnd.lpfnWndProc = wndProc;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	wnd.hInstance = hInstance;
	wnd.lpszClassName = _T("lesson01");
	wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	int width = 1000;
	int height = 1000;

	RegisterClassEx(&wnd);

	//2 创建窗口
	HWND hWnd = CreateWindowEx(
		0,
		_T("lesson01"),
		_T("窗口标题"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		width,
		height,
		0,
		0,
		hInstance,
		0
	);

	//!3    更新显示
	if (hWnd)
	{
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}
	else
	{
		return 0;
	}

	GLContext context;

	if (!context.setup(hWnd, GetDC(hWnd)))
	{
		return 0;
	}

	// 利用windows API 得到正确的窗口宽高（减去标题栏）
	RECT rect;
	GetClientRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	MSG     msg = { 0 };

	//4 消息循环
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			/**
			*   调用绘制函数进行绘制
			*/
			glClearColor(0.4, 0.1, 0.6, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			// 指定视口
			glViewport(0, 0, width, height);
			// 指定矩阵模式，这里传递 GL_PROJECTION 是告诉OpenGL我现在想操作的是 投影
			// 指定以下操作针对投影矩阵
			glMatrixMode(GL_PROJECTION);
			// 将投影矩阵清空为单位矩阵
			glLoadIdentity();
			// 指定正交投影空间,产生投影矩阵
			glOrtho(0, width, height, 0, -100, 100);

			// 告诉OpenGL我下面想画一个线
			glBegin(GL_LINES);
			// 指定线的起始点和终点
			glVertex3f(0, 0, 0);
			glVertex3f(500, 500, 0);

			glEnd();

			context.swapBuffer();
		}
	}

	context.shutdown();

	return  0;
}