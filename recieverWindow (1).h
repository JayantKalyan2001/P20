#ifndef RECVWINDOW_H
#define RECVWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>
#include <QPushButton>
#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QMainWindow>
#include "package.h"
#include "inputthread.h"

namespace Ui
{
    class Window;
}

class RecvWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::Window *ui;
        InputThread recvThread;
        int resizeCount;

    public slots:
        void recieveData(dataPackage* );

    public:
        QPixmap  pixRecieve;
        explicit RecvWindow(QWidget *parent = 0);

    protected:
        void paintEvent (QPaintEvent *recieverWindowOutput);
};

#endif // RECVVWINDOW_H
