#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QList>

class ModelTaskConfig
{
public:
    ModelTaskConfig();

};

///////////////////////////
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

///////////////////////////
class DataRefactorTaskConfig
{
public:
    DataRefactorTaskConfig();

};

////////////////////////////////
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
