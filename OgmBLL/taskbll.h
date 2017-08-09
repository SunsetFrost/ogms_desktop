#ifndef TASKBLL_H
#define TASKBLL_H

#include "OgmDAL/taskdal.h"

#include "OgmDAL/modeldal.h"
#include "OgmDAL/datadal.h"

#include <QSharedPointer>

class TaskBLL
{
public:
    TaskBLL();

    Task* getTaskById(QString id);
    QList<Task*> getAllTask();
    QList<Task*> getSpecificTaskListFromTaskList(QList<Task*> taskList, QString taskRunState, QString taskType);

    void saveTask(Task *task);
    void saveAsTask(Task *task, QString savePath);

    void deleteTask(QString id);

    void changeTaskRunState(QString taskId, QString taskRunState);

    //create task
    Task* createModelTask(QString serverId, QString modelId);//only allow  model have just on state


    //run  event loop
    QString runDatamapTask(Task *task);
    QString runDataRefactorTask(Task *task);
    QString runModelTask(Task *task);

    bool isRunningTaskFinish(QString serverIp, QString instanceId, QString type);
    bool isTaskInfoComplete(Task *task);


private:
    QSharedPointer<TaskDAL> _taskDAL;
    QSharedPointer<DataServerDAL> _dataServerDAL;
    QSharedPointer<ModelServerDAL> _modelServerDAL;
};





#endif // TASKBLL_H
