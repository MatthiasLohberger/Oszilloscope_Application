#ifndef BTWINDOW_H
#define BTWINDOW_H

#include <QWidget>
#include <QList>

//#include<QBluetoothDeviceInfo>
#include<QBluetoothAddress>
#include<QBluetoothLocalDevice>
//#include<QBluetoothHostInfo>

#include "commandline_eas_board.h"
#include"BluetoothSocket.h"
#include"BluetoothServiceFinder.h"




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

    void SocketWrite(const QByteArray &message);



private:
    Ui::BtWindow *ui;

    ConfigDataString CommandLineStringRef;

    struct BtServiceInfo{
        QString Name;
        QBluetoothServiceInfo BtService;
    };

    QList<BtServiceInfo> DiscoveredDevicesList;
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    BluetoothServiceFinder bluetoothServiceFinder;

    BluetoothSocket bluetoothSocket;


public slots:
    //void ConnectButtonPressed();


    void CloseButtonPressed();

    void NewValuesToSet(QString text);          // muss alle Werte auslesen





    //fertig kodiert:

    void newDataForPlainTextWidget(ConfigDataString &);

    void showBluetoothWindow();




private slots:
    //void sendConfigData();

    // fertig kodiert:

    void startServiceSearch();    // Scanning for Bluetooth Devices
    void ConnectToService();      // Mit Gerät verbinden
    void ShowNewBtService(const QBluetoothServiceInfo &);




signals:
    void newValues();
    void DefaultButtonPressed();
    void SendButtonPressed();

    void newDataToPlotReceived(const QByteArray &);


};



#endif // BTWINDOW_H
