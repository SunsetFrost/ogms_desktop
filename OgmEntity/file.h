#ifndef FILE_H
#define FILE_H

#include <QString>

class DataFile
{
public:
    DataFile();

public:
    QString id;
    QString name;
    QString type;
    QString dataTime;
    QString size;
    QString parentId;
};

///////////////////////////////
class ModelFile
{
public:
    ModelFile();

};

#endif // FILE_H
