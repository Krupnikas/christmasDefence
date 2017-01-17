#include <Resource.h>

R::R()
{
    dir = "res/christmas/";
    res_dir = "://res/christmas/";
    gm_dir = "://gm/res/christmas/game_menu/";
    lm_dir = "://lm/res/christmas/level_menu/";
    
    //GameMenu resources
    game_menu_background = std::make_shared<QPixmap>(getGm("background"));
    game_menu_caption = std::make_shared<QPixmap>(getGm("caption"));
    
    gm_buttons.resize(m::GameMenuButtonNum);
    for (int i = 0; i < m::GameMenuButtonNum; ++i)
        gm_buttons[i] = std::make_shared<QPixmap>(getGmWithPrefix("button_", i + 1));
    
    gm_focused_buttons.resize(m::GameMenuButtonNum);
    for (int i = 0; i < m::GameMenuButtonNum; ++i)
        gm_focused_buttons[i] = std::make_shared<QPixmap>(getGmWithPrefix("focused_button_", i + 1));
    
    gm_pressed_buttons.resize(m::GameMenuButtonNum);    
    for (int i = 0; i < m::GameMenuButtonNum; ++i)
        gm_pressed_buttons[i] = std::make_shared<QPixmap>(getGmWithPrefix("pressed_button_", i + 1));

    //LevelMenu resources
    level_menu_background = std::make_shared<QPixmap>(getLm("background"));
    level_menu_caption = std::make_shared<QPixmap>(getLm("caption"));
    level_menu_back = std::make_shared<QPixmap>(getLm("back"));
    
    lm_levels.resize(m::LevelNum);
    for (int i = 0; i < m::LevelNum; ++i)
        lm_levels[i] = std::make_shared<QPixmap>(getLmWithPrefix("", i + 1));
    
    lm_focused_levels.resize(m::LevelNum);
    for (int i = 0; i < m::LevelNum; ++i)
        lm_focused_levels[i] = std::make_shared<QPixmap>(getLmWithPrefix("focused_", i + 1));

    lm_pressed_levels.resize(m::LevelNum);
    for (int i = 0; i < m::LevelNum; ++i)
        lm_pressed_levels[i] = std::make_shared<QPixmap>(getLmWithPrefix("pressed_", i + 1));
    
    
    //Game resources
    border_cell = std::make_shared<QPixmap>(get("border"));
    cell1 = std::make_shared<QPixmap>(get("cell1"));
    cell2 = std::make_shared<QPixmap>(get("cell2"));
    cellSelected = std::make_shared<QPixmap>(get("cellSelected"));
    
    game_background = std::make_shared<QPixmap>(get("game_background"));
    field_background = std::make_shared<QPixmap>(get("field_background"));

    cannonSelectionBackground = std::make_shared<QPixmap>(get("cannonSelectingInfoBlockBackground"));
    cannonUpgradeBackground = std::make_shared<QPixmap>(get("cannonUpgradeInfoBlockBackground"));
    imageAndNumberBackground = std::make_shared<QPixmap>(get("SmallBlockBG.png"));
    userInfoBackground = std::make_shared<QPixmap>(get("userInfoBlock.png"));
    
    hp_icon = std::make_shared<QPixmap>(get("hp.png"));
    coins_icon = std::make_shared<QPixmap>(get("coin.png"));
    wave_counter_icon = std::make_shared<QPixmap>(get("waveCounterIcon"));
    current_wave_icon = std::make_shared<QPixmap>(get("currentWaveIcon"));
    game_menu_button = std::make_shared<QPixmap>(get("menu_button"));

    buttonUpgrade = std::make_shared<QPixmap>(get("upgrade.png"));
    buttonSell = std::make_shared<QPixmap>(get("sell.png"));
    
    entireRadius = std::make_shared<QPixmap>(get("entireRadius.png"));

    buttonClose = std::make_shared<QPixmap>(get("clo.png"));
   
    burn_cannon_1 = std::make_shared<QPixmap>(get("cannons/burn_cannon_1"));
    burn_cannon_2 = std::make_shared<QPixmap>(get("cannons/burn_cannon_2"));
    burn_cannon_3 = std::make_shared<QPixmap>(get("cannons/burn_cannon_3"));

    fast_cannon_1 = std::make_shared<QPixmap>(get("cannons/fast_cannon_1"));
    fast_cannon_2 = std::make_shared<QPixmap>(get("cannons/fast_cannon_2"));
    fast_cannon_3 = std::make_shared<QPixmap>(get("cannons/fast_cannon_3"));

    monster_cannon_1 = std::make_shared<QPixmap>(get("cannons/monster_cannon_1"));
    monster_cannon_2 = std::make_shared<QPixmap>(get("cannons/monster_cannon_2"));
    monster_cannon_3 = std::make_shared<QPixmap>(get("cannons/monster_cannon_3"));

    slow_cannon_1 = std::make_shared<QPixmap>(get("cannons/slow_cannon_1"));
    slow_cannon_2 = std::make_shared<QPixmap>(get("cannons/slow_cannon_2"));
    slow_cannon_3 = std::make_shared<QPixmap>(get("cannons/slow_cannon_3"));
    
    burn_bullet_1 = std::make_shared<QPixmap>(get("bullets/burn_bullet_1"));
    burn_bullet_2 = std::make_shared<QPixmap>(get("bullets/burn_bullet_2"));
    burn_bullet_3 = std::make_shared<QPixmap>(get("bullets/burn_bullet_3"));

    fast_bullet_1 = std::make_shared<QPixmap>(get("bullets/fast_bullet_1"));
    fast_bullet_2 = std::make_shared<QPixmap>(get("bullets/fast_bullet_2"));
    fast_bullet_3 = std::make_shared<QPixmap>(get("bullets/fast_bullet_3"));

    monster_bullet_1 = std::make_shared<QPixmap>(get("bullets/monster_bullet_1"));
    monster_bullet_2 = std::make_shared<QPixmap>(get("bullets/monster_bullet_2"));
    monster_bullet_3 = std::make_shared<QPixmap>(get("bullets/monster_bullet_3"));

    slow_bullet_1 = std::make_shared<QPixmap>(get("bullets/slow_bullet_1"));
    slow_bullet_2 = std::make_shared<QPixmap>(get("bullets/slow_bullet_2"));
    slow_bullet_3 = std::make_shared<QPixmap>(get("bullets/slow_bullet_3"));
    
    fast_enemy_1 = std::make_shared<QPixmap>(get("enemies/fast_enemy_1"));
    fast_enemy_2 = std::make_shared<QPixmap>(get("enemies/fast_enemy_2"));
    fast_enemy_3 = std::make_shared<QPixmap>(get("enemies/fast_enemy_3"));
    
    hp_cur = std::make_shared<QPixmap>(get("hp_cur"));
    hp_background = std::make_shared<QPixmap>(get("hp_background"));

    enemy_comes = std::make_shared<QPixmap>(get("enemy_comes"));
    levels = get("levels/level");
    
    s_button_pressed.setSource(QUrl(getSound("button.wav")));
    s_button_pressed.setVolume(m::SoundLevel);
    
    url_gunshots.resize(m::TypesOfCannon);
    for (int i = 0; i < m::TypesOfCannon; ++i)
    {
        QString path = getSound("gunshot") + QString::number(i + 1) + ".wav";
        url_gunshots[i] = QUrl(path);
    }
    
    url_cash = QUrl(getSound("cash.wav"));
    
    for (int i = 0; i < m::TypesOfCannon; i++)
    {
        cannonTypePreview[i] = std::make_shared<QPixmap>(get(getNameOfTypePreview(i)));
        cannonUnableTypePreview[i] = std::make_shared<QPixmap>(get(getNameOfUnableTypePreview(i)));
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

QString R::getSound(QString val)
{
    return "qrc:/" + dir + "sounds/" + val;
}
