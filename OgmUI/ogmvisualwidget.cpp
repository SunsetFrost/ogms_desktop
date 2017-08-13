#include "ogmvisualwidget.h"

#include <QLayout>
#include <QtWebChannel/QtWebChannel>

OgmVisualWidget::OgmVisualWidget(QWidget *parent) : QWidget(parent)
{
    initWidget();
}

void OgmVisualWidget::changeVisualUrl(QString url)
{
    _view->setUrl(url);
}

void OgmVisualWidget::initWidget()
{
    _view=new QWebEngineView();

    QVBoxLayout *layoutMain=new QVBoxLayout();
    layoutMain->setMargin(0);
    layoutMain->addWidget(_view);
    this->setLayout(layoutMain);
}
