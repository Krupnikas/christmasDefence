#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <Game/Resource.h>
#include <Game/Scene.h>
#include <Game/Game.h>

#define TEST

/* MainView - объект приложения.
 * Он создает объекты меню и игры,
 * занимается сохранением результатов
 * Следит за разрешением и системами отсчета
 */

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT
    
public:
    
    R r;
    Scene scene;
    Game game;
    
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    
    
    
    #ifdef TEST
        void resizeEvent(QResizeEvent *);
    #endif
    
private:

    Ui::MainView *ui;
    
};

#endif // MAINVIEW_H
