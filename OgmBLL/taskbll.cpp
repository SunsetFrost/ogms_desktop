#include "taskbll.h"

TaskBLL::TaskBLL()
{
    _taskDAL=QSharedPointer<TaskDAL>(new TaskDAL);
}

Task *TaskBLL::getTaskById(QString id)
{
    Task *task=_taskDAL.data()->getTaskById(id);
    return task;
}

QList<Task *> TaskBLL::getAllTask()
{
    QList<Task*> taskList=_taskDAL.data()->getAllTask();
    return taskList;
}

void TaskBLL::saveTask(Task *task)
{
    _taskDAL.data()->saveTask(task);
}

void TaskBLL::saveAsTask(Task *task, QString savePath)
{
    _taskDAL.data()->saveAsTask(task, savePath);
}

void TaskBLL::deleteTask(QString id)
{
    _taskDAL.data()->deleteTask(id);
}

void TaskBLL::changeTaskRunState(QString taskId, QString taskRunState)
{
    _taskDAL.data()->changeTaskRunState(taskId, taskRunState);
}
