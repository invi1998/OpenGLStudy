#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(HINSTANCE hInst)
{
	//1 ע�ᴰ����
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
	//2 ��������
	HWND hWnd = CreateWindowEx(
		0,
		_T("lesson01"),
		_T("���ڱ���"),
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

	//!3    ������ʾ
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

	//4 ��Ϣѭ��
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ����windows API �õ���ȷ�Ĵ��ڿ�ߣ���ȥ��������
			RECT rect;
			GetClientRect(hWnd, &rect);
			_width = rect.right - rect.left;
			_height = rect.bottom - rect.top;

			//glClearColor(0.4, 0.1, 0.6, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// ָ���ӿ�
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
	*   ���û��ƺ������л���
	*/
}

/**
 * brief ��Ϣ�������
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