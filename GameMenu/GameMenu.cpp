#include <GameMenu/GameMenu.h>
#include <Game/Game.h>
#include <mainview.h>

CGameMenu::CGameMenu(CGame *game)
{
    this->game = game;
}

void CGameMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, &game->r->game_menu_background);
    
    qreal itemZOrder = BackgroundZOrder + 0.1;
    
    caption = std::make_shared<CSceneObject>(
                0, itemZOrder,
                QPointF(LocalWidth / 5.0, 0),
                QSizeF(LocalWidth / 5.0 * 3, LocalHeight / 3.0),
                &game->r->game_menu_caption, game);
    
    
    
    qreal buttonWidth = LocalWidth / 5.0 * 3;
    qreal buttonTop = LocalHeight / 3.0;
    
    qreal buttonDist = LocalHeight * 2.0 / 3 / GameMenuButtonNum / 5;
    qreal buttonHeight = (LocalHeight / 3.0 * 2 - buttonDist * (GameMenuButtonNum + 1)) / GameMenuButtonNum;
    
    buttons.resize(GameMenuButtonNum);
    
    for (int i = 0; i < GameMenuButtonNum; ++i)
    {
        buttons[i] = std::make_shared<CButton>(
                    itemZOrder,
                    QPointF(LocalWidth / 2, buttonTop + buttonDist * (i + 1) + buttonHeight * (i + 0.5)),
                    QSizeF(buttonWidth, buttonHeight),
                    game, static_cast<eButtonType>(eBTgmCampaign + i),
                    &game->r->gm_buttons[i], &game->r->gm_focused_buttons[i],
                    &game->r->gm_pressed_buttons[i], &game->r->gm_buttons[i],
                    false
                    );
    }
    
    connect(buttons[1].get(), SIGNAL(pressed(eButtonType)), this, SLOT(onButtonPressed(eButtonType)));
    
}

void CGameMenu::show()
{
    background->show();
    
    caption->draw();
    caption->show();
    
    for (auto button: buttons)
    {
        button->draw();
        button->show();
    }
}

void CGameMenu::hide()
{
    background->hide();
    caption->hide();
    
    for (auto button: buttons)
        button->hide();
}

void CGameMenu::resize()
{
    background->scale();
    background->draw();
    background->show();
    
    caption->scale();
    caption->draw();
    caption->show();
    
    for (auto button: buttons)
    {
        button->scale();
        button->draw();
        button->show();
    }
}

void CGameMenu::close()
{

}

void CGameMenu::mousePressEvent(QMouseEvent *event)
{

}

void CGameMenu::mouseMoveEvent(QMouseEvent *event)
{
    
}

void CGameMenu::onButtonPressed(eButtonType type)
{
    switch (type)
    {
    case eButtonType::eBTgmQuickPlay:
        hide();
        game->show();
        game->startGameLevel(1);
        game->view->gameStatus = eGameStatus::eGame;
        break;
    default:
        break;
    }
}
