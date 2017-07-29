#include "ogmpopwidget.h"

#include "ui_ogmpopwidget.h"

#include "OgmCommon/ogmsetting.h"

OgmPopWidget::OgmPopWidget(QString widgetType, QWidget *parent)
    :OgmWidget(false, true, parent)
    ,_ui(new Ui::OgmPopUI)
{
    _ui->setupUi(this);

    _ui->widgetPopFile->setHidden(true);
    _ui->widgetPopDeleteFile->setHidden(true);
    _ui->widgetPopChooseFile->setHidden(true);
    _ui->widgetPopSaveTask->setHidden(true);

    if(widgetType=="NewFile")
        initNewFileWidget();
    else if(widgetType=="DeleteFile")
        initDeleteFileWidget();
    else if(widgetType=="ChooseFile")
        initChooseDataFile();
    else if(widgetType=="SaveTask")
        initSaveTask();

    setDragWidgetName("widgetPopTitle");
    this->setAttribute(Qt::WA_DeleteOnClose);
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

void OgmPopWidget::initChooseDataFile()
{
    this->setFixedSize(800, 600);
    _ui->widgetPopChooseFile->setHidden(false);

    OgmListWidget *listWidget=new OgmListWidget(_ui->widgetPopChooseFile);
    listWidget->changeFileListUI(OgmSetting::defaultDataServerId, "Data");
    listWidget->setFileListState("chooseDataFile");
    _ui->widgetPopChooseFile->layout()->addWidget(listWidget);

    _ui->lblPopTitle->setText("Choose file");
    _ui->btnPopA->setText("Choose");
    _ui->btnPopB->setText("Cancel");

    connect(_ui->btnPopA, &QToolButton::clicked, [=](){
        emit signalOperationResult(listWidget->getCheckFileInfo().toStringList());
        this->close();
    });
    connect(_ui->btnPopB, &QToolButton::clicked, this, &OgmPopWidget::close);
}

void OgmPopWidget::initChooseRefactorMethod()
{
    this->setFixedSize(800, 600);
    _ui->widgetPopChooseFile->setHidden(false);
    _ui->widgetPopBtnGroup->setHidden(true);

    _ui->lblPopTitle->setText("Choose refactor method");
}

void OgmPopWidget::initSaveTask()
{
    this->setFixedHeight(400);
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
