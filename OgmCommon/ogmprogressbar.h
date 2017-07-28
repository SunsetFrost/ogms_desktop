#ifndef OGMPROGRESSBAR_H
#define OGMPROGRESSBAR_H

#include <QObject>
#include <QProgressBar>
#include <QTimer>

class OgmProgressBar:public QProgressBar
{
    Q_OBJECT

public:
    explicit OgmProgressBar(QString id, QWidget *parent=0);

public slots:
    void progressBarChange();

public:
    QString getTaskId();
    void setIsFinished(bool isFinished);

private:
    QTimer *_timer;
    QString _id;
    bool _isFinished;

signals:
    void signalProgressBarFinish();
};

#endif // OGMPROGRESSBAR_H
