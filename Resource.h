#pragma once

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QPixmap>
#include <QTransform>
#include <QMatrix>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>
#include <QLineF>
#include <QtCore/qmath.h>
#include <QDebug>
#include <QThread>

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>

#include <qopengl.h>
#include <QOpenGLContext>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFormat>

#include <memory>
#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>

#include <Metrics/Metrics.h>

enum class eGameStatus {
    eNotInited, eGameMenu, eLevelMenu, eGame
};

enum eSizeType {
    SMALL, MEDIUM, BIG
};

enum eScaleCenter {
    LeftTop, Center
};

enum class eButtonType{
    eBTnone,
    eBTCloseButton,
    eBTChooseFast,
    eBTChooseMonster,
    eBTChooseSlow,
    eBTChooseBurn,
    eBTcannonUpgrade,
    eBTcannonSell,
    eBTuiPause,
    eBTuiAccelerate,
    eBTgmCampaign,
    eBTgmQuickPlay,
    eBTgmDev,
    eBTgmExit,
    eBTgMenu
};

enum class eSound {
    eSoundtrack,
    eButtonPress,
    eShot
};

struct R
{
    QString dir;
    QString res_dir;
    QString gm_dir;
    QString lm_dir;
    
    QPixmap game_background;
    QPixmap field_background;
    QPixmap cannonSelectionBackground;
    QPixmap cannonUpgradeBackground;
    QPixmap imageAndNumberBackground;
    QPixmap userInfoBackground;
    
    QPixmap game_menu_background;
    QPixmap game_menu_caption;
    std::vector<QPixmap> gm_buttons;
    std::vector<QPixmap> gm_focused_buttons;
    std::vector<QPixmap> gm_pressed_buttons;
    
    QPixmap level_menu_background;
    QPixmap level_menu_caption;
    QPixmap level_menu_back;
    std::vector<QPixmap> lm_levels;
    std::vector<QPixmap> lm_focused_levels;
    std::vector<QPixmap> lm_pressed_levels;
    std::vector<QPixmap> lm_disabled_levels;
    
    QPixmap hp_icon;
    QPixmap coins_icon;
    QPixmap current_wave_icon;
    QPixmap wave_counter_icon;
    QPixmap game_menu_button;

    QPixmap cannonTypePreview[TypesOfCannon];
    QPixmap cannonUnableTypePreview[TypesOfCannon];

    QPixmap cell1;
    QPixmap cell2;
    QPixmap cellSelected;

    QPixmap entireRadius;

    QPixmap buttonClose;
    QPixmap buttonUpgrade;
    QPixmap buttonSell;
    
    QPixmap burn_cannon_1;
    QPixmap burn_cannon_2;
    QPixmap burn_cannon_3;
    QPixmap fast_cannon_1;
    QPixmap fast_cannon_2;
    QPixmap fast_cannon_3;
    QPixmap monster_cannon_1;
    QPixmap monster_cannon_2;
    QPixmap monster_cannon_3;
    QPixmap slow_cannon_1;
    QPixmap slow_cannon_2;
    QPixmap slow_cannon_3;
    
    QPixmap burn_bullet_1;
    QPixmap burn_bullet_2;
    QPixmap burn_bullet_3;
    QPixmap fast_bullet_1;
    QPixmap fast_bullet_2;
    QPixmap fast_bullet_3;
    QPixmap monster_bullet_1;
    QPixmap monster_bullet_2;
    QPixmap monster_bullet_3;
    QPixmap slow_bullet_1;
    QPixmap slow_bullet_2;
    QPixmap slow_bullet_3;
    
    QPixmap fast_enemy_1;
    QPixmap fast_enemy_2;
    QPixmap fast_enemy_3;
    
    QPixmap hp_cur;
    QPixmap hp_background;
    
    QPixmap enemy_comes;
    QString waves;
    
    QSoundEffect s_button_pressed;
    
    std::vector<QUrl> url_gunshots;
    QUrl url_cash;
    
    //QString get(QString file, QString root = QString("/"), QString subdir = QString(""));
    
    QString get(QString val);
    QString getWithPrefix(QString prefix, int num);
    
    QString getGm(QString val);
    QString getGmWithPrefix(QString prefix, int num);
    
    QString getLm(QString val);
    QString getLmWithPrefix(QString prefix, int num);
    
    QString getNameOfTypePreview(int num);
    QString getNameOfUnableTypePreview(int num);
    
    QString getSound(QString val);
    
    R();
    
};
