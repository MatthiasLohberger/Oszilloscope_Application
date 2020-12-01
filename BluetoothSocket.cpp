 #include "BluetoothSocket.h"

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







/*

//! [readSocket]
void BluetoothSocket::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit messageReceived(socket->peerName(),
                             QString::fromUtf8(line.constData(), line.length()));
    }
}
//! [readSocket]



//! [sendMessage]
void BluetoothSocket::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}
//! [sendMessage]




void BluetoothSocket::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    if (error == QBluetoothSocket::NoSocketError)
        return;

    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QString errorString = socket->peerName() + QLatin1Char(' ')
            + metaEnum.valueToKey(error) + QLatin1String(" occurred");

    emit socketErrorOccurred(errorString);
}

*/






//! [connected]
void BluetoothSocket::connected()
{
    emit connected(socket->peerName());
}
//! [connected]
