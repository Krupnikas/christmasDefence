#include "Scene.h"

//public:
Scene::Scene()
{
    graphicsScene = new QGraphicsScene();
}

QGraphicsItem *Scene::drawPixmap(int x_local, int y_local, int x_size_local, int y_size_local, QPixmap pixmap)
{
    QPixmap scaled_pixmap = pixmap.scaled(toGlobalX(x_size_local), toGlobalY(y_size_local));
    QGraphicsPixmapItem *item = graphicsScene->addPixmap(scaled_pixmap);
    item->setPos(toGlobalX(x_local), toGlobalY(y_local));
    return item;
}

void Scene::positionItem(int x_local, int y_local, QGraphicsItem *item)
{
    item->setPos(toGlobalX(x_local), toGlobalY(y_local));
}

void Scene::calculateWorkingRectangle(QRect geometry)
{
    //Если экран шире, чем 16х9
    //Устанавливаем новую ширину
    //Иначе экран выше, чем 16х9
    //Устанавливаем новую высоту
    workingRectangle = geometry;
    if (geometry.width() * 9 > geometry.height() * 16)      
        workingRectangle.setWidth(geometry.height() * 16.0 / 9);                                  
    else                                                                        
        workingRectangle.setHeight(geometry.width() * 9.0 / 16);                                
}

//private:
int Scene::toGlobalX(int x_local)
{
    return workingRectangle.left()
            + workingRectangle.width() * x_local / LOCAL_WIDTH;
}

int Scene::toGlobalY(int y_local)
{
    return workingRectangle.top()
            + workingRectangle.height() * y_local / LOCAL_HEIGHT;
}
