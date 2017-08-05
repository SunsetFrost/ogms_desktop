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
                modelServer->id=OgmHelper::createUId();

                _modelServerBLL.data()->addServer(modelServer);
                emit signalChangeServerList("ModelServer");
            }
            else if(strList.at(2)=="DataServer"){
                DataServer *dataServer=new DataServer();
                dataServer->ip=strList.at(0);
                dataServer->name=strList.at(1);
                dataServer->desc=strList.at(3);
                dataServer->id=OgmHelper::createUId();

                _dataServerBLL.data()->addServer(dataServer);
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
    else if(taskType=="Prepare")
        _ui->btnPrepareMintop->setChecked(true);
    else if(taskType=="ModelServer")
        _ui->btnMiniTopModelServer->setChecked(true);
    else if(taskType=="DataServer")
        _ui->btnMiniTopDataServer->setChecked(true);
}












