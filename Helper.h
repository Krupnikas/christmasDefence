#pragma once

#include <Resource.h>

class ICannon;
class IEnemy;
struct CWave;
class CGame;

namespace helper {

bool circlesIntersect(QPointF p1, qreal r1, QPointF p2, qreal r2);
QPointF addVector(QPointF point, qreal len, const qreal &angle);
qreal calcAngle(QPointF p1, QPointF p2);
qreal calcAngle(qreal x1, qreal y1, qreal x2, qreal y2);

qreal calcAngle(QPointF cannonCenter, qreal cannonAngle, QPointF enemyCenter, QPointF enemySpeed, qreal bulletSpeed);
qreal manhattanLength(QPointF p1, QPointF p2);

void reconcileAngles(qreal &angle, const qreal &deltaAngle, const qreal &step);

void updateDistances(std::vector<std::vector<std::shared_ptr<ICannon>>> &cannons,
    std::vector<std::vector<int>> &distances);
bool okToAdd(QPoint cell, const std::vector<std::vector<int>> &distances,
             std::vector<std::shared_ptr<IEnemy> > &enemies);
QPoint findLowerNeighbour(std::vector<std::vector<int>> &distances, const QPoint& curPoint);

template <class T>
T choose(ESizeType type, T var1, T var2, T var3)
{
    switch (type)
    {
    case ESizeType::eSmall:
        return var1;
    case ESizeType::eMedium:
        return var2;
    case ESizeType::eBig:
        return var3;
    default:
        return var1;
    }
}

std::shared_ptr<QPixmap> renderPixmapFromText(QString text,
                                              QPen pen = QPen(QBrush(QColor(153, 199, 255, 255)), 2),
                                              QBrush brush = QBrush(Qt::white),
                                              QFont font = QFont("Helvetica [Cronyx]", 376),
                                              QColor backgroundColor = Qt::transparent);

void readLevel(const QString &filename, std::vector<CWave> &waves);

qreal ticksToTime(int ticks);

QPointF getCellLeftTop(QPoint cell);
QPointF getCellLeftTop(int cellX, int cellY);

QSizeF getCellSize(QPoint cell);
QSizeF getCellSize(int cellX, int cellY);

EEdge cellToEdge(QPoint cell);

void initMetrics();

}
