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

    void showOscilloscopeMainWindow();

private:
    BtWindow BluetoothWindow;
    MainWindow OsziMainWindow;
    CommandLine_EAS_Board OsziConfigData;

public slots:


signals:

};

#endif // OSCILLOSCOPE_H
