#ifndef REMOTESELECTOR_H
#define REMOTESELECTOR_H

//#include <QtWidgets/qdialog.h>

//#include <QtBluetooth/qbluetoothaddress.h>
//#include <QtBluetooth/qbluetoothserviceinfo.h>
//#include <QtBluetooth/qbluetoothuuid.h>

#include<QBluetoothAddress>
#include<QBluetoothServiceInfo>
#include<QBluetoothServiceDiscoveryAgent>
#include<QBluetoothUuid>

QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)
//QT_FORWARD_DECLARE_CLASS(QListWidgetItem)

QT_USE_NAMESPACE


QT_END_NAMESPACE

class BluetoothServiceFinder : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothServiceFinder(QObject *parent = nullptr);
    ~BluetoothServiceFinder();

    void startDiscovery();
    void stopDiscovery();
    //QBluetoothServiceInfo service() const;

private:

    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    //QBluetoothDeviceInfo m_service;
    //QMap<QListWidgetItem *, QBluetoothServiceInfo> m_discoveredServices;

private slots:
    void ServiceDiscovered(const QBluetoothServiceInfo &serviceInfo);
    void discoveryFinished();
    //void on_remoteDevices_itemActivated(QListWidgetItem *item);
    //void on_cancelButton_clicked();

signals:
    void ShowServiceDiscovered(const QBluetoothServiceInfo &serviceInfo);
};

#endif // REMOTESELECTOR_H
