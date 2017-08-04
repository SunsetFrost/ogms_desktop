#include "ogmlistwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"
#include "OgmCommon/ogmprogressbar.h"

#include "OgmUI/ogmpopwidget.h"

#include <QLayout>
#include <QScrollArea>

OgmListWidget::OgmListWidget(QWidget *parent) : QWidget(parent)
{
    _modelServiceBLL= QSharedPointer<ModelServiceBLL> (new ModelServiceBLL);
    _modelServerBLL=  QSharedPointer<ModelServerBLL>  (new ModelServerBLL);
    _dataServerBLL=   QSharedPointer<DataServerBLL>   (new DataServerBLL);
    _dataServiceBLL=  QSharedPointer<DataServiceBLL>  (new DataServiceBLL);
    _dataMappingBLL=  QSharedPointer<DataMappingBLL>  (new DataMappingBLL);
    _dataRefactorBLL= QSharedPointer<DataRefactorBLL> (new DataRefactorBLL);
    _dataFileBLL=     QSharedPointer<DataFileBll>     (new DataFileBll);
    _taskBLL=         QSharedPointer<TaskBLL>         (new TaskBLL);

    initWidget();
}

void OgmListWidget::changeModelListUIByPage(QString serverId, int pageIndex)
{
    _serverId=serverId;
    QList<ModelService*> modelList=_modelServiceBLL.data()->getModelServiceListByPage(serverId, pageIndex);
    changeModelListUI(modelList);
}

void OgmListWidget::changeModelListUI(QList<ModelService *> modelList)
{
    _listType="Model";
    clearList();

    QList<QVariant> varList=OgmHelper::toVarList(modelList);

    listPaging(varList, 25);
}

void OgmListWidget::changeDataListUI(QList<DataService *> dataList)
{
    _listType="Data";
    clearList();

    QList<QVariant> varList=OgmHelper::toVarList(dataList);

    listPaging(varList, 25);
}

void OgmListWidget::changeDataListUI(QList<DataMapping *> dataMappingList)
{
    _listType="DataMapping";
    clearList();

    QList<QVariant> varList=OgmHelper::toVarList(dataMappingList);

    listPaging(varList, 25);
}

void OgmListWidget::changeDataListUI(QList<DataRefactor *> dataRefactorList)
{
    _listType="DataRefactor";
    clearList();

    QList<QVariant> varList=OgmHelper::toVarList(dataRefactorList);
    listPaging(varList, 25);
}

void OgmListWidget::changeDataListUI(QString serverId, QString type, int pageIndex)
{
    _serverId=serverId;
    _currentPageIndex=pageIndex;

    if(type=="Data"){
        QList<DataService*> dataList=_dataServiceBLL.data()->getDataListByPage(serverId, pageIndex);
        changeDataListUI(dataList);
    }
    else if(type=="DataMapping"){
        QList<DataMapping*> dataMappingList=_dataMappingBLL.data()->getDataMappingByPage(serverId, pageIndex);
        changeDataListUI(dataMappingList);
    }
    else if(type=="DataRefactor"){
        QList<DataRefactor*> dataRefactorList=_dataRefactorBLL.data()->getDataRefactorByPage(serverId, pageIndex);
        changeDataListUI(dataRefactorList);
    }
}

void OgmListWidget::changeFileListUI(QList<DataFile *> dataFileList, QString checkType)
{
    _listType=checkType;
    clearList();

    QList<QVariant> varList=OgmHelper::toVarList(dataFileList);

    listPaging(varList, 25);
}

void OgmListWidget::changeFileListUI(QString serverId, QString fileType, QString checkType)
{
    _serverId=serverId;

    if(fileType=="Data"){
        QList<DataFile*> fileList=_dataFileBLL.data()->getAllFiles(serverId);
        changeFileListUI(fileList, checkType);
    }
}

void OgmListWidget::changeFileListUIByParentId(QString serverId, QString parentId, QString checkType)
{
    _serverId=serverId;

    QList<DataFile*> fileList=_dataFileBLL.data()->getFilesByParent(serverId, parentId);
    changeFileListUI(fileList, checkType);
}

