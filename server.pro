TEMPLATE = app

QT += network widgets

CONFIG += c++11

SOURCES += src/main.cpp \
    src/pieces.cpp \
    src/data.cpp \
    src/handler.cpp \

HEADERS += \
    src/consts.h \
    src/pieces.h \
    src/data.h \
    src/handler.h \
