#include "QtWidgetsOpenGL.h"

QtWidgetsOpenGL::QtWidgetsOpenGL(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	HWND hWnd = (HWND)this->winId();
	_context.setup(hWnd, GetDC(hWnd));

	QObject::connect(&_renderTimer, SIGNAL(timeout()), this, SLOT(render()));

	_renderTimer.setInterval(16);

	_renderTimer.start();
}

QtWidgetsOpenGL::~QtWidgetsOpenGL()
{
	_context.shutdown();
}

void QtWidgetsOpenGL::paintEvent(QPaintEvent* event)
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	_context.swapBuffer();
}

void QtWidgetsOpenGL::render()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	_context.swapBuffer();
}