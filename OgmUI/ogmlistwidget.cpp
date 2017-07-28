#include "ogmlistwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"

#include "OgmUI/ogmpopwidget.h"

#include <QLayout>
#include <QScrollArea>

OgmListWidget::OgmListWidget(QWidget *parent) : QWidget(parent)
{
    _modelServiceBLL=  QSharedPointer<ModelServiceBLL>(new ModelServiceBLL);
    _dataServiceBLL=  QSharedPointer<DataServiceBLL>(new DataServiceBLL);
    _dataMappingBLL=  QSharedPointer<DataMappingBLL>(new DataMappingBLL);
    _dataRefactorBLL= QSharedPointer<DataRefactorBLL>(new DataRefactorBLL);
    _dataFileBLL=     QSharedPointer<DataFileBll>(new DataFileBll);

    initWidget();
}

void OgmListWidget::changeModelListUI(QString serverId)
{
    QList<ModelService*> modelList=_modelServiceBLL.data()->getAllModelService(serverId);
    changeModelListUI(modelList);
}

void OgmListWidget::changeModelListUI(QList<ModelService *> modelList)
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(_widgetList->layout()->count()>0){
        QWidget *widgetDel= _widgetList->layout()->itemAt(0)->widget();
        _widgetList->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    int modelCount=modelList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    //add data widget
    if(modelCount==0){
        layoutList->addStretch();
    }
    else if(modelCount<=25){
        for(int i=0; i<modelCount; ++i){
            if(i%2==0){
                addOneModelServiceOnUI(modelList[i], "btn-model-dark");
            }
            else{
                addOneModelServiceOnUI(modelList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();
    }
    else{
        for(int i=0; i<25; ++i){
            if(i%2==0){
                addOneModelServiceOnUI(modelList[i], "btn-model-dark");
            }
            else{
                addOneModelServiceOnUI(modelList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        //build turn page ui
        initTurnPage();
    }
}

void OgmListWidget::changeDataListUI(QList<DataService *> dataList)
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(_widgetList->layout()->count()>0){
        QWidget *widgetDel= _widgetList->layout()->itemAt(0)->widget();
        _widgetList->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    int dataCount=dataList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    //add data widget
    if(dataCount==0){
        layoutList->addStretch();
    }
    else if(dataCount<=25){
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataOnUI(dataList[i], "btn-model-dark");
            }
            else{
                addOneDataOnUI(dataList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();
    }
    else{
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataOnUI(dataList[i], "btn-model-dark");
            }
            else{
                addOneDataOnUI(dataList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        //build turn page ui
        initTurnPage();
    }
}

void OgmListWidget::changeDataListUI(QList<DataMapping *> dataMappingList)
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(_widgetList->layout()->count()>0){
        QWidget *widgetDel= _widgetList->layout()->itemAt(0)->widget();
        _widgetList->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    int dataCount=dataMappingList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    //add data widget
    if(dataCount==0){
        layoutList->addStretch();
    }
    else if(dataCount<=25){
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataMappingOnUI(dataMappingList[i], "btn-model-dark");
            }
            else{
                addOneDataMappingOnUI(dataMappingList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();
    }
    else{
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataMappingOnUI(dataMappingList[i], "btn-model-dark");
            }
            else{
                addOneDataMappingOnUI(dataMappingList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        //build turn page ui
        initTurnPage();
    }
}

void OgmListWidget::changeDataListUI(QList<DataRefactor *> dataRefactorList)
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(_widgetList->layout()->count()>0){
        QWidget *widgetDel= _widgetList->layout()->itemAt(0)->widget();
        _widgetList->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    int dataCount=dataRefactorList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    //add data widget
    if(dataCount==0){
        layoutList->addStretch();
    }
    else if(dataCount<=25){
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataRefactorOnUI(dataRefactorList[i], "btn-model-dark");
            }
            else{
                addOneDataRefactorOnUI(dataRefactorList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();
    }
    else{
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataRefactorOnUI(dataRefactorList[i], "btn-model-dark");
            }
            else{
                addOneDataRefactorOnUI(dataRefactorList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        //build turn page ui
        initTurnPage();
    }
}

void OgmListWidget::changeDataListUI(QString serverId, QString type)
{
    _dataServerId=serverId;

    if(type=="Data"){
        QList<DataService*> dataList=_dataServiceBLL.data()->getAllData(serverId);
        changeDataListUI(dataList);
    }
    else if(type=="DataMapping"){
        QList<DataMapping*> dataMappingList=_dataMappingBLL.data()->getAllDataMapping(serverId);
        changeDataListUI(dataMappingList);
    }
    else if(type=="DataRefactor"){
        QList<DataRefactor*> dataRefactorList=_dataRefactorBLL.data()->getAllDataRefactor(serverId);
        changeDataListUI(dataRefactorList);
    }
}

void OgmListWidget::changeFileListUI(QList<DataFile *> dataFileList)
{
    //clear list
    while (_widgetTurnPage->layout()->count()>0) {
        QWidget *widgetDel=_widgetTurnPage->layout()->itemAt(0)->widget();
        _widgetTurnPage->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(_widgetList->layout()->count()>0){
        QWidget *widgetDel= _widgetList->layout()->itemAt(0)->widget();
        _widgetList->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }

    int dataCount=dataFileList.count();
    QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

    //add data widget
    if(dataCount==0){
        layoutList->addStretch();
    }
    else if(dataCount<=25){
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataFileOnUI(dataFileList[i], "btn-model-dark");
            }
            else{
                addOneDataFileOnUI(dataFileList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();
    }
    else{
        for(int i=0; i<dataCount; ++i){
            if(i%2==0){
                addOneDataFileOnUI(dataFileList[i], "btn-model-dark");
            }
            else{
                addOneDataFileOnUI(dataFileList[i], "btn-model-light");
            }
        }
        layoutList->addStretch();

        //build turn page ui
        initTurnPage();
    }
}

void OgmListWidget::changeFileListUI(QString serverId, QString type)
{
    _dataServerId=serverId;

    if(type=="Data"){
        QList<DataFile*> fileList=_dataFileBLL.data()->getAllFiles(serverId);
        changeFileListUI(fileList);
    }
}

void OgmListWidget::changeFileListUIByParentId(QString serverId, QString parentId)
{
    _dataServerId=serverId;

    QList<DataFile*> fileList=_dataFileBLL.data()->getFilesByParent(serverId, parentId);
    changeFileListUI(fileList);
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
    QVariant varFileInfo(strList);
    return varFileInfo;
}

//void OgmListWidget::changeTaskListUI(QString taskType)
//{

//}

void OgmListWidget::changeTaskListUI(QList<Task *> taskList, QString taskRunState)
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
                if(taskRunState=="Running"){
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

    if(taskRunState!="Running"){
        int dataCount=taskList.count();
        QVBoxLayout *layoutList=qobject_cast<QVBoxLayout*>(_widgetList->layout());

        //add data widget
        if(dataCount==0){
            layoutList->addStretch();
        }
        else if(dataCount<=25){

            int num=0;

            for(int i=0; i<dataCount; ++i){
                if(taskList.at(i)->runstate==taskRunState){
                    if(num%2==0){
                        addOneTaskOnUI(taskList[i], "btn-model-dark", taskRunState);
                    }
                    else{
                        addOneTaskOnUI(taskList[i], "btn-model-light", taskRunState);
                    }
                }
                num++;
            }
            layoutList->addStretch();
        }
        else{

            int num=0;

            for(int i=0; i<dataCount; ++i){
                if(taskList.at(i)->runstate==taskRunState){
                    if(num%2==0){
                        addOneTaskOnUI(taskList[i], "btn-model-dark", taskRunState);
                    }
                    else{
                        addOneTaskOnUI(taskList[i], "btn-model-light", taskRunState);
                    }
                }
            }
            layoutList->addStretch();

            //build turn page ui
            initTurnPage();
        }
    }
}

void OgmListWidget::initWidget()
{
    _dataServerId="1001";

    QVBoxLayout *layoutMain=new QVBoxLayout();
    layoutMain->setContentsMargins(15, 3, 15, 15);
    this->setLayout(layoutMain);

    _widgetList=new QWidget(this);
    layoutMain->addWidget(_widgetList);

    QVBoxLayout *layoutList=new QVBoxLayout();
    layoutList->setMargin(0);
    layoutList->setSpacing(0);
    _widgetList->setLayout(layoutList);

    _widgetTurnPage=new QWidget(this);
    layoutMain->addWidget(_widgetTurnPage);

    QHBoxLayout *layoutTurnPage=new QHBoxLayout();
    _widgetTurnPage->setLayout(layoutTurnPage);
}

void OgmListWidget::addOneDataOnUI(DataService *data, QString style)
{
    QList<LISTITEM> listItemList;

    LISTITEM listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTITEM listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTITEM listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTITEM listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf019;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="download data";
    listItemBtnDownload.objectName="btnDataDownload|"+data->id;
    listItemList.append(listItemBtnDownload);

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemAuthor;
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
    QList<LISTITEM> listItemList;

    LISTITEM listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTITEM listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataMappingDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTITEM listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataMappingFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTITEM listItemBtnInvoke;
    listItemBtnInvoke.typeValue=ItemType::ToolButton;
    listItemBtnInvoke.iconValue=0xf04b;
    listItemBtnInvoke.styleName="btn-light";
    listItemBtnInvoke.toolTipValue="invoke data mapping service";
    listItemBtnInvoke.objectName="btnDataMappingInvoke|"+data->id;
    listItemList.append(listItemBtnInvoke);

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemAuthor;
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
        emit signalChangeDataMapTaskConfigUI(data->id);
    });
}

void OgmListWidget::addOneDataRefactorOnUI(DataRefactor *data, QString style)
{
    QList<LISTITEM> listItemList;

    LISTITEM listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=data->name;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTITEM listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataRefactorDetail|"+data->id;
    listItemList.append(listItemBtnDetail);

    LISTITEM listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor";
    listItemBtnFavor.objectName="btnDataRefactorFavor|"+data->id;
    listItemList.append(listItemBtnFavor);

    LISTITEM listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf019;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="download data";
    listItemBtnDownload.objectName="btnDataRefactorDownload|"+data->id;
    listItemList.append(listItemBtnDownload);

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemAuthor;
    listItemAuthor.typeValue=ItemType::Label;
    listItemAuthor.textValue=data->author;
    listItemAuthor.fixWidth=100;
    listItemAuthor.iconValue=0;
    listItemAuthor.styleName="lbl-light";
    listItemList.append(listItemAuthor);

    OgmListHelper::addListItem(_widgetList, "btnDataRefactorList|"+data->id, style, "btn", listItemList);

    //connect
    QToolButton *btn=_widgetList->findChild<QToolButton*>(listItemBtnFavor.objectName);
    connect(btn, &QToolButton::clicked, [=](){
        emit signalAddFavorSidebar(data->serverId, data->id, "DataRefactor");
    });
}

void OgmListWidget::addOneModelServiceOnUI(ModelService *model, QString style)
{
    QList<LISTITEM> listItemList;

    LISTITEM listItemDataName;
    listItemDataName.typeValue=ItemType::Label;
    listItemDataName.textValue=model->mName;
    listItemDataName.styleName="lbl-lightdark";
    listItemDataName.fixWidth=220;
    listItemDataName.iconValue=0;
    listItemList.append(listItemDataName);

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTITEM listItemBtnDetail;
    listItemBtnDetail.typeValue=ItemType::ToolButton;
    listItemBtnDetail.iconValue=0xf05a;
    listItemBtnDetail.styleName="btn-light";
    listItemBtnDetail.toolTipValue="detail information";
    listItemBtnDetail.objectName="btnDataDetail|"+model->id;
    listItemList.append(listItemBtnDetail);

    LISTITEM listItemBtnFavor;
    listItemBtnFavor.typeValue=ItemType::ToolButton;
    listItemBtnFavor.iconValue=0xf004;
    listItemBtnFavor.styleName="btn-light";
    listItemBtnFavor.toolTipValue="add to my favor group";
    listItemBtnFavor.objectName="btnModelFavor|"+model->id;
    listItemList.append(listItemBtnFavor);

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemAuthor;
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

    QList<LISTITEM> listItemList;

    if(file->type=="file"){
        LISTITEM listItemDataIcon;
        listItemDataIcon.typeValue=ItemType::Label;
        listItemDataIcon.iconValue=0xf016;
        listItemDataIcon.styleName="lbl-lightdark";
        listItemDataIcon.fixWidth=0;
        listItemList.append(listItemDataIcon);

        LISTITEM listItemDataName;
        listItemDataName.typeValue=ItemType::Label;
        listItemDataName.textValue=file->name;
        listItemDataName.iconValue=0;
        listItemDataName.styleName="lbl-lightdark";
        listItemDataName.fixWidth=220;
        listItemList.append(listItemDataName);
    }
    else if(file->type=="folder"){
        LISTITEM listItemFile;
        listItemFile.typeValue=ItemType::ToolButtonWithText;
        listItemFile.textValue=file->name;
        listItemFile.iconValue=0xf115;
        listItemFile.styleName="btn-lightdark";
        listItemFile.objectName="btnDataFileName|"+file->id;
        listItemFile.fixWidth=238;
        listItemFile.isCursorChange=true;
        listItemList.append(listItemFile);
    }

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    LISTITEM listItemBtnDownload;
    listItemBtnDownload.typeValue=ItemType::ToolButton;
    listItemBtnDownload.iconValue=0xf019;
    listItemBtnDownload.styleName="btn-light";
    listItemBtnDownload.toolTipValue="download file";
    listItemBtnDownload.objectName="btnDataFileDownload|"+file->id;
    listItemList.append(listItemBtnDownload);

    LISTITEM listItemBtnDataFileReName;
    listItemBtnDataFileReName.typeValue=ItemType::ToolButton;
    listItemBtnDataFileReName.iconValue=0xf040;
    listItemBtnDataFileReName.styleName="btn-light";
    listItemBtnDataFileReName.toolTipValue="rename file";
    listItemBtnDataFileReName.objectName="btnDataFileRename|"+file->id;
    listItemList.append(listItemBtnDataFileReName);

    LISTITEM listItemBtnDataFileDelete;
    listItemBtnDataFileDelete.typeValue=ItemType::ToolButton;
    listItemBtnDataFileDelete.iconValue=0xf1f8;
    listItemBtnDataFileDelete.styleName="btn-light";
    listItemBtnDataFileDelete.toolTipValue="delete file";
    listItemBtnDataFileDelete.objectName="btnDataFileDelete|"+file->id;
    listItemList.append(listItemBtnDataFileDelete);

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemFileSize;
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
        OgmListHelper::addListItem(_widgetList, "btnDataFileList|"+file->id+"|"+file->name, style, "btn", listItemList, true);
    }
    else if(file->type=="folder"){
        OgmListHelper::addListItem(_widgetList, "btnDataFileList|"+file->id+"|"+file->name, style, "btn", listItemList);
    }

    //btn function
    QToolButton *btnFolder=_widgetList->findChild<QToolButton*>("btnDataFileName|"+file->id);
    connect(btnFolder, &QToolButton::clicked, [=](){
        QList<DataFile*> fileList=_dataFileBLL.data()->getFilesByParent(_dataServerId, file->id);
        changeFileListUI(fileList);
        emit signalAddFolderOnFileLink(file->id, file->name);
    });

    QToolButton *btnDelete=_widgetList->findChild<QToolButton*>("btnDataFileDelete|"+file->id);
    connect(btnDelete, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("DeleteFile");
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varIsDelete){
            bool isDelete=varIsDelete.toBool();
            if(isDelete){
                _dataFileBLL.data()->deleteData(_dataServerId, file->id, file->type);

                changeFileListUIByParentId(_dataServerId, file->parentId);
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

void OgmListWidget::addOneTaskOnUI(Task *task, QString style, QString type)
{
    QList<LISTITEM> listItemList;

    LISTITEM listItemNameIcon;
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

    LISTITEM listItemName;
    listItemName.typeValue=ItemType::Label;
    listItemName.textValue=task->name;
    listItemName.iconValue=0;
    listItemName.styleName="lbl-lightdark";
    listItemName.fixWidth=220;
    listItemList.append(listItemName);

    LISTITEM listItemSpaceA;
    listItemSpaceA.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceA);

    if(type=="ToRun"){
        LISTITEM listItemBtnRun;
        listItemBtnRun.typeValue=ItemType::ToolButton;
        listItemBtnRun.iconValue=0xf04b;
        listItemBtnRun.styleName="btn-light";
        listItemBtnRun.toolTipValue="run this task";
        listItemBtnRun.objectName="btnTaskCal|"+task->uid;
        listItemList.append(listItemBtnRun);
    }

    LISTITEM listItemBtnEdit;
    listItemBtnEdit.typeValue=ItemType::ToolButton;
    listItemBtnEdit.iconValue=0xf040;
    listItemBtnEdit.styleName="btn-light";
    listItemBtnEdit.toolTipValue="edit task";
    listItemBtnEdit.objectName="btnTaskEdit|"+task->uid;
    listItemList.append(listItemBtnEdit);

    LISTITEM listItemBtnDelete;
    listItemBtnDelete.typeValue=ItemType::ToolButton;
    listItemBtnDelete.iconValue=0xf1f8;
    listItemBtnDelete.styleName="btn-light";
    listItemBtnDelete.toolTipValue="delete task";
    listItemBtnDelete.objectName="btnTaskDel|"+task->uid;
    listItemList.append(listItemBtnDelete);

    if(type=="Finish"){
        LISTITEM listItemBtnVisual;
        listItemBtnVisual.typeValue=ItemType::ToolButton;
        listItemBtnVisual.iconValue=0xf0ac;
        listItemBtnVisual.styleName="btn-light";
        listItemBtnVisual.toolTipValue="view result";
        listItemBtnVisual.objectName="btnTaskView|"+task->uid;
        listItemList.append(listItemBtnVisual);
    }

    LISTITEM listItemSpaceB;
    listItemSpaceB.typeValue=ItemType::SpaceItem;
    listItemList.append(listItemSpaceB);

    LISTITEM listItemType;
    listItemType.typeValue=ItemType::Label;
    listItemType.textValue=task->type;
    listItemType.iconValue=0;
    listItemType.styleName="lbl-lightdark";
    listItemType.fixWidth=80;
    listItemList.append(listItemType);

    LISTITEM listItemTime;
    listItemTime.typeValue=ItemType::Label;
    listItemTime.textValue=task->createTime;
    listItemTime.iconValue=0;
    listItemTime.styleName="lbl-lightdark";
    listItemTime.fixWidth=80;
    listItemList.append(listItemTime);

    OgmListHelper::addListItem(_widgetList, "btnTaskList|"+task->uid, style, "btn", listItemList);

    //btn function
//    QToolButton *btnFolder=_widgetList->findChild<QToolButton*>("btnDataFileName|"+file->id);
//    connect(btnFolder, &QToolButton::clicked, [=](){
//        QList<DataFile*> fileList=_dataFileBLL.data()->getFilesByParent(_dataServerId, file->id);
//        changeFileListUI(fileList);
//        emit signalAddFolderOnFileLink(file->id, file->name);
//    });
}

void OgmListWidget::initTurnPage()
{
    QHBoxLayout *layoutTurnPage=qobject_cast<QHBoxLayout*>(_widgetTurnPage->layout());

    layoutTurnPage->addStretch();

    QToolButton *btnPrevPage=new QToolButton(_widgetTurnPage);
    OgmUiHelper::Instance()->setIcon(btnPrevPage, QChar(0xf053));
    connect(btnPrevPage, SIGNAL(clicked()), this, SLOT(onTurnPage()));
    btnPrevPage->setObjectName("btnPrevPage");
    btnPrevPage->setWindowTitle("btn-normal");
    layoutTurnPage->addWidget(btnPrevPage);

    layoutTurnPage->addSpacing(30);

    QLabel *lblPageIndex=new QLabel(_widgetTurnPage);
    lblPageIndex->setObjectName("lblPageIndex");
    lblPageIndex->setText("1");
    lblPageIndex->setWindowTitle("lbl-normal");
    layoutTurnPage->addWidget(lblPageIndex);

    layoutTurnPage->addSpacing(30);

    QToolButton *btnNextPage=new QToolButton(_widgetTurnPage);
    OgmUiHelper::Instance()->setIcon(btnNextPage, QChar(0xf054));
    connect(btnNextPage, SIGNAL(clicked()), this, SLOT(onTurnPage()));
    btnNextPage->setObjectName("btnNextPage");
    btnNextPage->setWindowTitle("btn-normal");
    layoutTurnPage->addWidget(btnNextPage);

    layoutTurnPage->addStretch();
}

void OgmListWidget::btnTurnPageClicked()
{

}

void OgmListWidget::setAllBtnUnCheck()
{
    QList<QToolButton*> btnList= _widgetList->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(int i=0; i<btnList.count(); ++i){
        btnList[i]->setChecked(false);
    }
}
















