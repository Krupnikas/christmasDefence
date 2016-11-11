#include <Game/Game.h>
#include <Cannon/FastCannon.h>
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

    scene.updateWindowBackground();    
    scene.drawPixmap(0, 0, LocalWidth, LocalHeight, r.game_background);
    
    std::shared_ptr<ICannon> cannon = std::static_pointer_cast<ICannon>(std::make_shared<FastCannon>(&game));
    cannon->draw();
    //game.gameScene->addRect(workingRectangle, QPen("lightblue"), QBrush("blue"));
}

#endif
