#include <Menu/LevelMenu.h>
#include <Game/Game.h>
#include <mainview.h>

CLevelMenu::CLevelMenu(CGame *game)
{
    this->game = game;
}

void CLevelMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, &game->r->level_menu_background);
    
    qreal itemZOrder = BackgroundZOrder + 0.1;
    
    caption = std::make_shared<CSceneObject>(
                0, itemZOrder,
                QPointF(LocalWidth / 5.0, 0),
                QSizeF(LocalWidth / 5.0 * 3, LocalHeight / 3.0),
                &game->r->level_menu_caption, game);
    
    qreal buttonTop = LocalHeight / 3.0;
    
    qreal buttonDist = LocalHeight * 2.0 / 3 / LevelNum / 5;
    qreal buttonHeight = (LocalHeight / 3.0 * 2 - buttonDist * (LevelNum + 1)) / LevelNum;
    qreal buttonWidth = buttonHeight;
    
    levels.resize(LevelNum);
    
    for (int i = 0; i < LevelNum; ++i)
    {
        levels[i] = std::make_shared<CButton>(
                    itemZOrder,
                    QPointF(LocalWidth / 2, buttonTop + buttonDist * (i + 1) + buttonHeight * (i + 0.5)),
                    QSizeF(buttonWidth, buttonHeight),
                    game, i,
                    &game->r->lm_levels[i],
                    &game->r->lm_focused_levels[i],
                    &game->r->lm_pressed_levels[i],
                    nullptr,
                    true
                    );
        connect(levels[i].get(), SIGNAL(pressed(int)), this, SLOT(onButtonPressed(int)));
    }
    
    back = std::make_shared<CButton>(
                itemZOrder,
                QPointF(0, LocalHeight - buttonHeight),
                QSizeF(buttonWidth, buttonHeight),
                game, LevelNum,
                &game->r->level_menu_back
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
    
    game->view->gameStatus = eGameStatus::eLevelMenu;
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
    background->draw();
    background->show();
    
    caption->scale();
    caption->draw();
    caption->show();
    
    back->scale();
    back->draw();
    back->show();
    
    for (auto level: levels)
    {
        level->scale();
        level->draw();
        level->show();
    }
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
    game->startGameLevel(level);
    game->view->gameStatus = eGameStatus::eGame;
    
}
