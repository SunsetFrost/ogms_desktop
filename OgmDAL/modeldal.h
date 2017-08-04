#ifndef MODELDAL_H
#define MODELDAL_H

#include "OgmEntity/model.h"

#include <QList>

class ModelServiceDAL
{
public:
    ModelServiceDAL();

    QList<ModelService*> getAllModelService(ModelServer *server);

    QList<ModelService *> getModelServiceListByNumber(ModelServer *server, int start, int count);

    ModelService* getOneModelServiceById(ModelServer *server, QString modelId);

private:
    QList<ModelService*> json2modelServiceList(QByteArray modelListJson, QString serverId);
};

class ModelServerDAL
{
public:
    ModelServerDAL();

    QList<ModelServer*> getAllServer();
    ModelServer* getServerById(QString serverId);

private:
    QList<ModelServer*> _serverList;
};

#endif // MODELDAL_H
