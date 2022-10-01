#pragma once
#include <windows.h>
#include <tchar.h>
#include "GLContext.h"

class OpenGLWindow :public GLContext
{
protected:
	int _width;
	int _height;

public:
	OpenGLWindow(HINSTANCE hInst = 0);

	virtual bool main(int w, int h);
	virtual void render();
	virtual LRESULT events(UINT msgId, WPARAM wParam, LPARAM lParam);

protected:
	static LRESULT CALLBACK  wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		if (msgId == WM_CREATE)
		{
			// 如果是创建窗口的消息
			LPCREATESTRUCT pData = (LPCREATESTRUCT)lParam;
			OpenGLWindow* pThis = (OpenGLWindow*)pData->lpCreateParams;
			// 在当前窗口上关联一个用户数据 pThis
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
			return DefWindowProc(hWnd, msgId, wParam, lParam);
		}
		else
		{
			OpenGLWindow* pThis = (OpenGLWindow*)GetWindowLong(hWnd, GWL_USERDATA);
			if (pThis)
			{
				return  pThis->events(msgId, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msgId, wParam, lParam);
			}
		}
	}
};
