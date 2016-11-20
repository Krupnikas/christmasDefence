#pragma once

#include <Game/Scene.h>

class ICannon;
class IBullet;
class MainView;

class CGame : public QObject
{
    Q_OBJECT
    
//public attributes
public:
    R *r;
    CScene *scene;
    MainView *view;
    QTimer *gameTimer;
    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    std::vector<std::vector<int>> distances;
    
//private attributes
private:

    
//public methods
public:
    CGame(R *r, CScene *scene, MainView *view);
    ~CGame();
    
    void updatePath();
    void scaleObjects(qreal scaleFactor);
    QPoint findNearestCell(QPointF from);
    bool addCannon(QPoint cell);
    bool addCannon(int x, int y);
    
public slots:
    virtual void onTimer();
    
};
