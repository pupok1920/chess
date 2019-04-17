TEMPLATE = app

QT += network widgets

CONFIG += c++14

SOURCES += src/main.cpp \
    src/square.cpp \
    src/pieces.cpp \
    src/data.cpp \
    src/handler.cpp \

HEADERS += \
    src/consts.h \
    src/square.h \
    src/pieces.h \
    src/player.h \
    src/data.h \
    src/handler.h \
