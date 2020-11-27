#include "btwindow.h"
#include "ui_btwindow.h"


//[Konstruktor]
BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),                                //Init Liste
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);




    // connect(ui->SearchButton, SIGNAL(), this, SLOT())
    connect(ui->ConnectButton, &QPushButton::clicked, this, &BtWindow::ConnectButtonPressed);
    connect(ui->SendButton, &QPushButton::clicked, this, &BtWindow::SendButtonPressed);
    connect(ui->DefaultButton, SIGNAL(clicked()),
            this, SIGNAL(DefaultButtonPressed()));
    connect(ui->CloseButton, SIGNAL(clicked()),
            this, SLOT(CloseButtonPressed()));

    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geschlossener Zustand
    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geöffneter Zustand


    connect(ui->lineEdit_EntranceArea, SIGNAL(textChanged), this, SLOT(NewValue_EntranceArea));
    connect(ui->lineEdit_N_High, SIGNAL(textChanged), this, SLOT(NewValue_N_High));
    connect(ui->lineEdit_N_Low, SIGNAL(textChanged), this, SLOT(NewValue_N_Low));
    connect(ui->lineEdit_TriggerHigh, SIGNAL(textChanged), SLOT(NewValue_TriggerHigh));
    connect(ui->lineEdit_TriggerLow, SIGNAL(textChanged), SLOT(NewValue_TriggerLow));
    connect(ui->lineEdit_TriggerEdge, SIGNAL(textChanged), SLOT(NewValue_TriggerEdge));
    connect(ui->lineEdit_TriggerMode, SIGNAL(textChanged), this, SLOT(NewValue_TriggerMode));

    // [Construct UI] End


    // [Standartwerte anzeigen]


    /*
    ui->plainTextEdit_EntranceArea->setPlainText(CommandLineStringRef.EntranceArea);
    ui->plainTextEdit_N_High->setPlainText("Test");
    ui->plainTextEdit_N_Low->setPlainText("Test");
    ui->plainTextEdit_TriggerHigh->setPlainText("Test");
    ui->plainTextEdit_TriggerLow->setPlainText("Test");
    ui->plainTextEdit_TriggerEdge->setPlainText(CommandLineStringRef.TriggerEdge);
    ui->plainTextEdit_TriggerMode->setPlainText(CommandLineStringRef.TriggerMode);
    */



    // local oder default adapter für Bt auswählen

    // Bt Server

    // Get local device name




}



//[~Destruktor]
BtWindow::~BtWindow()
{
    delete ui;
}



// Andere Methoden ---------------------------------------------------------

//[Slot Funktionen] Buttons Pressed/Selected

void BtWindow::ConnectButtonPressed(){
    //Connect to Bt Device
}


void BtWindow::SendButtonPressed(){
    //Send to Bt Device
}


void BtWindow::CloseButtonPressed(){
    //Close Bt Win bzw Show Main/Oszi Win
    this->hide();
}


void BtWindow::BtDeviceSelected(){
    //Name in Var speichern, UUID etc. herausfinden und auf connect pressed warten
    //Namen anzeigen
}
//[Slot Funktionen] Buttons Pressed/Selected   End



//-------------------



//[Slot Funktionen] NewValues for ConfigFrame

void BtWindow::NewValue_EntranceArea(){
    //set new Value
}


void BtWindow::NewValue_N_High(){
    //set new Value
}


void BtWindow::NewValue_N_Low(){
    //set new Value
}


void BtWindow::NewValue_TriggerHigh(){
    //set new Value
}


void BtWindow::NewValue_TriggerLow(){
    //set new Value
}


void BtWindow::NewValue_TriggerEdge(){
    //set new Value
}


void BtWindow::NewValue_TriggerMode(){
    //set new Value
}
//[Slot Funktionen] NewValues for ConfigFrame  End---------------------------------------------------------


void BtWindow::newDataForPlainTextWidget(ConfigDataString & CommandLineStringRef){

    ui->lineEdit_EntranceArea->setText(CommandLineStringRef.EntranceArea);
    ui->lineEdit_N_High->setText(CommandLineStringRef.N_High);
    ui->lineEdit_N_Low->setText(CommandLineStringRef.N_Low);
    ui->lineEdit_TriggerHigh->setText(CommandLineStringRef.TriggerThresholdHigh);
    ui->lineEdit_TriggerLow->setText(CommandLineStringRef.TriggerThresholdLow);
    ui->lineEdit_TriggerEdge->setText(CommandLineStringRef.TriggerEdge);
    ui->lineEdit_TriggerMode->setText(CommandLineStringRef.TriggerMode);

    /*
    qDebug() << CommandLineStringRef.EntranceArea;
    qDebug() << CommandLineStringRef.N_High;
    qDebug() << CommandLineStringRef.N_Low;
    qDebug() << CommandLineStringRef.TriggerThresholdHigh;
    qDebug() << CommandLineStringRef.TriggerThresholdLow;
    qDebug() << CommandLineStringRef.TriggerEdge;
    qDebug() << CommandLineStringRef.TriggerMode;
    */

}




void BtWindow::showBluetoothWindow(){
    this->showFullScreen();
}


/*
x.append("0x");     // zur verdeutlichung, dass ausgegebene Zahl hex ist
x.append(CommandLineStringRef.EntranceArea);
ui->lineEdit_EntranceArea->setText(x);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.N_High);
ui->lineEdit_N_High->setText(x);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.N_Low);
ui->lineEdit_N_Low->setText(x);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.N_Low);
ui->lineEdit_TriggerHigh->setText(CommandLineStringRef.TriggerThresholdHigh);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.TriggerThresholdLow);
ui->lineEdit_TriggerLow->setText(x);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.TriggerEdge);
ui->lineEdit_TriggerEdge->setText(x);
x.clear();

x.append("0x");
x.append(CommandLineStringRef.TriggerMode);
ui->lineEdit_TriggerMode->setText(x);
x.clear();

*/







