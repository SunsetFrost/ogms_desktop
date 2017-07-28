#ifndef TASKBLL_H
#define TASKBLL_H

#include "OgmDAL/taskdal.h"

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

private:
    QSharedPointer<TaskDAL> _taskDAL;
};

#endif // TASKBLL_H
