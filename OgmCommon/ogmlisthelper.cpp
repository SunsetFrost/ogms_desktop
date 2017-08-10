#include "ogmlisthelper.h"

#include <QLabel>
#include <QToolButton>
#include <QLayout>
#include <QUuid>

#include "ogmuihelper.h"
#include "ogmsetting.h"
#include "ogmnetwork.h"

int OgmListHelper::pageAmount=20;

OgmListHelper::OgmListHelper()
{

}

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QList<LISTCHILD> itemList)
{
    QToolButton *item=new QToolButton(parent);
    item->setObjectName(itemName);
    item->setFixedHeight(35);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    item->setWindowTitle(itemStyle);
    item->setAccessibleDescription("btn");
    parent->layout()->addWidget(item);

    QHBoxLayout *layoutItem=new QHBoxLayout();
    layoutItem->setMargin(6);
    item->setLayout(layoutItem);

    for(int i=0; i<itemList.count(); ++i){
        addItemChildrenByItemStruct(item, itemList[i]);
    }
}

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTCHILD> itemList)
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

void OgmListHelper::addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTCHILD> itemList, bool checkable)
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

void OgmListHelper::addListItemNoResult(QWidget *parent, QString itemStyle, QString accessDes)
{
    QToolButton *item=new QToolButton(parent);
    item->setFixedHeight(35);
    item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    item->setWindowTitle(itemStyle);
    item->setAccessibleDescription(accessDes);
    parent->layout()->addWidget(item);

    QHBoxLayout *layoutItem=new QHBoxLayout();
    layoutItem->setMargin(6);
    item->setLayout(layoutItem);

    layoutItem->addStretch();

    QLabel *lbl=new QLabel(item);
    lbl->setText("No Result");
    lbl->setWindowTitle("lbl-lightdark-f18");
    layoutItem->addWidget(lbl);

    layoutItem->addStretch();
}

LISTCHILD OgmListHelper::createLableChild(QString style, int iconValue)
{
    LISTCHILD lbl;
    lbl.typeValue=ItemType::Label;
    lbl.styleName=style;
    lbl.iconValue=iconValue;

    return lbl;
}

LISTCHILD OgmListHelper::createLableChild(QString style, int width, QString text)
{
    LISTCHILD lbl;
    lbl.typeValue=ItemType::Label;
    lbl.styleName=style;
    lbl.textValue=text;
    lbl.fixWidth=width;
    lbl.iconValue=0;

    return lbl;
}

LISTCHILD OgmListHelper::createButtonChild(int iconValue, QString objectName, QString styleName, QString toolTip)
{
    LISTCHILD btn;
    btn.typeValue=ItemType::ToolButton;
    btn.iconValue=iconValue;
    btn.styleName=styleName;
    btn.toolTipValue=toolTip;
    btn.objectName=objectName;

    return btn;
}

LISTCHILD OgmListHelper::createSpaceChild()
{
    LISTCHILD space;
    space.typeValue=ItemType::SpaceItem;
    return space;
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

void OgmListHelper::addItemChildrenByItemStruct(QWidget *parent, LISTCHILD item)
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
        if(!item.toolTipValue.isEmpty()){
            lbl->setToolTip(item.toolTipValue);
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

QList<QVariant> OgmHelper::toVarList(QList<ModelService *> modelList)
{
    QList<QVariant> varList;
    for(int i=0; i<modelList.count(); ++i){
        QVariant var;
        var.setValue(modelList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataService *> dataList)
{
    QList<QVariant> varList;
    for(int i=0; i<dataList.count(); ++i){
        QVariant var;
        var.setValue(dataList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataMapping *> datamapList)
{
    QList<QVariant> varList;
    for(int i=0; i<datamapList.count(); ++i){
        QVariant var;
        var.setValue(datamapList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataRefactor *> refactorList)
{
    QList<QVariant> varList;
    for(int i=0; i<refactorList.count(); ++i){
        QVariant var;
        var.setValue(refactorList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataRefactorMethod *> methodList)
{
    QList<QVariant> varList;
    for(int i=0; i<methodList.count(); ++i){
        QVariant var;
        var.setValue(methodList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<ModelServer *> modelServerList)
{
    QList<QVariant> varList;
    for(int i=0; i<modelServerList.count(); ++i){
        QVariant var;
        var.setValue(modelServerList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataServer *> dataServerList)
{
    QList<QVariant> varList;
    for(int i=0; i<dataServerList.count(); ++i){
        QVariant var;
        var.setValue(dataServerList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<DataFile *> dataFileList)
{
    QList<QVariant> varList;
    for(int i=0; i<dataFileList.count(); ++i){
        QVariant var;
        var.setValue(dataFileList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<Favor *> favorList)
{
    QList<QVariant> varList;
    for(int i=0; i<favorList.count(); ++i){
        QVariant var;
        var.setValue(favorList[i]);
        varList.append(var);
    }
    return varList;
}

QList<QVariant> OgmHelper::toVarList(QList<Task *> taskList)
{
    QList<QVariant> varList;
    for(int i=0; i<taskList.count(); ++i){
        QVariant var;
        var.setValue(taskList[i]);
        varList.append(var);
    }
    return varList;
}

QString OgmHelper::getXmlStringByPath(QString filePath)
{
    QDomDocument doc;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    doc.setContent(&file);
    file.close();

    QString xml= doc.toString();
    return xml;
}

QString OgmHelper::getInitDiagramJson(QString modelId)
{
    QString strIp="http://"+OgmSetting::webDiagramIP+"/GeoModeling/diagramExpressionZBWServlet?uid="+modelId;

    QString result=QString::fromUtf8(OgmNetWork::get(strIp));

    return result;
}

QString OgmHelper::getElidedText(QString originalTxt, int width)
{
    QFont font(OgmUiHelper::g_fontName);

    QFontMetrics fontWidth(font);
    int txtWidth=fontWidth.width(originalTxt);
    if(txtWidth>width)
        originalTxt=fontWidth.elidedText(originalTxt, Qt::ElideRight, width);
    return originalTxt;
}





















