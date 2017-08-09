#include "task.h"

Task::Task()
{

}

ModelTaskConfig *Task::getModelTaskConfig()
{
    return _modelTaskConfig;
}

DataMapTaskConfig *Task::getDataMapTaskConfig()
{
    return _dataMapTaskConfig;
}

DataRefactorTaskConfig *Task::getDataRefactorTaskConfig()
{
    return _dataRefactorConfig;
}

void Task::setTaskConfig(ModelTaskConfig *modelConfig)
{
    _modelTaskConfig=modelConfig;
}

void Task::setTaskConfig(DataMapTaskConfig *dataMapConfig)
{
    _dataMapTaskConfig=dataMapConfig;
}

void Task::setTaskConfig(DataRefactorTaskConfig *dataRefactorConfig)
{
    _dataRefactorConfig=dataRefactorConfig;
}

ModelTaskConfig::ModelTaskConfig()
{

}

DataMapTaskConfig::DataMapTaskConfig()
{

}

DataRefactorTaskConfig::DataRefactorTaskConfig()
{

}

EventTaskConfig::EventTaskConfig()
{

}
