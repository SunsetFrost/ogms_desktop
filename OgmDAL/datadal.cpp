#include "datadal.h"

#include "OgmCommon/ogmnetwork.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

DataServiceDAL::DataServiceDAL()
{

}

DataService* DataServiceDAL::getDataById(DataServer *server, QString id)
{
    int count=getDataCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=data&pageamount="+count+"&page=0&ids[]="+id;
    QByteArray result=OgmNetWork::get(request);

    QList<DataService*> listData=json2dataServiceList(result, server->id);

    if(listData.isEmpty()){
        DataService *njData=new DataService();
        return njData ;
    }

    DataService *data=listData.at(0);
    return data;
}

QList<DataService *> DataServiceDAL::getAllData(DataServer *server)
{
    int count=getDataCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=data&pageamount="+count+"&page=0&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataServiceList(result, server->id);
}

QList<DataService *> DataServiceDAL::getDataListByPage(DataServer *server, int pageAmount, int pageIndex)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=data&pageamount="+pageAmount+"&page="+pageIndex+"&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataServiceList(result, server->id);
}

//DataService DataServiceDAL::getDataByPage(DataServer *server, int pageAmount, int pageIndex, QString ids)
//{

//}

int DataServiceDAL::getDataCount(DataServer *server)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/serviceCount?stype=data";
    QByteArray result=OgmNetWork::get(request);

    int count=result.toInt();
    return count;
}

QList<DataService *> DataServiceDAL::json2dataServiceList(QByteArray dataStr, QString serverId)
{
    QJsonParseError jsonError;
    QJsonArray jsonArray=QJsonDocument::fromJson(dataStr, &jsonError).array();

    QList<DataService*> listData;

    if(jsonError.error==QJsonParseError::NoError){
        for(int i=0; i<jsonArray.size(); ++i){
            QJsonObject json=jsonArray.at(i).toObject();

            DataService *njData=new DataService();
            njData->id=json.value("_id").toString();
            njData->serverId=serverId;
            njData->name=json.value("name").toString();
            njData->desc=json.value("dDescription").toString();
            njData->author=json.value("author").toString();
            QList<QString> tagList;
            for(int j=0; j<json.value("dTags").toArray().size(); ++j){
                QString tag=json.value("dTags").toArray().at(j).toString();
                tagList.append(tag);
            }
            njData->tags=tagList;
//            njData->genTime=json.value("dGenTime").toString();
//            njData->propertyOwner=json.value("dPropertyOwner").toString();
//            njData->remarkers=json.value("dRemarkers").toString();
//            njData->authorizationMode=json.value("dAuthorizationMode").toString();
//            njData->permissions=json.value("dPermissions").toString();
//            njData->snapShot=json.value("dSnapshot").toString();
//            njData->available=json.value("available").toString();
//            njData->dateTime=json.value("datetime").toString();
            njData->details=json.value("details").toString();

            listData.append(njData);
        }
        return listData;
    }
    else{
        return listData;
    }
}

DataServerDAL::DataServerDAL()
{
    DataServer *dataServerA=new DataServer();
    dataServerA->id="1000";      dataServerA->ip="223.2.35.240:8899";
    dataServerA->name="DataServerAlpha";  dataServerA->system="Windows";
    dataServerA->location="NJ,China";

    DataServer *dataServerB=new DataServer();
    dataServerB->id="1001";     dataServerB->ip="223.2.41.140:8899";
    dataServerB->name="DataServerBeta";     dataServerB->system="Windows";
    dataServerB->location="NJ,China";

    _serverList.append(dataServerA);
    _serverList.append(dataServerB);
}

QList<DataServer*> DataServerDAL::getAllServer()
{
    return _serverList;
}

DataServer* DataServerDAL::getServerById(QString serverId)
{
    for(int i=0; i<_serverList.count(); ++i){
        if(_serverList.at(i)->id==serverId){
            return _serverList.at(i);
        }
    }
    DataServer *nullServer=new DataServer();
    return nullServer;
}

DataMappingDAL::DataMappingDAL()
{

}

DataMapping *DataMappingDAL::getDataMappingById(DataServer *server, QString id)
{
    int count=getDataMappingCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=datamap&pageamount="+count+"&page=0&ids[]="+id;
    QByteArray result=OgmNetWork::get(request);

    QList<DataMapping*> listData=json2dataMappingList(result, server->id);

    if(listData.isEmpty()){
        DataMapping *njData=new DataMapping();
        return njData ;
    }

    DataMapping *data=listData.at(0);
    return data;
}

QList<DataMapping *> DataMappingDAL::getAllDataMapping(DataServer *server)
{
    int count=getDataMappingCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=datamap&pageamount="+count+"&page=0&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataMappingList(result, server->id);
}

QList<DataMapping *> DataMappingDAL::getDataMappingListByPage(DataServer *server, int pageAmount, int pageIndex)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=datamap&pageamount="+pageAmount+"&page="+pageIndex+"&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataMappingList(result, server->id);
}

int DataMappingDAL::getDataMappingCount(DataServer *server)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/serviceCount?stype=datamap";
    QByteArray result=OgmNetWork::get(request);

    int count=result.toInt();
    return count;
}

