#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QFont f("Arial", 12, QFont::Normal);
    //f.setCapitalization(QFont::MixedCase);
    //this->setFont(f);

    QFont f("Helvetica", 12, QFont::Normal);
    ui->CaptureTimeLabel->setFont(f);

    ui->SendButton->setEnabled(false);

    //connect(ui->BtSettingsButton, &QToolButton::clicked, this, &MainWindow::showBluetoothWindow);
    connect(ui->BtSettingsButton, SIGNAL(clicked()),
            this, SIGNAL(BtSettingsButtonPressed()));
    connect(ui->SendButton, SIGNAL(clicked()),
            this, SIGNAL(SendButton_Pressed()));

    connect(ui->CaptureTimePlusButton, SIGNAL(clicked()),
            this, SLOT(CaptureTimePlusButtonClicked()));
    connect(ui->CaptureTimeMinusButton, SIGNAL(clicked()),
            this, SLOT(CaptureTimeMinusButtonClicked()));

    connect(ui->EntranceVoltagePlusButton, SIGNAL(clicked()),
            this, SLOT(EntranceVoltagePlusButtonClicked()));
    connect(ui->EntranceVoltageMinusButton, SIGNAL(clicked()),
            this, SLOT(EntranceVoltageMinusButtonClicked()));

    connect(ui->TriggerPlusButton, SIGNAL(pressed()),
            this, SLOT(TriggerPlusButtonClicked()));
    connect(ui->TriggerMinusButton, SIGNAL(pressed()),
            this, SLOT(TriggerMinusButtonClicked()));

    connect(ui->FreezeButton, SIGNAL(clicked()),
            this, SIGNAL(FreezeButtonClicked()));




    //default Values   --> delete later
    //setDefaultValuesManually();

    PlotFlag = 0;


    SetUpPlot();
}





MainWindow::~MainWindow()
{
    PlotThread.quit();
    PlotThread.wait();

    MainWindowControlsThread.quit();
    MainWindowControlsThread.wait();

    delete ui;
}


// ------------------------------------------------------------------------------------






//[QCustomPlot]


void MainWindow::SetUpPlot(){
/*
    //ui->horizontalFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //ui->horizontalFrame->setLineWidth(3);
    //ui->horizontalFrame->setMidLineWidth(1);


        //ui->QCPlot->addGraph();

    // look(colors, brush, ...)
*/
    ui->QCPlot->setBackground(Qt::darkBlue);

/*
        //ui->QCPlot->graph(0)->setPen(QPen(Qt::green));
    //ui->QCustomPlotTestW->addGraph(0)->setBrush()


    // axe labels
//    ui->QCPlot->xAxis->setLabel("Time [µs]");
//    ui->QCPlot->xAxis->setLabelColor(Qt::white);
//    ui->QCPlot->xAxis->setTickLabelColor(Qt::white);

//    ui->QCPlot->yAxis->setLabel("Voltage [V]");
//    ui->QCPlot->yAxis->setLabelColor(Qt::white);
//    ui->QCPlot->yAxis->setTickLabelColor(Qt::white);
    // axe ranges
//    ui->QCPlot->xAxis->setRange(-0.128, 0.128);       //anpassen!!!!!!!!!!!!!!!
//    ui->QCPlot->xAxis->setBasePen(QColor(255, 255, 255));
//    ui->QCPlot->yAxis->setRange(-12, 12);
//    ui->QCPlot->yAxis->setBasePen(QColor(255, 255, 255));
*/
    // grid
    ui->QCPlot->xAxis->grid();
    ui->QCPlot->xAxis->grid()->setSubGridVisible(false);
    ui->QCPlot->yAxis->grid();
    ui->QCPlot->yAxis->grid()->setSubGridVisible(false);

    PlotPen.setWidth(3);
    PlotPen.setColor(Qt::green);

}





