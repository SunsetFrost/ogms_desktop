#include "visualdal.h"
#include "OgmCommon/ogmsetting.h"

#include <QDir>

VisualDAL::VisualDAL()
{

}

QList<Visual *> VisualDAL::getAllVisual()
{
    QDir dir(OgmSetting::visualPath);
    dir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    QList<Visual*> visualList;

    QFileInfoList list=dir.entryInfoList();
    for(int i=0; i<list.size(); ++i){
        QFileInfo fileInfo=list.at(i);
        QString fileName=fileInfo.fileName();

        Visual *visual=getOneVisualById(fileName);
        visualList.append(visual);
    }

    return visualList;
}

Visual *VisualDAL::getOneVisualById(QString visualId)
{
    QDomDocument *doc=new QDomDocument();
    QString visualPath=OgmSetting::visualPath+"/"+visualId+"/DataVisualizationMethod.xml";
    QFile file(visualPath);
    file.open(QIODevice::ReadOnly);
    doc->setContent(&file);
    file.close();

    Visual *visual=new Visual();
    visual->id=visualId;
    xml2visual(doc, visual);
    return visual;
}

QString VisualDAL::getVisualSchema(QString visualId, QString schemaName)
{
    QString schemaPath=OgmSetting::visualPath+"/"+visualId+"/"+schemaName;
    QFile file(schemaPath);
    file.open(QIODevice::ReadOnly);
    QString result=QString::fromUtf8(file.readAll());
    return result;
}

void VisualDAL::xml2visual(QDomDocument *doc, Visual *visual)
{
    QDomElement eleVisual=doc->documentElement();
    //visual->id=eleVisual.attributeNode("id").value();

    QDomElement eleLocals=eleVisual.firstChildElement("Localizations");
    QDomNodeList nodeListLocal=eleLocals.childNodes();
    for(int i=0; i<nodeListLocal.count(); ++i){
        QDomElement eleLocal=nodeListLocal.at(i).toElement();
        QString local=eleLocal.attributeNode("local").value();
        if(local=="EN_US"){
            visual->name=eleLocal.attributeNode("localName").value();

            QDomElement eleAbstract=eleLocal.firstChildElement("Abstract");
            visual->desc=eleAbstract.text().trimmed();
        }
    }

    QDomElement eleFormats=eleVisual.firstChildElement("Params");
    QDomNodeList nodeListFormat=eleFormats.childNodes();

    QList<VisualFormat*> formatList;

    for(int i=0; i<nodeListFormat.size(); ++i){
        VisualFormat *format=new VisualFormat();
        format->name=nodeListFormat.at(i).toElement().attributeNode("name").value();

        QDomNodeList nodeListParam=nodeListFormat.at(i).childNodes();
        QList<VisualPrama*> paramList;
        for(int j=0; j<nodeListParam.size(); ++j){
            QDomElement eleParam=nodeListParam.at(j).toElement();

            VisualPrama *param=new VisualPrama();
            param->name=eleParam.attributeNode("name").value();
            param->type=eleParam.attributeNode("type").value();
            param->desc=eleParam.attributeNode("description").value();
            param->schema=eleParam.attributeNode("schema").value();

            paramList.append(param);
        }
        format->pramaList=paramList;
        formatList.append(format);
    }
    visual->formatList=formatList;
}


















