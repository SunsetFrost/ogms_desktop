#ifndef OGMCONFIGTASKWIDGET_H
#define OGMCONFIGTASKWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QWebEngineView>

#include <OgmCommon/ogmwidget.h>
#include "OgmBLL/taskbll.h"
#include "OgmBLL/databll.h"

#include "ui_ogmdataserviceconfig.h"
#include "ui_ogmrefactortaskconfigui.h"
#include "ui_ogmtaskmodelconfigui.h"

namespace Ui{
class DataMapTaskConfigUI;
class DataRefactorTaskConfigUI;
class TaskConfigModelUI;
}

class OgmConfigTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmConfigTaskWidget(QString taskType, QWidget *parent = 0);

    void changeDataMapTaskByService(QString serverId, QString dataMapId);
    void changeDataMapTaskByTask(Task *task);

    void changeDataRefactorTask(QString serverId, QString dataRefactorId, QString methodName);
    void changeDataRefactorTaskByTask(Task *task);

    void changeModelTask(QString serverId, QString modelId);
    void changeModelTaskByTask(Task *task);

    void initAggregationConfig();

private:
    void initDataMapTaskConfig();
    void initDataRefctorTaskConfig();
    void initModelTaskConfig();


    void changeMethodParamUI(DataRefactorMethodParam *param, TASKREFACTORPARAM taskParam);

    //btn
    void saveTask();

    void chooseFile();

    void configModelData();



private:
    Ui::DataMapTaskConfigUI *_uiDataMap;
    Ui::DataRefactorTaskConfigUI *_uiDataRefactor;
    Ui::TaskConfigModelUI *_uiModel;
    QWebEngineView *_webView;

    QString _serverId;
    QString _taskType;
    QString _paramIndex;
    QString _refactorId;

    Task *_task;

    QSharedPointer<TaskBLL> _taskBLL;
    QSharedPointer<DataRefactorBLL> _dataRefactorBLL;

signals:
    void signalSwitchPage(QString pageType);
};

#endif // OGMCONFIGTASKWIDGET_H
