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
    
    QGraphicsItem *drawPixmap(int xSizeLocal, int ySizeLocal, QPixmap &pixmap);
    
    void positionItem(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, 
                      qreal angle, qreal zval, QGraphicsItem *item);
    
    void drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, 
                         QPixmap &pixmap, qreal angle = 0, qreal zval = 0);
    

    void updateGameRect(QRect geometry);
    void updateWindowBackground();
    void updateGameBackground();
    
    int getWidth() { return gameRect.width(); }
    int getHeight() { return gameRect.height(); }
    QGraphicsScene *getGraphicsScene() { return graphicsScene; }
    
    int toGlobalX(int x_local);
    int toGlobalY(int y_local);
    int toGlobalCX(int cx_local);
    int toGlobalCY(int cy_local);
    
    bool insideGameRect(QPointF point);
    
private:
    
    R* r;
    QRect gameRect; //Прямоугольник рабочей области
    QRect windowRect; //Whole window rectangle
    QRect enclosingRect;
    QGraphicsScene *graphicsScene;
    QPainter painter;
    
};

#endif // SCENE_H
