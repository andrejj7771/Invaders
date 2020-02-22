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

HEADERS += ../include/Object.h

HEADERS += ../include/GameObjects/GameObject.h
HEADERS += ../include/GameObjects/Player.h
HEADERS += ../include/GameObjects/Bullet.h
HEADERS += ../include/GameObjects/Enemy.h

HEADERS += ../include/GUIObjects/GUIObject.h
HEADERS += ../include/GUIObjects/Label.h
HEADERS += ../include/GUIObjects/Button.h

HEADERS += ../include/Events.h

HEADERS += ../include/Scene.h
HEADERS += ../include/Level.h
HEADERS += ../include/LevelManager.h

SOURCES += ../src/Components/Component.cpp
SOURCES += ../src/Components/ComponentFactory.cpp
SOURCES += ../src/Components/AnimationComponent.cpp
SOURCES += ../src/Components/SoundComponent.cpp

SOURCES += ../src/Object.cpp

SOURCES += ../src/GameObjects/GameObject.cpp
SOURCES += ../src/GameObjects/Player.cpp
SOURCES += ../src/GameObjects/Bullet.cpp
SOURCES += ../src/GameObjects/Enemy.cpp

SOURCES += ../src/GUIObjects/GUIObject.cpp
SOURCES += ../src/GUIObjects/Label.cpp
SOURCES += ../src/GUIObjects/Button.cpp

SOURCES += ../src/Events.cpp

SOURCES += ../src/Scene.cpp
SOURCES += ../src/Level.cpp
SOURCES += ../src/LevelManager.cpp

SOURCES += ../src/main.cpp

OTHER_FILES += ../TODO.txt
