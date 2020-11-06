#include "bluetooth_window.h"
#include "ui_bluetooth_window.h"


//[Konstruktor]
bluetooth_window::bluetooth_window(QWidget *parent, CommandLine_EAS_Board &OsziConfigData) :
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

    // [Construct UI]

    //Standartwerte anzeigen






    //local oder default adapter für Bt auswählen

    // Bt Server

    // Get local device name

}

//[Konstruktor] End






//[~Denstruktor]
bluetooth_window::~bluetooth_window()
{
    delete ui;
}
//[~Denstruktor] End



