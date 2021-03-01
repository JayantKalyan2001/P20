#ifndef RECIEVERWINDOW_H
#define RECIEVERWINDOW_H

#include <QDialog>

namespace Ui {
class recieverWindow;
}

class recieverWindow : public QDialog
{
    Q_OBJECT

public:
    explicit recieverWindow(QWidget *parent = 0);
    ~recieverWindow();

private:
    Ui::recieverWindow *ui;
};

#endif // RECIEVERWINDOW_H
