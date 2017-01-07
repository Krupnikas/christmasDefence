#pragma once

//#define SHOW_DISTANCES
#define SHOW_GRAPHICS_DEBUG


#include <Scene.h>
#include <Window.h>
#include <SceneObject/GameBackground.h>
#include <Wave/WaveManager.h>
#include <Game/User.h>

class IBullet;
class IEnemy;
class ICannon;
class CCannonSelection;
class CCannonUpgrade;
class CButton;
class CUserInfo;
class CWaveInfoBlock;
class MainView;

class CGame : public IWindow
{
    Q_OBJECT
    
//public attributes
public:
    const QPoint UnselCell = QPoint(-1, -1);
    
    R *r;
    CScene *scene;
    MainView *view;
    
    CWaveManager waveManager;
    CUser user;   

    eButtonType pressedButton;
    
    QTimer *positionTimer;
    QTimer *drawTimer;
    
    std::shared_ptr<CGameBackground> background;
    std::shared_ptr<CCannonSelection> cannonSelectionInfoBlock;
    std::shared_ptr<CCannonUpgrade> cannonUpgradeInfoBlock;
    std::shared_ptr<CUserInfo> userInformationBlock;
    std::shared_ptr<CWaveInfoBlock> waveInformationBlock;
    std::shared_ptr<CButton> menuButton;
    
    //TODO - remove this shit!
    std::shared_ptr<QGraphicsItem> selectedCellItem;
    
    QPoint selectedCell = UnselCell;

    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::shared_ptr<IEnemy> > enemies;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//public methods
public:
    CGame(R *r, CScene *scene, MainView *view);
    ~CGame();

    //IWindow methods
    virtual void create() override;
    virtual void show() override;
    virtual void hide() override;
    virtual void resize() override;
    virtual void close() override;

    void mousePressEvent(QMouseEvent *event);

    void startGameLevel(int level);
    void endGame();


    bool isGameCell(QPoint cell);
    
    bool buyCannon(std::shared_ptr<ICannon> cannon);
    void sellCannon(std::shared_ptr<ICannon> cannon);
    void sellCannon(QPoint cell);
    bool addEnemy(int enemyType, int enemyTexture, int enemyPower);
    
    QPointF cellLeftTop(QPoint cell);
    QPointF cellCenter(QPoint cell);
    
    void updateDistances();
    
    void selectCell(QPoint pos);
    void deselectCell();

    QPoint findNearestCell(QPointF from);

signals:
    void mousePressed(QMouseEvent *pressEvent);

private slots:
    void onButtonPressed(int type);
    
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
    
    std::mutex cannonsMutex;
};
