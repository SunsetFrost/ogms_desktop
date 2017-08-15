#include "ogmconfigtaskwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"
#include "OgmCommon/ogmsetting.h"
#include "OgmUI/ogmpopwidget.h"

#include <QDateTime>


OgmConfigTaskWidget::OgmConfigTaskWidget(QString taskType, QWidget *parent)
    : QWidget(parent)
    , _taskType(taskType)
{
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);
    _dataRefactorBLL=QSharedPointer<DataRefactorBLL>(new DataRefactorBLL);
    _visualBLL=QSharedPointer<VisualBLL>(new VisualBLL);
    _fileDataBll=QSharedPointer<DataFileBll>(new DataFileBll);

    if(taskType=="DataMap"){
        initDataMapTaskConfig();
    }
    else if(taskType=="DataRefactor"){
        initDataRefctorTaskConfig();
    }
    else if(taskType=="Model"){
        initModelTaskConfig();
    }
    else if(taskType=="Visual"){
        initVisualConfig();
    }
    else if(taskType=="Aggragation"){
        initAggregationConfig();
    }
}

void OgmConfigTaskWidget::changeDataMapTaskByService(QString serverId, QString dataMapId)
{
    //init task
    _serverId=serverId;
    _task=new Task();
    DataMapTaskConfig *dataMapConfig=new DataMapTaskConfig();
    _task->setTaskConfig(dataMapConfig);
    _task->type="DataMap";

    _task->getDataMapTaskConfig()->id=dataMapId;
    _task->getDataMapTaskConfig()->serverId=serverId;

    QString xml=_taskBLL.data()->getDatamapSchema(serverId, dataMapId);

    _uiDataMap->txtDatamapTaskInput->setText(QString());
    _uiDataMap->txtDatamapTaskOutput->setText(QString());

    _uiDataMap->txtDatamapTaskXML->setText(xml);
    _uiDataMap->txtDatamapTaskXML->setAutoFormatting(QTextEdit::AutoAll);
}

void OgmConfigTaskWidget::changeDataMapTaskByTask(Task *task)
{
    _task=task;
    _serverId=task->getDataMapTaskConfig()->serverId;

    if(_task->getDataMapTaskConfig()->calltype=="src2udx"){
        _uiDataMap->radioButtonSrc2Udx->setChecked(true);
        _uiDataMap->radioButtonUdx2Src->setChecked(false);
    }
    else if(_task->getDataMapTaskConfig()->calltype=="udx2src"){
        _uiDataMap->radioButtonSrc2Udx->setChecked(false);
        _uiDataMap->radioButtonUdx2Src->setChecked(true);
    }

    if(_task->getDataMapTaskConfig()->inputId!=""){
        _uiDataMap->txtDatamapTaskInput->setText(_task->getDataMapTaskConfig()->inputFilename);
    }
    if(_task->getDataMapTaskConfig()->outputFilename!=""){
        _uiDataMap->txtDatamapTaskOutput->setText(_task->getDataMapTaskConfig()->outputFilename);
    }

    QString xml=_taskBLL.data()->getDatamapSchema(task->getDataMapTaskConfig()->serverId, task->getDataMapTaskConfig()->id);
    _uiDataMap->txtDatamapTaskXML->setText(xml);
    _uiDataMap->txtDatamapTaskXML->setAutoFormatting(QTextEdit::AutoAll);
}

