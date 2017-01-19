#include <Game/Game.h>
#include <Enemy/IEnemy.h>
#include <Enemy/Movements.h>
#include <Enemy/CHpBackground.h>
#include <Enemy/CHpCurrent.h>
#include <Cannon/FastCannon.h>
#include <Helper.h>

IEnemy::IEnemy():
    dead(false),
    wasInsideGame(false),
    wasOutsideGame(false)
{}

IEnemy::~IEnemy(){}

bool IEnemy::isDead() const
{
    return dead;
}

void IEnemy::hit(int hpDiff)
{
    hpCur -= hpDiff;
    if (hpCur <= 0)
    {
        dead = true;
        hide();
        
        int cash = hpMax / m::EnemyCostFactor + 2;
        game->userManager.increaseCash(cash);
    }

    //not optimal, called too often
    if (hpCur < hpMax)
    {
        hpBackgroundItem->show();
        hpCurItem->show();
        updateHpSize();
    }
}

void IEnemy::updateHpPos()
{
    QPointF leftTop(0, 0);
    leftTop.setX(this->center.x() - m::HpSize.width() / 2.0);
    leftTop.setY(this->center.y() + m::CellSize / 2.0 - m::HpSize.height() * 4);
    hpCurItem->setLeftTop(leftTop);
    hpBackgroundItem->setLeftTop(leftTop);
}

void IEnemy::updateHpSize()
{
    QSizeF hpCurSize(m::HpSize);
    hpCurSize.setWidth(m::HpSize.width() * hpCur / hpMax);
    hpCurItem->scaleWithLoss(hpCurSize);
}

qreal IEnemy::getDistanceToFinish() const
{
    return movements->getDistanceToFinish();
}

QPoint IEnemy::getCurrentGameCell() const
{
    return movements->getCurrentGameCell();
}

QPoint IEnemy::getNextGameCell() const
{
    return movements->getNextGameCell();
}

bool IEnemy::beforeTurnArea() const
{
    return movements->beforeTurnArea();
}

QPointF IEnemy::getSpeed() const
{
    return movements->getSpeed() * moveIter;
}

bool IEnemy::getWasInsideGame()
{
    return wasInsideGame;
}

bool IEnemy::getWasOutsideGame()
{
    return wasOutsideGame;
}


void IEnemy::scale()
{
    CSceneObject::scale();
    hpBackgroundItem->scale();
    hpCurItem->scale();
}

void IEnemy::remove()
{
    hpBackgroundItem->remove();
    hpCurItem->remove();
    CSceneObject::remove();
//    game->buyCannon(std::make_shared<CFastCannon>(game, QPoint(0, 0), 0));
//    qDebug() << "removing enemy...";
}

void IEnemy::draw()
{
    game->scene->positionItemByCenter(center, textureSize, angle, zOrder, position);
    hpBackgroundItem->draw();
    hpCurItem->draw();
}

bool IEnemy::move()
{
    for (int i = 0; i < moveIter; ++i)
        center = movements->move();
    angle = movements->curAngle();

    updateHpPos();

    bool insideGame = game->scene->insideGameRect(center);
    if (wasInsideGame && !wasOutsideGame && !insideGame)
    {
        game->userManager.decreaseHp(1);
        wasOutsideGame = true;
    }
    if (!wasInsideGame && insideGame)
        wasInsideGame = true;
    
    if (!wasOutsideGame)
        return true;
    
    EEdge edge(helper::cellToEdge(m::endCells[0]));
    switch (edge)
    {
    case EEdge::eLeft:
        if (center.x() + textureSize.width() / 2 <= 0)
            return false;
        break;
    case EEdge::eTop:
        if (center.y() + textureSize.height() / 2 <= 0)
            return false;
        break;
    case EEdge::eRight:
        if (center.x() - textureSize.width() / 2 >= m::LocalWidth)
            return false;
        break;
    case EEdge::eBottom:
        if (center.y() - textureSize.height() / 2 >= m::LocalHeight)
            return false;
    case EEdge::eInside:
        break;
    }
    
    return true;
}

void IEnemy::hide()
{
    CSceneObject::hide();
    hpBackgroundItem->hide();
    hpCurItem->hide();
}

