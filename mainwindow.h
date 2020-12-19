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
    void startPlot();
    void stopPlot();
    void clearPlot();



private:
    Ui::MainWindow *ui;



public slots:
    void EnableSendButton();

signals:
    void BtSettingsButtonPressed();
    void SendButton_Pressed();

};
#endif // MAINWINDOW_H
