#include <SceneObject/GameBackground.h>
#include <Game/Game.h>

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

QRectF get_cell_left_top_(QPoint cell, CGame *game)
{
    qreal x = 0;
    qreal y = 0;
    qreal height = m::CellSize;
    qreal width = height;
    
    if (cell.x() == 0)
    {
        x = 0;
        y = m::OffsetY + cell.y() * m::CellSize;
        width = m::OffsetX;
    }
    else if (cell.x() == m::CellNumX - 1)
    {
        x = m::OffsetX + m::CellNumX * m::CellSize;
        y = m::OffsetY + cell.y() * m::CellSize;
        width = m::OffsetX;
    }
    else if (cell.y() == 0)
    {
        x = m::OffsetX + cell.x() * m::CellSize;
        y = 0;
    }
    else if (cell.y() == m::CellNumY - 1)
    {
        x = m::OffsetX + (cell.x() + 1) * m::CellSize;
        y = m::OffsetY + m::CellNumY * m::CellSize;
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
    QRectF start = get_cell_left_top_(m::startCell, game);    
    QPoint startCell = get_border_cell_(m::startCell, game);
    cells[m::startCell.x()][m::startCell.y()] = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.2,
                start.topLeft(), start.size(),
                game->r->cell1, game);
    
    //end cell
    QRectF end = get_cell_left_top_(m::endCell, game);
    QPoint endCell = get_border_cell_(m::endCell, game);
    cells[endCell.x()][endCell.y()] = std::make_shared<CSceneObject>(
                0, m::BackgroundZOrder + 0.2,
                end.topLeft(), end.size(),
                game->r->cell2, game);
    
    //game cells
    for (int i = 1; i < m::CellNumX - 1; ++i)
        for (int j = 1; j < m::CellNumY - 1; ++j)
        {
            int x = m::OffsetX + i * m::CellSize;
            int y = m::OffsetY + j * m::CellSize;
            std::shared_ptr<QPixmap> cellPixmap = ((i + j) % 2 == 0) ? game->r->cell1 : game->r->cell2;
            cells[i][j] = std::make_shared<CSceneObject>(
                        0, m::BackgroundZOrder + 0.2,
                        QPointF(x, y), QSizeF(m::CellSize, m::CellSize),
                        cellPixmap, game);
        }
    
    
    //border cells
    for (int i = 1; i < m::CellNumX + 1; ++i)
    {
        if (!cells[i][0])
            cells[i][0] = std::make_shared<CSceneObject>(
                        0, m::BackgroundZOrder + 0.2,
                        QPointF(m::OffsetX + (i - 1) * m::CellSize, 0),
                        QSizeF(m::CellSize, m::OffsetY),
                        game->r->border_cell, game);
        
        int indY = m::CellNumY + 1;
        if (!cells[i][indY])
            cells[i][indY] = std::make_shared<CSceneObject>(
                        0, m::BackgroundZOrder + 0.2,
                        QPointF(m::OffsetX + (i - 1) * m::CellSize, 
                                m::OffsetY + (indY - 1) * m::CellSize),
                        QSizeF(m::CellSize, m::OffsetY),
                        game->r->border_cell, game);
    }
    
    for (int j = 0; j < m::CellNumY + 2; ++j)
    {
        if (!cells[0][j])
            cells[0][j] = std::make_shared<CSceneObject>(
                        0, m::BackgroundZOrder + 0.2,
                        QPointF(0, j * m::CellSize),
                        QSizeF(m::OffsetX, m::CellSize),
                        game->r->border_cell, game);
        
        int indX = m::CellNumX + 1;
        if (!cells[indX][j])
            cells[indX][j] = std::make_shared<CSceneObject>(
                        0, m::BackgroundZOrder + 0.2,
                        QPointF(m::OffsetX + (indX - 1) * m::CellSize, j * m::CellSize),
                        QSizeF(m::OffsetX, m::CellSize),
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
