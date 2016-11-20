#include "mainview.h"
#include "ui_mainview.h"
#include <Game/Helper.h>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    r(), scene(&r), game(&r, &scene, this), ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    

    
}

MainView::~MainView()
{
    delete ui;
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    qreal scaleFactor = scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    game.scaleObjects(scaleFactor);
}

#endif

void MainView::showEvent(QShowEvent *event)
{    
    scene.updateGameRect(ui->graphicsView->geometry());
     
     game.cannons[2][2] = std::make_shared<CFastCannon>(&game, 2, 2, 100, 30, 100);
     game.cannons[5][3] = std::make_shared<CFastCannon>(&game, 5, 3, 100, 30, 100);
     game.cannons[CellNumX - 1][4] = 
             std::make_shared<CFastCannon>(&game, CellNumX - 1, 4, 100, 30, 100);     
     
     CFastCannon *can2 = reinterpret_cast<CFastCannon*>(game.cannons[2][2].get());
     CFastCannon *can1 = reinterpret_cast<CFastCannon*>(game.cannons[5][3].get());
     CFastCannon *can3 = reinterpret_cast<CFastCannon*>(game.cannons[CellNumX - 1][4].get());
     connect(game.gameTimer, SIGNAL(timeout()), can1, SLOT(onTimer()));
     connect(game.gameTimer, SIGNAL(timeout()), can2, SLOT(onTimer()));
     connect(game.gameTimer, SIGNAL(timeout()), can3, SLOT(onTimer()));
     connect(game.gameTimer, SIGNAL(timeout()), &game, SLOT(onTimer()));
     
     game.updatePath();
    
}

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    QPointF p = game.view->mapFromGlobal(QCursor::pos());

    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            if (game.cannons[i][j])
            {
                QPointF center = game.cannons[i][j]->getCenter();
                int x1 = game.scene->toGlobalX(center.x());
                int y1 = game.scene->toGlobalY(center.y());
                qreal angle = helper::calcAngle(x1, y1, p.x(), p.y());
                game.cannons[i][j]->fire(angle);
            }
}
