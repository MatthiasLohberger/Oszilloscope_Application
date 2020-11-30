#ifndef REMOTESELECTOR_H
#define REMOTESELECTOR_H

//#include <QtWidgets/qdialog.h>

//#include <QtBluetooth/qbluetoothaddress.h>
//#include <QtBluetooth/qbluetoothserviceinfo.h>
//#include <QtBluetooth/qbluetoothuuid.h>

#include<QBluetoothAddress>
#include<QBluetoothDeviceInfo>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothUuid>

QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)
//QT_FORWARD_DECLARE_CLASS(QListWidgetItem)

QT_USE_NAMESPACE


QT_END_NAMESPACE

class BluetoothDeviceFinder : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothDeviceFinder(QObject *parent = nullptr);
    ~BluetoothDeviceFinder();

    void startDiscovery();
    void stopDiscovery();
    QBluetoothDeviceInfo service() const;

private:

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    //QBluetoothDeviceInfo m_service;
    //QMap<QListWidgetItem *, QBluetoothServiceInfo> m_discoveredServices;

private slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
    void discoveryFinished();
    //void on_remoteDevices_itemActivated(QListWidgetItem *item);
    //void on_cancelButton_clicked();

signals:
    void ShowDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo);
};

#endif // REMOTESELECTOR_H
