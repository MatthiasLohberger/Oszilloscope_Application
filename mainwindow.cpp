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
