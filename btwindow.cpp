#include "btwindow.h"
#include "ui_btwindow.h"


//[Konstruktor]
BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),                                //Init Liste
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);




    connect(ui->SearchButton,  SIGNAL(clicked),   this, SLOT(startDeviceSearch()));
    connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(ConnectToDevice()));
    //connect(ui->SendButton, &QPushButton::clicked, this, &BtWindow::SendButtonPressed);
    connect(ui->DefaultButton, SIGNAL(clicked()), this, SIGNAL(DefaultButtonPressed()));
    connect(ui->CloseButton,   SIGNAL(clicked()), this, SLOT(CloseButtonPressed()));




    connect(ui->lineEdit_EntranceArea, SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_N_High,       SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_N_Low,        SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_TriggerHigh,  SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_TriggerLow,   SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_TriggerEdge,  SIGNAL(textChanged), this, SLOT(NewValuesToSet));
    connect(ui->lineEdit_TriggerMode,  SIGNAL(textChanged), this, SLOT(NewValuesToSet));

    // [Construct UI] End



    // local oder default adapter für Bt auswählen

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

void BtWindow::NewValuesToSet(){

}

//[Slot Funktionen] NewValues for ConfigFrame  End---------------------------------------------------------


void BtWindow::newDataForPlainTextWidget(ConfigDataString & CommandLineStringRef){
    QString string;


    string = HexNumAsString(CommandLineStringRef.EntranceArea);
    ui->lineEdit_EntranceArea->setText(string);
    string.clear();

    string = HexNumAsString(CommandLineStringRef.N_High);
    ui->lineEdit_N_High->setText(string);


    string = HexNumAsString(CommandLineStringRef.N_Low);
    ui->lineEdit_N_Low->setText(string);
     string.clear();

    string = HexNumAsString(CommandLineStringRef.TriggerThresholdHigh);
    ui->lineEdit_TriggerHigh->setText(string);
     string.clear();

    string = HexNumAsString(CommandLineStringRef.TriggerThresholdLow);
    ui->lineEdit_TriggerLow->setText(string);
    string.clear();

    ui->lineEdit_TriggerEdge->setText(CommandLineStringRef.TriggerEdge);

    ui->lineEdit_TriggerMode->setText(CommandLineStringRef.TriggerMode);
}



QString BtWindow::HexNumAsString(QString StringNum){
    QString HexStringNum;
    HexStringNum.append("0x");
    HexStringNum.append(StringNum);

    if (HexStringNum.length() == 3){
        HexStringNum.insert(2, "0");        //wenn z.B. 1 dann wird aus 0x1 -> 0x01
        return HexStringNum;
    } else {
        return HexStringNum;
    }
}




void BtWindow::showBluetoothWindow(){
    this->showFullScreen();
}









