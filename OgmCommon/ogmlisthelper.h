#ifndef OGMLISTHELPER_H
#define OGMLISTHELPER_H

#include <QWidget>

enum ItemType{
    Label=0,
    ToolButton=1,
    SpaceItem,
    ToolButtonWithText
};

struct LISTITEM{
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
    QList<LISTITEM> listItemList;
};

class OgmHelper
{
public:
    static QString createUId();
};

class OgmListHelper
{
public:
    OgmListHelper();

    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QList<LISTITEM> itemList);

    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTITEM> itemList);

    static void addListItem(QWidget *parent, QString itemName, QString itemStyle, QString accessDes, QList<LISTITEM> itemList, bool checkable);

    static void addInfoItem(QWidget *parent, QString itemName, QString itemStyle, QList<INFOITEM> infoList);

private:
    static void addItemChildrenByItemStruct(QWidget *parent, LISTITEM item);
};

#endif // OGMLISTHELPER_H
