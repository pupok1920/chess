TEMPLATE = lib

QT += qml quick widgets xml xmlpatterns

SOURCES += chboardmodel.cpp \
    chpieces.cpp \
    chboarddata.cpp \
    chexception.cpp \
    chsquare.cpp \
    chplayer.cpp \
    chhumanplayer.cpp \
    chvalidator.cpp \
    chsimplevalidator.cpp \
    chmovecommand.cpp \
    chselection.cpp \
    chparserbase.cpp \
    chmessagehandler.cpp \
    chgameparser.cpp

RESOURCES += qml.qrc

HEADERS += \
    chboardmodel.h \
    chconsts.h \
    chpieces.h \
    chsquare.h \
    chboarddata.h \
    chexception.h \
    chplayer.h \
    chhumanplayer.h \
    chvalidator.h \
    chsimplevalidator.h \
    chmovecommand.h \
    chselection.h \
    chparserbase.h \
    chmessagehandler.h \
    chgameparser.h

DEFINES += QMLCHESSLIB

CONFIG(debug, debug|release):DESTDIR=../../bin/debug
CONFIG(release, debug|release):DESTDIR=../../bin/release

