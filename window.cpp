#include "window.h"
#include "ui_window.h"


Window::Window(QWidget *parent) :QMainWindow(parent),ui(new Ui::Window)
{  
    ui->setupUi(this);
    clear_button=new QPushButton("clear",this);
    clear_button->setGeometry(QRect(QPoint(10, 50),QSize(100, 25)));
    connect(clear_button,SIGNAL(pressed()),this,SLOT(clearImage()));
    resizeCount=0;
}

Window::~Window()
{
    delete ui;
}

void Window::resizeEvent(QResizeEvent *userResizing)
{
    pix = QPixmap(userResizing->size().width(), userResizing->size().height());
    pix.fill();
    if(resizeCount>=1)
   {
        dataPackage pkg;//
        pkg.command = dataPackage::Enlarge;
        pkg.data.append((const char *)&userResizing->size(), sizeof(userResizing->size()));
        sendThread.transferPackage(&pkg);
    }
    resizeCount++;
}

void Window::paintEvent(QPaintEvent *userDrawingOutput)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pix);
}

void Window::mouseMoveEvent(QMouseEvent *userDrawingInput)
{
    QPainter pixPainter(&pix);
    endingPoint=userDrawingInput->pos();
    pixPainter.drawLine(lastRecordedPoint,endingPoint);
    dataPackage pkg;
    pkg.command = dataPackage::Draw;
    pkg.data.append((const char *)&lastRecordedPoint, sizeof(lastRecordedPoint));
    pkg.data.append((const char *)&endingPoint, sizeof(lastRecordedPoint));
    sendThread.transferPackage(&pkg);
    lastRecordedPoint = endingPoint;
    update();
}

void Window::mousePressEvent(QMouseEvent *userDrawingInput)
{
    if(userDrawingInput->button()==Qt::LeftButton)
     {
       lastRecordedPoint=userDrawingInput->pos();
       drawing=true;
     }
}

void Window::clearImage()
{
  pix.fill(); //empty argument clears the pix.
  update();
  dataPackage pkg;
  pkg.command = dataPackage::Blank; 
  sendThread.transferPackage(&pkg);
}

