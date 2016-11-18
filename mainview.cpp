#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    r(), scene(&r), game(&r, &scene, this), ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
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
}

#endif

void MainView::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint p = game.view->mapFromGlobal(QCursor::pos());

    for (int i = 0; i < CellNumY; ++i)
        for (int j = 0; j < CellNumX; ++j)
            if (game.cannons[i][j])
            {
                QPoint center = game.cannons[i][j]->getCenter();
                int x1 = game.scene->toGlobalX(center.x());
                int y1 = game.scene->toGlobalY(center.y());
                qreal angle = helper::calcAngle(x1, y1, p.x(), p.y());
                game.cannons[i][j]->fire(angle);
            }
}
