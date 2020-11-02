#include "commandline_eas_board.h"

CommandLine_EAS_Board::CommandLine_EAS_Board()
{
    setDefault();
    CommandLine_Byte.resize(9);
    convert();
}



void CommandLine_EAS_Board::setDefault(){
    CommandLine.Vertical = 'V';
    //CommandLine.EntranceArea =
    CommandLine.Horizontal = 'H';
    //CommandLine.N_Low =
    //CommandLine.N_High =
    CommandLine.Trigger = 'T';
    //CommandLine.TriggerThresholdLow =
    //CommandLine.TriggerThresholdHigh =
    CommandLine.TriggerMode = 'A';
    CommandLine.TriggerEdge = 'p';
}



void CommandLine_EAS_Board::convert(){
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
