#include <Game/Scene.h>

//public:
Scene::Scene(R* r) : r(r)
{
    graphicsScene = new QGraphicsScene();
}

QGraphicsItem* Scene::drawPixmap(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, QPixmap pixmap)
{
    QPixmap scaledPixmap = pixmap.scaled(toGlobalCX(xSizeLocal), toGlobalCY(ySizeLocal));
    QGraphicsPixmapItem *item = graphicsScene->addPixmap(scaledPixmap);
    item->setPos(toGlobalX(xLocal), toGlobalY(yLocal));
    return item;
}

void Scene::positionItem(int xLocal, int yLocal, QGraphicsItem *item)
{
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
}

void Scene::updateWindowBackground()
{
    QPixmap scaledPixmap = r->window_background.scaled(windowRect.size());
    graphicsScene->addPixmap(scaledPixmap);
}

void Scene::updateGameBackground()
{
    //update background
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
    return 1.0 * gameRect.width() * cxLocal / LocalWidth;
}

int Scene::toGlobalCY(int cyLocal)
{
    return 1.0 * gameRect.height() * cyLocal / LocalHeight;
}
