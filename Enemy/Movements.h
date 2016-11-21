#pragma once

#include <Game/Resource.h>

//number of vector to be added
const int WindowSize = 7;

//112 = number of steps with length = 1 through one Cell in width (the same about height)
const qreal Step = CellSize / ((WindowSize + 1) / 2  * WindowSize * 4); // = CellSize / 112

const qreal dP = 0.1;
const qreal dN = -0.1;


struct Queue
{
    qreal dxArr[WindowSize];
    qreal dyArr[WindowSize];
    int frontInd;
    int backInd;
    
    Queue();
    QPointF front();
    void push(QPointF val);
    
    QPointF sum();
};

class Movements
{
public:
    Movements();
    
private:
    
    QSize curCell;
    QSize nextCell;
    QSize curPos; //from (0, 0) to (112, 112)
    Queue queue;
    
    
    
    
};
