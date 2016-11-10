#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <Game/resource.h>


class Scene
{
public:
    
    static const int LOCAL_WIDTH = 1600;
    static const int LOCAL_HEIGHT = 900;
    
    enum DrawType {
        BACKGROUND, CANNON, ENEMY, BULLET
    };
    
    Scene();
    
    QGraphicsItem *drawPixmap(int x_local, int y_local, int x_size_local, int y_size_local, QPixmap pixmap);
    void positionItem(int x_local, int y_local, QGraphicsItem *item);
    
    void calculateWorkingRectangle(QRect geometry);
    
    int getWidth() { return workingRectangle.width(); }
    int getHeight() { return workingRectangle.height(); }
    QGraphicsScene *getGraphicsScene() { return graphicsScene; }
    
private:
    
    int toGlobalX(int x_local);
    int toGlobalY(int y_local);
    

    
    QRect workingRectangle;               //Прямоугольник рабочей области
    QGraphicsScene *graphicsScene;
    
};

#endif // SCENE_H
