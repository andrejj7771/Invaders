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

HEADERS += ../include/Components/Component.h
HEADERS += ../include/Components/ComponentFactory.h
HEADERS += ../include/Components/AnimationComponent.h
HEADERS += ../include/Components/SoundComponent.h

HEADERS += ../include/Objects/Object.h
HEADERS += ../include/Objects/Player.h
HEADERS += ../include/Objects/Bullet.h
HEADERS += ../include/Objects/Enemy.h

HEADERS += ../include/GUI/GObject.h

HEADERS += ../include/Scene.h
HEADERS += ../include/Level.h
HEADERS += ../include/LevelManager.h

SOURCES += ../src/Components/Component.cpp
SOURCES += ../src/Components/ComponentFactory.cpp
SOURCES += ../src/Components/AnimationComponent.cpp
SOURCES += ../src/Components/SoundComponent.cpp

SOURCES += ../src/Objects/Object.cpp
SOURCES += ../src/Objects/Player.cpp
SOURCES += ../src/Objects/Bullet.cpp
SOURCES += ../src/Objects/Enemy.cpp

SOURCES += ../src/GUI/GObject.cpp

SOURCES += ../src/Scene.cpp
SOURCES += ../src/Level.cpp
SOURCES += ../src/LevelManager.cpp

SOURCES += ../src/main.cpp

OTHER_FILES += ../TODO.txt
