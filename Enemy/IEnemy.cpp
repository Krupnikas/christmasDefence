#include <Game/Game.h>
#include <Enemy/IEnemy.h>
#include <Enemy/Movements.h>
#include <Enemy/CHpBackground.h>
#include <Enemy/CHpCurrent.h>

IEnemy::IEnemy(){}

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
        game->user.increaseCash(hpMax / EnemyCostFactor);
    }
    updateHpSize();
}

void IEnemy::updateHpPos()
{
    QPointF leftTop(0, 0);
    leftTop.setX(this->center.x() - HpSize.width() / 2.0);
    leftTop.setY(this->center.y() + CellSize / 2.0 - HpSize.height() * 4);
    hpCurItem->setLeftTop(leftTop);
    hpBackgroundItem->setLeftTop(leftTop);
}

void IEnemy::updateHpSize()
{
    QSizeF hpCurSize(HpSize);
    hpCurSize.setWidth(HpSize.width() * hpCur / hpMax);
    hpCurItem->scaleItemWithLoss(hpCurSize);
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


void IEnemy::scaleItem()
{
    CGameObject::scaleItem();
    hpBackgroundItem->scaleItem();
    hpCurItem->scaleItem();
}

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
    
    updateHpPos();
    hpBackgroundItem->draw();
    hpCurItem->draw();
    
    bool inside = game->scene->insideEnclosingRect(center);
    if (!inside)
        game->user.decreaseHp(hpCur);
    return inside;
}

QPixmap *IEnemy::getTexture(int enemyTexture){}

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