void OgmConfigTaskWidget::changeDataRefactorTask(QString serverId, QString dataRefactorId, QString methodName)
{
    DataRefactorMethod *method=_dataRefactorBLL.data()->getDataRefactorByMethodName(serverId, dataRefactorId, methodName);

    //init task
    _task=new Task();
    _task->type="DataRefactor";
    _serverId=serverId;
    _refactorId=dataRefactorId;

    DataRefactorTaskConfig *dataRefactorConfig=new DataRefactorTaskConfig();
    dataRefactorConfig->id=dataRefactorId;
    dataRefactorConfig->serverId=serverId;
    dataRefactorConfig->methodName=methodName;

    QList<TASKREFACTORPARAM> paramList;
    for(int j=0; j<method->paramList.count(); ++j){
        TASKREFACTORPARAM param;
        paramList.append(param);
    }
    dataRefactorConfig->paramList=paramList;
    _task->setTaskConfig(dataRefactorConfig);

    //ui

    //clear btn
    while (_uiDataRefactor->widgetBtnParamsGroup->layout()->count()>0) {
        QWidget *widgetDel=_uiDataRefactor->widgetBtnParamsGroup->layout()->itemAt(0)->widget();
        _uiDataRefactor->widgetBtnParamsGroup->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    _uiDataRefactor->lblRefactorName->setText(method->name);
    _uiDataRefactor->lblRefactorDesc->setText(method->description);

    for(int i=0; i<method->paramList.count(); ++i){
        QToolButton *btnParam=new QToolButton(_uiDataRefactor->widgetBtnParamsGroup);
        btnParam->setText(method->paramList.at(i)->name);
        btnParam->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        btnParam->setWindowTitle("btn-miniTopLeft");
        btnParam->setCheckable(true);
        btnParam->setAccessibleDescription(QString::number(i));

        connect(btnParam, &QToolButton::clicked, [=](){

            //btn check state
            _paramIndex=btnParam->accessibleDescription();
            _uiDataRefactor->txtRefactorTaskConfigInput->setText(QString());


            QList<QToolButton*> btns=_uiDataRefactor->widgetBtnParamsGroup->findChildren<QToolButton*>();
            foreach(QToolButton *mBtn, btns){
                if(mBtn==btnParam){
                    mBtn->setChecked(true);
                }
                else{
                    mBtn->setChecked(false);
                }
            }

            changeMethodParamUI(method->paramList.at(i), _task->getDataRefactorTaskConfig()->paramList.at(i));
        });
        _uiDataRefactor->widgetBtnParamsGroup->layout()->addWidget(btnParam);
    }
    //init param
    QList<QToolButton*> btnList=_uiDataRefactor->widgetBtnParamsGroup->findChildren<QToolButton*>();
    for(int i=0; i<btnList.count(); ++i){
        if(btnList.at(i)->accessibleDescription()=="0")
            btnList.at(i)->click();
    }

    //changeMethodParamUI(method->paramList.at(0), _task->getDataRefactorTaskConfig()->paramList.at(0));
}

void OgmConfigTaskWidget::changeDataRefactorTaskByTask(Task *task)
{
    _task=task;
    _serverId=task->getDataRefactorTaskConfig()->serverId;
    _refactorId=task->getDataRefactorTaskConfig()->id;
    DataRefactorMethod *method=_dataRefactorBLL.data()->getDataRefactorByMethodName(_task->getDataRefactorTaskConfig()->serverId, _task->getDataRefactorTaskConfig()->id, _task->getDataRefactorTaskConfig()->methodName);

    if(NULL==method){
        OgmPopWidget *popWidget=new OgmPopWidget("Common");
        popWidget->setCommonWidgetInfo("Warning", "Data Refactor information is expired", "Ok");
        popWidget->show();
        return;
    }
    //ui

    //clear btn
    while (_uiDataRefactor->widgetBtnParamsGroup->layout()->count()>0) {
        QWidget *widgetDel=_uiDataRefactor->widgetBtnParamsGroup->layout()->itemAt(0)->widget();
        _uiDataRefactor->widgetBtnParamsGroup->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    _uiDataRefactor->lblRefactorName->setText(method->name);
    _uiDataRefactor->lblRefactorDesc->setText(method->description);

    for(int i=0; i<method->paramList.count(); ++i){
        QToolButton *btnParam=new QToolButton(_uiDataRefactor->widgetBtnParamsGroup);
        btnParam->setText(method->paramList.at(i)->name);
        btnParam->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        btnParam->setWindowTitle("btn-miniTopLeft");
        btnParam->setCheckable(true);
        btnParam->setAccessibleDescription(QString::number(i));

        connect(btnParam, &QToolButton::clicked, [=](){

            //btn check state
            _paramIndex=btnParam->accessibleDescription();
            _uiDataRefactor->txtRefactorTaskConfigInput->setText(method->paramList.at(_paramIndex.toInt())->name);

            QList<QToolButton*> btns=_uiDataRefactor->widgetBtnParamsGroup->findChildren<QToolButton*>();
            foreach(QToolButton *mBtn, btns){
                if(mBtn==btnParam){
                    mBtn->setChecked(true);
                }
                else{
                    mBtn->setChecked(false);
                }
            }

            changeMethodParamUI(method->paramList.at(i), _task->getDataRefactorTaskConfig()->paramList.at(i));
        });
        _uiDataRefactor->widgetBtnParamsGroup->layout()->addWidget(btnParam);
    }
    //init param
    QList<QToolButton*> btnList=_uiDataRefactor->widgetBtnParamsGroup->findChildren<QToolButton*>();
    for(int i=0; i<btnList.count(); ++i){
        if(btnList.at(i)->accessibleDescription()=="0")
            btnList.at(i)->click();
    }

    //changeMethodParamUI(method->paramList.at(0), _task->getDataRefactorTaskConfig()->paramList.at(0));
}

void OgmConfigTaskWidget::changeModelTask(QString serverId, QString modelId)
{
    //init task
    _task=_taskBLL.data()->createModelTask(serverId, modelId);
    _serverId=serverId;

    //init diagram
    QString initJson=OgmHelper::getInitDiagramJson("TnprME1XSTRaalF0TWpVMU5pMDBaVFUyTFdJek16TXRNVEEzT0RZMU16TXhNelZs");
    initJson="initPage("+initJson+")";
    _webView->page()->runJavaScript(initJson);
}

void OgmConfigTaskWidget::changeModelTaskByTask(Task *task)
{
    _task=task;
    _serverId=task->getModelTaskConfig()->serverId;

    //init diagram
    QString initJson=OgmHelper::getInitDiagramJson("TnprME1XSTRaalF0TWpVMU5pMDBaVFUyTFdJek16TXRNVEEzT0RZMU16TXhNelZs");
    initJson="initPage("+initJson+")";
    _webView->page()->runJavaScript(initJson);
}

void OgmConfigTaskWidget::changeVisual(Visual *visual, int formatIndex)
{
    _visualFormatIndex=formatIndex;
    _visualParamIndex=0;
    _serverId=OgmSetting::defaultDataServerId;

    _visual=visual;

    //ui

    //clear btn
    while (_uiVisual->widgetBtnParamsGroup->layout()->count()>0) {
        QWidget *widgetDel=_uiVisual->widgetBtnParamsGroup->layout()->itemAt(0)->widget();
        _uiVisual->widgetBtnParamsGroup->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    _uiVisual->lblRefactorName->setText(_visual->name);
    _uiVisual->lblRefactorDesc->setText(_visual->desc);

    for(int i=0; i<_visual->formatList.at(_visualFormatIndex)->pramaList.count(); ++i){
        QToolButton *btnParam=new QToolButton(_uiVisual->widgetBtnParamsGroup);
        btnParam->setText(_visual->formatList.at(_visualFormatIndex)->pramaList.at(i)->name);
        btnParam->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        btnParam->setWindowTitle("btn-miniTopLeft");
        btnParam->setCheckable(true);
        btnParam->setAccessibleDescription(QString::number(i));

        ///////btn function
        connect(btnParam, &QToolButton::clicked, [=](){
            //btn check state
            _visualParamIndex=btnParam->accessibleDescription().toInt();

            QList<QToolButton*> btns=_uiVisual->widgetBtnParamsGroup->findChildren<QToolButton*>();
            foreach(QToolButton *mBtn, btns){
                if(mBtn==btnParam){
                    mBtn->setChecked(true);
                }
                else{
                    mBtn->setChecked(false);
                }
            }

            _uiVisual->lblParamName->setText(_visual->formatList.at(_visualFormatIndex)->pramaList.at(i)->name);
            _uiVisual->lblParamType->setText(_visual->formatList.at(_visualFormatIndex)->pramaList.at(i)->type);
            _uiVisual->lblParamDescription->setText(_visual->formatList.at(_visualFormatIndex)->pramaList.at(i)->desc);
            _uiVisual->txtRefactorTaskConfigInput->setText(_visual->formatList.at(_visualFormatIndex)->pramaList.at(i)->fileName);

            _uiVisual->txtRefactorSchema->setText(_visualBLL.data()->getVisualSchema(_visual, _visualFormatIndex, _visualParamIndex));
            _uiVisual->txtRefactorSchema->setAutoFormatting(QTextEdit::AutoAll);
        });
        _uiVisual->widgetBtnParamsGroup->layout()->addWidget(btnParam);
    }
    //init param
    QList<QToolButton*> btnList=_uiVisual->widgetBtnParamsGroup->findChildren<QToolButton*>();
    for(int i=0; i<btnList.count(); ++i){
        if(btnList.at(i)->accessibleDescription()=="0")
            btnList.at(i)->click();
    }
}

void OgmConfigTaskWidget::changeAggregationConfig(QString url)
{
    //_webView=new QWebEngineView();
    _webView->load(QUrl(url));
}

void OgmConfigTaskWidget::initDataMapTaskConfig()
{
    //init ui
    _uiDataMap=new Ui::DataMapTaskConfigUI();
    _uiDataMap->setupUi(this);
    _uiDataMap->btnDataMapTaskSaveAs->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskChooseInput, 0xf07c, "Choose", 6);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskSave, 0xf0c2, "Save", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiDataMap->btnDataMapTaskSaveAs, 0xf02e, "Save as", 6);

    //init function
    connect(_uiDataMap->btnDataMapTaskChooseInput, &QToolButton::clicked, this, &OgmConfigTaskWidget::chooseFile);
    connect(_uiDataMap->btnDataMapTaskSave, &QToolButton::clicked, this, &OgmConfigTaskWidget::saveTask);

}

void OgmConfigTaskWidget::initDataRefctorTaskConfig()
{
    //init ui
    _uiDataRefactor=new Ui::DataRefactorTaskConfigUI();
    _uiDataRefactor->setupUi(this);
    _uiDataRefactor->btnRefactorTaskConfigSaveAsTask->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataRefactor->btnRefactorTaskConfigInput, 0xf07c, "Choose", 6);

    OgmUiHelper::Instance()->setButtonIcon(_uiDataRefactor->btnRefactorTaskConfigSaveTask, 0xf0c2, "Save", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiDataRefactor->btnRefactorTaskConfigSaveAsTask, 0xf02e, "Save as", 6);

    //init function
    connect(_uiDataRefactor->btnRefactorTaskConfigInput, &QToolButton::clicked, this, &OgmConfigTaskWidget::chooseFile);
    connect(_uiDataRefactor->btnRefactorTaskConfigSaveTask, &QToolButton::clicked, this, &OgmConfigTaskWidget::saveTask);
}

