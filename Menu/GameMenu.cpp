#include <Menu/GameMenu.h>
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
                    game, static_cast<int>(EButtonType::eBTgmCampaign) + i,
                    &game->r->gm_buttons[i], &game->r->gm_focused_buttons[i],
                    &game->r->gm_pressed_buttons[i], &game->r->gm_buttons[i],
                    true
                    );
        connect(buttons[i].get(), SIGNAL(pressed(int)), this, SLOT(onButtonPressed(int)));
    }
    
    
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
    
    game->view->gameStatus = EGameStatus::eGameMenu;
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
    
    caption->scale();
    
    for (auto button: buttons)
        button->scale();
}

void CGameMenu::close()
{
    background->remove();
    caption->remove();
    for (auto button: buttons)
        button->remove();
}

void CGameMenu::onButtonPressed(int type)
{
    EButtonType eType = static_cast<EButtonType>(type);
    switch (eType)
    {
    case EButtonType::eBTgmCampaign:
        hide();
        game->view->levelMenu.show();
        break;   
    case EButtonType::eBTgmQuickPlay:
        hide();
        game->show();
        game->startGameLevel(1);
        break;
    case EButtonType::eBTgmDev:
        break;
    case EButtonType::eBTgmExit:
        QApplication::quit();
    default:
        break;
    }
}
