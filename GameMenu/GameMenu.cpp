#include <GameMenu/GameMenu.h>
#include <Game/Game.h>

CGameMenu::CGameMenu(CGame *game)
{
    this->game = game;
}

void CGameMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, &game->r->game_menu_background);
    caption = std::make_shared<CSceneObject>(
                0, BackgroundZOrder + 0.1,
                QPointF(LocalWidth / 5.0, 0),
                QSizeF(LocalWidth / 5.0 * 3, LocalHeight / 3.0),
                &game->r->game_menu_caption, game);
}

void CGameMenu::show()
{
    background->show();
    
    caption->draw();
    caption->show();
}

void CGameMenu::hide()
{
    background->hide();
    caption->hide();
}

void CGameMenu::resize()
{
    background->scale();
    background->draw();
    background->show();
    
    caption->scale();
    caption->draw();
    caption->show();
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
