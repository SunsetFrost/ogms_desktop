#ifndef OGMSERVERSIDEBARWIDGET_H
#define OGMSERVERSIDEBARWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QLayout>
#include <QToolButton>

#include "OgmBLL/modelbll.h"
#include "OgmBLL/databll.h"

class OgmServerSidebarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmServerSidebarWidget(QWidget *parent = 0);

    void changeModelServerUI();

    void changeDataServerUI();

private:
    void initWidget();

    void buttonCheck(QToolButton* btn);

private:
    QSharedPointer<ModelServerBLL> _modelBLL;
    QSharedPointer<DataServerBLL> _dataBLL;

    QWidget *_widgetServerTop;
    QWidget *_widgetServerBottom;
    QVBoxLayout *_layoutServer;

signals:
    void signalChangeModelList(QString serverId);
    void signalChangeDataList(QString serverId);
};

#endif // OGMSERVERSIDEBARWIDGET_H
