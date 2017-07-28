#include "task.h"

Task::Task()
{

}

DataMapTaskConfig *Task::getDataMapTaskConfig()
{
    return _dataMapTaskConfig;
}

void Task::setTaskConfig(DataMapTaskConfig *dataMapConfig)
{
    _dataMapTaskConfig=dataMapConfig;
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
