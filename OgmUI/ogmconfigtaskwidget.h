#ifndef OGMCONFIGTASKWIDGET_H
#define OGMCONFIGTASKWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include <OgmCommon/ogmwidget.h>
#include "OgmBLL/taskbll.h"
#include "OgmBLL/databll.h"

#include "ui_ogmdataserviceconfig.h"
#include "ui_ogmrefactortaskconfigui.h"

namespace Ui{
class DataMapTaskConfigUI;
class DataRefactorTaskConfigUI;
}

class OgmConfigTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmConfigTaskWidget(QString taskType, QWidget *parent = 0);

    void changeDataMapTask(QString serverId, QString dataMapId);

    void changeDataRefactorTask(QString serverId, QString dataRefactorId, QString methodName);

private:
    void initDataMapTaskConfig();

    void initDataRefctorTaskConfig();

    bool isTaskInfoComplete();

    void uiInfo2task();

    void saveTask();

    void chooseFile();

    void changeMethodParamUI(DataRefactorMethodParam *param);

private:
    Ui::DataMapTaskConfigUI *_uiDataMap;
    Ui::DataRefactorTaskConfigUI *_uiDataRefactor;
    QString _taskType;
    QString _paramIndex;

    Task *_task;

    QSharedPointer<TaskBLL> _taskBLL;
    QSharedPointer<DataRefactorBLL> _dataRefactorBLL;

signals:
    void signalSwitchPage(QString pageType);
};

#endif // OGMCONFIGTASKWIDGET_H
