TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ../bin

LIBS += -LC:/SFML/lib/ -lsfml-graphics
LIBS += -LC:/SFML/lib/ -lsfml-window
LIBS += -LC:/SFML/lib/ -lsfml-system
LIBS += -LC:/SFML/lib/ -logg
LIBS += -LC:/SFML/lib/ -lopenal32
LIBS += -LC:/SFML/lib/ -lsfml-audio

INCLUDEPATH += C:/SFML/include
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