void MainWindow::plot(QByteArray data){

    PlotFlag = 1;

    //QVector<double> x(2048), y(2048);
    QVector<double> x(NumberOfValues), y(NumberOfValues);
    //QVector<double> x(2040), y(2040);     //false
    unsigned int yUInt;

    int i, k=0;
    double yDouble, xDouble;
    //int PlotStepSize = 32;

    QByteArray hcontainer;







    // 1. determine yValues --> read data, combine high and low byte to an uint variable,
    //                          cast the value to 12 Bit max and compute the corresponding double value

    // for all 4096 Values (4108 Byte - 21 Byte Header)
    /*
    qDebug() << "Plot 1";

    for(i=12; i<4108; i=i+2){
        yUInt = ((unsigned int) data[i]) + ((unsigned int)data[i+1]<<8);     //QByteArray to unsigned int mit cast erlaubt???
        yUInt = yUInt & 0x0FFF;                                             // 12 Bit max lenght

        yDouble = yUInt*((2*y_OneSidedEntranceVoltage)/4096) - y_OneSidedEntranceVoltage;

        y[k] = yDouble;                             // Zugriff auf Vektor so ok? oder mit append(...)
        k++;
    }
    */

    for(i=12; i<4108; i=i+8){

        yUInt = ((unsigned int) data[i]) + ((unsigned int)data[i+1]<<8);     //QByteArray to unsigned int mit cast erlaubt???
        yUInt = yUInt & 0x0FFF;                                             // 12 Bit max lenght

        yDouble = yUInt*((2*y_OneSidedEntranceVoltage)/4096) - y_OneSidedEntranceVoltage;

        y[k] = yDouble;                             // Zugriff auf Vektor so ok? oder mit append(...)
        k++;
    }





    // 2. determine corresponding xValues
    /*
    qDebug() << "Plot 2";

    for(i=0; i<2048; i++){

        xDouble = (xMin + (T_AD * i)) * CorrectionFactor;
        x[i] = xDouble;
        //qDebug() << "x[" << i << "] = " << x.at(i);
    }
    */
    for(i=0; i<NumberOfValues; i++){

        xDouble = (xMin + ((T_AD *4) * i)) * CorrectionFactor;
        x[i] = xDouble;
        //qDebug() << "x[" << i << "] = " << x.at(i);
    }







     qDebug() << "Plot 3";
    // 1. allocate mutex or wait until the allocation was successful         // nach unten verschieben, daten können vorbereitet werden!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //while(mutexPlot.tryLock()){

    //}



    // 2. clear plot bzw unten replot beim ersten plot Teil                 // nach unten verschieben, clear unten nach plot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ui->QCPlot->clearGraphs();
    ui->QCPlot->addGraph(0);

    //PlotPen.setStyle();
    ui->QCPlot->graph(0)->setPen(PlotPen);

    //ui->QCPlot->graph(0)->moveToThread()


    qDebug() << "Plot 4.1";


    // 6. Plotten


    qDebug() << "Size of xVektor = " << x.size();
    qDebug() << "Size of yVektor = " << y.size();
    qDebug() << "Plot 4.2";


     ui->QCPlot->graph(0)->setData(x, y, true);
     ui->QCPlot->replot();



    PlotFlag = 0;
}

// ----------------------------------------------------------




void MainWindow::ClearPlot(){
    ui->QCPlot->clearGraphs();
}




