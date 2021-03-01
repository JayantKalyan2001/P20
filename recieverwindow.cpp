#include "recieverwindow.h"
//#include "window.h"
#include "ui_recieverwindow.h"

recieverWindow::recieverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recieverWindow)
{
    ui->setupUi(this);
}

recieverWindow::~recieverWindow()
{
    delete ui;
}
