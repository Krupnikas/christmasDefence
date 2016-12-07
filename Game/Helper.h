#pragma once

#include <Game/Resource.h>

class ICannon;
class CWave;
class CGame;

namespace helper {

QPointF addVector(QPointF point, qreal len, const qreal &angle);
qreal calcAngle(QPointF p1, QPointF p2);
qreal calcAngle(qreal x1, qreal y1, qreal x2, qreal y2);

qreal calcAngle(QPointF cannonCenter, qreal cannonAngle, QPointF enemyCenter, QPointF enemySpeed, qreal bulletSpeed);
qreal manhattanLength(QPointF p1, QPointF p2);

void reconcileAngles(qreal &angle, const qreal &deltaAngle, const qreal &step);

void updateDistances(
    std::vector<std::vector<std::shared_ptr<ICannon>>> &cannons,
    std::vector<std::vector<int>> &distances);
bool okToAdd(int xInd, int yInd, const std::vector<std::vector<int>> &distances);
QPoint findLowerNeighbour(std::vector<std::vector<int>> &distances, const QPoint& curPoint);

template <class T>
T choose(SizeType type, T var1, T var2, T var3)
{
    switch (type)
    {
    case SMALL:
        return var1;
    case MEDIUM:
        return var2;
    case BIG:
        return var3;
    default:
        return var1;
    }
}

void readWaves(const QString &filename, std::vector<CWave> &waves);

qreal ticksToTime(int ticks);

}
