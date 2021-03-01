#include "inputthread.h"

InputThread::InputThread()
{
 MutexSend.lock();
 restart=false;
 abort=false;
 cmdFinished=false;
 MutexSend.unlock();
}

InputThread::~InputThread()
{

}

void InputThread::startThread()
{

}

void InputThread::run()
{
    qDebug()<<"[RecieveThread] run() is running";
    int count =0;
    for(;;)
    {
         dataPackage pkg;
         qDebug() << "[RecieveThread] exeCount = " << count;
         count++;
         pkg.command = recvByte();
         int size = recvByte();
         cmdRead = true;
         qDebug() << "[RecieveThread] datasize = " << size;
         for(int k=0;k<size;k++)
          {
              pkg.data.append(recvByte());
          }
         qDebug() << "[RecieveThread] data = " << pkg.data;
         emit transferPackageToRecieve(&pkg);
         while(!cmdFinished)
         {
             usleep(3);
         }
         cmdFinished = false;
     }
 }

quint8 InputThread::recvByte()
{
   quint8 data = 0;
   for (int i = 0; i < 8; i++)
   {
         for(;;)
         {
            if(cmdRead != true)
            {
                break;
            }
         }
         data <<=1;
         data|=globalBinaryData;
         globalMutex.lock();
         cmdRead = true;
         globalMutex.unlock();
    }
    return data;
}
