#include "ogmfavorsidebarwidget.h"

#include "OgmCommon/ogmuihelper.h"

#include <QLabel>

OgmFavorSidebarWidget::OgmFavorSidebarWidget(QWidget *parent) : QWidget(parent)
{
    _favorBLL=QSharedPointer<FavorBLL>(new FavorBLL);

    initWidget();
}

void OgmFavorSidebarWidget::changeFavorUI()
{
    this->setHidden(false);
    QHBoxLayout *layoutH=qobject_cast<QHBoxLayout*>(_widgetTop->layout());

    QList<Favor*> groupList=_favorBLL.data()->getAllFavorGroup();

    while(_widgetMain->layout()->count()>0){
        QWidget *widgetDel=_widgetMain->layout()->itemAt(0)->widget();
        _widgetMain->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(layoutH->count()>0){
        QWidget *widgetDel=layoutH->itemAt(0)->widget();
        layoutH->removeWidget(widgetDel);
        delete widgetDel;
    }

    //layoutTop content
    QLabel *lblTopIcon=new QLabel();
    lblTopIcon->setObjectName("lblStorageTopIcon");
    lblTopIcon->setWindowTitle("lbl-cGrey");
    OgmUiHelper::Instance()->setIcon(lblTopIcon, QChar(0xf233));

    QLabel *lblTop=new QLabel();
    lblTop->setObjectName("lblStorageTop");
    lblTop->setWindowTitle("lbl-cGrey");
    lblTop->setFixedWidth(200);
    lblTop->setText("Favor");

    layoutH->addWidget(lblTopIcon);
    layoutH->addWidget(lblTop);
    layoutH->addSpacing(50);
    layoutH->setMargin(20);

    for(int i=0; i<groupList.count(); ++i){
        QWidget *widget=new QWidget();
        QHBoxLayout *layout=new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);

        QToolButton *btnStorage=new QToolButton();
        btnStorage->setWindowTitle("btn-sidebar");
        btnStorage->setCheckable(true);
        btnStorage->setFixedSize(180, 40);
        OgmUiHelper::Instance()->setButtonIcon(btnStorage, 0xf1b3, groupList[i]->name);
        btnStorage->setAccessibleDescription(groupList[i]->id);

        connect(btnStorage, &QToolButton::clicked, [=](){
            buttonCheck(btnStorage);
            QString favorId=groupList[i]->id;
            emit signalChangeFavorTop(favorId);
            emit signalSwitchPage("FavorList");
            this->setHidden(true);
        });

//        else if(_pageType=="Mini"){
//            connect(btnStorage, SIGNAL(clicked()), this, SLOT(onChooseStorageBtnClicked()));
//        }
        layout->addWidget(btnStorage);
        //layout->addStretch();
        widget->setLayout(layout);

        _widgetMain->layout()->addWidget(widget);
    }
    QVBoxLayout *layout= qobject_cast<QVBoxLayout*>(_widgetMain->layout());
    layout->addStretch();
}

