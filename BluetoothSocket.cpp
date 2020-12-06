 #include "BluetoothSocket.h"

#include <QByteArray>
#include <QtCore/qmetaobject.h>

BluetoothSocket::BluetoothSocket(QObject *parent)
    :   QObject(parent)
{


}






BluetoothSocket::~BluetoothSocket()
{
    stopClient();
}





//! [startClient]
void BluetoothSocket::startClient(const QBluetoothServiceInfo &remoteService)
{
    if (socket)
        return;

    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";
    qDebug() << "Service: " << remoteService.serviceName();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));

    //connect(socket, &QBluetoothSocket::readyRead, this, &ChatClient::readSocket);
    //connect(socket, &QBluetoothSocket::connected, this, QOverload<>::of(&ChatClient::connected));
    //connect(socket, &QBluetoothSocket::disconnected, this, &ChatClient::disconnected);
    //connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
     //       this, &ChatClient::onSocketErrorOccurred);

}
//! [startClient]




//! [stopClient]
void BluetoothSocket::stopClient()
{
    delete socket;
    socket = nullptr;
}
//! [stopClient]





//! [readSocket]
void BluetoothSocket::readSocket()
{
    if (!socket)
        return;

    qDebug() << "New Data avialable!";

    while(socket->bytesAvailable() < 4108){
    }
    qDebug() << "Enough data ready to read!";
    //while (socket->canReadLine()) {
        QByteArray received = socket->read(4108);
        //emit messageReceived(socket->peerName(),
        //                     QString::fromUtf8(line.constData(), line.length()));
    //}
    qDebug() << "Data read!";
    emit newDataReceived(received);
}
//! [readSocket]






//! [sendMessage]
void BluetoothSocket::sendMessage(const QByteArray &message)
{

    socket->write(message);
    qDebug() << "Message sent to EAS Borad!";
}
//! [sendMessage]





/*

void BluetoothSocket::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    if (error == QBluetoothSocket::NoSocketError)
        return;

    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QString errorString = socket->peerName() + QLatin1Char(' ')
            + metaEnum.valueToKey(error) + QLatin1String(" occurred");

    emit socketErrorOccurred(errorString);
}








//! [connected]
void BluetoothSocket::connected()
{
    emit connected(socket->peerName());
}
//! [connected]
*/



