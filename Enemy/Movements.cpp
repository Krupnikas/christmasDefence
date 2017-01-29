#include <Enemy/Movements.h>
#include <Game/Game.h>
#include <Helper.h>

namespace mov
{

Queue::Queue() : frontInd(0), backInd(QueueSize - 1)
{
    int dx = 0;
    int dy = 0;
    
    switch (helper::cellToEdge(m::startCells[0]))
    {
    case EEdge::eLeft:
        dx = dP;
        break;
    case EEdge::eTop:
        dy = dP;
        break;
    case EEdge::eRight:
        dx = dN;
        break;
    case EEdge::eBottom:
        dy = dN;
        break;
    case EEdge::eInside:
        qDebug() << "Queue(): START CELL INSIDE GAME!!!";
        return;
        break;
    }
    
    curSum = QPoint(0, 0);
    for (int i = 0; i < QueueSize; ++i)
    {
        dxArr[i] = dx;
        dyArr[i] = dy;
        curSum.setX(curSum.x() + dxArr[i]);
        curSum.setY(curSum.y() + dyArr[i]);
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
    ExitWidth = m::OffsetX + m::CellSize;
    ExitHeight = m::OffsetY + m::CellSize;
    
    LocalExitWidth = LocalSize * ExitWidth / m::CellSize / QueueSize * QueueSize;
    LocalExitHeight = LocalSize * ExitHeight / m::CellSize / QueueSize * QueueSize;
    
    NormalRect = QRect(0, 0, LocalSize, LocalSize);
    NormalSize = QSize(m::CellSize, m::CellSize);
    
    EdgeXRect = QRect(0, 0, LocalExitWidth, LocalSize);
    EdgeXSize = QSize(ExitWidth, m::CellSize);
    EdgeYRect = QRect(0, 0, LocalSize, LocalExitHeight);
    EdgeYSize = QSize(m::CellSize, ExitHeight);
    
    NormalLocalCell = Cell(NormalSize, NormalRect, false);
    EdgeXLocalCell = Cell(EdgeXSize, EdgeXRect, true);
    EdgeYLocalCell = Cell(EdgeYSize, EdgeYRect, true);
    
    curGameCell = m::startCells[rand() % m::startCells.size()];
    nextGameCell = helper::findLowerNeighbour(game->distances, curGameCell);
    nextLocalCell = NormalLocalCell;
    
    EEdge edge = helper::cellToEdge(curGameCell);
    if (edge == EEdge::eLeft || edge == EEdge::eRight)
        curLocalCell = EdgeXLocalCell;
    else
        curLocalCell = EdgeYLocalCell;
    
    switch (helper::cellToEdge(curGameCell))
    {
    case EEdge::eLeft:
        curPos = QPoint(-1, half);
        break;
    case EEdge::eTop:
        curPos = QPoint(half, - 1);
        break;
    case EEdge::eRight:
        curPos = QPoint(LocalExitWidth - 1, half);
        break;
    case EEdge::eBottom:
        curPos = QPoint(half, LocalExitHeight - 1);
        break;
    case EEdge::eInside:
        qDebug() << "Movements(): START CELL INSIDE GAME!!!";
        return;
        break;
    }
    
}

QPointF Movements::move()
{
    if (beforeTurnArea())
    {
        if (on_turn_area_() && helper::cellToEdge(curGameCell) == EEdge::eInside)
            update_next_();
        QPoint toCenter = vector_to_center_();
        queue.push(toCenter);
    }
    else
    {
        QPoint toNext = vector_to_next_();
        queue.push(toNext);
    }

    curPos += queue.curSum;
    update_cur_();
    return curCenter();
}

QPointF Movements::curCenter() const
{
    QPointF curPoint(0, 0);
    if (curGameCell.x() <= 0)
        curPoint.setX(-(ExitWidth  * (curGameCell.x() + 1)) +
                      m::OffsetX + static_cast<qreal>(curPos.x()) * ExitWidth / LocalExitWidth);
    else
        curPoint.setX(m::OffsetX + (curGameCell.x() - 1) * m::CellSize + static_cast<qreal>(curPos.x()) * 
                  curLocalCell.cellGameSize.width() / curLocalCell.localRect.width());
    
    if (curGameCell.y() <= 0)
        curPoint.setY(-(ExitHeight * (curGameCell.y() + 1)) +
                      m::OffsetY + static_cast<qreal>(curPos.y()) * ExitHeight / LocalExitHeight);
    else
        curPoint.setY(m::OffsetY + (curGameCell.y() - 1) * m::CellSize + static_cast<qreal>(curPos.y()) * 
                  curLocalCell.cellGameSize.height() / curLocalCell.localRect.height());
    return curPoint;
}

qreal Movements::curAngle() const
{
    return helper::calcAngle(QPointF(0, 0), queue.curSum);
}

int Movements::iterNum(qreal step) const
{
    qreal pointsOnMove = static_cast<qreal>(QueueSize) * m::CellSize / LocalSize;
    if (step < pointsOnMove)
    {
        //qDebug() << "Movements: too small step:(";
        return 1;
    }
        
    return static_cast<int>(step / pointsOnMove);
}

qreal Movements::getDistanceToFinish() const
{
    EEdge startEdge = helper::cellToEdge(m::startCells[0]);
    EEdge curEdge = helper::cellToEdge(curGameCell);
    
    qreal dist = game->distances[curGameCell.x()][curGameCell.y()];
    qreal addDist = 0;
    
    qreal pWidth = curPos.x() / curLocalCell.localRect.width();
    qreal nWidth = (curLocalCell.localRect.width() - curPos.x()) / curLocalCell.localRect.width();
    qreal pHeight = curPos.y() / curLocalCell.localRect.height();
    qreal nHeight = (curLocalCell.localRect.height() - curPos.y()) / curLocalCell.localRect.height();
    
    if (curEdge != EEdge::eInside)
    {
        switch (curEdge)
        {
        case EEdge::eLeft:
            addDist += (startEdge == curEdge) ? pWidth : nWidth;
            break;
        case EEdge::eTop:
            addDist += (startEdge == curEdge) ? pHeight : nHeight;
            break;
        case EEdge::eRight:
            addDist += (startEdge == curEdge) ? nWidth : pWidth;
            break;
        case EEdge::eBottom:
            addDist += (startEdge == curEdge) ? nHeight : pHeight;
            break;
        case EEdge::eInside:
            qDebug() << "Movements: getDistanceToFinish: WTH?!?!?!";
            break;
        }
        
        return dist + addDist;
    }
    
    
    if (is_center_directed_())
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
    return QPointF(static_cast<qreal>(queue.curSum.x()) / curLocalCell.localRect.width() *
                   curLocalCell.cellGameSize.width(),
                   static_cast<qreal>(queue.curSum.y()) / curLocalCell.localRect.height() *
                   curLocalCell.cellGameSize.height());
}

bool Movements::beforeTurnArea() const
{
    bool centerDirected = is_center_directed_();
    bool insideTurnArea = turnArea.contains(curPos, true);
    return !insideTurnArea && centerDirected;
}


//private methods:
bool Movements::is_center_directed_() const
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

bool Movements::on_turn_area_() const
{
    bool centerDirected = is_center_directed_();
    return centerDirected && !turnArea.contains(curPos, true) && turnArea.contains(curPos, false);
}

QPoint Movements::vector_to_center_()
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

QPoint Movements::vector_to_next_()
{
    if (std::abs(curGameCell.x() - nextGameCell.x()) + std::abs(curGameCell.y() - nextGameCell.y()) > 1)
    {
        qDebug() << "Movements: wrong next cell";
        update_next_();
    }
    if (std::abs(curGameCell.x() - nextGameCell.x()) + std::abs(curGameCell.y() - nextGameCell.y()) > 1)
        qDebug() << "Movements: still wrong next cell(((((";
    return QPoint(nextGameCell.x() - curGameCell.x(), nextGameCell.y() - curGameCell.y());
}

void Movements::update_cur_()
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
        curPos.setY(curPos.y() + nextLocalCell.localRect.height());
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
        curLocalCell = get_movements_cell_(curGameCell);
        update_next_();
    }
}

void Movements::update_next_()
{
    nextGameCell = helper::findLowerNeighbour(game->distances, curGameCell);
    nextLocalCell = get_movements_cell_(nextGameCell);
}

Cell Movements::get_movements_cell_(QPoint gameCell)
{
    if (gameCell.x() <= 0 || gameCell.x() >= m::CellNumX - 1)
        return EdgeXLocalCell;
    else if (gameCell.y() <= 0 || gameCell.y() >= m::CellNumY - 1)
        return EdgeYLocalCell;
    else
        return NormalLocalCell;
}

} // namespace mov
