#include <windows.h>
#include <tchar.h>
#include <math.h>

#include "GLContext.h"
#include "OpenGLWindow.h"
#include <corecrt_math_defines.h>

class SamplerTriangle : public OpenGLWindow
{
public:
	struct float3
	{
		float x, y, z;
	};

	float3 _circle[360 * 3];

	void render() override
	{
		// 指定矩阵模式，这里传递 GL_PROJECTION 是告诉OpenGL我现在想操作的是 投影
		// 指定以下操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		// 将投影矩阵清空为单位矩阵
		glLoadIdentity();
		// 指定正交投影空间,产生投影矩阵
		glOrtho(0, _width, _height, 0, -100, 100);

		float cx = 500;
		float cy = 500;
		float cz = 0;
		float cr = 200;

		for (int i = 0; i < 360; ++i)
		{
			_circle[i * 3 + 0].x = cx;
			_circle[i * 3 + 0].y = cy;
			_circle[i * 3 + 0].z = cz;

			_circle[i * 3 + 1].x = (float)cos((double)i * M_PI / 180) * cr + cx;
			_circle[i * 3 + 1].y = (float)sin((double)i * M_PI / 180) * cr + cy;
			_circle[i * 3 + 1].z = cz;

			_circle[i * 3 + 2].x = (float)cos((double)(i + 1) * M_PI / 180) * cr + cx;
			_circle[i * 3 + 2].y = (float)sin((double)(i + 1) * M_PI / 180) * cr + cy;
			_circle[i * 3 + 2].z = cz;
		}
		// 启用顶点数组
		glEnableClientState(GL_VERTEX_ARRAY);
		// 绑定顶点数据 大小、类型、步幅 数据指针
		glVertexPointer(3, GL_FLOAT, sizeof(float3), _circle);
		// 调用 drawArray
		glDrawArrays(GL_TRIANGLES, 0, 3 * 360);
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