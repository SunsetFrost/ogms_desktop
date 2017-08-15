#include "favorbll.h"

FavorBLL::FavorBLL()
{
    _favorDAL=QSharedPointer<FavorDAL>(new FavorDAL);

    _modelServerDAL=QSharedPointer<ModelServerDAL>(new ModelServerDAL);
    _modelServiceDAL=QSharedPointer<ModelServiceDAL>(new ModelServiceDAL);

    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL);
    _dataServiceDAL=QSharedPointer<DataServiceDAL>(new DataServiceDAL);
    _dataMappingDAL=QSharedPointer<DataMappingDAL>(new DataMappingDAL);
    _dataRefactorDAL=QSharedPointer<DataRefactorDAL>(new DataRefactorDAL);
}

Favor *FavorBLL::getFavorGroupById(QString favorId)
{
    Favor *favor=_favorDAL.data()->getFavorById(favorId);
    return favor;
}

QList<Favor *> FavorBLL::getAllFavorGroup()
{
    QList<Favor*> favorList=_favorDAL.data()->getAllFavor();
    return favorList;
}

void FavorBLL::addOneFavorGroup(Favor *favor)
{
    _favorDAL.data()->addOneFavor(favor);
}

bool FavorBLL::deleteOneFavorGroup(QString favorId)
{
    Favor *favor=getFavorGroupById(favorId);
    bool isSuccess=_favorDAL.data()->deleteOneFavor(favor);
    return isSuccess;
}

bool FavorBLL::addOneFavorService(SERVICEITEM service, QString favorId)
{
    Favor *favor=_favorDAL.data()->getFavorById(favorId);

    //judge repitition
    foreach(SERVICEITEM item, favor->serviceList){
        if(item.serverId==service.serverId && item.serviceId==service.serviceId){
            return false;
        }
    }

    bool isSuccess=_favorDAL.data()->addOneServiceToOneFavor(service, favor);
    return isSuccess;
}

bool FavorBLL::deleteOneFavorService(SERVICEITEM service, QString favorId)
{
    Favor *favor=_favorDAL.data()->getFavorById(favorId);
    bool isSuccess=_favorDAL.data()->deleteOneServiceInOneFavorGroup(service, favor);
    return isSuccess;
}

QList<ModelService *> FavorBLL::favor2modelServiceList(Favor *favor)
{
    QList<ModelService*> listModel;
    for(int i=0; i<favor->serviceList.count(); ++i){
        if(favor->serviceList.at(i).serviceType=="Model"){
            ModelServer *server=_modelServerDAL.data()->getServerById(favor->serviceList.at(i).serverId);
            ModelService *service=_modelServiceDAL.data()->getOneModelServiceById(server, favor->serviceList.at(i).serviceId);
            if(service->id!=""){
                listModel.append(service);
            }
        }
    }
    return listModel;
}

QList<DataService *> FavorBLL::favor2dataServiceList(Favor *favor)
{
    QList<DataService*> listModel;
    for(int i=0; i<favor->serviceList.count(); ++i){
        if(favor->serviceList[i].serviceType=="Data"){
            DataServer *server=_dataServerDAL.data()->getServerById(favor->serviceList[i].serverId);
            DataService *service=_dataServiceDAL.data()->getDataById(server, favor->serviceList[i].serviceId);
            if(service->id!=""){
                listModel.append(service);
            }
        }
    }
    return listModel;
}

QList<DataMapping *> FavorBLL::favor2dataMappingList(Favor *favor)
{
    QList<DataMapping*> listModel;
    for(int i=0; i<favor->serviceList.count(); ++i){
        if(favor->serviceList[i].serviceType=="DataMapping"){
            DataServer *server=_dataServerDAL.data()->getServerById(favor->serviceList[i].serverId);
            DataMapping *service=_dataMappingDAL.data()->getDataMappingById(server, favor->serviceList[i].serviceId);
            if(service->id!=""){
                listModel.append(service);
            }
        }
    }
    return listModel;
}

QList<DataRefactor *> FavorBLL::favor2dataRefactorList(Favor *favor)
{
    QList<DataRefactor*> listModel;
    for(int i=0; i<favor->serviceList.count(); ++i){
        if(favor->serviceList[i].serviceType=="DataRefactor"){
            DataServer *server=_dataServerDAL.data()->getServerById(favor->serviceList[i].serverId);
            DataRefactor *service=_dataRefactorDAL.data()->getDataRefactorById(server, favor->serviceList[i].serviceId);
            if(service->id!=""){
                listModel.append(service);
            }
        }
    }
    return listModel;
}
