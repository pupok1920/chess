TEMPLATE = app

QT += qml quick widgets network

CONFIG += c++11

SOURCES += src/main.cpp \
    src/square.cpp \
    src/pieces.cpp \
    src/boarddata.cpp \
    src/boardmodel.cpp \
    src/filehandler.cpp \
    src/replaycommand.cpp

RESOURCES += qml/qml.qrc

HEADERS += \
    src/square.h \
    src/consts.h \
    src/structs.h \
    src/pieces.h \
    src/boarddata.h \
    src/boardmodel.h \
    src/filehandler.h \
    src/replaycommand.h
