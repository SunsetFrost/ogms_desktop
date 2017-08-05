#ifndef FAVORDAL_H
#define FAVORDAL_H

#include "OgmEntity/favor.h"
#include "OgmEntity/model.h"
#include "OgmEntity/data.h"

#include <QString>
#include <QDomDocument>

class FavorDAL
{
public:
    FavorDAL();

    static QString favorFilePath;

    Favor* getFavorById(QString favorId);

    QList<Favor*> getAllFavor();

    //void setFavorFile(QList<NjFavor> favorList);

    void addOneFavor(Favor *favor);

    bool deleteOneFavor(Favor *favor);

    bool addOneServiceToOneFavor(SERVICEITEM service, Favor *favor);

    bool deleteOneServiceInOneFavorGroup(SERVICEITEM service, Favor *favor);

private:
    void setAllFavor(QList<Favor*> favorList);

    void favorList2xml(QList<Favor*> &favorList, QDomDocument &doc);

    void xml2favorList(QDomDocument &doc, QList<Favor*> &favorList);
};

#endif // FAVORDAL_H
