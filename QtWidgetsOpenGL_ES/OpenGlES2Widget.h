#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_OpenGlES2Widget.h"

#include "GLESContext.h"

class OpenGlES2Widget : public QWidget
{
	Q_OBJECT

protected:
	GLESContext _context;
	QTimer _renderTimer;

public:
	OpenGlES2Widget(QWidget* parent = Q_NULLPTR);
	~OpenGlES2Widget();

public:
	void paintEvent(QPaintEvent* event) override;

public Q_SLOTS:
	void render();

private:
	Ui::OpenGlES2Widget ui;
};
