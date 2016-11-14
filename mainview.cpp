#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    r(), scene(&r), game(&r, &scene), ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
}

MainView::~MainView()
{
    delete ui;
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    scene.updateGameRect(ui->graphicsView->geometry());
    game.scene = &scene;
    ui->graphicsView->setScene(scene.getGraphicsScene());
    
    game.updateObjects();
    /*std::shared_ptr<ICannon> cannon = std::static_pointer_cast<ICannon>(
                std::make_shared<FastCannon>(&game, 0, 0, 100, 50, 100));
    cannon->draw();*/
    
    /*QTimer *timer = new QTimer(this);
    FastCannon *can = reinterpret_cast<FastCannon*>(cannon.get());
    connect(timer, SIGNAL(timeout()), can, SLOT(rotate()));
    timer->start(1000);*/
    
    /*
    QTime time;
    time.start();
    for(;time.elapsed() < 1000;)
    {
    }*/
    //game.gameScene->addRect(workingRectangle, QPen("lightblue"), QBrush("blue"));
}

#endif
