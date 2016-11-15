#pragma once

#include <Game/Resource.h>
#include <Game/Scene.h>
#include <Bullet/IBullet.h>

class ICannon;
class FastCannon;
class MainView;

class Game : public QObject
{
    Q_OBJECT
    
//public attributes
public:
    R *r;
    Scene *scene;
    MainView *view;
    QTimer *gameTimer;
    std::vector<std::shared_ptr<IBullet> > bullets;
    std::vector<std::vector<std::shared_ptr<ICannon>>> cannons;
    
//private attributes
private:

    
    
    
//public methods
public:
    Game(R *r, Scene *scene, MainView *view);
    ~Game();
    
public slots:
    virtual void updateObjects();
    
};

#include <Cannon/ICannon.h>
#include <Cannon/FastCannon.h>
#include <mainview.h>
