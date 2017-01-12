#include <SceneObject/GameBackground.h>
#include <Game/Game.h>

namespace
{

QRectF get_border_cell_left_top_(QPoint cell, CGame *game)
{
    qreal x = 0;
    qreal y = 0;
    qreal height = game->CellSize;
    qreal width = height;
    
    if (cell.x() == 0)
    {
        x = 0;
        y = game->OffsetY + cell.y() * game->CellSize;
        width = game->OffsetX;
    }
    else if (cell.x() == game->CellNumX - 1)
    {
        x = game->OffsetX + game->CellNumX * game->CellSize;
        y = game->OffsetY + cell.y() * game->CellSize;
        width = game->OffsetX;
    }
    else if (cell.y() == 0)
    {
        x = game->OffsetX + cell.x() * game->CellSize;
        y = 0;
    }
    else if (cell.y() == game->CellNumY - 1)
    {
        x = game->OffsetX + (cell.x() + 1) * game->CellSize;
        y = game->OffsetY + game->CellNumY * game->CellSize;
    }
    
    return QRectF(x, y, width, height);
}

QPoint get_border_cell_(QPoint cell, CGame *game)
{
    int x = cell.x();
    int y = cell.y();
    if (cell.x() == 0)
    {
        ++y;
    }
    else if (cell.x() == game->CellNumX - 1)
    {
        x += 2;
        ++y;
    }
    else if (cell.y() == 0)
    {
        ++x;
    }
    else if (cell.y() == game->CellNumY - 1)
    {
        ++x;
        y += 2;
    }
    return QPoint(x, y);
}

}

CGameBackground::CGameBackground(CGame *game):
    CSceneBackground(game, game->r->game_background)
{
    fieldBackground = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.1,
                QPointF(0, 0), QSizeF(LocalWidth, LocalHeight),
                game->r->field_background, game);

    cells.assign(game->CellNumX + 2, std::vector<std::shared_ptr<CSceneObject>>(game->CellNumY + 2, nullptr));
    
    //start cell
    QRectF start = get_border_cell_left_top_(game->startCell, game);    
    QPoint startCell = get_border_cell_(game->startCell, game);
    cells[startCell.x()][startCell.y()] = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.2,
                start.topLeft(), start.size(),
                game->r->cell1, game);
    
    //end cell
    QRectF end = get_border_cell_left_top_(game->endCell, game);
    QPoint endCell = get_border_cell_(game->endCell, game);
    cells[endCell.x()][endCell.y()] = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.2,
                end.topLeft(), end.size(),
                game->r->cell2, game);
    
    //game cells
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
    
    
    //border cells
    for (int i = 1; i < game->CellNumX + 1; ++i)
    {
        if (!cells[i][0])
            cells[i][0] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + (i - 1) * game->CellSize, 0),
                        QSizeF(game->CellSize, game->OffsetY),
                        game->r->border_cell, game);
        
        int indY = game->CellNumY + 1;
        if (!cells[i][indY])
            cells[i][indY] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + (i - 1) * game->CellSize, 
                                game->OffsetY + (indY - 1) * game->CellSize),
                        QSizeF(game->CellSize, game->OffsetY),
                        game->r->border_cell, game);
    }
    
    for (int j = 0; j < game->CellNumY + 2; ++j)
    {
        if (!cells[0][j])
            cells[0][j] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(0, j * game->CellSize),
                        QSizeF(game->OffsetX, game->CellSize),
                        game->r->border_cell, game);
        
        int indX = game->CellNumX + 1;
        if (!cells[indX][j])
            cells[indX][j] = std::make_shared<CSceneObject>(
                        0, BackgroundZOrder + 0.2,
                        QPointF(game->OffsetX + (indX - 1) * game->CellSize, j * game->CellSize),
                        QSizeF(game->OffsetX, game->CellSize),
                        game->r->border_cell, game);
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
