#include "ogmservertopwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmUI/ogmpopwidget.h"

#include <QDateTime>
#include <QFileDialog>

OgmServerTopWidget::OgmServerTopWidget(QString widgetType, QWidget *parent)
    : QWidget(parent)
    ,_ui(new Ui::OgmTopWidget)
{
    _ui->setupUi(this);

    _dServerBLL=QSharedPointer<DataServerBLL>(new DataServerBLL());
    _mServerBLL=QSharedPointer<ModelServerBLL>(new ModelServerBLL);
    _favorBLL=QSharedPointer<FavorBLL>(new FavorBLL);
    _dataFileBLL=QSharedPointer<DataFileBll>(new DataFileBll);

    if(widgetType=="Model")
        initModelWidget();
    else if(widgetType=="Data")
        initDataWidget();
    else if(widgetType=="Favor")
        initFavorWidget();
    else if(widgetType=="File")
        initFileWidget();
}

void OgmServerTopWidget::changeDataServer(QString serverId)
{
    //content
    _id=serverId;
    DataServer *server=_dServerBLL.data()->getServerId(serverId);

    _ui->lblName->setText(server->name);
    _ui->lblServerLocation->setText(server->location);
    if(!server->desc.isEmpty() || !server->desc.isNull() || server->desc!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(server->desc);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }
}

void OgmServerTopWidget::changeModelServer(QString serverId)
{
    //content
    _id=serverId;
    ModelServer *server=_mServerBLL.data()->getServerId(serverId);

    _ui->lblName->setText(server->name);
    _ui->lblServerLocation->setText(server->location);
    if(!server->desc.isEmpty() || !server->desc.isNull() || server->desc!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(server->desc);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }
}

void OgmServerTopWidget::changeFileManager(QString serverId)
{
    //content
    _id=serverId;

    DataServer *server=_dServerBLL.data()->getServerId(serverId);

    _ui->lblName->setText(server->name);
    _ui->lblServerLocation->setText(server->location);
    if(!server->desc.isEmpty() || !server->desc.isNull() || server->desc!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(server->desc);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }
}

void OgmServerTopWidget::changeFavorManager(QString favorId)
{
    _id=favorId;
    Favor *favor=_favorBLL.data()->getFavorGroupById(_id);

    _ui->lblName->setText(favor->name);

    if(!favor->des.isEmpty() || !favor->des.isNull() || favor->des!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(favor->des);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }
}

QString OgmServerTopWidget::getCurrentId()
{
    return _id;
}

QString OgmServerTopWidget::getCurrentFileId()
{
    return _currentFileId;
}

void OgmServerTopWidget::initModelWidget()
{
    //style
    OgmUiHelper::Instance()->setIcon(_ui->lblNameIcon, QChar(0xf17a));
    OgmUiHelper::Instance()->setIcon(_ui->lblServerLocationIcon, QChar(0xf041));
    OgmUiHelper::Instance()->setIcon(_ui->lblIcon, QChar(0xf0ac));
    OgmUiHelper::Instance()->setIcon(_ui->lblTopModelIcon, QChar(0xf0ac));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDes, 0xf05a, "detail", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDefault, 0xf085, "default server", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerChange, 0xf0ec, "switch server", 6);

    _ui->widgetFavorTopBtnGroup->setVisible(false);

    _ui->widgetDataServerBtnGroup->setVisible(false);
    _ui->widgetFavorBtnGroup->setVisible(false);

    _ui->widgetFileManagerTool->setVisible(false);

    //function
    connect(_ui->btnServerChange, &QToolButton::clicked, [=](){
        emit signalChangeModelServer();
    });
}

void OgmServerTopWidget::initDataWidget()
{
    //style
    OgmUiHelper::Instance()->setIcon(_ui->lblNameIcon, QChar(0xf17a));
    OgmUiHelper::Instance()->setIcon(_ui->lblServerLocationIcon, QChar(0xf041));
    OgmUiHelper::Instance()->setIcon(_ui->lblIcon, QChar(0xf1c0));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDes, 0xf05a, "detail", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDefault, 0xf085, "default server", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerChange, 0xf0ec, "switch server", 6);

    //visible
    _ui->widgetFavorTopBtnGroup->setVisible(false);

    _ui->widgetModelBtnGroup->setVisible(false);
    _ui->widgetFavorBtnGroup->setVisible(false);

    _ui->widgetFileManagerTool->setVisible(false);

    //function
    connect(_ui->btnServerDataPage, &QToolButton::clicked, [=](){
        emit signalChangeDataList(_id);
        //emit signalSwitchPage("DataList");
    });
    connect(_ui->btnServerDataMappingPage, &QToolButton::clicked, [=](){
        emit signalChangeDataMappingList(_id);
        //emit signalSwitchPage("DataList");
    });
    connect(_ui->btnServerDataRefactorPage, &QToolButton::clicked, [=](){
        emit signalChangeDataRefactorList(_id);
        //emit signalSwitchPage("DataList");
    });
}

