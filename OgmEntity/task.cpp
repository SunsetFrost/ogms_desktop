#include "task.h"

Task::Task()
{

}

DataMapTaskConfig *Task::getDataMapTaskConfig()
{
    return _dataMapTaskConfig;
}

DataRefactorTaskConfig *Task::getDataRefactorTaskConfig()
{
    return _dataRefactorConfig;
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
