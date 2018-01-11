#include "taskdal.h"

#include "OgmCommon/ogmsetting.h"
#include "OgmCommon/ogmnetwork.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

QString TaskDAL::taskPath=QDir::currentPath()+"/task";

TaskDAL::TaskDAL()
{

}

Task *TaskDAL::getTaskById(QString id)
{
    QDomDocument *doc=new QDomDocument();
    QString taskFilePath=OgmSetting::taskPath+"/"+id+".task";
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
    QDir dir(OgmSetting::taskPath);
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
    QString taskFileName=OgmSetting::taskPath+"/"+task->uid+".task";
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
    QString taskFileName=OgmSetting::taskPath+"/"+id+".task";
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
    QString request="http://"+serverIp+"/datamap/use/call?id="+datamapId+"&in_oid="+inputId+"&in_filename="+inputName+"&out_dir="+outputPId+"&out_filename="+outputName+"&callType="+callType+"&username="+OgmSetting::dataServerUserName;
    QByteArray result=OgmNetWork::get(request);

    QString strResult=result;
    return strResult;
}

QString TaskDAL::runDataRefactorTask(QString serverIp, Task *task)
{
    QString request="http://"+serverIp+"/refactor/call?id="+task->getDataRefactorTaskConfig()->id+"&method="+task->getDataRefactorTaskConfig()->methodName+"&username="+OgmSetting::dataServerUserName;
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

ModelTaskConfig *TaskDAL::getStateInfo(QString serverIp, QString modelId)
{
    QString strRequest="http://"+serverIp+"/modelser/inputdata/json/"+modelId;

    QByteArray byteResult=OgmNetWork::get(strRequest);

    return json2state(byteResult);
}

QString TaskDAL::getModelRunResultByModelFileId(QString serverIp, QString dataId)
{
    QString url="http://"+serverIp+"/geodata/"+dataId;

    QNetworkAccessManager net;
    QNetworkReply *reply=net.get(QNetworkRequest(url));

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray result=reply->readAll();
    return QString::fromUtf8(result);
}

QString TaskDAL::uploadFileToModelServer(QString serverIp, QString filePath)
{
    QString url="http://"+serverIp+"/geodata?type=file";

    //config upload data
    QByteArray data;
    QString crlf="\r\n";
    QString b=QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();
    QString boundary="---------------------------"+b;
    QString endBoundary=crlf+"--"+boundary+"--"+crlf;
    QString contentType="multipart/form-data; boundary="+boundary;
    boundary="--"+boundary+crlf;
    QByteArray bond=boundary.toUtf8();

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"myfile\"; filename=\""+QString(filePath+"\""+crlf).toUtf8()));
    data.append("Content-Type:application/xml""\r\n\r\n");
    data.append(crlf.toUtf8());
    data.append(file.readAll());
    data.append(endBoundary.toUtf8());

    file.close();

    //config qt network
    QNetworkAccessManager net;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QNetworkReply *reply=net.post(request, data);
    QEventLoop eventLoop;

    //config event loop
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    //result data
    QByteArray result=reply->readAll();

    QJsonParseError jsonError;
    QJsonObject json=QJsonDocument::fromJson(result, &jsonError).object();
    QString dataId=json.value("gd_id").toString();

    return dataId;
}

QString TaskDAL::uploadFileStreamToModelServer(QString serverIp, QString fileStream)
{
    QString url="http://"+serverIp+"/geodata?type=file";

    //config upload data
    QByteArray data;
    QString crlf="\r\n";
    QString b=QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();
    QString boundary="---------------------------"+b;
    QString endBoundary=crlf+"--"+boundary+"--"+crlf;
    QString contentType="multipart/form-data; boundary="+boundary;
    boundary="--"+boundary+crlf;
    QByteArray bond=boundary.toUtf8();

    data.append(bond);
    boundary = crlf + boundary;
    bond = boundary.toUtf8();
    data.append(QString("Content-Disposition: form-data; name=\"myfile\"; filename=test.xml"+crlf).toUtf8());
    data.append("Content-Type:application/xml""\r\n\r\n");
    data.append(fileStream.toUtf8());
    data.append(endBoundary.toUtf8());

    //config qt network
    QNetworkAccessManager net;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

    QNetworkReply *reply=net.post(request, data);
    QEventLoop eventLoop;

    //config event loop
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    //result data
    QByteArray result=reply->readAll();

    QJsonParseError jsonError;
    QJsonObject json=QJsonDocument::fromJson(result, &jsonError).object();
    QString dataId=json.value("gd_id").toString();

    return dataId;
}

