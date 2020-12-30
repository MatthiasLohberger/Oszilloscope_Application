#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "btwindow.h"
#include "commandline_eas_board.h"
#include "qcustomplot.h"


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
    //void clearPlot();




private:
    Ui::MainWindow *ui;

    QMutex mutexPlot;
    const double T_AD0=125/1000000000;            //Grundsamplezeit in [ns]

    int N_SampleFactor;
    int M_new;
    int M_old;
    int step_down = -1, step_up = 1;


public slots:
    void EnableSendButton();
    void DisableSendButton();

    void ClearPlot();

    void plot(QByteArray data);
    // void scaleAxes(QByteArray CommandLine);



private slots:
    void CaptureTimeWidgetManagement(int step);
    void CaptureTimePlusButtonClicked();
    void CaptureTimeMinusButtonClicked();



signals:
    void BtSettingsButtonPressed();
    void SendButton_Pressed();

};
#endif // MAINWINDOW_H
