#ifndef MODELBLL_H
#define MODELBLL_H

#include "OgmDAL/modeldal.h"

#include <QSharedPointer>

class ModelServiceBLL
{
public:
    ModelServiceBLL();

    QList<ModelService*> getAllModelService(QString serverId);
    QList<ModelService*> getModelServiceListByPage(QString serverId, int pageIndex);

    ModelService* getOneModelServiceById(QString serverId, QString modelId);

private:
    QSharedPointer<ModelServerDAL> _modelServerDAL;
    QSharedPointer<ModelServiceDAL> _modelServiceDAL;
};

class ModelServerBLL
{
public:
    ModelServerBLL();

    QList<ModelServer*> getAllServer();

    ModelServer* getServerId(QString serverId);

    void addServer(ModelServer *server);

    bool deleteOneServer(ModelServer *server);

private:
    QSharedPointer<ModelServerDAL> _modelServerDAL;
};

#endif // MODELBLL_H
