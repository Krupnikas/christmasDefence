#pragma once

#include <QLineF>
#include <QtCore/qmath.h>

namespace helper {

double calcAngle(QPoint p1, QPoint p2);
double calcAngle(int x1, int y1, int x2, int y2);
QPointF addVector(QPointF point, qreal len, qreal angle);

}
