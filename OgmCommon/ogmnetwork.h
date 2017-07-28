#ifndef OGMNETWORK_H
#define OGMNETWORK_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>

class OgmNetWork
{
public:
    OgmNetWork();

    static QByteArray get(QString request);

    static QByteArray postDataFile(QString request, QString filePath, QString parentId);
};

#endif // OGMNETWORK_H
