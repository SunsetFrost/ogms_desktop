#include "ogmmainwidget.h"
#include "ui_ogmmainwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmsetting.h"

OgmMainWidget::OgmMainWidget(QWidget *parent) :
    OgmWidget(false, true, parent),
    _ui(new Ui::OgmMainWidget)
{
    _ui->setupUi(this);

    _favorBLL=QSharedPointer<FavorBLL>(new FavorBLL);
    _taskBLL=QSharedPointer<TaskBLL>(new TaskBLL);

    initStyle();
    initChildWidget();
    initFunction();
}

OgmMainWidget::~OgmMainWidget()
{
    delete _ui;
}

void OgmMainWidget::initStyle()
{
    _ui->lblUserIconPic->setHidden(true);

    //btn navigation icon
    OgmUiHelper::Instance()->setIcon(_ui->lblTitleIcon, QChar(0xf0c2));
    OgmUiHelper::Instance()->setIcon(_ui->lblUserIcon, QChar(0xf2be));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeModel, 0xf0ac, "Model");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeData, 0xf1c0, "Data");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeServer, 0xf233, "Server");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeTool, 0xf00a, "Tool");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceTask, 0xf0ae, "Task");

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceFavor, 0xf004, "Favor");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceFileManager, 0xf07b, "FileManager");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceVisual, 0xf2d5, "Visual");

    //btn main top icon
    OgmUiHelper::Instance()->setIcon(_ui->btnWidgetMainTopConfig, QChar(0xf013));
    OgmUiHelper::Instance()->setIcon(_ui->btnWidgetMainTopMin, QChar(0xf068));
    OgmUiHelper::Instance()->setIcon(_ui->btnWidgetMainTopMax, QChar(0xf2d0));
    OgmUiHelper::Instance()->setIcon(_ui->btnWidgetMainTopExit, QChar(0xf00d));
}

void OgmMainWidget::initFunction()
{
    setDragWidgetName("widgetMainTop");

    //side bar function
    QList<QToolButton*> sidebarBtnList=_ui->widgetTop->findChildren<QToolButton*>();
    foreach (QToolButton* btn, sidebarBtnList) {
        connect(btn, &QToolButton::clicked, this, &OgmMainWidget::btnSideBarClicked);
    }

    connect(_ui->btnWidgetMainTopExit, &QToolButton::clicked, this, &OgmMainWidget::close);
    connect(_ui->btnWidgetMainTopMin, &QToolButton::clicked, this, &OgmMainWidget::showMinimized);
    connect(_ui->btnWidgetMainTopMax, &QToolButton::clicked, [=](){
        if(this->isMaximized()){
            this->showNormal();
        }
        else {
            this->showMaximized();
        }
    });

    //connect

    //data top
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataList, [=](QString serverId){
        _widgetList->changeDataListUI(serverId, "Data");
    });
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataMappingList, [=](QString serverId){
        _widgetList->changeDataListUI(serverId, "DataMapping");
    });
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataRefactorList, [=](QString serverId){
        _widgetList->changeDataListUI(serverId, "DataRefactor");
    });

    //model top
    connect(_widgetModelServerTop, &OgmServerTopWidget::signalChangeModelServer, _widgetServerSidebar, &OgmServerSidebarWidget::changeModelServerUI);

    //server top
    connect(_widgetServerTop, &OgmMiniTopWidget::signalChangeServerList, _widgetList, &OgmListWidget::changeServerListUI);

    //file top
    connect(_widgetFileServerTop, &OgmServerTopWidget::signalChangeDataFileByParentId, _widgetList, &OgmListWidget::changeFileListUIByParentId);

    //favor top
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeFavor, _widgetFavorSidebar, &OgmFavorSidebarWidget::changeFavorUI);

    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeModelListByList, [=](QList<ModelService*> msList){
        _widgetList->changeModelListUI(msList);
    });

    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataListByList, [=](QList<DataService*> dsList){
        _widgetList->changeDataListUI(dsList);
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataMappingListByList, [=](QList<DataMapping*> mappingList){
        _widgetList->changeDataListUI(mappingList);
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataRefactorListByList, [=](QList<DataRefactor*> refactorList){
        _widgetList->changeDataListUI(refactorList);
    });
    //task top
    connect(_widgetTaskTop, &OgmMiniTopWidget::signalChangeTaskList, _widgetList, &OgmListWidget::changeTaskListUI);

    //list
    connect(_widgetList, &OgmListWidget::signalAddFolderOnFileLink, _widgetFileServerTop, &OgmServerTopWidget::addOneFileLinkOnUI);
    connect(_widgetList, &OgmListWidget::signalAddFavorSidebar, _widgetFavorSidebar, &OgmFavorSidebarWidget::changeChooseFavorUI);
    connect(_widgetList, &OgmListWidget::signalChangeDataMapTaskConfigUI, _widgetDataMapTaskConfig, &OgmConfigTaskWidget::changeDataMapTask);
    connect(_widgetList, &OgmListWidget::signalChangeDataRefactorTaskConfigUI, _widgetDataRefactorTaskConfig, &OgmConfigTaskWidget::changeDataRefactorTask);
    connect(_widgetList, &OgmListWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);

    //server sidebar
    connect(_widgetServerSidebar, &OgmServerSidebarWidget::signalChangeModelList, [=](QString serverId){
        _widgetModelServerTop->changeModelServer(serverId);
        _widgetList->changeModelListUI(serverId);
    });

    //favor sidebar
    connect(_widgetFavorSidebar, &OgmFavorSidebarWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetFavorSidebar, &OgmFavorSidebarWidget::signalChangeFavorTop, _widgetFavorTop, &OgmServerTopWidget::changeFavorManager);

    //task config
    connect(_widgetDataMapTaskConfig, &OgmConfigTaskWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);



    switchPage("Home");
}

