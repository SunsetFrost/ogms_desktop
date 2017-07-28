#include "ogmwidget.h"

#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QApplication>

const int OgmWidget::widgetPadding=4;

OgmWidget::OgmWidget(bool dragBorder, bool hasShadow, QWidget *parent)
    : QWidget(parent)
    , _dragBorder(dragBorder)
    , _hasShadow(hasShadow)
{
    qApp->installEventFilter(this);
    isLeftPressDown=false;
    this->dir=NONE;
    this->setMinimumHeight(100);
    this->setMinimumWidth(150);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void OgmWidget::paintEvent(QPaintEvent *)
{
    //custom widget achieve qss
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    if(_hasShadow){
        //border shadow
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10, 10, this->width()-20, this->height()-20);

        p.setRenderHint(QPainter::Antialiasing, true);
        p.fillPath(path, QBrush(Qt::white));

        QColor color(100, 100, 100, 50);
        for(int i=0; i<10; ++i){
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
            color.setAlpha(150 - qSqrt(i)*50);
            p.setPen(color);
            p.drawPath(path);
        }
    }
}

void OgmWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(_dragBorder){
        if(event->button() == Qt::LeftButton) {
            isLeftPressDown = false;
            if(dir != NONE) {
                this->releaseMouse();
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }
    else{
        QWidget::mouseReleaseEvent(event);
    }
}

void OgmWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(_dragBorder){
        QPoint gloPoint = event->globalPos();
        QRect rect = this->rect();
        QPoint tl = mapToGlobal(rect.topLeft());
        QPoint rb = mapToGlobal(rect.bottomRight());

        if(!isLeftPressDown) {
            this->region(gloPoint);
        } else {

            if(dir != NONE) {
                QRect rMove(tl, rb);

                switch(dir) {
                case LEFT:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    break;
                case RIGHT:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    break;
                case UP:
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case DOWN:
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case LEFTTOP:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case RIGHTTOP:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setY(gloPoint.y());
                    break;
                case LEFTBOTTOM:
                    rMove.setX(gloPoint.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case RIGHTBOTTOM:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                default:
                    break;
                }
                this->setGeometry(rMove);
            } else {
                //move(event->globalPos() - dragPosition);
                event->accept();
            }
        }
    }

    QWidget::mouseMoveEvent(event);
}

void OgmWidget::mousePressEvent(QMouseEvent *event)
{
    if(_dragBorder){
        switch(event->button()) {
        case Qt::LeftButton:
            isLeftPressDown = true;
            if(dir != NONE) {
                this->mouseGrabber();
            } else {
                dragPosition = event->globalPos() - this->frameGeometry().topLeft();
            }
            break;
        case Qt::RightButton:
            //this->close();
            break;
        default:
            QWidget::mousePressEvent(event);
        }
    }
    else
        QWidget::mousePressEvent(event);
}

void OgmWidget::region(const QPoint &cursorGlobalPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    if(tl.x() + widgetPadding >= x && tl.x() <= x && tl.y() + widgetPadding >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    } else if(x >= rb.x() - widgetPadding && x <= rb.x() && y >= rb.y() - widgetPadding && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    } else if(x <= tl.x() + widgetPadding && x >= tl.x() && y >= rb.y() - widgetPadding && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= rb.x() && x >= rb.x() - widgetPadding && y >= tl.y() && y <= tl.y() + widgetPadding) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    } else if(x <= tl.x() + widgetPadding && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    } else if( x <= rb.x() && x >= rb.x() - widgetPadding) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }else if(y >= tl.y() && y <= tl.y() + widgetPadding){
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    } else if(y <= rb.y() && y >= rb.y() - widgetPadding) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void OgmWidget::setDragWidgetName(QString dragWidgetName)
{
    this->_dragWidgetName=dragWidgetName;
}

bool OgmWidget::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w=(QWidget*)obj;
    if(w->objectName()!=_dragWidgetName){
        return QObject::eventFilter(obj, evt);
    }

    static QPoint mousePoint;
    static bool mousePressed=false;

    QMouseEvent *event=static_cast<QMouseEvent*>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos()-this->pos() ;
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            this->move(event->globalPos() - mousePoint);
            return true;
        }
    }else if(event->type()== QEvent::MouseButtonDblClick){
        if(this->isMaximized()){
            this->showNormal();
        }
        else {
            this->showMaximized();
        }
    }

    return QObject::eventFilter(obj, evt);
}
