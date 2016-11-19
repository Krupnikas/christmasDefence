#pragma once

#include <Game/Resource.h>

class CScene
{
public:
    
    enum DrawType {
        BACKGROUND, CANNON, ENEMY, BULLET
    };
    
    CScene(R* r);
    
    std::shared_ptr<QGraphicsItem> addPixmap(const QSizeF &sizeLocal, QPixmap *pixmap);
    
    void positionItem(const QPointF &leftTopLocal, const QSizeF &sizeLocal, 
                      qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item);
    void removeItem(std::shared_ptr<QGraphicsItem> item);
    
    void drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal, 
                         QPixmap *pixmap, qreal angle = 0, qreal zval = 0);
    

    qreal updateGameRect(QRect geometry);
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
