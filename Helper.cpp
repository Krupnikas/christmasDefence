#include <queue>
#include <utility>
#include <limits>
#include <Helper.h>
#include <Game/Game.h>
#include <Wave/Wave.h>
#include <Enemy/FastEnemy.h>

namespace
{

const int dNum = 4;
const int dx[dNum] = {0, 1, 0, -1};
const int dy[dNum] = {-1, 0, 1, 0};

const int Inf = std::numeric_limits<int>::max();

std::mutex distancesMutex;

void breadth_first_search_(std::vector<std::vector<int> > &distances)
{
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
}


}

namespace helper
{

bool circlesIntersect(QPointF p1, qreal r1, QPointF p2, qreal r2)
{
    return manhattanLength(p1, p2)  <= r1 + r2;   
}

QPointF addVector(QPointF point, qreal len, const qreal &angle)
{
    qreal x = point.x() + qSin(qDegreesToRadians(angle)) * len;
    qreal y = point.y() - qCos(qDegreesToRadians(angle)) * len;
    return QPointF(x, y);
}

qreal calcAngle(QPointF p1, QPointF p2)
{
    QPointF p(p1.x(), p1.y() - 10);
    QLineF line1(p1, p);
    QLineF line2(p1, p2);
    return line2.angleTo(line1);
}

qreal calcAngle(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QLineF line1(x1, y1, x1, y1 - 10);
    QLineF line2(x1, y1, x2, y2);
    return 360 - line1.angleTo(line2);
}

void reconcileAngles(qreal &angle, const qreal &deltaAngle, const qreal &step)
{
    if (deltaAngle <= 180)
        angle += step;
    else
        angle -= step;
}

void updateDistances(
        std::vector<std::vector<std::shared_ptr<ICannon> > > &cannons,
        std::vector<std::vector<int> > &distances)
{
    distancesMutex.lock();
    //here we expect cannons to be correct array
    for (int x = 0; x < CellNumX; ++x)
        for (int y = 0; y < CellNumY; ++y)
        {
            if (cannons[x][y])
                distances[x][y] = Inf;    
            else
                distances[x][y] = -1;
        }
    
    breadth_first_search_(distances);
    distancesMutex.unlock();
}


bool okToAdd(int xInd, int yInd, const std::vector<std::vector<int> > &distances,
             std::vector<std::shared_ptr<IEnemy> > &enemies)
{
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->getCurrentGameCell() == QPoint(xInd, yInd) ||
            (enemies[i]->getNextGameCell() == QPoint(xInd, yInd) &&
             enemies[i]->beforeTurnArea()))
            return false;
    }

    distancesMutex.lock();
        if ((xInd == ExitX && yInd == ExitY) || (xInd == EntranceX && yInd == EntranceY))
        {
            distancesMutex.unlock();
            return false;
        }
        std::vector<std::vector<int>> distCheck(distances);
    distancesMutex.unlock();
    
    distCheck[xInd][yInd] = Inf;
    for (int x = 0; x < CellNumX; ++x)
        for (int y = 0; y < CellNumY; ++y)
            if (distCheck[x][y] != Inf)
                distCheck[x][y] = -1;
    
    breadth_first_search_(distCheck);
    
    /*    bool connected = true;
        for (int x = 0; x < CellNumX; ++x)
            for (int y = 0; y < CellNumY; ++y)
                if (distances[x][y] == -1)
                    connected = false;*/
    return /*connected && */(distCheck[EntranceX][EntranceY] > -1);
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
    
    qDebug() << "Helper: findLowerNeighbour: next cell not found, returning (-1, -1)";
    return QPoint(-1, -1);
}

qreal manhattanLength(QPointF p1, QPointF p2)
{
    return pow(pow(std::abs(p1.x() - p2.x()), 2.0) + pow(std::abs(p1.y() - p2.y()), 2.0), 0.5);
}

void readWaves(const QString &filename, std::vector<CWave> &waves)
{
    QFile waveFile(filename);
    if (!waveFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Helper: readWaves: failed to open waves.txt";
        return;
    }
    QTextStream textStream(&waveFile);
    QString line;
    line = textStream.readLine();
    int waveNum(line.toInt());
    
    waves.clear();
    for (int i = 0; i < waveNum; ++i)
    {
        CWave wave;        
        line = textStream.readLine();
        std::stringstream in(line.toStdString());
        
        in >> wave.timeBeforeStart;
        in >> wave.enemyIncomeInterval;
        in >> wave.totalEnemyNum;
        in >> wave.enemyType;
        in >> wave.enemyTexture;
        in >> wave.enemyPower;
        waves.push_back(wave);        
    }
    
    waveFile.close();
}

qreal ticksToTime(int ticks)
{
    return static_cast<qreal>(ticks) * TimerInterval / 1000;
}

std::shared_ptr<QPixmap> renderPixmapFromText(QString Text)
{
    QPainterPath path;
    QFont myFont("Helvetica [Cronyx]", 94);
    int i = 0;
    if (Text.count() == 1)
        i++;
    std::shared_ptr<QPixmap> pixmap = std::make_shared<QPixmap>((Text.count() + i) * myFont.pointSize() * 0.9, 100);

    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap.get());
    painter.setPen(QPen(QBrush(Qt::black), 2));
    painter.setBrush(Qt::white);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    path.addText(QPointF(10 + i * myFont.pointSize() * 0.4, 96), myFont, Text);

    painter.drawPath(path);

    return pixmap;
}

}
