TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

LIBS +=  -lsfml-graphics
LIBS +=  -lsfml-window
LIBS +=  -lsfml-system
LIBS +=  -logg
LIBS +=  -lopenal32
LIBS +=  -lsfml-audio

INCLUDEPATH += ../include

HEADERS += ../include/Scene.h
HEADERS += ../include/Object.h
HEADERS += ../include/Player.h
HEADERS += ../include/Bullet.h
HEADERS += ../include/Enemy.h

SOURCES += ../src/Scene.cpp
SOURCES += ../src/Object.cpp
SOURCES += ../src/Player.cpp
SOURCES += ../src/Bullet.cpp
SOURCES += ../src/Enemy.cpp
SOURCES += ../src/main.cpp
