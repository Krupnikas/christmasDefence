#pragma once

#include <QObject>
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
#include <QOpenGLWidget>
#include <QtOpenGL/QGLFormat>

#include <memory>
#include <atomic>
#include <mutex>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>

#include <Metrics/Metrics.h>

enum class EGameStatus {
    eNotInited, eGameMenu, eLevelMenu, eGame
};

enum class ESizeType {
    eSmall, eMedium, eBig
};

enum class EScaleCenter {
    eLeftTop, eCenter
};

enum class EButtonType{
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

enum class ESound {
    eSoundtrack,
    eButtonPress,
    eShot
};

enum class ESelectionStatus {
    eNone,
    eCannonSelection,
    eCannonUpgrade
};

enum class EEdge {
    eLeft, eTop, eRight, eBottom, eInside
};

struct R
{
    QString dir;
    QString res_dir;
    QString gm_dir;
    QString lm_dir;
    
    std::shared_ptr<QPixmap> game_background;
    std::shared_ptr<QPixmap> field_background;
    std::shared_ptr<QPixmap> cannonSelectionBackground;
    std::shared_ptr<QPixmap> cannonUpgradeBackground;
    std::shared_ptr<QPixmap> imageAndNumberBackground;
    std::shared_ptr<QPixmap> userInfoBackground;
    
    std::shared_ptr<QPixmap> game_menu_background;
    std::shared_ptr<QPixmap> game_menu_caption;
    std::vector<std::shared_ptr<QPixmap>> gm_buttons;
    std::vector<std::shared_ptr<QPixmap>> gm_focused_buttons;
    std::vector<std::shared_ptr<QPixmap>> gm_pressed_buttons;
    
    std::shared_ptr<QPixmap> level_menu_background;
    std::shared_ptr<QPixmap> level_menu_caption;
    std::shared_ptr<QPixmap> level_menu_back;
    std::vector<std::shared_ptr<QPixmap>> lm_levels;
    std::vector<std::shared_ptr<QPixmap>> lm_focused_levels;
    std::vector<std::shared_ptr<QPixmap>> lm_pressed_levels;
    std::vector<std::shared_ptr<QPixmap>> lm_disabled_levels;
    
    std::shared_ptr<QPixmap> hp_icon;
    std::shared_ptr<QPixmap> coins_icon;
    std::shared_ptr<QPixmap> current_wave_icon;
    std::shared_ptr<QPixmap> wave_counter_icon;
    std::shared_ptr<QPixmap> game_menu_button;

    std::shared_ptr<QPixmap> cannonTypePreview[m::TypesOfCannon];
    std::shared_ptr<QPixmap> cannonUnableTypePreview[m::TypesOfCannon];

    std::shared_ptr<QPixmap> border_cell;
    std::shared_ptr<QPixmap> cell1;
    std::shared_ptr<QPixmap> cell2;
    std::shared_ptr<QPixmap> cellSelected;

    std::shared_ptr<QPixmap> entireRadius;

    std::shared_ptr<QPixmap> buttonClose;
    std::shared_ptr<QPixmap> buttonUpgrade;
    std::shared_ptr<QPixmap> buttonSell;
    
    std::shared_ptr<QPixmap> burn_cannon_1;
    std::shared_ptr<QPixmap> burn_cannon_2;
    std::shared_ptr<QPixmap> burn_cannon_3;
    std::shared_ptr<QPixmap> fast_cannon_1;
    std::shared_ptr<QPixmap> fast_cannon_2;
    std::shared_ptr<QPixmap> fast_cannon_3;
    std::shared_ptr<QPixmap> monster_cannon_1;
    std::shared_ptr<QPixmap> monster_cannon_2;
    std::shared_ptr<QPixmap> monster_cannon_3;
    std::shared_ptr<QPixmap> slow_cannon_1;
    std::shared_ptr<QPixmap> slow_cannon_2;
    std::shared_ptr<QPixmap> slow_cannon_3;
    
    std::shared_ptr<QPixmap> burn_bullet_1;
    std::shared_ptr<QPixmap> burn_bullet_2;
    std::shared_ptr<QPixmap> burn_bullet_3;
    std::shared_ptr<QPixmap> fast_bullet_1;
    std::shared_ptr<QPixmap> fast_bullet_2;
    std::shared_ptr<QPixmap> fast_bullet_3;
    std::shared_ptr<QPixmap> monster_bullet_1;
    std::shared_ptr<QPixmap> monster_bullet_2;
    std::shared_ptr<QPixmap> monster_bullet_3;
    std::shared_ptr<QPixmap> slow_bullet_1;
    std::shared_ptr<QPixmap> slow_bullet_2;
    std::shared_ptr<QPixmap> slow_bullet_3;
    
    std::shared_ptr<QPixmap> fast_enemy_1;
    std::shared_ptr<QPixmap> fast_enemy_2;
    std::shared_ptr<QPixmap> fast_enemy_3;
    
    std::shared_ptr<QPixmap> hp_cur;
    std::shared_ptr<QPixmap> hp_background;
    
    std::shared_ptr<QPixmap> enemy_comes;
    QString levels;
    
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