QString TaskDAL::getModelRunInstanceId(QString serverIp, Task *task)
{
    QString url="http://"+serverIp+"/modelser/"+task->getModelTaskConfig()->modelId+"?ac=run&inputdata=[";
    foreach(EventTaskConfig *event, task->getModelTaskConfig()->eventList){
        if(event->eventType=="response"){
            url.append("{\"StateId\":\""+task->getModelTaskConfig()->stateId+"\",");
            url.append("\"Event\":\""+event->eventName+"\",");
            url.append("\"DataId\":\""+event->dataFromModelId+"\"},");
        }
    }
    url=url.left(url.length()-1);
    url.append("]");

    QNetworkAccessManager net;
    QNetworkReply* reply=net.get(QNetworkRequest(url));

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT (quit()));
    eventLoop.exec();

    QByteArray result=reply->readAll();

    QJsonParseError jsonError;
    QJsonObject json=QJsonDocument::fromJson(result, &jsonError).object();
    QString msrId=json.value("msr_id").toString();

    return msrId;
}

double TaskDAL::getModelRunInstanceInfo(QString serverIp, QString msrId, Task *task)
{
    QString url="http://"+serverIp+"/modelserrun/json/"+msrId;

    QNetworkAccessManager net;
    QNetworkReply *reply=net.get(QNetworkRequest(url));

    QEventLoop eventLoop;
    QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QByteArray result=reply->readAll();

    QJsonParseError jsonError;
    QJsonObject json=QJsonDocument::fromJson(result, &jsonError).object();
    QJsonObject jsonMsr=json.value("data").toObject();
    double msrTime=jsonMsr.value("msr_time").toDouble();

    if(msrTime>0){
        QJsonArray jsonOutput=jsonMsr.value("msr_output").toArray();
        for(int i=0; i<jsonMsr.size(); ++i){
            QString eventName=jsonOutput.at(i).toObject().value("Event").toString();
            QString dataId=jsonOutput.at(i).toObject().value("DataId").toString();

            for(int j=0; j<task->getModelTaskConfig()->eventList.count(); ++j){
                if(task->getModelTaskConfig()->eventList.at(j)->eventName==eventName){
                    task->getModelTaskConfig()->eventList.at(j)->dataFromModelId=dataId;
                }
            }
        }

    }
    return msrTime;
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
    else if(task->type=="Model"){
        ModelTaskConfig *modelTask=task->getModelTaskConfig();
        QDomElement eleModel=doc->createElement("ModelConfig");

        attr=doc->createAttribute("modelId");
        attr.setValue(modelTask->modelId);
        eleModel.setAttributeNode(attr);

        attr=doc->createAttribute("stateId");
        attr.setValue(modelTask->stateId);
        eleModel.setAttributeNode(attr);

        attr=doc->createAttribute("serverId");
        attr.setValue(modelTask->serverId);
        eleModel.setAttributeNode(attr);

        attr=doc->createAttribute("stateName");
        attr.setValue(modelTask->serverId);
        eleModel.setAttributeNode(attr);

        elementTask.appendChild(eleModel);

        for(int i=0; i<modelTask->eventList.count(); ++i){
            QDomElement eleEvent=doc->createElement("Event");

            attr=doc->createAttribute("eventName");
            attr.setValue(modelTask->eventList.at(i)->eventName);
            eleEvent.setAttributeNode(attr);

            attr=doc->createAttribute("eventDes");
            attr.setValue(modelTask->eventList.at(i)->eventDes);
            eleEvent.setAttributeNode(attr);

            attr=doc->createAttribute("eventType");
            attr.setValue(modelTask->eventList.at(i)->eventType);
            eleEvent.setAttributeNode(attr);

            eleModel.appendChild(eleEvent);

            QDomElement eleData=doc->createElement("Data");

            attr=doc->createAttribute("dataType");
            attr.setValue(modelTask->eventList.at(i)->dataType);
            eleData.setAttributeNode(attr);

            attr=doc->createAttribute("dataServerId");
            attr.setValue(modelTask->eventList.at(i)->dataServerId);
            eleData.setAttributeNode(attr);

            attr=doc->createAttribute("modelServerId");
            attr.setValue(modelTask->eventList.at(i)->modelServerId);
            eleData.setAttributeNode(attr);

            attr=doc->createAttribute("modelId");
            attr.setValue(modelTask->eventList.at(i)->dataFromModelId);
            eleData.setAttributeNode(attr);

            attr=doc->createAttribute("dataId");
            attr.setValue(modelTask->eventList.at(i)->dataFromDataId);
            eleData.setAttributeNode(attr);

            attr=doc->createAttribute("dataPath");
            attr.setValue(modelTask->eventList.at(i)->dataPath);
            eleData.setAttributeNode(attr);

            eleEvent.appendChild(eleData);
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
    else if(task->type=="Model"){
        ModelTaskConfig *modelTask=new ModelTaskConfig();

        QDomElement eleModel=elementTask.firstChildElement("ModelConfig");
        modelTask->modelId=eleModel.attributeNode("modelId").value();
        modelTask->stateId=eleModel.attributeNode("stateId").value();
        modelTask->serverId=eleModel.attributeNode("serverId").value();
        modelTask->stateName=eleModel.attributeNode("stateName").value();

        QDomNodeList nodeEventList=eleModel.childNodes();
        QList<EventTaskConfig*> eventList;
        for(int i=0; i<nodeEventList.size(); ++i){
            EventTaskConfig *event=new EventTaskConfig();
            event->eventName=nodeEventList.at(i).toElement().attributeNode("eventName").value();
            event->eventDes=nodeEventList.at(i).toElement().attributeNode("eventDes").value();
            event->eventType=nodeEventList.at(i).toElement().attributeNode("eventType").value();

            QDomElement eleData=nodeEventList.at(i).toElement().firstChildElement();
            event->dataType=eleData.attributeNode("dataType").value();
            event->dataServerId=eleData.attributeNode("dataServerId").value();
            event->modelServerId=eleData.attributeNode("modelServerId").value();
            event->dataFromModelId=eleData.attributeNode("modelId").value();
            event->dataFromDataId=eleData.attributeNode("dataId").value();
            event->dataPath=eleData.attributeNode("dataPath").value();

            eventList.append(event);
        }
        modelTask->eventList=eventList;
        task->setTaskConfig(modelTask);
    }
}

ModelTaskConfig *TaskDAL::json2state(QByteArray json)
{
    ModelTaskConfig *modelTaskConfig=new ModelTaskConfig();
    QList<EventTaskConfig*> eventList;
    QJsonParseError jsonError;
    QJsonObject jsonObj=QJsonDocument::fromJson(json, &jsonError).object();
    if(jsonError.error== QJsonParseError::NoError){
        QJsonObject jsData=jsonObj.value("data").toObject();
        QJsonArray jsState=jsData.value("States").toArray();

        QJsonObject jsStateItem=jsState.at(0).toObject();
        QJsonObject jsStateRoot=jsStateItem.value("$").toObject();
        modelTaskConfig->stateId=jsStateRoot.value("id").toString();
        modelTaskConfig->stateName=jsStateRoot.value("name").toString();
        //modelState.description=jsStateRoot.value("description").toString();
        //modelState.type=jsStateRoot.value("type").toString();

        QJsonArray jsEventArray=jsStateItem.value("Event").toArray();
        for(int i=0; i<jsEventArray.size(); ++i){
            EventTaskConfig *event=new EventTaskConfig();

            QJsonObject jsEvent=jsEventArray.at(i).toObject();
            QJsonObject jsEventRoot=jsEvent.value("$").toObject();

            event->eventName=jsEventRoot.value("name").toString();
            event->eventType=jsEventRoot.value("type").toString();
            event->eventDes=jsEventRoot.value("description").toString();

            eventList.append(event);
        }

        modelTaskConfig->eventList=eventList;
    }
    return modelTaskConfig;
}













