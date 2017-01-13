#include <SceneObject/GameBackground.h>
#include <Game/Game.h>
#include <Helper.h>

namespace
{

/*
QRectF get_border_cell_left_top_(QPoint cell, CGame *game)
{
    qreal x = 0;
    qreal y = 0;
    qreal height = metrics::CellSize;
    qreal width = height;
    
    if (cell.x() == 0)
    {
        x = 0;
        y = m::OffsetY + cell.y() * metrics::CellSize;
        width = m::OffsetX;
    }
    else if (cell.x() == CellNumX - 1)
    {
        x = m::OffsetX + CellNumX * metrics::CellSize;
        y = m::OffsetY + cell.y() * metrics::CellSize;
        width = m::OffsetX;
    }
    else if (cell.y() == 0)
    {
        x = m::OffsetX + cell.x() * metrics::CellSize;
        y = 0;
    }
    else if (cell.y() == metrics::CellNumY - 1)
    {
        x = m::OffsetX + (cell.x() + 1) * metrics::CellSize;
        y = m::OffsetY + metrics::CellNumY * metrics::CellSize;
    }
    
    return QRectF(x, y, width, height);
}*/


QPoint get_border_cell_(QPoint cell, CGame *game)
{
    int x = cell.x();
    int y = cell.y();
    if (cell.x() == 0)
    {
        ++y;
    }
    else if (cell.x() == m::CellNumX - 1)
    {
        x += 2;
        ++y;
    }
    else if (cell.y() == 0)
    {
        ++x;
    }
    else if (cell.y() == m::CellNumY - 1)
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
                0, m::BackgroundZOrder + 0.1,
                QPointF(0, 0), QSizeF(m::LocalWidth, m::LocalHeight),
                game->r->field_background, game);

    cells.assign(m::CellNumX, std::vector<std::shared_ptr<CSceneObject>>(m::CellNumY, nullptr));
    
    //start cell
    cells[m::startCell.x()][m::startCell.y()] = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.2,
                helper::getCellLeftTop(m::startCell), helper::getCellSize(m::startCell),
                game->r->cell1, game);
    
    //end cell
    cells[m::endCell.x()][m::endCell.y()] = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.2,
                getCellLeftTop(m::endCell), helper::getCellSize(m::endCell),
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
                            getCellLeftTop(i, j), helper::getCellSize(i, j),
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
