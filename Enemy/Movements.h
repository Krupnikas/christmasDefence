#pragma once

#include <Game/Resource.h>

//number of vector to be added
const int QueueSize = 10;

const int dP = 1;
const int dZ = 0;
const int dN = -1;

//60 ++ 55 + 55 + 60, 55 - turnArea, 60 - nonturnArea
const int LocalSize = 230;
const QRect turnArea(59, 59, 110, 110);

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

struct Cell
{
    QSize cellGameSize;
    QRect localRect;
    bool edge;
    Cell();
    Cell(QSize cellGameSize, QRect localRect, bool edge);
    Cell(const Cell &cell);
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
    
private:
    CGame *game;

    QPoint curGameCell;
    QPoint nextGameCell;

    Cell curLocalCell;
    Cell nextLocalCell;
    QPoint curPos; //(0, 0) .. (220, 220)
    
    Queue queue;
    
    const int ExitWidth = OffsetX * 2;
    const int LocalExitSize = LocalSize * ExitWidth / CellSize / 10 * 10;
    
    const QRect NormalRect = QRect(0, 0, LocalSize, LocalSize);
    const QSize NormalSize = QSize(CellSize, CellSize);
    
    const QRect EdgeRect = QRect(0, 0, LocalExitSize, LocalExitSize);
    const QSize EdgeSize = QSize(ExitWidth, CellSize);
    
    const Cell NormalLocalCell = Cell(NormalSize, NormalRect, false);
    const Cell EdgeLocalCell = Cell(EdgeSize, EdgeRect, true);
    
};
