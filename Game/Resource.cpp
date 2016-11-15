#include <Game/Resource.h>

R::R()
{
    res_dir = "../christmasDefence/res/christmas";

    cell1 = QPixmap(get("cell1"));
    cell2 = QPixmap(get("cell2"));
    
    window_background = QPixmap(get("window_background"));
    game_background = QPixmap(get("game_background"));
    
    fast_cannon_1 = QPixmap(get("fast_cannon_1"));
    fast_cannon_2 = QPixmap(get("fast_cannon_2.png"));
    fast_cannon_3 = QPixmap(get("fast_cannon_3.png"));
    
    //fast_cannon_1 = QPixmap(get("fast_cannon_1"));
    fast_bullet_2 = QPixmap(get("fast_bullet_2.png"));
    //fast_cannon_3 = QPixmap(get("fast_cannon_3.png"));    
}

QString R::get(const char *val)
{
    QString str = res_dir + "/" + val;
    return str;
}
