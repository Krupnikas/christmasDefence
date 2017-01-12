#include <Enemy/Movements.h>
#include <Game/Game.h>
#include <Helper.h>

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
    ExitWidth = game->OffsetX * 2;
    LocalExitSize = LocalSize * ExitWidth / game->CellSize / QueueSize * QueueSize;
    
    NormalRect = QRect(0, 0, LocalSize, LocalSize);
    NormalSize = QSize(game->CellSize, game->CellSize);
    
    EdgeRect = QRect(0, 0, LocalExitSize, LocalSize);
    EdgeSize = QSize(ExitWidth, game->CellSize);
    
    NormalLocalCell = Cell(NormalSize, NormalRect, false);
    EdgeLocalCell = Cell(EdgeSize, EdgeRect, true);
    
    
    curLocalCell = EdgeLocalCell;
    nextLocalCell = NormalLocalCell;
    
    if (ExitLeft)
    {
        curGameCell = QPoint(game->startCell.x() + 1, game->startCell.y());
        nextGameCell = QPoint(game->startCell.x(), game->startCell.y());
        curPos = QPoint(LocalExitSize - 1, half);
    }
    else
    {
        curGameCell = QPoint(-1, game->startCell.y());
        nextGameCell = QPoint(0, game->startCell.y());
        curPos = QPoint(-1, half);
    }
}

QPointF Movements::move()
{
    if (beforeTurnArea())
    {
        if (onTurnArea())
            updateNext();
        QPoint toCenter = vectorToCenter();
        queue.push(toCenter);
    }
    else
    {
        QPoint toNext = vectorToNext();
        queue.push(toNext);
    }

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
        curPoint.setX(game->OffsetX + curGameCell.x() * game->CellSize + static_cast<qreal>(curPos.x()) * 
                  curLocalCell.cellGameSize.width() / curLocalCell.localRect.width());
    
    curPoint.setY(game->OffsetY + curGameCell.y() * game->CellSize + static_cast<qreal>(curPos.y()) * 
                  curLocalCell.cellGameSize.height() / curLocalCell.localRect.height());
    return curPoint;
}

qreal Movements::curAngle() const
{
    return helper::calcAngle(QPointF(0, 0), queue.curSum);
}

int Movements::iterNum(qreal step) const
{
    qreal pointsOnMove = static_cast<qreal>(QueueSize) * game->CellSize / LocalSize;
    if (step < pointsOnMove)
    {
        //qDebug() << "Movements: too small step:(";
        return 1;
    }
        
    return static_cast<int>(step / pointsOnMove);
}

qreal Movements::getDistanceToFinish() const
{
    if (curGameCell.x() < 0)
    {
        qreal dist = game->distances[0][game->CellNumY / 2];
        qreal localDist = (curLocalCell.localRect.width() - curPos.x()) / curLocalCell.localRect.width();
        if (ExitLeft)
            localDist *= -1;
        
        return dist + localDist;
    }
    
    if (curGameCell.x() >= game->CellNumX)
    {
        qreal dist = game->distances[game->CellNumX - 1][game->CellNumY / 2];
        qreal localDist = curPos.x() / curLocalCell.localRect.width();
        if (!ExitLeft)
            localDist *= -1;
        
        return dist + localDist;
    }
    
    qreal dist = game->distances[curGameCell.x()][curGameCell.y()];
    if (isCenterDirected())
    {
        dist += half / curLocalCell.localRect.width();
        dist += (std::abs(CellCenter.x() - curPos.x()) +
                 std::abs(CellCenter.y() - curPos.y())) / curLocalCell.localRect.width();
    }
    else
    {
        dist += (half - (std::abs(CellCenter.x() - curPos.x()) +
                         std::abs(CellCenter.y() - curPos.y())))  / curLocalCell.localRect.width();
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
    return QPointF(static_cast<qreal>(queue.curSum.x()) / curLocalCell.localRect.width() * curLocalCell.cellGameSize.width(),
                   static_cast<qreal>(queue.curSum.y()) / curLocalCell.localRect.height() * curLocalCell.cellGameSize.height());
}

bool Movements::beforeTurnArea() const
{
    bool centerDirected = isCenterDirected();
    bool insideTurnArea = turnArea.contains(curPos, true);
    return !insideTurnArea && centerDirected;
}


//private methods:
bool Movements::isCenterDirected() const
{
    bool insideTurnArea = turnArea.contains(curPos, true);
    if (!insideTurnArea && curPos.x() != half && curPos.y() != half)
        qDebug() << "Movements: out of trajectory";

    qreal dx = queue.curSum.x();
    qreal dy = queue.curSum.y();
    if (std::abs(dx) < std::abs(dy))
        return (curPos.y() <= half && dy >= 0) ||
                (curPos.y() >= half && dy <= 0);
    return (curPos.x() <= half && dx >= 0) ||
            (curPos.x() >= half && dx <= 0);
}

bool Movements::onTurnArea() const
{
    bool centerDirected = isCenterDirected();
    return centerDirected && !turnArea.contains(curPos, true) && turnArea.contains(curPos, false);
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
    if (std::abs(curGameCell.x() - nextGameCell.x()) + std::abs(curGameCell.y() - nextGameCell.y()) > 1)
    {
        qDebug() << "Movements: wrong next cell";
        updateNext();
    }
    if (std::abs(curGameCell.x() - nextGameCell.x()) + std::abs(curGameCell.y() - nextGameCell.y()) > 1)
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
        if (curGameCell.x() < 0 || curGameCell.x() >= game->CellNumX)
            curLocalCell = EdgeLocalCell;
        else
            curLocalCell = NormalLocalCell;

        updateNext();
    }
}

void Movements::updateNext()
{
    nextGameCell = helper::findLowerNeighbour(game->distances, curGameCell, game);

    if (nextGameCell.x() < 0 || nextGameCell.x() >= game->CellNumX)
        nextLocalCell = EdgeLocalCell;
    else
        nextLocalCell = NormalLocalCell;
}

} // namespace mov
