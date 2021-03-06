#include "ogmpopwidget.h"

#include "ui_ogmpopwidget.h"

#include "OgmCommon/ogmsetting.h"
#include "OgmCommon/ogmuihelper.h"

#include <QFileDialog>
#include <QScrollArea>

OgmPopWidget::OgmPopWidget(QString widgetType, QWidget *parent)
    :OgmWidget(false, true, parent)
    ,_ui(new Ui::OgmPopUI)
{
    _ui->setupUi(this);

    _ui->widgetPopFile->setHidden(true);
    _ui->widgetPopDeleteFile->setHidden(true);
    _ui->widgetPopChooseFile->setHidden(true);
    _ui->widgetPopSaveTask->setHidden(true);
    _ui->widgetPopNewServer->setHidden(true);
    _ui->widgetPopConfigModelTaskData->setHidden(true);

    if(widgetType=="NewFile")
        initNewFileWidget();
    else if(widgetType=="RenameFile")
        initReNameFileWidget();
    else if(widgetType=="DeleteFile")
        initDeleteFileWidget();
    else if(widgetType=="ChooseFile")
        initChooseDataFile();
    else if(widgetType=="ChooseRefactorMethod")
        initChooseRefactorMethod();
    else if(widgetType=="SaveTask")
        initSaveTask();
    else if(widgetType=="NewServer")
        initNewServer();
    else if(widgetType=="NewFavorGroup")
        initNewFavorGroupWidget();
    else if(widgetType=="DeleteFavorGroup")
        initDeleteFavorWidget();
    else if(widgetType=="Common")
        initDeleteFileWidget();
    else if(widgetType=="CommonV2")
        initCommonV2Widget();
    else if(widgetType=="ConfigModelTask")
        initConfigModelTask();

    setDragWidgetName("widgetPopTitle");
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->raise();
}

