#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "bluetooth_connection.h"

#include<QByteArray>
#include<QString>

#include "oscilloscope.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setPalette(Qt::darkGray);




/*
    //MainWindow window;
    //window.resize();

    //window.show();
    //window.hide();
    //window.start();

#ifdef Q_OS_ANDROID
    //window.showMaximized();
#else
    //window.show();
#endif

    //ConfigData OsziConfigData;            // -> done
    // BtWindow BluetoothWindow;            // -> done
    // BluetoothWindow.show();
*/

    Oscilloscope o;
    o.showOscilloscopeMainWindow();





    // Test Konsolenausgabe
    qDebug() << "Hello World";
    qDebug() << "(Test)";

    /*
    // Bluetooth Test
    bluetooth_connection Bt;
    bool BtStatus;
    BtStatus=Bt.RetrLocalDevInfo();

    if(BtStatus == true){
        qDebug() << "Punkt 2 erreicht!";
        Bt.startDeviceDiscovery();
        qDebug() << "Punkt 3 erreicht!";
    }




    // QString und QByteArray Test
    QByteArray Byte;
    Byte.number(255, 10);
    QString string;
    string.fromUtf8(Byte);
    qDebug() << "TestTestTest: " << string;
*/
    bool ok = app.exec();


    return ok;
}
