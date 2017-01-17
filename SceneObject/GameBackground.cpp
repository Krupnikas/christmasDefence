#include <SceneObject/GameBackground.h>
#include <Game/Game.h>
#include <Helper.h>

CGameBackground::CGameBackground(CGame *game):
    CSceneBackground(game, game->r->game_background)
{
    fieldBackground = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.1,
                QPointF(0, 0), QSizeF(m::LocalWidth, m::LocalHeight),
                game->r->field_background, game);

    cells.assign(m::CellNumX, std::vector<std::shared_ptr<CSceneObject>>(m::CellNumY, nullptr));
    
    //start cell
    for (QPoint &p: m::startCells)
        cells[p.x()][p.y()] = std::make_shared<CSceneObject>(
                    0, m::BackgroundZOrder + 0.2,
                    game->cellLeftTop(p), game->cellSize(p),
                    game->r->cell1, game);
        
    //end cell
    for (QPoint &p: m::endCells)
    cells[p.x()][p.y()] = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.2,
                game->cellLeftTop(p), game->cellSize(p),
                game->r->cell2, game);
    
    //game cells
    for (int i = 0; i < m::CellNumX; ++i)
        for (int j = 0; j < m::CellNumY; ++j)
            if (!cells[i][j])
            {
                EEdge edge(helper::cellToEdge(QPoint(i, j)));
                
                std::shared_ptr<QPixmap> cellPixmap;
                if (edge != EEdge::eInside)
                    cellPixmap = game->r->border_cell;
                else if ((i + j) % 2 == 0)
                    cellPixmap = game->r->cell1;
                else
                    cellPixmap = game->r->cell2;
                
                cells[i][j] = std::make_shared<CSceneObject>(
                            0, m::BackgroundZOrder + 0.2,
                            game->cellLeftTop(QPoint(i, j)), game->cellSize(QPoint(i, j)),
                            cellPixmap, game);
            }
}

void CGameBackground::scale()
{
    CSceneBackground::scale();
    fieldBackground->scale();
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->scale();
}

void CGameBackground::scaleWithLoss(QSizeF newSize)
{
    CSceneBackground::scaleWithLoss(newSize);
    fieldBackground->scaleWithLoss(newSize);
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->scaleWithLoss(newSize);
}

void CGameBackground::remove()
{
    CSceneBackground::remove();
    fieldBackground->remove();
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->remove();
}

void CGameBackground::draw()
{
    CSceneBackground::draw();
    fieldBackground->draw();
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->draw();
}

void CGameBackground::hide()
{
    CSceneBackground::hide();
    fieldBackground->hide();
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->hide();
}

void CGameBackground::show()
{
    CSceneBackground::show();
    fieldBackground->show();
    for (size_t i = 0; i < cells.size(); ++i)
        for (size_t j = 0; j < cells[i].size(); ++j)
            cells[i][j]->show();
}
