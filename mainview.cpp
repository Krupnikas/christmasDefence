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

MainView::MainView(QApplication *app, QWidget *parent):
    QWidget(parent),
    app(app),
    gameStatus(EGameStatus::eNotInited),
    r(), scene(&r),
    game(this, &r, &scene, &playlist, &player),
    gameMenu(&game),
    levelMenu(&game),
    ui(new Ui::MainView)
{
    //app setting
    app->installEventFilter(this);
    
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

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    //OpenGL optimizations
    QGLFormat format = QGLFormat(QGL::DirectRendering);
    QGLWidget *glWidget = new QGLWidget(format);
    ui->graphicsView->setViewport(glWidget/*new QOpenGLWidget()*/);
/*
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
    this->setAttribute(Qt::WA_AcceptTouchEvents);
    */
    //playlist setting
//    QString sound = r.getSound("mainTheme.mp3");//"qrc:/res/christmas/sounds/mainTheme.mp3";
//    bool success = playlist.addMedia(QUrl(sound/*r.getSound("mainTheme.mp3")*/));
//    if (!success)
//        qDebug() << "failed to load mp3";
    
//    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);    

//    playlist.setCurrentIndex(0);
    
//    player.setPlaylist(&playlist);
//    player.setVolume(1);
//    player.play();
    
    
    //this->showFullScreen();
}

MainView::~MainView()
{
    delete ui;
}

void MainView::setGraphicsViewUpdatesEnabled(bool enabled)
{
    ui->graphicsView->setUpdatesEnabled(enabled);
}

void MainView::resizeEvent(QResizeEvent *event)
{
    event->accept();
    ui->graphicsView->setSceneRect(ui->gridLayout->geometry());
    scene.updateGameRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene.getGraphicsScene());
    
    switch (gameStatus)
    {
    case EGameStatus::eNotInited:
        break;
    case EGameStatus::eGameMenu:
        gameMenu.resize();
        gameMenu.show();
        break;
    case EGameStatus::eLevelMenu:
        levelMenu.resize();
        levelMenu.show();
        break;
    case EGameStatus::eGame:
        game.resize();
        game.show();
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

    gameMenu.create();
    //game.create();

    gameMenu.show();
    gameStatus = EGameStatus::eGameMenu;
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
    case EGameStatus::eGameMenu:
        //emit mouseDown(event);
        break;
    case EGameStatus::eLevelMenu:
        break;
    case EGameStatus::eGame:
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
        qDebug() << "MainView: mousePressEvent: invalid gameStatus";
    }
}

void MainView::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseUp(event);
}

void MainView::wheelEvent(QWheelEvent *event)
{
    
//    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    //Scale the view ie. do the zoom
//    double scaleFactor = 1.15; //How fast we zoom
//    if(event->delta() > 0) {
//        //Zoom in
//        ui->graphicsView->scale(scaleFactor, scaleFactor);
//    } else {
//        //Zooming out
//        ui->graphicsView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
//    }
}

bool MainView::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (gameStatus == EGameStatus::eNotInited)
        return false;
    
    QEventLoop loop;
    
    switch (event->type())
    {
    case QEvent::MouseMove:
        emit mouseMoved(mouseEvent);
        return true;
    case QEvent::MouseButtonPress:
    {
        if (gameStatus == EGameStatus::eGame &&
                !game.cannonSelectionInfoBlock->isVisible() &&
                !game.cannonUpgradeInfoBlock->isVisible())
            game.mousePressEvent(mouseEvent);

        emit mouseDown(mouseEvent);

        return true;
    }
    case QEvent::MouseButtonRelease:
        emit mouseUp(mouseEvent);
        return true;
    default:
        return false;
    }
}

void MainView::setEnabled()
{
    //ui->graphicsView->setVisible(true);
}
