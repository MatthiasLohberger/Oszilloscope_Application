#ifndef COMMANDLINE_EAS_BOARD_H
#define COMMANDLINE_EAS_BOARD_H

#include <QByteArray>
#include <QString>


struct ConfigData {

    const QChar Vertical = 'V';              //QString besser?
    int EntranceArea;

    const QChar Horizontal = 'H';
    unsigned int N;                         //Aufspalten in High und Low Byte (hier unsigned richtig:       ???????)


    const QChar Trigger = 'T';
    unsigned int TriggerThreshold ;         //Aufspalten in High und Low Byte (hier unsigned richtig:       ???????)

    QChar TriggerMode;
    QChar TriggerEdge;
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




class CommandLine_EAS_Board
{
private:

    ConfigData CommandLine;                     // CommandLine in int und char
    QByteArray CommandLine_Byte;                // CommandLine in QByte zum versenden über Bt
    ConfigDataString CommandLine_String;        // CommandLine als Strings zur Anzeige im Bt Window


public:
    CommandLine_EAS_Board();

    void setDefaultValues();
    void convertToByteArray();
    void convertToString();

    unsigned int* ValueToHighAndLowByte(int x);                // X=1 -> N berechnet, x = 2 -> Trigger berechnet

    void setEntranceArea(int EntranceArea);                 // Eingangsbereiche kodiert mit Zahlen 1 - 4
    void setN(unsigned int N);                                       // Aufteilen in High und Low Teil
    void setTriggerThreshold(unsigned int TriggerThreshold);         // Aufteilen in High und Low Teil, unsigned int
    void setTriggerMode(QChar Mode);                         // A, N oder S
    void setTriggerEdge(QChar Edge);                         // p oder n

    //get Fnkt
    ConfigData getData();
    ConfigDataString getDataString();
};

#endif // COMMANDLINE_EAS_BOARD_H

