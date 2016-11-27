#include "mainview.h"
#include "ui_mainview.h"
#include <Game/Helper.h>
#include <Enemy/FastEnemy.h>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    r(), scene(&r), game(&r, &scene, this), ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGLFormat format = QGLFormat(QGL::DirectRendering);
    QGLWidget *glWidget = new QGLWidget(format);
    ui->graphicsView->setViewport(glWidget);
    
    setAttribute(Qt::WA_TranslucentBackground, true);
   // ui->graphicsView->setViewportUpdateMode(QGraphicsView::);
    //this->showFullScreen();
}

MainView::~MainView()
{
    delete ui;
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    game.hideObjects();
    ui->graphicsView->setSceneRect(ui->graphicsView->geometry());
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    game.scaleObjects();
    game.showObjects();

}

#endif

void MainView::showEvent(QShowEvent*)
{

    scene.updateGameRect(ui->graphicsView->geometry());

    for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            game.addCannon(std::make_shared<CFastCannon>(&game, i, j, 100, 30, 100));
    scene.updateDistances(game.distances);
    /*
    game.addCannon(std::make_shared<CFastCannon>(&game, 2, 2, 100, 30, 100));
    game.addCannon(std::make_shared<CFastCannon>(&game, 5, 3, 100, 30, 100));
    game.addCannon(std::make_shared<CFastCannon>(&game, CellNumX - 1, 4, 100, 30, 100));     
    connect(game.gameTimer, SIGNAL(timeout()), &game, SLOT(onTimer()));*/
    
    connect(game.gameTimer, SIGNAL(timeout()), &game, SLOT(onTimer()));
    connect(game.gameTimer2, SIGNAL(timeout()), &game, SLOT(onTimer2()));
    game.showObjects();
}

void MainView::mouseDoubleClickEvent(QMouseEvent *)
{
    game.addEnemy(std::make_shared<CFastEnemy>(&game));       
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
        game.addEnemy(std::make_shared<CFastEnemy>(&game));
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
