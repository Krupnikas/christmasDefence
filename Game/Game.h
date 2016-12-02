#pragma once

//#define SHOW_DISTANCES
#define SHOW_GRAPHICS_DEBUG

#include <Game/Scene.h>
#include <Wave/WaveManager.h>

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
    const QPoint UnselCell = QPoint(-1, -1);
    
    R *r;
    CScene *scene;
    QWidget *view;
    CWaveManager waveManager;
    
    QTimer *positionTimer;
    QTimer *drawTimer;
    std::shared_ptr<CCannonSelection> block;
    std::shared_ptr<QGraphicsItem> selectedCellItem;
    QPoint selectedCell = UnselCell;
    QPoint hintedCell = UnselCell;

    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::shared_ptr<IEnemy> > enemies;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//public methods
public:
    CGame(R *r, CScene *scene, QWidget *view);
    ~CGame();
    
    bool isGameCell(QPoint cell);
    
    bool addCannon(std::shared_ptr<ICannon> cannon);
    bool addEnemy(std::shared_ptr<IEnemy> enemy);

    bool isEnemieCollision(QPoint Cell);
    
    QPointF cellLeftTop(QPoint cell);
    QPointF cellCenter(QPoint cell);
    
    void updateDistances();
    void scaleObjects();
    
    void hideObjects();
    void showObjects();

    void selectCell(QPoint pos);
    void deselectCell();

    QPoint findNearestCell(QPointF from);

signals:
    void mousePressed(QMouseEvent *pressEvent);


public slots:
    virtual void onPositionTimer();
    virtual void onDrawTimer();
    virtual void onMousePressed(QMouseEvent *pressEvent);

//private methods
private:
    void deselect_cell_();    
    
//private attributes
private:
    qreal fps = 0;
    qreal tps = 0;
    bool distancesChanged = false;
        
};
