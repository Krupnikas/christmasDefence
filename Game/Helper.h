#pragma once

#include <Game/Resource.h>

class ICannon;

namespace helper {

qreal calcAngle(QPointF p1, QPointF p2);
qreal calcAngle(qreal x1, qreal y1, qreal x2, qreal y2);
bool calcDistances(
    std::vector<std::vector<std::shared_ptr<ICannon>>> &cannons,
    std::vector<std::vector<int>> &distances);
QPoint findLowerNeighbour(std::vector<std::vector<int>> &distances, QPoint curPoint);

QPointF addVector(QPointF point, qreal len, qreal angle);

}
