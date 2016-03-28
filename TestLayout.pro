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
    indigoexpandergroup.cpp \
    indigomenubar.cpp \
    anglepicker.cpp \
    stylefactory.cpp \
    configmanager.cpp \
    helper.cpp \
    indigohub.cpp \
    textboxsimulator.cpp \
    indigoiconwidget.cpp

HEADERS  += mainwindow.h \
    colorswatch.h \
    indigodock.h \
    indigotabbar.h \
    indigopanel.h \
    indigoexpandergroup.h \
    indigomenubar.h \
    anglepicker.h \
    stylefactory.h \
    configmanager.h \
    helper.h \
    indigohub.h \
    textboxsimulator.h \
    indigoiconwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc


ROOT_DIRECTORY = $$PWD

CONFIG(debug, debug|release) {
    BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build/debug
} else {
    BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build/release
}

DESTDIR = $${ROOT_DIRECTORY}/build
OBJECTS_DIR = $${BUILD_DIRECTORY}
MOC_DIR = $${BUILD_DIRECTORY}
RCC_DIR = $${BUILD_DIRECTORY}
UI_DIR = $${BUILD_DIRECTORY}
