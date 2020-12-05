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


    connect(&OsziMainWindow, SIGNAL(SendButtonPressed()),
            this, SLOT(SendMessage()));
    connect(&BluetoothWindow, SIGNAL(SendButtonPressed()),
            this, SLOT(SendMessage()));


    connect(&BluetoothWindow, SIGNAL(newDataToPlotReceived(const QByteArray &)),
                                     this, SLOT(ReceiveData(const QByteArray &)));



    OsziConfigData.setDefaultValues();

}

Oscilloscope::~Oscilloscope(){

}


//----------------------------------------------------------------------------


void Oscilloscope::showOscilloscopeMainWindow(){
    OsziMainWindow.showFullScreen();
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

     BluetoothWindow.SocketWrite(message);      //calls the real "socket->write(message);" Fnkt.

}



void Oscilloscope::ReceiveData(const QByteArray & message){
    QByteArray header = "";
     for(int i=0; i<=11; i++){
         header.append(message[i]);
     }
    qDebug() << "Header Check: ";
    if(checkHeader(header) == false){
        qDebug() << "Wrong Header received!";
        return;
    }
    qDebug() << "Correct Header received!";
    ReceiveBuffer = message;

}



bool Oscilloscope::checkHeader(const QByteArray &header){
      ConfigData CommandLine = OsziConfigData.getData();
      UIntHeader UintHeaderElements;

      UintHeaderElements.element3.append(header.at(3));
      UintHeaderElements.element5.append(header.at(5));
      UintHeaderElements.element6.append(header.at(6));
      UintHeaderElements.element8.append(header.at(8));
      UintHeaderElements.element9.append(header.at(9));

      QByteArray Element1 = "";
      Element1.append(header.at(0));

    if(     Element1.toInt() == 255

            /*header.at(0) == 0xFF &&
            header.at(1) == 0xFF   &&
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






