#ifndef BLUETOOTH_CONNECTION_H
#define BLUETOOTH_CONNECTION_H

#include <qwidget.h>
#include <QBluetoothDeviceDiscoveryAgent>

class bluetooth_connection : public QWidget
{
    Q_OBJECT

public:
    bluetooth_connection();         // Konstruktor

    bool RetrLocalDevInfo();        // Retrieving Local Device Information
    void startDeviceDiscovery();    // Scanning for Bluetooth Devices

public Q_SLOTS:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    //bool connect();
};


#endif // BLUETOOTH_CONNECTION_H
