#ifndef TASKDAL_H
#define TASKDAL_H

#include <QList>
#include <QDir>
#include <QDomDocument>
#include <QTextStream>

#include "OgmEntity/task.h"

class TaskDAL
{
public:
    TaskDAL();

    Task* getTaskById(QString id);

    QList<Task*> getAllTask();

    void saveTask(Task *task);

    void saveAsTask(Task *task, QString savePath);

    void deleteTask(QString id);

    void changeTaskRunState(QString taskId, QString taskRunState);

private:
    void task2xml(Task *task, QDomDocument *doc);

    void xml2task(QDomDocument *doc, Task *task);

private:
    static QString taskPath;
};

#endif // TASKDAL_H