void OgmListWidget::changeServerListUI(QString serverType)
{
    _listType="Server";
    clearList();

    QList<QVariant> varList;

    if(serverType=="ModelServer"){
        QList<ModelServer*> serverList=_modelServerBLL.data()->getAllServer();
        varList=OgmHelper::toVarList(serverList);
    }
    else if(serverType=="DataServer"){
        QList<DataServer*> serverList=_dataServerBLL.data()->getAllServer();
        varList=OgmHelper::toVarList(serverList);
    }

    listPaging(varList, 25);
}

void OgmListWidget::setFileListState(QString state)
{
    if(state=="chooseDataFile"){
        _isCheckable=true;
    }
}

QVariant OgmListWidget::getCheckFileInfo()
{
    int checkIndex;
    QList<QToolButton*> btnList= _widgetList->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0; i<btnList.count(); ++i){
        if(btnList.at(i)->isChecked())
            checkIndex=i;
    }
    QStringList strList;
    strList.append(btnList.at(checkIndex)->objectName().split("|")[1]);
    strList.append(btnList.at(checkIndex)->objectName().split("|")[2]);
    strList.append(btnList.at(checkIndex)->objectName().split("|")[3]);
    QVariant varFileInfo(strList);
    return varFileInfo;
}

//void OgmListWidget::changeTaskListUI(QString taskType)
//{

//}

void OgmListWidget::changeTaskListUI(QList<Task *> taskList, QString taskRunState)
{
    _listType=taskRunState;
    clearList();

    QList<Task*> displayedTaskList=_taskBLL.data()->getSpecificTaskListFromTaskList(taskList, taskRunState, QString());

    if(taskRunState!="Running"){
        QList<QVariant> varList=OgmHelper::toVarList(displayedTaskList);
        listPaging(varList, 25);
    }
}

void OgmListWidget::changeRefactorMethodListUI(QString serverId, QString refactorId)
{
    _listType="ChooseRefactorMethod";
    clearList();

    QList<DataRefactorMethod*> methodList=_dataRefactorBLL.data()->getAllDataRefactorMethodByRefactorId(serverId, refactorId);
    QList<QVariant> varList=OgmHelper::toVarList(methodList);

    listPaging(varList, 25);
}

void OgmListWidget::setPageIndex(int pageIndex)
{
    _currentPageIndex=pageIndex;
}

void OgmListWidget::initWidget()
{
    _currentPageIndex=0;

    QVBoxLayout *layoutMain=new QVBoxLayout();
    //layoutMain->setContentsMargins(15, 3, 15, 15);
    this->setLayout(layoutMain);

    _widgetList=new QWidget(this);
    layoutMain->addWidget(_widgetList);

    QVBoxLayout *layoutList=new QVBoxLayout();
    layoutList->setMargin(0);
    layoutList->setSpacing(0);
    _widgetList->setLayout(layoutList);

    layoutMain->addStretch();

    _widgetTurnPage=new QWidget(this);
    layoutMain->addWidget(_widgetTurnPage);
    //_widgetTurnPage->setHidden(true);

    QHBoxLayout *layoutTurnPage=new QHBoxLayout();
    _widgetTurnPage->setLayout(layoutTurnPage);
}

void OgmListWidget::clearList()
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    //delete or hide exist widget
    for(int i=(_widgetList->layout()->count()-1); i>=0; --i){
        QWidget* widgetDel=_widgetList->layout()->itemAt(i)->widget();
        if(widgetDel){
            if(widgetDel->accessibleDescription()=="progressBar"){
                if(_listType=="Running"){
                    widgetDel->setHidden(false);
                }
                else{
                    widgetDel->setHidden(true);
                }
            }
            else if(widgetDel->accessibleDescription()=="btn"){
                _widgetList->layout()->removeWidget(widgetDel);
                delete widgetDel;
            }
        }
        else{
            QSpacerItem *space=_widgetList->layout()->itemAt(i)->spacerItem();
            _widgetList->layout()->removeItem(space);
            delete space;
        }
    }
}

