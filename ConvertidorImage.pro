#-------------------------------------------------
#
# Project created by QtCreator 2016-09-04T09:03:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConvertidorImage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsfilter.cpp

HEADERS  += mainwindow.h \
    process.h \
    settingsfilter.h \
    resources.h \
    filterminmedmax.h \
    globals.h \
    filter.h

FORMS    += mainwindow.ui \
    settingsfilter.ui

RESOURCES += \
    resources.qrc
