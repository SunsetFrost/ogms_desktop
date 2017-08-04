#include "modeldal.h"

#include "OgmCommon/ogmnetwork.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

ModelServiceDAL::ModelServiceDAL()
{

}

QList<ModelService *> ModelServiceDAL::getAllModelService(ModelServer *server)
{
    QString request="http://"+server->ip+":8060/modelser/json/all";

    QByteArray byteResult=OgmNetWork::get(request);

    return json2modelServiceList(byteResult, server->id);
}

QList<ModelService *> ModelServiceDAL::getModelServiceListByNumber(ModelServer *server, int start, int count)
{
    QString request="http://"+server->ip+":8060/modelser/json/all?start="+QString::number(start)+"&count="+QString::number(count);

    QByteArray byteResult=OgmNetWork::get(request);
    return json2modelServiceList(byteResult, server->id);
}

ModelService *ModelServiceDAL::getOneModelServiceById(ModelServer *server, QString modelId)
{
    QList<ModelService*> msList= getAllModelService(server);

    for(int i=0; i<msList.count(); ++i){
        if(msList[i]->id==modelId){
            return msList[i];
        }
    }
    ModelService *nullModel=new ModelService();
    return nullModel;
}

QList<ModelService *> ModelServiceDAL::json2modelServiceList(QByteArray modelListJson, QString serverId)
{
    QJsonParseError jsonError;
    QJsonObject jsonObj=QJsonDocument::fromJson(modelListJson, &jsonError).object();

    QList<ModelService*> mAllModelServiceList;

    if(jsonError.error == QJsonParseError::NoError){
            QJsonArray jsonArray=jsonObj.value("data").toArray();

            for(int i=0; i<jsonArray.size(); ++i){
                QJsonObject json=jsonArray.at(i).toObject();

                ModelService *modelService=new ModelService();

                modelService->id=json.value("_id").toString();
                modelService->serverId=serverId;
                modelService->msDes=json.value("ms_des").toString();
                modelService->msStatus=json.value("ms_status").toInt();
                modelService->msUpdate=json.value("ms_update").toString();

                QJsonValue jsValueModel= json.value("ms_model");
                QJsonObject jsObjModel=jsValueModel.toObject();
                modelService->mName=jsObjModel.value("m_name").toString();
                modelService->mType=jsObjModel.value("m_type").toString();

                QJsonValue jsValueUser=json.value("ms_user");
                QJsonObject jsObjUser=jsValueUser.toObject();
                modelService->userName=jsObjUser.value("u_name").toString();

                mAllModelServiceList.append(modelService);
            }
    }

    return mAllModelServiceList;
}

ModelServerDAL::ModelServerDAL()
{
    ModelServer *modelServerA=new ModelServer();       modelServerA->id="0000";
    modelServerA->name="ModelServerAlpha";           modelServerA->system="Windows";
    modelServerA->modelNum="78";                modelServerA->location="NJ,China";
    modelServerA->ip="127.0.0.1";               modelServerA->isConnect=true;

    ModelServer *modelServerB=new ModelServer();       modelServerB->id="0001";
    modelServerB->name="ModelServerBeta";            modelServerB->system="Windows";
    modelServerB->modelNum="142";               modelServerB->location="NJ,China";
    modelServerB->ip="223.2.41.140";            modelServerB->isConnect=true;

    ModelServer *modelServerC=new ModelServer();       modelServerC->id="0002";
    modelServerC->name="ModelServerGamma";           modelServerC->system="Windows";
    modelServerC->modelNum="158";               modelServerC->location="NJ,China";
    modelServerC->ip="222.192.7.75";            modelServerC->isConnect=true;

    _serverList.append(modelServerA);
    _serverList.append(modelServerB);
    _serverList.append(modelServerC);
}

QList<ModelServer *> ModelServerDAL::getAllServer()
{
    return _serverList;
}

ModelServer *ModelServerDAL::getServerById(QString serverId)
{
    for(int i=0; i<_serverList.count(); ++i){
        if(_serverList.at(i)->id==serverId){
            return _serverList.at(i);
        }
    }
    ModelServer *nullServer=new ModelServer();
    return nullServer;
}
