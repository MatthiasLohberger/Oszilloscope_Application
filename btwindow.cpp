#include "btwindow.h"
#include "ui_btwindow.h"
#include<QDebug>

//[Konstruktor]
BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),                                //Init Liste
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);



    // [Construct UI]
    connect(ui->SearchButton,  SIGNAL(clicked()),   this, SLOT(startDeviceSearch()));
    //connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(ConnectToDevice()));
    //connect(ui->SendButton, &QPushButton::clicked, this, &BtWindow::SendButtonPressed);
    connect(ui->DefaultButton, SIGNAL(clicked()), this, SIGNAL(DefaultButtonPressed()));
    connect(ui->CloseButton,   SIGNAL(clicked()), this, SLOT(CloseButtonPressed()));




    connect(ui->lineEdit_EntranceArea, SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_N_High,       SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_N_Low,        SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerHigh,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerLow,   SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerEdge,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerMode,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));

    // [Construct UI] End


    //For Bluetooth Connection

    // Check if Bluetooth is available on this device
    if (localDevice.isValid()) {

        // Turn Bluetooth on
        localDevice.powerOn();

        // Read local device name
        localDeviceName = localDevice.name();

        // Make it visible to others
        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);

        // Get connected devices
        QList<QBluetoothAddress> remotes;
        remotes = localDevice.connectedDevices();
    }








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






//[Slot Funktionen] Buttons Pressed/Selected   End



//-------------------







//[Slot Funktionen] NewValues for ConfigFrame

void BtWindow::NewValuesToSet(QString text){
    QString HilfUseless = text;

    // Alle QTestEdit Felder händtisch auslesen
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



void BtWindow::ShowNewBtDevice(const QBluetoothDeviceInfo &NewBtDevice){
    int size;
    BtDeviceInfo NewDevice;
    NewDevice.BtDevice = NewBtDevice;

   qDebug() << "Found new device:" << NewDevice.BtDevice.name() << '(' << NewDevice.BtDevice.address().toString() << ')';


    if (NewDevice.BtDevice.name().isEmpty()){                           // Überprüfung, ob Name vorhanden ist
        QBluetoothAddress address = NewDevice.BtDevice.address();
        NewDevice.Name = address.toString();
    }
    else{
        NewDevice.Name = NewDevice.BtDevice.name();
    }


    DiscoveredDevicesList.append(NewDevice);
    size = DiscoveredDevicesList.size();

    ui->BtDeviceSelect->addItem(DiscoveredDevicesList.at(size-1).Name);
}





void BtWindow::startDeviceSearch(){
    ui->SearchButton->setEnabled(false);

    qDebug() << "Start Discovery";
    //const QBluetoothAddress adapter = localDevice.address();
    //BluetoothDeviceFinder HBluetoothDeviceFinder(adapter);
    //bluetoothDeviceFinder = HBluetoothDeviceFinder;

    connect(&bluetoothDeviceFinder, SIGNAL(ShowDeviceDiscovered(const QBluetoothDeviceInfo)),
            this, SLOT(ShowNewBtDevice(const QBluetoothDeviceInfo)));

    bluetoothDeviceFinder.startDiscovery();



}









