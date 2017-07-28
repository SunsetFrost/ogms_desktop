#ifndef OGMPOPWIDGET_H
#define OGMPOPWIDGET_H

#include "OgmCommon/ogmwidget.h"
#include "OgmUI/ogmlistwidget.h"

#include <QVariant>

namespace Ui{
class OgmPopUI;
}

class OgmPopWidget : public OgmWidget
{
    Q_OBJECT

public:
    OgmPopWidget(QString widgetType, QWidget *parent=0);

    void initNewFileWidget();

    void initDeleteFileWidget();

    void initChooseDataFile();

    void initSaveTask();


private:
    Ui::OgmPopUI *_ui;

signals:
    void signalOperationResult(QVariant result);
};

#endif // OGMPOPWIDGET_H
