 #ifndef COMMANDLINE_EAS_BOARD_H
#define COMMANDLINE_EAS_BOARD_H

#include <QByteArray>
#include <QString>

class CommandLine_EAS_Board
{
private:
    struct ConfigData {
        char Vertical;              //QString besser?
        int EntranceArea;
        char Horizontal;
        // hier unsigned richtig:       ???????
        unsigned int N; //Aufspalten in High und Low Byte

        char Trigger;

        unsigned int TriggerThreshold ; //Aufspalten in High und Low Byte

        char TriggerMode;
        char TriggerEdge;

    };

    struct ConfigDataString {
        //QString Vertical;
        QString EntranceArea;
        //QString Horizontal;
        QString N_Low;
        QString N_High;
        //QString Trigger;
        QString TriggerThresholdLow;
        QString TriggerThresholdHigh;
        QString TriggerMode;
        QString TriggerEdge;

    };



    ConfigData CommandLine;                     // CommandLine in int und char
    QByteArray CommandLine_Byte;                // CommandLine in QByte zum versenden über Bt
    ConfigDataString CommandLine_String;        // CommandLine als Strings zur Anzeige im Bt Window


public:
    CommandLine_EAS_Board();

    /*
    struct ConfigDataShow {

        int EntranceArea;

        int N_Low;
        int N_High;

        int TriggerThresholdLow;
        int TriggerThresholdHigh;
        char TriggerMode;
        char TriggerEdge;

    };
    */



    void setDefaultValues();
    void convertToByteArray();
    void convertToString();

    ByteStruct ValueToHighAndLowByte(int x);                // X=1 -> N berechnet, x = 2 -> Trigger berechnet

    void setEntranceArea(int EntranceArea);                 // Eingangsbereiche kodiert mit Zahlen 1 - 4
    void setN(int N);                                       // Aufteilen in High und Low Teil
    void setTriggerThreshold(int TriggerThreshold);         // Aufteilen in High und Low Teil, unsigned int
    void setTriggerMode(char Mode);                         // A, N oder S
    void setTriggerEdge(char Edge);                         // p oder n



    //get Fnkt

};

#endif // COMMANDLINE_EAS_BOARD_H
