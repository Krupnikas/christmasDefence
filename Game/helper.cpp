#include <Game/Helper.h>

namespace helper {

double calcAngle(QPoint p1, QPoint p2)
{
    QPoint p(p1.x(), p1.y() - 10);
    QLineF line1(p1, p);
    QLineF line2(p1, p2);
    return 360 - line1.angleTo(line2);
}

double calcAngle(int x1, int y1, int x2, int y2)
{
    QLineF line1(x1, y1, x1, y1 - 10);
    QLineF line2(x1, y1, x2, y2);
    return 360 - line1.angleTo(line2);
}
}
