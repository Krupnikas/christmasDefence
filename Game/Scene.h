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
    void positionItemByCenter(const QPointF &centerLocal, const QSizeF &sizeLocal, 
                      qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item);
    void removeItem(std::shared_ptr<QGraphicsItem> item);
    
    std::shared_ptr<QGraphicsItem> drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal,
                         QPixmap *pixmap, qreal angle = 0, qreal zval = 0);
    std::shared_ptr<QGraphicsItem> drawAndPosition(int xLocal, int yLocal, const QString &text, qreal zval = 0);

    
    void updateGameRect(QRect geometry);
    void updateWindowBackground();
    void updateGameBackground();
    void updateDistances(std::vector<std::vector<int>> &distances);
    
    int getWidth() { return gameRect.width(); }
    int getHeight() { return gameRect.height(); }
    QGraphicsScene *getGraphicsScene() { return graphicsScene; }
    
    int toGlobalX(qreal x_local);
    int toGlobalY(qreal y_local);
    int toGlobalCX(qreal cx_local);
    int toGlobalCY(qreal cy_local);

    qreal toLocalX(qreal xGlobal);
    qreal toLocalY(qreal yGlobal);    
    qreal toLocalCX(qreal cxGlobal);
    qreal toLocalCY(qreal cyGlobal);

    QPointF toLocalPoint(QPointF globalPoint);
    
    bool insideGameRect(QPointF point);

private:
    
    R* r;
    QRect gameRect; //Прямоугольник рабочей области
    QRect windowRect; //Whole window rectangle
    QRect enclosingRect;
    QGraphicsScene *graphicsScene;
    QPainter painter;
    
    std::vector<std::shared_ptr<QGraphicsItem>> backgroundItems;
    std::vector<std::shared_ptr<QGraphicsItem>> textItems;
    
    
private slots:
    void scalePixmap(qreal scale, QSizeF sizeGlobal, QPixmap *pixmap);
};
