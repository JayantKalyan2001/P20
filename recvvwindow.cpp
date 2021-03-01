#include "recieverWindow.h"
#include "window.h"
#include "ui_window.h"

RecvWindow::RecvWindow(QWidget *parent) :
    QMainWindow(parent),  ui(new Ui::Window)
{
  ui->setupUi(this);
  setAutoFillBackground(true);
  pixRecieve=QPixmap(size());
  pixRecieve.fill();
  recvThread.start();
  QObject::connect(&recvThread,SIGNAL(transferPackageToRecieve(dataPackage*)),this,SLOT(recieveData(dataPackage*)));
  update();
  setWindowTitle("Recieve Window");
}

void RecvWindow::paintEvent (QPaintEvent *recieverWindowOutput)
{
    QPainter recievePainter(this);
    recievePainter.drawPixmap(rect(),pixRecieve);
}

void RecvWindow::recieveData(dataPackage* pck)
{
    globalMutex.lock();
    dataPackage pkg = *pck;
    recvThread.cmdFinished = true;
    globalMutex.unlock();

    if(pkg.command==dataPackage::Blank)
    {
        pixRecieve.fill();
    }
    else if(pkg.command==dataPackage::Draw)
    {
        QPainter pixPainter(&pixRecieve);
        qDebug() << "[recvWindoe] draw pkg.data = "<<pkg.data;
        QPoint *points = (QPoint *)pkg.data.constData();
        pixPainter.drawLine(points[0], points[1]);
    }
    else if(pkg.command==dataPackage::Enlarge)
    {
        qDebug() << "[recvWindoe] resize pkg.data = "<<pkg.data;
        QSize size = *(QSize *)pkg.data.constData();
        resize(size);
        pixRecieve=QPixmap(size);
        pixRecieve.fill();
    }
    update();
}
RecvWindow::~RecvWindow()
{
   delete ui;
}

