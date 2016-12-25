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
    cannonUpgradeBackground = QPixmap(get("cannonUpgradeInfoBlockBackground"));

    buttonUpgrade = QPixmap(get("upgrade.png"));
    buttonSell = QPixmap(get("sell.png"));
    
    entireRadius = QPixmap(get("entireRadius.png"));

    buttonClose = QPixmap(get("clo.png"));
    
    burn_cannon_1 = QPixmap(get("cannons/burn_cannon_1"));
    burn_cannon_2 = QPixmap(get("cannons/burn_cannon_2"));
    burn_cannon_3 = QPixmap(get("cannons/burn_cannon_3"));

    fast_cannon_1 = QPixmap(get("cannons/fast_cannon_1"));
    fast_cannon_2 = QPixmap(get("cannons/fast_cannon_2"));
    fast_cannon_3 = QPixmap(get("cannons/fast_cannon_3"));

    monster_cannon_1 = QPixmap(get("cannons/monster_cannon_1"));
    monster_cannon_2 = QPixmap(get("cannons/monster_cannon_2"));
    monster_cannon_3 = QPixmap(get("cannons/monster_cannon_3"));

    slow_cannon_1 = QPixmap(get("cannons/slow_cannon_1"));
    slow_cannon_2 = QPixmap(get("cannons/slow_cannon_2"));
    slow_cannon_3 = QPixmap(get("cannons/slow_cannon_3"));
    
    burn_bullet_1 = QPixmap(get("bullets/burn_bullet_1"));
    burn_bullet_2 = QPixmap(get("bullets/burn_bullet_2"));
    burn_bullet_3 = QPixmap(get("bullets/burn_bullet_3"));

    fast_bullet_1 = QPixmap(get("bullets/fast_bullet_1"));
    fast_bullet_2 = QPixmap(get("bullets/fast_bullet_2"));
    fast_bullet_3 = QPixmap(get("bullets/fast_bullet_3"));

    monster_bullet_1 = QPixmap(get("bullets/monster_bullet_1"));
    monster_bullet_2 = QPixmap(get("bullets/monster_bullet_2"));
    monster_bullet_3 = QPixmap(get("bullets/monster_bullet_3"));

    slow_bullet_1 = QPixmap(get("bullets/slow_bullet_1"));
    slow_bullet_2 = QPixmap(get("bullets/slow_bullet_2"));
    slow_bullet_3 = QPixmap(get("bullets/slow_bullet_3"));
    
    fast_enemy_1 = QPixmap(get("enemies/fast_enemy_1"));
    fast_enemy_2 = QPixmap(get("enemies/fast_enemy_2"));
    fast_enemy_3 = QPixmap(get("enemies/fast_enemy_3"));
    
    hp_cur = QPixmap(get("hp_cur"));
    hp_background = QPixmap(get("hp_background"));

    enemy_comes = QPixmap(get("enemy_comes"));
    waves = get("waves/level");

    for (int i = 0; i < TypesOfCannon; i++)
    {
        cannonTypePreview[i] = QPixmap(get(getNameOfTypePreview(i)));
    }
}

QString R::get(QString val)
{
    QString str = res_dir + "/" + val;
    return str;
}

QString R::getNameOfTypePreview(int num)
{
    QString str = "cannons/cannonPreviewType_" + QString::number(num) + ".png";
    return str;
}
