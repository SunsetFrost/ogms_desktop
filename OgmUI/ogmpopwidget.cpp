#include "ogmpopwidget.h"

#include "ui_ogmpopwidget.h"

#include "OgmCommon/ogmsetting.h"
#include "OgmCommon/ogmuihelper.h"

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

    if(widgetType=="NewFile")
        initNewFileWidget();
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

    setDragWidgetName("widgetPopTitle");
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void OgmPopWidget::changeChooseRefactorMethod(QString serverId, QString refactorId)
{
    OgmListWidget *mList=_ui->widgetPopChooseFile->findChild<OgmListWidget*>();
    mList->changeRefactorMethodListUI(serverId, refactorId);
}

void OgmPopWidget::setCommonWidgetInfo(QString title, QString content, QString btnText)
{
    _ui->lblPopTitle->setText(title);
    _ui->lblPop->setText(content);
    _ui->btnPopA->setText(btnText);
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
        emit signalOperationResult(result);
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initNewFileWidget()
{
    //style
    this->setFixedHeight(200);
    _ui->widgetPopFile->setHidden(false);

    _ui->lblPopTitle->setText("New File");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    _ui->txtPopNewFile->setPlaceholderText("Please input folder name");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QString folderName=_ui->txtPopNewFile->text();
        QVariant result(folderName);
        emit signalOperationResult(result);
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initNewFavorGroupWidget()
{
    this->setFixedHeight(250);
    _ui->widgetPopSaveTask->setHidden(false);

    _ui->lblPopTitle->setText("New Favor Group");
    _ui->btnPopA->setText("Confirm");
    _ui->btnPopB->setText("Cancel");

    _ui->txtPopTaskName->setPlaceholderText("Please input group name");
    _ui->txtPopTaskDesc->setPlaceholderText("Please input group description");
    _ui->txtPopTaskTag->setHidden(true);

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        QStringList strList;

        strList.append(_ui->txtPopTaskName->text());
        strList.append(_ui->txtPopTaskDesc->toPlainText());

        QVariant varTaskInfo(strList);
        emit signalOperationResult(varTaskInfo);

        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initDeleteFileWidget()
{
    //style
    this->setFixedHeight(200);
    _ui->widgetPopDeleteFile->setHidden(false);

    _ui->lblPopTitle->setText("Delete File");
    _ui->btnPopA->setText("Delete");
    _ui->btnPopB->setText("Cancel");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        bool isConfirm=true;
        QVariant result(isConfirm);
        emit signalOperationResult(result);
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initDeleteFavorWidget()
{
    //style
    this->setFixedHeight(200);
    _ui->widgetPopDeleteFile->setHidden(false);

    _ui->lblPopTitle->setText("Delete Favor Group");
    _ui->btnPopA->setText("Delete");
    _ui->btnPopB->setText("Cancel");

    //function
    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        bool isConfirm=true;
        QVariant result(isConfirm);
        emit signalOperationResult(result);
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initChooseDataFile()
{
    this->setFixedSize(700, 600);
    _ui->widgetPopChooseFile->setHidden(false);

    _ui->lblPopTitle->setText("Choose file");
    _ui->btnPopA->setText("Choose");
    _ui->btnPopB->setText("Cancel");

    _currentFileId=-1;

    OgmListWidget *listWidget=new OgmListWidget(_ui->widgetPopFileList);
    listWidget->setObjectName("mPopListWidget");
    listWidget->changeFileListUI(OgmSetting::defaultDataServerId, "Data", "FileCheck");
    listWidget->setFileListState("chooseDataFile");
    connect(listWidget, &OgmListWidget::signalAddFolderOnFileLink, this, &OgmPopWidget::addOneFileLinkOnUI);
    _ui->widgetPopFileList->layout()->addWidget(listWidget);

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
        _currentFileId="-1";
        listWidget->changeFileListUIByParentId(listWidget->getServerId(), "-1", "FileCheck");
        removeNextAllFileLink("-1", "All");
    });
    _ui->widgetPopFileLink->layout()->addWidget(btnFileLinkAll);
    _fileLinkList.append(btnFileLinkAll->objectName());


    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        emit signalOperationResult(listWidget->getCheckFileInfo().toStringList());
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initChooseRefactorMethod()
{
    this->setFixedSize(500, 280);
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
        emit signalSwitchPage(pageType);
        this->close();
    });

    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initSaveTask()
{
    this->setFixedHeight(280);
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
        emit signalOperationResult(varTaskInfo);

        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initNewServer()
{
    this->setFixedHeight(350);
    _ui->widgetPopNewServer->setHidden(false);

    _ui->lblPopTitle->setText("New Server");
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

        QVariant varTaskInfo(strList);
        emit signalOperationResult(varTaskInfo);

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
        OgmListWidget *widgetPopListWidget=_ui->widgetPopFileList->findChild<OgmListWidget*>("mPopListWidget");
        widgetPopListWidget->changeFileListUIByParentId(widgetPopListWidget->getServerId(), fileId, "FileCheck");
        removeNextAllFileLink(fileId, fileName);
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
