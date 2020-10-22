#ifndef BLUETOOTH_CONNECTION_H
#define BLUETOOTH_CONNECTION_H

#include <QBluetoothDeviceDiscoveryAgent>

class bluetooth_connection
{
public:
    bluetooth_connection();         // Konstruktor

    bool RetrLocalDevInfo();        // Retrieving Local Device Information
    void startDeviceDiscovery();    // Scanning for Bluetooth Devices
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    bool connect();
};


#endif // BLUETOOTH_CONNECTION_H
