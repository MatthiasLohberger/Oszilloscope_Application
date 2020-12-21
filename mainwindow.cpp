#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>

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




    SetUpPlot();
}





MainWindow::~MainWindow()
{
    delete ui;
}


// ------------------------------------------------------------------------------------


void MainWindow::EnableSendButton(){
    ui->SendButton->setEnabled(true);
}





//-----------------------------------------------------------




//[QCustomPlot]


void MainWindow::SetUpPlot(){

    //ui->horizontalFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //ui->horizontalFrame->setLineWidth(3);
    //ui->horizontalFrame->setMidLineWidth(1);


    ui->QCPlot->addGraph();

    // look(colors, brush, ...)
    ui->QCPlot->setBackground(Qt::darkBlue);
    ui->QCPlot->addGraph(0)->setPen(QPen(Qt::green));
    //ui->QCustomPlotTestW->addGraph(0)->setBrush()

    // axe labels
    ui->QCPlot->xAxis->setLabel("Time [µs]");
    ui->QCPlot->xAxis->setLabelColor(Qt::white);
    ui->QCPlot->xAxis->setTickLabelColor(Qt::white);

    ui->QCPlot->yAxis->setLabel("Voltage [V]");
    ui->QCPlot->yAxis->setLabelColor(Qt::white);
    ui->QCPlot->yAxis->setTickLabelColor(Qt::white);
    // axe ranges
    ui->QCPlot->xAxis->setRange(-1, 1);       //anpassen!!!!!!!!!!!!!!!
    ui->QCPlot->xAxis->setBasePen(QColor(255, 255, 255));
    ui->QCPlot->yAxis->setRange(-12, 12);
    ui->QCPlot->yAxis->setBasePen(QColor(255, 255, 255));

    // grid
    ui->QCPlot->xAxis->grid();
    ui->QCPlot->xAxis->grid()->setSubGridVisible(false);
    ui->QCPlot->yAxis->grid();
    ui->QCPlot->yAxis->grid()->setSubGridVisible(false);

    // ticks
}





void MainWindow::plot(QByteArray data){
    QVector<double> x(2048), y(2048);
    unsigned int yUInt;

    int i, k=0, SampleFactor, T_AD;
    float xStepSize, yRange;
    double yDouble, xMin, xDouble;
    QByteArray hcontainer;

    // 1. allocate mutex or wait until the allocation was sucessful
    while(mutexPlot.tryLock()){

    }



    // 2. clear plot bzw unten replot beim ersten plot Teil



    // 3. read yRange = EntranceArea out
        // später auslagern in Slot "void scaleAxes(QByteArray CommandLine);"
    hcontainer[0] = data[3];         // 2nd CommandLine element = EntranceArea
    hcontainer.toInt();
    switch(hcontainer.toInt()){
        case 1: yRange =10;
        case 2: yRange =3;
        case 3: yRange =1;
        case 4: yRange =0.3;
        //default:
    }



    // 4. determine yValues
    for(i=12; i<4108; i=i+2){
        yUInt = ((unsigned int) data[i]) + ((unsigned int)data[i+1]<<8);     //QByteArray to unsigned int mit cast erlaubt???
        yUInt = yUInt & 0x0FFF;                                             // 12 Bit max lenght

        yDouble = yUInt*((2*yRange)/4096) - yRange;

        y[k] = yDouble;                             // Zugriff auf Vektor so ok? oder mit append(...)
        k++;
    }



    // 5. determine corresponding xValues
    SampleFactor = ((int) data[5]) + ((int) data[6]<<8);          //combine high & low byte   // cast erlaubt? Hilfsvar???
    T_AD = T_AD0 * SampleFactor;                                // T_AD0 const Attribut von MAinWindos
    xStepSize = T_AD/2048;

    xMin = (T_AD/2) - T_AD;
    x[0] = xMin;
    for(i=1; i<=2048; i++){

        xDouble = xMin + (xStepSize * i);

        x[i] = xDouble;
    }



    // 6. Plotten
    i = 0;
    QVector<double> xValueMin(1), yValueMin;
    xValueMin[0] = x[0];
    yValueMin[0] = y[0];
    ui->QCPlot->graph(0)->setData(xValueMin, yValueMin);
    ui->QCPlot->replot();
        // delay(); ???

    for (i=1; i<2048; i++) {
        ui->QCPlot->graph(0)->addData(x[i], y[i]);
        ui->QCPlot->replot();
            // delay(); ???
    }



    // 7. free the mutex
    mutexPlot.unlock();
}



















