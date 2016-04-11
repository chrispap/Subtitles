#-------------------------------------------------
#
# Project created by QtCreator 2013-01-30T18:52:21
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Subtitles

SOURCES += \
        subtitlewidget.cpp \
    subtitlewindow.cpp \
    playbackcontrols.cpp \
    time.cpp \
    subtitle.cpp

HEADERS  += \
    subtitlewidget.h \
    subtitle.h \
    time.h \
    subtitlewindow.h \
    playbackcontrols.h

FORMS += \
    playbackcontrols.ui

RESOURCES += \
    Icons/icons.qrc

include(C:\libs\Qwt-6.1.2-qt-5.5.0\features\qwt.prf)
include(D:\Libs\Qwt-6.1.2-qt-5.5.1-vs2013\features\qwt.prf)
