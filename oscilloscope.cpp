#include "oscilloscope.h"


Oscilloscope::Oscilloscope(QObject *parent) : QObject(parent)
{

    connect(&OsziMainWindow, SIGNAL(BtSettingsButtonPressed()),
            &BluetoothWindow, SLOT(showBluetoothWindow()));
    // Zurückwechseln mit hide im BTWin direkt

    connect(&OsziConfigData, SIGNAL(newConfigData(ConfigDataString &)),
            &BluetoothWindow, SLOT(newDataForPlainTextWidget(ConfigDataString &)));

    connect(&BluetoothWindow, SIGNAL(DefaultButtonPressed()),
            &OsziConfigData, SLOT(DefaultValues()));

    connect(this, SIGNAL(ChangeTextConnectButton()),
            &BluetoothWindow, SLOT(setTextConnectButton()));


    connect(&OsziMainWindow, SIGNAL(SendButton_Pressed()),
            this, SLOT(SendMessage()));
    connect(&BluetoothWindow, SIGNAL(SendButtonPressed()),
            this, SLOT(SendMessage()));

    connect(this, SIGNAL(EnableSendOsziMainWindowBtWindow()),
            &OsziMainWindow, SLOT(EnableSendButton()));
    connect(this, SIGNAL(EnableSendButtonBtWindow()),
            &BluetoothWindow, SLOT(Enable_SendButton()));


    connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray &)),
            this, SLOT(ReceiveData(QByteArray &)));

    connect(&BluetoothWindow, SIGNAL(ServiceSelectedForConnection(const QBluetoothServiceInfo &)),
            this, SLOT(startOscilloscope(const QBluetoothServiceInfo &)));


    OsziConfigData.setDefaultValues();

}




Oscilloscope::~Oscilloscope(){
    //PlotThread.quit();
    BluetoothThread.quit();
    //PlotThread.wait();
    BluetoothThread.wait();

}


//----------------------------------------------------------------------------


void Oscilloscope::showOscilloscopeMainWindow(){
    OsziMainWindow.showFullScreen();
}


//----------------------------------------------------------------------------


void Oscilloscope::startOscilloscope(const QBluetoothServiceInfo &service){
    qDebug() << "Start Oscilloscope!";
    //starting the threads
    bluetoothSocket.moveToThread(&BluetoothThread);
    BluetoothThread.start();
    qDebug() << "Treads started!";

    //Connect to service (EAS Board)
    bluetoothSocket.startClient(service);

    emit ChangeTextConnectButton();

    connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray &)),
            this, SLOT(ReceiveData(QByteArray &)));

    //Kommandline das erste mal senden
    SendMessage();

    //Plot starten

    //Send buttons enablen in beiden Windows
    emit EnableSendButtonBtWindow();
    emit EnableSendOsziMainWindowBtWindow();

}



//----------------------------------------------------------------------------

//[Slots zum Empfangen über Bluetooth]

void Oscilloscope::SendMessage(){
     QByteArray message;
     ConfigData CommandLine = OsziConfigData.getData();

     message = "";
     message.append((char)0xFF);
     message.append((char)0xFF);

     message.append(CommandLine.Vertical);
     message.append((char)CommandLine.EntranceArea);

     message.append(CommandLine.Horizontal);
     message.append((char)CommandLine.N_Low);
     message.append((char)CommandLine.N_High);

     message.append(CommandLine.Trigger);
     message.append((char)CommandLine.TriggerThreshold_Low);
     message.append((char)CommandLine.TriggerThreshold_High);
     message.append(CommandLine.TriggerMode);
     message.append(CommandLine.TriggerEdge);

     qDebug() << "CommandLine ready to send!";
     qDebug() << "Data Size: " << message.size() << " Byte";


     bluetoothSocket.sendMessage(message);  //calls the real Fnkt.

}



void Oscilloscope::ReceiveData(QByteArray &message){

    QByteArray header = "";
     for(int i=0; i<=11; i++){
         header.append(message[i]);
     }
    qDebug() << "Header Check: ";
    if(checkHeader(header) == false){
        qDebug() << "Wrong Header received!";


        int i, PosFirstSyncByte, Pos2ndSyncByte;
        qDebug() << "-------Start Check-------";
        qDebug() << "Size of Data: " << message.size();
        for (i=0; i<= 4107; i++){
            if(message.at(i) == 0xff){
                if(PosFirstSyncByte > 0){
                    Pos2ndSyncByte = i;
                    qDebug() << "SyncByte2 (0xff) found at position i = "
                             << Pos2ndSyncByte << " in the received data.";
                }else {
                   PosFirstSyncByte = i;
                    qDebug() << "SyncByte1 (0xff) found at position i = "
                             << PosFirstSyncByte << " in the received data.";
                }
            }
        }
        qDebug() << "-------End Check-------";


        message = SocketSynchronisation(message, PosFirstSyncByte);
    } else{
        qDebug() << "Correct Header received!";
    }

    //ReceiveBuffer = message;

}




bool Oscilloscope::checkHeader(const QByteArray &header){
      //ConfigData CommandLine = OsziConfigData.getData();
      UIntHeader UintHeaderElements;

      UintHeaderElements.element3.append(header.at(3));
      UintHeaderElements.element5.append(header.at(5));
      UintHeaderElements.element6.append(header.at(6));
      UintHeaderElements.element8.append(header.at(8));
      UintHeaderElements.element9.append(header.at(9));

      QByteArray Element0 = "";
      Element0.append(header.at(0));
      qDebug() << "First Element: " << Element0.toInt();

    if(     //Element0.toInt() == 255

            header.at(0) == 0xff &&
            header.at(1) == 0xff    /*&&
            header.at(2) == 'V' &&
            UintHeaderElements.element3.toInt() == CommandLine.EntranceArea &&
            header.at(4) == 'H' &&
            UintHeaderElements.element5.toUInt() == CommandLine.N_Low &&
            UintHeaderElements.element6.toUInt() == CommandLine.N_High &&
            header.at(7) == 'T' &&
            UintHeaderElements.element8.toUInt() == CommandLine.TriggerThreshold_Low &&
            UintHeaderElements.element8.toUInt() == CommandLine.TriggerThreshold_High &&
            header.at(10) == CommandLine.TriggerMode &&
            header.at(11) == CommandLine.TriggerEdge */ ) {
        return true;
    } else {
        return false;
    }
}




QByteArray Oscilloscope::SocketSynchronisation(QByteArray &message, int PosFirstSyncByte){
    //Synchronisation through search for the SyncWort
    bluetoothSocket.disconnect_readyRead();

    message.remove(0, PosFirstSyncByte);
    if(message.size() != 4108 - PosFirstSyncByte){
        //?
    }

    message.append(bluetoothSocket.ReadSocketForSync(PosFirstSyncByte));
    bluetoothSocket.connect_readyRead();

    QByteArray header = "";
    for(int i=0; i<=11; i++){
             header.append(message[i]);
    }
    qDebug() << "Header Check: ";
    if(checkHeader(header) == false){
        qDebug() << "Wrong Header received!";
        message.clear();                    // ändern
    } else{
        qDebug() << "Correct Header received!";
    }

    return message;
}








