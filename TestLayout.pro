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
QMAKE_INFO_PLIST += Info.plist #retina ready

TARGET = TestLayout
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \    
    configmanager.cpp \
    textboxsimulator.cpp \
    indigodock/indigodock.cpp \
    indigodock/indigopanel.cpp \
    indigodock/indigotabbar.cpp \
    uiwidgets/anglepicker.cpp \
    uiwidgets/colorswatch.cpp \
    uiwidgets/indigomenubar.cpp \
    uiwidgets/iconwidget.cpp \
    uiwidgets/expandergroup.cpp \
    indigodock/indigodockmanager.cpp \
    uiwidgets/flowlayout.cpp \
    themefactory.cpp \
    indigo-helper.cpp

HEADERS  += mainwindow.h \    
    configmanager.h \
    helper.h \    
    textboxsimulator.h \
    indigodock/indigodock.h \
    indigodock/indigopanel.h \
    indigodock/indigotabbar.h \
    uiwidgets/anglepicker.h \
    uiwidgets/colorswatch.h \
    uiwidgets/indigomenubar.h \
    uiwidgets/iconwidget.h \
    uiwidgets/expandergroup.h \
    indigodock/indigodockmanager.h \
    uiwidgets/flowlayout.h \
    themefactory.h

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
