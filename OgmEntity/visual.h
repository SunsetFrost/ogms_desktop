#ifndef VISUAL_H
#define VISUAL_H

#include <QString>
#include <QList>

class VisualPrama
{
public:
    VisualPrama();
public:
    QString name;
    QString type;
    QString desc;
    QString schema;
    QString fileName;
    QString fileId;
};

///////////////////////////////

class VisualFormat
{
public:
    VisualFormat();

public:
    QString name;
    QList<VisualPrama*> pramaList;
};

/////////////////////////

class Visual
{
public:
    Visual();

public:
    QString id;
    QString name;
    QString desc;
    QList<VisualFormat*> formatList;
};

Q_DECLARE_METATYPE(Visual*)

////////////////////





#endif // VISUAL_H
