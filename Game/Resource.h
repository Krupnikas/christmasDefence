#pragma once

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QString>
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
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>

#include <memory>
#include <vector>
#include <string>

#include <Metrics/Metrics.h>

enum SizeType {
    SMALL, MEDIUM, BIG
};

struct R
{
    
    QString res_dir;
    
    QPixmap window_background;
    QPixmap game_background;
    QPixmap cannonSelectionBackground;

    QPixmap cell1;
    QPixmap cell2;
    QPixmap cellSelected;

    QPixmap entireRadius;
    
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    
    QPixmap fast_bullet_1;
    QPixmap fast_bullet_2;
    QPixmap fast_bullet_3;
    
    QPixmap fast_enemy_1;
    QPixmap fast_enemy_2;
    QPixmap fast_enemy_3;
    
    QPixmap hp_cur;
    QPixmap hp_background;
    
    QString get(const char *val);
    
    R();
    
};
