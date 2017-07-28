#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QList>

class ModelService
{
public:
    ModelService();

public:
    QString id;
    QString serverId;
    QString msDes;
    QString msStatus;
    QString msUpdate;
    QString mName;
    QString mType;
    QString userName;
};

Q_DECLARE_METATYPE(ModelService*)

/////////////////////////////////////////////
class ModelServer
{
public:
    ModelServer();

public:
    QString id;
    QString name;
    QString system;
    QString modelNum;
    QString location;
    QString ip;
    QString port;
    QString desc;
    bool isConnect;
};

Q_DECLARE_METATYPE(ModelServer*)


#endif // MODEL_H
