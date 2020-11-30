#include "BluetoothDeviceFinder.h"

#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <QtBluetooth/qbluetoothservicediscoveryagent.h>

QT_USE_NAMESPACE





BluetoothDeviceFinder::BluetoothDeviceFinder(QObject *parent)                  //Ui und QDiaglog weg
    :   QObject(parent)
{   
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SIGNAL(ShowDeviceDiscovered(const QBluetoothDeviceInfo)));
    //connect(m_discoveryAgent, SIGNAL(finished()), this, SLOT(discoveryFinished()));
    //connect(m_discoveryAgent, SIGNAL(canceled()), this, SLOT(discoveryFinished()));
}








BluetoothDeviceFinder::~BluetoothDeviceFinder()
{

    delete discoveryAgent;
}








void BluetoothDeviceFinder::startDiscovery()
{
    //ui->status->setText(tr("Scanning..."));

    //qDebug() << "Scanning...";

    if (discoveryAgent->isActive())
        discoveryAgent->stop();


    //discoveryAgent->setUuidFilter(uuid);
    //discoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
    discoveryAgent->start();
}








void BluetoothDeviceFinder::stopDiscovery()
{
    if (discoveryAgent){
        discoveryAgent->stop();
    }
}





/*
QBluetoothServiceInfo RemoteSelector::service() const
{
    return m_service;
}
*/






void BluetoothDeviceFinder::deviceDiscovered(const QBluetoothDeviceInfo &deviceInfo)
{
#if 0
    qDebug() << "Discovered service on"
             << serviceInfo.device().name() << serviceInfo.device().address().toString();
    qDebug() << "\tService name:" << serviceInfo.serviceName();
    qDebug() << "\tDescription:"
             << serviceInfo.attribute(QBluetoothServiceInfo::ServiceDescription).toString();
    qDebug() << "\tProvider:"
             << serviceInfo.attribute(QBluetoothServiceInfo::ServiceProvider).toString();
    qDebug() << "\tL2CAP protocol service multiplexer:"
             << serviceInfo.protocolServiceMultiplexer();
    qDebug() << "\tRFCOMM server channel:" << serviceInfo.serverChannel();
#endif
    /*
    const QBluetoothAddress address = serviceInfo.device().address();
    for (const QBluetoothServiceInfo &info : qAsConst(m_discoveredServices)) {
        if (info.device().address() == address)
            return;
    }

    QString remoteName;
    if (serviceInfo.device().name().isEmpty())
        remoteName = address.toString();
    else
        remoteName = serviceInfo.device().name();

    QListWidgetItem *item =
        new QListWidgetItem(QString::fromLatin1("%1 %2").arg(remoteName,
                                                             serviceInfo.serviceName()));

    m_discoveredServices.insert(item, serviceInfo);
    //ui->remoteDevices->addItem(item);
    */

    emit ShowDeviceDiscovered(deviceInfo);
}










void BluetoothDeviceFinder::discoveryFinished()
{
    //ui->status->setText(tr("Select the chat service to connect to."));
}






/*
void BluetoothDeviceFinder::on_remoteDevices_itemActivated(QListWidgetItem *item)
{
    qDebug() << "got click" << item->text();
    m_service = m_discoveredServices.value(item);
    if (m_discoveryAgent->isActive())
        m_discoveryAgent->stop();

    accept();
}








void BluetoothDeviceFinder::on_cancelButton_clicked()
{
    reject();
}
*/
