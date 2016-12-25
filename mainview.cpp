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
    gameStatus(eGameStatus::eGameMenu),
    r(), scene(&r), game(&r, &scene, this), ui(new Ui::MainView)
{
    //layout setting
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);

    //graphics view optimizations
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //OpenGL optimizations
    QGLFormat format = QGLFormat(QGL::DirectRendering);
    QGLWidget *glWidget = new QGLWidget(format);
    ui->graphicsView->setViewport(glWidget);

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
    
    //interface connection setting
    connect(this, SIGNAL(mousePressed(QMouseEvent*)),
            &game, SLOT(onMousePressed(QMouseEvent*)));

   // this->showFullScreen();*/
}

MainView::~MainView()
{
    delete ui;
}

void MainView::resizeEvent(QResizeEvent *event)
{
    event->accept();
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());

    switch (gameStatus)
    {
    case eGameStatus::eGameMenu:
        break;
    case eGameStatus::eLevelMenu:
        break;
    case eGameStatus::eGame:
        game.resize();
        break;
    default:
        qDebug() << "MainView: resizeEvent: invalid gameStatus";
    }

    //QTimer::singleShot(2000, this, SLOT(setEnabled()));

}

void MainView::showEvent(QShowEvent*)
{
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->gridLayout->geometry());


//    game.resize();
//    game.showObjects();

}

void MainView::mouseDoubleClickEvent(QMouseEvent *)
{
/*    if (e->button() == Qt::LeftButton)
    {
        QPointF p = game.view->mapFromGlobal(QCursor::pos());
        QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));
        int selX = selectedCell.x();
        int selY = selectedCell.y();
        if (game.cannons[selX][selY])
            game.cannons[selX][selY]->upgrade();
    }
    */
}

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    switch (gameStatus)
    {
    case eGameStatus::eGameMenu:
        game.startLevel(1);
        gameStatus = eGameStatus::eGame;
        break;
    case eGameStatus::eLevelMenu:
        break;
    case eGameStatus::eGame:
    {
        emit mousePressed(eventPress);

        if (game.pressedButton != eBTnone){
            game.pressedButton = eBTnone;
            return;
        }

        QPointF p = game.view->mapFromGlobal(QCursor::pos());
        QPoint selectedCell = game.findNearestCell(scene.toLocalPoint(p));

        game.selectCell(selectedCell);
        break;
    }
    default:
        qDebug() << "MainView: resizeEvent: invalid gameStatus";
    }



}

void MainView::setEnabled()
{
    //ui->graphicsView->setVisible(true);
}
