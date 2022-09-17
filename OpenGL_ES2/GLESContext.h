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
	*   ��ʼ��EGL
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

		// �������Ǹ�����DC���õ�һ����ʾ�豸��ͼƬ����ӡ������Ļ��ͶӰ�ǵȵȣ�
		_display = eglGetDisplay(hDC);

		// ��ʼ���汾��
		//eglInitialize()����һ��EGLDisplay������EGLint��Ϊ���������ڳ�ʼ��������EGLint������дΪNULL
		//����ֵ
		//major��minor�������NULL����᷵����Ҫ�汾�ʹ�Ҫ�汾����֪����ɶ�ã�
		//��������ɹ��򷵻�EGL_TRUE��ʧ�ܷ���EGL_FALSE
		eglInitialize(_display, &major, &minor);

		// ����dispaly��
		/*��ѯ��������
		������������EGL��һ��EGLConfig������ֵ���Լ���μ�����Щֵ��Ҫ��ѯ��EGLConfig�������ض����ԣ���ʹ��eglGetConfigAttrb(display, config, attribute, value)
		�������ع�����EGLConfig���ض����Ե�ֵ����ʹ��������ȫ�������մ�����Ⱦ����ʱѡ������á�Ȼ����������3.1�����ǵ�ѡ�������������ܻ���Щ���¡�EGL�ṩ����һ�����̣�eglChooseConfig����������ָ��������Ӧ�ó�����˵ʲô����Ҫ�ģ���������������������ƥ������á�

		��EGLѡ������
		������Լ�ѡ�񣬿���ʹ��
		eglChooseChofig(display, attributeList, config, maxReturnConfigs, numConfigs)
		����Ҫ�ṩһ�������б��Լ�������Ӧ�ó������ȷ��������Ҫ���������Ե������ѡֵ�����磬�������Ҫһ��֧����λ��ɫ����ɫ����λ��ɫ(�����ġ�RGB 565����ʽ)����Ȼ�������֧��OpenGL ES 2.0����Ⱦ�����EGLConfig������������ʾ��3 - 2����ʾ�����顣*/
		eglChooseConfig(_display, attribs, &_config, 1, &numConfigs);

		// �������ǷŻص�config������ȡһ��fromat����ʽ�룬������
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
	*   ����EGL
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
	*   ����������
	*/
	void    swapBuffer()
	{
		eglSwapBuffers(_display, _surface);
	}
};