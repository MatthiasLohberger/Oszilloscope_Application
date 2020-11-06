#include "commandline_eas_board.h"



// [Construktor]
CommandLine_EAS_Board::CommandLine_EAS_Board()
{
    setDefaultValues();
    CommandLine_Byte.resize(9);
    convertToByteArray();
}
// [Constructor] End






void CommandLine_EAS_Board::setDefaultValues(){
    CommandLine.Vertical = 'V';
    CommandLine.EntranceArea = 1;
    CommandLine.Horizontal = 'H';
    CommandLine.N_Low = 1;
    CommandLine.N_High = 0;
    CommandLine.Trigger = 'T';
    CommandLine.TriggerThresholdLow = 0;
    CommandLine.TriggerThresholdHigh = 8;
    CommandLine.TriggerMode = 'A';
    CommandLine.TriggerEdge = 'p';



    //!!!!!   fehlt:    !!!!!!

    // convertToByteArray()
    // convertToString() evtl
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
    CommandLine_String.EntranceArea.setNum(CommandLine.EntranceArea, 2);

}


QString* CommandLine_EAS_Board::ValueToHighAndLowByte(int x){
    QString hArray[1];
    QString *hptr = hArray;
    QString hString;
    unsigned int hValue;                // unsigened richtig   ??????

    switch(x){                           // X=1 -> N berechnet, x = 2 -> Trigger berechnet
        case 1: hValue = CommandLine.N; break;
        case 2: hValue = CommandLine.TriggerThreshold; break;
    }

    if(hValue <= 255){
           hArray[0].setNum(hValue, 2);     // Low Byte
           hArray[1].setNum(00000000, 2);     // Low Byte
    }
    else if (hValue > 255){
        hString.setNum(hValue, 2);

        //hArray[0]
        //hArray[1]

        //Length oder size
        //section
        //insert
        //to Int
        //setNum





    return hptr;
}
// [Convert Functions] End








// [Set Functions]
void CommandLine_EAS_Board::setEntranceArea(int EntranceArea){
    CommandLine.EntranceArea = EntranceArea;
}


void CommandLine_EAS_Board::setN(int N){
    //CommandLine.N_Low =
    //CommandLine.N_High =
}


void CommandLine_EAS_Board::setTriggerThreshold(int TriggerThreshold){
    //CommandLine.TriggerThresholdLow =
    //CommandLine.TriggerThresholdHigh =
}


void CommandLine_EAS_Board::setTriggerMode(char Mode){
    CommandLine.TriggerMode = Mode;
}


void CommandLine_EAS_Board::setTriggerEdge(char Edge){
    CommandLine.TriggerEdge = Edge;
}
// [Set Functions] End