void OgmMainWidget::initChildWidget()
{
    //init server sidebar
    _widgetServerSidebar=new OgmServerSidebarWidget(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_widgetServerSidebar);

    //init favor sidebar
    _widgetFavorSidebar=new OgmFavorSidebarWidget(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_widgetFavorSidebar);

    //init listPage
    _scrollArea=new QScrollArea(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_scrollArea);

    QWidget *widgetListPage=new QWidget(_ui->widgetContent);
    widgetListPage->setWindowTitle("widget-content");
    //_ui->widgetContent->layout()->addWidget(widgetListPage);

    _scrollArea->setWidget(widgetListPage);
    _scrollArea->setWidgetResizable(widgetListPage);

    QVBoxLayout *layoutListPage=new QVBoxLayout();
    layoutListPage->setContentsMargins(10, 0, 10, 10);
    layoutListPage->setSpacing(0);
    widgetListPage->setLayout(layoutListPage);

    //init taskConfig
    _widgetDataMapTaskConfig=new OgmConfigTaskWidget("DataMap", widgetListPage);
    _ui->widgetContent->layout()->addWidget(_widgetDataMapTaskConfig);

    _widgetDataRefactorTaskConfig=new OgmConfigTaskWidget("DataRefactor", widgetListPage);
    _ui->widgetContent->layout()->addWidget(_widgetDataRefactorTaskConfig);

    //init tool
    _widgetTool=new OgmToolWidget(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_widgetTool);

    //init serverTop
    _widgetDataServerTop=new OgmServerTopWidget("Data", widgetListPage);
    _widgetDataServerTop->changeDataServer(OgmSetting::defaultDataServerId);
    layoutListPage->addWidget(_widgetDataServerTop);

    _widgetModelServerTop=new OgmServerTopWidget("Model", widgetListPage);
    _widgetModelServerTop->changeModelServer(OgmSetting::defaultModelServerId);
    layoutListPage->addWidget(_widgetModelServerTop);

    _widgetFileServerTop=new OgmServerTopWidget("File", widgetListPage);
    _widgetFileServerTop->changeFileManager(OgmSetting::defaultDataServerId);
    layoutListPage->addWidget(_widgetFileServerTop);

    _widgetFavorTop=new OgmServerTopWidget("Favor", widgetListPage);
    _widgetFavorTop->changeFavorManager(OgmSetting::defaultFavorId);
    layoutListPage->addWidget(_widgetFavorTop);

    _widgetTaskTop=new OgmMiniTopWidget("Task", widgetListPage);
    layoutListPage->addWidget(_widgetTaskTop);

    _widgetServerTop=new OgmMiniTopWidget("Server", widgetListPage);
    layoutListPage->addWidget(_widgetServerTop);

    //init list
    _widgetList=new OgmListWidget(widgetListPage);
    layoutListPage->addWidget(_widgetList);



}

