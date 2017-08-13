#ifndef OGMVISUALWIDGET_H
#define OGMVISUALWIDGET_H

#include <QWidget>
#include <QWebEngineView>

class OgmVisualWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmVisualWidget(QWidget *parent = 0);

    void changeVisualUrl(QString url);

private:
    void initWidget();

    QWebEngineView *_view;
};

#endif // OGMVISUALWIDGET_H