void MainWindow::scaleAxesAndRange(ConfigData CommandLine){
       float y_OneSidedEntranceVoltage_withOffset = 0;
       float xMax, xMax_Axis = 0, xMin_Axis = 0;


    // 1. determine y_OneSidedEntranceVoltage

    switch(CommandLine.EntranceArea){
        case 1: y_OneSidedEntranceVoltage =10; break;
        case 2: y_OneSidedEntranceVoltage =3; break;
        case 3: y_OneSidedEntranceVoltage =1; break;
        case 4: y_OneSidedEntranceVoltage =0.3; break;
        //default:
    }

    if(y_OneSidedEntranceVoltage == 10){      // 12V
        y_OneSidedEntranceVoltage_withOffset = y_OneSidedEntranceVoltage + 2;
    }
    else if(y_OneSidedEntranceVoltage == 3){
        y_OneSidedEntranceVoltage_withOffset = y_OneSidedEntranceVoltage + 0.5;   // 3.5V
    }
    else if(y_OneSidedEntranceVoltage == 1){
        y_OneSidedEntranceVoltage_withOffset = y_OneSidedEntranceVoltage + 0.2;   // 1.2V
    }
    else if(y_OneSidedEntranceVoltage == 0.3){
        y_OneSidedEntranceVoltage_withOffset = y_OneSidedEntranceVoltage + 0.1; // 0.4V
    }


    // 2. scale y-Axis

    ui->QCPlot->yAxis->setLabel("Voltage [V]");
    ui->QCPlot->yAxis->setLabelColor(Qt::white);
    ui->QCPlot->yAxis->setTickLabelColor(Qt::white);

    ui->QCPlot->yAxis->setRange(-y_OneSidedEntranceVoltage_withOffset,
                                y_OneSidedEntranceVoltage_withOffset);
    ui->QCPlot->yAxis->setBasePen(QColor(255, 255, 255));

    qDebug() << "yAxis:     y_OneSidedEntranceVoltage = " << y_OneSidedEntranceVoltage
             << "   y_OneSidedEntranceVoltage_withOffset = " << y_OneSidedEntranceVoltage_withOffset;



    // 3. determine xRange, T_AD, t, ...

    N_SampleFactor = CommandLine.N;

    T_AD = T_AD0 * N_SampleFactor;         // T_AD0 const Attribut von MAinWindos

    t = T_AD * 2048;

    xMax = t/2;
    xMin = -xMax;



    qDebug() << "xAxis:     N_SampleFactor = " << N_SampleFactor << "  T_AD0 = " << T_AD0
             << "   T_AD = " << T_AD << "   t = " << t << "    xMin = " << xMin;



    // 4. scale x-Axis and change the Lable
        // display the right prefix of the unit und rescale the xMin/xMax values (view e.g.)
    if(t < 1*pow(10, -3)){
        CorrectionFactor = 1*pow(10, 6);
        xMax_Axis = xMax * CorrectionFactor;                    // e.g. xMax_Axis = 125 [µs] while xMax = 0.000125 [µs]
        xMin_Axis = -xMax_Axis;
        ui->QCPlot->xAxis->setLabel("Time [µs]");
    }
    else if(t >= 1*pow(10, -3) && t < 1){
        CorrectionFactor = 1*pow(10, 3);
        xMax_Axis = xMax * CorrectionFactor;                    // e.g. xMax_Axis = 125 [ms] while xMax = 0.125 [ms]
        xMin_Axis = -xMax_Axis;
        ui->QCPlot->xAxis->setLabel("Time [ms]");
    }
    else if(t >= 1){
        CorrectionFactor = 1;
        xMax_Axis = xMax * CorrectionFactor;                                   // e.g. xMax_Axis = 1 [s] while xMax = 1 [s]
        xMin_Axis = -xMax_Axis;
        ui->QCPlot->xAxis->setLabel("Time [s]");
    }
    qDebug() << "xAxis:     xMax_Axis = " << xMax_Axis << " - xMin_Axis = " << xMin_Axis;

    ui->QCPlot->xAxis->setLabelColor(Qt::white);
    ui->QCPlot->xAxis->setTickLabelColor(Qt::white);

    ui->QCPlot->xAxis->setRange(xMin_Axis, xMax_Axis);
    ui->QCPlot->xAxis->setBasePen(QColor(255, 255, 255));



    // 5. grid
    ui->QCPlot->xAxis->grid();
    ui->QCPlot->xAxis->grid()->setSubGridVisible(false);
    ui->QCPlot->yAxis->grid();
    ui->QCPlot->yAxis->grid()->setSubGridVisible(false);


    ui->QCPlot->replot();
}





//------------------------------------------------------------------------------------





// Buttons and Displays

void MainWindow::setDefaultValuesManually(){
    //später unnötig

    //[CaptureTimeLCDWidget]
    //N_SampleFactor = 1;
    CaptureTimeCounter_new = 1;
    ui->CaptureTimeLabel->setText("Capture Time [µs]");
    ui->CaptureTimeLcdDisplay->display(200);

    //[EntranceVoltageLCDWidget]
    EntranceVoltageCounter = 1;
    ui->EntranceVoltageLcdDisplay->display("±10");

}






    //[CaptureTimeLCDWidget]
void MainWindow::CaptureTimeWidgetManagement(int step){
    if((CaptureTimeCounter_new==1 && step==-1)||(CaptureTimeCounter_new==16 && step==1)){
        return;
    }


    CaptureTimeCounter_new = CaptureTimeCounter_new + step;


    if(1<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 2){
        ui->CaptureTimeLabel->setText("Capture Time [µs]");
    }
    else if(3<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 11){
        ui->CaptureTimeLabel->setText("Capture Time [ms]");
    }
    else if(12<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 16){
        ui->CaptureTimeLabel->setText("Capture Time [s]");
    }


    switch (CaptureTimeCounter_new) {
        case 1: ui->CaptureTimeLcdDisplay->display(200); break;
        case 2: ui->CaptureTimeLcdDisplay->display(500); break;
        case 3: ui->CaptureTimeLcdDisplay->display(1); break;
        case 4: ui->CaptureTimeLcdDisplay->display(2); break;
        case 5: ui->CaptureTimeLcdDisplay->display(5); break;
        case 6: ui->CaptureTimeLcdDisplay->display(10); break;
        case 7: ui->CaptureTimeLcdDisplay->display(20); break;
        case 8: ui->CaptureTimeLcdDisplay->display(50); break;
        case 9: ui->CaptureTimeLcdDisplay->display(100); break;
        case 10: ui->CaptureTimeLcdDisplay->display(200); break;
        case 11: ui->CaptureTimeLcdDisplay->display(500); break;
        case 12: ui->CaptureTimeLcdDisplay->display(1); break;
        case 13: ui->CaptureTimeLcdDisplay->display(2); break;
        case 14: ui->CaptureTimeLcdDisplay->display(5); break;
        case 15: ui->CaptureTimeLcdDisplay->display(10); break;
        case 16: ui->CaptureTimeLcdDisplay->display(20); break;

    }
}

