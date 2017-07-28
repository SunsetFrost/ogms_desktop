#include "ogmminitopwidget.h"

#include "OgmCommon/ogmuihelper.h"

OgmMiniTopWidget::OgmMiniTopWidget(QString widgetType, QWidget *parent)
    : QWidget(parent)
    ,_ui(new Ui::OgmMiniTopWidget)
    ,_widgetType(widgetType)
{
    _ui->setupUi(this);
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);

    initWidget();
}

void OgmMiniTopWidget::initWidget()
{
    //style


    if(_widgetType=="Task"){

        OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewTaskMiniTop, 0xf055, "new", 7);
        OgmUiHelper::Instance()->setButtonIcon(_ui->btnOpenTaskMiniTop, 0xf07c, "open", 7);

        connect(_ui->btnToRunMiniTop, &QToolButton::clicked, [=](){
            QList<Task*> taskList=_taskBLL.data()->getAllTask();
            emit signalChangeTaskList(taskList, "ToRun");
        });
        connect(_ui->btnRunningMiniTop, &QToolButton::clicked, [=](){
            QList<Task*> taskList=_taskBLL.data()->getAllTask();
            emit signalChangeTaskList(taskList, "Running");
        });
        connect(_ui->btnFinishMiniTop, &QToolButton::clicked, [=](){
            QList<Task*> taskList=_taskBLL.data()->getAllTask();
            emit signalChangeTaskList(taskList, "Finish");
        });
        connect(_ui->btnPrepareMintop, &QToolButton::clicked, [=](){
            QList<Task*> taskList=_taskBLL.data()->getAllTask();
            emit signalChangeTaskList(taskList, "Prepare");
        });
    }
}
