#include "favordal.h"

#include <QFile>
#include <QTextStream>
#include <QDir>


QString FavorDAL::favorFilePath=QDir::currentPath()+"/user.config";

FavorDAL::FavorDAL()
{

}

Favor *FavorDAL::getFavorById(QString favorId)
{
    QList<Favor*> favorList=getAllFavor();
    for(int i=0; i<favorList.count(); ++i){
        if(favorList.at(i)->id==favorId){
            return favorList.at(i);
        }
    }
    Favor *favor=NULL;
    return favor;
}

QList<Favor *> FavorDAL::getAllFavor()
{
    QDomDocument doc;
    QFile file(favorFilePath);
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();

    QList<Favor*> favorList;
    xml2favorList(doc, favorList);

    return favorList;
}

void FavorDAL::addOneFavor(Favor *favor)
{
    QList<Favor*> favorList=getAllFavor();
    favorList.append(favor);
    setAllFavor(favorList);
}

bool FavorDAL::deleteOneFavor(Favor *favor)
{
    QList<Favor*> favorList=getAllFavor();
    for(int i=0; i<favorList.count(); ++i){
        if(favorList.at(i)->id==favor->id){
            favorList.removeAt(i);
            setAllFavor(favorList);
            return true;
        }
    }
    return false;
}

bool FavorDAL::addOneServiceToOneFavor(SERVICEITEM service, Favor *favor)
{
    QList<Favor*> favorList=getAllFavor();
    for(int i=0; i<favorList.count(); ++i){
        if(favorList[i]->id==favor->id){
            favorList[i]->serviceList.append(service);
            setAllFavor(favorList);
            return true;
        }
    }
    return false;
}

void FavorDAL::setAllFavor(QList<Favor *> favorList)
{
    QFile file(favorFilePath);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    QDomDocument doc;
    favorList2xml(favorList, doc);
    doc.save(out, 4);
}

void FavorDAL::favorList2xml(QList<Favor *> &favorList, QDomDocument &doc)
{
    QDomAttr attr;

    QDomElement elementConfig=doc.createElement("User");
    doc.appendChild(elementConfig);

    QDomElement elementModelConfig=doc.createElement("Favors");
    elementConfig.appendChild(elementModelConfig);

    for(int i=0; i<favorList.count(); ++i){
        QDomElement elementGroup=doc.createElement("Favor");
        attr=doc.createAttribute("name");
        attr.setValue(favorList.at(i)->name);
        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("id");
        attr.setValue(favorList.at(i)->id);
        elementGroup.setAttributeNode(attr);

//        attr=doc.createAttribute("type");
//        attr.setValue(favorList.at(i).type);
//        elementGroup.setAttributeNode(attr);

        attr=doc.createAttribute("des");
        attr.setValue(favorList.at(i)->des);
        elementGroup.setAttributeNode(attr);

        for(int j=0; j<favorList.at(i)->serviceList.count(); ++j){
            QDomElement elementModel=doc.createElement("Service");

            attr=doc.createAttribute("serverId");
            attr.setValue(favorList.at(i)->serviceList.at(j).serverId);
            elementModel.setAttributeNode(attr);

            attr=doc.createAttribute("serviceId");
            attr.setValue(favorList.at(i)->serviceList.at(j).serviceId);
            elementModel.setAttributeNode(attr);

            attr=doc.createAttribute("serviceType");
                attr.setValue(favorList.at(i)->serviceList.at(j).serviceType);

            elementModel.setAttributeNode(attr);

            elementGroup.appendChild(elementModel);
        }
        elementModelConfig.appendChild(elementGroup);
    }
}

void FavorDAL::xml2favorList(QDomDocument &doc, QList<Favor *> &favorList)
{
    QDomElement elementConfig=doc.documentElement();
    QDomElement elementModelConfig=elementConfig.firstChildElement();
    QDomNodeList nodeListGroup=elementModelConfig.childNodes();
    for(int i=0; i<nodeListGroup.count(); ++i){
        QDomNode nodeGroup=nodeListGroup.item(i);
        QDomElement elementGroup=nodeGroup.toElement();

        Favor *modelGroup=new Favor();
        modelGroup->id=elementGroup.attributeNode("id").value();
        modelGroup->name=elementGroup.attributeNode("name").value();
        //modelGroup.type=elementGroup.attributeNode("type").value();
        modelGroup->des=elementGroup.attributeNode("des").value();

        QList<SERVICEITEM> msList;

        QDomNodeList nodeListModel=elementGroup.childNodes();
        for(int j=0; j<nodeListModel.count(); ++j){
            QDomNode nodeModel=nodeListModel.item(j);
            QDomElement elementModel=nodeModel.toElement();

            SERVICEITEM serviceItem;

            QString serverId=elementModel.attributeNode("serverId").value();
            QString modelId=elementModel.attributeNode("serviceId").value();
            QString serviceType=elementModel.attributeNode("serviceType").value();

            serviceItem.serverId=serverId;
            serviceItem.serviceId=modelId;
            serviceItem.serviceType=serviceType;

            msList.append(serviceItem);
        }
        modelGroup->serviceList=msList;
        favorList.append(modelGroup);
    }
}
