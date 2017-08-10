#ifndef FILEDAL_H
#define FILEDAL_H

#include "OgmEntity/file.h"
#include "OgmEntity/data.h"

#include <QList>

class DataFileDAL
{
public:
    DataFileDAL();

    QList<DataFile*> getFiles(DataServer *server, QString parentId, QString userName, int pageAmount, int page);
    //post
    void uploadFile(DataServer *server, QString parentId, QString dataPath);

    void deleteData(DataServer *server, QString id, QString type);

    void updateName(DataServer *server, QString id, QString newName, QString newTime);

    void addFolder(DataServer *server, QString parentId, QString folderName, QString addTime);

    QString download(DataServer *server, QString fileName);

private:
    QList<DataFile*> json2fileList(QByteArray response);
};

#endif // FILEDAL_H
