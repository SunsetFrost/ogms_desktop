#include "ogmlisthelper.h"

#include <QLabel>
#include <QToolButton>
#include <QLayout>
#include <QUuid>

#include "ogmuihelper.h"

OgmListHelper::OgmListHelper()
{

}

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QList<LISTITEM> itemList)
{
    QToolButton *item=new QToolButton(parent);
    item->setObjectName(itemName);
    item->setFixedHeight(35);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    item->setWindowTitle(itemStyle);
    parent->layout()->addWidget(item);

    QHBoxLayout *layoutItem=new QHBoxLayout();
    layoutItem->setMargin(6);
    item->setLayout(layoutItem);

    for(int i=0; i<itemList.count(); ++i){
        addItemChildrenByItemStruct(item, itemList[i]);
    }
}

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTITEM> itemList)
{
    QToolButton *item=new QToolButton(parent);
    item->setObjectName(itemName);
    item->setFixedHeight(35);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    item->setWindowTitle(itemStyle);
    item->setAccessibleDescription(accessDes);
    parent->layout()->addWidget(item);

    QHBoxLayout *layoutItem=new QHBoxLayout();
    layoutItem->setMargin(6);
    item->setLayout(layoutItem);

    for(int i=0; i<itemList.count(); ++i){
        addItemChildrenByItemStruct(item, itemList[i]);
    }
}

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTITEM> itemList, bool checkable)
{
    QToolButton *item=new QToolButton(parent);
    item->setObjectName(itemName);
    item->setFixedHeight(35);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    item->setWindowTitle(itemStyle);
    item->setAccessibleDescription(accessDes);
    if(checkable){
        item->setCheckable(true);
    }
    else{
        item->setCheckable(false);
    }
    parent->layout()->addWidget(item);

    QHBoxLayout *layoutItem=new QHBoxLayout();
    layoutItem->setMargin(6);
    item->setLayout(layoutItem);

    for(int i=0; i<itemList.count(); ++i){
        addItemChildrenByItemStruct(item, itemList[i]);
    }
}

void OgmListHelper::addInfoItem(QWidget *parent, QString itemName, QString itemStyle, QList<INFOITEM> infoList)
{
    parent->setHidden(true);

    QHBoxLayout *layoutTop=new QHBoxLayout();
    layoutTop->setSpacing(30);
    parent->setLayout(layoutTop);

    QVBoxLayout *layoutIcon=new QVBoxLayout();
    layoutIcon->setMargin(0);
    layoutTop->addLayout(layoutIcon);

    QLabel *lblPic=new QLabel();
    if(itemName=="data")
        OgmUiHelper::Instance()->setIcon(lblPic, QChar(0xf1c0));
    lblPic->setWindowTitle(itemStyle);
    lblPic->setFixedSize(180, 180);
    lblPic->setAlignment(Qt::AlignCenter);
    layoutIcon->addWidget(lblPic);

    layoutIcon->addStretch();

    QVBoxLayout *layoutInfo=new QVBoxLayout();
    layoutInfo->setSpacing(18);
    layoutTop->addLayout(layoutInfo);

    for(int i=0; i<infoList.count(); ++i){
        QWidget *widgetInfoItem=new QWidget();
        layoutInfo->addWidget(widgetInfoItem);

        QHBoxLayout *layoutList=new QHBoxLayout();
        layoutList->setSpacing(4);
        widgetInfoItem->setLayout(layoutList);

        for(int j=0; j<infoList[i].listItemList.count(); ++j){
            addItemChildrenByItemStruct(widgetInfoItem, infoList[i].listItemList[j]);
        }
    }
}

void OgmListHelper::addItemChildrenByItemStruct(QWidget *parent, LISTITEM item)
{
    if(item.typeValue==ItemType::Label){
        QLabel *lbl=new QLabel(parent);

        if(!item.objectName.isEmpty())
            lbl->setObjectName(item.objectName);
        if(!item.textValue.isEmpty())
            lbl->setText(item.textValue);
        if(!item.styleName.isEmpty())
            lbl->setWindowTitle(item.styleName);
        if(item.iconValue)
            OgmUiHelper::Instance()->setIcon(lbl, QChar(item.iconValue));
        if(item.fixWidth)
            lbl->setFixedWidth(item.fixWidth);
        if(!item.alignment.isEmpty()){
            if(item.alignment=="center")
                lbl->setAlignment(Qt::AlignCenter);
        }

        parent->layout()->addWidget(lbl);
    }
    else if(item.typeValue==ItemType::ToolButton){
        QToolButton *btn=new QToolButton(parent);
        if(!item.objectName.isEmpty())
            btn->setObjectName(item.objectName);
        if(item.iconValue)
            OgmUiHelper::Instance()->setIcon(btn, QChar(item.iconValue));
        if(!item.styleName.isEmpty())
            btn->setWindowTitle(item.styleName);
        if(item.isCursorChange){
            btn->setCursor(Qt::PointingHandCursor);
        }
        if(!item.toolTipValue.isEmpty())
            btn->setToolTip(item.toolTipValue);

        parent->layout()->addWidget(btn);
    }
    else if(item.typeValue==ItemType::ToolButtonWithText){
        QToolButton *btn=new QToolButton(parent);

        if(!item.objectName.isEmpty())
            btn->setObjectName(item.objectName);
        if(item.iconValue && !item.textValue.isEmpty())
            OgmUiHelper::Instance()->setButtonIcon(btn, item.iconValue, item.textValue, 0);
        if(!item.styleName.isEmpty())
            btn->setWindowTitle(item.styleName);
        if(item.fixWidth){
            btn->setFixedWidth(item.fixWidth);
        }
        if(item.isCursorChange){
            btn->setCursor(Qt::PointingHandCursor);
        }
        if(!item.toolTipValue.isEmpty())
            btn->setToolTip(item.toolTipValue);

        parent->layout()->addWidget(btn);
    }

    else if(item.typeValue==ItemType::SpaceItem){
        QHBoxLayout *layoutParent=qobject_cast<QHBoxLayout*>(parent->layout());
        layoutParent->addStretch();
    }
}

QString OgmHelper::createUId()
{
    QUuid uId=QUuid::createUuid();
    QString strUId=uId.toString();
    strUId=strUId.remove("{");
    strUId=strUId.remove("}");
    return strUId;
}
