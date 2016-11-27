#pragma once

#include <Game/Resource.h>

class CGame;

//number of vector to be added
namespace mov
{

const int QueueSize = 50;

const int dP = 1;
const int dZ = 0;
const int dN = -1;

//60 ++ 55 + 55 + 60, 55 - turnArea, 60 - nonturnArea = 230
//1300*2 + 1275*2 = 5150
const int LocalSize = 5150;
const QRect turnArea(1299, 1299, 2550, 2550);

const int half = 1299 + 1275;
const QPoint CellCenter(half, half);

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
    int iterNum(qreal step);
    qreal getDistanceToFinish();
    
    void updateNext();
    
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
    const int LocalExitSize = LocalSize * ExitWidth / CellSize / QueueSize * QueueSize;
    
    const QRect NormalRect = QRect(0, 0, LocalSize, LocalSize);
    const QSize NormalSize = QSize(CellSize, CellSize);
    
    const QRect EdgeRect = QRect(0, 0, LocalExitSize, LocalSize);
    const QSize EdgeSize = QSize(ExitWidth, CellSize);
    
    const Cell NormalLocalCell = Cell(NormalSize, NormalRect, false);
    const Cell EdgeLocalCell = Cell(EdgeSize, EdgeRect, true);
    
};

}
