TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RC_FILE = qmlchess.rc

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''

INCLUDEPATH += ../qmlchesslib

CONFIG(debug, debug|release):LIBS=-L../../bin/debug -lqmlchesslib
CONFIG(release, debug|release):LIBS=-L../../bin/release -lqmlchesslib
CONFIG(debug, debug|release):DESTDIR=../../bin/debug
CONFIG(release, debug|release):DESTDIR=../../bin/release

DISTFILES += \
    qmlchess.rc
