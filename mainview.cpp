#include "mainview.h"
#include "ui_mainview.h"
#include <Game/Helper.h>
#include <Enemy/FastEnemy.h>
#include <Cannon/BurnCannon.h>
#include <Cannon/FastCannon.h>
#include <Cannon/MonsterCannon.h>
#include <Cannon/SlowCannon.h>
#include <InfoBlock/CannonSelection.h>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    r(), scene(&r), game(&r, &scene, this), ui(new Ui::MainView)
{
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    QOpenGLContext::OpenGLModuleType type(QOpenGLContext::openGLModuleType());
    qDebug() << "QOpenGLContextQOpenGLContextQOpenGLContext" << type;
    if (type == QOpenGLContext::LibGL) {
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    } else {
        fmt.setVersion(3, 0);
        fmt.setRenderableType(QSurfaceFormat::OpenGLES);
    }

    QSurfaceFormat::setDefaultFormat(fmt);

    ui->setupUi(this);

    this->setLayout(ui->gridLayout);

    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    //ui->graphicsView->fitInView(ui->gridLayout->geometry());

    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGLFormat format = QGLFormat(QGL::DirectRendering);
    QGLWidget *glWidget = new QGLWidget(format);
    ui->graphicsView->setViewport(glWidget);
    
    //setAttribute(Qt::WA_TranslucentBackground);
   // this->showFullScreen();*/
}

MainView::~MainView()
{
    delete ui;
}

void MainView::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    game.scaleObjects();

    QTimer::singleShot(2000, this, SLOT(setEnabled()));

}

void MainView::showEvent(QShowEvent*)
{
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->gridLayout->geometry());
    game.waveManager.initialize(&game);
    scene.updateDistances(game.distances);
    
    connect(game.positionTimer, SIGNAL(timeout()), &game, SLOT(onPositionTimer()));
    connect(game.drawTimer, SIGNAL(timeout()), &game, SLOT(onDrawTimer()));
    connect(this, SIGNAL(mousePressed(QMouseEvent*)),
            &game, SLOT(onMousePressed(QMouseEvent*)));
    game.block = std::make_shared<CCannonSelection>(&game, game.selectedCell);
    game.showObjects();

}

void MainView::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
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
    emit mousePressed(eventPress);

    if (game.pressedButton != eBTnone){
        game.pressedButton = eBTnone;
        return;
    }

    QPointF p = game.view->mapFromGlobal(QCursor::pos());
    QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
    
    int selX = selectedCell.x();
    int selY = selectedCell.y();

    game.selectCell(selectedCell);

}

void MainView::setEnabled()
{
    //ui->graphicsView->setVisible(true);
}
