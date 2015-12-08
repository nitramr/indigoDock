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

# OSX: Xcode 7.1.x doesn't support macosx10.10 sdk
QMAKE_MAC_SDK = macosx10.11

TARGET = TestLayout
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colorswatch.cpp \
    indigodock.cpp \
    indigotabbar.cpp \
    indigopanel.cpp \
    indigodropzone.cpp \
    indigoexpandergroup.cpp \
    indigomenubar.cpp \
    anglepicker.cpp

HEADERS  += mainwindow.h \
    colorswatch.h \
    indigodock.h \
    indigotabbar.h \
    indigopanel.h \
    indigodropzone.h \
    indigoexpandergroup.h \
    indigomenubar.h \
    anglepicker.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
