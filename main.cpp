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
    qDebug() << "Welcome to the Bluetooth Oscilloscope Application for the EAS Board of the Hochschule Lanshut!";
    qDebug() << "Starting Application...";


    bool ok = app.exec();
    return ok;
}