void OgmConfigTaskWidget::initModelTaskConfig()
{
    //init ui
    _uiModel=new Ui::TaskConfigModelUI();
    _uiModel->setupUi(this);
    _uiModel->btnTaskConfigModelSaveAs->setHidden(true);

    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelData, 0xf07c, "Config", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelSave, 0xf0c2, "Save", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelSaveAs, 0xf02e, "Save as", 6);

    //web diagram
    _webView=new QWebEngineView();
    _webView->setUrl(QUrl(OgmSetting::webDiagramPath));
    _uiModel->widgetTaskConfigModelDiagram->layout()->addWidget(_webView);

    //init function
    connect(_uiModel->btnTaskConfigModelData, &QToolButton::clicked, this, &OgmConfigTaskWidget::configModelData);
    connect(_uiModel->btnTaskConfigModelSave, &QToolButton::clicked, this, &OgmConfigTaskWidget::saveTask);
}

void OgmConfigTaskWidget::initVisualConfig()
{
    //init ui
    _uiVisual=new Ui::DataRefactorTaskConfigUI();
    _uiVisual->setupUi(this);

    OgmUiHelper::Instance()->setButtonIcon(_uiVisual->btnRefactorTaskConfigInput, 0xf07c, "Choose", 6);

    _uiVisual->btnRefactorTaskConfigSaveTask->setFixedWidth(150);
    OgmUiHelper::Instance()->setButtonIcon(_uiVisual->btnRefactorTaskConfigSaveTask, 0xf0ec, "switch format", 6);
    OgmUiHelper::Instance()->setButtonIcon(_uiVisual->btnRefactorTaskConfigSaveAsTask, 0xf2d5, "visual", 6);

    //init function
    connect(_uiVisual->btnRefactorTaskConfigInput, &QToolButton::clicked, this, &OgmConfigTaskWidget::chooseFile);
    connect(_uiVisual->btnRefactorTaskConfigSaveTask, &QToolButton::clicked, [=](){
        emit signalChangeVisualFormatSidebar(_visual);
    });

    connect(_uiVisual->btnRefactorTaskConfigSaveAsTask, &QToolButton::clicked, [=](){
        emit signalGoVisual(_visualBLL.data()->getVisualUrl(_visual, _visualFormatIndex));
        emit signalSwitchPage("Visual");
    });
}

