#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QPixmap>
#include <QTransform>
#include <QMatrix>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>
#include <QLineF>
#include <QtCore/qmath.h>
#include <QDebug>
#include <qopengl.h>
#include <QOpenGLContext>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>

#include <memory>
#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>

#include <Metrics/Metrics.h>

enum class eGameStatus {
    eGameMenu, eLevelMenu, eGame
};

enum eSizeType {
    SMALL, MEDIUM, BIG
};

enum eScaleCenter {
    LeftTop, Center
};

enum eButtonTypes{
    eBTnone,
    eBTCloseButton,
    eBTChooseFast,
    eBTChooseMonster,
    eBTChooseSlow,
    eBTChooseBurn,
    eBTcannonUpgrade,
    eBTcannonSell,
    eBTuiPause,
    eBTuiAccelerate
};

struct R
{
    
    QString res_dir;
    
    QPixmap window_background;
    QPixmap game_background;
    QPixmap cannonSelectionBackground;
    QPixmap cannonUpgradeBackground;
    QPixmap imageAndNumberBackground;
    QPixmap userInfoBackground;

    QPixmap hpIcon;
    QPixmap coinsIcon;

    QPixmap cannonTypePreview[TypesOfCannon];

    QPixmap cell1;
    QPixmap cell2;
    QPixmap cellSelected;

    QPixmap entireRadius;

    QPixmap buttonClose;
    QPixmap buttonUpgrade;
    QPixmap buttonSell;
    
    QPixmap burn_cannon_1;
    QPixmap burn_cannon_2;
    QPixmap burn_cannon_3;
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    QPixmap monster_cannon_1;
    QPixmap monster_cannon_2;
    QPixmap monster_cannon_3;
    QPixmap slow_cannon_1;
    QPixmap slow_cannon_2;
    QPixmap slow_cannon_3;
    
    QPixmap burn_bullet_1;
    QPixmap burn_bullet_2;
    QPixmap burn_bullet_3;
    QPixmap fast_bullet_1;
    QPixmap fast_bullet_2;
    QPixmap fast_bullet_3;
    QPixmap monster_bullet_1;
    QPixmap monster_bullet_2;
    QPixmap monster_bullet_3;
    QPixmap slow_bullet_1;
    QPixmap slow_bullet_2;
    QPixmap slow_bullet_3;
    
    QPixmap fast_enemy_1;
    QPixmap fast_enemy_2;
    QPixmap fast_enemy_3;
    
    QPixmap hp_cur;
    QPixmap hp_background;
    
    QPixmap enemy_comes;
    QString waves;
    
    QString get(QString val);
    QString getNameOfTypePreview(int num);
    
    R();
    
};
