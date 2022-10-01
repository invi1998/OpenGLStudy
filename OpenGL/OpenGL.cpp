#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "GLContext.h"
#include "OpenGLWindow.h"
#include <corecrt_math_defines.h>

class SamplerTriangle : public OpenGLWindow
{
public:
	void render() override
	{
		// ָ������ģʽ�����ﴫ�� GL_PROJECTION �Ǹ���OpenGL��������������� ͶӰ
		// ָ�����²������ͶӰ����
		glMatrixMode(GL_PROJECTION);
		// ��ͶӰ�������Ϊ��λ����
		glLoadIdentity();
		// ָ������ͶӰ�ռ�,����ͶӰ����
		glOrtho(0, _width, _height, 0, -100, 100);

		float cx = 500;
		float cy = 500;
		float cz = 0;
		float cr = 200;

		glBegin(GL_TRIANGLES);

		for (int i = 0; i < 360; ++i)
		{
			float x = (float)cos((double)i * M_PI / 180) * cr + cx;
			float y = (float)sin((double)i * M_PI / 180) * cr + cy;

			float x1 = (float)cos((double)(i + 1) * M_PI / 180) * cr + cx;
			float y1 = (float)sin((double)(i + 1) * M_PI / 180) * cr + cy;

			glVertex3f(cx, cy, cz);
			glVertex3f(x, y, cz);
			glVertex3f(x1, y1, cz);
		}

		glEnd();
	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	SamplerTriangle instance;
	instance.main(1000, 1000);

	return  0;
}