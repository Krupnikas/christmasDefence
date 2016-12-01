#include <queue>
#include <utility>
#include <limits>
#include <Game/Helper.h>
#include <Wave/Wave.h>

namespace
{

const int dNum = 4;
const int dx[dNum] = {0, 1, 0, -1};
const int dy[dNum] = {-1, 0, 1, 0};

const int Inf = std::numeric_limits<int>::max();
}

namespace helper
{

qreal calcAngle(QPointF p1, QPointF p2)
{
    QPointF p(p1.x(), p1.y() - 10);
    QLineF line1(p1, p);
    QLineF line2(p1, p2);
    return 360 - line1.angleTo(line2);
}

qreal calcAngle(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QLineF line1(x1, y1, x1, y1 - 10);
    QLineF line2(x1, y1, x2, y2);
    return 360 - line1.angleTo(line2);
}

qreal calcAngle(QPointF p1, QPointF p2, const qreal &angle1)
{
    QPointF p3(addVector(p1, 10, angle1));
    QLineF line1(p1, p3);
    QLineF line2(p1, p2);
    qreal deltaAngle = line2.angleTo(line1);
    if (deltaAngle > 180)
        deltaAngle -= 360;
    return std::max(deltaAngle, deltaAngle);
}

void reconcileAngles(qreal &angle, const qreal &deltaAngle, const qreal &step)
{
    if (deltaAngle <= 180)
        angle += step;
    else
        angle -= step;
}

bool calcDistances(
        std::vector<std::vector<std::shared_ptr<ICannon> > > &cannons,
        std::vector<std::vector<int> > &distances)
{
    if (cannons[ExitX][ExitY] || cannons[EntranceX][EntranceY])
        return false;
    
    for (int x = 0; x < CellNumX; ++x)
        for (int y = 0; y < CellNumY; ++y)
        {
            if (cannons[x][y])
                distances[x][y] = Inf;    
            else
                distances[x][y] = -1;
        }
    
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(ExitX, ExitY));
    distances[ExitX][ExitY] = 0;
    
    while (!queue.empty())
    {
        int x = queue.front().first ;
        int y = queue.front().second;
        queue.pop();

        int nextDistance = distances[x][y] + 1;
        for (int i = 0; i < dNum; ++i)
        {
            int xNext = x + dx[i];
            int yNext = y + dy[i];
            if (xNext < 0 || yNext < 0 || 
                    xNext >= CellNumX || yNext >= CellNumY || 
                    distances[xNext][yNext] > -1)
                continue;
            
            distances[xNext][yNext] = nextDistance;
            queue.push(std::make_pair(xNext, yNext));
        }
    }
    
/*    bool connected = true;
    for (int x = 0; x < CellNumX; ++x)
        for (int y = 0; y < CellNumY; ++y)
            if (distances[x][y] == -1)
                connected = false;*/
    
    return /*connected && */(distances[EntranceX][EntranceY] > -1);
}

QPoint findLowerNeighbour(std::vector<std::vector<int> > &distances, const QPoint& curPoint)
{
    QPoint ans(curPoint);
    if (ExitLeft)
    {
        if (ans.y() == CellNumY / 2 && (ans.x() <= 0 || ans.x() >= CellNumX))
        {
            ans.setX(ans.x() - 1);
            return ans;
        }
    }
    else
    {
        if (ans.y() == CellNumY / 2 && (ans.x() < 0 || ans.x() >= CellNumX - 1))
        {
            ans.setX(ans.x() + 1);        
            return ans;
        }
    }

    //random permutation of indecies for moving to random cell first
    std::vector<int> randomInd(dNum);
    for (int i = 0; i < dNum; ++i)
        randomInd[i] = i;
    std::random_shuffle(randomInd.begin(), randomInd.end());
    
    int curVal = distances[curPoint.x()][curPoint.y()];
    for (int i = 0; i < dNum; ++i)
    {
        int xNext = curPoint.x() + dx[randomInd[i]];
        int yNext = curPoint.y() + dy[randomInd[i]];
        if (xNext < 0 || yNext < 0 || 
                xNext >= CellNumX || yNext >= CellNumY)
            continue;
        if (distances[xNext][yNext] + 1 == curVal)
            return QPoint(xNext, yNext);
    }
    return QPoint(-1, -1);
}

QPointF addVector(QPointF point, qreal len, const qreal &angle)
{
    qreal x = point.x() + qSin(qDegreesToRadians(angle)) * len;
    qreal y = point.y() - qCos(qDegreesToRadians(angle)) * len;
    return QPointF(x, y);
}

qreal manhattanLength(QPointF p1, QPointF p2)
{
    return pow(pow(abs(p1.x() - p2.x()), 2.0) + pow(abs(p1.y() - p2.y()), 2.0), 0.5);
}

std::vector<CWave> &readWaves(std::string filename)
{
    std::ifstream in(filename.c_str());
    int waveNum;
    in >> waveNum;
    
    std::vector<CWave> waves;
    for (int i = 0; i < waveNum; ++i)
    {
        CWave wave;
        
    }
}


}
