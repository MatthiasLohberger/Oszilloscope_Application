#ifndef COMMANDLINE_EAS_BOARD_H
#define COMMANDLINE_EAS_BOARD_H

#include <QByteArray>

class CommandLine_EAS_Board
{
private:
    struct ConfigData {
        char Vertical;              //QString besser?
        int EntranceArea;
        char Horizontal;
        int N_Low;
        int N_High;
        char Trigger;
        int TriggerThresholdLow;
        int TriggerThresholdHigh;
        char TriggerMode;
        char TriggerEdge;

    };

    ConfigData CommandLine;
    QByteArray CommandLine_Byte;


public:
    CommandLine_EAS_Board();

    void setDefault();
    void convert();

    void setEntranceArea(int EntranceArea);                 // Eingangsbereiche kodiert mit Zahlen 1 - 4
    void setN(int N);                                       // Aufteilen in High und Low Teil
    void setTriggerThreshold(int TriggerThreshold);         // Aufteilen in High und Low Teil, unsigned int
    void setTriggerMode(char Mode);                         // A, N oder S
    void setTriggerEdge(char Edge);                         // p oder n

    //get Fnkt

};

#endif // COMMANDLINE_EAS_BOARD_H
