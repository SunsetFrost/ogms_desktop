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

    static QString udxToolPath;
    static QString omsToolPath;
};

#endif // OGMSETTING_H
