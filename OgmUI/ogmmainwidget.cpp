#include "ogmmainwidget.h"
#include "ui_ogmmainwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmsetting.h"
#include "OgmUI/ogmpopwidget.h"

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
    _ui->lblTitle->setHidden(true);
    _ui->widgetIntegration->setHidden(true);

    QPixmap image(":/png/png/logo.png");
    _ui->lblTitleIcon->setPixmap(image);
    _ui->lblTitleIcon->setFixedSize(100, 30);
    _ui->lblTitleIcon->setScaledContents(true);

    //btn navigation icon
    //OgmUiHelper::Instance()->setIcon(_ui->lblTitleIcon, QChar(0xf0c2));
    OgmUiHelper::Instance()->setIcon(_ui->lblUserIcon, QChar(0xf2be));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeModel, 0xf0ac, "ModelRes");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeData, 0xf1c0, "DataRes");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeServer, 0xf233, "Server");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnHomeTool, 0xf00a, "Tool");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceTask, 0xf0ae, "Task");

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceFavor, 0xf004, "Favor");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceFileManager, 0xf07b, "FileManager");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceVisual, 0xf2d5, "Visual");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceIntegrated, 0xf0e8, "Integrated");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceIntegratedSolution, 0xf0b1, "Solution");
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnSpaceIntegratedTask, 0xf085, "Task");

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
        _widgetList->clearList();
        _widgetList->changeDataListUI(serverId, "Data", 0);
    });
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataMappingList, [=](QString serverId){
        _widgetList->clearList();
        _widgetList->changeDataListUI(serverId, "DataMapping", 0);
    });
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataRefactorList, [=](QString serverId){
        _widgetList->clearList();
        _widgetList->changeDataListUI(serverId, "DataRefactor", 0);
    });

    connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataServer, _widgetServerSidebar, &OgmServerSidebarWidget::changeDataServerUI);
    connect(_widgetDataServerTop, &OgmServerTopWidget::signalSearchTxtChanged, _widgetList, &OgmListWidget::searchListItemOnUI);
    //connect(_widgetDataServerTop, &OgmServerTopWidget::signalChangeDataFileByParentId, _widgetServerSidebar, &OgmServerSidebarWidget::changeDataFileUI);

    //model top
    connect(_widgetModelServerTop, &OgmServerTopWidget::signalChangeModelList, _widgetList, &OgmListWidget::changeModelListUIByPage);
    connect(_widgetModelServerTop, &OgmServerTopWidget::signalChangeModelServer, _widgetServerSidebar, &OgmServerSidebarWidget::changeModelServerUI);
    connect(_widgetModelServerTop, &OgmServerTopWidget::signalSearchTxtChanged, _widgetList, &OgmListWidget::searchListItemOnUI);

    //server top
    connect(_widgetServerTop, &OgmMiniTopWidget::signalChangeServerList, _widgetList, &OgmListWidget::changeServerListUI);
    connect(_widgetServerTop, &OgmMiniTopWidget::signalClearList, _widgetList, &OgmListWidget::clearList);

    //file top
    connect(_widgetFileServerTop, &OgmServerTopWidget::signalChangeDataServer, _widgetServerSidebar, &OgmServerSidebarWidget::changeDataFileUI);
    connect(_widgetFileServerTop, &OgmServerTopWidget::signalChangeDataFileByParentId, _widgetList, &OgmListWidget::changeFileListUIByParentId);
    connect(_widgetFileServerTop, &OgmServerTopWidget::signalClearList, _widgetList, &OgmListWidget::clearList);

    //favor top
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeFavor, _widgetFavorSidebar, &OgmFavorSidebarWidget::changeFavorUI);

    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeModelListByList, [=](QList<ModelService*> msList){
        _widgetList->setFavorId(_widgetFavorTop->getCurrentFavorId());
        _widgetList->setPageIndex(0);
        _widgetList->changeModelListUI(msList, "FavorModel");
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataListByList, [=](QList<DataService*> dsList){
        _widgetList->setFavorId(_widgetFavorTop->getCurrentFavorId());
        _widgetList->setPageIndex(0);
        _widgetList->changeDataListUI(dsList, "FavorData");
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataMappingListByList, [=](QList<DataMapping*> mappingList){
        _widgetList->setFavorId(_widgetFavorTop->getCurrentFavorId());
        _widgetList->setPageIndex(0);
        _widgetList->changeDataListUI(mappingList, "FavorDataMapping");
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalChangeDataRefactorListByList, [=](QList<DataRefactor*> refactorList){
        _widgetList->setFavorId(_widgetFavorTop->getCurrentFavorId());
        _widgetList->setPageIndex(0);
        _widgetList->changeDataListUI(refactorList, "FavorDataRefactor");
    });
    connect(_widgetFavorTop, &OgmServerTopWidget::signalClearList, _widgetList, &OgmListWidget::clearList);
    connect(_widgetFavorTop, &OgmServerTopWidget::signalSearchTxtChanged, _widgetList, &OgmListWidget::searchListItemOnUI);

    //task top
    connect(_widgetTaskTop, &OgmMiniTopWidget::signalChangeTaskList, _widgetList, &OgmListWidget::changeTaskListUI);
    connect(_widgetTaskTop, &OgmMiniTopWidget::signalClearList, _widgetList, &OgmListWidget::clearList);
    connect(_widgetTaskTop, &OgmMiniTopWidget::signalSetListType, _widgetList, &OgmListWidget::setListType);
    connect(_widgetTaskTop, &OgmMiniTopWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);

    //visual top
    connect(_widgetVisualTop, &OgmMiniTopWidget::signalClearList, _widgetList, &OgmListWidget::clearList);
    connect(_widgetVisualTop, &OgmMiniTopWidget::signalChangeVisualList, _widgetList, &OgmListWidget::changeVisualListUI);

    //list
    connect(_widgetList, &OgmListWidget::signalAddFolderOnFileLink, _widgetFileServerTop, &OgmServerTopWidget::addOneFileLinkOnUI);
    connect(_widgetList, &OgmListWidget::signalAddFavorSidebar, _widgetFavorSidebar, &OgmFavorSidebarWidget::changeChooseFavorUI);

    connect(_widgetList, &OgmListWidget::signalChangeDataMapTaskConfigUI, _widgetDataMapTaskConfig, &OgmConfigTaskWidget::changeDataMapTaskByService);
    connect(_widgetList, &OgmListWidget::signalChangeDataMapTaskConfigUIByTask, _widgetDataMapTaskConfig, &OgmConfigTaskWidget::changeDataMapTaskByTask);
    connect(_widgetList, &OgmListWidget::signalChangeDataRefactorTaskConfigUI, _widgetDataRefactorTaskConfig, &OgmConfigTaskWidget::changeDataRefactorTask);
    connect(_widgetList, &OgmListWidget::signalChangeDataRefactorTaskConfigUIByTask, _widgetDataRefactorTaskConfig, &OgmConfigTaskWidget::changeDataRefactorTaskByTask);
    connect(_widgetList, &OgmListWidget::signalChangeModelTaskConfigUI, _widgetModelTaskConfig, &OgmConfigTaskWidget::changeModelTask);
    connect(_widgetList, &OgmListWidget::signalChangeModelTaskConfigUIByTask, _widgetModelTaskConfig, &OgmConfigTaskWidget::changeModelTaskByTask);
    connect(_widgetList, &OgmListWidget::signalchangeVisualConfigUI, _widgetVisualConfig, &OgmConfigTaskWidget::changeVisual);

    connect(_widgetList, &OgmListWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);

    connect(_widgetList, &OgmListWidget::signalChangeModelServerTopUI, _widgetModelServerTop, &OgmServerTopWidget::changeModelServer);
    connect(_widgetList, &OgmListWidget::signalChangeDataServerTopUI, _widgetDataServerTop, &OgmServerTopWidget::changeDataServer);
    connect(_widgetList, &OgmListWidget::signalChangeMiniServerTopUI, _widgetServerTop, &OgmMiniTopWidget::changeServerType);
    connect(_widgetList, &OgmListWidget::signalChangeMiniTaskTopUI, _widgetTaskTop, &OgmMiniTopWidget::changeTaskType);

    //server sidebar
    connect(_widgetServerSidebar, &OgmServerSidebarWidget::signalChangeModelList, [=](QString serverId){
        _widgetModelServerTop->changeModelServer(serverId);
        //_widgetList->changeModelListUIByPage(serverId, 0);
    });
    connect(_widgetServerSidebar, &OgmServerSidebarWidget::signalChangeDataList, [=](QString serverId){
        _widgetDataServerTop->changeDataServer(serverId);
        //_widgetList->changeDataListUI(serverId, "Data", 0);
    });
    connect(_widgetServerSidebar, &OgmServerSidebarWidget::signalChangeDataFileUI, [=](QString serverId, QString fileParentId, QString fileCheckType){
        _widgetFileServerTop->changeFileManager(serverId);
        //_widgetList->changeFileListUIByParentId(serverId, fileParentId, fileCheckType);
    });
    connect(_widgetServerSidebar, &OgmServerSidebarWidget::signalChangeVisualConfigUI, _widgetVisualConfig, &OgmConfigTaskWidget::changeVisual);

    //favor sidebar
    connect(_widgetFavorSidebar, &OgmFavorSidebarWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetFavorSidebar, &OgmFavorSidebarWidget::signalChangeFavorTop, _widgetFavorTop, &OgmServerTopWidget::changeFavorManager);

    //task config
    connect(_widgetDataMapTaskConfig, &OgmConfigTaskWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetDataRefactorTaskConfig, &OgmConfigTaskWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetModelTaskConfig, &OgmConfigTaskWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetVisualConfig, &OgmConfigTaskWidget::signalSwitchPage, this, &OgmMainWidget::switchPage);
    connect(_widgetVisualConfig, &OgmConfigTaskWidget::signalGoVisual, _widgetVisual, &OgmVisualWidget::changeVisualUrl);
    connect(_widgetVisualConfig, &OgmConfigTaskWidget::signalChangeVisualFormatSidebar, _widgetServerSidebar, &OgmServerSidebarWidget::changeVisualFormat);


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

    //init visual
    _widgetVisual=new OgmVisualWidget(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_widgetVisual);

    //init listPage
    _scrollArea=new QScrollArea(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_scrollArea);

    QWidget *widgetListPage=new QWidget(_ui->widgetContent);
    widgetListPage->setWindowTitle("widget-content");

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

    _widgetModelTaskConfig=new OgmConfigTaskWidget("Model", widgetListPage);
    _ui->widgetContent->layout()->addWidget(_widgetModelTaskConfig);

    _widgetVisualConfig=new OgmConfigTaskWidget("Visual", widgetListPage);
    _ui->widgetContent->layout()->addWidget(_widgetVisualConfig);

    _widgetAggragationConfig=new OgmConfigTaskWidget("Aggragation", widgetListPage);
    _ui->widgetContent->layout()->addWidget(_widgetAggragationConfig);

    //init tool
    _widgetTool=new OgmToolWidget(_ui->widgetContent);
    _ui->widgetContent->layout()->addWidget(_widgetTool);

    //init server top
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

    //init mini top
    _widgetTaskTop=new OgmMiniTopWidget("Task", widgetListPage);
    layoutListPage->addWidget(_widgetTaskTop);

    _widgetServerTop=new OgmMiniTopWidget("Server", widgetListPage);
    layoutListPage->addWidget(_widgetServerTop);

    _widgetVisualTop=new OgmMiniTopWidget("Visual", widgetListPage);
    layoutListPage->addWidget(_widgetVisualTop);

    //init list
    _widgetList=new OgmListWidget(widgetListPage);
    layoutListPage->addWidget(_widgetList);



}

void OgmMainWidget::btnSideBarClicked()
{
    QToolButton* btn=(QToolButton*)sender();
    QString btnName=btn->objectName();

    //integration
    bool isIntegrationWidgetHide=_ui->widgetIntegration->isHidden();
    _ui->widgetIntegration->setHidden(true);


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
        switchPage("VisualList");
    }
    else if(btnName=="btnSpaceIntegrated"){
        btnCheckStateChange("btnSpaceIntegrated");

        if(isIntegrationWidgetHide)
            _ui->widgetIntegration->setHidden(false);
        else
            _ui->widgetIntegration->setHidden(true);
    }
    else if(btnName=="btnSpaceIntegratedSolution"){
        _ui->widgetIntegration->setHidden(false);

        btnCheckStateChange("btnSpaceIntegratedSolution");

        OgmPopWidget *popWidget=new OgmPopWidget("CommonV2");
        popWidget->setCommonV2WidgetInfo("Solution Type", "Create an new solution or start with exist solution", "New", "Exist");
        popWidget->show();
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varResult){
            if(varResult.toBool()){
                switchPage("IntegratedSolutionNew");
            }
            else
                switchPage("IntegratedSolutionQuery");
        });


    }
    else if(btnName=="btnSpaceIntegratedTask"){
        _ui->widgetIntegration->setHidden(false);

        btnCheckStateChange("btnSpaceIntegratedTask");

        switchPage("IntegratedTask");
    }
}

