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

    static QString modelServerFilePath;
    static QString dataServerFilePath;

    static QString webDiagramIP;
    static QString webDiagramPath;

    static QString urlAggragationNewSolution;
    static QString urlAggragationQuerySolution;
    static QString urlAggragationQueryTask;
};

#endif // OGMSETTING_H
