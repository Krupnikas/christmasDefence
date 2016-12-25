#pragma once

//#define SHOW_DISTANCES
#define SHOW_GRAPHICS_DEBUG

#include <Game/Scene.h>
#include <Wave/WaveManager.h>
#include <Game/User.h>

class IBullet;
class IEnemy;
class ICannon;
class MainView;
class CCannonSelection;
class CCannonUpgrade;

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
    CUser user;   

    eButtonTypes pressedButton;
    
    QTimer *positionTimer;
    QTimer *drawTimer;
    std::shared_ptr<CCannonSelection> cannonSelectionInfoBlock;
    std::shared_ptr<CCannonUpgrade> cannonUpgradeInfoBlock;
    std::shared_ptr<QGraphicsItem> selectedCellItem;
    QPoint selectedCell = UnselCell;

    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::shared_ptr<IEnemy> > enemies;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//public methods
public:
    CGame(R *r, CScene *scene, QWidget *view);
    ~CGame();
    
    void startLevel(int level);
    void end();
    void resize();


    bool isGameCell(QPoint cell);
    
    bool addCannon(std::shared_ptr<ICannon> cannon);
    bool addEnemy(int enemyType, int enemyTexture, int enemyPower);
    
    QPointF cellLeftTop(QPoint cell);
    QPointF cellCenter(QPoint cell);
    
    void updateDistances();
    
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
    void scaleObjects();

//private attributes
private:
    qreal fps = 0;
    
    std::mutex cannonAddMutex;
    bool cannonsAdded = false;
};
