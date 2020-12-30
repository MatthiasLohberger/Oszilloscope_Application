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

/*
QByteArray BluetoothSocket::ReadSocketForSync(int PosFirstSyncByte){
    while(socket->bytesAvailable() < PosFirstSyncByte){
    }
    //qDebug() << "Read data for synchronisation!";

    QByteArray SyncData = socket->read(PosFirstSyncByte);

    qDebug() << "\t\t\\tSyncData read!";
    return SyncData;
}
*/

void BluetoothSocket::disconnect_readyRead(){
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}


void BluetoothSocket::connect_readyRead(){
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}


void BluetoothSocket::connectReadyRead(){
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}




void BluetoothSocket::SocketSynchronisation(){
    qDebug() << "SocketSynchronisation!         Socket";

    while(socket->bytesAvailable() < 4108){}

    int flagHeaderComplete = 0;
    int i = 0, h = 0;
    int helpInt;
    QByteArray byte;


    while(i <= 4096 || flagHeaderComplete == 0){
        h = 0;

        byte = socket->read(1);
        i++;
        if(byte.at(0) == 0xff){
            byte.toInt();
            helpInt = byte[0];
            qDebug() << "$$$$$$   Possible header start found   $$$$$$";
            qDebug() << "At Position: " << i;
            qDebug() << "Header[" << h << "] "<< "/FirstSyncByte = " << helpInt;
            byte = socket->read(1);
            i++;
            h++;


            if(byte.at(0) == 0xff){
                byte.toInt();
                helpInt = byte[0];
                qDebug() << "Header[" << h << "] "<< "/SecondSyncByte = " << helpInt;
                byte = socket->read(1);
                i++;
                h++;


                if(byte.at(0) == CommandLineDefault.Vertical){
                    qDebug() << "Header[" << h << "] "<< "/Vertical = " << byte.at(0);
                    byte = socket->read(9);
                    //qDebug() << "Bytes read: " << byte.size();
                    i++;
                    h++;
                    byte.toInt();


                    if(byte.size() == 9 && byte.at(0) == (char)CommandLineDefault.EntranceArea){
                        byte.toInt();
                        helpInt = byte[0];
                        qDebug() << "Header[" << h << "] "<< "/EntranceArea = " << helpInt;
                        //byte = socket->read(1);
                        i++;
                        h++;

                        if(byte.at(1) == CommandLineDefault.Horizontal){
                            qDebug() << "Header[" << h << "] "<< "/Horizontal = " << ((char)byte.at(1));
                            //byte = socket->read(1);
                            i++;
                            h++;

                            if(byte.at(2) == (char)CommandLineDefault.N_Low){
                                //byte.toInt();
                                helpInt = byte[2];
                                qDebug() << "Header[" << h << "] "<< "/N_Low = " << helpInt;
                                //byte = socket->read(1);
                                i++;
                                h++;

                                if(byte.at(3) == (char)CommandLineDefault.N_High){
                                    //byte.toInt();
                                    helpInt = byte[3];
                                    qDebug() << "Header[" << h << "] "<< "/N_High = " << helpInt;
                                    //byte = socket->read(1);
                                    i++;
                                    h++;

                                    if(byte.at(4) == CommandLineDefault.Trigger){
                                        qDebug() << "Header[" << h << "] "<< "/Trigger = " << ((char)byte.at(4));
                                        //byte.clear();
                                        //byte = socket->read(2);
                                        i++;
                                        h++;

                                        //if(byte.at(5) == (char)CommandLineDefault.TriggerThreshold_Low){                  //hier tritt ein Fehler auf, Trig_Thres_Low liefer 0 anstatt richtigen wert???
                                        if(byte.at(5) == (char)0){
                                            //byte.toInt();
                                            helpInt = byte[5];
                                            qDebug() << "Header[" << h << "] "<< "/TriggerThreshold_Low = " << helpInt;
                                            //byte = socket->read(1);
                                            i++;
                                            h++;

                                            if(byte.at(6) == (char)CommandLineDefault.TriggerThreshold_High){
                                                //byte.toInt();
                                                helpInt = byte[6];
                                                qDebug() << "Header[" << h << "] "<< "/TriggerThreshold_High = " << helpInt;
                                                //byte.clear();
                                                //byte = socket->read(1);
                                                i++;
                                                h++;

                                                if(byte.at(7) == CommandLineDefault.TriggerMode){
                                                    qDebug() << "Header[" << h << "] "<< "/TriggerMode = " << ((char)byte.at(7));
                                                    //byte = socket->read(1);
                                                    i++;
                                                    h++;

                                                    if(byte.at(8) == CommandLineDefault.TriggerEdge){
                                                        qDebug() << "Header[" << h << "] "<< "/TriggerEdge = " << ((char)byte.at(8));

                                                        qDebug() << "$$$$$$   Complete header found   $$$$$$";
                                                        flagHeaderComplete = 1;

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(flagHeaderComplete != 0){
        qDebug() << "Complete header found, starting normal transmission...";
        socket->read(4096);     // 4108 - 12 (Header schon eingelesen)

        //Starten der normalen Übertragung
        emit StartNormalTransmission();
    }
    else if(i >= 4096){
        qDebug() << "No valid header found. Restart app!";
    } else {
        qDebug() << "Unknown Error. Restart app!";
    }


}




void BluetoothSocket::setDefaultCommanLine(ConfigData CommandLine){
    CommandLineDefault = CommandLine;
}







































