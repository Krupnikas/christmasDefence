#pragma once

#include <Game/Resource.h>

class ICannon;

namespace helper {

double calcAngle(QPoint p1, QPoint p2);
double calcAngle(int x1, int y1, int x2, int y2);
bool calcDistances(
    std::vector<std::vector<std::shared_ptr<ICannon>>> &cannons,
    std::vector<std::vector<int>> &distances);
QPointF addVector(QPointF point, qreal len, qreal angle);

}
