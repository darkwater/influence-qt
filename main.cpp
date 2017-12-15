#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    QPoint pos;
    pos.setX(1920);
    pos.setY(1055 - window.size().height());
    window.move(pos);
    window.show();

    return app.exec();
}
