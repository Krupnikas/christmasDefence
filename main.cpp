#include <mainview.h>
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <Resource.h>
#include <Metrics/MetricsDef.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QPixmap pixmap("://res/christmas/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    MainView w(&a);
    w.show();

    QTimer::singleShot(1000, &splash, SLOT(close()));
    QTimer::singleShot(1000, &w, SLOT(show()));

    return a.exec();
}
