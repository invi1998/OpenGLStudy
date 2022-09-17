#include <windows.h>
#include <tchar.h>
#include "GLESContext.h"

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
	//1 ע�ᴰ����
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

	RegisterClassEx(&wnd);

	//2 ��������
	HWND hWnd = CreateWindowEx(
		0
		, _T("lesson01")
		, _T("���ڱ���")
		, WS_OVERLAPPEDWINDOW
		, 100
		, 100
		, 480
		, 320
		, 0
		, 0
		, hInstance
		, 0);

	//!3    ������ʾ
	if (hWnd)
	{
		UpdateWindow(hWnd);
		ShowWindow(hWnd, SW_SHOW);
	}

	else
	{
		return  0;
	}

	GLESContext   context;

	if (!context.setup(hWnd, GetDC(hWnd)))
	{
		return  0;
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
			/**
			*   ���û��ƺ������л���
			*/
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			context.swapBuffer();
		}
	}

	context.shutdown();

	return  0;
}