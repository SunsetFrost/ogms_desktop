#ifndef OGMCONFIGTASKWIDGET_H
#define OGMCONFIGTASKWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include <OgmCommon/ogmwidget.h>
#include "OgmBLL/taskbll.h"

#include "ui_ogmdataserviceconfig.h"


namespace Ui{
class DataMapTaskConfigUI;
}

class OgmConfigTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmConfigTaskWidget(QString taskType, QWidget *parent = 0);

    void changeDataMapTask(QString serverId, QString dataMapId);

private:
    void initDataMapTaskConfig();

    bool isTaskInfoComplete();

    void uiInfo2task();

    void saveTask();

    void chooseFile();

private:
    Ui::DataMapTaskConfigUI *_uiDataMap;

    Task *_task;

    QSharedPointer<TaskBLL> _taskBLL;

signals:
    void signalSwitchPage(QString pageType);
};

#endif // OGMCONFIGTASKWIDGET_H
