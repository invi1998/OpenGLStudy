#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsOpenGL_ES.h"
#include "OpenGlES2Widget.h"

class QtWidgetsOpenGL_ES : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsOpenGL_ES(QWidget* parent = Q_NULLPTR);
	~QtWidgetsOpenGL_ES();

private:
	Ui::QtWidgetsOpenGL_ESClass ui;

	OpenGlES2Widget* gles;
};