OgmPopWidget::OgmPopWidget(QString widgetType, QString serverId, QWidget *parent)
    :OgmWidget(false, true, parent)
    ,_ui(new Ui::OgmPopUI)
    ,_fileServerId(serverId)
{
    _ui->setupUi(this);

    _ui->widgetPopFile->setHidden(true);
    _ui->widgetPopDeleteFile->setHidden(true);
    _ui->widgetPopChooseFile->setHidden(true);
    _ui->widgetPopSaveTask->setHidden(true);
    _ui->widgetPopNewServer->setHidden(true);
    _ui->widgetPopConfigModelTaskData->setHidden(true);

    if(widgetType=="NewFile")
        initNewFileWidget();
    else if(widgetType=="RenameFile")
        initReNameFileWidget();
    else if(widgetType=="DeleteFile")
        initDeleteFileWidget();
    else if(widgetType=="ChooseFile")
        initChooseDataFile();
    else if(widgetType=="ChooseRefactorMethod")
        initChooseRefactorMethod();
    else if(widgetType=="SaveTask")
        initSaveTask();
    else if(widgetType=="NewServer")
        initNewServer();
    else if(widgetType=="NewFavorGroup")
        initNewFavorGroupWidget();
    else if(widgetType=="DeleteFavorGroup")
        initDeleteFavorWidget();
    else if(widgetType=="Common")
        initDeleteFileWidget();
    else if(widgetType=="ConfigModelTask")
        initConfigModelTask();

    setDragWidgetName("widgetPopTitle");
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void OgmPopWidget::changeChooseRefactorMethod(QString serverId, QString refactorId)
{
    OgmListWidget *mList=_ui->widgetPopChooseFile->findChild<OgmListWidget*>();
    mList->changeRefactorMethodListUI(serverId, refactorId);
}

void OgmPopWidget::changeConfigModelTaskUI(Task *task)
{
    _task=task;

    while(_ui->widgetPopTaskModelBtnGroup->layout()->count()>0){
        QWidget *widgetDel=_ui->widgetPopTaskModelBtnGroup->layout()->itemAt(0)->widget();
        _ui->widgetPopTaskModelBtnGroup->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
        if(task->getModelTaskConfig()->eventList.at(i)->eventType=="response"){
            QToolButton *btnEvent=new QToolButton(_ui->widgetPopTaskModelBtnGroup);
            btnEvent->setObjectName("btnConfigTaskEvent"+task->getModelTaskConfig()->eventList.at(i)->eventName);
            btnEvent->setText(task->getModelTaskConfig()->eventList.at(i)->eventName);
            //btnEvent->setFixedWidth(50);
            btnEvent->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            btnEvent->setWindowTitle("btn-miniTopLeft-f14");
            btnEvent->setCheckable(true);
            btnEvent->setAccessibleDescription(QString::number(i));
            connect(btnEvent, &QToolButton::clicked, [=](){
                _eventIndex=btnEvent->accessibleDescription();
                QString dataPath=_task->getModelTaskConfig()->eventList.at(_eventIndex.toInt())->dataPath;
                QString dataType=_task->getModelTaskConfig()->eventList.at(_eventIndex.toInt())->dataType;
                if(dataType=="remote"){
                    _ui->txtPopEventFileName->setText("remote data");
                }
                if(dataType=="example"){
                    _ui->txtPopEventFileName->setText("example data");
                }
                else{
                    if(dataPath=="")
                        _ui->txtPopEventFileName->setText(QString());
                    else{
                        QStringList pathList=dataPath.split("/");
                        QString fileName=pathList.at(pathList.count()-1);
                        _ui->txtPopEventFileName->setText(fileName);
                    }
                }

                QList<QToolButton*> btns=_ui->widgetPopTaskModelBtnGroup->findChildren<QToolButton*>();
                foreach(QToolButton *mBtn, btns){
                    if(mBtn==btnEvent){
                        mBtn->setChecked(true);
                    }
                    else{
                        mBtn->setChecked(false);
                    }
                }

                _ui->lblPopEventDes->setText(_task->getModelTaskConfig()->eventList.at(i)->eventDes);
            });
            _ui->widgetPopTaskModelBtnGroup->layout()->addWidget(btnEvent);
        }
    }
    //click first event
    QToolButton *btnFirstEvent=_ui->widgetPopTaskModelBtnGroup->findChild<QToolButton*>("btnConfigTaskEvent"+task->getModelTaskConfig()->eventList.at(0)->eventName);
    btnFirstEvent->click();
}

void OgmPopWidget::setCommonWidgetInfo(QString title, QString content, QString btnText)
{
    _ui->lblPopTitle->setText(title);
    _ui->lblPop->setText(content);
    _ui->btnPopA->setText(btnText);
}

void OgmPopWidget::setCommonV2WidgetInfo(QString title, QString content, QString btnTextLeft, QString btnTextRight)
{
    _ui->lblPopTitle->setText(title);
    _ui->lblPop->setText(content);
    _ui->btnPopA->setText(btnTextLeft);
    _ui->btnPopB->setText(btnTextRight);
}

void OgmPopWidget::setFileServerId(QString fileServerId)
{
    _fileServerId=fileServerId;
}

void OgmPopWidget::initCommonWidget()
{
    //style
    this->setFixedHeight(200);
    _ui->widgetPopDeleteFile->setHidden(false);

    _ui->btnPopB->setText("Cancel");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        bool isConfirm=true;
        QVariant result(isConfirm);
        this->close();
        emit signalOperationResult(result);

    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initCommonV2Widget()
{
    //style
    this->setFixedHeight(190);
    _ui->widgetPopDeleteFile->setHidden(false);

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        bool isConfirm=true;
        QVariant result(isConfirm);

        emit signalOperationResult(result);
        this->close();

    });
    connect(_ui->btnPopB, &QToolButton::clicked, [=](){
        bool isConfirm=false;
        QVariant result(isConfirm);

        emit signalOperationResult(result);
        this->close();
    });
}

