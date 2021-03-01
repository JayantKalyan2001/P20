#include <QApplication>
#include <QDebug>
#include "recieverWindow.h"

#include <pthread.h>
#include <wiringPi.h>

#include "window.h"
#include "recieverwindow.h"
#include "outputthread.h"
#include "inputthread.h"

QQueue <char> cmdQueueGlobal;
bool cmdRead = true;
bool globalBinaryData=false;
QMutex globalMutex;



int main(int argc, char *argv[])
{
    qDebug()<<"[main] line 30 cmdRead="<< cmdRead;
    QApplication a(argc, argv);
    Window w;
    w.show();
    R.show();
    int ret = a.exec();
    return ret;
}
