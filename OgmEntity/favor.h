#ifndef FAVOR_H
#define FAVOR_H

#include <QString>
#include <QList>

struct SERVICEITEM
{
    QString serverId;
    QString serviceId;
    QString serviceType;
};

class Favor
{
public:
    Favor();

public:
    QString id;
    QString name;
    QString des;
    QList<QString> tags;
    QList<SERVICEITEM> serviceList;
};

#endif // FAVOR_H
