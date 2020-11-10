#ifndef BTWINDOW_H
#define BTWINDOW_H

#include <QWidget>

namespace Ui {
class BtWindow;
}

class BtWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BtWindow(QWidget *parent = nullptr);
    ~BtWindow();

private:
    Ui::BtWindow *ui;
};

#endif // BTWINDOW_H
