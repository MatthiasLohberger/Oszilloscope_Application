#include "commandline_eas_board.h"



// [Construktor]
CommandLine_EAS_Board::CommandLine_EAS_Board()
{
    setDefaultValues();
    CommandLine_Byte.resize(9);
    convertToByteArray();

    convertToString();
}
// [Constructor] End






void CommandLine_EAS_Board::setDefaultValues(){

    CommandLine.EntranceArea = 1;
    CommandLine.N = 1;
    CommandLine.TriggerThreshold = 2050;    //LowByte eig 0x02 und High eig 0x08
    CommandLine.TriggerMode = 'A';
    CommandLine.TriggerEdge = 'p';

    convertToString();

    //!!!!!   fehlt:    !!!!!!

    // convertToByteArray()
    // etc
    // update oszi
    // uptade Anzeigen (BtWin und Oszi-/MainWin
    // -> mit Signals uns Slots arbeiten
}








// [Convert Functions]
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


void CommandLine_EAS_Board::convertToString(){
   unsigned int *hPtr1, *hPtr2;

    CommandLine_String.EntranceArea.setNum(CommandLine.EntranceArea, 16);

    hPtr1 = ValueToHighAndLowByte(1);     //1 -> N Wird berechnet
    CommandLine_String.N_Low.setNum(hPtr1[0], 16);
    CommandLine_String.N_High.setNum(hPtr1[1], 16);

    hPtr2 = ValueToHighAndLowByte(2);     //2 -> Trigger Threshold Wird berechnet
    CommandLine_String.TriggerThresholdLow.setNum(hPtr2[0], 16);
    CommandLine_String.TriggerThresholdHigh.setNum(hPtr2[0], 16);

    CommandLine_String.TriggerMode = CommandLine.TriggerMode;
    CommandLine_String.TriggerEdge = CommandLine.TriggerEdge;

}


unsigned int* CommandLine_EAS_Board::ValueToHighAndLowByte(int x){
    QString hArray[1];

    QString hString;
    unsigned int hValue;                // unsigened richtig   ??????

    unsigned int hArrayInt[2];
    unsigned int *hptr = hArrayInt;

    int size, i;

    switch(x){                           // X=1 -> N berechnet, x = 2 -> Trigger berechnet
        case 1: hValue = CommandLine.N; break;
        case 2: hValue = CommandLine.TriggerThreshold; break;
    }

    if(hValue <= 255){                          // Highbyte == 0
           hArray[0].setNum(hValue, 2);         // Low Byte
           hArray[1].setNum(00000000, 2);       // Low Byte
    }
    else if (hValue > 255){

            hString.setNum(x, 2);
            size = hString.size();

            for (i=size-8; i<=size-1; i++){
                hArray[0].append(hString.data()[i]);        //Low Byte
            }

            for (i=0; i<size-8; i++){
                hArray[1].append(hString.data()[i]);        //Highbyte
            }
     }

    //hier ggf HighByte mit Nullen auffüllen

    hArrayInt[0] = hArray[0].toInt(nullptr, 2);
    hArrayInt[1] = hArray[1].toInt(nullptr, 2);


    //qDebug() << "IntZahl: " << x << "-> binär: " << hString
    //         << "bzw. ByteLow: " << ByteL << "+" << "ByteHigh: " << ByteH;

            /*
            hString2.append(ByteH);
            hString2.append(ByteL);
            qDebug() << "Wieder zusammengesetzt:   " << hString2;
            y = hString2.toInt(nullptr, 2);
            qDebug() << "Wieder als Int: " << y;
            */

    return hptr;
}
// [Convert Functions] End








// [Set Functions]
void CommandLine_EAS_Board::setEntranceArea(int EntranceArea){
    CommandLine.EntranceArea = EntranceArea;
}


void CommandLine_EAS_Board::setN(unsigned int N){
     CommandLine.N = N;
}


void CommandLine_EAS_Board::setTriggerThreshold(unsigned int TriggerThreshold){
     CommandLine.TriggerThreshold = TriggerThreshold;
}


void CommandLine_EAS_Board::setTriggerMode(QChar Mode){
    CommandLine.TriggerMode = Mode;
}


void CommandLine_EAS_Board::setTriggerEdge(QChar Edge){
    CommandLine.TriggerEdge = Edge;
}
// [Set Functions] End



//[get Fnkt]
ConfigData CommandLine_EAS_Board::getData(){
    return CommandLine;
}

ConfigDataString CommandLine_EAS_Board::getDataString(){
    return CommandLine_String;
}
