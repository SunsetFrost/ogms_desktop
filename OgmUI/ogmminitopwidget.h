#ifndef OGMMINITOPWIDGET_H
#define OGMMINITOPWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include "ui_ogmminitopwidget.h"
#include "OgmBLL/taskbll.h"
#include "OgmBLL/modelbll.h"
#include "OgmBLL/databll.h"

namespace Ui{
class OgmMiniTopWidget;
}

class OgmMiniTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmMiniTopWidget(QString widgetType, QWidget *parent = 0);

    void changeServerType(QString serverType);

    void changeTaskType(QString taskType);

public:

private:
    void initTaskWidget();

    void initServerWidget();

    void taskBtnCheckStateManage(QString taskType);

private:
    Ui::OgmMiniTopWidget *_ui;

    QSharedPointer<TaskBLL> _taskBLL;
    QSharedPointer<ModelServerBLL> _modelServerBLL;
    QSharedPointer<DataServerBLL> _dataServerBLL;

signals:
    void signalChangeTaskList(QList<Task*> taskList, QString taskRunState);
    void signalChangeServerList(QString serverType);
    void signalClearList();
    void signalSetListType(QString taskType);
    void signalSwitchPage(QString pageType);
};

#endif // OGMMINITOPWIDGET_H
