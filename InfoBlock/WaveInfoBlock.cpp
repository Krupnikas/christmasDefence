#include "WaveInfoBlock.h"

CWaveInfoBlock::CWaveInfoBlock(CGame *game):
    totalWaveNum(0)
{
    //IGameObject fields
    this->label = "Wave Information Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = UserInfoOnSides;

    this->textureSize = QSize(game->OffsetX,
                              game->OffsetY + game->CellSize * (game->CellNumY / 2));
    this->pixmap = game->r->userInfoBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->leftTop = QPoint(game->OffsetX + game->CellSize * game->CellNumX, 0);

    waveCounter = std::make_shared<CImageAndNumber>(game,
                                           game->r->wave_counter_icon,
                                           QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                                  InternalOffsetY),
                                                 QSize(textureSize.width() - 2 * InternalOffsetX,
                                                       (textureSize.height() - 3 * InternalOffsetY)/2)));
    enemyCounter = std::make_shared<CImageAndNumber>(game,
                                           game->r->current_wave_icon,
                                           QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                                  InternalOffsetY * 2 + (textureSize.height() - 3 * InternalOffsetY)/2),
                                                 QSize(textureSize.width() - 2 * InternalOffsetX,
                                                       (textureSize.height() - 3 * InternalOffsetY)/2)));
}

void CWaveInfoBlock::draw()
{
    CSceneObject::draw();
    waveCounter->updatePosition(QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                        InternalOffsetY),
                                       QSize(textureSize.width() - 2 * InternalOffsetX,
                                             (textureSize.height() - 3 * InternalOffsetY)/2)));
    waveCounter->draw();
    enemyCounter->updatePosition(QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                           InternalOffsetY * 2 + (textureSize.height() - 3 * InternalOffsetY)/2),
                                          QSize(textureSize.width() - 2 * InternalOffsetX,
                                                (textureSize.height() - 3 * InternalOffsetY)/2)));
    enemyCounter->draw();
}

void CWaveInfoBlock::hide()
{
    CSceneObject::hide();
    waveCounter->hide();
    enemyCounter->hide();
}

void CWaveInfoBlock::show()
{
    CSceneObject::show();
    waveCounter->show();
    enemyCounter->show();
}

void CWaveInfoBlock::scale()
{
    CSceneObject::scale();
    waveCounter->scale();
    enemyCounter->scale();
}

void CWaveInfoBlock::remove()
{
    waveCounter->remove();
    enemyCounter->remove();
    CSceneObject::remove();
}

void CWaveInfoBlock::onEnemyNumChanged(int newEnemyNum)
{
    enemyCounter->changeText(QString::number(newEnemyNum));
    enemyCounter->draw();
    enemyCounter->show();
}

void CWaveInfoBlock::onCurWaveChanged(int newCurWave)
{
    if (newCurWave > totalWaveNum)
        newCurWave = totalWaveNum;
    this->waveCounter->changeText(QString::number(newCurWave + 1)
                                  + QString("/")
                                  + QString::number(totalWaveNum));
    waveCounter->draw();
    waveCounter->show();
}

int CWaveInfoBlock::getTotalWaveNum() const
{
    return totalWaveNum;
}

void CWaveInfoBlock::setTotalWaveNum(int value)
{
    totalWaveNum = value;
}
