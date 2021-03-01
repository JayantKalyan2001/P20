#ifndef PACKAGE_H
#define PACKAGE_H
#include <QMutex>
#include <QByteArray>
#include <QQueue>

extern QQueue <char> cmdQueueGlobal;
extern bool cmdRead;
extern QMutex globalMutex;
extern bool globalBinaryData;

struct dataPackage
{
    quint8 command;//holds the command given in a quint data type , which is a unsigned int repurposed for Qt
    QByteArray data; //Used since we need raw binary data, it is a replacement for qt
    enum Instructions {Blank = 0, Enlarge, Draw};//encodes the commands into numbers via ennumerating them
};
#endif // PACKAGE_H
