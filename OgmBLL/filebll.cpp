#include "filebll.h"

DataFileBll::DataFileBll()
{
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL);
    _dataFileDAL=QSharedPointer<DataFileDAL>(new DataFileDAL);
}

QList<DataFile *> DataFileBll::getAllFiles(QString serverId)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    QList<DataFile*> fileList=_dataFileDAL.data()->getFiles(server, "-1", "admin", 10, 0);
    return fileList;
}

QList<DataFile *> DataFileBll::getFilesByParent(QString serverId, QString parentId)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    QList<DataFile*> fileList=_dataFileDAL.data()->getFiles(server, parentId, "admin", 10, 0);

    return fileList;
}

void DataFileBll::addFolder(QString serverId, QString parentId, QString folderName, QString addTime)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->addFolder(server, parentId, folderName, addTime);
}

void DataFileBll::deleteData(QString serverId, QString id, QString type)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->deleteData(server, id, type);
}

void DataFileBll::uploadFile(QString serverId, QString parentId, QString filePath)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->uploadFile(server, parentId, filePath);
}
