#include "ogmtoolwidget.h"

#include "OgmCommon/ogmuihelper.h"
#include "OgmCommon/ogmsetting.h"

#include <QProcess>

OgmToolWidget::OgmToolWidget(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::OgmToolUI)
{
    _ui->setupUi(this);
    initWidget();
}

void OgmToolWidget::initWidget()
{
    OgmUiHelper::Instance()->setIcon(_ui->lblToolUdx, QChar(0xf02d));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolUdxRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolUdxInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolOms, QChar(0xf1d0));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolOmsRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolOmsInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolA, QChar(0xf1b2));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolARun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolAInfo, QChar(0xf05a));

    OgmUiHelper::Instance()->setIcon(_ui->lblToolB, QChar(0xf1b2));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolBRun, QChar(0xf144));
    OgmUiHelper::Instance()->setIcon(_ui->btnToolBInfo, QChar(0xf05a));

    //function
    connect(_ui->btnToolUdxRun, &QToolButton::clicked, [=](){
       QProcess *pro=new QProcess();
       pro->start(OgmSetting::udxToolPath);
    });
    connect(_ui->btnToolOmsRun, &QToolButton::clicked, [=](){
       QProcess *pro=new QProcess();
       pro->start(OgmSetting::omsToolPath);
    });
}



