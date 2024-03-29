#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include <QObject>
#include <QThread>

#include "btwindow.h"
#include "mainwindow.h"
#include "commandline_eas_board.h"
#include "BluetoothSocket.h"

class Oscilloscope : public QObject
{
    Q_OBJECT
    //QThread PlotThread;
    QThread BluetoothThread;

public:
    explicit Oscilloscope(QObject *parent = nullptr);
    ~Oscilloscope();
    void showOscilloscopeMainWindow();

    bool checkHeader(const QByteArray &);
    QByteArray SocketSynchronisation(QByteArray &message, int);
    void displayHeader(QByteArray);


private:
    BtWindow BluetoothWindow;
    MainWindow OsziMainWindow;

    CommandLine_EAS_Board OsziConfigData;

    BluetoothSocket bluetoothSocket;
    int flag_connect_readyRead;
    bool FreezeFlag;        //true = unfreezed, false = freezed

    //QByteArray ReceiveBuffer;



public slots:
    void SendMessage();                                     //Sending a message via socket
    void ReceiveData(QByteArray);                           //Receive Data via socket

    void SetUpOscilloscope(const QBluetoothServiceInfo &service);   //Connect to a discovered service via Socket
                                                                    //Starting threads for bluetooth transmission and plot
    void startOscilloscope();

    void stopOszilloscope();
    void StopAndRestartOscilloscope();

    void DefaultButtonClicked();
    void SendButtonPressed();

    void FreezePlot();      //Freeze Button MainWinClicked

    void ConnectionToServiceLost();
    void DisconnectButtonClicked();
    void DisconnectServiceAndPrepareForNewDiscovery();






signals:
    void ChangeTextConnectButton();
    void EnableSendButtonBtWindow();
    void EnableSendOsziMainWindowBtWindow();
    void synchronizeSocket();
    void sendDefaultCommandLine(ConfigData);
    void connectSocketToReadyRead();
    void disconnectSocketFromReadyRead();
    void DataReadyToPlot(QByteArray);
};

#endif // OSCILLOSCOPE_H
