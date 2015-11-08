#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T18:08:15
#
#-------------------------------------------------

QT       += core widgets gui designer
CONFIG   += plugin debug_and_release

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += core widgets gui designer
} else {
    CONFIG += designer
}

TARGET = TestLayout
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colorswatch.cpp \
    indigotabwidget.cpp \
    indigopanel.cpp \
    indigo2dropzone.cpp \
    indigo2panel.cpp \
    indigo2dock.cpp \
    indigo2tabbar.cpp \
    indigodropzone.cpp

HEADERS  += mainwindow.h \
    colorswatch.h \
    indigotabwidget.h \
    indigopanel.h \
    indigo2dropzone.h \
    indigo2panel.h \
    indigo2dock.h \
    indigo2tabbar.h \
    indigodropzone.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