QList<DataMapping *> DataMappingDAL::json2dataMappingList(QByteArray dataStr, QString serverId)
{
    QJsonParseError jsonError;
    QJsonArray jsonArray=QJsonDocument::fromJson(dataStr, &jsonError).array();

    QList<DataMapping*> listData;

    if(jsonError.error==QJsonParseError::NoError){
        for(int i=0; i<jsonArray.size(); ++i){
            QJsonObject json=jsonArray.at(i).toObject();

            DataMapping *njData=new DataMapping();
            njData->id=json.value("_id").toString();
            njData->serverId=serverId;
            njData->name=json.value("name").toString();
            njData->description=json.value("dDescription").toString();
            njData->author=json.value("author").toString();
            QList<QString> tagList;
            for(int j=0; j<json.value("dTags").toArray().size(); ++j){
                QString tag=json.value("dTags").toArray().at(j).toString();
                tagList.append(tag);
            }
            njData->tags=tagList;
            njData->details=json.value("details").toString();

            listData.append(njData);
        }
        return listData;
    }
    else{
        return listData;
    }
}

DataRefactorDAL::DataRefactorDAL()
{

}

DataRefactor *DataRefactorDAL::getDataRefactorById(DataServer *server, QString id)
{
    int count=getDataRefactorCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=refactor&pageamount="+count+"&page=0&ids[]="+id;
    QByteArray result=OgmNetWork::get(request);

    QList<DataRefactor*> listData=json2dataRefactorList(result, server->id);

    if(listData.isEmpty()){
        DataRefactor *njData=new DataRefactor();
        return njData ;
    }

    DataRefactor *data=listData.at(0);
    return data;
}

QList<DataRefactor *> DataRefactorDAL::getAllDataRefactor(DataServer *server)
{
    int count=getDataRefactorCount(server);

    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=refactor&pageamount="+count+"&page=0&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataRefactorList(result, server->id);
}

QList<DataRefactor *> DataRefactorDAL::getDataRefactorListByPage(DataServer *server, int pageAmount, int pageIndex)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/services?type=refactor&pageamount="+pageAmount+"&page="+pageIndex+"&ids=all";
    QByteArray result=OgmNetWork::get(request);

    return json2dataRefactorList(result, server->id);
}

int DataRefactorDAL::getDataRefactorCount(DataServer *server)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/common/serviceCount?stype=refactor";
    QByteArray result=OgmNetWork::get(request);

    int count=result.toInt();
    return count;
}

QList<DataRefactorMethod *> DataRefactorDAL::getDataRefactorMethodList(DataServer *server, QString refactorId)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/refactor/methods?id="+refactorId;
    QByteArray result=OgmNetWork::get(request);

    return json2dataRefactorMethodList(result, server->id, refactorId);
}

QList<DataRefactor *> DataRefactorDAL::json2dataRefactorList(QByteArray dataStr, QString serverId)
{
    QJsonParseError jsonError;
    QJsonArray jsonArray=QJsonDocument::fromJson(dataStr, &jsonError).array();

    QList<DataRefactor*> listData;

    if(jsonError.error==QJsonParseError::NoError){
        for(int i=0; i<jsonArray.size(); ++i){
            QJsonObject json=jsonArray.at(i).toObject();

            DataRefactor *njData=new DataRefactor();
            njData->id=json.value("_id").toString();
            njData->serverId=serverId;
            njData->name=json.value("name").toString();
            njData->description=json.value("dDescription").toString();
            njData->author=json.value("author").toString();
            QList<QString> tagList;
            for(int j=0; j<json.value("dTags").toArray().size(); ++j){
                QString tag=json.value("dTags").toArray().at(j).toString();
                tagList.append(tag);
            }
            njData->tags=tagList;
            njData->details=json.value("details").toString();

            listData.append(njData);
        }
        return listData;
    }
    else{
        return listData;
    }
}

QList<DataRefactorMethod *> DataRefactorDAL::json2dataRefactorMethodList(QByteArray byte, QString serverId, QString refactorId)
{
    QJsonParseError jsonError;
    QJsonObject jsonObj=QJsonDocument::fromJson(byte, &jsonError).object();

    QList<DataRefactorMethod*> methodList;

    if(jsonError.error==QJsonParseError::NoError){
        QJsonObject jsonReInfo=jsonObj.value("RefactorMethodInfo").toObject();
        QJsonArray jsonMethodArray=jsonReInfo.value("Method").toArray();
        for(int i=0; i<jsonMethodArray.size(); ++i){
            QJsonObject jsonMethod=jsonMethodArray.at(i).toObject();

            DataRefactorMethod *method=new DataRefactorMethod();
            method->serverId=serverId;
            method->refactorId=refactorId;

            method->name=jsonMethod.value("@name").toString();
            method->methodClass=jsonMethod.value("@class").toString();
            method->description=jsonMethod.value("@description").toString();

            QList<DataRefactorMethodParam*> paramList;

            QJsonArray jsonParamArray=jsonMethod.value("Params").toArray();
            for(int j=0; j<jsonParamArray.size(); ++j){
                QJsonObject jsonParam=jsonParamArray.at(j).toObject();

                DataRefactorMethodParam *param=new DataRefactorMethodParam();
                param->dataType=jsonParam.value("@datatype").toString();
                param->type=jsonParam.value("@type").toString();
                param->name=jsonParam.value("@name").toString();
                param->description=jsonParam.value("@description").toString();
                param->schema=jsonParam.value("@schema").toString();

                paramList.append(param);
            }
            method->paramList=paramList;

            methodList.append(method);
        }
    }
    return methodList;
}
