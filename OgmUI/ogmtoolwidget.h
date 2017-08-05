#ifndef OGMTOOLWIDGET_H
#define OGMTOOLWIDGET_H

#include <QWidget>

#include "ui_ogmtoolui.h"
#include "OgmBLL/modelbll.h"
#include "OgmBLL/databll.h"

namespace Ui{
class OgmToolUI;
}

class OgmToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmToolWidget(QWidget *parent = 0);

private:
    void initWidget();

private:
    Ui::OgmToolUI *_ui;

    QSharedPointer<ModelServerBLL> _modelServerBLL;
    QSharedPointer<DataServerBLL> _dataServerBLL;
};

#endif // OGMTOOLWIDGET_H
