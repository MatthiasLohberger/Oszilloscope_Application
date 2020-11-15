#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->BtSettingsButton, &QToolButton::clicked, this, &MainWindow::showBluetoothWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::showBluetoothWindow(){
    BluetoothWindow.show();
}
