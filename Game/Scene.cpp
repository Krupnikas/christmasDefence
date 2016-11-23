#include <Game/Scene.h>

//public:
CScene::CScene(R* r) : r(r)
{
    graphicsScene = new QGraphicsScene();
}

std::shared_ptr<QGraphicsItem> CScene::addPixmap(const QSizeF &sizeLocal, QPixmap *pixmap)
{
    int sizeXGlobal = toGlobalCX(sizeLocal.width());
    int sizeYGlobal = toGlobalCY(sizeLocal.height());
    
    QPixmap scaledPixmap = *pixmap;
    if (pixmap->size() != QSize(sizeXGlobal, sizeYGlobal))
        scaledPixmap = pixmap->scaled(sizeXGlobal, sizeYGlobal, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(scaledPixmap));
    item->hide();
    return item;
}

void CScene::positionItem(const QPointF &leftTopLocal, const QSizeF &sizeLocal, 
                          qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item)
{
    int sizeXGlobal = toGlobalCX(sizeLocal.width());
    int sizeYGlobal = toGlobalCY(sizeLocal.height());
    item->setTransformOriginPoint(sizeXGlobal / 2, sizeYGlobal / 2);
    item->setRotation(angle);
    item->setPos(toGlobalX(leftTopLocal.x()), toGlobalY(leftTopLocal.y()));
    item->setZValue(zval);
    item->show();
}

void CScene::removeItem(std::shared_ptr<QGraphicsItem> item)
{
    graphicsScene->removeItem(item.get());
}

std::shared_ptr<QGraphicsItem> CScene::drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal,
                            QPixmap *pixmap, qreal angle /*=0*/, qreal zval/*=0*/)
{
    int sizeX = toGlobalCX(xSizeLocal);
    int sizeY = toGlobalCY(ySizeLocal);
    if (pixmap->size() != QSize(sizeX, sizeY))
        *pixmap = pixmap->scaled(sizeX, sizeY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(*pixmap));
    backgroundItems.push_back(item);
    
    if (angle != 0)
    {
        item->setTransformOriginPoint(sizeX / 2, sizeY / 2);
        item->setRotation(angle);
    }
    item->setPos(toGlobalX(xLocal), toGlobalY(yLocal));
    item->setZValue(zval);
    return item;
}

std::shared_ptr<QGraphicsItem> CScene::drawAndPosition(int xLocal, int yLocal, const QString &text, qreal zval)
{
    std::shared_ptr<QGraphicsTextItem> item(graphicsScene->addText(text));
    textItems.push_back(item);
    item->setPos(toGlobalX(xLocal), toGlobalY(yLocal));
    item->setZValue(zval);
    return item;
}

void CScene::updateGameRect(QRect newWindowRect)
{
    //Если экран шире, чем 16х9
    //Устанавливаем новую ширину
    //Иначе экран выше, чем 16х9
    //Устанавливаем новую высоту
    backgroundItems.clear(); /////////////////////////////////////////PROBLEM! NOT DELETING BUT LOOSE POINTERS!
    gameRect = windowRect = newWindowRect;
    
    QPoint enclosingTopLeft(gameRect.topLeft() - QPoint(CellSize, CellSize));
    QPoint enclosingBottomRight(gameRect.bottomRight() + QPoint(CellSize, CellSize));
    enclosingRect = QRect(enclosingTopLeft, enclosingBottomRight);
    
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

void CScene::updateWindowBackground()
{
    QPixmap scaledPixmap = r->window_background.scaled(windowRect.size(),
                                                       Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(scaledPixmap));
    backgroundItems.push_back(item);
    item->setZValue(0);
}

void CScene::updateGameBackground()
{
    drawAndPosition(0, 0, LocalWidth, LocalHeight, &r->game_background);
    
    //draw chess-like field
    for (int i = 0; i < CellNumX; ++i)
    {
        for (int j = 0; j < CellNumY; ++j)
        {
            int x = OffsetX + i * CellSize;
            int y = OffsetY + j * CellSize;
            if ((i+j)%2 == 0)
                drawAndPosition(x, y, CellSize, CellSize, &(r->cell1));
            else
                drawAndPosition(x, y, CellSize, CellSize, &(r->cell2));
        }
    }
    
    //draw path inside and outside the field
    int y = (CellNumY / 2) * CellSize + OffsetY;
    int xLeft = 0;
    int xRight = OffsetX + CellNumX * CellSize;
    
    drawAndPosition(xLeft, y, OffsetX, CellSize, &r->cell1);
    if (CellNumX % 2)
        drawAndPosition(xRight, y, OffsetX, CellSize, &r->cell1);
    else
        drawAndPosition(xRight, y, OffsetX, CellSize, &r->cell2);
}

void CScene::updateDistances(std::vector<std::vector<int>> &distances)
{
#ifdef SHOW_DISTANCES
    textItems.clear();
    if (DrawText)
        for (int i = 0; i < CellNumX; ++i)
            for (int j = 0; j < CellNumY; ++j)
            {
                int x = OffsetX + i * CellSize;
                int y = OffsetY + j * CellSize;
                QString text = QString::number(distances[i][j]);
                drawAndPosition(x, y, text, 0.5);
            }
#endif
}

//private:
int CScene::toGlobalX(qreal xLocal)
{
    return gameRect.left()
            + static_cast<int>(1.0 * gameRect.width() * xLocal / LocalWidth);
}

int CScene::toGlobalY(qreal yLocal)
{
    return gameRect.top()
            + static_cast<int>(1.0 * gameRect.height() * yLocal / LocalHeight);
}

int CScene::toGlobalCX(qreal cxLocal)
{
    return std::ceil(1.0 * gameRect.width() * cxLocal / LocalWidth);
}

int CScene::toGlobalCY(qreal cyLocal)
{
    return std::ceil(1.0 * gameRect.height() * cyLocal / LocalHeight);
}

qreal CScene::toLocalX(qreal xGlobal)
{
    return (xGlobal - gameRect.left()) * LocalWidth / gameRect.width();
}

qreal CScene::toLocalY(qreal yGlobal)
{
    return (yGlobal - gameRect.top()) * LocalHeight/ gameRect.height();
}

qreal CScene::toLocalCX(qreal cxGlobal)
{
    return cxGlobal * LocalWidth / gameRect.width();
}

qreal CScene::toLocalCY(qreal cyGlobal)
{
    return cyGlobal * LocalHeight / gameRect.height();
}

QPointF CScene::toLocalPoint(QPointF globalPoint)
{
    return QPointF(toLocalX(globalPoint.x()),
                   toLocalY(globalPoint.y()));
}

bool CScene::insideGameRect(QPointF point)
{
    int x = toGlobalX(point.x());
    int y = toGlobalY(point.y());
    QPoint pointInt(x, y);
    return enclosingRect.contains(pointInt);
}
