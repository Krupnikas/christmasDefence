#include <Enemy/Movements.h>
#include <Game/Game.h>
#include <Game/Helper.h>

namespace mov
{

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
Cell::Cell():
    cellGameSize(0, 0),
    localRect(0, 0, 0, 0),
    edge(false)
{
}

Cell::Cell(QSize cellGameSize, QRect localRect, bool edge):
    cellGameSize(cellGameSize),
    localRect(localRect),
    edge(edge)
{
}

Cell::Cell(const Cell &cell):
    cellGameSize(cell.cellGameSize),
    localRect(cell.localRect),
    edge(cell.edge)
{
}

///////////////////////////////////////////////
Movements::Movements(CGame *game):
    game(game)
{
    curLocalCell = EdgeLocalCell;
    nextLocalCell = NormalLocalCell;
    if (ExitLeft)
    {
        curGameCell = QPoint(EntranceX + 1, EntranceY);
        nextGameCell = QPoint(EntranceX, EntranceY);
        curPos = QPoint(LocalExitSize - 1, half);
    }
    else
    {
        curGameCell = QPoint(-1, EntranceY);
        nextGameCell = QPoint(0, EntranceY);
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

QPointF Movements::curCenter() const
{
    QPointF curPoint;
    if (curGameCell.x() < 0)
        curPoint.setX((curGameCell.x() + 0.5) * ExitWidth + static_cast<qreal>(curPos.x()) * ExitWidth / LocalExitSize);
    else
        curPoint.setX(OffsetX + curGameCell.x() * CellSize + static_cast<qreal>(curPos.x()) * 
                  curLocalCell.cellGameSize.width() / curLocalCell.localRect.width());
    
    curPoint.setY(OffsetY + curGameCell.y() * CellSize + static_cast<qreal>(curPos.y()) * 
                  curLocalCell.cellGameSize.height() / curLocalCell.localRect.height());
    return curPoint;
}

qreal Movements::curAngle() const
{
    return helper::calcAngle(QPointF(0, 0), queue.curSum);
}

int Movements::iterNum(qreal step) const
{
    qreal pointsOnMove = static_cast<qreal>(QueueSize) * CellSize / LocalSize;
    if (step < pointsOnMove)
    {
        qDebug() << "Movements: too small step:(";
        return 1;
    }
        
    return static_cast<int>(step / pointsOnMove);
}

qreal Movements::getDistanceToFinish() const
{
    if (curGameCell.x() < 0)
    {
        return -(curLocalCell.localRect.width() - curPos.x()) / curLocalCell.localRect.width();
    }
    
    if (curGameCell.x() >= CellNumX)
    {
        return game->distances[CellNumX - 1][CellNumY / 2] + curPos.x() / curLocalCell.localRect.width();
    }
    
    qreal dist = game->distances[curGameCell.x()][curGameCell.y()];
    if (isCenterDirected())
    {
        dist += half / curLocalCell.localRect.width();
        dist += (abs(CellCenter.x() - curPos.x()) + 
                 abs(CellCenter.y() - curPos.y())) / curLocalCell.localRect.width();
    }
    else
    {
        dist += (half - (abs(CellCenter.x() - curPos.x()) + 
                         abs(CellCenter.y() - curPos.y())))  / curLocalCell.localRect.width();
    }
    return dist;
}

QPoint Movements::getCurrentGameCell() const
{
    return curGameCell;
}

QPoint Movements::getNextGameCell() const
{
    return nextGameCell;
}

QPointF Movements::getSpeed() const
{
    
}

void Movements::updateNext()
{

}

bool Movements::isCenterDirected() const
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
    if (abs(curGameCell.x() - nextGameCell.x()) + abs(curGameCell.y() - nextGameCell.y()) > 1)
    {
        qDebug() << "Movements: wrong next cell";
        updateNext();
    }
    if (abs(curGameCell.x() - nextGameCell.x()) + abs(curGameCell.y() - nextGameCell.y()) > 1)
        qDebug() << "Movements: still wrong next cell(((((";
    return QPoint(nextGameCell.x() - curGameCell.x(), nextGameCell.y() - curGameCell.y());
}

void Movements::updateCur()
{
    bool update = false;
    if (curPos.x() < 0)
    {
        curGameCell.setX(curGameCell.x() - 1);
        curPos.setX(curPos.x() + nextLocalCell.localRect.width());
        update = true;
    }
    else if (curPos.x() >= curLocalCell.localRect.width())
    {
        curGameCell.setX(curGameCell.x() + 1);
        curPos.setX(curPos.x() - curLocalCell.localRect.width());
        update = true;
    }
    
    if (curPos.y() < 0)
    {
        curGameCell.setY(curGameCell.y() - 1);
        curPos.setY(curPos.y() + curLocalCell.localRect.height());
        update = true;
    }
    else if (curPos.y() >= curLocalCell.localRect.height())
    {
        curGameCell.setY(curGameCell.y() + 1);
        curPos.setY(curPos.y() - curLocalCell.localRect.height());
        update = true;
    }
    
    if (update)
    {
        if (curGameCell.x() < 0 || curGameCell.x() >= CellNumX)
            curLocalCell = EdgeLocalCell;
        else
            curLocalCell = NormalLocalCell;
        
        nextGameCell = helper::findLowerNeighbour(game->distances, curGameCell);
        
        if (nextGameCell.x() < 0 || curGameCell.x() >= CellNumX)
            nextLocalCell = EdgeLocalCell;
        else
            nextLocalCell = NormalLocalCell;
    }
}

} // namespace mov
