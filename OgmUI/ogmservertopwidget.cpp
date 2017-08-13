#include "ogmservertopwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmlisthelper.h"
#include "OgmCommon/ogmsetting.h"
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
    _serverId=serverId;
    DataServer *server=_dServerBLL.data()->getServerId(serverId);

    _ui->lblName->setText(server->name);
    _ui->lblServerLocation->setText(server->location);

    if(serverId==OgmSetting::defaultDataServerId){
        _ui->btnServerDefault->setHidden(true);
    }
    else{
        _ui->btnServerDefault->setHidden(false);
    }

    if(!server->desc.isEmpty() || !server->desc.isNull() || server->desc!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(server->desc);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }

    setBtnCheckState(_ui->btnServerDataPage->objectName());
    emit signalChangeDataList(_serverId);
}

void OgmServerTopWidget::changeModelServer(QString serverId)
{
    //content
    _serverId=serverId;
    ModelServer *server=_mServerBLL.data()->getServerId(serverId);

    _ui->lblName->setText(server->name);
    _ui->lblServerLocation->setText(server->location);

    if(serverId==OgmSetting::defaultModelServerId){
        _ui->btnServerDefault->setHidden(true);
    }
    else{
        _ui->btnServerDefault->setHidden(false);
    }

    if(server->desc!=""){
        _ui->widgetTopDes->setHidden(true);
        _ui->lblServerDesContent->setHidden(false);
        _ui->lblServerDesContent->setText(server->desc);
    }
    else{
        _ui->widgetTopDes->setHidden(false);
        _ui->lblServerDesContent->setHidden(true);
    }

    emit signalChangeModelList(_serverId, 0);
}

void OgmServerTopWidget::changeFileManager(QString serverId)
{
    //content
    _serverId=serverId;

    DataServer *server=_dServerBLL.data()->getServerId(serverId);

    if(serverId==OgmSetting::defaultDataServerId){
        _ui->btnServerDefault->setHidden(true);
    }
    else{
        _ui->btnServerDefault->setHidden(false);
    }

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

    emit signalClearList();
    emit signalChangeDataFileByParentId(_serverId, "-1", "");
}

void OgmServerTopWidget::changeFavorManager(QString favorId)
{
    _favorId=favorId;
    Favor *favor=_favorBLL.data()->getFavorGroupById(_favorId);

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

    if(favorId==OgmSetting::defaultFavorId){
        _ui->btnTopDeleteFavor->setHidden(true);
    }
    else
        _ui->btnTopDeleteFavor->setHidden(false);


    //change list
    setBtnCheckState(_ui->btnFavorToolModel->objectName());
    emit signalClearList();
    QList<ModelService*> msList=_favorBLL.data()->favor2modelServiceList(favor);

    emit signalChangeModelListByList(msList);
}

QString OgmServerTopWidget::getCurrentServerId()
{
    return _serverId;
}

QString OgmServerTopWidget::getCurrentFileId()
{
    return _folderId;
}

QString OgmServerTopWidget::getCurrentFavorId()
{
    return _favorId;
}

void OgmServerTopWidget::initModelWidget()
{
    _serverId=OgmSetting::defaultModelServerId;

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
    connect(_ui->btnServerDefault, &QToolButton::clicked, [=](){
        OgmSetting::defaultModelServerId=_serverId;
        _ui->btnServerDefault->setHidden(true);
    });
    connect(_ui->txtServerSearch, &QLineEdit::textChanged, [=](QString txt){
        emit signalSearchTxtChanged(txt);
    });
}

void OgmServerTopWidget::initDataWidget()
{
    _serverId=OgmSetting::defaultDataServerId;

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
        setBtnCheckState(_ui->btnServerDataPage->objectName());
        emit signalChangeDataList(_serverId);
        //emit signalSwitchPage("DataList");
    });
    connect(_ui->btnServerDataMappingPage, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnServerDataMappingPage->objectName());
        emit signalChangeDataMappingList(_serverId);
        //emit signalSwitchPage("DataList");
    });
    connect(_ui->btnServerDataRefactorPage, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnServerDataRefactorPage->objectName());
        emit signalChangeDataRefactorList(_serverId);
        //emit signalSwitchPage("DataList");
    });

    connect(_ui->btnServerChange, &QToolButton::clicked, [=](){
        emit signalChangeDataServer();
    });
    connect(_ui->btnServerDefault, &QToolButton::clicked, [=](){
        OgmSetting::defaultDataServerId=_serverId;
        _ui->btnServerDefault->setHidden(true);
    });
    connect(_ui->txtServerSearch, &QLineEdit::textChanged, [=](QString txt){
        emit signalSearchTxtChanged(txt);
    });
}

