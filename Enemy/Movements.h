#pragma once

#include <Resource.h>

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
const QRect turnArea(1299, 1299, 2551, 2551);

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
    
    QPointF curCenter() const;
    qreal curAngle() const;
    int iterNum(qreal step) const;
    qreal getDistanceToFinish() const;
    QPoint getCurrentGameCell() const;
    QPoint getNextGameCell() const;
    QPointF getSpeed() const;

    bool beforeTurnArea() const;
    
private:
    bool is_center_directed_() const;
    bool on_turn_area_() const;
    QPoint vector_to_center_();
    QPoint vector_to_next_();
    
    void update_cur_();
    void update_next_();
    
    Cell get_movements_cell_(QPoint gameCell);
    
private:
    CGame *game;

    QPoint curGameCell;
    QPoint nextGameCell;

    Cell curLocalCell;
    Cell nextLocalCell;
    QPoint curPos; //(0, 0) .. (220, 220)
    
    Queue queue;
    
    int ExitWidth;
    int ExitHeight;
    int LocalExitWidth;
    int LocalExitHeight;
    
    QRect NormalRect;
    QSize NormalSize;
    
    QRect EdgeXRect;
    QSize EdgeXSize;
    
    QRect EdgeYRect;
    QSize EdgeYSize;
    
    Cell NormalLocalCell;
    Cell EdgeXLocalCell;
    Cell EdgeYLocalCell;
    
    QPointF delta;
    
};

}
