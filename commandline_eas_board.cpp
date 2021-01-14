#include "commandline_eas_board.h"



//---[Construktor]---
CommandLine_EAS_Board::CommandLine_EAS_Board(QObject *parent) : QObject(parent)
{
    //setDefaultValues();

    //CommandLine_Byte.resize(9);     //richtige Größe ??????????????
    //convertToByteArray();

    //convertToString();    // -> in der set Default enthalten
}

//---[Constructor] End---






//----------------------------------------------------------------------------------------



//---[Convert/ Default Functions]---

void CommandLine_EAS_Board::setDefaultValues(){

    CommandLine.EntranceArea = 1;
    CommandLine.N = 1;
    CommandLine.TriggerThreshold = 2048;    //LowByte eig 0x02 und High eig 0x08
    CommandLine.TriggerMode = 'A';
    CommandLine.TriggerEdge = 'p';

    convertToString();

    emit newConfigData(CommandLine_String);       //Signal aussenden

    qDebug() << "CommandLine set to Default!";

    //!!!!!   fehlt:    !!!!!!
    //!
    // convertToByteArray()
    // etc
    // update oszi
    // uptade Anzeigen (BtWin und Oszi-/MainWin
    // -> mit Signals uns Slots arbeiten
}





void CommandLine_EAS_Board::setConfigData(ConfigData NewConfigData){
    CommandLine.EntranceArea = NewConfigData.EntranceArea;
    CommandLine.N = NewConfigData.N;

    CommandLine.TriggerThreshold = NewConfigData.TriggerThreshold;    //LowByte eig 0x02 und High eig 0x08
    CommandLine.TriggerMode = NewConfigData.TriggerMode;
    CommandLine.TriggerEdge = NewConfigData.TriggerEdge;

    convertToString();
    // in this method the high and lowm bytes are also determined

    emit newConfigData(CommandLine_String);       //Signal aussenden

    qDebug() << "CommandLine set to new Values!";
    qDebug() << "N = " << NewConfigData.N;
}





void CommandLine_EAS_Board::convertToString(){

    CommandLine_String.EntranceArea.setNum(CommandLine.EntranceArea, 16);

    qDebug() << "CommandLine convert to QString!";
    TwoBytes hByte = ValueToHighAndLowByte(1);     //1 -> N Wird berechnet
    CommandLine_String.N_Low.setNum(hByte.ByteLow, 16);
    CommandLine_String.N_High.setNum(hByte.ByteHigh, 16);

    hByte = ValueToHighAndLowByte(2);     //2 -> Trigger Threshold wird berechnet
    CommandLine_String.TriggerThresholdLow.setNum(hByte.ByteLow, 16);
    CommandLine_String.TriggerThresholdHigh.setNum(hByte.ByteHigh, 16);

    CommandLine_String.TriggerMode = CommandLine.TriggerMode;
    CommandLine_String.TriggerEdge = CommandLine.TriggerEdge;

}






TwoBytes CommandLine_EAS_Board::ValueToHighAndLowByte(int x){
    QString hArray[2];
    QString hString;
    int hValue;                // unsigened richtig   ??????
    //unsigned int hArrayInt[1];
    TwoBytes hByte;
    int size, i;

    //qDebug() << "x: " << x;
    switch(x){                           // X=1 -> N berechnet, x = 2 -> Trigger berechnet
        case 1: hValue = CommandLine.N; break;
        case 2: hValue = CommandLine.TriggerThreshold; break;
    }
    //qDebug() << "Wert: " << hValue;

    if(hValue <= 255){                          // Highbyte == 0
           hArray[0].setNum(hValue, 2);         // Low Byte
           hArray[1].setNum(00000000, 2);       // High Byte

           //qDebug() << "Wert <= 255, LowByte: " << hArray[0];
           //qDebug() << "Wert <= 255, HighByte: " << hArray[1];
    }
    else if (hValue > 255){
            hString.setNum(hValue, 2);
            size = hString.size();
            //qDebug() << "Size HString (binär Zahl): " << size;


            for (i=size-8; i<=size-1; i++){
                hArray[0].append(hString.data()[i]);        //Low Byte
            }
            //qDebug() << "Wert > 255, LowByte: " << hArray[0];


            for (i=0; i<size-8; i++){
                hArray[1].append(hString.data()[i]);        //Highbyte
            }
            //qDebug() << "Wert > 255, HighByte: " << hArray[1];
     }

    //hier ggf HighByte mit Nullen auffüllen

    //hArrayInt[0] = hArray[0].toInt(nullptr, 2);
    //hArrayInt[1] = hArray[1].toInt(nullptr, 2);
    //qDebug() << "Wert wieder als Int, LowByte: " << hArrayInt[0];
    //qDebug() << "Wert wieder als Int, HighByte: " << hArrayInt[1];

    hByte.ByteLow = hArray[0].toInt(nullptr, 2);
    hByte.ByteHigh = hArray[1].toInt(nullptr, 2);

    switch(x){
        case 1:
            CommandLine.N_Low = hByte.ByteLow;
            CommandLine.N_High = hByte.ByteHigh;
            break;
        case 2:
            CommandLine.TriggerThreshold_Low = hByte.ByteLow;
            CommandLine.TriggerThreshold_High = hByte.ByteHigh;
            break;
    }
            /*
            hString2.append(ByteH);
            hString2.append(ByteL);
            qDebug() << "Wieder zusammengesetzt:   " << hString2;
            y = hString2.toInt(nullptr, 2);
            qDebug() << "Wieder als Int: " << y;
            */

    //qDebug() << "StructInhalt Testfnkt. , LowByte: " << hByte.ByteLow;
    //qDebug() << "StructInhalt Testfnkt. , HighByte: " << hByte.ByteHigh;

    return hByte;
}






void CommandLine_EAS_Board:: convertToByteArray(){
    //CommandLine_Byte[0] =
    //CommandLine_Byte[1] =
    //CommandLine_Byte[2] =
    //CommandLine_Byte[3] =
    //CommandLine_Byte[4] =
    //CommandLine_Byte[5] =
    //CommandLine_Byte[6] =
    //CommandLine_Byte[7] =
    //CommandLine_Byte[8] =
    //CommandLine_Byte[9] =

}


//---[Convert Functions] End---






//----------------------------------------------------------------------------------------
//[Slots]

void CommandLine_EAS_Board::DefaultValues(){
    qDebug() << "Default ValuesSlot";
    setDefaultValues();
}









//----------------------------------------------------------------------------------------






// ---[Set Functions]---
void CommandLine_EAS_Board::setEntranceArea(int EntranceArea){
    CommandLine.EntranceArea = EntranceArea;
}


void CommandLine_EAS_Board::setN(unsigned int N){
     CommandLine.N = N;
}


void CommandLine_EAS_Board::setTriggerThreshold(unsigned int TriggerThreshold){
     CommandLine.TriggerThreshold = TriggerThreshold;
}


void CommandLine_EAS_Board::setTriggerMode(char Mode){
    CommandLine.TriggerMode = Mode;
}


void CommandLine_EAS_Board::setTriggerEdge(char Edge){
    CommandLine.TriggerEdge = Edge;
}
// ---[Set Functions] End---





//----------------------------------------------------------------------------------------





//---[get Fnkt]---
ConfigData CommandLine_EAS_Board::getData(){
    return CommandLine;
}

ConfigDataString CommandLine_EAS_Board::getDataString(){
    return CommandLine_String;
}

//---[get Fnkt] End---
