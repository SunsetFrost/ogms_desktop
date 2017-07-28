#ifndef OGMMINITOPWIDGET_H
#define OGMMINITOPWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include "ui_ogmminitopwidget.h"
#include "OgmBLL/taskbll.h"

namespace Ui{
class OgmMiniTopWidget;
}

class OgmMiniTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmMiniTopWidget(QString widgetType, QWidget *parent = 0);

public:

private:
    void initWidget();

private:
    Ui::OgmMiniTopWidget *_ui;
    QString _widgetType;

    QSharedPointer<TaskBLL> _taskBLL;

signals:
    void signalChangeTaskList(QList<Task*> taskList, QString taskRunState);
};

#endif // OGMMINITOPWIDGET_H
