#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QList>

//temp written here  , next add mdl class in model, these info should include in model class
class EventTaskConfig
{
public:
    EventTaskConfig();

    QString eventName;
    QString eventType;
    QString eventDes;

    QString dataType;
    QString modelServerId;
    QString dataServerId;
    QString dataFromModelId;
    QString dataFromDataId;
    QString dataPath;
};

//model task only for one state
class ModelTaskConfig
{
public:
    ModelTaskConfig();

    QString modelId;
    QString serverId;
    QString stateId;
    QString stateName;
    QList<EventTaskConfig*> eventList;
};

///////////////////////////////////////////
class DataMapTaskConfig
{
public:
    DataMapTaskConfig();

public:
    QString id;
    QString serverId;
    QString calltype;
    QString inputId;
    QString inputFilename;
    QString outputDirId;
    QString outputFilename;


};

/////////////////////////////////////////////////
struct TASKREFACTORPARAM{
    QString oid;
    QString fileName;
    QString pid;
    QString ioType;
};

class DataRefactorTaskConfig
{
public:
    DataRefactorTaskConfig();

public:
    QString id;
    QString serverId;
    QString methodName;
    QList<TASKREFACTORPARAM> paramList;
};

///////////////////////////////////////////////
class Task
{
public:
    Task();

public:
    QString uid;
    QString name;
    QString desc;
    QList<QString> tagList;
    QString type;
    QString createTime;
    QString completeTime;
    QString runstate;

    ModelTaskConfig* getModelTaskConfig();
    DataMapTaskConfig* getDataMapTaskConfig();
    DataRefactorTaskConfig* getDataRefactorTaskConfig();

    void setTaskConfig(ModelTaskConfig *modelConfig);
    void setTaskConfig(DataMapTaskConfig *dataMapConfig);
    void setTaskConfig(DataRefactorTaskConfig *dataRefactorConfig);

private:
    ModelTaskConfig *_modelTaskConfig;
    DataMapTaskConfig *_dataMapTaskConfig;
    DataRefactorTaskConfig *_dataRefactorConfig;
};

Q_DECLARE_METATYPE(Task*)

#endif // TASK_H
