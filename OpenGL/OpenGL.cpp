#include <windows.h>
#include <tchar.h>
#include "OpenGLWindow.h"

class SamplerTriangle : public OpenGLWindow
{
public:
	SamplerTriangle(HINSTANCE hins) :OpenGLWindow(hins)
	{
	}
	void render() override
	{
		// ָ������ģʽ�����ﴫ�� GL_PROJECTION �Ǹ���OpenGL��������������� ͶӰ
		// ָ�����²������ͶӰ����
		glMatrixMode(GL_PROJECTION);
		// ��ͶӰ�������Ϊ��λ����
		glLoadIdentity();
		// ָ������ͶӰ�ռ�,����ͶӰ����
		glOrtho(0, _width, _height, 0, -100, 100);

		glColor3f(1, 0, 1);
		glBegin(GL_TRIANGLES);

		glVertex3f(_width * 0.5f, 0, 0);
		glVertex3f(_width, _height, 0);
		glVertex3f(0, _height, 0);

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
	OpenGLWindow* instance = new SamplerTriangle(hInstance);
	instance->main(1000, 1000);

	return  0;
}