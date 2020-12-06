#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QtCore/qobject.h>

#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothsocket.h>

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

//! [declaration]
class BluetoothSocket : public QObject
{
    Q_OBJECT

public:
    explicit BluetoothSocket(QObject *parent = nullptr);
    ~BluetoothSocket();

    void startClient(const QBluetoothServiceInfo &remoteService);
    void stopClient();


public slots:
    void sendMessage(const QByteArray &message);



signals:
    //void messageReceived(const QString &sender, const QString &message);
    //void connected(const QString &name);
    //void disconnected();
    //void socketErrorOccurred(const QString &errorString);
    void newDataReceived(const QByteArray &);



private slots:
    void readSocket();
    //void connected();
    //void onSocketErrorOccurred(QBluetoothSocket::SocketError);



private:
    QBluetoothSocket *socket = nullptr;
};
//! [declaration]

#endif // CHATCLIENT_H
