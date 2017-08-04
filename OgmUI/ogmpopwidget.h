#ifndef OGMPOPWIDGET_H
#define OGMPOPWIDGET_H

#include "OgmCommon/ogmwidget.h"
#include "OgmUI/ogmlistwidget.h"

#include <QVariant>

namespace Ui{
class OgmPopUI;
}

class OgmPopWidget : public OgmWidget
{
    Q_OBJECT

public:
    OgmPopWidget(QString widgetType, QWidget *parent=0);

    void changeChooseRefactorMethod(QString serverId, QString refactorId);

private:
    void initNewFileWidget();

    void initNewFavorGroupWidget();

    void initDeleteFileWidget();

    void initDeleteFavorWidget();

    void initChooseDataFile();

    void initChooseRefactorMethod();

    void initSaveTask();

    //file
    void addOneFileLinkOnUI(QString fileId, QString fileName);
    void removeNextAllFileLink(QString fileId, QString fileName);




private:
    Ui::OgmPopUI *_ui;

    //file
    QString _currentFileId;
    QList<QString> _fileLinkList;

signals:
    void signalOperationResult(QVariant result);

    void signalSwitchPage(QString pageType);
    void signalChangeDataRefactorConfigUI(QString serverId, QString refactorId, QString methodName);
};

#endif // OGMPOPWIDGET_H
