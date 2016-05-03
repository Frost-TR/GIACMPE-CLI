QT += core
QT -= gui

CONFIG += c++11

TARGET = ICP-cli
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    Source/gamedata.cpp \
    Source/gameinteligence.cpp \
    Source/gamelogic.cpp \
    Source/main.cpp

HEADERS += \
    Headers/gamedata.h \
    Headers/gameinteligence.h \
    Headers/gamelogic.h

