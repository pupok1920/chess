TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += src/main.cpp \
    src/square.cpp \
    src/pieces.cpp \
    src/boarddata.cpp \
    src/boardmodel.cpp \

RESOURCES += qml/qml.qrc

HEADERS += \
    src/square.h \
    src/consts.h \
    src/pieces.h \
    src/boarddata.h \
    src/boardmodel.h \



