#include <Game/Scene.h>

//public:
CScene::CScene(R* r) : r(r), fpsItem(nullptr), tpsItem(nullptr)
{
    graphicsScene = new QGraphicsScene();
    graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);

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
    item->setFlag(QGraphicsItem::ItemHasNoContents, true);
    item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
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
}

void CScene::positionItemByCenter(const QPointF &centerLocal, const QSizeF &sizeLocal,
                                  qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item)
{
    int sizeXGlobal = toGlobalCX(sizeLocal.width());
    int sizeYGlobal = toGlobalCY(sizeLocal.height());
    item->setTransformOriginPoint(sizeXGlobal / 2, sizeYGlobal / 2);
    item->setRotation(angle);
    
    QRectF boundRect = item->boundingRect();
    qreal left = toGlobalX(centerLocal.x()) - boundRect.width() / 2;
    qreal top = toGlobalY(centerLocal.y()) - boundRect.height() / 2;
    item->setPos(left, top);
    item->setZValue(zval);
}

void CScene::removeItem(std::shared_ptr<QGraphicsItem> item)
{
    item->setEnabled(false);
    //graphicsScene->removeItem(item.get());
}

std::shared_ptr<QGraphicsItem> CScene::drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal,
                            QPixmap *pixmap, qreal angle /*=0*/, qreal zval/*=0*/)
{
    int sizeX = toGlobalCX(xSizeLocal);
    int sizeY = toGlobalCY(ySizeLocal);
    QPixmap scaledPixmap = *pixmap;
    if (pixmap->size() != QSize(sizeX, sizeY))
        scaledPixmap = pixmap->scaled(sizeX, sizeY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(scaledPixmap));
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
    item->setDefaultTextColor(Qt::red);
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
    backgroundItems.clear();
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
            {
                drawAndPosition(x, y, CellSize, CellSize, &(r->cell1));
            }
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

void CScene::updateFPS(int fps, int tps)
{
#ifdef SHOW_FPS
    
    if (fpsItem)
        graphicsScene->removeItem(fpsItem.get());
    if (tpsItem)
        graphicsScene->removeItem(tpsItem.get());
    
    fpsItem = std::shared_ptr<QGraphicsTextItem>(graphicsScene->addText(QString::number((int)fps) + " FPS"));
    fpsItem->setPos(toGlobalX(10), toGlobalY(10));
    fpsItem->setDefaultTextColor(Qt::red);
    fpsItem->setZValue(10);
    
    tpsItem = std::shared_ptr<QGraphicsTextItem>(graphicsScene->addText(QString::number((int)tps) + " TPS"));
    tpsItem->setPos(gameRect.width() - 45, toGlobalY(10));
    tpsItem->setDefaultTextColor(Qt::red);
    tpsItem->setZValue(10);
#endif
}

void CScene::updateItems()
{
    graphicsScene->update(gameRect);    
}

//private:
qreal CScene::toGlobalX(qreal xLocal)
{
    return gameRect.left()
            + 1.0 * gameRect.width() * xLocal / LocalWidth;
}

qreal CScene::toGlobalY(qreal yLocal)
{
    return gameRect.top()
            + 1.0 * gameRect.height() * yLocal / LocalHeight;
}

qreal CScene::toGlobalCX(qreal cxLocal)
{
    return 1.0 * gameRect.width() * cxLocal / LocalWidth;
}

qreal CScene::toGlobalCY(qreal cyLocal)
{
    return 1.0 * gameRect.height() * cyLocal / LocalHeight;
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
