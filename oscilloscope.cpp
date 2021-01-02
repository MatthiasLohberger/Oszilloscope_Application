 #include "oscilloscope.h"


Oscilloscope::Oscilloscope(QObject *parent) : QObject(parent)
{
    // Fensterwechsel
    connect(&OsziMainWindow, SIGNAL(BtSettingsButtonPressed()),
            &BluetoothWindow, SLOT(showBluetoothWindow()));
                // Zurückwechseln mit hide im BTWin direkt


    // Kommandozeile
    connect(&OsziConfigData, SIGNAL(newConfigData(ConfigDataString &)),
            &BluetoothWindow, SLOT(newDataForPlainTextWidget(ConfigDataString &)));


    // Buttons und Textausgaben
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


    // Bluetooth Service Suche
    connect(&BluetoothWindow, SIGNAL(ServiceSelectedForConnection(const QBluetoothServiceInfo &)),
            this, SLOT(SetUpOscilloscope(const QBluetoothServiceInfo &)));


    //Bluetooth Socket
    connect(this, SIGNAL(synchronizeSocket()),
            &bluetoothSocket, SLOT(SocketSynchronisation()));

    connect(this, SIGNAL(sendDefaultCommanLine(ConfigData)),
            &bluetoothSocket, SLOT(setDefaultCommanLine(ConfigData)));

    connect(this, SIGNAL(connectSocketToReadyRead()),
            &bluetoothSocket, SLOT(connectReadyRead()));

    connect(this, SIGNAL(disconnectSocketFromReadyRead()),
            &bluetoothSocket, SLOT(disconnect_readyRead()));



    connect(&bluetoothSocket, SIGNAL(StartNormalTransmission()),
            this, SLOT(startOscilloscope()));



    //connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray)),
    //       this, SLOT(ReceiveData(QByteArray)));

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





void Oscilloscope::SetUpOscilloscope(const QBluetoothServiceInfo &service){
    qDebug() << "Start Oscilloscope!";
    emit sendDefaultCommanLine(OsziConfigData.getData());

    //starting the threads
    bluetoothSocket.moveToThread(&BluetoothThread);
    BluetoothThread.start();
    //OsziMainWindow.moveToThread(&PlotThread);
    //PlotThread.start();
    qDebug() << "Treads started!";


    //Connect to service (EAS Board)
    bluetoothSocket.startClient(service);

    emit ChangeTextConnectButton();


    //Kommandline das erste mal senden
    SendMessage();

    emit synchronizeSocket();

}




void Oscilloscope::startOscilloscope(){
    qDebug() << "Starting plot and transmission...";

    connect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray)),
            this, SLOT(ReceiveData(QByteArray)));

    connect(this, SIGNAL(DataReadyToPlot(QByteArray)),
            &OsziMainWindow, SLOT(plot(QByteArray)));


    //Send buttons enablen in beiden Windows
    emit EnableSendButtonBtWindow();
    emit EnableSendOsziMainWindowBtWindow();

    //Connect Sinal readyRead von socket
    emit connectSocketToReadyRead();
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

     OsziMainWindow.scaleAxesAndRange(CommandLine);

}





void Oscilloscope::ReceiveData(QByteArray message){
    qDebug() << "+++++++Data Verification+++++++";
    qDebug() << "Size of Data: " << message.size();


    // Header extrahieren
    QByteArray header = "";
     for(int i=0; i<=11; i++){
         header.append(message[i]);
     }

    // Header Check
    qDebug() << "Header Check: ";
    if(checkHeader(header) == false){
        qDebug() << "Wrong Header received!";

        StopAndRestartOscilloscope();

        //Aufruf Slot für
                // Plot stoppen
                // Bluetooth Übertragung stoppen
                // Plot fenster clearen
                // rteadyRead und receiveData disconnecten
                // SocketSynchronsitaion im Bluetooth Socket aufrufen

                // Diese Fnkt nicht mehr weiter ausführen!!!!!

    } else{
        qDebug() << "Correct Header received!";


        qDebug() << "+++++++End Data Verification+++++++";
        qDebug() << "Data ready to plot!";
        //ReceiveBuffer = message;




        /*
        if(flag_connect_readyRead == 1){
            flag_connect_readyRead = 0;
            qDebug() << "\t\t******Reconnect socket";
        .connect_readyRead();
        }
        */
        emit DataReadyToPlot(message);

     }
}






bool Oscilloscope::checkHeader(const QByteArray &header){
    ConfigData CommandLine = OsziConfigData.getData();

    if(

            header.at(0) == 0xff &&
            header.at(1) == 0xff &&
            header.at(2) == CommandLine.Vertical &&
            header.at(3) == (char)CommandLine.EntranceArea &&
            header.at(4) == CommandLine.Horizontal &&
            header.at(5) == (char)CommandLine.N_Low &&
            header.at(6) == (char)CommandLine.N_High &&
            header.at(7) == CommandLine.Trigger &&
            //header.at(8) == (char)CommandLine.TriggerThreshold_Low &&
            header.at(8) == (char)0 &&
            header.at(9) == (char)CommandLine.TriggerThreshold_High &&
            header.at(10) == CommandLine.TriggerMode &&
            header.at(11) == CommandLine.TriggerEdge )
    {
        return true;
    } else {
        return false;
    }
}





/*
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
*/








/*
void Oscilloscope::displayHeader(QByteArray header){

     for(int i = 0; i<header.size(); i++){
         qDebug()  << "\t\t\t\t\tHeader Element " << i << ", Inhalt: " << header.at(i);
     }
}
*/









/*
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
*/




void Oscilloscope::stopOszilloscope(){
    // Disconnect der Signale für receive Data und Plot
    disconnect(&bluetoothSocket, SIGNAL(newDataReceived(QByteArray)),
            this, SLOT(ReceiveData(QByteArray)));

    disconnect(this, SIGNAL(DataReadyToPlot(QByteArray)),
            &OsziMainWindow, SLOT(plot(QByteArray)));


    emit disconnectSocketFromReadyRead();


    // Treads stoppen
    BluetoothThread.exit();
        //PlotThread.exit();


    // Send Buttons disablen
    BluetoothWindow.Disable_SendButton();
    OsziMainWindow.DisableSendButton();

     qDebug() << "Signals disconnected, Buttons disabled, Threads stopped!";

    // Plot leeren
    OsziMainWindow.ClearPlot();

    // (set default values)
        // scale Axes and
}


void Oscilloscope::StopAndRestartOscilloscope(){
    qDebug() << "Stop normal Transmission";
    stopOszilloscope();

     qDebug() << "Try Resynchronisation!";
    bluetoothSocket.SocketSynchronisation();
}














