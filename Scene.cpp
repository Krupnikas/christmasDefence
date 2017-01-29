#include <Scene.h>

//public:
CScene::CScene(R* r) : r(r), fpsItem(nullptr), waveInfoItem(nullptr)
{
    graphicsScene = new QGraphicsScene();
    graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);
}

std::shared_ptr<QGraphicsItem> CScene::addPixmap(const QSizeF &sizeLocal, std::shared_ptr<QPixmap> pixmap)
{
    qreal sizeXGlobal = toGlobalCX(sizeLocal.width());
    qreal sizeYGlobal = toGlobalCY(sizeLocal.height());
    
    std::shared_ptr<QPixmap> scaledPixmap = pixmap;
    if (pixmap->size() != QSize(sizeXGlobal, sizeYGlobal))
        scaledPixmap = std::make_shared<QPixmap>(
                    pixmap->scaled(sizeXGlobal, sizeYGlobal, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(*scaledPixmap));
    item->hide();
    item->setFlag(QGraphicsItem::ItemHasNoContents, true);
    //item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    return item;
}

std::shared_ptr<QGraphicsItem> CScene::addBackgroundPixmap(std::shared_ptr<QPixmap> pixmap)
{
    qreal sizeX = windowRect.width();
    qreal sizeY = windowRect.height();

    std::shared_ptr<QPixmap> scaledPixmap = pixmap;
    if (pixmap->size() != QSize(sizeX, sizeY))
        scaledPixmap = std::make_shared<QPixmap>(
                    pixmap->scaled(sizeX, sizeY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    std::shared_ptr<QGraphicsPixmapItem> item(graphicsScene->addPixmap(*scaledPixmap));
    item->hide();
    item->setFlag(QGraphicsItem::ItemHasNoContents, true);
//    item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    return item;
}

std::shared_ptr<QGraphicsItem> CScene::addEllipse(const QPointF &centerLocal, const QSizeF &sizeLocal)
{
    qreal sizeXGlobal = toGlobalCX(sizeLocal.width());
    qreal sizeYGlobal = toGlobalCY(sizeLocal.height());
    QPointF centerGlobal = toGlobalPoint(centerLocal);
    qreal leftTopX = centerGlobal.x() - sizeXGlobal / 2;
    qreal leftTopY = centerGlobal.y() - sizeYGlobal / 2;
    
    std::shared_ptr<QGraphicsItem> item(
                graphicsScene->addEllipse(0, 0, sizeXGlobal, sizeYGlobal));
    item->setPos(leftTopX, leftTopY);
    item->hide();
    //item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    return item;
}

void CScene::positionItem(const QPointF &leftTopLocal, const QSizeF &sizeLocal, 
                          qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item)
{
    qreal sizeXGlobal = toGlobalCX(sizeLocal.width());
    qreal sizeYGlobal = toGlobalCY(sizeLocal.height());
    
    QPointF curPos = item->pos();
    QPointF newPos = QPointF(toGlobalX(leftTopLocal.x()), toGlobalY(leftTopLocal.y()));
    if (curPos != newPos)
        item->setPos(newPos);
    
    if (angle != item->rotation())
    {
        item->setTransformOriginPoint(sizeXGlobal / 2, sizeYGlobal / 2);
        item->setRotation(angle);
    }
    if (zval != item->zValue())
        item->setZValue(zval);
}

void CScene::positionItemByCenter(const QPointF &centerLocal, const QSizeF &sizeLocal,
                                  qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item)
{
    qreal left = centerLocal.x() - sizeLocal.width() / 2;
    qreal top = centerLocal.y() - sizeLocal.height() / 2;
    positionItem(QPointF(left, top), sizeLocal, angle, zval, item);
}

void CScene::removeItem(std::shared_ptr<QGraphicsItem> item)
{
    graphicsScene->removeItem(item.get());
}

void CScene::scaleItem(QSizeF originSizeLocal, QSizeF resultSizeLocal,
                       std::shared_ptr<QGraphicsItem> item)
{
    QSizeF originSizeGlobal(toGlobalSize(originSizeLocal));
    QSizeF resultSizeGlobal(toGlobalSize(resultSizeLocal));
    QTransform transform = QTransform().scale(resultSizeGlobal.width() / originSizeGlobal.width(),
                                              resultSizeGlobal.height() / originSizeGlobal.height());
    item->setTransform(transform);
}

void CScene::updateGameRect(QRect newWindowRect)
{
    //Если экран шире, чем 16х9
    //Устанавливаем новую ширину
    //Иначе экран выше, чем 16х9
    //Устанавливаем новую высоту
    //qDebug() << "New window rect: " << newWindowRect;
    backgroundItems.clear();
    gameRect = windowRect = newWindowRect;
    
    
    QPoint enclosingTopLeft(gameRect.topLeft() - QPoint(m::LocalWidth / 20, m::LocalHeight / 20));
    QPoint enclosingBottomRight(gameRect.bottomRight() + QPoint(m::LocalWidth / 20, m::LocalHeight / 20));
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
}

void CScene::updateDistances(std::vector<std::vector<int>>&)
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

void CScene::updateWaveInfo(QString info)
{
    if (waveInfoItem)
        graphicsScene->removeItem(waveInfoItem.get());

    waveInfoItem = std::shared_ptr<QGraphicsTextItem>(graphicsScene->addText(info));
    waveInfoItem->setPos(gameRect.width() - info.size() * 6 - toGlobalX(50), toGlobalY(10));
    waveInfoItem->setDefaultTextColor(Qt::red);
    waveInfoItem->setZValue(10);
}

void CScene::removeWaveInfo()
{
    if (waveInfoItem)
    {
        graphicsScene->removeItem(waveInfoItem.get());
        waveInfoItem = nullptr;
    }
}

void CScene::updateFPS(int fps, int tps)
{
#ifdef SHOW_FPS
    if (fpsItem)
        graphicsScene->removeItem(fpsItem.get());
    
    fpsItem = std::shared_ptr<QGraphicsTextItem>(graphicsScene->addText(QString::number((int)fps) + " FPS"));
    fpsItem->setPos(toGlobalX(10), toGlobalY(10));
    fpsItem->setDefaultTextColor(Qt::red);
    fpsItem->setZValue(10);
    
    if (tpsItem)
        graphicsScene->removeItem(tpsItem.get());
    
    tpsItem = std::shared_ptr<QGraphicsTextItem>(graphicsScene->addText(QString::number((int)tps) + " TPS"));
    tpsItem->setPos(toGlobalX(m::LocalWidth - m::CellSize * 2), toGlobalY(10));
    tpsItem->setDefaultTextColor(Qt::red);
    tpsItem->setZValue(10);
#endif
}

void CScene::removeFPS()
{
    if (fpsItem)
    {
        graphicsScene->removeItem(fpsItem.get());
        fpsItem = nullptr;
    }
}

void CScene::updateItems()
{
    graphicsScene->update(gameRect);    
}

//private:
qreal CScene::toGlobalX(qreal xLocal)
{
    return gameRect.left()
            + 1.0 * gameRect.width() * xLocal / m::LocalWidth;
}

qreal CScene::toGlobalY(qreal yLocal)
{
    return gameRect.top()
            + 1.0 * gameRect.height() * yLocal / m::LocalHeight;
}

qreal CScene::toGlobalCX(qreal cxLocal)
{
    return 1.0 * gameRect.width() * cxLocal / m::LocalWidth;
}

qreal CScene::toGlobalCY(qreal cyLocal)
{
    return 1.0 * gameRect.height() * cyLocal / m::LocalHeight;
}

qreal CScene::toGlobalDist(qreal distLocal, qreal angle)
{
    qreal angleRad(qDegreesToRadians(angle));
    
    qreal dx = distLocal * sin(angleRad);
    qreal dy = distLocal * cos(angleRad);
    
    qreal dxGlobal(toGlobalCX(dx));
    qreal dyGlobal(toGlobalCY(dy));
    return sqrt(dxGlobal * dxGlobal + dyGlobal * dyGlobal);
}


QPointF CScene::toGlobalPoint(QPointF localPoint)
{
    return QPointF(toGlobalX(localPoint.x()), toGlobalY(localPoint.y()));
}

QPointF CScene::toGlobalSize(QPointF localSize)
{
    return QPointF(toGlobalCX(localSize.x()), toGlobalCY(localSize.y()));
}

QSizeF CScene::toGlobalSize(QSizeF localSize)
{
    return QSizeF(toGlobalCX(localSize.width()), toGlobalCY(localSize.height()));
}

qreal CScene::toLocalX(qreal xGlobal)
{
    return (xGlobal - gameRect.left()) * m::LocalWidth / gameRect.width();
}

qreal CScene::toLocalY(qreal yGlobal)
{
    return (yGlobal - gameRect.top()) * m::LocalHeight/ gameRect.height();
}

qreal CScene::toLocalCX(qreal cxGlobal)
{
    return cxGlobal * m::LocalWidth / gameRect.width();
}

qreal CScene::toLocalCY(qreal cyGlobal)
{
    return cyGlobal * m::LocalHeight / gameRect.height();
}

QPointF CScene::toLocalPoint(QPointF globalPoint)
{
    return QPointF(toLocalX(globalPoint.x()),
                   toLocalY(globalPoint.y()));
}

bool CScene::insideEnclosingRect(QPointF point)
{
    int x = toGlobalX(point.x());
    int y = toGlobalY(point.y());
    QPoint pointInt(x, y);
    return enclosingRect.contains(pointInt);
}

bool CScene::insideGameRect(QPointF point)
{
    int x = toGlobalX(point.x());
    int y = toGlobalY(point.y());
    QPoint pointInt(x, y);
    return gameRect.contains(pointInt);
}

QRect CScene::getGameRect() const
{
    return gameRect;
}

