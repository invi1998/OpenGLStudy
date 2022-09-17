#pragma once

#include "gles2/gl2.h"
#include "gles2/egl.h"
class   GLESContext
{
public:
	EGLConfig	        _config;
	EGLSurface          _surface;
	EGLContext          _context;
	EGLDisplay          _display;
	HWND                _hWnd;
	HDC                 _hDC;
	int                 _winWidth;
	int                 _winHeight;
public:
	GLESContext()
	{
		_config = 0;
		_display = EGL_NO_DISPLAY;
		_context = EGL_NO_CONTEXT;
		_surface = EGL_NO_SURFACE;

		_hWnd = 0;
		_hDC = 0;
		_winWidth = 0;
		_winHeight = 0;
	}

	~GLESContext()
	{
		shutdown();
	}
	/**
	*   初始化EGL
	*/
	bool    setup(HWND hWnd, HDC hDC)
	{
		_hWnd = hWnd;
		_hDC = hDC;
		shutdown();

		const EGLint attribs[] =
		{
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE,16,
			EGL_NONE
		};
		EGLint 	format(0);
		EGLint	numConfigs(0);
		EGLint  major;
		EGLint  minor;

		// 根据我们给定的DC来得到一个显示设备（图片，打印机，屏幕，投影仪等等）
		_display = eglGetDisplay(hDC);

		// 初始化版本号
		//eglInitialize()接受一个EGLDisplay和两个EGLint作为参数，用于初始化，两个EGLint可以填写为NULL
		//返回值
		//major和minor如果不是NULL，则会返回主要版本和次要版本（不知道有啥用）
		//函数如果成功则返回EGL_TRUE，失败返回EGL_FALSE
		eglInitialize(_display, &major, &minor);

		// 给定dispaly，
		/*查询配置属性
		我们现在描述EGL与一个EGLConfig关联的值，以及如何检索这些值。要查询与EGLConfig关联的特定属性，请使用eglGetConfigAttrb(display, config, attribute, value)
		它将返回关联的EGLConfig的特定属性的值。这使您可以完全控制最终创建渲染表面时选择的配置。然而，看看表3.1，考虑到选项的数量，你可能会有些害怕。EGL提供了另一个例程，eglChooseConfig，它允许您指定对您的应用程序来说什么是重要的，并将返回与您的请求最匹配的配置。

		让EGL选择配置
		如果是自己选择，可以使用
		eglChooseChofig(display, attributeList, config, maxReturnConfigs, numConfigs)
		您需要提供一个属性列表，以及对您的应用程序的正确操作很重要的所有属性的相关首选值。例如，如果您需要一个支持五位红色和蓝色、六位绿色(常见的“RGB 565”格式)、深度缓冲区和支持OpenGL ES 2.0的渲染表面的EGLConfig，您可以声明示例3 - 2中所示的数组。*/
		eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);

		// 根据我们放回的config，来获取一个fromat（格式码，索引）
		eglGetConfigAttrib(_display, _config, EGL_NATIVE_VISUAL_ID, &format);

		_surface = eglCreateWindowSurface(_display, _config, hWnd, NULL);
		if (_surface == 0)
		{
			return  false;
		}

		EGLint attr[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
		_context = eglCreateContext(_display, _config, 0, attr);
		if (_context == 0)
		{
			eglDestroySurface(_display, _surface);
			eglTerminate(_display);
			return  false;
		}

		if (eglMakeCurrent(_display, _surface, _surface, _context) == EGL_FALSE)
		{
			eglDestroySurface(_display, _surface);
			eglTerminate(_display);
			return false;
		}

		eglQuerySurface(_display, _surface, EGL_WIDTH, &_winWidth);
		eglQuerySurface(_display, _surface, EGL_HEIGHT, &_winHeight);

		return  true;
	}
	/**
	*   销毁EGL
	*/
	void    shutdown()
	{
		if (_display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if (_context != EGL_NO_CONTEXT)
			{
				eglDestroyContext(_display, _context);
			}
			if (_surface != EGL_NO_SURFACE)
			{
				eglDestroySurface(_display, _surface);
			}
			eglTerminate(_display);
		}
		_display = EGL_NO_DISPLAY;
		_context = EGL_NO_CONTEXT;
		_surface = EGL_NO_SURFACE;
	}
	/**
	*   交换缓冲区
	*/
	void    swapBuffer()
	{
		eglSwapBuffers(_display, _surface);
	}
};