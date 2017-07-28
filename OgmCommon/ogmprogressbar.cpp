#include "ogmprogressbar.h"

OgmProgressBar::OgmProgressBar(QString id, QWidget *parent):_id(id)
{
    _timer=new QTimer();
    connect(_timer, &QTimer::timeout, this, &OgmProgressBar::progressBarChange);
    _timer->start(20);

    this->setRange(0, 1000);
    this->setValue(0);
    this->setAccessibleDescription("progressBar");
    this->setTextVisible(false);
}

void OgmProgressBar::progressBarChange()
{
    this->setValue(this->value()+1);
    if(this->value()>950){
        if(!_isFinished){
            this->setValue(value()-1);
        }
    }
    if(this->value()>=1000){
        QTimer *timer=(QTimer*)sender();
        timer->stop();
        emit signalProgressBarFinish();
    }
}

QString OgmProgressBar::getTaskId()
{
    return _id;
}

void OgmProgressBar::setIsFinished(bool isFinished)
{
    _isFinished=isFinished;
}
