#ifndef OGMPOPWIDGET_H
#define OGMPOPWIDGET_H

#include "OgmCommon/ogmwidget.h"
#include "OgmUI/ogmlistwidget.h"
#include "OgmEntity/task.h"

#include <QVariant>

namespace Ui{
class OgmPopUI;
}

class OgmPopWidget : public OgmWidget
{
    Q_OBJECT

public:
    OgmPopWidget(QString widgetType, QWidget *parent=0);
    OgmPopWidget(QString widgetType, QString serverId, QWidget *parent=0);

    void changeChooseRefactorMethod(QString serverId, QString refactorId);
    void changeConfigModelTaskUI(Task *task);

    void setCommonWidgetInfo(QString title, QString content, QString btnText);

    void setFileServerId(QString fileServerId);

private:
    void initCommonWidget();

    void initNewFileWidget();
    void initReNameFileWidget();

    void initNewFavorGroupWidget();

    void initDeleteFileWidget();

    void initDeleteFavorWidget();

    void initChooseDataFile();

    void initChooseRefactorMethod();

    void initSaveTask();

    void initNewServer();

    void initConfigModelTask();



    //file
    void addOneFileLinkOnUI(QString fileId, QString fileName);
    void removeNextAllFileLink(QString fileId, QString fileName);
    //task
    Task *_task;
    QString _eventIndex;


private:
    Ui::OgmPopUI *_ui;

    //file
    QString _currentFileId;
    QList<QString> _fileLinkList;
    QString _fileServerId;

signals:
    void signalOperationResult(QVariant result);

    void signalSwitchPage(QString pageType);
    void signalChangeDataRefactorConfigUI(QString serverId, QString refactorId, QString methodName);
};

#endif // OGMPOPWIDGET_H