void OgmServerTopWidget::initFavorWidget()
{
    _favorId=OgmSetting::defaultFavorId;

    OgmUiHelper::Instance()->setIcon(_ui->lblIcon, QChar(0xf004));
    OgmUiHelper::Instance()->setIcon(_ui->lblServerLocationIcon, QChar(0xf041));
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
    connect(_ui->btnTopNewFavor, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("NewFavorGroup");
        popWidget->show();
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varResult){
            Favor *addFavor=new Favor();
            addFavor->id=OgmHelper::createUId();
            addFavor->name=varResult.toStringList().at(0);
            addFavor->des=varResult.toStringList().at(1);

            _favorBLL.data()->addOneFavorGroup(addFavor);
        });
    });
    connect(_ui->btnTopDeleteFavor, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("DeleteFavorGroup");
        popWidget->show();
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant varResult){
            if(varResult.toBool()){
                _favorBLL.data()->deleteOneFavorGroup(_favorId);
                changeFavorManager(OgmSetting::defaultFavorId);
            }
        });
    });

    //favor function
    connect(_ui->btnFavorToolModel, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnFavorToolModel->objectName());
        emit signalClearList();

        Favor *favor=_favorBLL.data()->getFavorGroupById(_favorId);
        QList<ModelService*> msList=_favorBLL.data()->favor2modelServiceList(favor);

        emit signalChangeModelListByList(msList);
    });
    connect(_ui->btnFavorToolData, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnFavorToolData->objectName());
        emit signalClearList();

        Favor *favor=_favorBLL.data()->getFavorGroupById(_favorId);
        QList<DataService*> dsList=_favorBLL.data()->favor2dataServiceList(favor);

        emit signalChangeDataListByList(dsList);
    });
    connect(_ui->btnFavorToolDataMapping, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnFavorToolDataMapping->objectName());
        emit signalClearList();

        Favor *favor=_favorBLL.data()->getFavorGroupById(_favorId);
        QList<DataMapping*> mappingList=_favorBLL.data()->favor2dataMappingList(favor);

        emit signalChangeDataMappingListByList(mappingList);
    });
    connect(_ui->btnFavorToolDataRefactor, &QToolButton::clicked, [=](){
        setBtnCheckState(_ui->btnFavorToolDataRefactor->objectName());
        emit signalClearList();

        Favor *favor=_favorBLL.data()->getFavorGroupById(_favorId);
        QList<DataRefactor*> refactorList=_favorBLL.data()->favor2dataRefactorList(favor);

        emit signalChangeDataRefactorListByList(refactorList);
    });

    connect(_ui->txtServerSearch, &QLineEdit::textChanged, [=](QString txt){
        emit signalSearchTxtChanged(txt);
    });
}

void OgmServerTopWidget::initFileWidget()
{
    _folderId="-1";

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
        _folderId="-1";
        removeNextAllFileLink("-1", "All");
        emit signalClearList();
        emit signalChangeDataFileByParentId(_serverId, "-1", "File");
    });
    _ui->widgetFileLink->layout()->addWidget(btnFileLinkAll);
    _fileLinkList.append(btnFileLinkAll->objectName());

    //function
    connect(_ui->btnNewFolder, &QToolButton::clicked, [=](){
        OgmPopWidget *popWidget=new OgmPopWidget("NewFile");
        connect(popWidget, &OgmPopWidget::signalOperationResult, [=](QVariant result){
            QString folderName=result.toString();
            QString addTime=QDateTime::currentDateTime().toString("yyyy-MM-dd");

            emit signalClearList();

            _dataFileBLL.data()->addFolder(_serverId, _folderId, folderName, addTime);

            //change list
            emit signalChangeDataFileByParentId(_serverId, _folderId, "File");
        });
        popWidget->show();
    });
    connect(_ui->btnUploadFile, &QToolButton::clicked, [=](){
       QString filePath=QFileDialog::getOpenFileName(this, "choose upload data");
       if(filePath==QString::null)
           return;
       _dataFileBLL.data()->uploadFile(_serverId, _folderId, filePath);
    });

    connect(_ui->btnServerChange, &QToolButton::clicked, [=](){
        emit signalChangeDataServer();
    });
    connect(_ui->btnServerDefault, &QToolButton::clicked, [=](){
        OgmSetting::defaultDataServerId=_serverId;
        _ui->btnServerDefault->setHidden(true);
    });
}

void OgmServerTopWidget::addOneFileLinkOnUI(QString fileId, QString fileName)
{
    _folderId=fileId;

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
        removeNextAllFileLink(fileId, fileName);
        emit signalClearList();
        emit signalChangeDataFileByParentId(_serverId, fileId, "File");

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

void OgmServerTopWidget::setBtnCheckState(QString btnName)
{
    QList<QToolButton*> btnList=_ui->widgetDataServerTool->findChildren<QToolButton*>();
    for(int i=0; i<btnList.count(); ++i){
        if(btnList.at(i)->objectName()==btnName){
            btnList[i]->setChecked(true);
        }
        else
            btnList[i]->setChecked(false);
    }
}
