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

    /*for (int i = 0; i < CellNumX; ++i)
        for (int j = 0; j < CellNumY; ++j)
            game.addCannon(std::make_shared<CFastCannon>(&game, i, j, 100, 30, 100));*/
    

    game.addEnemy(std::make_shared<CFastEnemy>(&game));
    scene.updateDistances(game.distances);
    
    connect(game.positionTimer, SIGNAL(timeout()), &game, SLOT(onPositionTimer()));
    connect(game.drawTimer, SIGNAL(timeout()), &game, SLOT(onDrawTimer()));
    game.showObjects();
}

void MainView::mouseDoubleClickEvent(QMouseEvent *eventPress)
{

}

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    QPointF p = game.view->mapFromGlobal(QCursor::pos());
    QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
    
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
        QPointF cellCenterGlobal(game.scene->toGlobalPoint(game.cellCenter(selectedCell)));
        qreal angle = helper::calcAngle(cellCenterGlobal, p);
        game.addCannon(std::make_shared<CFastCannon>(&game,
                                                     selectedCell,
                                                     angle));
        game.block->hide();
        game.deselectCell();
    }
    
    if (selectedCell != game.hintedCell && game.cannons[game.hintedCell.x()][game.hintedCell.y()])
        game.cannons[game.hintedCell.x()][game.hintedCell.y()]->hideRadius();
        
    if (game.cannons[selectedCell.x()][selectedCell.y()])
    {
        game.cannons[selectedCell.x()][selectedCell.y()]->showRadius();
        game.hintedCell = selectedCell;
    }

                 
    if (eventPress->button() == Qt::LeftButton)
        game.addEnemy(std::make_shared<CFastEnemy>(&game));
}