void OgmMainWidget::btnSideBarClicked()
{
    QToolButton* btn=(QToolButton*)sender();
    QString btnName=btn->objectName();

    if(btnName=="btnHomeModel"){
        switchPage("ModelList");
    }
    else if(btnName=="btnHomeData"){
        switchPage("DataList");
    }
    else if(btnName=="btnHomeServer"){
        switchPage("ServerList");
    }
    else if(btnName=="btnHomeTool"){
        switchPage("Tool");
    }
    else if(btnName=="btnSpaceTask"){
        switchPage("TaskList");
    }
    else if(btnName=="btnSpaceModelTask"){

    }
    else if(btnName=="btnSpaceMappingTask"){

    }
    else if(btnName=="btnSpaceRefactorTask"){

    }
    else if(btnName=="btnSpaceFavor"){
        switchPage("FavorList");
    }
    else if(btnName=="btnSpaceFileManager"){
        switchPage("DataFileList");
    }
    else if(btnName=="btnSpaceVisual"){

    }

    //btnCheckState
    QList<QToolButton*> btns=_ui->widgetTop->findChildren<QToolButton*>();
    foreach(QToolButton *mBtn, btns){
        if(mBtn==btn){
            mBtn->setChecked(true);
        }
        else{
            mBtn->setChecked(false);
        }
    }
}

void OgmMainWidget::switchPage(QString type)
{
    _widgetServerSidebar->setHidden(true);
    _widgetFavorSidebar->setHidden(true);
    _scrollArea->setHidden(true);
    _widgetTool->setHidden(true);

    _widgetDataServerTop->setHidden(true);
    _widgetModelServerTop->setHidden(true);
    _widgetFileServerTop->setHidden(true);
    _widgetFavorTop->setHidden(true);
    _widgetTaskTop->setHidden(true);
    _widgetServerTop->setHidden(true);

    _widgetDataMapTaskConfig->setHidden(true);
    _widgetDataRefactorTaskConfig->setHidden(true);

    _widgetList->setHidden(true);

    if(type=="Home"){
    }
    else if(type=="Tool"){
        _widgetTool->setHidden(false);
    }
    else if(type=="DataList"){
        _widgetList->changeDataListUI(_widgetDataServerTop->getCurrentId(), "Data");

        _widgetDataServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="ModelList"){
        _widgetList->changeModelListUI(_widgetModelServerTop->getCurrentId());

        _widgetModelServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="ServerList"){
        _widgetList->changeServerListUI("ModelServer");
        _widgetServerTop->taskBtnCheckStateManage("ModelServer");

        _widgetServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="DataFileList"){
        _widgetList->changeFileListUIByParentId(_widgetFileServerTop->getCurrentId(), _widgetFileServerTop->getCurrentFileId());

        _widgetFileServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="FavorList"){
        Favor *favor=_favorBLL.data()->getFavorGroupById(_widgetFavorTop->getCurrentId());
        QList<ModelService*> msList=_favorBLL.data()->favor2modelServiceList(favor);
        _widgetList->changeModelListUI(msList);

        _widgetFavorTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="TaskList"){
        QList<Task*> taskList=_taskBLL.data()->getAllTask();
        _widgetList->changeTaskListUI(taskList, "ToRun");

        _widgetTaskTop->setHidden(false);
        _widgetTaskTop->taskBtnCheckStateManage("ToRun");
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="DataMapTaskConfig"){
        _widgetDataMapTaskConfig->setHidden(false);
    }
    else if(type=="DataRefactorTaskConfig"){
        _widgetDataRefactorTaskConfig->setHidden(false);
    }
}




















