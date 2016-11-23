#include <Game/Resource.h>

R::R()
{
    res_dir = "://res/christmas";

    cell1 = QPixmap(get("cell1.png"));
    cell2 = QPixmap(get("cell2.png"));
    cellSelected = QPixmap(get("cellSelected.png"));
    
    window_background = QPixmap(get("window_background.jpg"));
    game_background = QPixmap(get("game_background.jpg"));
    
    fast_cannon_1 = QPixmap(get("fast_cannon_1.jpg"));
    fast_cannon_2 = QPixmap(get("fast_cannon_2.png"));
    fast_cannon_3 = QPixmap(get("fast_cannon_3.png"));
    
    fast_bullet_1 = QPixmap(get("fast_bullet_1.png"));
    fast_bullet_2 = QPixmap(get("fast_bullet_2.png"));
    fast_bullet_3 = QPixmap(get("fast_bullet_3.png"));
}

QString R::get(const char *val)
{
    QString str = res_dir + "/" + val;
    return str;
}
