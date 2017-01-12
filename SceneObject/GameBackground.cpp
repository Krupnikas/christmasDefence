#include <SceneObject/GameBackground.h>
#include <Game/Game.h>

CGameBackground::CGameBackground(CGame *game):
    CSceneBackground(game, game->r->game_background)
{
    fieldBackground = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.1,
                QPointF(0, 0), QSizeF(LocalWidth, LocalHeight),
                game->r->field_background, game);

    cells.assign(game->CellNumX + 2, std::vector<std::shared_ptr<CSceneObject>>(game->CellNumY + 2, nullptr));
    
    cells[game->startCell.x() + 1][game->startCell.y() + 1] = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.2,
                QPointF(x, y), QSizeF(game->CellSize, game->CellSize),
                game->r->cell1, game);
    
    cells[game->endCell.x() + 1][game->endCell.y() + 1] = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.2,
                QPointF(x, y), QSizeF(game->CellSize, game->CellSize),
                game->r->cell2, game);
    
    for (int i = 0; i < game->CellNumX; ++i)
        for (int j = 0; j < game->CellNumY; ++j)
        {
            int x = game->OffsetX + i * game->CellSize;
            int y = game->OffsetY + j * game->CellSize;
            std::shared_ptr<QPixmap> cellPixmap = ((i + j) % 2 == 0) ? game->r->cell1 : game->r->cell2;
            cells[i + 1][j + 1] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(x, y), QSizeF(game->CellSize, game->CellSize),
                        cellPixmap, game);
        }
    
    for (int i = 1; i < game->CellNumX + 1; ++i)
    {
        if (!cell[i][0])
            cells[i][0] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + i * game->CellSize, 0),
                        QSizeF(game->CellSize, game->OffsetY),
                        game->r->border_cell, game);
        
        int indY = game->CellNumY + 1;
        if (!cells[i][indY])
            cells[i][indY] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + i * game->CellSize, 
                                game->OffsetY + indY * game->CellSize),
                        QSizeF(game->CellSize, game->OffsetY),
                        game->r->border_cell, game);
    }
    
    for (int j = 0; j < CellNumY + 2; ++j)
    {
        if (!cell[0][j])
            cells[0][j] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(0, j * game->CellSize),
                        QSizeF(game->OffsetX, game->CellSize),
                        game->r->border_cell, game);
        
        int indX = game->CellNumX + 1;
        if (!cell[indX][j])
            cells[indX][j] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + indX * game->CellSize, j * game->CellSize),
                        QSizeF(game->OffsetX, game->CellSize),
                        game->r->border_cell, game);
    }
}

void CGameBackground::scale()
{
    CSceneBackground::scale();
    fieldBackground->scale();
    for (int i = 0; i < cells.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->scale();
}

void CGameBackground::scaleWithLoss(QSizeF newSize)
{
    CSceneBackground::scaleWithLoss(newSize);
    fieldBackground->scaleWithLoss(newSize);
    for (int i = 0; i < cells.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->scaleWithLoss(newSize);
}

void CGameBackground::remove()
{
    CSceneBackground::remove();
    fieldBackground->remove();
    for (int i = 0; i < cells.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->remove();
}

void CGameBackground::draw()
{
    CSceneBackground::draw();
    fieldBackground->draw();
    for (int i = 0; i < cell.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->draw();
}

void CGameBackground::hide()
{
    CSceneBackground::hide();
    fieldBackground->hide();
    for (int i = 0; i < cells.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->hide();
}

void CGameBackground::show()
{
    CSceneBackground::show();
    fieldBackground->show();
    for (int i = 0; i < cells.size(); ++i)
        for (int j = 0; j < cells[i].size(); ++j)
            cells[i][j]->show();
}
