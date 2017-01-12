#include <mainview.h>
#include <QApplication>

#include <Metrics/MetricsDef.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainView w(&a);
    w.show();

    return a.exec();
}
