#ifndef MODELDAL_H
#define MODELDAL_H

#include "OgmEntity/model.h"

#include <QList>
#include <QDomDocument>

class ModelServiceDAL
{
public:
    ModelServiceDAL();

    QList<ModelService*> getAllModelService(ModelServer *server);

    QList<ModelService *> getModelServiceListByNumber(ModelServer *server, int start, int count);

    ModelService* getOneModelServiceById(ModelServer *server, QString modelId);

    QString getExampleDataOfOneEvent(ModelServer *server, QString modelId, QString stateId, QString eventName);



private:
    QList<ModelService*> json2modelServiceList(QByteArray modelListJson, QString serverId);
};

class ModelServerDAL
{
public:
    ModelServerDAL();

    QList<ModelServer*> getAllServer();
    ModelServer* getServerById(QString serverId);
    void addServer(ModelServer *server);
    bool deleteOneServer(ModelServer *server);

private:
    void modelServerList2xml(QList<ModelServer*> &modelServerList, QDomDocument &doc);
    void xml2modelServerList(QDomDocument &doc, QList<ModelServer*> &modelServerList);
    void setAllModelServerList(QList<ModelServer*> modelServerList);

private:
    QList<ModelServer*> _serverList;
};

#endif // MODELDAL_H