void OgmMainWidget::btnCheckStateChange(QString btnName)
{
    //btnCheckState
    QList<QToolButton*> btns=_ui->widgetTop->findChildren<QToolButton*>();
    foreach(QToolButton *mBtn, btns){
        if(mBtn->objectName()==btnName){
            mBtn->setChecked(true);
        }
        else{
            mBtn->setChecked(false);
        }
    }
}

void OgmMainWidget::switchPage(QString type)
{
    //btn check state
    if(type=="ModelList"){
        btnCheckStateChange("btnHomeModel");
    }
    else if(type=="DataList"){
        btnCheckStateChange("btnHomeData");
    }
    else if(type=="ServerList"){
        btnCheckStateChange("btnHomeServer");
    }
    else if(type=="Tool"){
        btnCheckStateChange("btnHomeTool");
    }
    else if(type=="TaskList"){
        btnCheckStateChange("btnSpaceTask");
    }
    else if(type=="FavorList"){
        btnCheckStateChange("btnSpaceFavor");
    }
    else if(type=="DataFileList"){
        btnCheckStateChange("btnSpaceFileManager");
    }
    else if(type=="VisualList"){
        btnCheckStateChange("btnSpaceVisual");
    }
    else if(type=="Integrated"){
        btnCheckStateChange("btnSpaceIntegrated");
    }
    else if(type=="IntegratedSolution"){
        btnCheckStateChange("btnSpaceIntegratedSolution");
    }
    else if(type=="IntegratedTask"){
        btnCheckStateChange("btnSpaceIntegratedTask");
    }

    _widgetServerSidebar->setHidden(true);
    _widgetFavorSidebar->setHidden(true);
    _widgetVisual->setHidden(true);
    _scrollArea->setHidden(true);
    _widgetTool->setHidden(true);

    _widgetDataServerTop->setHidden(true);
    _widgetModelServerTop->setHidden(true);
    _widgetFileServerTop->setHidden(true);
    _widgetFavorTop->setHidden(true);
    _widgetTaskTop->setHidden(true);
    _widgetServerTop->setHidden(true);
    _widgetVisualTop->setHidden(true);

    _widgetDataMapTaskConfig->setHidden(true);
    _widgetDataRefactorTaskConfig->setHidden(true);
    _widgetModelTaskConfig->setHidden(true);
    _widgetVisualConfig->setHidden(true);
    _widgetAggragationConfig->setHidden(true);

    _widgetList->setHidden(true);


    if(type=="Home"){
    }
    else if(type=="Tool"){
        _widgetTool->setHidden(false);
    }
    else if(type=="DataList"){
        _widgetList->setListType("DataList");
        _widgetList->clearList();

        _widgetDataServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

        _widgetDataServerTop->changeDataServer(_widgetDataServerTop->getCurrentServerId());
        //_widgetList->changeDataListUI(_widgetDataServerTop->getCurrentServerId(), "Data", 0);
    }
    else if(type=="ModelList"){

        _widgetList->setListType("ModelList");
        _widgetList->clearList();

        _widgetModelServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

        _widgetModelServerTop->changeModelServer(_widgetModelServerTop->getCurrentServerId());
    }
    else if(type=="ServerList"){
        _widgetList->setListType("ServerList");
        _widgetList->clearList();

        _widgetServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

        //_widgetList->changeServerListUI("ModelServer");
        _widgetServerTop->changeServerType("ModelServer");
    }
    else if(type=="DataFileList"){
        //_widgetList->changeFileListUIByParentId(_widgetFileServerTop->getCurrentId(), _widgetFileServerTop->getCurrentFileId(), "File");
        _widgetList->setListType("DataFileList");
        _widgetList->clearList();

        _widgetFileServerTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

        _widgetFileServerTop->changeFileManager(_widgetFileServerTop->getCurrentServerId());
    }
    else if(type=="FavorList"){
        _widgetList->setListType("FavorList");
        _widgetList->clearList();

        _widgetFavorTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

//        Favor *favor=_favorBLL.data()->getFavorGroupById(_widgetFavorTop->getCurrentServerId());
//        QList<ModelService*> msList=_favorBLL.data()->favor2modelServiceList(favor);
//        _widgetList->changeModelListUI(msList, "FavorModel");
        _widgetFavorTop->changeFavorManager(_widgetFavorTop->getCurrentFavorId());
    }
    else if(type=="TaskList"){
        _widgetList->setListType("TaskList");
        _widgetList->clearList();

        _widgetTaskTop->changeTaskType("ToRun");

        _widgetTaskTop->setHidden(false);      
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);
    }
    else if(type=="DataMapTaskConfig"){
        _widgetDataMapTaskConfig->setHidden(false);
    }
    else if(type=="DataRefactorTaskConfig"){
        _widgetDataRefactorTaskConfig->setHidden(false);
    }
    else if(type=="ModelTaskConfig"){
        _widgetModelTaskConfig->setHidden(false);
    }
    else if(type=="VisualConfig"){
        _widgetVisualConfig->setHidden(false);
    }
    else if(type=="IntegratedSolutionNew"){
        _widgetAggragationConfig->changeAggregationConfig(OgmSetting::urlAggragationNewSolution);
        _widgetAggragationConfig->setHidden(false);
    }
    else if(type=="IntegratedSolutionQuery"){
        _widgetAggragationConfig->changeAggregationConfig(OgmSetting::urlAggragationQuerySolution);
        _widgetAggragationConfig->setHidden(false);
    }
    else if(type=="IntegratedTask"){
        _widgetAggragationConfig->changeAggregationConfig(OgmSetting::urlAggragationQueryTask);
        _widgetAggragationConfig->setHidden(false);
    }
    else if(type=="VisualList"){
        _widgetList->setListType("VisualList");
        _widgetList->clearList();

        _widgetVisualTop->setHidden(false);
        _widgetList->setHidden(false);
        _scrollArea->setHidden(false);

        //_widgetList->changeServerListUI("ModelServer");
        _widgetVisualTop->changeVisual();
    }
    else if(type=="Visual"){
        _widgetVisual->setHidden(false);
    }
}




















