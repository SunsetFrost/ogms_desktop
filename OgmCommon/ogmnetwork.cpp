#include "ogmnetwork.h"

#include <QFile>

OgmNetWork::OgmNetWork()
{

}

QByteArray OgmNetWork::get(QString request)
{
    QNetworkAccessManager net;
    QEventLoop eventLoop;

    QNetworkReply *reply=net.get(QNetworkRequest(request));
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);

    eventLoop.exec();

    return reply->readAll();
}

QByteArray OgmNetWork::postDataFile(QString request, QString filePath, QString parentId)
{
    //header
    QByteArray data;
    QString crlf="\r\n";
    QString b=QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();
    QString boundary="---------------------------"+b;
    QString endBoundary=crlf+"--"+boundary+"--"+crlf;
    QString contentType="multipart/form-data; boundary="+boundary;
    boundary="--"+boundary+crlf;
    QByteArray bond=boundary.toUtf8();

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    QStringList fileName=file.fileName().split("/");
    QString fileNameWithoutPath=fileName.at(fileName.count()-1);


    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"parentid\""+crlf).toUtf8());
    data.append(QString("Content-Transfer-Encoding: 8bit"+crlf).toUtf8());
    data.append(crlf.toUtf8());
    data.append(QString(parentId).toUtf8());

    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"files\" ;  filename=\""+QString(fileNameWithoutPath+"\""+crlf).toUtf8()));
    data.append("Content-Type:application/xml""\r\n\r\n");
    data.append(crlf.toUtf8());
    data.append(file.readAll());
    data.append(endBoundary.toUtf8());

    file.close();

    QNetworkAccessManager net;
    QNetworkRequest netRequest;
    netRequest.setUrl(QUrl(request));
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QNetworkReply *reply=net.post(netRequest, data);
    QEventLoop eventLoop;

    //config event loop
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    //result data
    QByteArray result=reply->readAll();

    return result;
}

QByteArray OgmNetWork::postDataFile(QString request, QString fileStream, QString fileName, QString parentId)
{
    //header
    QByteArray data;
    QString crlf="\r\n";
    QString b=QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();
    QString boundary="---------------------------"+b;
    QString endBoundary=crlf+"--"+boundary+"--"+crlf;
    QString contentType="multipart/form-data; boundary="+boundary;
    boundary="--"+boundary+crlf;
    QByteArray bond=boundary.toUtf8();

//    QFile file(filePath);
//    file.open(QIODevice::ReadOnly);

//    QStringList fileName=file.fileName().split("/");
//    QString fileNameWithoutPath=fileName.at(fileName.count()-1);


    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"parentid\""+crlf).toUtf8());
    data.append(QString("Content-Transfer-Encoding: 8bit"+crlf).toUtf8());
    data.append(crlf.toUtf8());
    data.append(QString(parentId).toUtf8());

    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"files\" ;  filename=\""+QString(fileName+"\""+crlf).toUtf8()));
    data.append("Content-Type:application/xml""\r\n\r\n");
    data.append(crlf.toUtf8());
    data.append(fileStream.toUtf8());
    data.append(endBoundary.toUtf8());

//    file.close();

    QNetworkAccessManager net;
    QNetworkRequest netRequest;
    netRequest.setUrl(QUrl(request));
    netRequest.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QNetworkReply *reply=net.post(netRequest, data);
    QEventLoop eventLoop;

    //config event loop
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    //result data
    QByteArray result=reply->readAll();

    return result;
}
