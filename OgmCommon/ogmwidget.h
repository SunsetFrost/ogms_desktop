#ifndef OGMWIDGET_H
#define OGMWIDGET_H

#include <QWidget>

class OgmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OgmWidget(bool dragBorder, bool hasShadow, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent*);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mousePressEvent(QMouseEvent *event);

    bool eventFilter(QObject *, QEvent *);

    void region(const QPoint &cursorGlobalPoint);

    void setDragWidgetName(QString dragWidgetName);

private:
    static const int widgetPadding;

    enum Direction{
        UP=0,
        DOWN=1,
        LEFT,
        RIGHT,
        LEFTTOP,
        LEFTBOTTOM,
        RIGHTBOTTOM,
        RIGHTTOP,
        NONE
    };

    bool isLeftPressDown;

    QPoint dragPosition;

    Direction dir;

    QString _dragWidgetName;

    bool _dragBorder;

    bool _hasShadow;
};

#endif // OGMWIDGET_H
