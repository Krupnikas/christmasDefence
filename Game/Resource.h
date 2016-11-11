#ifndef RESOURCE_H
#define RESOURCE_H

#include <QWidget>
#include <QRect>
#include <QString>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include <memory>
#include <vector>

#include <Game/GameMetrics.h>

struct R
{
    
    QString res_dir;
    
    QPixmap window_background;
    QPixmap game_background;
    
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    
    QString get(const char *val);
    
    R();
    
};

#endif // RESOURCE_H


