#ifndef BLUETOOTH_CONNECTION_H
#define BLUETOOTH_CONNECTION_H

#include <qwidget.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceInfo>

class bluetooth_connection : public QWidget
{
    Q_OBJECT

public:
    // Konstruktor
    bluetooth_connection();


    void setUpBluetooth(bluetooth_connection &Bt);

    //Gerätesuche
    bool RetrLocalDevInfo();        // Retrieving Local Device Information
    void startDeviceDiscovery();    // Scanning for Bluetooth Devices

    //Bluetooth Server & Socket
    void startClient(const QBluetoothServiceInfo &remoteService);


public Q_SLOTS:
    void deviceDiscovered(const QBluetoothDeviceInfo &device, QBluetoothDeviceDiscoveryAgent &discoveryAgent);

    //bool connect();

private:
    QBluetoothDeviceInfo EAS_Board;     //remoteService mit Info über Name und UUID von EAS Board
};


#endif // BLUETOOTH_CONNECTION_H
n<<<<<<<
