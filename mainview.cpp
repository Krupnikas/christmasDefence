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
    //this->showFullScreen();
}

MainView::~MainView()
{
    delete ui;
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    game.scaleObjects();
    
}

#endif

void MainView::showEvent(QShowEvent*)
{
    scene.updateGameRect(ui->graphicsView->geometry());

    game.addCannon(std::make_shared<CFastCannon>(&game, 2, 2, 100, 30, 100));
    game.addCannon(std::make_shared<CFastCannon>(&game, 5, 3, 100, 30, 100));
    game.addCannon(std::make_shared<CFastCannon>(&game, CellNumX - 1, 4, 100, 30, 100));     
    connect(game.gameTimer, SIGNAL(timeout()), &game, SLOT(onTimer()));
    
    scene.updateDistances(game.distances);
    connect(game.gameTimer, SIGNAL(timeout()), &game, SLOT(onTimer()));
}

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    QPointF p = game.view->mapFromGlobal(QCursor::pos());

    if (eventPress->button() == Qt::RightButton){
        QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
        if (game.selectedCell != selectedCell){
            game.selectCell(selectedCell);
            if (game.block)
            {
                game.block->updatePosition(selectedCell);
                game.block->draw();
            }
            else
            {
                game.block = std::make_shared<CCannonSelection>(&game, selectedCell);
                game.block->draw();
            }
            
            return;
        }
        game.addCannon(std::make_shared<CFastCannon>(&game,
                                                     selectedCell.x(), selectedCell.y(),
                                                     100, 30, 100));
        game.block->hide();
        game.deselectCell();
        return;
    }

    if (eventPress->button() == Qt::MidButton){
        QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
        if (game.selectedCell != selectedCell){
            game.selectCell(selectedCell);
            game.block = std::make_shared<CCannonSelection>(&game, selectedCell);
            game.block->draw();
            return;
        }
        game.addCannon(std::make_shared<CFastCannon>(&game,
                                                     selectedCell.x(), selectedCell.y(),
                                                     100, 30, 100));
        qDebug() << "Cannon added";
        game.block->hide();
        game.deselectCell();
        return;
    }
                  
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
