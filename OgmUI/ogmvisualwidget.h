#ifndef OGMVISUALWIDGET_H
#define OGMVISUALWIDGET_H

#include <QWidget>

class OgmVisualWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmVisualWidget(QWidget *parent = 0);

private:
    void initWidget();
};

#endif // OGMVISUALWIDGET_H
