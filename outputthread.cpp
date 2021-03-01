#include "outputthread.h"
#include "package.h"
#include <QDebug>
void OutputThread::OutputQQueue()
{
    if(!cmdQueueGlobal.isEmpty())
        {
            qDebug()<<"[Send thread empty ]";
        }
    while(!cmdQueueGlobal.isEmpty())
        {
            qDebug()<<" "<<cmdQueueGlobal.front();
            cmdQueueGlobal.pop_front();
        }
}
OutputThread::OutputThread() 
{
   MutexRecieve.lock();
   restart = false;
   abort = false;
   startFlag = false;
   MutexRecieve.unlock();
}
OutputThread::~OutputThread()
{
    MutexRecieve.lock();
    abort=true;
    MutexRecieve.unlock();
}
void OutputThread::run()
{
    qDebug()<<"run() is running";
    int count =0;
    for(;;)
    {
         while(!startFlag)
         {
            usleep(5);
         }
         dataPackage pkg =this->pkgRecieve;
         qDebug() <<"output thread execution count = "<< count;
         count++;
         startFlag = false;
         sendByteValue(pkg.command);
         int size = pkg.data.size();
         sendByteValue(size);
         qDebug() << "[SendThread] datasize = " << size;
         qDebug() << "[SendThread] data = " << pkg.data;
         for(int k=0;k<size;k++)
         {
           sendByteValue(pkg.data.at(k));
         }
     }

}

void OutputThread::transferPackage(dataPackage* pkg)
{
    globalMutex.lock();
    this->pkgRecieve=*pkg;
    startFlag = true;
    globalMutex.unlock();
    if(!(isRunning()))
    {
        start();
    }
}

void OutputThread::sendByteValue(quint8 localByteData)
{
    for (int i = 0; i < 8; i++)
    {
        while(cmdRead == false);
        globalMutex.lock();
        globalBinaryData=localByteData &0x80; // 0x80 1000 0000 and sending the MSB value
        localByteData <<=1;
        cmdRead = false;
        globalMutex.unlock();
    }
}


