#pragma once

//#define SHOW_DISTANCES
#include <Game/Scene.h>

class IBullet;
class IEnemy;
class ICannon;
class MainView;
class CCannonSelection;

class CGame : public QObject
{
    Q_OBJECT
    
//public attributes
public:
    R *r;
    CScene *scene;
    QWidget *view;
    QTimer *positionTimer;
    QTimer *drawTimer;
    std::shared_ptr<CCannonSelection> block;
    std::shared_ptr<QGraphicsItem> selectedCellItem;
    QPoint selectedCell = QPoint(-1, -1);
    QPoint hintedCell = QPoint(0, 0);

    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::shared_ptr<IEnemy> > enemies;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//private attributes
private:
    qreal fps = 0;
    qreal tps = 0;
    
    
//public methods
public:
    CGame(R *r, CScene *scene, QWidget *view);
    ~CGame();
    
    bool addCannon(std::shared_ptr<ICannon> cannon);
    bool addEnemy(std::shared_ptr<IEnemy> enemy);
    
    QPointF cellLeftTop(QPoint cell);
    QPointF cellCenter(QPoint cell);
    
    void updateDistances();
    void scaleObjects();
    
    void hideObjects();
    void showObjects();

    void selectCell(QPoint pos);
    void selectCell(int i, int j);
    void deselectCell();

    QPoint findNearestCell(QPointF from);

public slots:
    virtual void onPositionTimer();
    virtual void onDrawTimer();
    
};
