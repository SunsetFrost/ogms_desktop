#ifndef DATADAL_H
#define DATADAL_H

#include "OgmEntity/data.h"

class DataServiceDAL
{
public:
    DataServiceDAL();

    DataService* getDataById(DataServer *server, QString id);

    QList<DataService*> getAllData(DataServer *server);

    QList<DataService*> getDataListByPage(DataServer *server, int pageAmount, int pageIndex);

//    DataService* getDataByPage(DataServer *server, int pageAmount, int pageIndex, QString ids);

    int getDataCount(DataServer *server);

private:
    QList<DataService*> json2dataServiceList(QByteArray dataStr, QString serverId);
};

////////////////////////////////////////////////
class DataMappingDAL
{
public:
    DataMappingDAL();

    DataMapping* getDataMappingById(DataServer *server, QString id);

    QList<DataMapping*> getAllDataMapping(DataServer *server);

    QList<DataMapping*> getDataMappingListByPage(DataServer *server, int pageAmount, int pageIndex);

    int getDataMappingCount(DataServer *server);

private:
    QList<DataMapping*> json2dataMappingList(QByteArray dataStr, QString serverId);
};

/////////////////////////////////////////////////////
class DataRefactorDAL
{
public:
    DataRefactorDAL();

    DataRefactor* getDataRefactorById(DataServer *server, QString id);

    QList<DataRefactor*> getAllDataRefactor(DataServer *server);

    QList<DataRefactor*> getDataRefactorListByPage(DataServer *server, int pageAmount, int pageIndex);

    int getDataRefactorCount(DataServer *server);

    QList<DataRefactorMethod *> getDataRefactorMethodList(DataServer *server, QString refactorId);

private:
    QList<DataRefactor*> json2dataRefactorList(QByteArray dataStr, QString serverId);

    QList<DataRefactorMethod*> json2dataRefactorMethodList(QByteArray byte, QString serverId);
};

/////////////////////////////////////////////////
class DataServerDAL
{
public:
    DataServerDAL();

public:
    QList<DataServer*> getAllServer();
    DataServer* getServerById(QString serverId);

private:
    QList<DataServer*> _serverList;
};

#endif // DATADAL_H
