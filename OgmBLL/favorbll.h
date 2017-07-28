#ifndef FAVORBLL_H
#define FAVORBLL_H

#include "OgmDAL/favordal.h"
#include "OgmDAL/modeldal.h"
#include "OgmDAL/datadal.h"

#include <QSharedPointer>

class FavorBLL
{
public:
    FavorBLL();

    Favor* getFavorGroupById(QString favorId);

    QList<Favor*> getAllFavorGroup();

    void addOneFavorGroup(Favor *favor);

    bool deleteOneFavorGroup(Favor *favor);

    bool addOneFavorService(SERVICEITEM service, QString favorId);
    //trans
    QList<ModelService*> favor2modelServiceList(Favor *favor);

    QList<DataService*> favor2dataServiceList(Favor *favor);

    QList<DataMapping*> favor2dataMappingList(Favor *favor);

    QList<DataRefactor*> favor2dataRefactorList(Favor *favor);


private:
    QSharedPointer<FavorDAL> _favorDAL;

    QSharedPointer<ModelServerDAL> _modelServerDAL;
    QSharedPointer<ModelServiceDAL> _modelServiceDAL;

    QSharedPointer<DataServerDAL> _dataServerDAL;
    QSharedPointer<DataServiceDAL> _dataServiceDAL;
    QSharedPointer<DataMappingDAL> _dataMappingDAL;
    QSharedPointer<DataRefactorDAL> _dataRefactorDAL;
};

#endif // FAVORBLL_H
