#include <Enemy/Movements.h>
#include <Game/Game.h>
#include <Game/Helper.h>

Queue::Queue() : frontInd(0), backInd(QueueSize - 1)
{
    int defVal = dN;
    if (!ExitLeft)
        defVal = dP;
    curSum = QPoint(0, 0);
    for (int i = 0; i < QueueSize; ++i)
    {
        dxArr[i] = defVal;
        dyArr[i] = 0;
        curSum.setX(curSum.x() + dxArr[i]);
    }
}

QPoint Queue::front()
{
    return QPoint(dxArr[frontInd], dyArr[frontInd]);
            
}

void Queue::push(QPoint val)
{
    curSum -= QPoint(dxArr[frontInd], dyArr[frontInd]);
    curSum += val;
    dxArr[frontInd] = val.x();
    dyArr[frontInd] = val.y();
    backInd = frontInd;
    ++frontInd;
    frontInd %= QueueSize;
}

///////////////////////////////////////////////
Movements::Movements(CGame *game) : game(game)
{
    if (ExitLeft)
    {
        curCell = QPoint(EntranceX + 1, EntranceY);
        nextCell = QPoint(EntranceX, EntranceY);
        curPos = QPoint(LocalExitSize - 1, half);
    }
    else
    {
        curCell = QPoint(-1, EntranceY);
        nextCell = QPoint(0, EntranceY);
        curPos = QPoint(0, half);
    }
}

QPointF Movements::move()
{
    bool centerDirected = isCenterDirected();
    bool insideTurnArea = turnArea.contains(curPos);
    QPoint toCenter = vectorToCenter();
    QPoint toNext = vectorToNext();
    if (!insideTurnArea && centerDirected)
        queue.push(toCenter);
    else
        queue.push(toNext);
    curPos += queue.curSum;
    
    updateCur();
    
    return curCenter();
}

QPointF Movements::curCenter()
{
    QPointF curPoint;
    if (curCell == QPoint(-1, EntranceY))
        curPoint.setX(static_cast<qreal>(curPos.x()) / LocalExitSize);
    else if (curCell == QPoint(CellNumX, EntranceY))
        curPoint.setX(OffsetX + curCell.x() * CellSize + static_cast<qreal>(curPos.x()) / LocalExitSize);
    else
        curPoint.setX(OffsetX + curCell.x() * CellSize + static_cast<qreal>(curPos.x()) / LocalSize);
    
    curPoint.setY(OffsetY + curCell.y() * CellSize + static_cast<qreal>(curPos.y()) / LocalSize);
    return curPoint;
}

qreal Movements::curAngle()
{
    return helper::calcAngle(QPointF(0, 0), queue.curSum);
}

bool Movements::isCenterDirected()
{
    if (curPos.x() != half && curPos.y() != half)
        qDebug() << "Movements: out of trajectory";
    
    qreal dx = queue.curSum.x();
    qreal dy = queue.curSum.y();
    if (curPos.x() == half)
        return (curPos.y() <= half && dy >= 0) ||
                (curPos.y() >= half && dy <= 0);
    return (curPos.x() <= half && dx >= 0) ||
            (curPos.x() >= half && dx <= 0);
}

QPoint Movements::vectorToCenter()
{
    if (curPos.x() != half && curPos.y() != half)
        qDebug() << "Movements: out of trajectory";
    qreal dx = dZ;
    qreal dy = dZ;
    if (curPos.x() == half)
        if (curPos.y() < half)
            dy = dP;
        else
            dy = dN;
    else
        if (curPos.x() < half)
            dx = dP;
        else
            dx = dN;
    return QPoint(dx, dy);
}

QPoint Movements::vectorToNext()
{
    if (abs(curCell.x() - nextCell.x()) + abs(curCell.y() - nextCell.y()) > 1)
        qDebug() << "Movements: wrong next cell";
    return QPoint(nextCell.x() - curCell.x(), nextCell.y() - curCell.y());
}

void Movements::updateCur()
{
    //on start
    if ((curCell == QPoint(-1, EntranceY)) && curPos.x() >= LocalExitSize)
    {
        curCell.setX(0);
        curPos.setX(curPos.x() - LocalExitSize);
        updateNext();
        return;
    }
    if ((curCell == QPoint(0, EntranceY)) && curPos.x() < 0 && ExitLeft)
    {
        curCell.setX(-1);
        curPos.setX(curPos.x() + LocalExitSize);
        updateNext();
        return;
    }
        
    if (curPos.x() < 0)
    {
        curCell.setX(curCell.x() - 1);
        curPos.setX(curPos.x() + LocalSize);
        updateNext();
    }
    else if (curPos.x() >= LocalSize && curCell.x() < CellNumX && curCell.x() >= 0)
    {
        curCell.setX(curCell.x() + 1);
        curPos.setX(curPos.x() - LocalSize);
        updateNext();
    }
    
    if (curPos.y() < 0)
    {
        curCell.setY(curCell.y() - 1);
        curPos.setY(curPos.y() + LocalSize);
        updateNext();
    }
    else if (curPos.y() >= LocalSize)
    {
        curCell.setY(curCell.y() + 1);
        curPos.setY(curPos.y() - LocalSize);
        updateNext();
    }
}

void Movements::updateNext()
{
    //on start
    if ((curCell == QPoint(-1, EntranceY)) && !ExitLeft)
    {
        nextCell.setX(0);
        return;
    }
    else if ((curCell == QPoint(CellNumX, EntranceY)) && ExitLeft)
    {
        nextCell.setX(CellNumX - 1);
        return;
    }
        
    //before exit
    if ((curCell == QPoint(0, ExitY)) && ExitLeft)
    {
        nextCell.setX(-1);
        return;
    }
    else if ((curCell == QPoint(CellNumX - 1, ExitY)) && !ExitLeft)
    {
        nextCell.setX(CellNumX);
        return;
    }
    
    if (curCell.x() < 0  && ExitLeft)
    {
        nextCell.setX(curCell.x() - 1);
        return;
    }
    else if ((curCell == QPoint(CellNumX, ExitY)) && !ExitLeft)
    {
        nextCell.setX(CellNumX + 1);
        return;
    }
    
    nextCell = helper::findLowerNeighbour(game->distances, curCell);
}
