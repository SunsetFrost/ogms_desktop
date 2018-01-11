#include "ogmtoolwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmsetting.h"

#include <QProcess>
#include <QDesktopServices>
#include <QUrl>

OgmToolWidget::OgmToolWidget(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::OgmToolUI)
{
    _ui->setupUi(this);

    _modelServerBLL=QSharedPointer<ModelServerBLL>(new ModelServerBLL);
    _dataServerBLL=QSharedPointer<DataServerBLL>(new DataServerBLL);

    initWidget();
}

void OgmToolWidget::initWidget()
{
    OgmUiHelper::Instance()->setIcon(_ui->lblToolUdx, QChar(0xf02d));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolUdxDataRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolUdxInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolOms, QChar(0xf1d0));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolOmsRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolOmsInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolA, QChar(0xf1b2));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolUdxSchemaRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolAInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolB, QChar(0xf1b2));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolBRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolBInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolData, QChar(0xf1b2));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolDataRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolDataDesc, QChar(0xf05a));

    //function
    connect(_ui->btnToolUdxDataRun, &QToolButton::clicked, [=](){
        QProcess *pro=new QProcess();
        pro->start(OgmSetting::udxDataPath);
    });
    connect(_ui->btnToolUdxSchemaRun, &QToolButton::clicked, [=](){
        QProcess *pro=new QProcess();
        pro->start(OgmSetting::udxSchemaPath);
    });
    connect(_ui->btnToolOmsRun, &QToolButton::clicked, [=](){
        QProcess *pro=new QProcess();
        pro->start(OgmSetting::omsToolPath);
    });
    connect(_ui->btnToolBRun, &QToolButton::clicked, [=](){
        ModelServer *server=_modelServerBLL.data()->getServerId(OgmSetting::defaultModelServerId);
        QDesktopServices::openUrl(QUrl("http://"+server->ip+"/index"));
    });
    connect(_ui->btnToolDataRun, &QToolButton::clicked, [=](){
        DataServer *server=_dataServerBLL.data()->getServerId(OgmSetting::defaultDataServerId);
        QDesktopServices::openUrl(QUrl("http://"+server->ip));
    });
}



