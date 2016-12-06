#-------------------------------------------------
#
# Project created by QtCreator 2016-11-06T17:06:14
#
#-------------------------------------------------

QT       += core gui opengl

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
    Enemy/FastEnemy.cpp \
    Enemy/Movements.cpp \
    InfoBlock/IInfoBlock.cpp \
    InfoBlock/UserInfo.cpp \
    InfoBlock/ControlButtons.cpp \
    InfoBlock/PauseWindow.cpp \
    InfoBlock/CannonSelection.cpp \
    Enemy/CHpCurrent.cpp \
    Enemy/CHpBackground.cpp \
    Game/GameObject.cpp \
    Game/Button.cpp \
    Wave/Wave.cpp \
    Wave/WaveManager.cpp \
    InfoBlock/WaveInfo/WaveInfo.cpp \
    Cannon/CannonRadius.cpp \
    Game/User.cpp
    Game/Button.cpp

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
    Game/Helper.h \
    Bullet/FastBullet.h \
    Enemy/FastEnemy.h \
    Enemy/Movements.h \
    InfoBlock/IInfoBlock.h \
    InfoBlock/UserInfo.h \
    InfoBlock/WaveInfo.h \
    InfoBlock/ControlButtons.h \
    InfoBlock/PauseWindow.h \
    InfoBlock/CannonSelection.h \
    Metrics/Metrics.h \
    Metrics/CannonMetrics.h \
    Metrics/EnemyMetrics.h \
    Metrics/BulletMetrics.h \
    Enemy/CHpCurrent.h \
    Enemy/CHpBackground.h \
    Game/GameObject.h \
    Game/Button.h \
    Wave/Wave.h \
    Wave/WaveManager.h \
    InfoBlock/WaveInfo/WaveInfo.h \
    Cannon/CannonRadius.h \
    Game/User.h
    Game/Button.h

FORMS    += mainview.ui

RESOURCES += \
    qresource.qrc

DISTFILES +=
