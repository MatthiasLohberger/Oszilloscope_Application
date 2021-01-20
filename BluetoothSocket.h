#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QtCore/qobject.h>

#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothsocket.h>

#include "commandline_eas_board.h"


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

    QByteArray ReadSocketForSync(int);
    void connect_readyRead();



    bool getConnectOrUnblockFlag();
    void resetConnectOrUnblockFlag();
    void unblockSocketSignals();


public slots:
    void sendMessage(const QByteArray &message);
    //void SocketSynchronisation();
    void connectReadyRead();
    void setDefaultCommandLine(ConfigData);
    void disconnect_readyRead();

    void SocketSynchronisation();
    void Resync(ConfigData);

    void DisconnectFromService();

    //void ConnectDisconnectSignal();



signals:
    //void messageReceived(const QString &sender, const QString &message);
    //void connected(const QString &name);
    //void disconnected();
    void socketErrorOccurred(const QString &errorString);
    void newDataReceived(QByteArray);
    void StartNormalTransmission();

    void ConnectionToServiceLost();



private slots:
    void readSocket();
    //void connected();
    void onSocketErrorOccurred(QBluetoothSocket::SocketError);




private:
    QBluetoothSocket *socket = nullptr;

    ConfigData CommandLineForSync;

    //bool ConnectOrUnblockFlag;
    bool SocketFlag;

};
//! [declaration]

#endif // CHATCLIENT_H
