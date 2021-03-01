#ifndef INPUTTHREAD_H
#define INPUTTHREAD_H
#include <QThread>
#include <QtDebug>
#include "package.h"

class InputThread:public QThread
{
    Q_OBJECT

    public:
        InputThread();
       virtual ~InputThread();
        bool cmdFinished;
        quint8 recvByte();

    signals:
        void transferPackageToRecieve(dataPackage* pkg);

    public slots:
        void startThread();

    private:
        dataPackage pkgSend;
        QMutex MutexSend;
        bool abort,restart;

    protected:
        void run() override;
};

#endif // INPUTTHREAD_H
