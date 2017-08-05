#ifndef OGMSETTING_H
#define OGMSETTING_H

#include <QString>
#include <QDir>

class OgmSetting
{
public:
    OgmSetting();

    static QString defaultModelServerId;
    static QString defaultDataServerId;
    static QString defaultFavorId;

    static QString udxDataPath;
    static QString udxSchemaPath;
    static QString omsToolPath;

    static QString serverFilePath;
};

#endif // OGMSETTING_H
