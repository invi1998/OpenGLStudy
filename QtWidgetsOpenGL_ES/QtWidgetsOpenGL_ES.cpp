#include "QtWidgetsOpenGL_ES.h"

QtWidgetsOpenGL_ES::QtWidgetsOpenGL_ES(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	gles = new OpenGlES2Widget();

	gles->resize(500, 500);
	gles->show();
}

QtWidgetsOpenGL_ES::~QtWidgetsOpenGL_ES()
{
	delete gles;
}