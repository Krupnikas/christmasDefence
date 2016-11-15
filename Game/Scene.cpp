#include <Game/Scene.h>

//public:
Scene::Scene(R* r) : r(r)
{
    graphicsScene = new QGraphicsScene();
}

QGraphicsItem* Scene::drawPixmap(int xSizeLocal, int ySizeLocal, QPixmap &pixmap)
{
    int sizeX = toGlobalCX(xSizeLocal);
    int sizeY = toGlobalCY(ySizeLocal);
    
    if (pixmap.size() != QSize(sizeX, sizeY))
        pixmap = pixmap.scaled(sizeX, sizeY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);      
    QGraphicsPixmapItem *item = graphicsScene->addPixmap(pixmap);
    return item;
}

void Scene::positionItem(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, 
                         qreal angle, QGraphicsItem *item)
{
    int sizeX = toGlobalCX(xSizeLocal);
    int sizeY = toGlobalCY(ySizeLocal);
    item->setTransformOriginPoint(sizeX / 2, sizeY / 2);
    item->setRotation(angle);
    item->setPos(toGlobalX(xLocal), toGlobalY(yLocal));
}

void Scene::drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, 
                            QPixmap &pixmap, qreal angle /*= 0*/)
{
    int sizeX = toGlobalCX(xSizeLocal);
    int sizeY = toGlobalCY(ySizeLocal);
    if (pixmap.size() != QSize(sizeX, sizeY))
        pixmap = pixmap.scaled(sizeX, sizeY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    QGraphicsPixmapItem *item = graphicsScene->addPixmap(pixmap);
    if (angle != 0)
    {
        item->setTransformOriginPoint(sizeX / 2, sizeY / 2);
        item->setRotation(angle);
    }
    item->setPos(toGlobalX(xLocal), toGlobalY(yLocal));
}

void Scene::updateGameRect(QRect newWindowRect)
{
    //Если экран шире, чем 16х9
    //Устанавливаем новую ширину
    //Иначе экран выше, чем 16х9
    //Устанавливаем новую высоту
    gameRect = windowRect = newWindowRect;
    QPoint center = newWindowRect.center();
    
    if (newWindowRect.width() * 9 > newWindowRect.height() * 16)
    {
        int newWidth = gameRect.height() * 16.0 / 9;
        gameRect.setLeft(center.x() - newWidth / 2.0);
        gameRect.setWidth(newWidth);
    }
    else
    {
        int newHeight = newWindowRect.width() * 9.0 / 16;
        gameRect.setTop(center.y() - newHeight / 2.0);
        gameRect.setHeight(newHeight);
    }
    
    updateWindowBackground();
    updateGameBackground();
}

void Scene::updateWindowBackground()
{
    QPixmap scaledPixmap = r->window_background.scaled(windowRect.size(),
                                                       Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    graphicsScene->addPixmap(scaledPixmap);
}

void Scene::updateGameBackground()
{
    drawAndPosition(0, 0, LocalWidth, CellNumY * CellSize, r->game_background);
    
    //draw chess-like field 
    bool first_white = true;
    bool white;
    for (int i = 0; i < CellNumX; ++i)
    {
        white = first_white;
        first_white = !first_white;
    
        for (int j = 0; j < CellNumY; ++j)
        {
            int x = OffsetX + i * CellSize;
            int y = j * CellSize;
            if (white)
                drawAndPosition(x, y, CellSize, CellSize, r->cell1);
            else
                drawAndPosition(x, y, CellSize, CellSize, r->cell2);
            white = !white;
        }
    }
    
    //draw path inside and outside the field
    int y = (CellNumY / 2) * CellSize;
    int xLeft = 0;
    int xRight = OffsetX + CellNumX * CellSize;
    
    drawAndPosition(xLeft, y, OffsetX, CellSize, r->cell2);
    if (CellNumX % 2)
        drawAndPosition(xRight, y, OffsetX, CellSize, r->cell2);
    else
        drawAndPosition(xRight, y, OffsetX, CellSize, r->cell1);
}

//private:
int Scene::toGlobalX(int xLocal)
{
    return gameRect.left()
            + static_cast<int>(1.0 * gameRect.width() * xLocal / LocalWidth);
}

int Scene::toGlobalY(int yLocal)
{
    return gameRect.top()
            + static_cast<int>(1.0 * gameRect.height() * yLocal / LocalHeight);
}

int Scene::toGlobalCX(int cxLocal)
{
    return std::ceil(1.0 * gameRect.width() * cxLocal / LocalWidth);
}

int Scene::toGlobalCY(int cyLocal)
{
    return std::ceil(1.0 * gameRect.height() * cyLocal / LocalHeight);
}
