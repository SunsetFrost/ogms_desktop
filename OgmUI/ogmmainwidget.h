#ifndef OGMMAINWIDGET_H
#define OGMMAINWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QScrollArea>

#include "OgmCommon/ogmwidget.h"

#include "OgmUI/ogmlistwidget.h"
#include "OgmUI/ogmservertopwidget.h"
#include "OgmUI/ogmserversidebarwidget.h"
#include "OgmUI/ogmfavorsidebarwidget.h"
#include "OgmUI/ogmminitopwidget.h"
#include "OgmUI/ogmconfigtaskwidget.h"

namespace Ui {
class OgmMainWidget;
}

class OgmMainWidget : public OgmWidget
{
    Q_OBJECT

public:
    explicit OgmMainWidget(QWidget *parent = 0);
    ~OgmMainWidget();

private:
    //init text and icon
    void initStyle();

    void initFunction();

    void initChildWidget();

    void btnSideBarClicked();

    void switchPage(QString type);

private:
    Ui::OgmMainWidget *_ui;

    QScrollArea *_scrollArea;
    OgmListWidget *_widgetList;

    OgmServerTopWidget *_widgetDataServerTop;
    OgmServerTopWidget *_widgetModelServerTop;
    OgmServerTopWidget *_widgetFileServerTop;
    OgmServerTopWidget *_widgetFavorTop;

    OgmMiniTopWidget *_widgetTaskTop;

    OgmServerSidebarWidget *_widgetServerSidebar;
    OgmFavorSidebarWidget *_widgetFavorSidebar;

    OgmConfigTaskWidget *_widgetDataMapTaskConfig;

    QSharedPointer<FavorBLL> _favorBLL;
    QSharedPointer<TaskBLL> _taskBLL;
};

#endif // OGMMAINWIDGET_H