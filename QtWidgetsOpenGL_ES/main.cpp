#include "QtWidgetsOpenGL_ES.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsOpenGL_ES w;
    w.show();
    return a.exec();
}
