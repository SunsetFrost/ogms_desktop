#include "ogmminitopwidget.h"

#include "OgmCommon/ogmuihelper.h"

OgmMiniTopWidget::OgmMiniTopWidget(QString widgetType, QWidget *parent)
    : QWidget(parent)
    ,_ui(new Ui::OgmMiniTopWidget)
{
    _ui->setupUi(this);
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);

    if(widgetType=="Task"){
        initTaskWidget();
    }
    else if(widgetType=="Server"){
        initServerWidget();
    }
}

void OgmMiniTopWidget::initTaskWidget()
{
    _ui->widgetMiniTopServer->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewTaskMiniTop, 0xf055, "new", 7);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnOpenTaskMiniTop, 0xf07c, "open", 7);

    connect(_ui->btnToRunMiniTop, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("ToRun");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "ToRun");
    });
    connect(_ui->btnRunningMiniTop, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("Running");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "Running");
    });
    connect(_ui->btnFinishMiniTop, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("Finish");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "Finish");
    });
    connect(_ui->btnPrepareMintop, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("Prepare");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "Prepare");
    });
}

void OgmMiniTopWidget::initServerWidget()
{
    _ui->widgetMiniTopTask->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewServer, 0xf055, "new", 7);

    connect(_ui->btnMiniTopModelServer, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("ModelServer");
        emit signalChangeServerList("ModelServer");
    });
    connect(_ui->btnMiniTopDataServer, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("DataServer");
        emit signalChangeServerList("DataServer");
    });
}

void OgmMiniTopWidget::taskBtnCheckStateManage(QString taskType)
{
    QList<QToolButton*> btnList=_ui->widgetMiniTopTask->findChildren<QToolButton*>();
    for(int i=0; i<btnList.count(); ++i){
            btnList[i]->setChecked(false);
    }
    _ui->btnMiniTopModelServer->setChecked(false);
    _ui->btnMiniTopDataServer->setChecked(false);

    if(taskType=="ToRun")
        _ui->btnToRunMiniTop->setChecked(true);
    else if(taskType=="Running")
        _ui->btnRunningMiniTop->setChecked(true);
    else if(taskType=="Finish")
        _ui->btnFinishMiniTop->setChecked(true);
    else if(taskType=="Prepare")
        _ui->btnPrepareMintop->setChecked(true);
    else if(taskType=="ModelServer")
        _ui->btnMiniTopModelServer->setChecked(true);
    else if(taskType=="DataServer")
        _ui->btnMiniTopDataServer->setChecked(true);
}












