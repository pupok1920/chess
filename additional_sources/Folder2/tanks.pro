TEMPLATE = app
CONFIG += c++14
CONFIG += CONSOLE


QT += widgets
QT += qml 
QT += quick 
QT += multimedia

CONFIG += c++11

SOURCES +=  src/main.cpp \
            src/BattleCity.cpp \

HEADERS += \
    src/BattleCity.h \
    src/ListPublisher.h

DISTFILES += \
    qml/main.qml
