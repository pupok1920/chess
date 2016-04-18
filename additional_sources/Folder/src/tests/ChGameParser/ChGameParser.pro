#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T16:59:22
#
#-------------------------------------------------

QT       += xml xmlpatterns testlib

QT       -= gui

TARGET = tst_chgameparsertest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += testcase

TEMPLATE = app

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''

RESOURCES += data.qrc

SOURCES += tst_chgameparsertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../qmlchesslib
CONFIG(debug, debug|release):LIBS=-L../../../bin/debug -lqmlchesslib
CONFIG(release, debug|release):LIBS=-L../../../bin/release -lqmlchesslib
CONFIG(debug, debug|release):DESTDIR=../../../bin/debug
CONFIG(release, debug|release):DESTDIR=../../../bin/release
