#include "btwindow.h"
#include "ui_btwindow.h"


//[Konstruktor]
BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),                                //Init Liste
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);





    connect(ui->ConnectButton, &QPushButton::clicked, this, &BtWindow::ConnectButtonPressed);
    connect(ui->SendButton, &QPushButton::clicked, this, &BtWindow::SendButtonPressed);
    connect(ui->DefaultButton, SIGNAL(clicked), this, SIGNAL(DefaultButtonPressed));
    connect(ui->CloseButton, &QPushButton::clicked, this, &BtWindow::CloseButtonPressed);

    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geschlossener Zustand
    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geöffneter Zustand

    connect(ui->plainTextEdit_EntranceArea, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_EntranceArea);
    connect(ui->plainTextEdit_N_High, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_N_High);
    connect(ui->plainTextEdit_N_Low, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_N_Low);
    connect(ui->plainTextEdit_TriggerHigh, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_TriggerHigh);
    connect(ui->plainTextEdit_TriggerLow, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_TriggerLow);
    connect(ui->plainTextEdit_TriggerEdge, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_TriggerEdge);
    connect(ui->plainTextEdit_TriggerMode, &QPlainTextEdit::textChanged, this, &BtWindow::NewValue_TriggerMode);

    // [Construct UI] End


    // [Standartwerte anzeigen]



    ui->plainTextEdit_EntranceArea->setPlainText(CommandLineStringRef.EntranceArea);
    ui->plainTextEdit_N_High->setPlainText("Test");
    ui->plainTextEdit_N_Low->setPlainText("Test");
    ui->plainTextEdit_TriggerHigh->setPlainText("Test");
    ui->plainTextEdit_TriggerLow->setPlainText("Test");
    ui->plainTextEdit_TriggerEdge->setPlainText(CommandLineStringRef.TriggerEdge);
    ui->plainTextEdit_TriggerMode->setPlainText(CommandLineStringRef.TriggerMode);




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

    ui->plainTextEdit_EntranceArea->setPlainText(CommandLineStringRef.EntranceArea);
    ui->plainTextEdit_N_High->setPlainText(CommandLineStringRef.N_High);
    ui->plainTextEdit_N_Low->setPlainText(CommandLineStringRef.N_Low);
    ui->plainTextEdit_TriggerHigh->setPlainText(CommandLineStringRef.TriggerThresholdHigh);
    ui->plainTextEdit_TriggerLow->setPlainText(CommandLineStringRef.TriggerThresholdLow);
    ui->plainTextEdit_TriggerEdge->setPlainText(CommandLineStringRef.TriggerEdge);
    ui->plainTextEdit_TriggerMode->setPlainText(CommandLineStringRef.TriggerMode);
}




void BtWindow::showBluetoothWindow(){
    this->showFullScreen();
}











