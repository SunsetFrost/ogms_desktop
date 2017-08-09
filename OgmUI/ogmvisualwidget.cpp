#include "ogmvisualwidget.h"

#include <QLayout>
#include <QWebEngineView>
#include <QtWebChannel/QtWebChannel>

OgmVisualWidget::OgmVisualWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

void OgmVisualWidget::initWidget()
{
    QWebEngineView *view=new QWebEngineView();
    view->setUrl(QUrl("https://cesiumjs.org/NewYork/index.html"));
    //view->setUrl(QUrl("https://www.baidu.com"));

    QVBoxLayout *layoutMain=new QVBoxLayout();
    layoutMain->setMargin(0);
    layoutMain->addWidget(view);
    this->setLayout(layoutMain);
}