void OgmConfigTaskWidget::initAggregationConfig()
{
    //init ui
    _uiModel=new Ui::TaskConfigModelUI();
    _uiModel->setupUi(this);
    _uiModel->widget->setHidden(true);
    this->layout()->setMargin(0);

//    _uiModel->lblTaskConfigModelName->setText("  Aggregation Model");
//    _uiModel->btnTaskConfigModelData->setFixedWidth(140);
//    _uiModel->btnTaskConfigModelSave->setFixedWidth(150);
//    _uiModel->btnTaskConfigModelSaveAs->setFixedWidth(120);

//    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelData, 0xf0ae, "New solution", 6);
//    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelSave, 0xf0ae, "Query solution", 6);
//    OgmUiHelper::Instance()->setButtonIcon(_uiModel->btnTaskConfigModelSaveAs, 0xf0ae, "Query task", 6);

    //web diagram
    _webView=new QWebEngineView();
    _uiModel->widgetTaskConfigModelDiagram->layout()->addWidget(_webView);

    //init function
//    connect(_uiModel->btnTaskConfigModelData, &QToolButton::clicked, [=](){
//        _webView->setUrl(url);
//    });
//    connect(_uiModel->btnTaskConfigModelSave, &QToolButton::clicked, [=](){
//        _webView->setUrl(OgmSetting::urlAggragationQuerySolution);
//    });
//    connect(_uiModel->btnTaskConfigModelSaveAs, &QToolButton::clicked, [=](){
//        _webView->setUrl(OgmSetting::urlAggragationQueryTask);
//    });
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

       _task->createTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");

       if(_taskType=="DataMap"){
           if(_uiDataMap->radioButtonSrc2Udx->isChecked()){
               _task->getDataMapTaskConfig()->calltype="src2udx";
           }
           else if(_uiDataMap->radioButtonUdx2Src->isChecked()){
               _task->getDataMapTaskConfig()->calltype="udx2src";
           }
           _task->getDataMapTaskConfig()->outputFilename=_uiDataMap->txtDatamapTaskOutput->text();
       }
       else if(_taskType=="DataRefactor"){
           int paramsCount= _task->getDataRefactorTaskConfig()->paramList.count();
           _task->getDataRefactorTaskConfig()->paramList[paramsCount-1].oid=QString();
           _task->getDataRefactorTaskConfig()->paramList[paramsCount-1].fileName=_uiDataRefactor->txtRefactorTaskConfigInput->text();

           QString folderId=_fileDataBll.data()->addFolder(_task->getDataRefactorTaskConfig()->serverId, "599023d478983d271073c108", _task->name, QDateTime::currentDateTime().toString("yyyy-MM-dd"));

           folderId=folderId.split("|").at(1);

           _task->getDataRefactorTaskConfig()->paramList[paramsCount-1].pid=folderId;
           _task->getDataRefactorTaskConfig()->paramList[paramsCount-1].ioType="out";
       }

       if(_taskBLL.data()->isTaskConfigInfoComplete(_task)){
           _task->runstate="ToRun";
       }
       else{
           _task->runstate="Prepare";
       }

       _taskBLL.data()->saveTask(_task);
       emit signalSwitchPage("TaskList");
    });
}

