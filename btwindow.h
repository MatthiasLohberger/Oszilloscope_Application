#ifndef BTWINDOW_H
#define BTWINDOW_H

#include <QWidget>

#include "commandline_eas_board.h"



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


public slots:
    void ConnectButtonPressed();
    void SendButtonPressed();

    void CloseButtonPressed();

    void NewValuesToSet();          // muss alle Werte auslesen





    //fertig kodiert:

    void newDataForPlainTextWidget(ConfigDataString &);

    void showBluetoothWindow();




private slots:
    void startDeviceSearch();    // Scanning for Bluetooth Devices
    void ConnectToDevice();      // Mit Gerät verbinden


    // fertig kodiert:


signals:
    void newValues();
    void DefaultButtonPressed();



};



#endif // BTWINDOW_H
