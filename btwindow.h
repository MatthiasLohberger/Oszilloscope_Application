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
    CommandLine_EAS_Board getDataForPlainTextWidget(CommandLine_EAS_Board OsziConfigData);


private:
    Ui::BtWindow *ui;

    ConfigDataString CommandLineStringRef;


public slots:
    void ConnectButtonPressed();
    void SendButtonPressed();
    void DefaultButtonPressed();
    void CloseButtonPressed();

    void BtDeviceSelected();        //für comboBox

    void NewValue_EntranceArea();
    void NewValue_N_High();
    void NewValue_N_Low();
    void NewValue_TriggerHigh();
    void NewValue_TriggerLow();
    void NewValue_TriggerEdge();
    void NewValue_TriggerMode();


private slots:


signals:


};



#endif // BTWINDOW_H
