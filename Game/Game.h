#pragma once

#include <Game/Scene.h>

class ICannon;
class IBullet;
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
    QTimer *gameTimer;
    std::shared_ptr<CCannonSelection> block;
    std::shared_ptr<QGraphicsItem> selectedCellItem;
    QPoint selectedCell = QPoint(-1, -1);

    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//private attributes
private:

    
//public methods
public:
    CGame(R *r, CScene *scene, QWidget *view);
    ~CGame();
    
    bool addCannon(std::shared_ptr<ICannon> cannon);
    
    void updatePath();
    void scaleObjects();

    void selectCell(QPoint pos);
    void selectCell(int i, int j);
    void deselectCell();

    QPoint findNearestCell(QPointF from);

    bool addCannon(QPoint cell);
    bool addCannon(int x, int y);
    
public slots:
    virtual void onTimer();
    
};
