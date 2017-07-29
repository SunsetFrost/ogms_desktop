#ifndef TASKBLL_H
#define TASKBLL_H

#include "OgmDAL/taskdal.h"
#include "OgmDAL/datadal.h"

#include <QSharedPointer>

class TaskBLL
{
public:
    TaskBLL();

    Task* getTaskById(QString id);

    QList<Task*> getAllTask();

    void saveTask(Task *task);

    void saveAsTask(Task *task, QString savePath);

    void deleteTask(QString id);

    void changeTaskRunState(QString taskId, QString taskRunState);

    //run  event loop
    QString runDatamapTask(Task *task);

    bool isTaskFinish(QString serverIp, QString instanceId, QString type);


private:
    QSharedPointer<TaskDAL> _taskDAL;
    QSharedPointer<DataServerDAL> _dataServerDAL;
};





#endif // TASKBLL_H
