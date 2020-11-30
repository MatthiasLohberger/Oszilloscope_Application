#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include<QByteArray>
#include<QString>

#include "oscilloscope.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.setPalette(Qt::darkGray);

    Oscilloscope o;
    o.showOscilloscopeMainWindow();


    // Test Konsolenausgabe
    qDebug() << "Hello World";
    qDebug() << "(Test)";


    bool ok = app.exec();
    return ok;
}
