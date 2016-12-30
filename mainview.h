#pragma once

#include <Game/Game.h>
#include <GameMenu/GameMenu.h>

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

    eGameStatus gameStatus;
    
    R r;
    CScene scene;

    CGame game;
    CGameMenu gameMenu;

    explicit MainView(QWidget *parent = 0);
    ~MainView();

    void resizeEvent(QResizeEvent *);
    virtual void showEvent(QShowEvent *event);
    
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    
    bool eventFilter(QObject *obj, QEvent *event);

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