void OgmServerTopWidget::initFavorWidget()
{
    OgmUiHelper::Instance()->setIcon(_ui->lblIcon, QChar(0xf004));
    OgmUiHelper::Instance()->setIcon(_ui->lblNameIcon, QChar(0xf004));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnTopNewFavor, 0xf055, "new", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnTopDeleteFavor, 0xf1f8, "delete", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnTopSwitchFavor, 0xf0ec, "switch group", 6);

    _ui->widgetServerTopBtnGroup->setVisible(false);

    _ui->widgetModelBtnGroup->setVisible(false);
    _ui->widgetDataServerBtnGroup->setVisible(false);

    _ui->widgetFileManagerTool->setVisible(false);

    //favor top function
    connect(_ui->btnTopSwitchFavor, &QToolButton::clicked, [=](){
        emit signalChangeFavor();
    });

    //favor function
    connect(_ui->btnFavorToolModel, &QToolButton::clicked, [=](){
        Favor *favor=_favorBLL.data()->getFavorGroupById(_id);
        QList<ModelService*> msList=_favorBLL.data()->favor2modelServiceList(favor);

        emit signalChangeModelListByList(msList);
    });
    connect(_ui->btnFavorToolData, &QToolButton::clicked, [=](){
        Favor *favor=_favorBLL.data()->getFavorGroupById(_id);
        QList<DataService*> dsList=_favorBLL.data()->favor2dataServiceList(favor);

        emit signalChangeDataListByList(dsList);
    });
    connect(_ui->btnFavorToolDataMapping, &QToolButton::clicked, [=](){
        Favor *favor=_favorBLL.data()->getFavorGroupById(_id);
        QList<DataMapping*> mappingList=_favorBLL.data()->favor2dataMappingList(favor);

        emit signalChangeDataMappingListByList(mappingList);
    });
    connect(_ui->btnFavorToolDataRefactor, &QToolButton::clicked, [=](){
        Favor *favor=_favorBLL.data()->getFavorGroupById(_id);
        QList<DataRefactor*> refactorList=_favorBLL.data()->favor2dataRefactorList(favor);

        emit signalChangeDataRefactorListByList(refactorList);
    });
}

void OgmServerTopWidget::initFileWidget()
{
    _currentFileId="-1";

    OgmUiHelper::Instance()->setIcon(_ui->lblIcon, QChar(0xf07b));
    OgmUiHelper::Instance()->setIcon(_ui->lblNameIcon, QChar(0xf07b));
    OgmUiHelper::Instance()->setIcon(_ui->lblTopFileIcon, QChar(0xf07b));
    OgmUiHelper::Instance()->setIcon(_ui->lblServerLocationIcon, QChar(0xf041));

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDes, 0xf05a, "detail", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerDefault, 0xf085, "default server", 6);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnServerChange, 0xf0ec, "switch server", 6);

    OgmUiHelper::Instance()->setButtonIcon(_ui->btnUploadFile, 0xf093, "upload", 7);
    OgmUiHelper::Instance()->setButtonIcon(_ui->btnNewFolder, 0xf07b, "new folder", 7);


    //visible
    _ui->widgetFavorTopBtnGroup->setVisible(false);

    _ui->widgetModelBtnGroup->setVisible(false);
    _ui->widgetDataServerTool->setVisible(false);


    //private param init
    QToolButton *btnFileLinkAll=new QToolButton(_ui->widgetFileLink);
    btnFileLinkAll->setObjectName("btnFileLink|All");
    btnFileLinkAll->setText("All");
    btnFileLinkAll->setWindowTitle("btn-split");
    btnFileLinkAll->setAccessibleDescription("-1");
    connect(btnFileLinkAll, &QToolButton::clicked, [=](){
        _currentFileId="-1";
        emit signalChangeDataFileByParentId(_id, "-1");
        removeNextAllFileLink("-1", "All");
    });
    _ui->widgetFileLink->layout()->addWidget(btnFileLinkAll);
    _fileLinkList.append(btnFileLinkAll->objectName());

    //function
    connect(_ui->btnNewFolder, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("NewFile");
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant result){
            QString folderName=result.toString();
            QString addTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");

            _dataFileBLL.data()->addFolder(_id, _currentFileId, folderName, addTime);

            //change list
            emit signalChangeDataFileByParentId(_id, _currentFileId);
        });
        popWidget->show();
    });
    connect(_ui->btnUploadFile, &QToolButton::clicked, [=](){
       QString filePath=QFileDialog::getOpenFileName(this, "choose upload data");
       if(filePath==QString::null)
           return;
       _dataFileBLL.data()->uploadFile(_id, _currentFileId, filePath);
    });
}

void OgmServerTopWidget::addOneFileLinkOnUI(QString fileId, QString fileName)
{
    _currentFileId=fileId;

    QLabel *lblLinkIcon=new QLabel(_ui->widgetFileLink);
    lblLinkIcon->setObjectName("lblFileLink|"+fileName);
    lblLinkIcon->setText(">");
    lblLinkIcon->setWindowTitle("lbl-split");
    _ui->widgetFileLink->layout()->addWidget(lblLinkIcon);
    _fileLinkList.append(lblLinkIcon->objectName());

    QToolButton *btnLinkIcon=new QToolButton(_ui->widgetFileLink);
    btnLinkIcon->setObjectName("btnFileLink|"+fileName);
    btnLinkIcon->setText(fileName);
    btnLinkIcon->setWindowTitle("btn-split");
    btnLinkIcon->setAccessibleDescription(fileId);
    connect(btnLinkIcon, &QToolButton::clicked, [=](){
        emit signalChangeDataFileByParentId(_id, fileId);
        removeNextAllFileLink(fileId, fileName);
    });

    _ui->widgetFileLink->layout()->addWidget(btnLinkIcon);
    _fileLinkList.append(btnLinkIcon->objectName());
}

void OgmServerTopWidget::removeNextAllFileLink(QString fileId, QString fileName)
{
    int index;
    for(int i=0; i<_fileLinkList.count(); ++i){
        if(fileName==_fileLinkList[i].split("|")[1]){
            index=i;
        }
    }

    int count=_fileLinkList.count()-1;
    for(count; count>index; --count){
//        if(_fileLinkList.at(count)->contains("lbl")){
            QWidget *widgetDel=_ui->widgetFileLink->findChild<QWidget*>(_fileLinkList.at(count));
            _ui->widgetFileLink->layout()->removeWidget(widgetDel);
            delete widgetDel;
            _fileLinkList.removeAt(count);
    }
}
