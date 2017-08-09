#include "ogmminitopwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"
#include "ogmpopwidget.h"

OgmMiniTopWidget::OgmMiniTopWidget(QString widgetType, QWidget *parent)
    : QWidget(parent)
    ,_ui(new Ui::OgmMiniTopWidget)
{
    _ui->setupUi(this);
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);

    _modelServerBLL=QSharedPointer<ModelServerBLL>(new ModelServerBLL);
    _dataServerBLL=QSharedPointer<DataServerBLL>(new DataServerBLL);

    if(widgetType=="Task"){
        initTaskWidget();
    }
    else if(widgetType=="Server"){
        initServerWidget();
    }
}

void OgmMiniTopWidget::changeServerType(QString serverType)
{
    taskBtnCheckStateManage(serverType);
    emit signalClearList();
    emit signalChangeServerList(serverType);
}

void OgmMiniTopWidget::changeTaskType(QString taskType)
{
    taskBtnCheckStateManage(taskType);

    emit signalClearList();
    QList<Task*> taskList=_taskBLL.data()->getAllTask();
    emit signalChangeTaskList(taskList, taskType);
}

void OgmMiniTopWidget::initTaskWidget()
{
    _ui->widgetMiniTopServer->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewTaskMiniTop, 0xf055, "Aggragation task", 7);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnOpenTaskMiniTop, 0xf07c, "Open task", 7);

    connect(_ui->btnToRunMiniTop, &QToolButton::clicked, [=](){
        emit signalSetListType("ToRun");
        emit signalClearList();

        taskBtnCheckStateManage("ToRun");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "ToRun");
    });
    connect(_ui->btnRunningMiniTop, &QToolButton::clicked, [=](){
        emit signalSetListType("Running");
        emit signalClearList();

        taskBtnCheckStateManage("Running");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "Running");
    });
    connect(_ui->btnFinishMiniTop, &QToolButton::clicked, [=](){
        emit signalSetListType("Finish");
        emit signalClearList();

        taskBtnCheckStateManage("Finish");
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        emit signalChangeTaskList(taskList, "Finish");
    });

    connect(_ui->btnNewTaskMiniTop, &QToolButton::clicked, [=](){
        emit signalSwitchPage("AggragationConfig");

    });
//    connect(_ui->btnPrepareMintop, &QToolButton::clicked, [=](){
//        taskBtnCheckStateManage("Prepare");
//        QList<Task*> taskList=_taskBLL.data()->getAllTask();
//        emit signalChangeTaskList(taskList, "Prepare");
//    });
}

void OgmMiniTopWidget::initServerWidget()
{
    _ui->widgetMiniTopTask->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewServer, 0xf055, "Connect", 7);

    connect(_ui->btnMiniTopModelServer, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("ModelServer");
        emit signalClearList();
        emit signalChangeServerList("ModelServer");
    });
    connect(_ui->btnMiniTopDataServer, &QToolButton::clicked, [=](){
        taskBtnCheckStateManage("DataServer");
        emit signalClearList();
        emit signalChangeServerList("DataServer");
    });
    connect(_ui->btnNewServer, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("NewServer");
        popWidget->show();

        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varResult){
            QStringList strList=varResult.toStringList();
            if(strList.at(2)=="ModelServer"){
                ModelServer *modelServer=new ModelServer();
                modelServer->ip=strList.at(0);
                modelServer->name=strList.at(1);
                modelServer->desc=strList.at(3);
                modelServer->location=strList.at(4);
                modelServer->id=OgmHelper::createUId();

                _modelServerBLL.data()->addServer(modelServer);

                //ui change
                taskBtnCheckStateManage("ModelServer");
                emit signalClearList();
                emit signalChangeServerList("ModelServer");
            }
            else if(strList.at(2)=="DataServer"){
                DataServer *dataServer=new DataServer();
                dataServer->ip=strList.at(0);
                dataServer->name=strList.at(1);
                dataServer->desc=strList.at(3);
                dataServer->id=OgmHelper::createUId();
                dataServer->location=strList.at(4);

                _dataServerBLL.data()->addServer(dataServer);

                //ui change
                taskBtnCheckStateManage("DataServer");
                emit signalClearList();
                emit signalChangeServerList("DataServer");
            }
        });
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
//    else if(taskType=="Prepare")
//        _ui->btnPrepareMintop->setChecked(true);
    else if(taskType=="ModelServer")
        _ui->btnMiniTopModelServer->setChecked(true);
    else if(taskType=="DataServer")
        _ui->btnMiniTopDataServer->setChecked(true);
}












