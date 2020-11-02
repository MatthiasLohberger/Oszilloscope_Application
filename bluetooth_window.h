#ifndef BLUETOOTH_WINDOW_H
#define BLUETOOTH_WINDOW_H

#include <QDialog>

namespace Ui {
class bluetooth_window;
}

class bluetooth_window : public QDialog
{
    Q_OBJECT

public:
    explicit bluetooth_window(QWidget *parent = nullptr);
    ~bluetooth_window();

private:
    Ui::bluetooth_window *ui;
};

#endif // BLUETOOTH_WINDOW_H
