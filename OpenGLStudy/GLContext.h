#pragma once

// 包含OpenGL的标准头文件
#include <gl/glut.h>

class GLContext
{
protected:
	int _format;			// 窗口句柄
	HWND _hWnd;				// 绘制设备上下文
	HDC _hDC;				// OpenGL绘制上下文
	HGLRC _hRC;				// OpenGL对象
public:
	GLContext()
	{
		_format = 0;
		_hWnd = nullptr;
		_hDC = nullptr;
		_hRC = nullptr;
	}

	~GLContext()
	{
		shutdown();
	}

	/**
	*   初始化GL
	*/
	bool setup(HWND hWnd, HDC hDC)
	{
		_hWnd = hWnd;
		_hDC = hDC;

		unsigned PixelFormat;

		// 声明这样一个像素描述符
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0,
			0,
			0
		};

		if (!_format)
		{
			PixelFormat = ChoosePixelFormat(_hDC, &pfd);
		}
		else
		{
			PixelFormat = _format;
		}

		if (!SetPixelFormat(_hDC, PixelFormat, &pfd))
		{
			return false;
		}

		_hRC = wglCreateContext(_hDC);

		if (!wglMakeCurrent(_hDC, _hRC))
		{
			return false;
		}
		return  true;
	}

	/**
	*   销毁EGL
	*/
	void    shutdown()
	{
		if (_hRC != NULL)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_hRC);
			_hRC = NULL;
		}
		if (_hDC != NULL)
		{
			ReleaseDC(_hWnd, _hDC);
			_hDC = NULL;
		}
	}

	/**
*   交换缓冲区
*/
	void    swapBuffer()
	{
		SwapBuffers(_hDC);
	}
};
