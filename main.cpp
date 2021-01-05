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


    QFont f("Arial", 12, QFont::Normal);
    f.setCapitalization(QFont::MixedCase);

    app.setFont(f);

    Oscilloscope o;
    o.showOscilloscopeMainWindow();



    // Test Konsolenausgabe
    qDebug() << "Welcome to the Bluetooth Oscilloscope Application for the EAS Board of the Hochschule Landshut!";
    qDebug() << "Starting Application...";


    bool ok = app.exec();
    return ok;
}
