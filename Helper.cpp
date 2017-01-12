#include <queue>
#include <utility>
#include <limits>
#include <Helper.h>
#include <Game/Game.h>
#include <Game/Wave.h>
#include <Enemy/FastEnemy.h>

namespace
{

const int dNum = 4;
const int dx[dNum] = {0, 1, 0, -1};
const int dy[dNum] = {-1, 0, 1, 0};

const int Inf = std::numeric_limits<int>::max();

std::mutex distancesMutex;

void breadth_first_search_(std::vector<std::vector<int> > &distances, CGame *game)
{
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(game->endCell.x(), game->endCell.y()));
    distances[game->endCell.x()][game->endCell.y()] = 0;
    
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
                    xNext >= game->CellNumX || yNext >= game->CellNumY || 
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
        std::vector<std::vector<int> > &distances,
        CGame *game)
{
    distancesMutex.lock();
    //here we expect cannons to be correct array
    for (size_t x = 0; x < cannons.size(); ++x)
        for (size_t y = 0; y < cannons[x].size(); ++y)
        {
            if (cannons[x][y])
                distances[x][y] = Inf;    
            else
                distances[x][y] = -1;
        }
    
    breadth_first_search_(distances, game);
    distancesMutex.unlock();
}


bool okToAdd(int xInd, int yInd, const std::vector<std::vector<int> > &distances,
             std::vector<std::shared_ptr<IEnemy> > &enemies,
             CGame *game)
{
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i]->getCurrentGameCell() == QPoint(xInd, yInd) ||
            (enemies[i]->getNextGameCell() == QPoint(xInd, yInd) &&
             !enemies[i]->beforeTurnArea()))
            return false;
    }

    distancesMutex.lock();
        if ((xInd == game->endCell.x() && yInd == game->endCell.y()) || (xInd == game->startCell.x() && yInd == game->startCell.y()))
        {
            distancesMutex.unlock();
            return false;
        }
        std::vector<std::vector<int>> distCheck(distances);
    distancesMutex.unlock();
    
    distCheck[xInd][yInd] = Inf;
    for (size_t x = 0; x < distCheck.size(); ++x)
        for (size_t y = 0; y < distCheck[x].size(); ++y)
            if (distCheck[x][y] != Inf)
                distCheck[x][y] = -1;
    
    breadth_first_search_(distCheck, game);
    
    /*    bool connected = true;
        for (int x = 0; x < CellNumX; ++x)
            for (int y = 0; y < CellNumY; ++y)
                if (distances[x][y] == -1)
                    connected = false;*/
    return /*connected && */(distCheck[game->startCell.x()][game->startCell.y()] > -1);
}


QPoint findLowerNeighbour(std::vector<std::vector<int> > &distances, const QPoint& curPoint, CGame *game)
{        
    QPoint ans(curPoint);
    if (ExitLeft)
    {
        if (ans.x() <= 0 || ans.x() >= game->CellNumX)
        {
            ans.setX(ans.x() - 1);
            return ans;
        }
    }
    else
    {
        if (ans.x() < 0 || ans.x() >= game->CellNumX - 1)
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
                xNext >= game->CellNumX || yNext >= game->CellNumY)
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

void readLevel(const QString &filename, std::vector<CWave> &waves)
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

std::shared_ptr<QPixmap> renderPixmapFromText(QString text, QPen pen, QBrush brush, QFont font, QColor backgroundColor)
{
    QPainterPath path;
    QFontMetrics fm(font);

    int  width, minWidth, height;

    height = 400;
    minWidth = height * 16.0 / 9;    //соотношение сторон картинки 16*9 или шире

    width = fm.width(text);

    if (width < minWidth)
            width = minWidth;

    std::shared_ptr<QPixmap> pixmap = std::make_shared<QPixmap>(width, height);

    pixmap->fill(backgroundColor);

    QPainter painter(pixmap.get());
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    path.addText(QPointF((width / 2.0) - fm.width(text) / 2.0, height * 0.96), font, text);

    painter.drawPath(path);

    return pixmap;
}

}
