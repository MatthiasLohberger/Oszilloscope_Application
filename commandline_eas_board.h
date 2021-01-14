#ifndef COMMANDLINE_EAS_BOARD_H
#define COMMANDLINE_EAS_BOARD_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include<QDebug>


struct ConfigData {

    char Vertical = 'V';              //QString besser?
    int EntranceArea;

    char Horizontal = 'H';
    int N;                         //Aufspalten in High und Low Byte (hier unsigned richtig:       ???????)
    int N_Low;
    int N_High;

    char Trigger = 'T';
    int TriggerThreshold ;         //Aufspalten in High und Low Byte (hier unsigned richtig:       ???????)
    int TriggerThreshold_Low;
    int TriggerThreshold_High;


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


struct TwoBytes{
    int ByteLow;
    int ByteHigh;
};



// ----------------------------------------------------------------------------------------------------



class CommandLine_EAS_Board: public QObject
{
     Q_OBJECT

private:

    ConfigData CommandLine;                     // CommandLine in int und char
    //QByteArray CommandLine_Byte;                // CommandLine in QByte zum versenden über Bt
    ConfigDataString CommandLine_String;        // CommandLine als Strings zur Anzeige im Bt Window


public:
    //Konstruktor
    CommandLine_EAS_Board(QObject *parent = nullptr);

    //set Attributes
    void setDefaultValues();
    void setConfigData(ConfigData );
    void convertToByteArray();
    void convertToString();

    TwoBytes ValueToHighAndLowByte(int);                // X=1 -> N berechnet, x = 2 -> Trigger berechnet

    // set single values
    void setEntranceArea(int EntranceArea);                 // Eingangsbereiche kodiert mit Zahlen 1 - 4
    void setN(unsigned int N);                                       // Aufteilen in High und Low Teil
    void setTriggerThreshold(unsigned int TriggerThreshold);         // Aufteilen in High und Low Teil, unsigned int
    void setTriggerMode(char Mode);                         // A, N oder S
    void setTriggerEdge(char Edge);                         // p oder n

    //get Fnkt
    ConfigData getData();
    ConfigDataString getDataString();


public slots:
   void DefaultValues();


signals:
    void newConfigData(ConfigDataString &);

};




struct UIntHeader{
    QByteArray element3 = "";
    QByteArray element5 = "";
    QByteArray element6 = "";
    QByteArray element8 = "";
    QByteArray element9 = "";
};



struct ConfigDataValuesMainWin{
    int CaptureTime_N;
    int TriggerCounter;
    int EntranceVoltageCounter;

};

struct ConfigDataValuesBtWin{
    char TriggerMode;
    char TriggerEdge;
};
#endif // COMMANDLINE_EAS_BOARD_H

