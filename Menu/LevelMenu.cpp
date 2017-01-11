#include <Menu/LevelMenu.h>
#include <Game/Game.h>
#include <mainview.h>

CLevelMenu::CLevelMenu(CGame *game)
{
    this->game = game;
}

void CLevelMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, game->r->level_menu_background);
    
    qreal itemZOrder = BackgroundZOrder + 0.1;
    
    caption = std::make_shared<CSceneObject>(
                0, itemZOrder,
                QPointF(LocalWidth / 5.0, 0),
                QSizeF(LocalWidth / 5.0 * 3, LocalHeight / 4.0),
                game->r->level_menu_caption, game);
    
    levels.resize(LevelNum);
    int width = 5;
    int height = LevelNum / width;
    
    qreal buttonTopOffset = LocalHeight / 4.0;
    qreal buttonDistTop = LocalHeight * 3.0 / 4 / height / 5;
    qreal buttonHeight = (LocalHeight / 3.0 * 2 - buttonDistTop * (height + 1)) / height;
    
    qreal buttonWidth = buttonHeight;
    qreal buttonDistLeft = LocalWidth / width / 10.0 * 7;
    qreal buttonLeftOffset = (LocalWidth - (buttonWidth * width + buttonDistLeft * (width - 1))) / 2;
    
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            int ind = i * width + j;
            levels[ind] = std::make_shared<CButton>(
                        itemZOrder,
                        QPointF(buttonLeftOffset + buttonDistLeft * (j) + buttonWidth * (j + 0.5),
                                buttonTopOffset + buttonDistTop * (i + 1) + buttonHeight * (i + 0.5)),
                        QSizeF(buttonWidth, buttonHeight),
                        game, ind,
                        game->r->lm_levels[ind],
                        game->r->lm_focused_levels[ind],
                        game->r->lm_pressed_levels[ind],
                        nullptr,
                        true
                        );
            connect(levels[ind].get(), SIGNAL(pressed(int)), this, SLOT(onButtonPressed(int)));
        }
        
    back = std::make_shared<CButton>(
                itemZOrder,
                QPointF(buttonWidth / 2, LocalHeight - buttonHeight / 2),
                QSizeF(buttonWidth, buttonHeight),
                game, LevelNum,
                game->r->level_menu_back
                );
    connect(back.get(), SIGNAL(pressed(int)), this, SLOT(onButtonPressed(int)));
    
}

void CLevelMenu::show()
{
    background->show();
    
    caption->draw();
    caption->show();
    
    back->draw();
    back->show();
    
    for (auto level: levels)
    {
        level->draw();
        level->show();
    }
    
    game->view->gameStatus = EGameStatus::eLevelMenu;
}

void CLevelMenu::hide()
{
    background->hide();
    caption->hide();
    back->hide();
    
    for (auto level: levels)
        level->hide();
}

void CLevelMenu::resize()
{
    background->scale();
    caption->scale();
    back->scale();
    for (auto level: levels)
        level->scale();
}

void CLevelMenu::close()
{
    background->remove();
    caption->remove();
    back->remove();
    
    for (auto level: levels)
        level->remove();
}

void CLevelMenu::onButtonPressed(int level)
{
    if (level < 0 || level > LevelNum)
    {
        qDebug() << "CLevelMenu: onButtonPressed: invalid level";
        return;
    }
    
    if (level == BackButton)
    {
        hide();
        game->view->gameMenu.show();
        return;
    }
    
    hide();
    game->show();
    game->startGameLevel(level + 1);
    game->view->gameStatus = EGameStatus::eGame;
    
}
