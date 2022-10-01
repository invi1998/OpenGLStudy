#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(HINSTANCE hInst)
{
	//1 注册窗口类
	WNDCLASSEX  wnd;

	memset(&wnd, 0, sizeof(wnd));

	wnd.cbSize = sizeof(wnd);
	wnd.lpfnWndProc = wndProc;
	wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wnd.hCursor = LoadCursor(hInst, IDC_ARROW);
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	wnd.hInstance = 0;
	wnd.lpszClassName = _T("lesson01");
	wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	RegisterClassEx(&wnd);
}

bool OpenGLWindow::main(int w, int h)
{
	//2 创建窗口
	HWND hWnd = CreateWindowEx(
		0,
		_T("lesson01"),
		_T("窗口标题"),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		w,
		h,
		0,
		0,
		0,
		this
	);

	//!3    更新显示
	if (hWnd)
	{
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}
	else
	{
		return false;
	}

	if (!setup(hWnd, GetDC(hWnd)))
	{
		return false;
	}

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
			// 利用windows API 得到正确的窗口宽高（减去标题栏）
			RECT rect;
			GetClientRect(hWnd, &rect);
			_width = rect.right - rect.left;
			_height = rect.bottom - rect.top;

			//glClearColor(0.4, 0.1, 0.6, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// 指定视口
			glViewport(0, 0, _width, _height);

			render();

			swapBuffer();
		}
	}
	shutdown();

	return true;
}

void OpenGLWindow::render()
{
	/**
	*   调用绘制函数进行绘制
	*/
}

/**
 * brief 消息处理过程
 */
LRESULT OpenGLWindow::events(UINT msgId, WPARAM wParam, LPARAM lParam)
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
		return DefWindowProc(_hWnd, msgId, wParam, lParam);
	}

	return 0;
}