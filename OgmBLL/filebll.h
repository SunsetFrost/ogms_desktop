#ifndef FILEBLL_H
#define FILEBLL_H

#include "OgmDAL/filedal.h"
#include "OgmDAL/datadal.h"

#include <QSharedPointer>

class DataFileBll
{
public:
    DataFileBll();

    QList<DataFile*> getAllFiles(QString serverId);

    QList<DataFile*> getFilesByParent(QString serverId, QString parentId);

    void addFolder(QString serverId, QString parentId, QString folderName, QString addTime);

    void deleteData(QString serverId, QString id, QString type);

    void uploadFile(QString serverId, QString parentId, QString filePath);

private:
    QSharedPointer<DataServerDAL> _dataServerDAL;
    QSharedPointer<DataFileDAL> _dataFileDAL;
};

#endif // FILEBLL_H