void OgmConfigTaskWidget::chooseFile()
{
    OgmPopWidget *widgetPop=new OgmPopWidget("ChooseFile", _serverId);
    widgetPop->show();
    connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varFileInfo){
        if(_taskType=="DataMap"){
            QStringList strList=varFileInfo.toStringList();
            _task->getDataMapTaskConfig()->inputId=strList[0];
            _task->getDataMapTaskConfig()->inputFilename=strList[1];
            _task->getDataMapTaskConfig()->outputDirId=strList[2];
            _uiDataMap->txtDatamapTaskInput->setText(strList[1]);


//            QString xml=OgmHelper::getXmlStringByPath("D:/Program/OGMS/build-OGMS-Desktop_Qt_5_8_0_MSVC2015_32bit-Debug/bin/user.config");
//            _uiDataMap->txtDatamapTaskXML->setText(xml);
//            _uiDataMap->txtDatamapTaskXML->setAutoFormatting(QTextEdit::AutoAll);
        }
        else if(_taskType=="DataRefactor"){
            QStringList strList=varFileInfo.toStringList();
            _task->getDataRefactorTaskConfig()->paramList[_paramIndex.toInt()].oid=strList[0];
            _task->getDataRefactorTaskConfig()->paramList[_paramIndex.toInt()].fileName=strList[1];
            _task->getDataRefactorTaskConfig()->paramList[_paramIndex.toInt()].pid=strList[2];
            _task->getDataRefactorTaskConfig()->paramList[_paramIndex.toInt()].ioType="in";

            _uiDataRefactor->txtRefactorTaskConfigInput->setText(strList[1]);
        }
        else if(_taskType=="Visual"){
            QStringList strList=varFileInfo.toStringList();
            _visual->formatList[_visualFormatIndex]->pramaList[_visualParamIndex]->fileId=strList[0];
            _visual->formatList[_visualFormatIndex]->pramaList[_visualParamIndex]->fileName=strList[1];

            _uiVisual->txtRefactorTaskConfigInput->setText(strList[1]);
        }
    });
}

