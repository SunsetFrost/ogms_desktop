#ifndef OGMFAVORSIDEBARWIDGET_H
#define OGMFAVORSIDEBARWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QSharedPointer>

#include "OgmBLL/favorbll.h"
#include "OgmEntity/favor.h"

class OgmFavorSidebarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmFavorSidebarWidget(QWidget *parent = 0);

    void changeFavorUI();
    void changeChooseFavorUI(QString serverId, QString serviceId, QString serviceType);

private:
    void initWidget();
    void buttonCheck(QToolButton* btn);

private:
    QWidget *_widgetMain;
    QWidget *_widgetTop;
    QWidget *_widgetBtn;

    QToolButton *_btnConfirm;
    QToolButton *_btnCancel;

    QSharedPointer<FavorBLL> _favorBLL;

signals:
    void signalChangeFavorTop(QString favorId);
    void signalSwitchPage(QString pageType);
};

#endif // OGMFAVORSIDEBARWIDGET_H
