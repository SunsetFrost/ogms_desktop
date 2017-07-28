#include "modelbll.h"

ModelServiceBLL::ModelServiceBLL()
{
    _modelServerDAL=QSharedPointer<ModelServerDAL>(new ModelServerDAL);
    _modelServiceDAL=QSharedPointer<ModelServiceDAL>(new ModelServiceDAL);
}

QList<ModelService *> ModelServiceBLL::getAllModelService(QString serverId)
{
    ModelServer *modelServer=_modelServerDAL.data()->getServerById(serverId);
    QList<ModelService*> msList=_modelServiceDAL.data()->getAllModelService(modelServer);
    return msList;
}

ModelService *ModelServiceBLL::getOneModelServiceById(QString serverId, QString modelId)
{
    ModelServer *modelServer=_modelServerDAL.data()->getServerById(serverId);
    ModelService *modelService=_modelServiceDAL.data()->getOneModelServiceById(modelServer, modelId);
    return modelService;
}

ModelServerBLL::ModelServerBLL()
{
    _modelServerDAL=QSharedPointer<ModelServerDAL>(new ModelServerDAL);
}

QList<ModelServer *> ModelServerBLL::getAllServer()
{
    QList<ModelServer*> serverList=_modelServerDAL.data()->getAllServer();
    return serverList;
}

ModelServer *ModelServerBLL::getServerId(QString serverId)
{
    ModelServer *server=_modelServerDAL.data()->getServerById(serverId);
    return server;
}