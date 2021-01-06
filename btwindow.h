#ifndef BTWINDOW_H
#define BTWINDOW_H

#include <QWidget>
#include <QList>

//#include<QBluetoothDeviceInfo>
#include<QBluetoothAddress>
#include<QBluetoothLocalDevice>
//#include<QBluetoothHostInfo>

#include "commandline_eas_board.h"
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


private:
    // For the presentation of the Bluetooth Window
    Ui::BtWindow *ui;

    ConfigDataString CommandLineStringRef;

    //For searching new Bluetooth Services
    struct BtServiceInfo{
        QString Name;
        QBluetoothServiceInfo BtService;
    };

    QList<BtServiceInfo> DiscoveredDevicesList;
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    BluetoothServiceFinder bluetoothServiceFinder;




public slots:

    void NewValuesToSet(QString text);          // muss alle Werte auslesen

    //fertig kodiert:
    void CloseButtonPressed();
    void ConnectButtonPressed();
    void Enable_SendButton();
    void Disable_SendButton();

    void setTextConnectButton();
    void newDataForPlainTextWidget(ConfigDataString &);
    void showBluetoothWindow();
    void setTextStatusBar(QString);
    void DisableBtDeviceSelect();

    ConfigDataValuesBtWin readValuesWidgetsBtWindow();
    void setValuesWidgetsBtWindow(ConfigData);


private slots:
    // fertig kodiert:
    void startServiceSearch();    // Scanning for Bluetooth Devices
    void ShowNewBtService(const QBluetoothServiceInfo &);


signals:
    void newValues();
    void DefaultButtonPressed();
    void SendButtonPressed();
    void ServiceSelectedForConnection(const QBluetoothServiceInfo &);
    void DefaultButtonClicked();

    //void newDataToPlotReceived(const QByteArray &);

};



#endif // BTWINDOW_H
