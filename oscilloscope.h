#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QObject>

#include "btwindow.h"
#include "mainwindow.h"
#include "commandline_eas_board.h"

class Oscilloscope : public QObject
{
    Q_OBJECT
public:
    explicit Oscilloscope(QObject *parent = nullptr);
    ~Oscilloscope();
    void showOscilloscopeMainWindow();

    bool checkHeader(const QByteArray &);

private:
    BtWindow BluetoothWindow;
    MainWindow OsziMainWindow;

    CommandLine_EAS_Board OsziConfigData;

    QByteArray ReceiveBuffer;


public slots:

void SendMessage();
void ReceiveData(const QByteArray &);

//void StartOscilloscope();

signals:

};

#endif // OSCILLOSCOPE_H
