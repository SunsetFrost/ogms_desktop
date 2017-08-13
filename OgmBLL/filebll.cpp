#include "filebll.h"
#include "OgmCommon/ogmsetting.h"

#include <QTextStream>


DataFileBll::DataFileBll()
{
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL);
    _dataFileDAL=QSharedPointer<DataFileDAL>(new DataFileDAL);
}

QList<DataFile *> DataFileBll::getAllFiles(QString serverId)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    QList<DataFile*> fileList=_dataFileDAL.data()->getFiles(server, "-1", OgmSetting::dataServerUserName, 18, 0);
    return fileList;
}

QList<DataFile *> DataFileBll::getFilesByParent(QString serverId, QString parentId)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    QList<DataFile*> fileList=_dataFileDAL.data()->getFiles(server, parentId, OgmSetting::dataServerUserName, 18, 0);

    return fileList;
}

void DataFileBll::addFolder(QString serverId, QString parentId, QString folderName, QString addTime)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->addFolder(server, parentId, folderName, addTime, OgmSetting::dataServerUserName);
}

void DataFileBll::deleteData(QString serverId, QString id, QString type)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->deleteData(server, id, type, OgmSetting::dataServerUserName);
}

void DataFileBll::uploadFile(QString serverId, QString parentId, QString filePath)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->uploadFile(server, parentId, filePath, OgmSetting::dataServerUserName);
}

void DataFileBll::uploadFile(QString serverId, QString parentId, QString fileStream, QString fileName)
{
    DataServer* server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->uploadFile(server, parentId, fileStream, fileName, OgmSetting::dataServerUserName);
}

void DataFileBll::updateFileName(QString serverId, QString fileId, QString newName, QString newTime)
{
    DataServer *server=_dataServerDAL.data()->getServerById(serverId);
    _dataFileDAL.data()->updateName(server, fileId, newName, newTime, OgmSetting::dataServerUserName);
}

void DataFileBll::downloadFile(QString serverId, QString fileId, QString savePath)
{
    DataServer *server=_dataServerDAL.data()->getServerById(serverId);
    QString result=_dataFileDAL.data()->download(server, fileId, OgmSetting::dataServerUserName);

    QFile file(savePath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&file);
    ts<<result<<endl;
    file.close();
}
