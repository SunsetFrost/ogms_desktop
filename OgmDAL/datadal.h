#ifndef DATADAL_H
#define DATADAL_H

#include "OgmEntity/data.h"

#include <QDomDocument>

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

    QString getDataMappingXML(DataServer *server, QString id, QString type);//type=  xml  or json

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

    QString getDataRefactorParamSchema(DataServer *server, QString id, QString schema, QString ioType);

private:
    QList<DataRefactor*> json2dataRefactorList(QByteArray dataStr, QString serverId);

    QList<DataRefactorMethod*> json2dataRefactorMethodList(QByteArray byte, QString serverId, QString refactorId);
};

/////////////////////////////////////////////////
class DataServerDAL
{
public:
    DataServerDAL();

public:
    QList<DataServer*> getAllServer();
    DataServer* getServerById(QString serverId);
    void addServer(DataServer *server);
    bool deleteOneServer(DataServer *server);

private:
    void dataServerList2xml(QList<DataServer*> &dataServerList, QDomDocument &doc);
    void xml2dataServerList(QDomDocument &doc, QList<DataServer*> &dataServerList);
    void setAllDataServerList(QList<DataServer*> dataServerList);

    QList<DataServer*> _serverList;
};

#endif // DATADAL_H
