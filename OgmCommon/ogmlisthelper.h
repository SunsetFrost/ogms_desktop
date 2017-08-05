#ifndef OGMLISTHELPER_H
#define OGMLISTHELPER_H

#include <QWidget>
#include <QDomDocument>

#include <OgmEntity/data.h>
#include <OgmEntity/model.h>
#include <OgmEntity/favor.h>
#include <OgmEntity/file.h>
#include <OgmEntity/task.h>



class OgmHelper
{
public:    
    static QString createUId();

    //convert
    static QList<QVariant> toVarList(QList<ModelService*> modelList);

    static QList<QVariant> toVarList(QList<DataService *> dataList);
    static QList<QVariant> toVarList(QList<DataMapping *> datamapList);
    static QList<QVariant> toVarList(QList<DataRefactor *> refactorList);
    static QList<QVariant> toVarList(QList<DataRefactorMethod*> methodList);

    static QList<QVariant> toVarList(QList<ModelServer *> modelServerList);
    static QList<QVariant> toVarList(QList<DataServer *> dataServerList);

    static QList<QVariant> toVarList(QList<DataFile*> dataFileList);

    static QList<QVariant> toVarList(QList<Favor*> favorList);

    static QList<QVariant> toVarList(QList<Task*> taskList);

    //xml
    static QString getXmlStringByPath(QString filePath);

};

////////////////////////////////////////////////////////////////////
/// \brief The OgmListHelper class
///make build list item easy
enum ItemType{
    Label=0,
    ToolButton=1,
    SpaceItem,
    ToolButtonWithText
};

struct LISTCHILD{
    QString objectName;
    QString styleName;
    int iconValue;
    QString toolTipValue;
    QString textValue;
    ItemType typeValue;
    int fixWidth;
    QString alignment;
    bool isCursorChange=false;
};

struct INFOITEM{
    QString itemName;
    QList<LISTCHILD> listItemList;
};

class OgmListHelper
{
public:
    OgmListHelper();

    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QList<LISTCHILD> itemList);
    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTCHILD> itemList);
    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTCHILD> itemList, bool checkable);

    static LISTCHILD createLableChild(QString style, int iconValue);
    static LISTCHILD createLableChild(QString style, int width, QString text);
    static LISTCHILD createButtonChild(int iconValue, QString objectName, QString styleName, QString toolTip);
    static LISTCHILD createSpaceChild();

    static void addInfoItem(QWidget *parent, QString itemName, QString itemStyle, QList<INFOITEM> infoList);

    static int pageAmount;

private:
    static void addItemChildrenByItemStruct(QWidget *parent, LISTCHILD item);
};

#endif // OGMLISTHELPER_H
