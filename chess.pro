TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    square.cpp \
    pieces.cpp \
    boarddata.cpp \
    boardmodel.cpp

RESOURCES += qml.qrc

HEADERS += \
    square.h \
    consts.h \
    pieces.h \
    boarddata.h \
    boardmodel.h



