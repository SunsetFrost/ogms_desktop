QT       += core gui webenginewidgets network xml

CONFIG += c++11

TARGET = OGMS
TEMPLATE = app
MOC_DIR                  = temp/moc
RCC_DIR                  = temp/rcc
UI_DIR                   = temp/ui
OBJECTS_DIR              = temp/obj
DESTDIR                  = bin

INCLUDEPATH  +=$$PWD

include($$PWD/OgmCommon/OgmCommon.pro)
include($$PWD/OgmEntity/OgmEntity.pro)
include($$PWD/OgmDAL/OgmDAL.pro)
include($$PWD/OgmBLL/OgmBLL.pro)
include($$PWD/OgmUI/OgmUI.pro)

SOURCES +=\
     $$PWD/main.cpp \




DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    $$PWD/Resource/resource.qrc
