#include <Game/Game.h>
#include <Cannon/FastCannon.h>
#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
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
    scene.calculateWorkingRectangle(ui->graphicsView->geometry());
    Game game(&r, &scene);
    ui->graphicsView->setScene(scene.getGraphicsScene());
    
    QPixmap borders("borders.png");
    scene.drawPixmap(0, 0, Scene::LOCAL_WIDTH, Scene::LOCAL_HEIGHT, borders);
    
    std::shared_ptr<ICannon> cannon = std::static_pointer_cast<ICannon>(std::make_shared<FastCannon>(&game));
    cannon->draw();
    //game.gameScene->addRect(workingRectangle, QPen("lightblue"), QBrush("blue"));
}

#endif
