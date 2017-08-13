#ifndef DATABLL_H
#define DATABLL_H

#include "OgmEntity/data.h"
#include "OgmDAL/datadal.h"

#include <QSharedPointer>

class DataServiceBLL
{
public:
    DataServiceBLL();

    DataService* getDataById(QString serverId, QString modelId);

    QList<DataService*> getAllData(QString serverId);

    QList<DataService*> getDataListByPage(QString serverId, int pageIndex);

    int getDataCount(QString serverId);

private:
    QSharedPointer<DataServiceDAL> _dataServiceDAL;
    QSharedPointer<DataServerDAL> _dataServerDAL;

};
////////////////////////////////////////////////
class DataMappingBLL
{
public:
    DataMappingBLL();

    DataMapping* getDataMappingById(QString serverId, QString mappingId);

    QList<DataMapping*> getAllDataMapping(QString serverId);

    QList<DataMapping*> getDataMappingByPage(QString serverId, int pageIndex);

    int getDataMappingCount(QString serverId);

private:
    QSharedPointer<DataMappingDAL> _dataMappingDAL;
    QSharedPointer<DataServerDAL> _dataServerDAL;
};
/////////////////////////////////////////////////////////
class DataRefactorBLL
{
public:
    DataRefactorBLL();

    DataRefactor* getDataRefactorById(QString serverId, QString refactorId);

    QList<DataRefactor*> getAllDataRefactor(QString serverId);

    QList<DataRefactor*> getDataRefactorByPage(QString serverId, int pageIndex);

    int getDataRefactorCount(QString serverId);

    QList<DataRefactorMethod*> getAllDataRefactorMethodByRefactorId(QString serverId, QString refactorId);
    DataRefactorMethod* getDataRefactorByMethodName(QString serverId, QString refactorId, QString methodName);

private:
    QSharedPointer<DataRefactorDAL> _dataRefactorDAL;
    QSharedPointer<DataServerDAL> _dataServerDAL;
};
//////////////////////////////////////////////////////////
class DataServerBLL
{
public:
    DataServerBLL();

    QList<DataServer*> getAllServer();
    QList<DataServer*> getAllServerDelayed();

    DataServer* getServerId(QString serverId);

    void addServer(DataServer *server);

    bool deleteOneServer(DataServer *server);

private:
    QSharedPointer<DataServerDAL> _dataServerDAL;
};

#endif // DATABLL_H
