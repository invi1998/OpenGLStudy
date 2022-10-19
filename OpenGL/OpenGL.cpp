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

		_circle[0].x = cx;
		_circle[0].y = cy;
		_circle[0].z = cz;

		// GL_TRIANGLE_STRIP�������δ���
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
		//// ���ö�������
		//glEnableClientState(GL_VERTEX_ARRAY);
		//// �󶨶������� ��С�����͡����� ����ָ��
		//glVertexPointer(3, GL_FLOAT, sizeof(float3), _circle);
		//// ���� drawArray
		//glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

		// ȫ�ֵģ�������ж��㶼��Ч��ָ����ɫ��ʽ
		// glColor3f(1, 0, 1);
		// ��������ɫ����������ʵ��ʧЧ��

		// ���ö�������
		glEnableClientState(GL_VERTEX_ARRAY);
		// ������ɫ����
		glEnableClientState(GL_COLOR_ARRAY);
		// �󶨶������� ��С�����͡����� ����ָ��
		glVertexPointer(3, GL_FLOAT, sizeof(vertex), rect);
		// ����ɫ���� ͨ����3ͨ�� rgb), ���ͣ� ƫ������ ����ָ��
		glColorPointer(3, GL_FLOAT, sizeof(vertex), &rect[0].r);
		// ���� drawArray
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
};

// ʹ��OPenGL����
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

		// ��Բ
		float cx = 500;
		float cy = 500;
		float cz = 0;
		float r = 80;

		// Բ�ļ����귽��
		// x = cos(@)*r + center_x
		// y = sin(@)*r + center_y
		// ���� lines ��Բ
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

		// ���� strip ��Բ �� loop �Ļ��ֿ�����һ���㣨��β������
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