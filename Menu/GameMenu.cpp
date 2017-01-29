#include <Menu/GameMenu.h>
#include <Game/Game.h>
#include <mainview.h>

CGameMenu::CGameMenu(CGame *game)
{
    this->game = game;
}

void CGameMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, game->r->game_menu_background);
    
    qreal itemZOrder = m::BackgroundZOrder + 0.1;
    
    caption = std::make_shared<CSceneObject>(
                0, itemZOrder,
                QPointF(m::LocalWidth / 5.0, 0),
                QSizeF(m::LocalWidth / 5.0 * 3, m::LocalHeight / 3.0),
                game->r->game_menu_caption, game);
    
    
    
    qreal buttonWidth = m::LocalWidth / 5.0 * 3;
    qreal buttonTop = m::LocalHeight / 3.0;
    
    qreal buttonDist = m::LocalHeight * 2.0 / 3 / m::GameMenuButtonNum / 5;
    qreal buttonHeight = (m::LocalHeight / 3.0 * 2 - buttonDist * (m::GameMenuButtonNum + 1)) / m::GameMenuButtonNum;
    
    buttons.resize(m::GameMenuButtonNum);
    
    for (int i = 0; i < m::GameMenuButtonNum; ++i)
    {
        buttons[i] = std::make_shared<CButton>(
                    itemZOrder,
                    QPointF(m::LocalWidth / 2, buttonTop + buttonDist * (i + 1) + buttonHeight * (i + 0.5)),
                    QSizeF(buttonWidth, buttonHeight),
                    game, static_cast<int>(EButtonType::eBTgmCampaign) + i,
                    game->r->gm_buttons[i], game->r->gm_focused_buttons[i],
                    game->r->gm_pressed_buttons[i], game->r->gm_buttons[i],
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
        close();
        game->view->levelMenu.create();
        game->view->levelMenu.show();
        break;   
    case EButtonType::eBTgmQuickPlay:
        close();
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
