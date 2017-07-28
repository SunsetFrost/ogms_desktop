#include "taskdal.h"

QString TaskDAL::taskPath=QDir::currentPath()+"/task";

TaskDAL::TaskDAL()
{

}

Task *TaskDAL::getTaskById(QString id)
{
    QDomDocument *doc=new QDomDocument();
    QString taskFilePath=taskPath+"/"+id+".task";
    QFile file(taskFilePath);
    file.open(QIODevice::ReadOnly);
    doc->setContent(&file);
    file.close();

    Task *task=new Task();
    xml2task(doc, task);
    return task;
}

QList<Task *> TaskDAL::getAllTask()
{
    QDir dir(taskPath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);

    QList<Task*> taskList;

    QFileInfoList list=dir.entryInfoList();
    for(int i=0; i<list.size(); ++i){
        QFileInfo fileInfo=list.at(i);
        QString fileName=fileInfo.fileName();
        QString taskId=fileName.split(".")[0];

        Task *task=getTaskById(taskId);
        taskList.append(task);
    }
    return taskList;
}

void TaskDAL::saveTask(Task *task)
{
    QString taskFileName=taskPath+"/"+task->uid+".task";
    QFile file(taskFileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    QDomDocument *doc=new QDomDocument();
    task2xml(task, doc);
    doc->save(out, 4);
}

void TaskDAL::saveAsTask(Task *task, QString savePath)
{
    QString taskFileName=savePath+".task";
    QFile file(taskFileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    QDomDocument *doc=new QDomDocument();
    task2xml(task, doc);
    doc->save(out, 4);
}

void TaskDAL::deleteTask(QString id)
{
    QString taskFileName=taskPath+"/"+id+".task";
    QFile file(taskFileName);
    if(file.exists()){
        file.remove();
    }
}

void TaskDAL::changeTaskRunState(QString taskId, QString taskRunState)
{
    Task *task=getTaskById(taskId);
    task->runstate=taskRunState;
    saveTask(task);
}

void TaskDAL::task2xml(Task *task, QDomDocument *doc)
{
    QDomAttr attr;

    QDomElement elementTask=doc->createElement("Task");
    attr=doc->createAttribute("name");
    attr.setValue(task->name);
    elementTask.setAttributeNode(attr);
    attr=doc->createAttribute("uid");
    attr.setValue(task->uid);
    elementTask.setAttributeNode(attr);
    attr=doc->createAttribute("desc");
    attr.setValue(task->desc);
    elementTask.setAttributeNode(attr);
    attr=doc->createAttribute("type");
    attr.setValue(task->type);
    elementTask.setAttributeNode(attr);
    attr=doc->createAttribute("createTime");
    attr.setValue(task->createTime);
    elementTask.setAttributeNode(attr);
    attr=doc->createAttribute("runState");
    attr.setValue(task->runstate);
    elementTask.setAttributeNode(attr);
    doc->appendChild(elementTask);

    DataMapTaskConfig *dataMapTask=task->getDataMapTaskConfig();
    if(!dataMapTask->id.isEmpty()){
        QDomElement elementDataTaskConfig=doc->createElement("DataMapConfig");

        attr=doc->createAttribute("id");
        attr.setValue(dataMapTask->id);
        elementDataTaskConfig.setAttributeNode(attr);

        attr=doc->createAttribute("callType");
        attr.setValue(dataMapTask->calltype);
        elementDataTaskConfig.setAttributeNode(attr);

        elementTask.appendChild(elementDataTaskConfig);

        QDomElement elementInput=doc->createElement("Input");

        attr=doc->createAttribute("id");
        attr.setValue(dataMapTask->inputId);
        elementInput.setAttributeNode(attr);

        attr=doc->createAttribute("filename");
        attr.setValue(dataMapTask->inputFilename);
        elementInput.setAttributeNode(attr);

        elementDataTaskConfig.appendChild(elementInput);

        QDomElement elementOutput=doc->createElement("Output");

        attr=doc->createAttribute("dirid");
        attr.setValue(dataMapTask->outputDirId);
        elementOutput.setAttributeNode(attr);

        attr=doc->createAttribute("filename");
        attr.setValue(dataMapTask->outputFilename);
        elementOutput.setAttributeNode(attr);

        elementDataTaskConfig.appendChild(elementOutput);
    }

}

void TaskDAL::xml2task(QDomDocument *doc, Task *task)
{
    QDomElement elementTask=doc->documentElement();
    task->uid=elementTask.attributeNode("uid").value();
    task->name=elementTask.attributeNode("name").value();
    task->desc=elementTask.attributeNode("desc").value();
    task->type=elementTask.attributeNode("type").value();
    task->createTime=elementTask.attributeNode("createTime").value();
    task->runstate=elementTask.attributeNode("runState").value();

    if(task->type=="DataMap"){
        DataMapTaskConfig *dataMapTask=new DataMapTaskConfig();

        QDomElement elementDataMapConfig=elementTask.firstChildElement();
        dataMapTask->id=elementDataMapConfig.attributeNode("id").value();
        dataMapTask->calltype=elementDataMapConfig.attributeNode("callType").value();

        QDomElement elementInput=elementDataMapConfig.firstChildElement("Input");
        dataMapTask->inputId=elementInput.attributeNode("id").value();
        dataMapTask->inputFilename=elementInput.attributeNode("filename").value();

        QDomElement elementOutput=elementDataMapConfig.firstChildElement("Output");
        dataMapTask->outputDirId=elementOutput.attributeNode("dirid").value();
        dataMapTask->outputFilename=elementOutput.attributeNode("filename").value();

        task->setTaskConfig(dataMapTask);
    }
}













