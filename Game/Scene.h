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
    std::shared_ptr<QGraphicsItem> addEllipse(const QPointF &centerLocal, const QSizeF &sizeLocal);
    
    void positionItem(const QPointF &leftTopLocal, const QSizeF &sizeLocal, 
                      qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item);
    void positionItemByCenter(const QPointF &centerLocal, const QSizeF &sizeLocal, 
                      qreal angle, qreal zval, std::shared_ptr<QGraphicsItem> item);
    void removeItem(std::shared_ptr<QGraphicsItem> item);
    void scaleItem(QSizeF originSizeLocal, QSizeF resultSizeLocal,
                   std::shared_ptr<QGraphicsItem> item);
    
    std::shared_ptr<QGraphicsItem> drawAndPosition(int xLocal, int yLocal, int xSizeLocal, int ySizeLocal,
                         QPixmap *pixmap, qreal angle = 0, qreal zval = 0);
    std::shared_ptr<QGraphicsItem> drawAndPosition(int xLocal, int yLocal, const QString &text, qreal zval = 0);

    
    void updateGameRect(QRect geometry);

    void updateGameMenuBackground();
    void updateLevelMenuBackground();
    void updateGameBackground();

    void updateDistances(std::vector<std::vector<int>> &distances);
    void updateFPS(int fps);
    void updateWaveInfo(QString info);
    void updateUserInfo(int cash, int hp);
    void updateItems();
    
    int getWidth() { return gameRect.width(); }
    int getHeight() { return gameRect.height(); }
    QGraphicsScene *getGraphicsScene() { return graphicsScene; }
    
    qreal toGlobalX(qreal x_local);
    qreal toGlobalY(qreal y_local);
    qreal toGlobalCX(qreal cx_local);
    qreal toGlobalCY(qreal cy_local);
    qreal toGlobalDist(qreal distLocal, qreal angle);
    QPointF toGlobalPoint(QPointF localPoint);
    QPointF toGlobalSize(QPointF localSize);
    QSizeF toGlobalSize(QSizeF localSize);

    qreal toLocalX(qreal xGlobal);
    qreal toLocalY(qreal yGlobal);    
    qreal toLocalCX(qreal cxGlobal);
    qreal toLocalCY(qreal cyGlobal);

    QPointF toLocalPoint(QPointF globalPoint);
    
    bool insideEnclosingRect(QPointF point);
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
    std::shared_ptr<QGraphicsTextItem> fpsItem;
    std::shared_ptr<QGraphicsTextItem> waveInfoItem;
    std::shared_ptr<QGraphicsTextItem> userCashItem;
    std::shared_ptr<QGraphicsTextItem> userHpItem;

    
};
