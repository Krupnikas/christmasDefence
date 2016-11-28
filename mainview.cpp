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
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGLFormat format = QGLFormat(QGL::DirectRendering);
    QGLWidget *glWidget = new QGLWidget(format);
    ui->graphicsView->setViewport(glWidget);
    
    //setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TranslucentBackground);
   // ui->graphicsView->setViewportUpdateMode(QGraphicsView::);
    this->showFullScreen();
}

MainView::~MainView()
{
    delete ui;
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    //game.hideObjects();
    ui->graphicsView->setSceneRect(ui->graphicsView->geometry());
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    game.scaleObjects();
    //game.showObjects();

}

#endif

void MainView::showEvent(QShowEvent*)
{
    scene.updateGameRect(ui->graphicsView->geometry());
    /*for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            game.addCannon(std::make_shared<CFastCannon>(&game, i, j, 100, 30, 100));*/

    //game.addEnemy(std::make_shared<CFastEnemy>(&game));
    scene.updateDistances(game.distances);
    
    connect(game.positionTimer, SIGNAL(timeout()), &game, SLOT(onPositionTimer()));
    connect(game.drawTimer, SIGNAL(timeout()), &game, SLOT(onDrawTimer()));
    game.showObjects();
}

void MainView::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        QPointF p = game.view->mapFromGlobal(QCursor::pos());
        QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
        int selX = selectedCell.x();
        int selY = selectedCell.y();
        if (game.cannons[selX][selY])
            game.cannons[selX][selY]->upgrade();
    }     
}

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    QPointF p = game.view->mapFromGlobal(QCursor::pos());
    QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
    int selX = selectedCell.x();
    int selY = selectedCell.y();
    /*
    if (eventPress->button() == Qt::RightButton){
        if (game.selectedCell != selectedCell){
            game.selectCell(selectedCell);
            if (game.block)
                game.block->updatePosition(selectedCell);
            else
                game.block = std::make_shared<CCannonSelection>(&game, selectedCell);
            game.block->draw();
            game.block->show();            
            return;
        }
        if (!game.cannons[selX][selY])
        {
            QPointF cellCenterGlobal(game.scene->toGlobalPoint(game.cellCenter(selectedCell)));
            qreal angle = helper::calcAngle(cellCenterGlobal, p);
            game.addCannon(std::make_shared<CFastCannon>(&game,
                                                     selectedCell,
                                                     angle));
        }
        else
        {
            game.cannons[selX][selY] = nullptr;
        }
        game.block->hide();
        game.deselectCell();
    }*/
    
    if (eventPress->button() == Qt::LeftButton)
    {
        if (selectedCell == game.selectedCell)
        {
            game.deselectCell();
            if (!game.cannons[selX][selY])
            {
                QPointF cellCenterGlobal(game.scene->toGlobalPoint(game.cellCenter(selectedCell)));
                qreal angle = helper::calcAngle(cellCenterGlobal, p);
                game.addCannon(std::make_shared<CFastCannon>(&game, selectedCell, angle));
                game.addEnemy(std::make_shared<CFastEnemy>(&game));
                game.selectCell(selectedCell);
            }
            return;
        }
        
        game.selectCell(selectedCell);
        /*
        if (!game.cannons[selX][selY])
            game.addEnemy(std::make_shared<CFastEnemy>(&game));
        
        if (game.cannons[selX][selY])
        {
            if (selectedCell != game.selectedCell && 
                    game.selectedCell != QPoint(-1, -1))
            {
                if (game.cannons[game.selectedCell.x()][game.selectedCell.y()])
                {
                    game.cannons[game.selectedCell.x()][game.selectedCell.y()]->hideRadius();
                    game.selectedCell = QPoint(-1, -1);
                }
                else
                {
                    game.block->hide();
                    game.deselectCell();
                }
                game.cannons[selX][selY]->showRadius();
            }
            else if (selectedCell == game.selectedCell)
            {
                game.cannons[game.selectedCell.x()][game.selectedCell.y()]->hideRadius();
                game.selectedCell = QPoint(-1, -1);
            }
        }
        
        if (game.cannons[selX][selY])
        {
            game.cannons[selX][selY]->showRadius();
            if (game.selectedCell != QPoint(-1, -1) && game.cannons[game.selectedCell.x()][game.selectedCell.y()])
            {
                game.cannons[game.selectedCell.x()][game.selectedCell.y()]->hideRadius();
                game.selectedCell = QPoint(-1, -1);
            }
            game.selectedCell = selectedCell;
        }
        else if (game.selectedCell != QPoint(-1, -1))
        {
            if (game.cannons[game.selectedCell.x()][game.selectedCell.y()])
            {
                game.cannons[game.selectedCell.x()][game.selectedCell.y()]->hideRadius();
            }
            
        }*/
        
        
    }
    
}
