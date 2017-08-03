#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QList>

class DataService
{
public:
    DataService();

public:
    QString id;
    QString serverId;
    QString name;
    QString desc;
    QString author;
    QList<QString> tags;
    QString genTime;
    QString propertyOwner;
    QString remarkers;
    QString authorizationMode;
    QString permissions;
    QString snapShot;
    QString available;
    QString dateTime;
    QString details;
};

Q_DECLARE_METATYPE(DataService*)

/////////////////////////////////////
class DataMapping
{
public:
    DataMapping();

public:
    QString id;
    QString serverId;
    QString name;
    QString description;
    QList<QString> tags;
    QString author;
    QString dataTime;
    QString snapshot;
    QString details;
};

Q_DECLARE_METATYPE(DataMapping*)
//////////////////////////////////////
class DataRefactor
{
public:
    DataRefactor();

public:
    QString id;
    QString serverId;
    QString name;
    QString description;
    QList<QString> tags;
    QString author;
    QString dataTime;
    QString details;
};

Q_DECLARE_METATYPE(DataRefactor*)

class DataRefactorMethodParam
{
public:
    QString dataType;
    QString type;
    QString name;
    QString description;
    QString schema;
};


class DataRefactorMethod
{
public:
    QString name;
    QString serverId;
    QString refactorId;
    QString methodClass;
    QString description;
    QList<DataRefactorMethodParam*> paramList;
};

Q_DECLARE_METATYPE(DataRefactorMethod*)


/////////////////////////////////////////
class DataServer
{
public:
    DataServer();

public:
    QString id;
    QString ip;
    QString name;
    QString location;
    QString system;
    QString desc;
};

Q_DECLARE_METATYPE(DataServer*)






















#endif // DATA_H