void OgmPopWidget::initNewFileWidget()
{
    //style
    this->setFixedHeight(194);
    _ui->widgetPopFile->setHidden(false);

    _ui->lblPopTitle->setText("New Folder");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    _ui->txtPopNewFile->setPlaceholderText("Please input folder name");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QString folderName=_ui->txtPopNewFile->text();
        QVariant result(folderName);
        this->close();
        emit signalOperationResult(result);

    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initReNameFileWidget()
{
    //style
    this->setFixedHeight(190);
    _ui->widgetPopFile->setHidden(false);

    _ui->lblPopTitle->setText("Rename file");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    _ui->txtPopNewFile->setPlaceholderText("Please input file name");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QString folderName=_ui->txtPopNewFile->text();
        QVariant result(folderName);
        this->close();
        emit signalOperationResult(result);

    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initNewFavorGroupWidget()
{
    this->setFixedHeight(260);
    _ui->widgetPopSaveTask->setHidden(false);

    _ui->lblPopTitle->setText("New Solution");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    _ui->txtPopTaskName->setPlaceholderText("Please input solution name");
    _ui->txtPopTaskDesc->setPlaceholderText("Please input solution description");
    _ui->txtPopTaskTag->setHidden(true);

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QStringList strList;

        strList.append(_ui->txtPopTaskName->text());
        strList.append(_ui->txtPopTaskDesc->toPlainText());

        QVariant varTaskInfo(strList);
        this->close();
        emit signalOperationResult(varTaskInfo);


    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initDeleteFileWidget()
{
    //style
    this->setFixedHeight(190);
    _ui->widgetPopDeleteFile->setHidden(false);

    _ui->lblPopTitle->setText("Delete File");
    _ui->btnPopA->setText("Delete");
    _ui->btnPopB->setText("Cancel");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        this->close();
        bool isConfirm=true;
        QVariant result(isConfirm);
        emit signalOperationResult(result);    
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initDeleteFavorWidget()
{
    //style
    this->setFixedHeight(190);
    _ui->widgetPopDeleteFile->setHidden(false);

    _ui->lblPopTitle->setText("Delete solution");
    _ui->btnPopA->setText("Delete");
    _ui->btnPopB->setText("Cancel");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        bool isConfirm=true;
        QVariant result(isConfirm);
        this->close();
        emit signalOperationResult(result);
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initChooseDataFile()
{
    this->setFixedSize(700, 500);
    _ui->widgetPopChooseFile->setHidden(false);

    _ui->lblPopTitle->setText("Choose file");
    _ui->btnPopA->setText("Choose");
    _ui->btnPopB->setText("Cancel");

    _currentFileId=-1;

//    _scrollArea=new QScrollArea(_ui->widgetContent);
//    _ui->widgetContent->layout()->addWidget(_scrollArea);

//    QWidget *widgetListPage=new QWidget(_ui->widgetContent);
//    widgetListPage->setWindowTitle("widget-content");

//    _scrollArea->setWidget(widgetListPage);
//    _scrollArea->setWidgetResizable(widgetListPage);

//    QVBoxLayout *layoutListPage=new QVBoxLayout();
//    layoutListPage->setContentsMargins(10, 0, 10, 10);
//    layoutListPage->setSpacing(0);
//    widgetListPage->setLayout(layoutListPage);
    QScrollArea *scrollArea=new QScrollArea(_ui->widgetPopFileList);
    _ui->widgetPopFileList->layout()->addWidget(scrollArea);

    QWidget *widgetListPage=new QWidget(_ui->widgetPopFileList);
    widgetListPage->setWindowTitle("widget-content");

    scrollArea->setWidget(widgetListPage);
    scrollArea->setWidgetResizable(widgetListPage);

    QVBoxLayout *layoutListPage=new QVBoxLayout();
    layoutListPage->setSpacing(0);
    widgetListPage->setLayout(layoutListPage);

    OgmListWidget *listWidget=new OgmListWidget(_ui->widgetPopFileList);
    listWidget->layout()->setContentsMargins(5, 0, 0, 0);
    listWidget->setObjectName("mPopListWidget");
    listWidget->changeFileListUI(_fileServerId, "Data", "FileCheck");
    listWidget->setFileListState("chooseDataFile");
    connect(listWidget, &OgmListWidget::signalAddFolderOnFileLink, this, &OgmPopWidget::addOneFileLinkOnUI);
    layoutListPage->addWidget(listWidget);

    //file all btn
    QLabel *lblFileLinkAllIcon=new QLabel(_ui->widgetPopFileLink);
    OgmUiHelper::Instance()->setIcon(lblFileLinkAllIcon, QChar(0xf07b));
    lblFileLinkAllIcon->setWindowTitle("lbl-f16-normal");
    _ui->widgetPopFileLink->layout()->addWidget(lblFileLinkAllIcon);

    QToolButton *btnFileLinkAll=new QToolButton(_ui->widgetPopFileLink);
    btnFileLinkAll->setObjectName("btnFileLink|All");
    btnFileLinkAll->setText("All");
    btnFileLinkAll->setWindowTitle("btn-split");
    btnFileLinkAll->setAccessibleDescription("-1");
    connect(btnFileLinkAll, &QToolButton::clicked, [=](){
        removeNextAllFileLink("-1", "All");
        _currentFileId="-1";
        listWidget->clearList();
        listWidget->changeFileListUIByParentId(listWidget->getServerId(), "-1", "FileCheck");
    });
    _ui->widgetPopFileLink->layout()->addWidget(btnFileLinkAll);
    _fileLinkList.append(btnFileLinkAll->objectName());


    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        this->close();
        emit signalOperationResult(listWidget->getCheckFileInfo().toStringList());

    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initChooseRefactorMethod()
{
    this->setFixedSize(500, 295);
    _ui->widgetPopChooseFile->setHidden(false);
    _ui->widget_4->setHidden(true);
    _ui->btnPopA->setHidden(true);
    _ui->btnPopB->setText("Close");

    _ui->lblPopTitle->setText("Choose refactor method");

    OgmListWidget *listWidget=new OgmListWidget(_ui->widgetPopFileList);
    listWidget->setObjectName("mPopListWidget");
    _ui->widgetPopFileList->layout()->addWidget(listWidget);

    //function
    connect(listWidget, &OgmListWidget::signalChangeDataRefactorTaskConfigUI, [=](QString serverId, QString refactorId, QString methodName){
        emit signalChangeDataRefactorConfigUI(serverId, refactorId, methodName);
    });
    connect(listWidget, &OgmListWidget::signalSwitchPage, [=](QString pageType){
        this->close();
        emit signalSwitchPage(pageType);

    });

    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initSaveTask()
{
    this->setFixedHeight(275);
    _ui->widgetPopSaveTask->setHidden(false);

    _ui->lblPopTitle->setText("Save Task");
    _ui->btnPopA->setText("Save");
    _ui->btnPopB->setText("Cancel");

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QStringList strList;
        //TODO string is null or empty  or ""
//        if(_ui->txtPopTaskName->text().isEmpty())
        strList.append(_ui->txtPopTaskName->text());
        strList.append(_ui->txtPopTaskTag->text());
        strList.append(_ui->txtPopTaskDesc->toPlainText());

        QVariant varTaskInfo(strList);
        this->close();
        emit signalOperationResult(varTaskInfo);


    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initNewServer()
{
    this->setFixedHeight(374);
    _ui->widgetPopNewServer->setHidden(false);

    _ui->lblPopTitle->setText("Connect to Server");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QStringList strList;
        strList.append(_ui->txtPopNewServerIp->text());
        strList.append(_ui->txtPopNewServerName->text());
        if(_ui->radioBtnMs->isChecked())
            strList.append("ModelServer");
        else if(_ui->radioBtnDs->isChecked())
            strList.append("DataServer");
        strList.append(_ui->txtPopNewServerDesc->toPlainText());
        strList.append(_ui->txtPopNewServerLocation->text());

        QVariant varTaskInfo(strList);
        this->close();
        emit signalOperationResult(varTaskInfo);


    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initConfigModelTask()
{
    this->setFixedSize(500, 260);

    //_ui->btnUploadRemoteData->setHidden(true);
    _ui->widgetPopConfigModelTaskData->setHidden(false);

    _ui->lblPopTitle->setText("Config model task");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnPopUploadLocalData, 0xf07c, "Local", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnUploadRemoteData, 0xf07c, "Remote", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSelectDefaultData, 0xf15b, "Example", 6);

    connect(_ui->btnPopUploadLocalData, &QToolButton::clicked, [=](){
        QString filePath=QFileDialog::getOpenFileName(this, "choose upload data");
        if(filePath==QString::null)
            return;
        _task->getModelTaskConfig()->eventList[_eventIndex.toInt()]->dataType="local";
        _task->getModelTaskConfig()->eventList[_eventIndex.toInt()]->dataPath=filePath;

        QStringList pathList=filePath.split("/");
        QString fileName=pathList.at(pathList.count()-1);
        _ui->txtPopEventFileName->setText(fileName);
    });
    //remote
    connect(_ui->btnUploadRemoteData, &QToolButton::clicked, [=](){
        OgmPopWidget *widgetPop=new OgmPopWidget("ChooseFile", OgmSetting::defaultDataServerId);
        widgetPop->show();
        connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varFileInfo){
            QStringList strList=varFileInfo.toStringList();

            _task->getModelTaskConfig()->eventList[_eventIndex.toInt()]->dataType="remote";
            _task->getModelTaskConfig()->eventList[_eventIndex.toInt()]->modelServerId=_task->getModelTaskConfig()->serverId;
            _task->getModelTaskConfig()->eventList[_eventIndex.toInt()]->dataFromDataId=strList[0];


            _ui->txtPopEventFileName->setText(strList[1]);
        });

    });
    //example data
    connect(_ui->btnSelectDefaultData, &QToolButton::clicked, [=](){
        TaskBLL *taskBll=new TaskBLL();
        QString exampleDataId=taskBll->getExampleDataId(_task->getModelTaskConfig()->serverId, _task->getModelTaskConfig()->modelId, _task->getModelTaskConfig()->stateId, _task->getModelTaskConfig()->eventList.at(_eventIndex.toInt())->eventName);
        delete taskBll;
        if(exampleDataId=="")
            _ui->txtPopEventFileName->setText("No example data");
        else{
            _task->getModelTaskConfig()->eventList.at(_eventIndex.toInt())->dataType="example";
            _task->getModelTaskConfig()->eventList.at(_eventIndex.toInt())->dataFromModelId=exampleDataId;
            _ui->txtPopEventFileName->setText("Example data");
        }
    });

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QVariant varResult;
        varResult.setValue(_task);
        emit signalOperationResult(varResult);

        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::addOneFileLinkOnUI(QString fileId, QString fileName)
{
    _currentFileId=fileId;

    QLabel *lblLinkIcon=new QLabel(_ui->widgetPopFileLink);
    lblLinkIcon->setObjectName("lblFileLink|"+fileName);
    lblLinkIcon->setText(">");
    lblLinkIcon->setWindowTitle("lbl-split");
    _ui->widgetPopFileLink->layout()->addWidget(lblLinkIcon);
    _fileLinkList.append(lblLinkIcon->objectName());

    QToolButton *btnLinkIcon=new QToolButton(_ui->widgetPopFileLink);
    btnLinkIcon->setObjectName("btnFileLink|"+fileName);
    btnLinkIcon->setText(fileName);
    btnLinkIcon->setWindowTitle("btn-split");
    btnLinkIcon->setAccessibleDescription(fileId);
    connect(btnLinkIcon, &QToolButton::clicked, [=](){
        removeNextAllFileLink(fileId, fileName);

        OgmListWidget *widgetPopListWidget=_ui->widgetPopFileList->findChild<OgmListWidget*>("mPopListWidget");
        widgetPopListWidget->clearList();

        widgetPopListWidget->changeFileListUIByParentId(widgetPopListWidget->getServerId(), fileId, "FileCheck");
    });

    _ui->widgetPopFileLink->layout()->addWidget(btnLinkIcon);
    _fileLinkList.append(btnLinkIcon->objectName());
}

void OgmPopWidget::removeNextAllFileLink(QString fileId, QString fileName)
{
    int index;
    for(int i=0; i<_fileLinkList.count(); ++i){
        if(fileName==_fileLinkList[i].split("|")[1]){
            index=i;
        }
    }

    int count=_fileLinkList.count()-1;
    for(count; count>index; --count){
            QWidget *widgetDel=_ui->widgetPopFileLink->findChild<QWidget*>(_fileLinkList.at(count));
            _ui->widgetPopFileLink->layout()->removeWidget(widgetDel);
            delete widgetDel;
            _fileLinkList.removeAt(count);
    }
}
