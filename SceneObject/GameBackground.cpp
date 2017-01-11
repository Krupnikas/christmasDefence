#include <SceneObject/GameBackground.h>
#include <Game/Game.h>

CGameBackground::CGameBackground(CGame *game):
    CSceneBackground(game, game->r->game_background)
{
    fieldBackground = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.1,
                QPointF(0, 0), QSizeF(LocalWidth, LocalHeight),
                game->r->field_background, game);

    cells.assign(CellNumX, std::vector<std::shared_ptr<CSceneObject>>(CellNumY));
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
        {
            int x = OffsetX + i * CellSize;
            int y = OffsetY + j * CellSize;
            std::shared_ptr<QPixmap> cellPixmap = ((i + j) % 2 == 0) ? game->r->cell1 : game->r->cell2;
            cells[i][j] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(x, y), QSizeF(CellSize, CellSize),
                        cellPixmap, game);
        }
}

void CGameBackground::scale()
{
    CSceneBackground::scale();
    fieldBackground->scale();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->scale();
}

void CGameBackground::scaleWithLoss(QSizeF newSize)
{
    CSceneBackground::scaleWithLoss(newSize);
    fieldBackground->scaleWithLoss(newSize);
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->scaleWithLoss(newSize);
}

void CGameBackground::remove()
{
    CSceneBackground::remove();
    fieldBackground->remove();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->remove();
}

void CGameBackground::draw()
{
    CSceneBackground::draw();
    fieldBackground->draw();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->draw();
}

void CGameBackground::hide()
{
    CSceneBackground::hide();
    fieldBackground->hide();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->hide();
}

void CGameBackground::show()
{
    CSceneBackground::show();
    fieldBackground->show();
    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            cells[i][j]->show();
}
