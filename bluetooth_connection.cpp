#include <QDebug>
#include "bluetooth_connection.h"

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>



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
    QObject::connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // Start a discovery
    discoveryAgent->start();

    //...

    qDebug() << "Punkt 3 erreicht!";
}



void bluetooth_connection::deviceDiscovered(const QBluetoothDeviceInfo &device){
    qDebug() << "Punkt 4 erreicht!";

    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';

    qDebug() << "Punkt 5 erreicht!";
}






