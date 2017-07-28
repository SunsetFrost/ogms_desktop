#include "ogmuihelper.h"

QString OgmUiHelper::g_styleName = ":/css/css/uiCss.css";
QString OgmUiHelper::g_title = " NJGIS  ";
QString OgmUiHelper::g_fontName=QString();
OgmUiHelper *OgmUiHelper::self=0;

OgmUiHelper::OgmUiHelper()
{
    int fontId=QFontDatabase::addApplicationFont(":/font/font/fontawesome-webfont.ttf");
    QString fontName=QFontDatabase::applicationFontFamilies(fontId).at(0);
    iconFont=QFont(fontName);
}

void OgmUiHelper::setIcon(QLabel *lab, QChar c)
{
    lab->setFont(iconFont);
    lab->setText(c);
}

void OgmUiHelper::setIcon(QAbstractButton *btn, QChar c)
{
    btn->setFont(iconFont);
    btn->setText(c);
}

void OgmUiHelper::setMyIcon(QLabel &lab, QChar c)
{
    lab.setFont(iconFont);
    lab.setText(c);
}

void OgmUiHelper::setButtonIcon(QToolButton *btn, int intIcon, QString strName, int spaceing)
{
    QLabel *lblIcon=new QLabel;
    lblIcon->setWindowTitle("left");
    setIcon(lblIcon, QChar(intIcon));
    QLabel *lblText=new QLabel;
    lblText->setWindowTitle("right");
    lblText->setText(strName);
 //   lblText->setFixedWidth(lblWidth);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->setMargin(1);
    layout->addSpacing(spaceing); layout->addWidget(lblIcon); layout->addSpacing(2); layout->addWidget(lblText); layout->addStretch();
    btn->setLayout(layout);
}

void OgmUiHelper::setButtonIcon(QToolButton *btn, int intIcon, QString strName)
{
    QLabel *lblIcon=new QLabel;
    lblIcon->setWindowTitle("left");
    setIcon(lblIcon, QChar(intIcon));
    QLabel *lblText=new QLabel;
    lblText->setWindowTitle("right");
    lblText->setText(strName);
 //   lblText->setFixedWidth(lblWidth);
    QHBoxLayout *layout=new QHBoxLayout;
    layout->setMargin(3);
    layout->addSpacing(12);
    layout->addWidget(lblIcon); layout->addSpacing(2); layout->addWidget(lblText); layout->addStretch();
    btn->setLayout(layout);
}

void OgmUiHelper::setNavButtonIcon(QToolButton *btn, int intIcon, QString strName, QString iconStyleName, QString textStyleName)
{
    btn->setFixedSize(QSize(180, 250));

    QVBoxLayout *layout=new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    btn->setLayout(layout);

    QLabel *lblIcon=new QLabel();
    lblIcon->setWindowTitle(iconStyleName);
    lblIcon->setAlignment(Qt::AlignCenter);
    lblIcon->setFixedSize(btn->width(), btn->height()-40);
    setIcon(lblIcon, QChar(intIcon));
    layout->addWidget(lblIcon);

    QLabel *lblText=new QLabel();
    lblText->setWindowTitle(textStyleName);
    lblText->setAlignment(Qt::AlignCenter);
    lblText->setFixedSize(btn->width(), 40);
    lblText->setText(strName);
    layout->addWidget(lblText);

}
