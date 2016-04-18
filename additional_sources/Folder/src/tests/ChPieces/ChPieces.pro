#-------------------------------------------------
#
# Project created by QtCreator 2015-08-02T09:05:17
#
#-------------------------------------------------

QT       += xml xmlpatterns testlib

QT       -= gui

TARGET = tst_chpiecestest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += testcase

TEMPLATE = app

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''

SOURCES += tst_chpiecestest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../qmlchesslib
CONFIG(debug, debug|release):LIBS=-L../../../bin/debug -lqmlchesslib
CONFIG(release, debug|release):LIBS=-L../../../bin/release -lqmlchesslib
CONFIG(debug, debug|release):DESTDIR=../../../bin/debug
CONFIG(release, debug|release):DESTDIR=../../../bin/release

HEADERS += \
    ../test.h