void MainWindow::CaptureTimePlusButtonClicked(){
        CaptureTimeWidgetManagement(1);
}
void MainWindow::CaptureTimeMinusButtonClicked(){
        CaptureTimeWidgetManagement(-1);
}




    //[EntranceVoltageLCDWidget]
void MainWindow::EntranceVoltageWidgetManagement(int step){
    int real_step = - step;
    if((EntranceVoltageCounter==1 && real_step==-1)||(EntranceVoltageCounter==4 && real_step==1)){
        return;
    }


    EntranceVoltageCounter = EntranceVoltageCounter + real_step;


    switch(EntranceVoltageCounter) {
        case 1: ui->EntranceVoltageLcdDisplay->display("10"); break;
        case 2: ui->EntranceVoltageLcdDisplay->display("3"); break;
        case 3: ui->EntranceVoltageLcdDisplay->display("1"); break;
        case 4: ui->EntranceVoltageLcdDisplay->display("0.3"); break;
    }
}


void MainWindow::EntranceVoltagePlusButtonClicked(){
    EntranceVoltageWidgetManagement(1);
}
void MainWindow::EntranceVoltageMinusButtonClicked(){
    EntranceVoltageWidgetManagement(-1);
}



void MainWindow::EnableSendButton(){
    ui->SendButton->setEnabled(true);
}

void MainWindow::DisableSendButton(){
    ui->SendButton->setEnabled(false);
}




ConfigDataValuesMainWin MainWindow::readValuesWidgetsMainWindow(){
    ConfigDataValuesMainWin ConfigDataDataPartMainWin;
    int CaptureTime_N;
    switch (CaptureTimeCounter_new) {
        case 1: CaptureTime_N  = 1;       break;
        case 2: CaptureTime_N  = 2;       break;
        case 3: CaptureTime_N  = 4;       break;
        case 4: CaptureTime_N  = 8;       break;
        case 5: CaptureTime_N  = 20;      break;
        case 6: CaptureTime_N  = 40;      break;
        case 7: CaptureTime_N  = 80;      break;
        case 8: CaptureTime_N  = 200;     break;
        case 9: CaptureTime_N  = 400;     break;
        case 10: CaptureTime_N = 800;     break;
        case 11: CaptureTime_N = 2000;    break;
        case 12: CaptureTime_N = 4000;    break;
        case 13: CaptureTime_N = 8000;    break;
        case 14: CaptureTime_N = 20000;   break;
        case 15: CaptureTime_N = 40000;   break;
        case 16: CaptureTime_N = 65535;   break;
    }



    ConfigDataDataPartMainWin.EntranceVoltageCounter = EntranceVoltageCounter;
    ConfigDataDataPartMainWin.TriggerCounter = TriggerCounter;
    ConfigDataDataPartMainWin.CaptureTime_N = CaptureTime_N;

    return ConfigDataDataPartMainWin;
}



