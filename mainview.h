#ifndef MAINVIEW_H
#define MAINVIEW_H

#define TEST

/* MainView - объект приложения.
 * Он создает объекты меню и игры,
 * занимается сохранением результатов
 * Следит за разрешением и системами отсчета
 */

#include <QWidget>
#include <QRect>
#include <Game/resource.h>
#include <Game/Game.h>
#include <Game/Scene.h>

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT
    
public:
    
    Scene scene;

    R r;
    
    explicit MainView(QWidget *parent = 0);
    ~MainView();
    
    
    
    #ifdef TEST
        void resizeEvent(QResizeEvent *);
    #endif
    
private:

    Ui::MainView *ui;
    
};

#endif // MAINVIEW_H
