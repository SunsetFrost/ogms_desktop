#include "taskbll.h"
#include "OgmCommon/ogmlisthelper.h"

#include <QTimer>
#include <QEventLoop>

TaskBLL::TaskBLL()
{
    _taskDAL=QSharedPointer<TaskDAL>(new TaskDAL);

    _modelServerDAL=QSharedPointer<ModelServerDAL>(new ModelServerDAL);
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

Task *TaskBLL::createModelTask(QString serverId, QString modelId)
{
    ModelServer *server=_modelServerDAL.data()->getServerById(serverId);

    Task *task=new Task();
    task->uid=OgmHelper::createUId();
    task->type="Model";

    ModelTaskConfig *modelTaskConfig=_taskDAL.data()->getStateInfo(server->ip, modelId);
    modelTaskConfig->serverId=serverId;
    modelTaskConfig->modelId=modelId;

    task->setTaskConfig(modelTaskConfig);
    return task;
}

QList<Task *> TaskBLL::getSpecificTaskListFromTaskList(QList<Task *> taskList, QString taskRunState, QString taskType)
{
    QList<Task*> specificList;
    for(int i=0; i<taskList.count(); ++i){
        if(!taskRunState.isEmpty()){
            if(taskList.at(i)->runstate=="Prepare" && taskRunState=="ToRun"){

            }
            else if(taskList.at(i)->runstate!=taskRunState)
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
        isFinish=isRunningTaskFinish(server->ip, instanceId, "datamap");
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
        isFinish=isRunningTaskFinish(server->ip, instanceId, "refactor");
    }

    QString result=_taskDAL.data()->getDataTaskRecords(server->ip, instanceId, "refactor").toString();
    return result;
}

QString TaskBLL::runModelTask(Task *task)
{
    ModelServer *server=_modelServerDAL.data()->getServerById(task->getModelTaskConfig()->serverId);

    //upload data
    for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
        if(task->getModelTaskConfig()->eventList.at(i)->eventType=="response"){
            task->getModelTaskConfig()->eventList.at(i)->dataFromModelId=_taskDAL.data()->uploadFileToModelServer(server->ip ,task->getModelTaskConfig()->eventList.at(i)->dataPath);
        }
    }
    //run model  get instanceId
    QString instanceId=_taskDAL.data()->getModelRunInstanceId(server->ip, task);
    //polling until model finish
    double runTime=0;
    while(runTime<0.0001){
        QEventLoop timeLoop;
        QTimer::singleShot(3000, &timeLoop, SLOT(quit()));
        timeLoop.exec();
        runTime=_taskDAL.data()->getModelRunInstanceInfo(server->ip, instanceId, task);
    }
    //get result
    QList<QString> resultList;
    for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
        if(task->getModelTaskConfig()->eventList.at(i)->eventType=="noresponse"){
            QString result=_taskDAL.data()->getModelRunResultByModelFileId(server->ip, task->getModelTaskConfig()->eventList.at(i)->dataFromModelId);
            resultList.append(result);

            QString filePath=QDir::currentPath()+"/result/"+task->getModelTaskConfig()->eventList.at(i)->dataFromModelId+task->uid+".xml";
            QFile file(filePath);
            file.open(QIODevice::WriteOnly | QIODevice::Append );
            QTextStream ts(&file);
            ts<<result<<endl;
            file.close();
        }
    }

    task->runstate="Finish";
    _taskDAL.data()->saveTask(task);

    //TODO task run success or error
    return QString();
}

bool TaskBLL::isRunningTaskFinish(QString serverIp, QString instanceId, QString type)
{
    QVariant varRecord=_taskDAL.data()->getDataTaskRecords(serverIp, instanceId, type);

    QString typeName=varRecord.typeName();
    if(typeName=="bool"){
        return false;
    }
    else
        return true;
}

bool TaskBLL::isTaskInfoComplete(Task *task)
{
    if(task->type=="DataMap"){
        if(task->getDataMapTaskConfig()->calltype=="" || task->getDataMapTaskConfig()->inputId=="" || task->getDataMapTaskConfig()->outputFilename==""){
            return false;
        }
        else
            return true;
    }
    if(task->type=="DataRefactor"){
        for(int i=0; i<task->getDataRefactorTaskConfig()->paramList.count(); ++i){
            if(task->getDataRefactorTaskConfig()->paramList.at(i).fileName==""){
                return false;
            }
        }
        return true;
    }
    if(task->type=="Model"){
        for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
            if(task->getModelTaskConfig()->eventList.at(i)->eventType=="response" && task->getModelTaskConfig()->eventList.at(i)->dataPath==""){
                return false;
            }
        }
        return true;
    }
}















