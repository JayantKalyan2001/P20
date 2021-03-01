#ifndef OUTPUTTHREAD_H
#define OUTPUTTHREAD_H
#include <QMutex>
#include <QThread>
#include <QtDebug>
#include "package.h"

class OutputThread : public QThread
{
    Q_OBJECT

    signals:
        void startSignal();

    public slots:

    public:
        void transferPackage (dataPackage*);
         OutputThread();
         ~OutputThread();
         void OutputQQueue();
         void sendByteValue(quint8 );

    private:
         dataPackage pkgRecieve;
         QMutex MutexRecieve;
         bool abort,restart;
         bool startFlag;

    protected:
        void run() override;
};

#endif // OUTPUTTHREAD_H
