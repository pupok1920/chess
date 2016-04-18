#-------------------------------------------------
#
# Project created by QtCreator 2015-08-04T17:28:29
#
#-------------------------------------------------

QT       += xml xmlpatterns widgets testlib

QT       -= gui

TARGET = tst_chmovecommandtest
CONFIG   += console
CONFIG   += testcase
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''

SOURCES += tst_chmovecommandtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../qmlchesslib
CONFIG(debug, debug|release):LIBS=-L../../../bin/debug -lqmlchesslib
CONFIG(release, debug|release):LIBS=-L../../../bin/release -lqmlchesslib
CONFIG(debug, debug|release):DESTDIR=../../../bin/debug
CONFIG(release, debug|release):DESTDIR=../../../bin/release

HEADERS += \
    ../test.h
