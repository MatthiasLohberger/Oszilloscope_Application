#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "bluetooth_connection.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setPalette(Qt::darkGray);

    MainWindow window;
    //window.resize();
    window.show();

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
