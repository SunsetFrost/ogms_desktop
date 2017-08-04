#ifndef OGMSERVERTOPWIDGET_H
#define OGMSERVERTOPWIDGET_H

#include <QWidget>
#include <QSharedPointer>

#include "ui_ogmtopwidget.h"
#include "OgmBLL/databll.h"
#include "OgmBLL/modelbll.h"
#include "OgmBLL/favorbll.h"
#include "OgmBLL/filebll.h"

namespace Ui{
class OgmTopWidget;
}

class OgmServerTopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmServerTopWidget(QString widgetType, QWidget *parent = 0);

    void changeDataServer(QString serverId);

    void changeModelServer(QString serverId);

    void changeFileManager(QString serverId);

    void changeFavorManager(QString favorId);

    QString getCurrentId();
    QString getCurrentFileId();

    void addOneFileLinkOnUI(QString fileId, QString fileName);

private:
    void initModelWidget();
    void initDataWidget();
    void initFavorWidget();
    void initFileWidget();

    void removeNextAllFileLink(QString fileId, QString fileName);


private:
    Ui::OgmTopWidget *_ui;

    QSharedPointer<DataServerBLL> _dServerBLL;
    QSharedPointer<ModelServerBLL> _mServerBLL;
    QSharedPointer<FavorBLL> _favorBLL;
    QSharedPointer<DataFileBll> _dataFileBLL;

    QString _serverId;
    QString _currentFileId;

    QList<QString> _fileLinkList;

signals:
    void signalChangeModelServer();
    void signalChangeModelList(QString serverId);
    void signalChangeModelListByList(QList<ModelService*> msList);

    void signalChangeDataServer();
    void signalChangeDataList(QString serverId);
    void signalChangeDataListByList(QList<DataService*> dsList);
    void signalChangeDataMappingList(QString serverId);
    void signalChangeDataMappingListByList(QList<DataMapping*> dataMappingList);
    void signalChangeDataRefactorList(QString serverId);
    void signalChangeDataRefactorListByList(QList<DataRefactor*> dataRefactorList);

    void signalChangeFavor();

    void signalChangeDataFileByParentId(QString serverId, QString parentId, QString checkType);

    void signalSwitchPage(QString pageType);
};

#endif // OGMSERVERTOPWIDGET_H
