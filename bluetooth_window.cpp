#include "bluetooth_window.h"
#include "ui_bluetooth_window.h"

bluetooth_window::bluetooth_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bluetooth_window)
{
    ui->setupUi(this);
}

bluetooth_window::~bluetooth_window()
{
    delete ui;
}