void OgmFavorSidebarWidget::changeChooseFavorUI(QString serverId, QString serviceId, QString serviceType)
{
    this->setHidden(false);
    QHBoxLayout *layoutH=qobject_cast<QHBoxLayout*>(_widgetTop->layout());

    QList<Favor*> groupList=_favorBLL.data()->getAllFavorGroup();

    SERVICEITEM serviceItem;
    serviceItem.serverId=serverId;
    serviceItem.serviceId=serviceId;
    serviceItem.serviceType=serviceType;

    while(_widgetMain->layout()->count()>0){
        QWidget *widgetDel=_widgetMain->layout()->itemAt(0)->widget();
        _widgetMain->layout()->removeWidget(widgetDel);
        delete widgetDel;
    }
    while(layoutH->count()>0){
        QWidget *widgetDel=layoutH->itemAt(0)->widget();
        layoutH->removeWidget(widgetDel);
        delete widgetDel;
    }

    //layoutTop content
    QLabel *lblTopIcon=new QLabel();
    lblTopIcon->setObjectName("lblStorageTopIcon");
    lblTopIcon->setWindowTitle("lbl-cGrey");
    //NjUIHelper::Instance()->setIcon(lblTopIcon, QChar(0xf233));

    QLabel *lblTop=new QLabel();
    lblTop->setObjectName("lblStorageTop");
    lblTop->setWindowTitle("lbl-cGrey");
    lblTop->setFixedWidth(200);
    lblTop->setText("Choose");

    layoutH->addWidget(lblTopIcon);
    layoutH->addWidget(lblTop);
    layoutH->addSpacing(50);
    layoutH->setMargin(20);

    for(int i=0; i<groupList.count(); ++i){
        QWidget *widget=new QWidget();
        QHBoxLayout *layout=new QHBoxLayout();
        layout->setMargin(0);
        layout->setSpacing(0);

        QToolButton *btnStorage=new QToolButton();
        btnStorage->setWindowTitle("btn-sidebar");
        btnStorage->setCheckable(true);
        btnStorage->setFixedSize(180, 40);
        OgmUiHelper::Instance()->setButtonIcon(btnStorage, 0xf1b3, groupList[i]->name);
        btnStorage->setAccessibleDescription(groupList[i]->id);

        connect(btnStorage, &QToolButton::clicked, [=](){
            buttonCheck(btnStorage);
        });

        layout->addWidget(btnStorage);
        widget->setLayout(layout);
        _widgetMain->layout()->addWidget(widget);
    }
    QVBoxLayout *layout= qobject_cast<QVBoxLayout*>(_widgetMain->layout());
    layout->addStretch();

    //button
    _btnConfirm=new QToolButton();
    _btnConfirm->setFixedSize(180, 40);
    OgmUiHelper::Instance()->setButtonIcon(_btnConfirm, 0xf058, "Confirm", 35);
    _btnConfirm->setWindowTitle("btn-sidebar-bottom");
    connect(_btnConfirm, &QToolButton::clicked, [=](){
        QList<QToolButton*> btnList= this->findChildren<QToolButton*>();
        for(int i=0; i<btnList.count(); ++i){
            if(btnList[i]->isChecked()){

                _favorBLL.data()->addOneFavorService(serviceItem, groupList.at(i)->id);
            }
        }

        this->setHidden(true);

        delete _btnConfirm;
        delete _btnCancel;
    });
    _widgetBtn->layout()->addWidget(_btnConfirm);

    _btnCancel=new QToolButton();
    _btnCancel->setFixedSize(180, 40);
    OgmUiHelper::Instance()->setButtonIcon(_btnCancel, 0xf05e, "Cancel", 35);
    _btnCancel->setWindowTitle("btn-sidebar-bottom");
    connect(_btnCancel, &QToolButton::clicked, [=](){
        this->setHidden(true);
        delete _btnConfirm;
        delete _btnCancel;
    });
    _widgetBtn->layout()->addWidget(_btnCancel);
}

void OgmFavorSidebarWidget::initWidget()
{
    this->setFixedWidth(180);

    QHBoxLayout *layoutContainer=new QHBoxLayout();
    layoutContainer->setMargin(0);
    this->setLayout(layoutContainer);

    QWidget *widgetStorage=new QWidget();
    widgetStorage->setWindowTitle("widget-serverSidebar");
    layoutContainer->addWidget(widgetStorage);

    QVBoxLayout *layoutMain=new QVBoxLayout();
    layoutMain->setMargin(0);
    layoutMain->setSpacing(0);
    widgetStorage->setLayout(layoutMain);

    //layoutMain content
    _widgetTop=new QWidget();
    layoutMain->addWidget(_widgetTop);

    QHBoxLayout *layoutTop=new QHBoxLayout();
    layoutTop->setMargin(2);
    _widgetTop->setLayout(layoutTop);

    _widgetMain=new QWidget();
    layoutMain->addWidget(_widgetMain);

    QVBoxLayout *layout=new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    _widgetMain->setLayout(layout);

    _widgetBtn=new QWidget();
    layoutMain->addWidget(_widgetBtn);

    QVBoxLayout *layoutBtn=new QVBoxLayout();
    layoutBtn->setMargin(0);
    _widgetBtn->setLayout(layoutBtn);
}

void OgmFavorSidebarWidget::buttonCheck(QToolButton *btn)
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
