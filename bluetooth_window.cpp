#include "bluetooth_window.h"
#include "ui_bluetooth_window.h"


//[Konstruktor]
bluetooth_window::bluetooth_window(QDialog *parent) :
    QDialog(parent),                        //Init Liste
    ui(new Ui::bluetooth_window)
{
    // [Construct UI]
    ui->setupUi(this);

    connect(ui->ConnectButton, &QPushButton::clicked, this, &bluetooth_window::ConnectButtonPressed);
    connect(ui->SendButton, &QPushButton::clicked, this, &bluetooth_window::SendButtonPressed);
    connect(ui->DefaultButton, &QPushButton::clicked, this, &bluetooth_window::DefaultButtonPressed);
    connect(ui->CloseButton, &QPushButton::clicked, this, &bluetooth_window::ConnectButtonPressed);

    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geschlossener Zustand
    //connect(ui->BtDeviceSelect, QComboBox:: ...);  //geöffneter Zustand

    connect(ui->plainTextEdit_EntranceArea, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_EntranceArea);
    connect(ui->plainTextEdit_N_High, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_N_High);
    connect(ui->plainTextEdit_N_Low, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_N_Low);
    connect(ui->plainTextEdit_TriggerHigh, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_TriggerHigh);
    connect(ui->plainTextEdit_TriggerLow, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_TriggerLow);
    connect(ui->plainTextEdit_TriggerEdge, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_TriggerEdge);
    connect(ui->plainTextEdit_TriggerMode, &QPlainTextEdit::textChanged, this, &bluetooth_window::NewValue_TriggerMode);

    // [Construct UI] End


    // [Standartwerte anzeigen]
    /*
    ui->plainTextEdit_EntranceArea->setPlainText(OsziConfigData.getDataString().EntranceArea);
    ui->plainTextEdit_N_High->setPlainText(OsziConfigData.getDataString().N_Low);
    ui->plainTextEdit_N_Low->setPlainText(OsziConfigData.getDataString().N_High);
    ui->plainTextEdit_TriggerHigh->setPlainText(OsziConfigData.getDataString().TriggerThresholdHigh);
    ui->plainTextEdit_TriggerLow->setPlainText(OsziConfigData.getDataString().TriggerThresholdLow);
    ui->plainTextEdit_TriggerEdge->setPlainText(OsziConfigData.getDataString().TriggerEdge);
    ui->plainTextEdit_TriggerMode->setPlainText(OsziConfigData.getDataString().TriggerMode);
    */



    // local oder default adapter für Bt auswählen

    // Bt Server

    // Get local device name

}

//[Konstruktor] End






//[~Destruktor]
bluetooth_window::~bluetooth_window()
{
    delete ui;
}
//[~Destruktor] End




//[Slot Funktionen] Buttons Pressed/Selected

void bluetooth_window::ConnectButtonPressed(){
    //Connect to Bt Device
}


void bluetooth_window::SendButtonPressed(){
    //Send to Bt Device
}


void bluetooth_window::DefaultButtonPressed(){
    //Default
}


void bluetooth_window::CloseButtonPressed(){
    //Close Bt Win bzw Show Main/Oszi Win
}


void bluetooth_window::BtDeviceSelected(){
    //Name in Var speichern, UUID etc. herausfinden und auf connect pressed warten
    //Namen anzeigen
}
//[Slot Funktionen] Buttons Pressed/Selected   End



//[Slot Funktionen] NewValues for ConfigFrame

void bluetooth_window::NewValue_EntranceArea(){
    //set new Value
}


void bluetooth_window::NewValue_N_High(){
    //set new Value
}


void bluetooth_window::NewValue_N_Low(){
    //set new Value
}


void bluetooth_window::NewValue_TriggerHigh(){
    //set new Value
}


void bluetooth_window::NewValue_TriggerLow(){
    //set new Value
}


void bluetooth_window::NewValue_TriggerEdge(){
    //set new Value
}


void bluetooth_window::NewValue_TriggerMode(){
    //set new Value
}
//[Slot Funktionen] NewValues for ConfigFrame  End



