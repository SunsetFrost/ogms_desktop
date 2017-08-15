#ifndef TASKDAL_H
#define TASKDAL_H

#include <QList>
#include <QDir>
#include <QDomDocument>
#include <QTextStream>

#include "OgmEntity/task.h"

class TaskDAL
{
public:
    TaskDAL();

    Task* getTaskById(QString id);
    QList<Task*> getAllTask();

    void saveTask(Task *task);
    void saveAsTask(Task *task, QString savePath);

    void deleteTask(QString id);

    void changeTaskRunState(QString taskId, QString taskRunState);

    //run
    QString runDatamapTask(QString serverIp, QString datamapId, QString inputId, QString inputName, QString outputPId, QString outputName, QString callType);
    QString runDataRefactorTask(QString serverIp, Task *task);
    QVariant getDataTaskRecords(QString serverIp, QString instanceId, QString type);

    QString runModelTask(QString serverIp, Task *task);
    ModelTaskConfig* getStateInfo(QString serverIp, QString modelId);

    QString uploadFileToModelServer(QString serverIp, QString filePath);
    QString uploadFileStreamToModelServer(QString serverIp, QString fileStream);

    QString getModelRunInstanceId(QString serverIp, Task *task);
    double getModelRunInstanceInfo(QString serverIp, QString msrId, Task *task);
    QString getModelRunResultByModelFileId(QString serverIp, QString dataId);



private:
    void task2xml(Task *task, QDomDocument *doc);
    void xml2task(QDomDocument *doc, Task *task);
    ModelTaskConfig* json2state(QByteArray json);

private:
    static QString taskPath;
};



#endif // TASKDAL_H
