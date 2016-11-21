#include "Movements.h"

Queue::Queue() : frontInd(0), backInd(WindowSize - 1)
{
    qreal defVal = dN;
    if (!ExitLeft)
        defVal = dP;
    for (int i = 0; i < WindowSize; ++i)
    {
        dxArr[i] = dyArr[i] = defVal;                
    }
}

QPointF Queue::front()
{
    return QPointF(dxArr[frontInd], dyArr[frontInd]);
            
}

void Queue::push(QPointF val)
{
    dxArr[frontInd] = val.x();
    dyArr[frontInd] = val.y();
    backInd = frontInd;
    frontInd = ++frontInd % WindowSize;
}

QPointF Queue::sum()
{
    qreal xSum = 0;
    qreal ySum = 0;
    for (int i = 0; i < WindowSize; ++i)
    {
        xSum += dxArr[i];
        ySum += dyArr[i];
    }
    return QPointF(xSum, ySum);
}

Movements::Movements()
{
    
}
