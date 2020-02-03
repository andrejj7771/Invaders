TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

LIBS +=  -lsfml-graphics
LIBS +=  -lsfml-window
LIBS +=  -lsfml-system
LIBS +=  -lsfml-audio

INCLUDEPATH += ../include

HEADERS += ../include/Component.h
HEADERS += ../include/ComponentFactory.h
HEADERS += ../include/AnimationComponent.h

HEADERS += ../include/Scene.h
HEADERS += ../include/Level.h
HEADERS += ../include/LevelManager.h
HEADERS += ../include/Object.h
HEADERS += ../include/Player.h
HEADERS += ../include/Bullet.h
HEADERS += ../include/Enemy.h

SOURCES += ../src/Component.cpp
SOURCES += ../src/ComponentFactory.cpp
SOURCES += ../src/AnimationComponent.cpp

SOURCES += ../src/Scene.cpp
SOURCES += ../src/Level.cpp
SOURCES += ../src/LevelManager.cpp
SOURCES += ../src/Object.cpp
SOURCES += ../src/Player.cpp
SOURCES += ../src/Bullet.cpp
SOURCES += ../src/Enemy.cpp
SOURCES += ../src/main.cpp

OTHER_FILES += ../TODO.txt
