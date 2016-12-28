#include <GameMenu/GameMenu.h>
#include <Game/Game.h>

CGameMenu::CGameMenu(CGame *game)
{
    this->game = game;
}

void CGameMenu::create()
{
    background = std::make_shared<CSceneBackground>(game, &game->r->game_menu_background);
}

void CGameMenu::show()
{
    background->show();
}

void CGameMenu::hide()
{
    background->hide();
}

void CGameMenu::resize()
{
    background->scaleItem();
    background->draw();
    background->show();
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
