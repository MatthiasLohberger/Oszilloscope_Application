#ifndef BLUETOOTH_WINDOW_H
#define BLUETOOTH_WINDOW_H

#include <QDialog>

#include "commandline_eas_board.h"

namespace Ui {
class bluetooth_window;
}

class bluetooth_window : public QDialog
{
    Q_OBJECT



public:
    //explicit bluetooth_window(QWidget *parent, CommandLine_EAS_Board &OsziConfigData);
    explicit bluetooth_window(QDialog *parent = nullptr);
    ~bluetooth_window();

    void connected();



private:
    Ui::bluetooth_window *ui;



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

#endif // BLUETOOTH_WINDOW_H
