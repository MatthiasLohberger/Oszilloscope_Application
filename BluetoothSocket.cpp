 #include "BluetoothSocket.h"

#include <QByteArray>
#include <QtCore/qmetaobject.h>

BluetoothSocket::BluetoothSocket(QObject *parent)
    :   QObject(parent)
{
    //ConnectOrUnblockFlag = 0;
    SocketFlag = 0;
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
    connect(socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
            this, &BluetoothSocket::onSocketErrorOccurred);

}
//! [startClient]




//! [stopClient]
void BluetoothSocket::stopClient()
{
    delete socket;
    socket = nullptr;
}
//! [stopClient]



void BluetoothSocket::DisconnectFromService(){
    //int ByteNumber;
    qDebug() << "Socket reset 1";
    socket->disconnectFromService();
    qDebug() << "Socket reset 2";
    //ByteNumber = socket->bytesAvailable();

    socket->readAll();
    qDebug() << "Socket reset 3";
    //socket = nullptr;
    qDebug() << "Socket reset done!";
}








//-------------------------------------------------------------------------------------------
    // read, wirte and Synchronsiation

//! [readSocket]
void BluetoothSocket::readSocket()
{
    if (!socket || SocketFlag == 1){
        return;
    }

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







void BluetoothSocket::onSocketErrorOccurred(QBluetoothSocket::SocketError error)
{
    if (error == QBluetoothSocket::NoSocketError)
        return;

    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QString errorString = socket->peerName() + QLatin1Char(' ')
            + metaEnum.valueToKey(error) + QLatin1String(" occurred");

    qDebug() << errorString;

    //emit socketErrorOccurred(errorString);
}







/*
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
    /*
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));

    disconnect(socket, &QBluetoothSocket::readyRead,
               this, &BluetoothSocket::readSocket);

    socket->blockSignals(true);
    */
    //ConnectOrUnblockFlag = 1;

}


void BluetoothSocket::connect_readyRead(){
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));

}



bool BluetoothSocket::getSocketFlag(){
    return SocketFlag;
}

void BluetoothSocket::setSocketFlag(){
    SocketFlag = 1;
}


void BluetoothSocket::resetSocketFlag(){
    SocketFlag = 0;
}














void BluetoothSocket::SocketSynchronisation(){
    qDebug() << "SocketSynchronisation!         Socket";

    while(socket->bytesAvailable() < 4108){}

    int flagHeaderComplete = 0;
    int i = 0, h = 0;
    int helpInt;
    QByteArray byte;


    while(i <= 4096 || flagHeaderComplete == 0){
        if(flagHeaderComplete == 1){
            qDebug() << "Break, because flagHeaderComplete = " << flagHeaderComplete;
            break;
        }

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


                if(byte.at(0) == CommandLineForSync.Vertical){
                    qDebug() << "Header[" << h << "] "<< "/Vertical = " << byte.at(0);
                    byte = socket->read(9);
                    //qDebug() << "Bytes read: " << byte.size();
                    i++;
                    h++;
                    byte.toInt();


                    if(byte.size() == 9 && byte.at(0) == (char)CommandLineForSync.EntranceArea){
                        byte.toInt();
                        helpInt = byte[0];
                        qDebug() << "Header[" << h << "] "<< "/EntranceArea = " << helpInt;
                        //byte = socket->read(1);
                        i++;
                        h++;

                        if(byte.at(1) == CommandLineForSync.Horizontal){
                            qDebug() << "Header[" << h << "] "<< "/Horizontal = " << ((char)byte.at(1));
                            //byte = socket->read(1);
                            i++;
                            h++;

                            if(byte.at(2) == (char)CommandLineForSync.N_Low){
                                //byte.toInt();
                                helpInt = byte[2];
                                qDebug() << "Header[" << h << "] "<< "/N_Low = " << helpInt;
                                //byte = socket->read(1);
                                i++;
                                h++;

                                if(byte.at(3) == (char)CommandLineForSync.N_High){
                                    //byte.toInt();
                                    helpInt = byte[3];
                                    qDebug() << "Header[" << h << "] "<< "/N_High = " << helpInt;
                                    //byte = socket->read(1);
                                    i++;
                                    h++;

                                    if(byte.at(4) == CommandLineForSync.Trigger){
                                        qDebug() << "Header[" << h << "] "<< "/Trigger = " << ((char)byte.at(4));
                                        //byte.clear();
                                        //byte = socket->read(2);
                                        i++;
                                        h++;

                                        //if(byte.at(5) == (char)CommandLineForSync.TriggerThreshold_Low){                  //hier tritt ein Fehler auf, Trig_Thres_Low liefer 0 anstatt richtigen wert???
                                        if(byte.at(5) == (char)0){
                                            //byte.toInt();
                                            helpInt = byte[5];
                                            qDebug() << "Header[" << h << "] "<< "/TriggerThreshold_Low = " << helpInt;
                                            //byte = socket->read(1);
                                            i++;
                                            h++;

                                            if(byte.at(6) == (char)CommandLineForSync.TriggerThreshold_High){
                                                //byte.toInt();
                                                helpInt = byte[6];
                                                qDebug() << "Header[" << h << "] "<< "/TriggerThreshold_High = " << helpInt;
                                                //byte.clear();
                                                //byte = socket->read(1);
                                                i++;
                                                h++;

                                                if(byte.at(7) == CommandLineForSync.TriggerMode){
                                                    qDebug() << "Header[" << h << "] "<< "/TriggerMode = " << ((char)byte.at(7));
                                                    //byte = socket->read(1);
                                                    i++;
                                                    h++;

                                                    if(byte.at(8) == CommandLineForSync.TriggerEdge){
                                                        qDebug() << "Header[" << h << "] "<< "/TriggerEdge = " << ((char)byte.at(8));

                                                        flagHeaderComplete = 1;
                                                        qDebug() << "$$$$$$   Complete header found   $$$$$$";

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




void BluetoothSocket::setDefaultCommandLine(ConfigData CommandLine){
    CommandLineForSync = CommandLine;
}



void BluetoothSocket::Resync(ConfigData CommandLine){
    QByteArray neglect;
    int DataFramesNeglected = 5;        //  works with 10, but then there`s a little delay

    for(int i=0; i<DataFramesNeglected; i++){
        while(socket->bytesAvailable() < 4108){}
        neglect = socket->read(4108);
    }
    // after 10 times data was neglected, the sync can start
    CommandLineForSync = CommandLine;

    qDebug() << "Header for verify: ";
    qDebug() << CommandLineForSync.Vertical  << CommandLineForSync.EntranceArea
             << CommandLineForSync.Horizontal << CommandLineForSync.N << CommandLineForSync.N_Low << CommandLineForSync.N_High
             << CommandLineForSync.Trigger << CommandLineForSync.TriggerThreshold << CommandLineForSync.TriggerThreshold_Low
             << CommandLineForSync.TriggerThreshold_High << CommandLineForSync.TriggerMode << CommandLineForSync.TriggerEdge;

    SocketSynchronisation();
}

/*
void BluetoothSocket::ConnectDisconnectSignal(){
    connect(socket, &QBluetoothSocket::disconnected,
        this, &BluetoothSocket::ConnectionToServiceLost);
}
*/





