void OgmConfigTaskWidget::configModelData()
{
    OgmPopWidget *widgetPop=new OgmPopWidget("ConfigModelTask");
    widgetPop->changeConfigModelTaskUI(_task);
    widgetPop->show();
    connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varResult){
        _task=varResult.value<Task*>();
    });
}

void OgmConfigTaskWidget::changeMethodParamUI(DataRefactorMethodParam *param, TASKREFACTORPARAM taskParam)
{
    //schema
    QString xml=_taskBLL.data()->getDataRefactorParamSchema(_serverId, _refactorId, param->schema, param->type);
    _uiDataRefactor->txtRefactorSchema->setText(xml);
    _uiDataRefactor->txtRefactorSchema->setAutoFormatting(QTextEdit::AutoAll);

    _uiDataRefactor->lblParamName->setText(param->name);
    _uiDataRefactor->lblParamType->setText(param->type);
    _uiDataRefactor->lblParamDescription->setText(param->description);
    _uiDataRefactor->txtRefactorTaskConfigInput->setText(taskParam.fileName);

    if(param->type=="in"){
        _uiDataRefactor->lblMethodParamType->setText("Input data");
        _uiDataRefactor->txtRefactorTaskConfigInput->setReadOnly(true);
        _uiDataRefactor->btnRefactorTaskConfigInput->setHidden(false);
    }
    else if(param->type=="out"){
        _uiDataRefactor->lblMethodParamType->setText("Output data");
        _uiDataRefactor->txtRefactorTaskConfigInput->setReadOnly(false);
        _uiDataRefactor->btnRefactorTaskConfigInput->setHidden(true);
    }
}

//Task *OgmConfigTaskWidget::uiInfo2task()
//{

//}
