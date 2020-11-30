#ifndef BTWINDOW_H
#define BTWINDOW_H

#include <QWidget>
#include <QList>

#include<QBluetoothDeviceInfo>
#include<QBluetoothAddress>
#include<QBluetoothLocalDevice>
//#include<QBluetoothHostInfo>

#include "commandline_eas_board.h"
#include"BluetoothSocket.h"
#include"BluetoothDeviceFinder.h"




namespace Ui {
class BtWindow;
}

class BtWindow : public QWidget
{
    Q_OBJECT


public:
    explicit BtWindow(QWidget *parent = nullptr);
    ~BtWindow();

    void connected();

    QString HexNumAsString(QString StringNum);



private:
    Ui::BtWindow *ui;

    ConfigDataString CommandLineStringRef;

    struct BtDeviceInfo{
        QString Name;
        QBluetoothDeviceInfo BtDevice;
    };

    QList<BtDeviceInfo> DiscoveredDevicesList;
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    BluetoothDeviceFinder bluetoothDeviceFinder;


public slots:
    void ConnectButtonPressed();
    void SendButtonPressed();

    void CloseButtonPressed();

    void NewValuesToSet(QString text);          // muss alle Werte auslesen





    //fertig kodiert:

    void newDataForPlainTextWidget(ConfigDataString &);

    void showBluetoothWindow();




private slots:
    void startDeviceSearch();    // Scanning for Bluetooth Devices
    //void ConnectToDevice();      // Mit Gerät verbinden
    void ShowNewBtDevice(const QBluetoothDeviceInfo &);

    // fertig kodiert:


signals:
    void newValues();
    void DefaultButtonPressed();



};



#endif // BTWINDOW_H
