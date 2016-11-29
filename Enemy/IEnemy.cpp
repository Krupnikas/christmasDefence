#include <Game/Game.h>
#include <Enemy/IEnemy.h>
#include <Enemy/Movements.h>
#include <Enemy/CHpBackground.h>
#include <Enemy/CHpCurrent.h>

IEnemy::IEnemy(){}

IEnemy::~IEnemy(){}

void IEnemy::draw()
{
    CGameObject::draw();
    hpBackgroundItem->draw();
    hpCurItem->draw();
}

bool IEnemy::move()
{
    for (int i = 0; i < moveIter; ++i)
        center = movements->move();
    angle = movements->curAngle();
    game->scene->positionItemByCenter(center, textureSize, angle, zOrder, position);
    
    updateHp();
    hpBackgroundItem->draw();
    hpCurItem->draw();
    
    return game->scene->insideGameRect(center);
}

void IEnemy::hide()
{
    CGameObject::hide();
    hpBackgroundItem->hide();
    hpCurItem->hide();
}

void IEnemy::show()
{
    CGameObject::show();
    hpBackgroundItem->show();
    hpCurItem->show();
}

bool IEnemy::isDead() const
{
    return dead;
}

void IEnemy::hit(int hpDiff)
{
    hpCur -= hpDiff;
    if (hpCur <= 0)
        dead = true;
    updateHp();
}

void IEnemy::updateHp()
{
    QPointF leftTop(0, 0);
    leftTop.setX(this->center.x() - HpSize.width() / 2);
    leftTop.setY(this->center.y() + CellSize / 2 - HpSize.height() * 4);
    QSizeF hpCurSize(HpSize);
    hpCurSize.setWidth(HpSize.width() * hpCur / hpMax);
    hpCurItem->scaleItemWithLoss(hpCurSize, LeftTop);
    hpCurItem->setLeftTop(leftTop);
    hpBackgroundItem->setLeftTop(leftTop);
}

qreal IEnemy::getDistanceToFinish()
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


