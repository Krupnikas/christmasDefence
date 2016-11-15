#ifndef RESOURCE_H
#define RESOURCE_H

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

#include <memory>
#include <vector>

#include <Game/Metrics.h>
#include <Game/Helper.h>

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
    
    QString get(const char *val);
    
    R();
    
};

#endif // RESOURCE_H