void OgmListWidget::listPaging(QList<QVariant> varList, int pageAmount)
{
    int count=varList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    if(count==0){
        layoutList->addStretch();
    }
    else if(count<OgmListHelper::pageAmount){
        for(int i=0; i<count; ++i){
            if(i%2==0){
                addListIntelligent(varList[i], "btn-model-dark");
            }
            else{
                addListIntelligent(varList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        if(_currentPageIndex==0){
            initTurnPage("first");
        }
        else
            initTurnPage("last");
    }
    else{
        for(int i=0; i<OgmListHelper::pageAmount; ++i){
            if(i%2==0){
                addListIntelligent(varList[i], "btn-model-dark");
            }
            else{
                addListIntelligent(varList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        if(_currentPageIndex==0){
            initTurnPage("firstFull");
        }
        else
            initTurnPage("middle");
    }
}

void OgmListWidget::addListIntelligent(QVariant var, QString style)
{
    QString typeName=var.typeName();
    if(typeName=="ModelService*"){
        ModelService *model=var.value<ModelService*>();
        addOneModelServiceOnUI(model, style);
    }
    else if(typeName=="DataService*"){
        DataService *data=var.value<DataService*>();
        addOneDataOnUI(data, style);
    }
    else if(typeName=="DataMapping*"){
        DataMapping *datamap=var.value<DataMapping*>();
        addOneDataMappingOnUI(datamap, style);
    }
    else if(typeName=="DataRefactor*"){
        DataRefactor *dataRefactor=var.value<DataRefactor*>();
        addOneDataRefactorOnUI(dataRefactor, style);
    }
    else if(typeName=="DataRefactorMethod*"){
        DataRefactorMethod *dataMehtod=var.value<DataRefactorMethod*>();
        addOneDataMethodOnUI(dataMehtod, style);
    }
    else if(typeName=="DataFile*"){
        DataFile *dataFile=var.value<DataFile*>();
        addOneDataFileOnUI(dataFile, style);
    }
    else if(typeName=="Task*"){
        Task *task=var.value<Task*>();
        addOneTaskOnUI(task, style);
    }
    else if(typeName=="ModelServer*"){
        ModelServer *server=var.value<ModelServer*>();
        addOneServerOnUI(server, style);
    }
    else if(typeName=="DataServer*"){
        DataServer *server=var.value<DataServer*>();
        addOneServerOnUI(server,style);
    }
}

void OgmListWidget::addOneDataOnUI(DataService *data, QString style)
{
    QList<LISTCHILD> listItemList;

    LISTCHILD listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTCHILD listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTCHILD listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTCHILD listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf019;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="download data";
    listItemBtnDownload.objectName="btnDataDownload|"+data->id;
    listItemList.append(listItemBtnDownload);

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemAuthor;
    listItemAuthor.typeValue=ItemType::Label;
    listItemAuthor.textValue=data->author;
    listItemAuthor.fixWidth=100;
    listItemAuthor.iconValue=0;
    listItemAuthor.styleName="lbl-light";
    listItemList.append(listItemAuthor);

    OgmListHelper::addListItem(_widgetList, "btnDataList|"+data->id, style, "btn", listItemList);

    //connect
    QToolButton *btn=_widgetList->findChild<QToolButton*>(listItemBtnFavor.objectName);
    connect(btn, &QToolButton::clicked, [=](){
        emit signalAddFavorSidebar(data->serverId, data->id, "Data");
    });
}

void OgmListWidget::addOneDataMappingOnUI(DataMapping *data, QString style)
{
    QList<LISTCHILD> listItemList;

    LISTCHILD listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTCHILD listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataMappingDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTCHILD listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataMappingFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTCHILD listItemBtnInvoke;
    listItemBtnInvoke.typeValue=ItemType::ToolButton;
    listItemBtnInvoke.iconValue=0xf04b;
    listItemBtnInvoke.styleName="btn-light";
    listItemBtnInvoke.toolTipValue="invoke data mapping service";
    listItemBtnInvoke.objectName="btnDataMappingInvoke|"+data->id;
    listItemList.append(listItemBtnInvoke);

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemAuthor;
    listItemAuthor.typeValue=ItemType::Label;
    listItemAuthor.textValue=data->author;
    listItemAuthor.fixWidth=100;
    listItemAuthor.iconValue=0;
    listItemAuthor.styleName="lbl-light";
    listItemList.append(listItemAuthor);

    OgmListHelper::addListItem(_widgetList, "btnDataMappingList|"+data->id, style, "btn", listItemList);

    //connect
    QToolButton *btn=_widgetList->findChild<QToolButton*>(listItemBtnFavor.objectName);
    connect(btn, &QToolButton::clicked, [=](){
        emit signalAddFavorSidebar(data->serverId, data->id, "DataMapping");
    });

    QToolButton *btnInvoke=_widgetList->findChild<QToolButton*>(listItemBtnInvoke.objectName);
    connect(btnInvoke, &QToolButton::clicked, [=](){
        emit signalSwitchPage("DataMapTaskConfig");
        emit signalChangeDataMapTaskConfigUI(data->serverId, data->id);
    });
}

void OgmListWidget::addOneDataRefactorOnUI(DataRefactor *data, QString style)
{
    QList<LISTCHILD> listItemList;

    LISTCHILD listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTCHILD listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataRefactorDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTCHILD listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataRefactorFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTCHILD listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf04b;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="run data refactor method";
    listItemBtnDownload.objectName="btnDataRefactorRun|"+data->id;
    listItemList.append(listItemBtnDownload);

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemAuthor;
    listItemAuthor.typeValue=ItemType::Label;
    listItemAuthor.textValue=data->author;
    listItemAuthor.fixWidth=100;
    listItemAuthor.iconValue=0;
    listItemAuthor.styleName="lbl-light";
    listItemList.append(listItemAuthor);

    OgmListHelper::addListItem(_widgetList, "btnDataRefactorList|"+data->id, style, "btn", listItemList);

    //connect
    QToolButton *btnFavor=_widgetList->findChild<QToolButton*>(listItemBtnFavor.objectName);
    connect(btnFavor, &QToolButton::clicked, [=](){
        emit signalAddFavorSidebar(data->serverId, data->id, "DataRefactor");
    });

    QToolButton *btnRun=_widgetList->findChild<QToolButton*>(listItemBtnDownload.objectName);
    connect(btnRun, &QToolButton::clicked, [=](){
        OgmPopWidget *pop=new OgmPopWidget("ChooseRefactorMethod");
        pop->changeChooseRefactorMethod(_serverId, data->id);
        connect(pop, &OgmPopWidget::signalSwitchPage, [=](QString pageType){
            emit signalSwitchPage(pageType);
        });
        connect(pop, &OgmPopWidget::signalChangeDataRefactorConfigUI, [=](QString serverId, QString refactorId, QString methodId){
            emit signalChangeDataRefactorTaskConfigUI(serverId, refactorId, methodId);
        });
        pop->show();
    });
}

void OgmListWidget::addOneDataMethodOnUI(DataRefactorMethod *dataMethod, QString style)
{
    QList<LISTCHILD> list;

    LISTCHILD listName=OgmListHelper::createLableChild("lbl-lightdark", 220, dataMethod->name);
    list.append(listName);

    LISTCHILD listSpaceA=OgmListHelper::createSpaceChild();
    list.append(listSpaceA);

    LISTCHILD listRun=OgmListHelper::createButtonChild(0xf04b, "btnRefactorMethodRun|"+dataMethod->name, "btn-light", "choose this method");
    list.append(listRun);

    LISTCHILD listSpaceB=OgmListHelper::createSpaceChild();
    list.append(listSpaceB);

    LISTCHILD listDesc=OgmListHelper::createLableChild("lbl-light", 120, dataMethod->description);
    list.append(listDesc);

    OgmListHelper::addListItem(_widgetList, "btnRefactorMethod"+dataMethod->name, style, "btn", list);

    //btn function
    QToolButton *btnRun=_widgetList->findChild<QToolButton*>("btnRefactorMethodRun|"+dataMethod->name);
    connect(btnRun, &QToolButton::clicked, [=](){
        emit signalSwitchPage("DataRefactorTaskConfig");
        emit signalChangeDataRefactorTaskConfigUI(dataMethod->serverId, dataMethod->refactorId, dataMethod->name);
    });
}

void OgmListWidget::addOneModelServiceOnUI(ModelService *model, QString style)
{
    QList<LISTCHILD> listItemList;

    LISTCHILD listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=model->mName;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTCHILD listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataDetail|"+model->id;
    listItemList.append(listItemBtnDetail);

    LISTCHILD listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor group";
    listItemBtnFavor.objectName="btnModelFavor|"+model->id;
    listItemList.append(listItemBtnFavor);

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemAuthor;
    listItemAuthor.typeValue=ItemType::Label;
    listItemAuthor.textValue=model->userName;
    listItemAuthor.fixWidth=100;
    listItemAuthor.iconValue=0;
    listItemAuthor.styleName="lbl-light";
    listItemList.append(listItemAuthor);

    OgmListHelper::addListItem(_widgetList, "btnModelList|"+model->id, style, "btn", listItemList);

    //connect
    QToolButton *btn=_widgetList->findChild<QToolButton*>(listItemBtnFavor.objectName);
    connect(btn, &QToolButton::clicked, [=](){
        emit signalAddFavorSidebar(model->serverId, model->id, "Model");
    });
}

void OgmListWidget::addOneDataFileOnUI(DataFile *file, QString style)
{
    _fileId=file->id;

    QList<LISTCHILD> listItemList;

    if(file->type=="file"){
        LISTCHILD listItemDataIcon;
        listItemDataIcon.typeValue=ItemType::Label;
        listItemDataIcon.iconValue=0xf016;
        listItemDataIcon.styleName="lbl-lightdark";
        listItemDataIcon.fixWidth=0;
        listItemList.append(listItemDataIcon);

        LISTCHILD listItemDataName;
        listItemDataName.typeValue=ItemType::Label;
        listItemDataName.textValue=file->name;
        listItemDataName.iconValue=0;
        listItemDataName.styleName="lbl-lightdark";
        listItemDataName.fixWidth=220;
        listItemList.append(listItemDataName);
    }
    else if(file->type=="folder"){
        LISTCHILD listItemFile;
        listItemFile.typeValue=ItemType::ToolButtonWithText;
        listItemFile.textValue=file->name;
        listItemFile.iconValue=0xf115;
        listItemFile.styleName="btn-lightdark";
        listItemFile.objectName="btnDataFileName|"+file->id;
        listItemFile.fixWidth=238;
        listItemFile.isCursorChange=true;
        listItemList.append(listItemFile);
    }

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTCHILD listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf019;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="download file";
    listItemBtnDownload.objectName="btnDataFileDownload|"+file->id;
    listItemList.append(listItemBtnDownload);

    LISTCHILD listItemBtnDataFileReName;
    listItemBtnDataFileReName.typeValue=ItemType::ToolButton;
    listItemBtnDataFileReName.iconValue=0xf040;
    listItemBtnDataFileReName.styleName="btn-light";
    listItemBtnDataFileReName.toolTipValue="rename file";
    listItemBtnDataFileReName.objectName="btnDataFileRename|"+file->id;
    listItemList.append(listItemBtnDataFileReName);

    LISTCHILD listItemBtnDataFileDelete;
    listItemBtnDataFileDelete.typeValue=ItemType::ToolButton;
    listItemBtnDataFileDelete.iconValue=0xf1f8;
    listItemBtnDataFileDelete.styleName="btn-light";
    listItemBtnDataFileDelete.toolTipValue="delete file";
    listItemBtnDataFileDelete.objectName="btnDataFileDelete|"+file->id;
    listItemList.append(listItemBtnDataFileDelete);

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemFileSize;
    listItemFileSize.typeValue=ItemType::Label;
    if(file->size==""){
        listItemFileSize.textValue="Folder";
    }
    else
        listItemFileSize.textValue=file->size;
    listItemFileSize.fixWidth=80;
    listItemFileSize.iconValue=0;
    listItemFileSize.styleName="lbl-light";
    listItemList.append(listItemFileSize);

    if(file->type=="file"){
        if(_listType=="FileCheck"){
             OgmListHelper::addListItem(_widgetList, "btnDataFileList|"+file->id+"|"+file->name+"|"+file->parentId, style, "btn", listItemList, true);
        }
        else
             OgmListHelper::addListItem(_widgetList, "btnDataFileList|"+file->id+"|"+file->name+"|"+file->parentId, style, "btn", listItemList, false);

    }
    else if(file->type=="folder"){
        OgmListHelper::addListItem(_widgetList, "btnDataFileList|"+file->id+"|"+file->name+"|"+file->parentId, style, "btn", listItemList);
    }

    //btn function
    QToolButton *btnFolder=_widgetList->findChild<QToolButton*>("btnDataFileName|"+file->id);
    connect(btnFolder, &QToolButton::clicked, [=](){
        QList<DataFile*> fileList=_dataFileBLL.data()->getFilesByParent(_serverId, file->id);
        changeFileListUI(fileList, _listType);
        emit signalAddFolderOnFileLink(file->id, file->name);
    });

    QToolButton *btnDelete=_widgetList->findChild<QToolButton*>("btnDataFileDelete|"+file->id);
    connect(btnDelete, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("DeleteFile");
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varIsDelete){
            bool isDelete=varIsDelete.toBool();
            if(isDelete){
                _dataFileBLL.data()->deleteData(_serverId, file->id, file->type);

                changeFileListUIByParentId(_serverId, file->parentId, _listType);
            }
        });
        popWidget->show();
    });

    QToolButton *btnFile=_widgetList->findChild<QToolButton*>("btnDataFileList|"+file->id+"|"+file->name);
    connect(btnFile, &QToolButton::clicked, [=](){
        setAllBtnUnCheck();
        btnFile->setChecked(true);
    });
}

void OgmListWidget::addOneTaskOnUI(Task *task, QString style)
{
    QList<LISTCHILD> listItemList;

    LISTCHILD listItemNameIcon;
    listItemNameIcon.typeValue=ItemType::Label;
    if(task->type=="Model"){
        listItemNameIcon.iconValue=0xf0a3;
    }
    else if(task->type=="DataMap"){
        listItemNameIcon.iconValue=0xf0e8;
    }
    else if(task->type=="DataRefactor"){
        listItemNameIcon.iconValue=0xf085;
    }
    listItemNameIcon.styleName="lbl-light";
    listItemNameIcon.fixWidth=0;
    listItemList.append(listItemNameIcon);

    LISTCHILD listItemName;
    listItemName.typeValue=ItemType::Label;
    listItemName.textValue=task->name;
    listItemName.iconValue=0;
    listItemName.styleName="lbl-lightdark";
    listItemName.fixWidth=220;
    listItemList.append(listItemName);

    LISTCHILD listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    if(task->runstate=="ToRun"){
        LISTCHILD listItemBtnRun;
        listItemBtnRun.typeValue=ItemType::ToolButton;
        listItemBtnRun.iconValue=0xf04b;
        listItemBtnRun.styleName="btn-light";
        listItemBtnRun.toolTipValue="run this task";
        listItemBtnRun.objectName="btnTaskCal|"+task->uid;
        listItemList.append(listItemBtnRun);
    }

    LISTCHILD listItemBtnEdit;
    listItemBtnEdit.typeValue=ItemType::ToolButton;
    listItemBtnEdit.iconValue=0xf040;
    listItemBtnEdit.styleName="btn-light";
    listItemBtnEdit.toolTipValue="edit task";
    listItemBtnEdit.objectName="btnTaskEdit|"+task->uid;
    listItemList.append(listItemBtnEdit);

    LISTCHILD listItemBtnDelete;
    listItemBtnDelete.typeValue=ItemType::ToolButton;
    listItemBtnDelete.iconValue=0xf1f8;
    listItemBtnDelete.styleName="btn-light";
    listItemBtnDelete.toolTipValue="delete task";
    listItemBtnDelete.objectName="btnTaskDel|"+task->uid;
    listItemList.append(listItemBtnDelete);

    if(task->runstate=="Finish"){
        LISTCHILD listItemBtnVisual;
        listItemBtnVisual.typeValue=ItemType::ToolButton;
        listItemBtnVisual.iconValue=0xf0ac;
        listItemBtnVisual.styleName="btn-light";
        listItemBtnVisual.toolTipValue="view result";
        listItemBtnVisual.objectName="btnTaskView|"+task->uid;
        listItemList.append(listItemBtnVisual);
    }

    LISTCHILD listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTCHILD listItemType;
    listItemType.typeValue=ItemType::Label;
    listItemType.textValue=task->type;
    listItemType.iconValue=0;
    listItemType.styleName="lbl-lightdark";
    listItemType.fixWidth=100;
    listItemList.append(listItemType);

    LISTCHILD listItemSpaceC=OgmListHelper::createSpaceChild();
    listItemList.append(listItemSpaceC);

    LISTCHILD listItemTime;
    listItemTime.typeValue=ItemType::Label;
    listItemTime.textValue=task->createTime;
    listItemTime.iconValue=0;
    listItemTime.styleName="lbl-lightdark";
    listItemTime.fixWidth=80;
    listItemList.append(listItemTime);

    OgmListHelper::addListItem(_widgetList, "btnTaskList|"+task->uid, style, "btn", listItemList);

    //btn function
    QToolButton *btnTask=_widgetList->findChild<QToolButton*>("btnTaskCal|"+task->uid);


    connect(btnTask, &QToolButton::clicked, [=](){
        //change run state
        _taskBLL.data()->changeTaskRunState(task->uid, "Running");

        addRunningTaskOnUI(task);
        changeTaskListUI(_taskBLL.data()->getAllTask(), "ToRun");

        //synchronous untile task finish
        if(task->type=="DataMap"){
            _taskBLL.data()->runDatamapTask(task);
        }
        else if(task->type=="DataRefactor"){
            _taskBLL.data()->runDataRefactorTask(task);
        }

        for(int i=0; i<_widgetList->layout()->count(); ++i){
            QWidget *widgetPro=_widgetList->layout()->itemAt(i)->widget();
            if(widgetPro){
                if(widgetPro->accessibleDescription()=="progressBar"){
                    OgmProgressBar *pro=qobject_cast<OgmProgressBar*>(widgetPro);
                    if(pro->getTaskId()==task->uid){
                        pro->setIsFinished(true);
                    }
                }
            }
        }
    });
}

void OgmListWidget::addRunningTaskOnUI(Task *task)
{
    OgmProgressBar *proBar=new OgmProgressBar(task->uid);
    proBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    proBar->setFixedHeight(35);
    connect(proBar, &OgmProgressBar::signalProgressBarFinish, [=](){
        _taskBLL.data()->changeTaskRunState(proBar->getTaskId(), "Finish");
        _widgetList->layout()->removeWidget(proBar);
        delete proBar;

        changeTaskListUI(_taskBLL.data()->getAllTask(), "Running");
    });

    _widgetList->layout()->addWidget(proBar);

    QHBoxLayout *layoutTask=new QHBoxLayout();
    proBar->setLayout(layoutTask);

    QLabel *lblName=new QLabel();
    lblName->setText(task->name);
    lblName->setWindowTitle("lbl-lightdark");
    lblName->setFixedWidth(220);
    layoutTask->addWidget(lblName);
    layoutTask->addStretch();

    QToolButton *btnDel=new QToolButton();
    OgmUiHelper::Instance()->setIcon(btnDel, QChar(0xf1f8));
    btnDel->setObjectName("btnTaskDel|"+task->uid);
    btnDel->setWindowTitle("btn-light");
    btnDel->setToolTip("delete task");
    layoutTask->addWidget(btnDel);

    layoutTask->addStretch();

    QLabel *lblTaskTag=new QLabel();
    lblTaskTag->setText("taskTag");
    lblTaskTag->setFixedWidth(100);
    lblTaskTag->setWindowTitle("lbl-light");
    layoutTask->addWidget(lblTaskTag);
    layoutTask->addStretch();

    QLabel *lblTaskTime=new QLabel();
    lblTaskTime->setText(task->createTime);
    lblTaskTime->setFixedWidth(80);
    lblTaskTime->setWindowTitle("lbl-light");
    layoutTask->addWidget(lblTaskTime);
    layoutTask->addSpacing(5);
}

void OgmListWidget::addOneServerOnUI(ModelServer *modelServer, QString style)
{
    QList<LISTCHILD> list;

    LISTCHILD listName=OgmListHelper::createLableChild("lbl-lightdark", 220, modelServer->name);
    list.append(listName);

    LISTCHILD listSpaceA=OgmListHelper::createSpaceChild();
    list.append(listSpaceA);

    LISTCHILD listRun=OgmListHelper::createButtonChild(0xf05a, "btnModelServerDetail|"+modelServer->id, "btn-light", "server detail information");
    list.append(listRun);

    LISTCHILD listSpaceB=OgmListHelper::createSpaceChild();
    list.append(listSpaceB);

    LISTCHILD listDesc=OgmListHelper::createLableChild("lbl-light", 120, modelServer->location);
    list.append(listDesc);

    OgmListHelper::addListItem(_widgetList, "btnListModelServer"+modelServer->id, style, "btn", list);

    //btn function
//    QToolButton *btnRun=_widgetList->findChild<QToolButton*>("btnRefactorMethodRun|"+dataMethod->name);
//    connect(btnRun, &QToolButton::clicked, [=](){
//        emit signalSwitchPage("DataRefactorTaskConfig");
//        emit signalChangeDataRefactorTaskConfigUI(dataMethod->serverId, dataMethod->refactorId, dataMethod->name);
//    });
}

void OgmListWidget::addOneServerOnUI(DataServer *dataServer, QString style)
{
    QList<LISTCHILD> list;

    LISTCHILD listName=OgmListHelper::createLableChild("lbl-lightdark", 220, dataServer->name);
    list.append(listName);

    LISTCHILD listSpaceA=OgmListHelper::createSpaceChild();
    list.append(listSpaceA);

    LISTCHILD listRun=OgmListHelper::createButtonChild(0xf05a, "btnModelServerDetail|"+dataServer->id, "btn-light", "server detail information");
    list.append(listRun);

    LISTCHILD listSpaceB=OgmListHelper::createSpaceChild();
    list.append(listSpaceB);

    LISTCHILD listDesc=OgmListHelper::createLableChild("lbl-light", 120, dataServer->location);
    list.append(listDesc);

    OgmListHelper::addListItem(_widgetList, "btnListModelServer"+dataServer->id, style, "btn", list);
}

void OgmListWidget::initTurnPage(QString turnPageType)
{
    QHBoxLayout *layoutTurnPage=qobject_cast<QHBoxLayout*>(_widgetTurnPage->layout());

    QLabel *lblPageIndex=new QLabel(_widgetTurnPage);
    lblPageIndex->setObjectName("lblPageIndex");
    lblPageIndex->setText(QString::number(_currentPageIndex+1));
    lblPageIndex->setWindowTitle("lbl-normal");

    QToolButton *btnPrevPage=new QToolButton(_widgetTurnPage);
    OgmUiHelper::Instance()->setIcon(btnPrevPage, QChar(0xf053));
    connect(btnPrevPage, &QToolButton::clicked, this, &OgmListWidget::btnTurnPageClicked);
    btnPrevPage->setObjectName("btnPrevPage");
    btnPrevPage->setWindowTitle("btn-normal");  
    if(turnPageType=="firstFull")
        btnPrevPage->setEnabled(false);

    QToolButton *btnNextPage=new QToolButton(_widgetTurnPage);
    OgmUiHelper::Instance()->setIcon(btnNextPage, QChar(0xf054));
    connect(btnNextPage, &QToolButton::clicked, this, &OgmListWidget::btnTurnPageClicked);
    btnNextPage->setObjectName("btnNextPage");
    btnNextPage->setWindowTitle("btn-normal");
    if(turnPageType=="last"){
        btnNextPage->setEnabled(false);
    }
    if(turnPageType=="first"){
        btnPrevPage->setEnabled(false);
        btnNextPage->setEnabled(false);
    }

    layoutTurnPage->addStretch();
    layoutTurnPage->addWidget(btnPrevPage);
    layoutTurnPage->addSpacing(30);
    layoutTurnPage->addWidget(lblPageIndex);
    layoutTurnPage->addSpacing(30);
    layoutTurnPage->addWidget(btnNextPage);
    layoutTurnPage->addStretch();
}

void OgmListWidget::btnTurnPageClicked()
{
    QToolButton *btn=(QToolButton*)sender();
    if(btn->objectName()=="btnPrevPage")
        _currentPageIndex--;
    else if(btn->objectName()=="btnNextPage")
        _currentPageIndex++;

    if(_listType=="Model"){
        changeModelListUIByPage(_serverId, _currentPageIndex);
    }
    else if(_listType=="Data"){
        changeDataListUI(_serverId, "Data", _currentPageIndex);
    }

}

void OgmListWidget::popChooseDataMethodWidget()
{
    OgmPopWidget *widgetPop=new OgmPopWidget("ChooseFile");
    widgetPop->show();
    connect(widgetPop, &OgmPopWidget::signalOperationResult, [=](QVariant varFileInfo){
//        QStringList strList=varFileInfo.toStringList();
//        _task->getDataMapTaskConfig()->inputId=strList[0];
//        _task->getDataMapTaskConfig()->inputFilename=strList[1];
    });
}

void OgmListWidget::setAllBtnUnCheck()
{
    QList<QToolButton*> btnList= _widgetList->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0; i<btnList.count(); ++i){
        btnList[i]->setChecked(false);
    }
}

QString OgmListWidget::getServerId()
{
    return _serverId;
}

















