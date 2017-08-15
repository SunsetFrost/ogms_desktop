#ifndef OGMCONFIGTASKWIDGET_H
#define OGMCONFIGTASKWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QWebEngineView>

#include <OgmCommon/ogmwidget.h>
#include "OgmBLL/taskbll.h"
#include "OgmBLL/databll.h"
#include "OgmBLL/visualbll.h"
#include "OgmBLL/filebll.h"

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

    void changeVisual(Visual *visual, int formatIndex);

    void changeAggregationConfig(QString url);



private:
    void initDataMapTaskConfig();
    void initDataRefctorTaskConfig();
    void initModelTaskConfig();
    void initVisualConfig();
    void initAggregationConfig();


    void changeMethodParamUI(DataRefactorMethodParam *param, TASKREFACTORPARAM taskParam);

    //btn
    void saveTask();

    void chooseFile();

    void configModelData();



private:
    Ui::DataMapTaskConfigUI *_uiDataMap;
    Ui::DataRefactorTaskConfigUI *_uiDataRefactor;
    Ui::TaskConfigModelUI *_uiModel;
    Ui::DataRefactorTaskConfigUI *_uiVisual;

    QWebEngineView *_webView;

    Task *_task;
    QString _serverId;
    QString _taskType;
    QString _paramIndex;
    QString _refactorId;

    Visual *_visual;
    int _visualFormatIndex;
    int _visualParamIndex;

    QSharedPointer<TaskBLL> _taskBLL;
    QSharedPointer<DataRefactorBLL> _dataRefactorBLL;
    QSharedPointer<DataFileBll> _fileDataBll;
    QSharedPointer<VisualBLL> _visualBLL;

signals:
    void signalSwitchPage(QString pageType);
    void signalGoVisual(QString visualUrl);
    void signalChangeVisualFormatSidebar(Visual *visual);
};

#endif // OGMCONFIGTASKWIDGET_H