void MainWindow::setValuesWidgetsMainWindow(ConfigData OsziConfigData){
    EntranceVoltageCounter = OsziConfigData.EntranceArea;
    TriggerCounter = OsziConfigData.TriggerThreshold;
    CaptureTimeCounter_new = OsziConfigData.N;


    // EntranceArea
    switch(EntranceVoltageCounter) {
        case 1: ui->EntranceVoltageLcdDisplay->display("10"); break;
        case 2: ui->EntranceVoltageLcdDisplay->display("3"); break;
        case 3: ui->EntranceVoltageLcdDisplay->display("1"); break;
        case 4: ui->EntranceVoltageLcdDisplay->display("0.3"); break;
    }



    // Trigger
    TriggerVoltage =  (TriggerCounter * TriggerVoltageStep)
            - (2048 * TriggerVoltageStep);
    ui->TriggerLcdDisplay->display(TriggerVoltage);



    // CaptureTime
    if(1<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 2){
        ui->CaptureTimeLabel->setText("Capture Time [µs]");
    }
    else if(3<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 11){
        ui->CaptureTimeLabel->setText("Capture Time [ms]");
    }
    else if(12<=CaptureTimeCounter_new && CaptureTimeCounter_new<= 16){
        ui->CaptureTimeLabel->setText("Capture Time [s]");
    }
    switch (CaptureTimeCounter_new) {
        case 1: ui->CaptureTimeLcdDisplay->display(200); break;
        case 2: ui->CaptureTimeLcdDisplay->display(500); break;
        case 3: ui->CaptureTimeLcdDisplay->display(1); break;
        case 4: ui->CaptureTimeLcdDisplay->display(2); break;
        case 5: ui->CaptureTimeLcdDisplay->display(5); break;
        case 6: ui->CaptureTimeLcdDisplay->display(10); break;
        case 7: ui->CaptureTimeLcdDisplay->display(20); break;
        case 8: ui->CaptureTimeLcdDisplay->display(50); break;
        case 9: ui->CaptureTimeLcdDisplay->display(100); break;
        case 10: ui->CaptureTimeLcdDisplay->display(200); break;
        case 11: ui->CaptureTimeLcdDisplay->display(500); break;
        case 12: ui->CaptureTimeLcdDisplay->display(1); break;
        case 13: ui->CaptureTimeLcdDisplay->display(2); break;
        case 14: ui->CaptureTimeLcdDisplay->display(5); break;
        case 15: ui->CaptureTimeLcdDisplay->display(10); break;
        case 16: ui->CaptureTimeLcdDisplay->display(20); break;
    }

}




void MainWindow::setTextFreezeButton(QString text){
    ui->FreezeButton->setText(text);
}





void MainWindow::TriggerWidgetManagement(int step){
    if((step==1 && TriggerCounter == 65535) ||(step==-1 && TriggerCounter==0)){
        return;
    }


    if(step==1){
        TriggerCounter++;
        TriggerVoltage =  (TriggerCounter * TriggerVoltageStep)
                - (2048 * TriggerVoltageStep);
        ui->TriggerLcdDisplay->display(TriggerVoltage);
    } else{
        TriggerCounter--;
        TriggerVoltage =  (TriggerCounter * TriggerVoltageStep)
                - (2048 * TriggerVoltageStep);
        ui->TriggerLcdDisplay->display(TriggerVoltage);
    }
}
void MainWindow::TriggerPlusButtonClicked(){
    //while (ui->TriggerPlusButton->isDown() == true) {
        TriggerWidgetManagement(+1);
    //}
    qDebug() << "+TriggerCounter = " << TriggerCounter;
}
void MainWindow::TriggerMinusButtonClicked(){
     //do {
        TriggerWidgetManagement(-1);
    //} while (ui->TriggerMinusButton->isDown() == true);

    qDebug() << "-TriggerCounter = " << TriggerCounter;
}



//-----------------------------------------------------------

// [Plot Tread]

void MainWindow::Plot_MoveToThread(){
    ui->QCPlot->moveToThread(&PlotThread);
    PlotThread.start();


    ui->BtSettingsButton->moveToThread(&MainWindowControlsThread);
    ui->FreezeButton->moveToThread(&MainWindowControlsThread);
    ui->SendButton->moveToThread(&MainWindowControlsThread);

    ui->CaptureTimeLcdDisplay->moveToThread(&MainWindowControlsThread);
    ui->CaptureTimeMinusButton->moveToThread(&MainWindowControlsThread);
    ui->CaptureTimePlusButton->moveToThread(&MainWindowControlsThread);

    ui->EntranceVoltageLcdDisplay->moveToThread(&MainWindowControlsThread);
    ui->EntranceVoltageMinusButton->moveToThread(&MainWindowControlsThread);
    ui->EntranceVoltagePlusButton->moveToThread(&MainWindowControlsThread);

    ui->TriggerLcdDisplay->moveToThread(&MainWindowControlsThread);
    ui->TriggerMinusButton->moveToThread(&MainWindowControlsThread);
    ui->TriggerPlusButton->moveToThread(&MainWindowControlsThread);

    MainWindowControlsThread.start();


}
void MainWindow::Plot_QuitTread(){
    PlotThread.quit();
    MainWindowControlsThread.quit();
}


bool MainWindow::readPlotFlag(){
    return PlotFlag;
}
