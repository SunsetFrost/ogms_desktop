#ifndef OGMUIHELPER_H
#define OGMUIHELPER_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QFile>
#include <QtWidgets/QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QToolButton>
#include <QColor>
#include <QDesktopWidget>
#include <QLayout>

class OgmUiHelper
{
public:
    explicit OgmUiHelper();

    static QString g_styleName;
    static QString g_title;
    static QString g_fontName;

    static OgmUiHelper *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new OgmUiHelper;
            }
        }

        return self;
    }

    //set qss
    static void setStyle(const QString &qssFile)
    {
        QFile file(qssFile);

        if (file.open(QFile::ReadOnly)) {
            QString qss = QLatin1String(file.readAll());
            qApp->setStyleSheet(qss);
            QString PaletteColor = qss.mid(20, 7);
            qApp->setPalette(QPalette(QColor(PaletteColor)));
            file.close();
        }
    }

    static void setFormToCenter(QWidget *frm)
    {
        int frmX=frm->width();
        int frmY=frm->height();
        QDesktopWidget w;
        int deskWidth=w.availableGeometry().width();
        int deskHeight=w.availableGeometry().height();
        QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
        frm->move(movePoint);
    }

    //set font
    static void setMyFont()
    {
        int fontId=QFontDatabase::addApplicationFont(":/font/font/opensans.ttf");
        g_fontName=QFontDatabase::applicationFontFamilies(fontId).at(0);
    }

    void setIcon(QLabel *lab, QChar c);
    void setIcon(QAbstractButton *btn, QChar c);
    void setMyIcon(QLabel &lab, QChar c);

    void setButtonIcon(QToolButton *btn, int intIcon, QString strName, int spaceing);
    void setButtonIcon(QToolButton *btn, int intIcon, QString strName);
    void setNavButtonIcon(QToolButton *btn, int intIcon, QString strName, QString iconStyleName, QString textStyleName);

private:
    static OgmUiHelper *self;
    QFont iconFont;

};




























#endif // OGMUIHELPER_H
