#include "databll.h"
#include "OgmCommon/ogmlisthelper.h"

DataServiceBLL::DataServiceBLL()
{
    _dataServiceDAL=QSharedPointer<DataServiceDAL>(new DataServiceDAL());
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL());
}

DataService *DataServiceBLL::getDataById(QString serverId, QString modelId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    DataService* dataService=_dataServiceDAL.data()->getDataById(dataServer, modelId);
    return dataService;
}

QList<DataService *> DataServiceBLL::getAllData(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataService*> dsList=_dataServiceDAL.data()->getAllData(dataServer);
    return dsList;
}

QList<DataService *> DataServiceBLL::getDataListByPage(QString serverId, int pageIndex)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataService*> dsList=_dataServiceDAL.data()->getDataListByPage(dataServer, OgmListHelper::pageAmount, pageIndex);
    return dsList;
}

int DataServiceBLL::getDataCount(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    int count=_dataServiceDAL.data()->getDataCount(dataServer);
    return count;
}

DataServerBLL::DataServerBLL()
{
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL());
}

QList<DataServer *> DataServerBLL::getAllServer()
{
    QList<DataServer*> serverList=_dataServerDAL.data()->getAllServer();
    return serverList;
}

DataServer *DataServerBLL::getServerId(QString serverId)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    return server;
}

DataMappingBLL::DataMappingBLL()
{
    _dataMappingDAL=QSharedPointer<DataMappingDAL>(new DataMappingDAL());
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL());
}

DataMapping *DataMappingBLL::getDataMappingById(QString serverId, QString mappingId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    DataMapping* dataMapping=_dataMappingDAL.data()->getDataMappingById(dataServer, mappingId);
    return dataMapping;
}

QList<DataMapping *> DataMappingBLL::getAllDataMapping(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataMapping*> dsList=_dataMappingDAL.data()->getAllDataMapping(dataServer);
    return dsList;
}

QList<DataMapping *> DataMappingBLL::getDataMappingByPage(QString serverId, int pageIndex)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataMapping*> dsList=_dataMappingDAL.data()->getDataMappingListByPage(dataServer, OgmListHelper::pageAmount, pageIndex);
    return dsList;
}

int DataMappingBLL::getDataMappingCount(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    int count=_dataMappingDAL.data()->getDataMappingCount(dataServer);
    return count;
}

DataRefactorBLL::DataRefactorBLL()
{
    _dataRefactorDAL=QSharedPointer<DataRefactorDAL>(new DataRefactorDAL());
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL());
}

DataRefactor *DataRefactorBLL::getDataRefactorById(QString serverId, QString refactorId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    DataRefactor* dataRefactor=_dataRefactorDAL.data()->getDataRefactorById(dataServer, refactorId);
    return dataRefactor;
}

QList<DataRefactor *> DataRefactorBLL::getAllDataRefactor(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataRefactor*> dsList=_dataRefactorDAL.data()->getAllDataRefactor(dataServer);
    return dsList;
}

QList<DataRefactor *> DataRefactorBLL::getDataRefactorByPage(QString serverId, int pageIndex)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataRefactor*> dsList=_dataRefactorDAL.data()->getDataRefactorListByPage(dataServer, OgmListHelper::pageAmount, pageIndex);
    return dsList;
}

int DataRefactorBLL::getDataRefactorCount(QString serverId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    int count=_dataRefactorDAL.data()->getDataRefactorCount(dataServer);
    return count;
}

QList<DataRefactorMethod *> DataRefactorBLL::getAllDataRefactorMethodByRefactorId(QString serverId, QString refactorId)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataRefactorMethod*> methodList=_dataRefactorDAL.data()->getDataRefactorMethodList(dataServer, refactorId);
    return methodList;
}

DataRefactorMethod *DataRefactorBLL::getDataRefactorByMethodName(QString serverId, QString refactorId, QString methodName)
{
    DataServer* dataServer=_dataServerDAL.data()->getServerById(serverId);
    QList<DataRefactorMethod*> methodList=_dataRefactorDAL.data()->getDataRefactorMethodList(dataServer, refactorId);

    DataRefactorMethod *method=0;
    for(int i=0; i<methodList.count(); ++i){
        if(methodList[i]->name==methodName){
            return methodList[i];
        }
    }
    return method;
}














