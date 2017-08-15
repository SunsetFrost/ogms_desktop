#include "taskbll.h"
#include "OgmCommon/ogmlisthelper.h"
#include "OgmCommon/ogmsetting.h"

#include <QTimer>
#include <QEventLoop>
#include <QDateTime>

TaskBLL::TaskBLL()
{
    _taskDAL=QSharedPointer<TaskDAL>(new TaskDAL);

    _modelServerDAL=QSharedPointer<ModelServerDAL>(new ModelServerDAL);
    _dataServerDAL=QSharedPointer<DataServerDAL>(new DataServerDAL);

    _modelServiceDAL=QSharedPointer<ModelServiceDAL>(new ModelServiceDAL);
    _datamapDAL=QSharedPointer<DataMappingDAL>(new DataMappingDAL);
    _datarefactorDAL=QSharedPointer<DataRefactorDAL>(new DataRefactorDAL);
    _fileDataDAL=QSharedPointer<DataFileDAL>(new DataFileDAL);
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

    //add task result folder
    QString folderId=_fileDataDAL.data()->addFolder(server, "599023d478983d271073c108", task->name, QDateTime::currentDateTime().toString("yyyy-MM-dd"), OgmSetting::dataServerUserName);
    folderId=folderId.split("|").at(1);

    QString instanceId= _taskDAL.data()->runDatamapTask(server->ip, task->getDataMapTaskConfig()->id, task->getDataMapTaskConfig()->inputId, task->getDataMapTaskConfig()->inputFilename, folderId, task->getDataMapTaskConfig()->outputFilename, task->getDataMapTaskConfig()->calltype);

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
    ModelServer *modelServer=_modelServerDAL.data()->getServerById(task->getModelTaskConfig()->serverId);
    DataServer *dataServer=_dataServerDAL.data()->getServerById(OgmSetting::defaultDataServerId);

    //upload data
    for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
        if(task->getModelTaskConfig()->eventList.at(i)->eventType=="response"){
            if(task->getModelTaskConfig()->eventList.at(i)->dataType=="local"){
                            task->getModelTaskConfig()->eventList.at(i)->dataFromModelId=_taskDAL.data()->uploadFileToModelServer(modelServer->ip ,task->getModelTaskConfig()->eventList.at(i)->dataPath);
            }
            else if(task->getModelTaskConfig()->eventList.at(i)->dataType=="remote"){
                QString fileStream=_fileDataDAL.data()->download(dataServer, task->getModelTaskConfig()->eventList.at(i)->dataFromDataId, OgmSetting::dataServerUserName);
                task->getModelTaskConfig()->eventList.at(i)->dataFromModelId=_taskDAL.data()->uploadFileStreamToModelServer(modelServer->ip, fileStream);
            }

        }
    }
    //run model  get instanceId
    QString instanceId=_taskDAL.data()->getModelRunInstanceId(modelServer->ip, task);
    //polling until model finish
    double runTime=0;
    while(runTime<0.0001){
        QEventLoop timeLoop;
        QTimer::singleShot(3000, &timeLoop, SLOT(quit()));
        timeLoop.exec();
        runTime=_taskDAL.data()->getModelRunInstanceInfo(modelServer->ip, instanceId, task);
    }
    //get result
    QList<QString> resultList;
    for(int i=0; i<task->getModelTaskConfig()->eventList.count(); ++i){
        if(task->getModelTaskConfig()->eventList.at(i)->eventType=="noresponse"){
            QString result=_taskDAL.data()->getModelRunResultByModelFileId(modelServer->ip, task->getModelTaskConfig()->eventList.at(i)->dataFromModelId);
            resultList.append(result);

            //add task result folder
            QString folderId=_fileDataDAL.data()->addFolder(dataServer, "599023d478983d271073c108", task->name, QDateTime::currentDateTime().toString("yyyy-MM-dd"), OgmSetting::dataServerUserName);
            folderId=folderId.split("|").at(1);

            //upload result to default data server
            _fileDataDAL.data()->uploadFile(dataServer, folderId, result, task->getModelTaskConfig()->eventList.at(i)->eventName, OgmSetting::dataServerUserName);
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

bool TaskBLL::isTaskConfigInfoComplete(Task *task)
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
            if(task->getModelTaskConfig()->eventList.at(i)->eventType=="response" && task->getModelTaskConfig()->eventList.at(i)->dataType==""){
                return false;
            }
        }
        return true;
    }
}

QString TaskBLL::getDatamapSchema(QString serverId, QString datamapId)
{
    DataServer *server=_dataServerDAL.data()->getServerById(serverId);
    return _datamapDAL.data()->getDataMappingXML(server, datamapId, "xml");
}

QString TaskBLL::getDataRefactorParamSchema(QString serverId, QString refactorId, QString schemaName, QString ioType)
{
    DataServer *server=_dataServerDAL.data()->getServerById(serverId);
    return _datarefactorDAL.data()->getDataRefactorParamSchema(server, refactorId, schemaName, ioType);
}

QString TaskBLL::uploadDataFileToModelServer(QString dataServerId, QString dataFileId, QString modelServerId)
{
    DataServer *dataServer=_dataServerDAL.data()->getServerById(dataServerId);
    ModelServer *modelServer=_modelServerDAL.data()->getServerById(modelServerId);

    QString dataStream=_fileDataDAL.data()->download(dataServer, dataFileId, OgmSetting::dataServerUserName);
    QString modelFileId=_taskDAL.data()->uploadFileStreamToModelServer(modelServer->ip, dataStream);

    return modelFileId;
}

QString TaskBLL::getExampleDataId(QString serverId, QString modelId, QString stateId, QString eventName)
{
    ModelServer *modelServer=_modelServerDAL.data()->getServerById(serverId);
    return _modelServiceDAL.data()->getExampleDataOfOneEvent(modelServer, modelId, stateId, eventName);
}















