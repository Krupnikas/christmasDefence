#include "mainview.h"
#include "ui_mainview.h"

#include <Helper.h>
#include <Enemy/FastEnemy.h>
#include <Cannon/BurnCannon.h>
#include <Cannon/FastCannon.h>
#include <Cannon/MonsterCannon.h>
#include <Cannon/SlowCannon.h>
#include <InfoBlock/CannonSelection.h>
#include <InfoBlock/CannonUpgrade.h>

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    gameStatus(eGameStatus::eNotInited),
    r(), scene(&r),
    game(&r, &scene, this),
    gameMenu(&game),
    ui(new Ui::MainView)
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
    connect(this, SIGNAL(mousePressEvent(QMouseEvent*)),
            &game, SLOT(onMousePressed(QMouseEvent*)));
//    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)),
//            &game, SLOT(onMouseMoved(QMouseEvent*)));

   // this->showFullScreen();*/
    setMouseTracking(true);
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
    case eGameStatus::eNotInited:
        break;
    default:
        gameMenu.resize();
        game.resize();
        qDebug() << "MainView: resizeEvent: invalid gameStatus";
    }

    //QTimer::singleShot(2000, this, SLOT(setEnabled()));

}

void MainView::showEvent(QShowEvent*)
{
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->gridLayout->geometry());

    gameMenu.create();
    game.create();

    gameMenu.show();
    gameStatus = eGameStatus::eGameMenu;
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

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseUp(event);
}

void MainView::mousePressEvent(QMouseEvent *event)
{
    switch (gameStatus)
    {
    case eGameStatus::eGameMenu:
        emit mouseDown(event);
        break;
    case eGameStatus::eLevelMenu:
        break;
    case eGameStatus::eGame:
    {
        //QThread::msleep(500);
        bool iv = game.cannonSelectionInfoBlock->isVisible();
        bool sv = game.cannonUpgradeInfoBlock->isVisible();
        if (!iv && !sv)
            game.mousePressEvent(event);

        emit mouseDown(event);
        
        break;
    }
    default:
        qDebug() << "MainView: resizeEvent: invalid gameStatus";
    }
}

void MainView::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseUp(event);
}

bool MainView::eventFilter(QObject *, QEvent *event)
{
    if (gameStatus == eGameStatus::eNotInited)
        return false;
    
    QEventLoop loop;
    
    switch (event->type())
    {
    /*case QEvent::MouseMove:
        emit mouseMoved(dynamic_cast<QMouseEvent*>(event));
        return true;*/
    case QEvent::MouseButtonPress:
        emit mouseDown(dynamic_cast<QMouseEvent*>(event));
        if (gameStatus == eGameStatus::eGame &&
                !game.cannonSelectionInfoBlock->isVisible() &&
                !game.cannonUpgradeInfoBlock->isVisible())
            game.mousePressEvent(dynamic_cast<QMouseEvent*>(event));
        return true;
    case QEvent::MouseButtonRelease:
        emit mouseUp(dynamic_cast<QMouseEvent*>(event));
        return true;
    default:
        return false;
    }
}

void MainView::setEnabled()
{
    //ui->graphicsView->setVisible(true);
}
