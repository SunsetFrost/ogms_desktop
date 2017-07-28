#include <QApplication>
#include "OgmCommon/ogmuihelper.h"
#include "OgmUI/ogmmainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/png/png/ProgramIcon.png"));

    OgmUiHelper::setMyFont();
    a.setFont(QFont(OgmUiHelper::g_fontName));
    OgmUiHelper::setStyle(OgmUiHelper::g_styleName);

    OgmMainWidget widget;
    widget.show();

    return a.exec();
}
