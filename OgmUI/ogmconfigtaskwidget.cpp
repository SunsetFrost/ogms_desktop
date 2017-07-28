#include "ogmconfigtaskwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"
#include "OgmUI/ogmpopwidget.h"

#include <QDateTime>

OgmConfigTaskWidget::OgmConfigTaskWidget(QString taskType, QWidget *parent)
    : QWidget(parent)
{
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);

    _task=new Task();
    DataMapTaskConfig *dataMapConfig=new DataMapTaskConfig();
    _task->setTaskConfig(dataMapConfig);


    if(taskType=="DataMap"){
        _task->type="DataMap";
        initDataMapTaskConfig();
    }
}

void OgmConfigTaskWidget::changeDataMapTask(QString dataMapId)
{
    _task->getDataMapTaskConfig()->id=dataMapId;
}

void OgmConfigTaskWidget::initDataMapTaskConfig()
{
    _uiDataMap=new Ui::DataMapTaskConfigUI();
    _uiDataMap->setupUi(this);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskChooseInput, 0xf07c, "Choose", 6);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskSave, 0xf0c2, "Save", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskSaveAs, 0xf02e, "Save as", 6);

    connect(_uiDataMap->btnDataMapTaskChooseInput, &QToolButton::clicked, this, &OgmConfigTaskWidget::chooseFile);
    connect(_uiDataMap->btnDataMapTaskSave, &QToolButton::clicked, this, &OgmConfigTaskWidget::saveTask);
}

void OgmConfigTaskWidget::uiInfo2task()
{

}

void OgmConfigTaskWidget::saveTask()
{
    OgmPopWidget *widgetPop=new OgmPopWidget("SaveTask");
    widgetPop->show();

    connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varTaskInfo){
       QStringList strList=varTaskInfo.toStringList();

       _task->name=strList[0];
       _task->desc=strList[2];

       _task->uid=OgmHelper::createUId();
       _task->runstate="ToRun";
       _task->createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");

       //ui
       if(_uiDataMap->radioButtonSrc2Udx->isChecked()){
           _task->getDataMapTaskConfig()->calltype="src2udx";
       }
       else if(_uiDataMap->radioButtonUdx2Src->isChecked()){
           _task->getDataMapTaskConfig()->calltype="udx2src";
       }
       _task->getDataMapTaskConfig()->outputDirId="-1";
       _task->getDataMapTaskConfig()->outputFilename=_uiDataMap->txtDatamapTaskOutput->text();

       _taskBLL.data()->saveTask(_task);
       emit signalSwitchPage("TaskList");
    });
}

void OgmConfigTaskWidget::chooseFile()
{
    OgmPopWidget *widgetPop=new OgmPopWidget("ChooseFile");
    widgetPop->show();
    connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varFileInfo){
        QStringList strList=varFileInfo.toStringList();
        _task->getDataMapTaskConfig()->inputId=strList[0];
        _task->getDataMapTaskConfig()->inputFilename=strList[1];
    });
}

//Task *OgmConfigTaskWidget::uiInfo2task()
//{

//}
