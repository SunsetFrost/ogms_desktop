#ifndef VISUALBLL_H
#define VISUALBLL_H

#include "OgmDAL/visualdal.h"

#include <QSharedPointer>

class VisualBLL
{
public:
    VisualBLL();

    QList<Visual*> getAllVisual();
    Visual* getVisualById(QString id);
    QString getVisualSchema(Visual *visual, int formatIndex, int paramIndex);

    QString getVisualUrl(Visual *visual, int formatIndex);

private:
    QSharedPointer<VisualDAL> _visualDAL;
};

#endif // VISUALBLL_H
