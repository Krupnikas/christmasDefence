#pragma once

#include <Game/Resource.h>

//number of vector to be added
const int QueueSize = 10;

const int dP = 1;
const int dZ = 0;
const int dN = -1;

//60 ++ 55 + 55 + 60, 55 - turnArea, 60 - nonturnArea
const int LocalSize = 230;
const QRect turnArea(59, 59, 59 + 110, 59 + 110);

const int half = 59 + 55;
const QPoint CellCenter(half, half);



class CGame;

struct Queue
{
    int dxArr[QueueSize];
    int dyArr[QueueSize];
    int frontInd;
    int backInd;
    QPoint curSum;
    
    Queue();
    QPoint front();
    void push(QPoint val);
};

class Movements
{
public:
    Movements(){}
    Movements(CGame *game);
    QPointF move();
    QPointF curCenter();
    qreal curAngle();
    
private:
    bool isCenterDirected();
    QPoint vectorToCenter();
    QPoint vectorToNext();
    
    void updateCur();
    void updateNext();
    
private:
    CGame *game;
    
    QPoint curCell;
    QPoint nextCell;
    QPoint curPos; //(0, 0) .. (220, 220)
    Queue queue;
    
    
    QPoint center;
    
    const int ExitWidth = OffsetX * 2;
    const int LocalExitSize = LocalSize * ExitWidth / CellSize / 10 * 10;
    
};
