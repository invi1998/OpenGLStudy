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
		// ���ö�������
		glEnableClientState(GL_VERTEX_ARRAY);
		// �󶨶������� ��С�����͡����� ����ָ��
		glVertexPointer(3, GL_FLOAT, sizeof(float3), _circle);
		// ���� drawArray
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