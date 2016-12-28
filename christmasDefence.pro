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

SOURCES += \
    main.cpp\
    mainview.cpp \
    Window.cpp \
    \
    Bullet/IBullet.cpp \
    Bullet/FastBullet.cpp \
    Bullet/BurnBullet.cpp \
    Bullet/MonsterBullet.cpp \
    Bullet/SlowBullet.cpp \
    \
    Cannon/BurnCannon.cpp \
    Cannon/ICannon.cpp \
    Cannon/MonsterCannon.cpp \
    Cannon/SlowCannon.cpp \
    Cannon/FastCannon.cpp \
    Cannon/CannonRadius.cpp \
    \
    Enemy/IEnemy.cpp \
    Enemy/FastEnemy.cpp \
    Enemy/Movements.cpp \
    Enemy/CHpCurrent.cpp \
    Enemy/CHpBackground.cpp \
    \
    Game/Game.cpp \
    Game/User.cpp \
    \
    GameMenu/GameMenu.cpp \
    \
    InfoBlock/IInfoBlock.cpp \
    InfoBlock/UserInfo.cpp \
    InfoBlock/ControlButtons.cpp \
    InfoBlock/PauseWindow.cpp \
    InfoBlock/CannonSelection.cpp \
    \
    InfoBlock/WaveInfo/WaveInfo.cpp \
    InfoBlock/CannonUpgrade.cpp \
    InfoBlock/ImageAndNumber.cpp \
    \
    Wave/Wave.cpp \
    Wave/WaveManager.cpp \
    Resource.cpp \
    Scene.cpp \
    Helper.cpp \
    SceneObject/Button.cpp \
    SceneObject/GameObject.cpp \
    SceneObject/SceneBackground.cpp \
    SceneObject/GameBackground.cpp


HEADERS  += \
    mainview.h \
    Window.h \
    \
    Bullet/IBullet.h \
    Bullet/FastBullet.h \
    Bullet/BurnBullet.h \
    Bullet/MonsterBullet.h \
    Bullet/SlowBullet.h \
    \
    Cannon/BurnCannon.h \
    Cannon/ICannon.h \
    Cannon/MonsterCannon.h \
    Cannon/SlowCannon.h \
    Cannon/FastCannon.h \
    Cannon/CannonRadius.h \
    \
    Enemy/IEnemy.h \
    Enemy/FastEnemy.h \
    Enemy/Movements.h \
    Enemy/CHpCurrent.h \
    Enemy/CHpBackground.h \
    \
    Game/Game.h \
    Game/User.h \
    \
    GameMenu/GameMenu.h \
    \
    InfoBlock/IInfoBlock.h \
    InfoBlock/UserInfo.h \
    InfoBlock/ControlButtons.h \
    InfoBlock/PauseWindow.h \
    InfoBlock/CannonSelection.h \
    InfoBlock/WaveInfo/WaveInfo.h \
    InfoBlock/CannonUpgrade.h \
    InfoBlock/ImageAndNumber.h \
    \
    Metrics/Metrics.h \
    Metrics/CannonMetrics.h \
    Metrics/EnemyMetrics.h \
    Metrics/BulletMetrics.h \
    Metrics/ZOrderMetrics.h \
    \
    Wave/Wave.h \
    Wave/WaveManager.h \
    Resource.h \
    Scene.h \
    Helper.h \
    SceneObject/Button.h \
    SceneObject/SceneBackground.h \
    SceneObject/SceneObject.h \
    SceneObject/GameBackground.h

FORMS    += mainview.ui

RESOURCES += \
    qresource.qrc

DISTFILES +=
