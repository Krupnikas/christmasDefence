#include <Game/resource.h>

R::R()
{
    res_dir = "../christmasDefence/res/christmas";
    
    fast_cannon_1 = QPixmap(R::get("fast_cannon_1"));
    fast_cannon_2 = QPixmap(R::get("fast_cannon_2"));
    fast_cannon_3 = QPixmap(R::get("fast_cannon_3.png"));
    
    QSize size(100, 100);
    fast_cannon_3 = fast_cannon_3.scaled(size);
    
}

QString R::get(const char *val)
{
    QString str = res_dir + "/" + val;
    return str;
}
