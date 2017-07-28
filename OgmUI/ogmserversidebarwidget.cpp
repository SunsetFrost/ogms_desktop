#include "ogmserversidebarwidget.h"

#include "OgmCommon/ogmuihelper.h"

OgmServerSidebarWidget::OgmServerSidebarWidget(QWidget *parent) : QWidget(parent)
{
    _modelBLL=QSharedPointer<ModelServerBLL>(new ModelServerBLL);
    _dataBLL=QSharedPointer<DataServerBLL>(new DataServerBLL);

    initWidget();
}

void OgmServerSidebarWidget::changeModelServerUI()
{
    this->setHidden(false);

    while(_layoutServer->count()>0){
        QWidget *widgetDel= _layoutServer->itemAt(0)->widget();
        _layoutServer->removeWidget(widgetDel);
        delete widgetDel;
    }

    QList<ModelServer*> modelServerList= _modelBLL.data()->getAllServer();

    for(int i=0; i<modelServerList.count(); ++i){
        QWidget *mChildWidget=new QWidget();
        QHBoxLayout *layoutChildWidget=new QHBoxLayout();
        layoutChildWidget->setMargin(0);

        QToolButton *btnDictionaryName=new QToolButton();
        btnDictionaryName->setWindowTitle("btn-sidebar");
        btnDictionaryName->setCheckable(true);
        btnDictionaryName->setFixedHeight(40);
        btnDictionaryName->setFixedWidth(180);
        OgmUiHelper::Instance()->setButtonIcon(btnDictionaryName, 0xf17a, modelServerList.at(i)->name);
        btnDictionaryName->setObjectName("btnHomeModelServer|"+modelServerList.at(i)->id);
        //connect(btnDictionaryName, SIGNAL(clicked()), this, SLOT(onServerClicked()));
        connect(btnDictionaryName, &QToolButton::clicked, [=](){
            buttonCheck(btnDictionaryName);
            this->setHidden(true);
            emit signalChangeModelList(modelServerList.at(i)->id);
        });

        //layoutChildWidget->addSpacing(10);
        layoutChildWidget->addWidget(btnDictionaryName);
        //layoutChildWidget->addStretch();
        mChildWidget->setLayout(layoutChildWidget);
        _layoutServer->addWidget(mChildWidget);
    }
    _layoutServer->addStretch();
}

void OgmServerSidebarWidget::initWidget()
{
    this->setFixedWidth(180);

    QWidget *widgetServer=new QWidget;
    widgetServer->setWindowTitle("widget-serverSidebar");

    QVBoxLayout *layoutMain=new QVBoxLayout;
    layoutMain->addWidget(widgetServer);
    layoutMain->setMargin(0);
    layoutMain->setSpacing(0);
    this->setLayout(layoutMain);

    QLabel *lblTitleIcon=new QLabel;
    OgmUiHelper::Instance()->setIcon(lblTitleIcon, QChar(0xf233));
    lblTitleIcon->setWindowTitle("lbl-cGrey");
    QLabel *lblTitle=new QLabel;
    lblTitle->setText("Server");
    lblTitle->setWindowTitle("lbl-cGrey");

    QHBoxLayout *layoutTitle=new QHBoxLayout;
    layoutTitle->setMargin(20);
    layoutTitle->setSpacing(10);
    layoutTitle->addWidget(lblTitleIcon);
    layoutTitle->addWidget(lblTitle);
    layoutTitle->addStretch();

    _widgetServerTop=new QWidget;
    _widgetServerTop->setLayout(layoutTitle);

    _layoutServer=new QVBoxLayout();
    _layoutServer->setMargin(0);
    _layoutServer->setSpacing(0);
    _widgetServerBottom=new QWidget();
    _widgetServerBottom->setLayout(_layoutServer);

    QVBoxLayout *layoutMainChild= new QVBoxLayout;
    layoutMainChild->addWidget(_widgetServerTop);
    layoutMainChild->addWidget(_widgetServerBottom);
    layoutMainChild->setMargin(0);
    widgetServer->setLayout(layoutMainChild);
}

void OgmServerSidebarWidget::buttonCheck(QToolButton *btn)
{
    QList<QToolButton*> btns=this->findChildren<QToolButton*>();

    foreach (QToolButton *mBtn, btns) {
        if(mBtn==btn){
            mBtn->setChecked(true);
        }
        else{
            mBtn->setChecked(false);
        }
    }
}
