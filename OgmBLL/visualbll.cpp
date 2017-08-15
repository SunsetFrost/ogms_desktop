#include "visualbll.h"

VisualBLL::VisualBLL()
{
    _visualDAL=QSharedPointer<VisualDAL>(new VisualDAL);
}

QList<Visual *> VisualBLL::getAllVisual()
{
    return _visualDAL.data()->getAllVisual();
}

Visual *VisualBLL::getVisualById(QString id)
{
    return _visualDAL.data()->getOneVisualById(id);
}

QString VisualBLL::getVisualSchema(Visual *visual, int formatIndex, int paramIndex)
{
    QString schemaName=visual->formatList.at(formatIndex)->pramaList.at(paramIndex)->schema;
    QString schema=_visualDAL.data()->getVisualSchema(visual->id, schemaName);
    return schema;
}

QString VisualBLL::getVisualUrl(Visual *visual, int formatIndex)
{
    QString url="http://localhost:24689/visualization/"+visual->id+"/index.html?index="+QString::number(formatIndex);
    for(int i=0; i<visual->formatList.at(formatIndex)->pramaList.count(); ++i){
        url.append("&filename"+QString::number(i+1)+"=/files?id="+visual->formatList.at(formatIndex)->pramaList.at(i)->fileId);
    }
    return url;
}
