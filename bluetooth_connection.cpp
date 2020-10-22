#include <QDebug>
#include "bluetooth_connection.h"

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
    return true;
}




void bluetooth_connection::startDeviceDiscovery(){
    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));

    // Start a discovery
    discoveryAgent->start();

    //...
}



void bluetooth_connection::deviceDiscovered(const QBluetoothDeviceInfo &device){
    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
}



bool bluetooth_connection::connect(){

    return true;
}


