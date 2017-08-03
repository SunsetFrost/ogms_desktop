#include "taskdal.h"

#include "OgmCommon/ogmnetwork.h"

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

QString TaskDAL::runDatamapTask(QString serverIp, QString datamapId, QString inputId, QString inputName, QString outputPId, QString outputName, QString callType)
{
    QString request="http://"+serverIp+"/datamap/use/call?id="+datamapId+"&in_oid="+inputId+"&in_filename="+inputName+"&out_dir="+outputPId+"&out_filename="+outputName+"&callType="+callType+"&username=admin";
    QByteArray result=OgmNetWork::get(request);

    QString strResult=result;
    return strResult;
}

QString TaskDAL::runDataRefactorTask(QString serverIp, Task *task)
{
    QString request="http://"+serverIp+"/refactor/call?id="+task->getDataRefactorTaskConfig()->id+"&method="+task->getDataRefactorTaskConfig()->methodName+"&username=admin";
    for(int i=0; i<task->getDataRefactorTaskConfig()->paramList.count(); ++i){
        request.append("&params[]={\"oid\":\""+task->getDataRefactorTaskConfig()->paramList[i].oid+"\",\"filename\":\""+task->getDataRefactorTaskConfig()->paramList.at(i).fileName+"\",\"pid\":\""+task->getDataRefactorTaskConfig()->paramList.at(i).pid+"\",\"iotype\":\""+task->getDataRefactorTaskConfig()->paramList.at(i).ioType+"\"}");
    }

    QByteArray result=OgmNetWork::get(request);

    QString strResult=result;
    return strResult;
}

QVariant TaskDAL::getDataTaskRecords(QString serverIp, QString instanceId, QString type)
{
    QString request="http://"+serverIp+"/common/records?guid="+instanceId+"&type="+type;
    QByteArray result=OgmNetWork::get(request);
    QString strResult=result;

    if(strResult=="[]"){
        bool isFinish=false;
        QVariant varResult(isFinish);
        return varResult;
    }
    else{
        QVariant varResult(strResult);
        return varResult;
    }
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

    if(task->type=="DataMap"){
        DataMapTaskConfig *dataMapTask=task->getDataMapTaskConfig();

        QDomElement elementDataTaskConfig=doc->createElement("DataMapConfig");

        attr=doc->createAttribute("id");
        attr.setValue(dataMapTask->id);
        elementDataTaskConfig.setAttributeNode(attr);

        attr=doc->createAttribute("serverId");
        attr.setValue(dataMapTask->serverId);
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
    else if(task->type=="DataRefactor"){
        DataRefactorTaskConfig *dataRefactorTask=task->getDataRefactorTaskConfig();

        QDomElement elementRefactorConfig=doc->createElement("DataRefactorConfig");

        attr=doc->createAttribute("id");
        attr.setValue(dataRefactorTask->id);
        elementRefactorConfig.setAttributeNode(attr);

        attr=doc->createAttribute("serverId");
        attr.setValue(dataRefactorTask->serverId);
        elementRefactorConfig.setAttributeNode(attr);

        attr=doc->createAttribute("methodName");
        attr.setValue(dataRefactorTask->methodName);
        elementRefactorConfig.setAttributeNode(attr);

        elementTask.appendChild(elementRefactorConfig);

        for(int i=0; i<dataRefactorTask->paramList.count(); ++i){
            QDomElement elementParam=doc->createElement("RefactorParam");

            attr=doc->createAttribute("oid");
            attr.setValue(dataRefactorTask->paramList[i].oid);
            elementParam.setAttributeNode(attr);

            attr=doc->createAttribute("filename");
            attr.setValue(dataRefactorTask->paramList[i].fileName);
            elementParam.setAttributeNode(attr);

            attr=doc->createAttribute("pid");
            attr.setValue(dataRefactorTask->paramList[i].pid);
            elementParam.setAttributeNode(attr);

            attr=doc->createAttribute("iotype");
            attr.setValue(dataRefactorTask->paramList[i].ioType);
            elementParam.setAttributeNode(attr);

            elementRefactorConfig.appendChild(elementParam);
        }
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

        QDomElement elementDataMapConfig=elementTask.firstChildElement("DataMapConfig");
        dataMapTask->id=elementDataMapConfig.attributeNode("id").value();
        dataMapTask->serverId=elementDataMapConfig.attributeNode("serverId").value();
        dataMapTask->calltype=elementDataMapConfig.attributeNode("callType").value();

        QDomElement elementInput=elementDataMapConfig.firstChildElement("Input");
        dataMapTask->inputId=elementInput.attributeNode("id").value();
        dataMapTask->inputFilename=elementInput.attributeNode("filename").value();

        QDomElement elementOutput=elementDataMapConfig.firstChildElement("Output");
        dataMapTask->outputDirId=elementOutput.attributeNode("dirid").value();
        dataMapTask->outputFilename=elementOutput.attributeNode("filename").value();

        task->setTaskConfig(dataMapTask);
    }
    else if(task->type=="DataRefactor"){
        DataRefactorTaskConfig *refactorTask=new DataRefactorTaskConfig();

        QDomElement elementReafactorConfig=elementTask.firstChildElement("DataRefactorConfig");
        refactorTask->id=elementReafactorConfig.attributeNode("id").value();
        refactorTask->serverId=elementReafactorConfig.attributeNode("serverId").value();
        refactorTask->methodName=elementReafactorConfig.attributeNode("methodName").value();

        QDomNodeList nodeParamList=elementReafactorConfig.childNodes();
        QList<TASKREFACTORPARAM> paramList;
        for(int i=0; i<nodeParamList.size(); ++i){
            TASKREFACTORPARAM param;
            param.oid=nodeParamList.at(i).toElement().attributeNode("oid").value();
            param.fileName=nodeParamList.at(i).toElement().attributeNode("filename").value();
            param.pid=nodeParamList.at(i).toElement().attributeNode("pid").value();
            param.ioType=nodeParamList.at(i).toElement().attributeNode("iotype").value();

            paramList.append(param);
        }
        refactorTask->paramList=paramList;

        task->setTaskConfig(refactorTask);
    }
}













