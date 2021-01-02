#include "btwindow.h"
#include "ui_btwindow.h"
#include<QDebug>

//[Konstruktor]
BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),                                //Init Liste
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);

    ui->SendButton->setEnabled(false);

    // [Construct UI]
    connect(ui->SearchButton,  SIGNAL(clicked()),   this, SLOT(startServiceSearch()));
    connect(ui->ConnectButton, SIGNAL(clicked()), this, SLOT(ConnectButtonPressed()));
    connect(ui->SendButton, SIGNAL(clicked()), this, SIGNAL(SendButtonPressed()));
    connect(ui->DefaultButton, SIGNAL(clicked()), this, SIGNAL(DefaultButtonPressed()));
    connect(ui->CloseButton,   SIGNAL(clicked()), this, SLOT(CloseButtonPressed()));




    connect(ui->lineEdit_EntranceArea, SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_N_High,       SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_N_Low,        SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerHigh,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerLow,   SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerEdge,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));
    connect(ui->lineEdit_TriggerMode,  SIGNAL(textEdited(QString)), this, SLOT(NewValuesToSet(QString)));




    ui->lineEdit_EntranceArea->setReadOnly(true);
    ui->lineEdit_N_High->setReadOnly(true);
    ui->lineEdit_N_Low->setReadOnly(true);
    ui->lineEdit_TriggerHigh->setReadOnly(true);
    ui->lineEdit_TriggerLow->setReadOnly(true);
    ui->lineEdit_TriggerEdge->setReadOnly(true);
    ui->lineEdit_TriggerMode->setReadOnly(true);

    // [Construct UI] End

    QFont f("Calibri", 18);
    f.setCapitalization(QFont::MixedCase);
    ui->SendButton->setFont(f);



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

/*
void BtWindow::ConnectButtonPressed(){
    //Connect to Bt Device
}
*/


void BtWindow::CloseButtonPressed(){
    //Close Bt Win bzw Show Main/Oszi Win
    this->hide();
}

void BtWindow::setTextConnectButton(){
    ui->ConnectButton->setText("Connected");
}


void BtWindow::Enable_SendButton(){
     ui->SendButton->setEnabled(true);
}


void BtWindow::Disable_SendButton(){
     ui->SendButton->setEnabled(false);
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





//------------------------------------------------------------------------------------------------
// [Functions for Searching and Connecting to Bluetooth Devices]



void BtWindow::ShowNewBtService(const QBluetoothServiceInfo &NewBtService){
    int size;
    BtServiceInfo NewService;
    NewService.BtService = NewBtService;

   qDebug() << "Found new device:" << NewService.BtService.device().name() << '('
            << NewService.BtService.device().address().toString() << ')';


    if (NewService.BtService.device().name().isEmpty()){                           // Überprüfung, ob Name vorhanden ist
        QBluetoothAddress address = NewService.BtService.device().address();
        NewService.Name = address.toString();
    } else{
        NewService.Name = NewService.BtService.device().name();
    }


    DiscoveredDevicesList.append(NewService);
    size = DiscoveredDevicesList.size();

    ui->BtDeviceSelect->addItem(DiscoveredDevicesList.at(size-1).Name);
}





void BtWindow::startServiceSearch(){
    ui->SearchButton->setEnabled(false);

    qDebug() << "Start Discovery";
    //const QBluetoothAddress adapter = localDevice.address();
    //BluetoothDeviceFinder HBluetoothDeviceFinder(adapter);
    //bluetoothDeviceFinder = HBluetoothDeviceFinder;

    ui->SearchButton->setText("Searching...");

    connect(&bluetoothServiceFinder, SIGNAL(ShowServiceDiscovered(const QBluetoothServiceInfo)),
            this, SLOT(ShowNewBtService(const QBluetoothServiceInfo)));

    bluetoothServiceFinder.startDiscovery();

}



void BtWindow::ConnectButtonPressed(){
    int i= 0;
    QString SeletedServiceName = ui->BtDeviceSelect->currentText();

    ui->ConnectButton->setEnabled(false);
    ui->BtDeviceSelect->hidePopup();
    bluetoothServiceFinder.stopDiscovery();


    if(SeletedServiceName.isEmpty()){
        ui->SearchButton->setEnabled(true);
        ui->ConnectButton->setEnabled(true);
        qDebug() << "No device found/selected!";
        return;
    }

    while(DiscoveredDevicesList[i].Name != SeletedServiceName){
        i++;
        if(i == DiscoveredDevicesList.size()){
            qDebug() << "No such device in the discovery List!";
            return;
        }
    }
    qDebug() << "Connect cklicked!";
    qDebug() << "Trying to connect to selected Device: " << DiscoveredDevicesList[i].Name;

    emit ServiceSelectedForConnection(DiscoveredDevicesList[i].BtService);

}









