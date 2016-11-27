#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T17:06:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = christmasDefence
TEMPLATE = app

CONFIG += c++11 desktop 
QMAKE_CXXFLAGS += -opengl desktop

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
    Game/IGameObject.cpp \
    Enemy/FastEnemy.cpp \
    Enemy/Movements.cpp \
    InfoBlock/IInfoBlock.cpp \
    InfoBlock/UserInfo.cpp \
    InfoBlock/WaveInfo.cpp \
    InfoBlock/ControlButtons.cpp \
    InfoBlock/PauseWindow.cpp \
    InfoBlock/CannonSelection.cpp

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
    Game/IGameObject.h \
    Enemy/FastEnemy.h \
    Enemy/Movements.h \
    InfoBlock/IInfoBlock.h \
    InfoBlock/UserInfo.h \
    InfoBlock/WaveInfo.h \
    InfoBlock/ControlButtons.h \
    InfoBlock/PauseWindow.h \
    InfoBlock/CannonSelection.h

FORMS    += mainview.ui

RESOURCES += \
    qresource.qrc

DISTFILES += \
    android-sources/AndroidManifest.xml
