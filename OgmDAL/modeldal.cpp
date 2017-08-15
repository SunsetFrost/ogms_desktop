#include "modeldal.h"

#include "OgmCommon/ogmnetwork.h"
#include "OgmCommon/ogmsetting.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

ModelServiceDAL::ModelServiceDAL()
{

}

QList<ModelService *> ModelServiceDAL::getAllModelService(ModelServer *server)
{
    QString request="http://"+server->ip+"/modelser/json/all";

    QByteArray byteResult=OgmNetWork::get(request);

    return json2modelServiceList(byteResult, server->id);
}

QList<ModelService *> ModelServiceDAL::getModelServiceListByNumber(ModelServer *server, int start, int count)
{
    QString request="http://"+server->ip+"/modelser/json/all?start="+QString::number(start)+"&count="+QString::number(count);

    QByteArray byteResult=OgmNetWork::get(request);
    return json2modelServiceList(byteResult, server->id);
}

ModelService *ModelServiceDAL::getOneModelServiceById(ModelServer *server, QString modelId)
{
    QList<ModelService*> msList= getAllModelService(server);

    for(int i=0; i<msList.count(); ++i){
        if(msList.at(i)->id==modelId){
            return msList.at(i);
        }
    }
    ModelService *nullModel=new ModelService();
    return nullModel;
}

QString ModelServiceDAL::getExampleDataOfOneEvent(ModelServer *server, QString modelId, QString stateId, QString eventName)
{
    QString request="http://"+server->ip+"/modelser/testify/"+modelId;
    QByteArray byteResult=OgmNetWork::get(request);

    QJsonObject jsonRoot=QJsonDocument::fromJson(byteResult).object();
    QJsonArray jsonTestifies=jsonRoot.value("testifies").toArray();

    //TODO temp select first example data in array
    QJsonObject jsonTestify=jsonTestifies.at(0).toObject();
    QJsonArray jsonInputArray=jsonTestify.value("inputs").toArray();
    for(int iArray=0; iArray<jsonInputArray.size(); ++iArray){
        QString examepleStateId=jsonInputArray.at(iArray).toObject().value("StateId").toString();
        QString exampleEventName=jsonInputArray.at(iArray).toObject().value("Event").toString();
        QString exampleDataId=jsonInputArray.at(iArray).toObject().value("DataId").toString();
        if(exampleEventName==eventName && examepleStateId==stateId){
            return exampleDataId;
        }
    }
    return QString();
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
    QDomDocument doc;
    QFile file(OgmSetting::modelServerFilePath);
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();

    QList<ModelServer*> serverList;
    xml2modelServerList(doc, serverList);

    return serverList;
}

ModelServer *ModelServerDAL::getServerById(QString serverId)
{
    QList<ModelServer*> serverList=getAllServer();
    for(int i=0; i<serverList.count(); ++i){
        if(serverList.at(i)->id==serverId){
            return serverList.at(i);
        }
    }
    ModelServer *nullServer=new ModelServer();
    return nullServer;
}

void ModelServerDAL::addServer(ModelServer *server)
{
    QList<ModelServer*> serverList=getAllServer();
    serverList.append(server);
    setAllModelServerList(serverList);
}

bool ModelServerDAL::deleteOneServer(ModelServer *server)
{
    QList<ModelServer*> serverList=getAllServer();
    for(int i=0; i<serverList.count(); ++i){
        if(serverList.at(i)->id==server->id){
            serverList.removeAt(i);
            setAllModelServerList(serverList);
            return true;
        }
    }
    return false;
}

void ModelServerDAL::modelServerList2xml(QList<ModelServer *> &modelServerList, QDomDocument &doc)
{
    QDomAttr attr;

    QDomElement elementConfig=doc.createElement("server");
    doc.appendChild(elementConfig);

    for(int i=0; i<modelServerList.count(); ++i){
        QDomElement elementGroup=doc.createElement("modelserver");

        attr=doc.createAttribute("id");
        attr.setValue(modelServerList.at(i)->id);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("ip");
        attr.setValue(modelServerList.at(i)->ip);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("name");
        attr.setValue(modelServerList.at(i)->name);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("system");
        attr.setValue(modelServerList.at(i)->system);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("location");
        attr.setValue(modelServerList.at(i)->location);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("desc");
        attr.setValue(modelServerList.at(i)->desc);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("connect");
        if(modelServerList.at(i)->isConnect){
            attr.setValue("true");
        }
        else{
            attr.setValue("false");
        }
        elementGroup.setAttributeNode(attr);

        elementConfig.appendChild(elementGroup);
    }
}

void ModelServerDAL::xml2modelServerList(QDomDocument &doc, QList<ModelServer *> &modelServerList)
{
    QDomElement elementConfig=doc.documentElement();
    QDomNodeList nodeListGroup=elementConfig.childNodes();
    for(int i=0; i<nodeListGroup.count(); ++i){
        QDomNode nodeGroup=nodeListGroup.item(i);
        if(nodeGroup.nodeName()=="modelserver"){
            QDomElement elementGroup=nodeGroup.toElement();

            ModelServer *server=new ModelServer();
            server->id=elementGroup.attributeNode("id").value();
            server->ip=elementGroup.attributeNode("ip").value();
            server->name=elementGroup.attributeNode("name").value();
            server->system=elementGroup.attributeNode("system").value();
            server->location=elementGroup.attributeNode("location").value();
            server->desc=elementGroup.attributeNode("desc").value();

            modelServerList.append(server);
        }
    }
}

void ModelServerDAL::setAllModelServerList(QList<ModelServer *> modelServerList)
{
    QFile file(OgmSetting::modelServerFilePath);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    QDomDocument doc;
    modelServerList2xml(modelServerList, doc);
    doc.save(out, 4);
}
