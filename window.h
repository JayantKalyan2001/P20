#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>
#include <QPushButton>
#include "package.h"
#include "outputthread.h"


namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    QPixmap pix;
    OutputThread sendThread;
    ~Window();

public slots:
    void clearImage();

signals:
    void sendData(dataPackage* pkg);

private:
    Ui::Window *ui;
    int resizeCount;
    void testButton();
    bool drawing;

    QPoint lastRecordedPoint;
    QPoint endingPoint;
    QPushButton *clear_button;

protected:
    void paintEvent(QPaintEvent *userDrawingOutput) ;
    void mouseMoveEvent(QMouseEvent * userDrawingInput) ;
    void mousePressEvent(QMouseEvent * userDrawingInput) ;
    void resizeEvent(QResizeEvent *e) ;
};

#endif // WINDOW_H
