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

void MainView::calculateWorkingRectangle()
{
    workingRectangle = ui->graphicsView->geometry();                          //За основу возьмем прямоугольник всего экрана

    if (workingRectangle.width() * 9 > workingRectangle.height() * 16)      //Если экран шире, чем 16х9
    {
        int newWidth;                                                           //То найдем новую ширину рабочей области
        newWidth = workingRectangle.height() * 16.0/9;                        //Посчитав из высоты экрана * 16/9
        workingRectangle.setWidth(newWidth);                                  //Устанавливаем новую ширину
    }
    else                                                                        //Иначе экран выше, чем 16х9
    {
        int newHeight;                                                          //Найдем новую высоту рабочей области
        newHeight = workingRectangle.width() * 9.0/16;                        //Посчитав из ширины экрана * 16/9
        workingRectangle.setHeight(newHeight);                                //Устанавливаем новую высоту
    }
}

#ifdef TEST

void MainView::resizeEvent(QResizeEvent *)
{
    calculateWorkingRectangle();
    Game game(&r);
    ui->graphicsView->setScene(game.gameScene);
    QPixmap borders("borders.png");
    borders = borders.scaled(workingRectangle.width(), workingRectangle.height());
    game.gameScene->addPixmap(borders);
    std::shared_ptr<ICannon> cannon = std::static_pointer_cast<ICannon>(std::make_shared<FastCannon>(&game));
    cannon->draw();
    //game.gameScene->addRect(workingRectangle, QPen("lightblue"), QBrush("blue"));
}

#endif
