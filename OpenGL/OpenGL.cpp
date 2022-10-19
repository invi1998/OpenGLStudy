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

	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};

	float3 _circle[362];

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

		_circle[0].x = cx;
		_circle[0].y = cy;
		_circle[0].z = cz;

		// GL_TRIANGLE_STRIP（三角形带）
		vertex rect[] = {
			{10, 10, 0, 1, 1, 1},
			{110, 10, 0, 1, 0, 1},
			{10, 110, 0, 0, 0, 1},
			{110, 110, 0, 1, 1, 0}
		};

		/*for (int i = 0; i <= 360; ++i)
		{
			_circle[i].x = (float)cos((double)i * M_PI / 180) * cr + cx;
			_circle[i].y = (float)sin((double)i * M_PI / 180) * cr + cy;
			_circle[i].z = cz;
		}*/
		//// 启用顶点数组
		//glEnableClientState(GL_VERTEX_ARRAY);
		//// 绑定顶点数据 大小、类型、步幅 数据指针
		//glVertexPointer(3, GL_FLOAT, sizeof(float3), _circle);
		//// 调用 drawArray
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

		// 全局的，针对所有顶点都生效的指定颜色方式
		// glColor3f(1, 0, 1);
		// 启用了颜色数组后，这个其实就失效了

		// 启用顶点数组
		glEnableClientState(GL_VERTEX_ARRAY);
		// 启用颜色数组
		glEnableClientState(GL_COLOR_ARRAY);
		// 绑定顶点数据 大小、类型、步幅 数据指针
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		// 绑定颜色数据 通道（3通道 rgb), 类型， 偏移量， 数据指针
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect[0].r);
		// 调用 drawArray
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
};

// 使用OPenGL画线
class SamplerLine : public OpenGLWindow
{
public:
	struct vertex
	{
		float x, y, z;
		float r, g, b;
	};

	vertex _circle[360 * 2];
	vertex _circle_strip[361];

	void render() override
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		vertex rect[] = {
			{10, 10, 0, 1, 1, 1},
			{110, 10, 0, 1, 0, 1},
			{401, 50, 0, 0, 1, 1},
			{10, 110, 0, 0, 0, 1},
			{110, 110, 0, 1, 1, 0}
		};

		//glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		//glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		//glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect[0].r);
		////glDrawArrays(GL_LINES, 0, 4);
		////glDrawArrays(GL_LINE_STRIP, 0, 4);
		//glDrawArrays(GL_LINE_LOOP, 0, 5);

		// 画圆
		float cx = 500;
		float cy = 500;
		float cz = 0;
		float r = 80;

		// 圆的极坐标方程
		// x = cos(@)*r + center_x
		// y = sin(@)*r + center_y
		// 采用 lines 画圆
		/*for (int i = 0; i < 360; ++i)
		{
			_circle[i * 2 + 0].x = cos(double(i) * M_PI / 180) * r + cx;
			_circle[i * 2 + 0].y = sin(double(i) * M_PI / 180) * r + cy;
			_circle[i * 2 + 0].z = cz;
			_circle[i * 2 + 0].r = 1;
			_circle[i * 2 + 0].g = 1;
			_circle[i * 2 + 0].b = 1;

			_circle[i * 2 + 1].x = cos(double(i + 1) * M_PI / 180) * r + cx;
			_circle[i * 2 + 1].y = sin(double(i + 1) * M_PI / 180) * r + cy;
			_circle[i * 2 + 1].z = cz;
			_circle[i * 2 + 1].r = 1;
			_circle[i * 2 + 1].g = 1;
			_circle[i * 2 + 1].b = 1;
		}*/

		// 采用 strip 画圆 、 loop 的话又可以少一个点（首尾相连）
		for (int i = 0; i <= 360; ++i)
		{
			_circle_strip[i].x = cos(double(i) * M_PI / 180) * r + cx;
			_circle_strip[i].y = sin(double(i) * M_PI / 180) * r + cy;
			_circle_strip[i].z = cz;
			_circle_strip[i].r = 1;
			_circle_strip[i].g = 1;
			_circle_strip[i].b = 1;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), _circle_strip);
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &_circle_strip[0].r);
		glDrawArrays(GL_LINE_STRIP, 0, sizeof(_circle_strip) / sizeof(_circle_strip[0]));
	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	//SamplerTriangle instance;
	SamplerLine instance;
	instance.main(1000, 1000);

	return  0;
}