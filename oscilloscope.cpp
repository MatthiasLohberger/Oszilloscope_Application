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


    //connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray)),
    //       this, SLOT(ReceiveData(QByteArray)));

    connect(&BluetoothWindow, SIGNAL(ServiceSelectedForConnection(const QBluetoothServiceInfo &)),
            this, SLOT(startOscilloscope(const QBluetoothServiceInfo &)));

    connect(this, SIGNAL(synchronizeSocket()),
            &bluetoothSocket, SLOT(SocketSynchronisation()));

    connect(this, SIGNAL(sendDefaultCommanLine(ConfigData)),
            &bluetoothSocket, SLOT(setDefaultCommanLine(ConfigData)));




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
    emit sendDefaultCommanLine(OsziConfigData.getData());
    //starting the threads
    bluetoothSocket.moveToThread(&BluetoothThread);
    BluetoothThread.start();
    qDebug() << "Treads started!";


    //Connect to service (EAS Board)
    bluetoothSocket.startClient(service);

    emit ChangeTextConnectButton();
/*
    connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray)),
            this, SLOT(ReceiveData(QByteArray)));
*/

    //Kommandline das erste mal senden
    SendMessage();

    emit synchronizeSocket();

/*
    //Plot starten

    //Send buttons enablen in beiden Windows
    emit EnableSendButtonBtWindow();
    emit EnableSendOsziMainWindowBtWindow();
*/
}



//----------------------------------------------------------------------------

//[Slots zum Empfangen über Bluetooth]

void Oscilloscope::SendMessage(){
     QByteArray message;
     ConfigData CommandLine = OsziConfigData.getData();

     qDebug() << "Send Commandline:";

     message = "";
     message.append((char)0xFF);
     message.append((char)0xFF);

     message.append(CommandLine.Vertical);
     message.append((char)CommandLine.EntranceArea);

     message.append(CommandLine.Horizontal);
     message.append((char)CommandLine.N_Low);
     message.append((char)CommandLine.N_High);

     message.append(CommandLine.Trigger);
     qDebug() << "TriggerThreshold_Low  = " << CommandLine.TriggerThreshold_Low;
     qDebug() << "TriggerThreshold_High = " << CommandLine.TriggerThreshold_High;
     message.append((char)CommandLine.TriggerThreshold_Low);
     message.append((char)CommandLine.TriggerThreshold_High);
     message.append(CommandLine.TriggerMode);
     message.append(CommandLine.TriggerEdge);

     qDebug() << "CommandLine ready to send!";
     qDebug() << "Data Size: " << message.size() << " Byte";


     bluetoothSocket.sendMessage(message);  //calls the real Fnkt.

}



void Oscilloscope::ReceiveData(QByteArray message){
    qDebug() << "+++++++Data Verification+++++++";

    QByteArray header = "";
     for(int i=0; i<=11; i++){
         header.append(message[i]);
     }

    qDebug() << "Header Check: ";
    if(checkHeader(header) == false){
        qDebug() << "Wrong Header received!";


        int i, PosFirstSyncByte = 0, Pos2ndSyncByte = 0;
        qDebug() << "\t-------Start SyncWord Search-------";
        qDebug() << "\tSize of Data: " << message.size();
        for (i=0; i<= 4107; i++){
            if(message.at(i) == 0xff){
                if(PosFirstSyncByte > 0){
                    Pos2ndSyncByte = i;
                    qDebug() << "\t\tSyncByte2 (0xff) found at position i = "
                             << Pos2ndSyncByte << " in the received data.";

                    QByteArray header_Display = "";
                     for(int i=PosFirstSyncByte; i<=PosFirstSyncByte+11; i++){
                         header_Display.append(message[i]);
                     }
                    displayHeader(header_Display);


                }else {
                   PosFirstSyncByte = i;
                    qDebug() << "\t\tSyncByte1 (0xff) found at position i = "
                             << PosFirstSyncByte << " in the received data.";
                }
            }

        }
        qDebug() << "\t-------End SyncWord Search-------";


        message = SocketSynchronisation(message, PosFirstSyncByte);
    } else{
        qDebug() << "Correct Header received!";
    }
    qDebug() << "+++++++End Data Verification+++++++";
    qDebug() << "Data ready to plot!";
    //ReceiveBuffer = message;


    if(flag_connect_readyRead == 1){
        flag_connect_readyRead = 0;
        qDebug() << "\t\t******Reconnect socket";
        bluetoothSocket.connect_readyRead();
    }
}




bool Oscilloscope::checkHeader(const QByteArray &header){
      ConfigData CommandLine = OsziConfigData.getData();
      UIntHeader UintHeaderElements;

      UintHeaderElements.element3.append(header.at(3));
      UintHeaderElements.element5.append(header.at(5));
      UintHeaderElements.element6.append(header.at(6));
      UintHeaderElements.element8.append(header.at(8));
      UintHeaderElements.element9.append(header.at(9));

      QByteArray Element0 = "";
      Element0.append(header.at(0));
      //qDebug() << "First Element: " << Element0.toInt();

    if(     //Element0.toInt() == 255

            header.at(0) == 0xff &&
            header.at(1) == 0xff    &&
            header.at(2) == 'V' &&
            UintHeaderElements.element3.toInt() == CommandLine.EntranceArea &&
            header.at(4) == 'H' &&
            //UintHeaderElements.element5.toUInt() == CommandLine.N_Low &&
            //UintHeaderElements.element6.toUInt() == CommandLine.N_High &&
            header.at(7) == 'T' &&
            //UintHeaderElements.element8.toUInt() == CommandLine.TriggerThreshold_Low &&
            //UintHeaderElements.element8.toUInt() == CommandLine.TriggerThreshold_High &&
            header.at(10) == CommandLine.TriggerMode &&
            header.at(11) == CommandLine.TriggerEdge  ) {
        return true;
    } else {
        return false;
    }
}




QByteArray Oscilloscope::SocketSynchronisation(QByteArray &message, int PosFirstSyncByte){
    //Synchronisation through search for the SyncWort
    bluetoothSocket.disconnect_readyRead();
    qDebug() << "\t\t********Socket disconnected";

    message.remove(0, PosFirstSyncByte);
    qDebug() << "\t\t\tUnnecessary Data removed";
    if(message.size() != 4108 - PosFirstSyncByte){
        //?
    }

    message.append(bluetoothSocket.ReadSocketForSync(PosFirstSyncByte));
    qDebug() << "\t\t\tSyncData appended";
    flag_connect_readyRead = 1;

    QByteArray header = "";
    for(int i=0; i<=11; i++){
             header.append(message[i]);
    }
    qDebug() << "\t\t\tHeader Check after Sync: ";
    if(checkHeader(header) == false){
        qDebug() << "\t\t\tStill wrong Header received!";
        message.clear();                    // ändern
    } else{
        qDebug() << "\t\t\tAfter Sync correct Header received!";
    }

    return message;
}


void Oscilloscope::displayHeader(QByteArray header){

     for(int i = 0; i<header.size(); i++){
         qDebug()  << "\t\t\t\t\tHeader Element " << i << ", Inhalt: " << header.at(i);
     }
}





