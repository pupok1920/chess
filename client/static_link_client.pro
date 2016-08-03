TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += src/main.cpp \
    src/boardmodel.cpp

RESOURCES += qml/qml.qrc

HEADERS += \
    src/boardmodel.h
