#ifndef SCENE_H
#define SCENE_H

#include <Game/Resource.h>

class Scene
{
public:
    
    enum DrawType {
        BACKGROUND, CANNON, ENEMY, BULLET
    };
    
    Scene(R* r);
    
    QGraphicsItem *drawPixmap(int x_local, int y_local, int x_size_local, int y_size_local, QPixmap pixmap, int angle = 0);
    void positionItem(int x_local, int y_local, QGraphicsItem *item);
    
    void updateGameRect(QRect geometry);
    
    void updateWindowBackground();
    void updateGameBackground();
    
    int getWidth() { return gameRect.width(); }
    int getHeight() { return gameRect.height(); }
    QGraphicsScene *getGraphicsScene() { return graphicsScene; }
    
private:
    
    int toGlobalX(int x_local);
    int toGlobalY(int y_local);
    int toGlobalCX(int cx_local);
    int toGlobalCY(int cy_local);
        
    
    R* r;
    QRect gameRect; //Прямоугольник рабочей области
    QRect windowRect; //Whole window rectangle
    QGraphicsScene *graphicsScene;
    QPainter painter;
    
};

#endif // SCENE_H
