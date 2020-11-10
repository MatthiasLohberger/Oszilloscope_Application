 #include <QApplication>
#include <QDebug>


#include "mainwindow.h"
#include "bluetooth_window.h"
#include "commandline_eas_board.h"
#include "bluetooth_connection.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setPalette(Qt::darkGray);

    CommandLine_EAS_Board Oszi_ConfigData;

    //MainWindow window;
    bluetooth_window BtWindow();
    //window.resize();
    //window.show();

    BtWindow.show();

    //window.start();

    qDebug() << "Application Start: Hello World!";




    bluetooth_connection Bt;
    Bt.setUpBluetooth(Bt);

    bool BtStatus;
    BtStatus=Bt.RetrLocalDevInfo();

    if(BtStatus == true){
        //qDebug() << "Punkt 2 erreicht!";
        Bt.startDeviceDiscovery();
        //qDebug() << "Punkt 3 erreicht!";
    }








    bool ok = app.exec();


    return ok;
}
