#include <QDebug>
#include "bluetooth_connection.h"

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>
#include <QBluetoothServer>
#include <QBluetoothSocket>



bluetooth_connection::bluetooth_connection()        //Konstruktor
{

}



bool bluetooth_connection::RetrLocalDevInfo(){
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();
    }
    qDebug() << "Punkt 1 erreicht!";
    return true;
}




void bluetooth_connection::startDeviceDiscovery(){
    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                     this, SLOT(deviceDiscovered(QBluetoothDeviceInfo, discovery Agent)));

    //QObject::connect(discoveryAgent, SIGNAL(canceled()), , SLOT());   //Empfänger this und Slot Init Server/ Socket

    // Start a discovery
    discoveryAgent->start();

    //...

    qDebug() << "Punkt 3: Discovery started!";
}



void bluetooth_connection::deviceDiscovered(const QBluetoothDeviceInfo &device, QBluetoothDeviceDiscoveryAgent &discoveryAgent){
    //qDebug() << "Punkt 4 erreicht!";

    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    //qDebug() << "Punkt 5 erreicht!";

    if(device.name() == "RNBT-7122"){
        EAS_Board = device;
        discoveryAgent.stop();              //funktioniert das weil Pointer?        //Stelle?
         //Sendet cancelled Signal aus


    }
}



void bluetooth_connection::setUpBluetooth(bluetooth_connection &Bt){

    bool BtStatus;
    BtStatus=Bt.RetrLocalDevInfo();

    if(BtStatus == true){
        Bt.startDeviceDiscovery();
    }
}



//__________________________________________________________________________________________________________________________

/*
void bluetooth_connection::startClient(const QBluetoothServiceInfo &remoteService){
    if (socket)
        return;*

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";

    connect(socket, &QBluetoothSocket::readyRead, this, &ChatClient::readSocket);
    connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&ChatClient::connected));
    connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            this, &ChatClient::onSocketErrorOccurred);

}
*/

