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

    void set_remoteService(QBluetoothDeviceInfo remoteService);

public Q_SLOTS:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    //bool connect();

private:
    QBluetoothDeviceInfo remoteService; //mit Set Methode durch if abfrage in device discovered setzen wenn == Boardname
};


#endif // BLUETOOTH_CONNECTION_H
