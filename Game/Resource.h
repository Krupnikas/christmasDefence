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

#include <memory>
#include <vector>
#include <string>

#include <Game/Metrics.h>

enum CannonType {
    SMALL, MEDIUM, BIG
};

struct R
{
    
    QString res_dir;
    
    QPixmap window_background;
    QPixmap game_background;
    
    QPixmap cell1;
    QPixmap cell2;
    
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    
    QPixmap fast_bullet_1;
    QPixmap fast_bullet_2;
    QPixmap fast_bullet_3;
    
    QString get(const char *val);
    
    R();
    
};

