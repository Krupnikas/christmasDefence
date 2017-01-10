#include "WaveInfoBlock.h"

CWaveInfoBlock::CWaveInfoBlock(CGame *game)
{
    //IGameObject fields
    this->label = "Wave Information Block";
    this->angle = 0;
    this->game = game;
    this->zOrder = UserInfoOnSides;

    this->textureSize = QSize(OffsetX,
                              OffsetY + CellSize * (CellNumY / 2));
    this->pixmap = &game->r->userInfoBackground;
    this->position = game->scene->addPixmap(textureSize, pixmap);

    this->leftTop = QPoint(OffsetX + CellSize * CellNumX, 0);

    waveCounter = std::make_shared<CImageAndNumber>(game,
                                           &game->r->wave_counter_icon,
                                           QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                                  InternalOffsetY),
                                                 QSize(textureSize.width() - 2 * InternalOffsetX,
                                                       (textureSize.height() - 3 * InternalOffsetY)/2)));
    currentWave = std::make_shared<CImageAndNumber>(game,
                                           &game->r->current_wave_icon,
                                           QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                                  InternalOffsetY * 2 + (textureSize.height() - 3 * InternalOffsetY)/2),
                                                 QSize(textureSize.width() - 2 * InternalOffsetX,
                                                       (textureSize.height() - 3 * InternalOffsetY)/2)));

    connect(&game->user,
            SIGNAL(cashChanged(int)),
            this,
            SLOT(onCashChanged(int)));

    connect(&game->waveManager,
            SIGNAL(curWaveChanged(int)),
            this,
            SLOT(onCurWaveChanged(int)));

    waveCounter->changeText(QString::number(0));
    currentWave->changeText(QString::number(game->user.getCash()));
}

void CWaveInfoBlock::draw()
{
    CSceneObject::draw();
    waveCounter->updatePosition(QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                        InternalOffsetY),
                                       QSize(textureSize.width() - 2 * InternalOffsetX,
                                             (textureSize.height() - 3 * InternalOffsetY)/2)));
    waveCounter->draw();
    currentWave->updatePosition(QRect(leftTop.toPoint() + QPoint(InternalOffsetX,
                                                           InternalOffsetY * 2 + (textureSize.height() - 3 * InternalOffsetY)/2),
                                          QSize(textureSize.width() - 2 * InternalOffsetX,
                                                (textureSize.height() - 3 * InternalOffsetY)/2)));
    currentWave->draw();
}

void CWaveInfoBlock::hide()
{
    CSceneObject::hide();
    waveCounter->hide();
    currentWave->hide();
}

void CWaveInfoBlock::show()
{
    CSceneObject::show();
    waveCounter->show();
    currentWave->show();
}

void CWaveInfoBlock::scale()
{
    CSceneObject::scale();
    waveCounter->scale();
    currentWave->scale();
}

void CWaveInfoBlock::remove()
{
    waveCounter->remove();
    currentWave->remove();
    CSceneObject::remove();
}

void CWaveInfoBlock::onCurWaveChanged(int newCurWave)
{
    this->waveCounter->changeText(QString::number(newCurWave)
                                  + QString("/")
                                  + QString::number(game->waveManager.getNumberOfWaves()));
    waveCounter->draw();
    waveCounter->show();
}

void CWaveInfoBlock::onCashChanged(int newCash)
{
    this->currentWave->changeText(QString::number(newCash));
    currentWave->draw();
    currentWave->show();
}
