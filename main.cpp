#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setPalette(Qt::darkGray);

    MainWindow window;
    //window.resize();
    window.show();

    //window.start();

    qDebug() << "Hello World";
    qDebug() << "(Test)";


    bool ok = app.exec();


    return ok;
}
