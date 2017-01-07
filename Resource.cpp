#include <Resource.h>

R::R()
{
    dir = "res/christmas/";
    res_dir = "://res/christmas/";
    gm_dir = "://gm/res/christmas/game_menu/";
    lm_dir = "://lm/res/christmas/level_menu/";
    
    //GameMenu resources
    game_menu_background = QPixmap(getGm("background"));
    game_menu_caption = QPixmap(getGm("caption"));
    
    gm_buttons.resize(GameMenuButtonNum);
    for (int i = 0; i < GameMenuButtonNum; ++i)
        gm_buttons[i] = QPixmap(getGmWithPrefix("button_", i + 1));
    
    gm_focused_buttons.resize(GameMenuButtonNum);
    for (int i = 0; i < GameMenuButtonNum; ++i)
        gm_focused_buttons[i] = QPixmap(getGmWithPrefix("focused_button_", i + 1));
    
    gm_pressed_buttons.resize(GameMenuButtonNum);    
    for (int i = 0; i < GameMenuButtonNum; ++i)
        gm_pressed_buttons[i] = QPixmap(getGmWithPrefix("pressed_button_", i + 1));

    //LevelMenu resources
    level_menu_background = QPixmap(getLm("background"));
    level_menu_caption = QPixmap(getLm("caption"));
    level_menu_back = QPixmap(getLm("back"));
    
    lm_levels.resize(LevelNum);
    for (int i = 0; i < LevelNum; ++i)
        lm_levels[i] = QPixmap(getLmWithPrefix("", i + 1));
    
    lm_focused_levels.resize(LevelNum);
    for (int i = 0; i < LevelNum; ++i)
        lm_focused_levels[i] = QPixmap(getLmWithPrefix("focused_", i + 1));

    lm_pressed_levels.resize(LevelNum);
    for (int i = 0; i < LevelNum; ++i)
        lm_pressed_levels[i] = QPixmap(getLmWithPrefix("pressed_", i + 1));
    
    
    //Game resources
    cell1 = QPixmap(get("cell1"));
    cell2 = QPixmap(get("cell2"));
    cellSelected = QPixmap(get("cellSelected"));
    
    game_background = QPixmap(get("game_background"));
    field_background = QPixmap(get("field_background"));

    cannonSelectionBackground = QPixmap(get("cannonSelectingInfoBlockBackground"));
    cannonUpgradeBackground = QPixmap(get("cannonUpgradeInfoBlockBackground"));
    imageAndNumberBackground = QPixmap(get("SmallBlockBG.png"));
    userInfoBackground = QPixmap(get("userInfoBlock.png"));
    
    hp_icon = QPixmap(get("hp.png"));
    coins_icon = QPixmap(get("coin.png"));
    wave_counter_icon = QPixmap(get("waveCounterIcon"));
    current_wave_icon = QPixmap(get("currentWaveIcon"));
    game_menu_button = QPixmap(get("menu_button"));

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
        cannonUnableTypePreview[i] = QPixmap(get(getNameOfUnableTypePreview(i)));
    }
}

/*QString R::get(QString file, QString root, QString subdir)
{
    QString result = QString(":/") + root + dir + subdir;
    return result;
}*/

QString R::get(QString val)
{
    QString str = res_dir + val;
    return str;
}

QString R::getWithPrefix(QString prefix, int num)
{
    return get(prefix + QString::number(num));
}

QString R::getGm(QString val)
{
    QString str = gm_dir + val;
    return str;
}

QString R::getGmWithPrefix(QString prefix, int num)
{
    return getGm(prefix + QString::number(num));
}

QString R::getLm(QString val)
{
    QString str = lm_dir + val;
    return str;
}

QString R::getLmWithPrefix(QString prefix, int num)
{
    return getLm(prefix + QString::number(num));
}

QString R::getNameOfTypePreview(int num)
{
    QString str = "cannons/cannonPreviewType_" + QString::number(num) + ".png";
    return str;
}

QString R::getNameOfUnableTypePreview(int num)
{
    QString str = "cannons/cannonPreviewUnableType_" + QString::number(num) + ".png";
    return str;
}
