#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T17:06:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = christmasDefence
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainview.cpp \
    Bullet/IBullet.cpp \
    Cannon/BurnCannon.cpp \
    Cannon/ICannon.cpp \
    Cannon/MonsterCannon.cpp \
    Cannon/SlowCannon.cpp \
    Enemy/IEnemy.cpp \
    Game/Game.cpp \
    Cannon/FastCannon.cpp \
    Game/Scene.cpp \
    Game/Resource.cpp \
    Game/Helper.cpp \
    Bullet/FastBullet.cpp \
    Game/IGameObject.cpp

HEADERS  += mainview.h \
    Bullet/IBullet.h \
    Cannon/BurnCannon.h \
    Cannon/ICannon.h \
    Cannon/MonsterCannon.h \
    Cannon/SlowCannon.h \
    Enemy/IEnemy.h \
    Game/Game.h \
    Cannon/FastCannon.h \
    Game/Scene.h \
    Game/Resource.h \
    Game/Metrics.h \
    Game/Helper.h \
    Bullet/FastBullet.h \
    Game/IGameObject.h

FORMS    += mainview.ui

RESOURCES += \
    qresource.qrc

DISTFILES += \
    android-sources/AndroidManifest.xml
