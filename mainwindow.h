#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "btwindow.h"
#include "commandline_eas_board.h"
#include "qcustomplot.h"

#include "math.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetUpPlot();
    //void startPlot();
    //void stopPlot();





private:
    Ui::MainWindow *ui;

    QMutex mutexPlot;


    //scale axes and range
    const float T_AD0=125*pow(10, -9);  //Grundsamplezeit 125 [ns]
    int N_SampleFactor;
    float y_OneSidedEntranceVoltage;
    float t;
    float xMin;
    float T_AD;                         // Sample Zeit pro Wert(T_AD = TAD0*N)
    int CorrectionFactor;

    // Capture Time Widget
    int CaptureTimeCounter_new;
        //int CaptureTimeCounter_old;
        //int step_down = -1, step_up = 1;

    // EntranceVoltage Widget
    int EntranceVoltageCounter;


public slots:
    void EnableSendButton();
    void DisableSendButton();

    void ClearPlot();

    void plot(QByteArray data);
    void scaleAxesAndRange(ConfigData);

    void setDefaultValuesManually();
    //void setDefaultValues(ConfigData);
    ConfigDataValuesMainWin readValuesWidgetsMainWindow();
    void setValuesWidgetsMainWindow(ConfigData);



private slots:
    void CaptureTimeWidgetManagement(int step);
    void CaptureTimePlusButtonClicked();
    void CaptureTimeMinusButtonClicked();

    void EntranceVoltageWidgetManagement(int step);
    void EntranceVoltagePlusButtonClicked();
    void EntranceVoltageMinusButtonClicked();



signals:
    void BtSettingsButtonPressed();
    void SendButton_Pressed();

};
#endif // MAINWINDOW_H
