#ifndef OGMLISTWIDGET_H
#define OGMLISTWIDGET_H

#include <QWidget>
#include <QSharedPointer>
#include <QToolButton>

#include "OgmBLL/modelbll.h"
#include "OgmBLL/databll.h"
#include "OgmBLL/filebll.h"
#include "OgmBLL/favorbll.h"
#include "OgmBLL/taskbll.h"

class OgmListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmListWidget(QWidget *parent = 0);

public:
    QString getServerId();

    void changeModelListUIByPage(QString serverId, int pageIndex);
    void changeModelListUI(QList<ModelService*> modelList, QString listType);

    void changeDataListUI(QString serverId, QString type, int pageIndex);
    void changeDataListUI(QList<DataService*> dataList, QString listType);
    void changeDataListUI(QList<DataMapping*> dataMappingList, QString listType);
    void changeDataListUI(QList<DataRefactor*> dataRefactorList, QString listType);

    //TODO checkType should be deleted.   the chectstateinfo can involved in fileType
    void changeFileListUI(QString serverId, QString fileType, QString checkType);
    void changeFileListUI(QList<DataFile*> dataFileList, QString checkType);
    void changeFileListUIByParentId(QString serverId, QString parentId, QString checkType);

    void changeServerListUI(QString serverType);


    //data file choose
    void setFileListState(QString state);
    QVariant getCheckFileInfo();

//    void changeTaskListUI(QString taskType);
    void changeTaskListUI(QList<Task*> taskList, QString taskRunState);

    void changeRefactorMethodListUI(QString serverId, QString refactorId);

    void setPageIndex(int pageIndex);
    void setFavorId(QString favorId);

private:
    void initWidget();

    void clearList();
    void listPaging(QList<QVariant> varList, int pageAmount);
    void addListIntelligent(QVariant var, QString style);
    void setAllBtnUnCheck();

    //add list
    void addOneDataOnUI(DataService *data, QString style);
    void addOneDataMappingOnUI(DataMapping *data, QString style);
    void addOneDataRefactorOnUI(DataRefactor *data, QString style);
    void addOneDataMethodOnUI(DataRefactorMethod *dataMethod, QString style);

    void addOneModelServiceOnUI(ModelService *model, QString style);

    void addOneDataFileOnUI(DataFile *file, QString style);

    void addOneTaskOnUI(Task *task, QString style);
    void addRunningTaskOnUI(Task *task);

    void addOneServerOnUI(ModelServer *modelServer, QString style);
    void addOneServerOnUI(DataServer *dataServer, QString style);

    //turn page type first firstFull last middle
    void initTurnPage(QString turnPageType);
    void btnTurnPageClicked();

    void popChooseDataMethodWidget();


private:
    QString _serverId;
    QString _fileId;
    QString _listType;
    QString _favorId;
    int _currentPageIndex;

    bool _isCheckable;

    QWidget *_widgetList;
    QWidget *_widgetTurnPage;

    QSharedPointer<ModelServiceBLL> _modelServiceBLL;
    QSharedPointer<ModelServerBLL> _modelServerBLL;
    QSharedPointer<DataServerBLL> _dataServerBLL;
    QSharedPointer<DataServiceBLL> _dataServiceBLL;
    QSharedPointer<DataMappingBLL> _dataMappingBLL;
    QSharedPointer<DataRefactorBLL> _dataRefactorBLL;
    QSharedPointer<DataFileBll> _dataFileBLL;
    QSharedPointer<FavorBLL> _favorBLL;
    QSharedPointer<TaskBLL> _taskBLL;



signals:
    void signalAddFolderOnFileLink(QString fileId, QString fileName);

    void signalAddFavorSidebar(QString serverId, QString serviceId, QString serviceType);

    void signalSwitchPage(QString pageType);
    void signalChangeModelServerTopUI(QString serverId);

    void signalChangeDataMapTaskConfigUI(QString serverId, QString dataMapId);
    void signalChangeDataMapTaskConfigUIByTask(Task *task);
    void signalChangeDataRefactorTaskConfigUI(QString serverId, QString refactorId, QString methodName);
    void signalChangeDataRefactorTaskConfigUIByTask(Task *task);














};

#endif // OGMLISTWIDGET_H
