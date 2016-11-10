#include <Game/resource.h>

R::R()
{
    res_dir = "../christmasDefence/res/christmas";
    
    fast_cannon_1 = QPixmap(R::get("fast_cannon_1"));
    fast_cannon_2 = QPixmap(R::get("fast_cannon_2"));
    fast_cannon_3 = QPixmap(R::get("fast_cannon_3.png"));
    
}

QString R::get(const char *val)
{
    QString str = res_dir + "/" + val;
    return str;
}
