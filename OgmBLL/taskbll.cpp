#include "taskbll.h"

#include <QTimer>
#include <QEventLoop>

TaskBLL::TaskBLL()
{
    _taskDAL=QSharedPointer<TaskDAL>(new TaskDAL);
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL);
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

QList<Task *> TaskBLL::getSpecificTaskListFromTaskList(QList<Task *> taskList, QString taskRunState, QString taskType)
{
    QList<Task*> specificList;
    for(int i=0; i<taskList.count(); ++i){
        if(!taskRunState.isEmpty()){
            if(taskList.at(i)->runstate!=taskRunState)
                continue;
        }
        if(!taskType.isEmpty()){
            if(taskList.at(i)->type!=taskType)
                continue;
        }
        specificList.append(taskList.at(i));
    }
    return specificList;
}

QString TaskBLL::runDatamapTask(Task *task)
{
    DataServer *server=_dataServerDAL.data()->getServerById(task->getDataMapTaskConfig()->serverId);

    QString instanceId= _taskDAL.data()->runDatamapTask(server->ip, task->getDataMapTaskConfig()->id, task->getDataMapTaskConfig()->inputId, task->getDataMapTaskConfig()->inputFilename, task->getDataMapTaskConfig()->outputDirId, task->getDataMapTaskConfig()->outputFilename, task->getDataMapTaskConfig()->calltype);

    //polling model run info until model run finish
    bool isFinish=false;
    while(isFinish==false){
        QEventLoop timeLoop;
        QTimer::singleShot(3000, &timeLoop, SLOT(quit()));
        timeLoop.exec();
        isFinish=isTaskFinish(server->ip, instanceId, "datamap");
    }

    QString result=_taskDAL.data()->getDataTaskRecords(server->ip, instanceId, "datamap").toString();
    return result;
}

QString TaskBLL::runDataRefactorTask(Task *task)
{
    DataServer *server=_dataServerDAL.data()->getServerById(task->getDataRefactorTaskConfig()->serverId);

    QString instanceId=_taskDAL.data()->runDataRefactorTask(server->ip, task);

    //polling model run info until model run finish
    bool isFinish=false;
    while(isFinish==false){
        QEventLoop timeLoop;
        QTimer::singleShot(3000, &timeLoop, SLOT(quit()));
        timeLoop.exec();
        isFinish=isTaskFinish(server->ip, instanceId, "refactor");
    }

    QString result=_taskDAL.data()->getDataTaskRecords(server->ip, instanceId, "refactor").toString();
    return result;
}

bool TaskBLL::isTaskFinish(QString serverIp, QString instanceId, QString type)
{
    QVariant varRecord=_taskDAL.data()->getDataTaskRecords(serverIp, instanceId, type);

    QString typeName=varRecord.typeName();
    if(typeName=="bool"){
        return false;
    }
    else
        return true;
}
