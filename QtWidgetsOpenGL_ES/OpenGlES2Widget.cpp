#include "OpenGlES2Widget.h"

OpenGlES2Widget::OpenGlES2Widget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	HWND hWnd = (HWND)this->winId();
	_context.setup(hWnd, GetDC(hWnd));

	QObject::connect(&_renderTimer, SIGNAL(timeout()), this, SLOT(render()));

	_renderTimer.setInterval(16);

	_renderTimer.start();
}

OpenGlES2Widget::~OpenGlES2Widget()
{
	_context.shutdown();
}

void OpenGlES2Widget::paintEvent(QPaintEvent* event)
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	_context.swapBuffer();
}

void OpenGlES2Widget::render()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	_context.swapBuffer();
}