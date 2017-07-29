#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QList>

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

Q_DECLARE_METATYPE(DataFile*)

///////////////////////////////
class ModelFile
{
public:
    ModelFile();

};



#endif // FILE_H
