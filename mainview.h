#pragma once

#include <Game/Game.h>
#include <Menu/GameMenu.h>
#include <Menu/LevelMenu.h>

#define TEST

/* MainView - объект приложения.
 * Он создает объекты меню и игры,
 * занимается сохранением результатов
 */

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT
    
public:

    QApplication *app;
    
    eGameStatus gameStatus;
        
    R r;
    CScene scene;
    QMediaPlaylist playlist;
    QMediaPlayer player;

    CGame game;
    CGameMenu gameMenu;
    CLevelMenu levelMenu;

    explicit MainView(QApplication *app, QWidget *parent = 0);
    ~MainView();

    void resizeEvent(QResizeEvent *) override;
    virtual void showEvent(QShowEvent *event) override;
    
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseDown(QMouseEvent *event);
    void mouseUp(QMouseEvent *event);
    
public slots:
    void setEnabled();

private:

    Ui::MainView *ui;
    
};
