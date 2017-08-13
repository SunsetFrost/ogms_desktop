#include "filedal.h"

#include "OgmCommon/ogmnetwork.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

DataFileDAL::DataFileDAL()
{

}

QList<DataFile *> DataFileDAL::getFiles(DataServer *server, QString parentId, QString userName, int pageAmount, int page)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/files?parentid="+parentId+"&username="+userName+"&pageamount="+QString::number(pageAmount)+"&page="+QString::number(page);
    QByteArray response=OgmNetWork::get(request);

    return json2fileList(response);
}

void DataFileDAL::uploadFile(DataServer *server, QString parentId, QString dataPath, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/uploadfile?username="+username+"&parentId="+parentId;
    QByteArray response=OgmNetWork::postDataFile(request, dataPath, parentId);
}

void DataFileDAL::uploadFile(DataServer *server, QString parentId, QString dataStream, QString dataName, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/uploadfile?username="+username+"&parentId="+parentId;
    QByteArray response=OgmNetWork::postDataFile(request, dataStream, dataName, parentId);
}

void DataFileDAL::deleteData(DataServer *server, QString id, QString type, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/deleteUserData?username="+username+"&oid="+id+"&format="+type;
    QByteArray response=OgmNetWork::get(request);
}

void DataFileDAL::updateName(DataServer *server, QString id, QString newName, QString newTime, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/updatename?username="+username+"&oid="+id+"&newname="+newName+"&newTime="+newTime;
    QByteArray response=OgmNetWork::get(request);
}

QString DataFileDAL::addFolder(DataServer *server, QString parentId, QString folderName, QString addTime, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/addFolder?username="+username+"&parentid="+parentId+"&foldername="+folderName+"&addTime="+addTime;
    QByteArray response=OgmNetWork::get(request);
    return QString::fromUtf8(response);
}

QString DataFileDAL::download(DataServer *server, QString fileName, QString username)
{
    QString ip=server->ip;
    QString request="http://"+ip+"/user/download?username="+username+"&filename="+fileName;
    QByteArray response=OgmNetWork::get(request);
    return QString::fromUtf8(response);
}

QList<DataFile *> DataFileDAL::json2fileList(QByteArray response)
{
    QJsonParseError jsonError;
    QJsonArray jsonArray=QJsonDocument::fromJson(response, &jsonError).array();

    QList<DataFile*> listData;

    if(jsonError.error==QJsonParseError::NoError){
        for(int i=0; i<jsonArray.size(); ++i){
            QJsonObject json=jsonArray.at(i).toObject();

            DataFile *file=new DataFile();
            file->id=json.value("_id").toString();
            file->name=json.value("name").toString();
            file->type=json.value("format").toString();
            file->dataTime=json.value("datatime").toString();
            file->size=json.value("size").toString();
            file->parentId=json.value("parentid").toString();

            listData.append(file);
        }
        return listData;
    }
    else{
        return listData;
    }
}
