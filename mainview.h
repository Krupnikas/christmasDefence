#pragma once

#include <Game/Game.h>

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
    
    R r;
    CScene scene;
    CGame game;

    explicit MainView(QWidget *parent = 0);
    ~MainView();
    
    #ifdef TEST
        void resizeEvent(QResizeEvent *);
    #endif
    virtual void showEvent(QShowEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *eventPress);

signals:
    void mousePressed(QMouseEvent *eventPress);
    
private:

    Ui::MainView *ui;
    
};
