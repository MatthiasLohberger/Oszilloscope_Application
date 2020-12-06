#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->SendButton->setEnabled(false);

    //connect(ui->BtSettingsButton, &QToolButton::clicked, this, &MainWindow::showBluetoothWindow);
    connect(ui->BtSettingsButton, SIGNAL(clicked()),
            this, SIGNAL(BtSettingsButtonPressed()));
    connect(ui->SendButton, SIGNAL(clicked()),
            this, SIGNAL(SendButton_Pressed()));
}





MainWindow::~MainWindow()
{
    delete ui;
}


// ------------------------------------------------------------------------------------


void MainWindow::EnableSendButton(){
    ui->SendButton->setEnabled(true);
}
