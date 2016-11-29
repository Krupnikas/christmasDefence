#include <Game/Resource.h>

R::R()
{
    res_dir = "://res/christmas";

    cell1 = QPixmap(get("cell1"));
    cell2 = QPixmap(get("cell2"));
    cellSelected = QPixmap(get("cellSelected"));
    
    window_background = QPixmap(get("window_background"));
    game_background = QPixmap(get("game_background"));
    cannonSelectionBackground = QPixmap(get("cannonSelectingInfoBlockBackground"));
    
    entireRadius = QPixmap(get("entireRadius.png"));

    buttonClose = QPixmap(get("clo.png"));
    
    fast_cannon_1 = QPixmap(get("fast_cannon_1"));
    fast_cannon_2 = QPixmap(get("fast_cannon_2"));
    fast_cannon_3 = QPixmap(get("fast_cannon_3"));
    
    fast_bullet_1 = QPixmap(get("fast_bullet_1"));
    fast_bullet_2 = QPixmap(get("fast_bullet_2"));
    fast_bullet_3 = QPixmap(get("fast_bullet_3"));
    
    fast_enemy_1 = QPixmap(get("fast_enemy_1"));
    fast_enemy_2 = QPixmap(get("fast_enemy_2"));
    fast_enemy_3 = QPixmap(get("fast_enemy_3"));
}

QString R::get(const char *val)
{
    QString str = res_dir + "/" + val;
    return str;
}
