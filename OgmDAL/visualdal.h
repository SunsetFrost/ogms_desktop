#ifndef VISUALDAL_H
#define VISUALDAL_H

#include "OgmEntity/visual.h"

#include <QList>
#include <QDomDocument>

class VisualDAL
{
public:
    VisualDAL();

    QList<Visual*> getAllVisual();
    Visual* getOneVisualById(QString visualId);

    QString getVisualSchema(QString visualId, QString schemaName);

private:
    void xml2visual(QDomDocument *doc, Visual* visual);
};

#endif // VISUALDAL_H
