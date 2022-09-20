#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_QtWidgetsOpenGL.h"
#include "GLContext.h"

class QtWidgetsOpenGL : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsOpenGL(QWidget* parent = Q_NULLPTR);
	~QtWidgetsOpenGL();

protected:
	GLContext _context;
	QTimer _renderTimer;

public:
	void paintEvent(QPaintEvent* event) override;

public Q_SLOTS:
	void render();

private:
	Ui::QtWidgetsOpenGLClass ui;
};
