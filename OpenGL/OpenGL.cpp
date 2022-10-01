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
		// 指定矩阵模式，这里传递 GL_PROJECTION 是告诉OpenGL我现在想操作的是 投影
		// 指定以下操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		// 将投影矩阵清空为单位矩阵
		glLoadIdentity();
		// 指定正交投影空间,产生投影矩阵
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