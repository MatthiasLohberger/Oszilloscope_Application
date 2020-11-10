#include "btwindow.h"
#include "ui_btwindow.h"

BtWindow::BtWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtWindow)
{
    ui->setupUi(this);
}

BtWindow::~BtWindow()
{
    delete ui;
}
